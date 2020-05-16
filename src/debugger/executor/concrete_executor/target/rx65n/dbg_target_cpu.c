#include "concrete_executor/target/dbg_target_cpu.h"
#include "cpu.h"
#include "symbol_ops.h"

#include <stdio.h>


static void print_register(const char *regname, uint32 addr, char *opt)
{
	uint32 funcaddr;
	int funcid;
	uint32 gladdr;
	int glid;

	funcid = symbol_pc2funcid(addr, &funcaddr);
	if (funcid >= 0) {
		printf("%s		0x%x %s(+0x%x)", regname, addr, symbol_funcid2funcname(funcid), addr - funcaddr);
	}
	else {
		glid = symbol_addr2glid(addr, &gladdr);
		if (glid >= 0) {
			printf("%s		0x%x %s(+0x%x)", regname, addr, symbol_glid2glname(glid), addr - gladdr);
		}
		else {
			printf("%s		0x%x", regname, addr);
		}
	}
	if (opt != NULL) {
		printf(" %s\n", opt);
	}
	else {
		printf("\n");
	}
	return;
}

void dbg_target_print_cpu(uint32 core_id)
{
	int i;
	char buffer[128];
	uint32 pc = virtual_cpu.cores[CPU_CONFIG_CORE_ID_0].core.reg.pc;

	print_register("PC", pc, NULL);
	for (i = 0; i < 32; i++) {
		char *opt = NULL;
		sprintf(buffer, "R%d", i);
		switch (i) {
		case 3:
			opt = "Stack Pointer";
			break;
		case 10:
			opt = "Return Value";
			break;
		case 6:
			opt = "Arg1";
			break;
		case 7:
			opt = "Arg2";
			break;
		case 8:
			opt = "Arg3";
			break;
		case 9:
			opt = "Arg4";
			break;
		default:
			break;
		}
		print_register(buffer, virtual_cpu.cores[CPU_CONFIG_CORE_ID_0].core.reg.r[i], opt);
	}
	printf("ISP		0x%x\n", virtual_cpu.cores[CPU_CONFIG_CORE_ID_0].core.reg.isp);
	printf("USP		0x%x\n", virtual_cpu.cores[CPU_CONFIG_CORE_ID_0].core.reg.usp);
	printf("INTB		0x%x\n", virtual_cpu.cores[CPU_CONFIG_CORE_ID_0].core.reg.intb);
	printf("PC		0x%x\n", virtual_cpu.cores[CPU_CONFIG_CORE_ID_0].core.reg.pc);
	printf("PSW		0x%x\n", virtual_cpu.cores[CPU_CONFIG_CORE_ID_0].core.reg.psw);
	printf("BPC		0x%x\n", virtual_cpu.cores[CPU_CONFIG_CORE_ID_0].core.reg.bpc);
	printf("BPSW		0x%x\n", virtual_cpu.cores[CPU_CONFIG_CORE_ID_0].core.reg.bpsw);
	printf("FINTV		0x%x\n", virtual_cpu.cores[CPU_CONFIG_CORE_ID_0].core.reg.fintv);
	printf("FPSW		0x%x\n", virtual_cpu.cores[CPU_CONFIG_CORE_ID_0].core.reg.fpsw);
	printf("EXTB		0x%x\n", virtual_cpu.cores[CPU_CONFIG_CORE_ID_0].core.reg.extb);
	printf("ACC0		0x%08x%08x\n",
		hi_ui72(virtual_cpu.cores[CPU_CONFIG_CORE_ID_0].core.reg.acc[0]),
		lo_ui72(virtual_cpu.cores[CPU_CONFIG_CORE_ID_0].core.reg.acc[0]));
	printf("ACC1		0x%08x%08x\n",
		hi_ui72(virtual_cpu.cores[CPU_CONFIG_CORE_ID_0].core.reg.acc[1]),
		lo_ui72(virtual_cpu.cores[CPU_CONFIG_CORE_ID_0].core.reg.acc[1]));

	return;
}
