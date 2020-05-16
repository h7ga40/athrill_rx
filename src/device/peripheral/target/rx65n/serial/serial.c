#include "inc/serial.h"
#include "device.h"
#include "std_errno.h"
#include "mpu_types.h"
#include "device_ex_serial_ops.h"
#include "cpuemu_ops.h"
#include <stdio.h>

typedef struct {
	bool   is_support_intr;
	uint16 id;
	uint16 intno;
	uint32 last_raised_counter;
	uint32 bitrate;
	uint32 count_base;
	uint32 flush_count;
	bool   is_send_data;
	uint8 send_data;
	DeviceExSerialOpType *ops;
	DeviceClockType *dev_clock;
	uint64			start_clock;
} SerialDeviceType;

static SerialDeviceType SerialDevice[UDnChannelNum];
static void serial_set_str(bool enable, uint8 channel);
static bool serial_isset_str_ssf(uint8 channel);
static void serial_set_str_ssf(uint8 channel);

static Std_ReturnType serial_get_data8(MpuAddressRegionType *region, CoreIdType core_id, uint32 addr, uint8 *data);
static Std_ReturnType serial_get_data16(MpuAddressRegionType *region, CoreIdType core_id, uint32 addr, uint16 *data);
static Std_ReturnType serial_get_data32(MpuAddressRegionType *region, CoreIdType core_id, uint32 addr, uint32 *data);
static Std_ReturnType serial_put_data8(MpuAddressRegionType *region, CoreIdType core_id, uint32 addr, uint8 data);
static Std_ReturnType serial_put_data16(MpuAddressRegionType *region, CoreIdType core_id, uint32 addr, uint16 data);
static Std_ReturnType serial_put_data32(MpuAddressRegionType *region, CoreIdType core_id, uint32 addr, uint32 data);
static Std_ReturnType serial_get_pointer(MpuAddressRegionType *region, CoreIdType core_id, uint32 addr, uint8 **data);

MpuAddressRegionOperationType	serial_memory_operation = {
		.get_data8 		= 	serial_get_data8,
		.get_data16		=	serial_get_data16,
		.get_data32		=	serial_get_data32,

		.put_data8 		= 	serial_put_data8,
		.put_data16		=	serial_put_data16,
		.put_data32		=	serial_put_data32,

		.get_pointer	= serial_get_pointer,
};


#define CLOCK_PER_SEC	10000000U	/* 10MHz */
static MpuAddressRegionType *serial_region;

void device_init_serial(MpuAddressRegionType *region)
{
	int i = 0;
	char *path;

	for (i = 0; i < UDnChannelNum; i++) {
		SerialDevice[i].id = i;
		SerialDevice[i].is_support_intr = FALSE;
		SerialDevice[i].intno = -1;
		SerialDevice[i].is_send_data = FALSE;
		SerialDevice[i].start_clock = 0;
		SerialDevice[i].bitrate = 38400; /* bit/sec */
		SerialDevice[i].count_base = 1;
		SerialDevice[i].flush_count = 0;
		SerialDevice[i].ops = NULL;

		SerialDevice[i].last_raised_counter = 0;
	}

	SerialDevice[UDnCH0].is_support_intr = TRUE;
	SerialDevice[UDnCH0].intno = INTNO_INTUD0R;
	SerialDevice[UDnCH0].count_base = 1;

	if (cpuemu_get_devcfg_string("SERIAL_FILE_PATH", &path) == STD_E_OK) {
		SerialDevice[UDnCH1].is_support_intr = FALSE;
		SerialDevice[UDnCH1].intno = INTNO_INTUD1R;
		SerialDevice[UDnCH1].count_base = 1;
	}
	serial_region = region;

	return;
}

void device_do_serial(SerialDeviceType *serial)
{
	uint8 data;
	bool ret;

	if (serial->ops == NULL) {
		return;
	}
	if ((serial->dev_clock->clock % serial->count_base) != 0) {
		return;
	}
	/*
	 * 受信データチェック：存在している場合は，割り込みを上げる．
	 */
	if (serial_isset_str_ssf(serial->id) == FALSE) {
		if (serial->last_raised_counter == 0U) {
			ret = serial->ops->getchar(serial->id, &data);
			if (ret == TRUE) {
				serial_set_str_ssf(serial->id);
				//受信データをセットする．
				(void)serial_put_data8(serial_region, CPU_CONFIG_CORE_ID_0, (UDnRX(serial->id) & serial_region->mask), data);
				//受信割込みを上げる
				//printf("serial interrupt:%c\n", data);
				if (serial->is_support_intr == TRUE) {
					device_raise_int(serial->intno);
				}
				serial->last_raised_counter = 1000U;
			}
		}
		else {
			serial->last_raised_counter--;
		}
	}

	/*
	 * 送信データチェック：存在している場合は，データ転送する．
	 */
	if (serial->is_send_data) {
		//送信割込みを上げる
		//TODO 送信割り込みｋを上げるとサンプルプログラムがエラー終了してしまうため，一旦，コメントアウトした．
		serial_set_str(FALSE, serial->id);
		//device_raise_int(INTNO_INTUD0T);
		serial->is_send_data = FALSE;
	}
	if (serial->ops->flush != NULL) {
		if (serial->flush_count >= 100) {
			serial->ops->flush(serial->id);
			serial->flush_count = 0;
		}
		else {
			serial->flush_count++;
		}
	}

	return;
}

