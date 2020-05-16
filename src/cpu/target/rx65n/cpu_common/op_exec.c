#include "cpu_common/op_exec.h"
#include "cpu_exec/op_exec_ops.h"
#include "cpu.h"
#include "mpu_types.h"
#include "std_errno.h"
#include <stdio.h>
#include "cpu_common/rx_code_common_type.h"
#include "bus.h"

uint32 cpu_get_current_core_id(void)
{
	return ((const TargetCoreType *)virtual_cpu.current_core)->core_id;
}

uint32 cpu_get_current_core_pc(void)
{
	return cpu_get_pc((const TargetCoreType *)virtual_cpu.current_core);
}

void cpu_set_core_pc(CoreIdType core_id, uint32 pc)
{
	virtual_cpu.cores[core_id].core.reg.pc = pc;
	return;
}

uint32 cpu_get_current_core_register(uint32 inx)
{
	return ((TargetCoreType *)virtual_cpu.current_core)->reg.r[inx];
}

uint32 cpu_get_current_core_sp(void)
{
	return cpu_get_sp((const TargetCoreType *)virtual_cpu.current_core);
}

CoreIdType cpu_get_core_id(const TargetCoreType *core)
{
	return core->core_id;
}

uint32 cpu_get_return_addr(const TargetCoreType *core)
{
	return 0;
}

void bus_put_data(const TargetCoreType *core, OpSizeType sz, uint32 addr, uint32 data)
{
	Std_ReturnType ret;

	switch (sz) {
	case OpSize_B:
		ret = bus_put_data8(core->core_id, addr, (uint8)data);
		break;
	case OpSize_W:
		ret = bus_put_data16(core->core_id, addr, (uint16)data);
		break;
	case OpSize_L:
		ret = bus_put_data32(core->core_id, addr, data);
		break;
	}
}

uint32 bus_get_data(const TargetCoreType *core, OpSizeType sz, uint32 addr)
{
	Std_ReturnType ret;

	switch (sz) {
	case OpSize_B: {
		uint8 data = 0;
		ret = bus_get_data8(core->core_id, addr, &data);
		return data;
	}
	case OpSize_W: {
		uint16 data = 0;
		ret = bus_get_data16(core->core_id, addr, &data);
		return data;
	}
	case OpSize_L: {
		uint32 data = 0;
		ret = bus_get_data32(core->core_id, addr, &data);
		return data;
	}
	}
}

uint72_t MAKE_UINT72(unsigned char v9,
	unsigned char v8, unsigned char v7, unsigned char v6, unsigned char v5,
	unsigned char v4, unsigned char v3, unsigned char v2, unsigned char v1)
{
	return (((uint64_t)v8 << 56) | ((uint64_t)v7 << 48)
		| ((uint64_t)v6 << 40) | ((uint64_t)v5 << 32)
		| ((uint64_t)v4 << 24) | ((uint64_t)v3 << 16)
		| ((uint64_t)v2 << 8) | ((uint64_t)v1));
}

int73_t MAKE_INT73(signed char s, unsigned char v9,
	unsigned char v8, unsigned char v7, unsigned char v6, unsigned char v5,
	unsigned char v4, unsigned char v3, unsigned char v2, unsigned char v1)
{
	return s * (((uint64_t)v8 << 56) | ((uint64_t)v7 << 48)
		| ((uint64_t)v6 << 40) | ((uint64_t)v5 << 32)
		| ((uint64_t)v4 << 24) | ((uint64_t)v3 << 16)
		| ((uint64_t)v2 << 8) | ((uint64_t)v1));
}

uint32_t hi_ui72(uint72_t value)
{
	return value >> 32;
}

uint32_t lo_ui72(uint72_t value)
{
	return value & 0xFFFFFFFFu;
}
