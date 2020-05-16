#ifndef _ARM_PSEUDO_CODE_COMMON_TYPE_H_
#define _ARM_PSEUDO_CODE_COMMON_TYPE_H_

#include "std_types.h"
#include "target_cpu.h"

#define DBG_FMT_STR	"%s "

typedef uint32 CodeStatusType;
#define DBG_FMT_CodeStatusType			"CPSR(0x%x) "
#define DBG_ARG_CodeStatusType(arg)		(*(arg))

static inline const char *DbgPassedFlag(bool flag)
{
	return ((flag != FALSE) ? "" : "[Skip]");
}

typedef bool CodeCondPassedType;
#define DBG_FMT_CodeCondPassedType		"%s "
#define DBG_ARG_CodeCondPassedType(arg)	DbgPassedFlag(*(arg))

typedef enum CtrlReg {
	CtrlReg_none,
	CtrlReg_PSW,
	CtrlReg_USP,
	CtrlReg_FPSW,
	CtrlReg_BPSW,
	CtrlReg_BPC,
	CtrlReg_ISP,
	CtrlReg_FINTV,
	CtrlReg_INTB,
	CtrlReg_EXTB,
} CtrlRegType;

typedef enum DispLen {
	DispLen_none,
	DispLen_disp0,
	DispLen_disp8,
	DispLen_disp16,
	DispLen_register
} DispLenType;

typedef enum MemEx {
	MemEx_none,
	MemEx_B,
	MemEx_UB,
	MemEx_W,
	MemEx_UW,
	MemEx_L,
	MemEx_UL,
} MemExType;

typedef enum OpSize {
	OpSize_none,
	OpSize_B = 1,
	OpSize_W = 2,
	OpSize_L = 4
} OpSizeType;

typedef enum ImLen {
	ImLen_none,
	ImLen_imm32,
	ImLen_simm8,
	ImLen_simm16,
	ImLen_simm24,
} ImLenType;

typedef enum OpCnd {
	OpCnd_EQ_Z = 0,			// Z == 1
	OpCnd_NE_NZ = 1,		// Z == 0
	OpCnd_GEU_C = 2,		// C == 1
	OpCnd_LTU_NC = 3,		// C == 0
	OpCnd_GTU = 4,			// S == 0
	OpCnd_LEU = 5,			// (C & ~Z) == 0
	OpCnd_PZ = 6,			// S == 0
	OpCnd_N = 7,			// S == 1
	OpCnd_GE = 8,			// (S ^ O) == 0
	OpCnd_LT = 9,			// (S ^ O) == 1
	OpCnd_GT = 10,			// ((S ^ O) | Z) == 0
	OpCnd_LE = 11,			// ((S ^ O) | Z) == 1
	OpCnd_O = 12,			// O == 1
	OpCnd_NO = 13,			// O == 0
	OpCnd_BRA_B = 14,		// 0
	OpCnd_Reserve = 15,		// 0
} OpCndType;

typedef enum PswFlag {
	PswFlag_none,
	PswFlag_C,
	PswFlag_Z,
	PswFlag_S,
	PswFlag_O,
	PswFlag_I,
	PswFlag_U,
} PswFlagType;

extern void bus_put_data(const TargetCoreType *core, OpSizeType sz, uint32 addr, uint32 data);
extern uint32 bus_get_data(const TargetCoreType *core, OpSizeType sz, uint32 addr);

#endif /* _ARM_PSEUDO_CODE_COMMON_TYPE_H_ */