void device_supply_clock_serial(DeviceClockType *dev_clock)
{
#if 1
	SerialDevice[UDnCH0].dev_clock = dev_clock;
	device_do_serial(&SerialDevice[UDnCH0]);
	if (SerialDevice[UDnCH1].intno == INTNO_INTUD1R) {
		SerialDevice[UDnCH1].dev_clock = dev_clock;
		device_do_serial(&SerialDevice[UDnCH1]);
	}
#else
	int i = 0;

	for (i = 0; i < UDnChannelNum; i++) {
		if ((dev_clock->clock % SerialDevice[i].fd) != 0) {
			continue;
		}
		device_do_serial(&SerialDevice[i]);
	}
	return;
#endif
}


void device_ex_serial_register_ops(uint8 channel, DeviceExSerialOpType *ops)
{
	SerialDevice[channel].ops = ops;
	return;
}

static void serial_set_str(bool enable, uint8 channel)
{
	uint8 str;
	(void)serial_get_data8(serial_region, CPU_CONFIG_CORE_ID_0, (UDnSTR(channel) & serial_region->mask), &str);
	if (enable) {
		str |= 0x80;
	}
	else {
		str &= ~0x80;
	}
	(void)serial_put_data8(serial_region, CPU_CONFIG_CORE_ID_0, (UDnSTR(channel) & serial_region->mask), str);
	return;
}
static bool serial_isset_str_ssf(uint8 channel)
{
	uint8 str;
	(void)serial_get_data8(serial_region, CPU_CONFIG_CORE_ID_0, (UDnSTR(channel) & serial_region->mask), &str);
	return ((str & 0x10) == 0x10);
}
static void serial_set_str_ssf(uint8 channel)
{
	uint8 str;
	(void)serial_get_data8(serial_region, CPU_CONFIG_CORE_ID_0, (UDnSTR(channel) & serial_region->mask), &str);
	str |= 0x10;
	(void)serial_put_data8(serial_region, CPU_CONFIG_CORE_ID_0, (UDnSTR(channel) & serial_region->mask), str);
	//printf("str=0x%x\n", str);
	return;
}

static Std_ReturnType serial_get_data8(MpuAddressRegionType *region, CoreIdType core_id, uint32 addr, uint8 *data)
{
	uint32 off = (addr - region->start);
	*data = *((uint8*)(&region->data[off]));
	return STD_E_OK;
}
static Std_ReturnType serial_get_data16(MpuAddressRegionType *region, CoreIdType core_id, uint32 addr, uint16 *data)
{
	uint32 off = (addr - region->start);
	*data = *((uint16*)(&region->data[off]));
	return STD_E_OK;
}
static Std_ReturnType serial_get_data32(MpuAddressRegionType *region, CoreIdType core_id, uint32 addr, uint32 *data)
{
	uint32 off = (addr - region->start);
	*data = *((uint32*)(&region->data[off]));
	return STD_E_OK;
}
static Std_ReturnType serial_put_data8(MpuAddressRegionType *region, CoreIdType core_id, uint32 addr, uint8 data)
{
	uint32 off = (addr - region->start);
	*((uint8*)(&region->data[off])) = data;


	if (addr == (UDnTX(UDnCH0) & region->mask)) {
		(void)SerialDevice[UDnCH0].ops->putchar(SerialDevice[UDnCH0].id, data);
		SerialDevice[UDnCH0].is_send_data = TRUE;
		serial_set_str(TRUE, UDnCH0);
	}
	else if (addr == (UDnTX(UDnCH1) & region->mask)) {
		(void)SerialDevice[UDnCH1].ops->putchar(SerialDevice[UDnCH1].id, data);
		SerialDevice[UDnCH1].is_send_data = TRUE;
		serial_set_str(TRUE, UDnCH1);
	}
	return STD_E_OK;
}
static Std_ReturnType serial_put_data16(MpuAddressRegionType *region, CoreIdType core_id, uint32 addr, uint16 data)
{
	uint32 off = (addr - region->start);
	*((uint16*)(&region->data[off])) = data;
	return STD_E_OK;
}
static Std_ReturnType serial_put_data32(MpuAddressRegionType *region, CoreIdType core_id, uint32 addr, uint32 data)
{
	uint32 off = (addr - region->start);
	*((uint32*)(&region->data[off])) = data;
	return STD_E_OK;
}
static Std_ReturnType serial_get_pointer(MpuAddressRegionType *region, CoreIdType core_id, uint32 addr, uint8 **data)
{
	uint32 off = (addr - region->start);
	*data = &region->data[off];
	return STD_E_OK;
}

