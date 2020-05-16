#include "cpu.h"
#include "bus.h"
#include "std_cpu_ops.h"
#include <stdio.h>
#include "cpu_common/cpu_ops.h"
#include "cpu_common/op_exec.h"
#include "cpu_dec/op_dec.h"
#include "cpu_dec/rx_mcdecoder.h"
#include "mpu_types.h"

CpuType virtual_cpu = {
	.cores = {
		/*
		 * INDEX 0
		 */
		{
			.core.core_id = CPU_CONFIG_CORE_ID_0,
		}
	},
};

void cpu_init(void)
{
	cpu_reset(CPU_CONFIG_CORE_ID_0);
	return;
}

static void private_cpu_reset(TargetCoreType *cpu)
{
	cpu->reg.r[0] = 0;
	cpu->reg.isp = 0x0;
	cpu->reg.usp = 0x0;
	cpu->reg.intb = 0x0;
	cpu->reg.pc = 0x0;
	cpu->reg.psw.value = 0x0;
	cpu->reg.bpc = 0x0;
	cpu->reg.bpsw.value = 0x0;
	cpu->reg.fintv = 0x0;
	cpu->reg.fpsw = 0x0;
	cpu->reg.extb = 0x0;
	memset(cpu->reg.acc0, 0, sizeof(cpu->reg.acc0));
	memset(cpu->reg.acc1, 0, sizeof(cpu->reg.acc1));
	cpu->is_halt = FALSE;
	return;
}

void cpu_reset(CoreIdType core_id)
{
	private_cpu_reset(&virtual_cpu.cores[core_id].core);
	return;
}

bool cpu_is_halt(CoreIdType core_id)
{
	return virtual_cpu.cores[core_id].core.is_halt;
}

void cpu_set_current_core(CoreIdType core_id)
{
	virtual_cpu.current_core = &virtual_cpu.cores[core_id];
	return;
}

bool cpu_has_permission(CoreIdType core_id, MpuAddressRegionEnumType region_type, CpuMemoryAccessType access_type, uint32 addr, uint32 size)
{
	//TODO
	return TRUE;
}

Std_ReturnType cpu_supply_clock(CoreIdType core_id)
{
	int ret;
	Std_ReturnType err;
	RxOpDecodedCodeType *p_decoded_code = NULL;
	RxOperationCodeType optype;
	bool permission;

	if (virtual_cpu.cores[core_id].core.is_halt == TRUE) {
		return STD_E_OK;
	}

	/*
	 * 命令取得する
	 */
	err = bus_get_pointer(core_id,
		cpu_get_pc(&virtual_cpu.cores[core_id].core),
		(uint8 **)&(virtual_cpu.cores[core_id].core.current_code));
	if (err != STD_E_OK) {
		return err;
	}

	/*
	 * デコード
	 */
	ret = rx_op_parse(virtual_cpu.cores[core_id].core.current_code,
		p_decoded_code, &optype);
	if (ret != 0) {
		printf("Decode Error\n");
		return STD_E_DECODE;
	}

	permission = cpu_has_permission(core_id,
		READONLY_MEMORY,
		CpuMemoryAccess_EXEC,
		cpu_get_pc(&virtual_cpu.cores[core_id].core),
		p_decoded_code->size);

	if (permission == FALSE) {
		return STD_E_SEGV;
	}

	if (rx_op_exec_table[optype.code_id].exec == NULL) {
		printf("Not supported code(%d fmt=%d) Error code[0]=0x%x code[1]=0x%x type_id=0x%x\n",
			optype.code_id, optype.format_id,
			virtual_cpu.cores[core_id].core.current_code[0],
			virtual_cpu.cores[core_id].core.current_code[1],
			virtual_cpu.cores[core_id].core.decoded_code.type_id);
		return STD_E_EXEC;
	}

	/*
	 * 命令実行
	 */
	ret = rx_op_exec_table[optype.code_id].exec(&virtual_cpu.cores[core_id].core);
	if (ret < 0) {
		printf("Exec Error code[0]=0x%x code[1]=0x%x type_id=0x%x code_id=%u\n",
			virtual_cpu.cores[core_id].core.current_code[0],
			virtual_cpu.cores[core_id].core.current_code[1],
			virtual_cpu.cores[core_id].core.decoded_code.type_id,
			optype.code_id);
		return STD_E_EXEC;
	}

	return STD_E_OK;
}

bool cpu_illegal_access(CoreIdType core_id)
{
	//TODO
	return FALSE;
}
