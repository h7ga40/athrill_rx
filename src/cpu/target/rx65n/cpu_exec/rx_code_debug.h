#ifndef _RX_PSEUDO_CODE_DEBUG_H_
#define _RX_PSEUDO_CODE_DEBUG_H_

#include "dbg_log.h"
#include "rx_code_type.h"

static inline void DBG_BRK(TargetCoreType *core, brk_input_type *in, brk_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_RTS(TargetCoreType *core, rts_input_type *in, rts_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_NOP(TargetCoreType *core, nop_input_type *in, nop_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BRA_A(TargetCoreType *core, bra_a_input_type *in, bra_a_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BSR_A(TargetCoreType *core, bsr_a_input_type *in, bsr_a_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SUB_2X(TargetCoreType *core, sub_2x_input_type *in, sub_2x_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_CMP_4X(TargetCoreType *core, cmp_4x_input_type *in, cmp_4x_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_ADD_2X(TargetCoreType *core, add_2x_input_type *in, add_2x_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MUL_3X(TargetCoreType *core, mul_3x_input_type *in, mul_3x_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_AND_3X(TargetCoreType *core, and_3x_input_type *in, and_3x_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_OR_3X(TargetCoreType *core, or_3x_input_type *in, or_3x_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SBB_2(TargetCoreType *core, sbb_2_input_type *in, sbb_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_ADC_3(TargetCoreType *core, adc_3_input_type *in, adc_3_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_DIV_2X(TargetCoreType *core, div_2x_input_type *in, div_2x_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_DIVU_2X(TargetCoreType *core, divu_2x_input_type *in, divu_2x_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_EMUL_2X(TargetCoreType *core, emul_2x_input_type *in, emul_2x_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_EMULU_2X(TargetCoreType *core, emulu_2x_input_type *in, emulu_2x_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_ITOF_1X(TargetCoreType *core, itof_1x_input_type *in, itof_1x_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MAX_2X(TargetCoreType *core, max_2x_input_type *in, max_2x_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MIN_2X(TargetCoreType *core, min_2x_input_type *in, min_2x_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_TST_2X(TargetCoreType *core, tst_2x_input_type *in, tst_2x_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_XCHG_1X(TargetCoreType *core, xchg_1x_input_type *in, xchg_1x_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_XOR_2X(TargetCoreType *core, xor_2x_input_type *in, xor_2x_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BRA_S(TargetCoreType *core, bra_s_input_type *in, bra_s_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BCND_S(TargetCoreType *core, bcnd_s_input_type *in, bcnd_s_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BRA_B(TargetCoreType *core, bra_b_input_type *in, bra_b_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BCND_B(TargetCoreType *core, bcnd_b_input_type *in, bcnd_b_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BRA_W(TargetCoreType *core, bra_w_input_type *in, bra_w_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BSR_W(TargetCoreType *core, bsr_w_input_type *in, bsr_w_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BCND_W(TargetCoreType *core, bcnd_w_input_type *in, bcnd_w_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_RTSD_2(TargetCoreType *core, rtsd_2_input_type *in, rtsd_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MOV_4(TargetCoreType *core, mov_4_input_type *in, mov_4_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SUB_2(TargetCoreType *core, sub_2_input_type *in, sub_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_CMP_4(TargetCoreType *core, cmp_4_input_type *in, cmp_4_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_ADD_2(TargetCoreType *core, add_2_input_type *in, add_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MUL_3(TargetCoreType *core, mul_3_input_type *in, mul_3_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_AND_3(TargetCoreType *core, and_3_input_type *in, and_3_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_OR_3(TargetCoreType *core, or_3_input_type *in, or_3_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MOVU_2(TargetCoreType *core, movu_2_input_type *in, movu_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SUB_1(TargetCoreType *core, sub_1_input_type *in, sub_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_CMP_1(TargetCoreType *core, cmp_1_input_type *in, cmp_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_ADD_1(TargetCoreType *core, add_1_input_type *in, add_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MUL_1(TargetCoreType *core, mul_1_input_type *in, mul_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_AND_1(TargetCoreType *core, and_1_input_type *in, and_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_OR_1(TargetCoreType *core, or_1_input_type *in, or_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MOV_3(TargetCoreType *core, mov_3_input_type *in, mov_3_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_RTSD_1(TargetCoreType *core, rtsd_1_input_type *in, rtsd_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SHLR_1(TargetCoreType *core, shlr_1_input_type *in, shlr_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SHAR_1(TargetCoreType *core, shar_1_input_type *in, shar_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SHLL_1(TargetCoreType *core, shll_1_input_type *in, shll_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_PUSHM(TargetCoreType *core, pushm_input_type *in, pushm_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_POPM(TargetCoreType *core, popm_input_type *in, popm_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_ADD_3(TargetCoreType *core, add_3_input_type *in, add_3_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_CMP_2(TargetCoreType *core, cmp_2_input_type *in, cmp_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_INT(TargetCoreType *core, int_input_type *in, int_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MOV_5(TargetCoreType *core, mov_5_input_type *in, mov_5_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MVTIPL(TargetCoreType *core, mvtipl_input_type *in, mvtipl_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_AND_2(TargetCoreType *core, and_2_input_type *in, and_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_CMP_3(TargetCoreType *core, cmp_3_input_type *in, cmp_3_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MUL_2(TargetCoreType *core, mul_2_input_type *in, mul_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_OR_2(TargetCoreType *core, or_2_input_type *in, or_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BSET_3(TargetCoreType *core, bset_3_input_type *in, bset_3_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BCLR_3(TargetCoreType *core, bclr_3_input_type *in, bclr_3_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BTST_3(TargetCoreType *core, btst_3_input_type *in, btst_3_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_ABS_1(TargetCoreType *core, abs_1_input_type *in, abs_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_NEG_1(TargetCoreType *core, neg_1_input_type *in, neg_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_NOT_1(TargetCoreType *core, not_1_input_type *in, not_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_ROLC(TargetCoreType *core, rolc_input_type *in, rolc_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_POP(TargetCoreType *core, pop_input_type *in, pop_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_POPC(TargetCoreType *core, popc_input_type *in, popc_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_RORC(TargetCoreType *core, rorc_input_type *in, rorc_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_PUSH_1(TargetCoreType *core, push_1_input_type *in, push_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_PUSHC(TargetCoreType *core, pushc_input_type *in, pushc_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SAT(TargetCoreType *core, sat_input_type *in, sat_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_JMP(TargetCoreType *core, jmp_input_type *in, jmp_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_JSR(TargetCoreType *core, jsr_input_type *in, jsr_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BRA_L(TargetCoreType *core, bra_l_input_type *in, bra_l_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BSR_L(TargetCoreType *core, bsr_l_input_type *in, bsr_l_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SCMPU(TargetCoreType *core, scmpu_input_type *in, scmpu_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SUNTIL_B(TargetCoreType *core, suntil_b_input_type *in, suntil_b_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SUNTIL_W(TargetCoreType *core, suntil_w_input_type *in, suntil_w_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SUNTIL_L(TargetCoreType *core, suntil_l_input_type *in, suntil_l_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SMOVU(TargetCoreType *core, smovu_input_type *in, smovu_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SWHILE_B(TargetCoreType *core, swhile_b_input_type *in, swhile_b_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SWHILE_W(TargetCoreType *core, swhile_w_input_type *in, swhile_w_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SWHILE_L(TargetCoreType *core, swhile_l_input_type *in, swhile_l_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SMOVB(TargetCoreType *core, smovb_input_type *in, smovb_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SSTR_B(TargetCoreType *core, sstr_b_input_type *in, sstr_b_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SSTR_W(TargetCoreType *core, sstr_w_input_type *in, sstr_w_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SSTR_L(TargetCoreType *core, sstr_l_input_type *in, sstr_l_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SMOVF(TargetCoreType *core, smovf_input_type *in, smovf_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_RMPA(TargetCoreType *core, rmpa_input_type *in, rmpa_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SATR(TargetCoreType *core, satr_input_type *in, satr_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_RTFI(TargetCoreType *core, rtfi_input_type *in, rtfi_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_RTE(TargetCoreType *core, rte_input_type *in, rte_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_WAIT(TargetCoreType *core, wait_input_type *in, wait_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SETPSW(TargetCoreType *core, setpsw_input_type *in, setpsw_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_CLRPSW(TargetCoreType *core, clrpsw_input_type *in, clrpsw_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MOVU_1(TargetCoreType *core, movu_1_input_type *in, movu_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MOV_1(TargetCoreType *core, mov_1_input_type *in, mov_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MOV_2(TargetCoreType *core, mov_2_input_type *in, mov_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SBB_1(TargetCoreType *core, sbb_1_input_type *in, sbb_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_NEG_2(TargetCoreType *core, neg_2_input_type *in, neg_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_ADC_2(TargetCoreType *core, adc_2_input_type *in, adc_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_ABS_2(TargetCoreType *core, abs_2_input_type *in, abs_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_NOT_2(TargetCoreType *core, not_2_input_type *in, not_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BSET_4(TargetCoreType *core, bset_4_input_type *in, bset_4_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BCLR_4(TargetCoreType *core, bclr_4_input_type *in, bclr_4_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BTST_4(TargetCoreType *core, btst_4_input_type *in, btst_4_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BNOT_4(TargetCoreType *core, bnot_4_input_type *in, bnot_4_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MAX_2(TargetCoreType *core, max_2_input_type *in, max_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MIN_2(TargetCoreType *core, min_2_input_type *in, min_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_EMUL_2(TargetCoreType *core, emul_2_input_type *in, emul_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_EMULU_2(TargetCoreType *core, emulu_2_input_type *in, emulu_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_DIV_2(TargetCoreType *core, div_2_input_type *in, div_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_DIVU_2(TargetCoreType *core, divu_2_input_type *in, divu_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_TST_2(TargetCoreType *core, tst_2_input_type *in, tst_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_XOR_2(TargetCoreType *core, xor_2_input_type *in, xor_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_XCHG_1(TargetCoreType *core, xchg_1_input_type *in, xchg_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_ITOF_1(TargetCoreType *core, itof_1_input_type *in, itof_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BSET_2(TargetCoreType *core, bset_2_input_type *in, bset_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BCLR_2(TargetCoreType *core, bclr_2_input_type *in, bclr_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BTST_2(TargetCoreType *core, btst_2_input_type *in, btst_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BNOT_2(TargetCoreType *core, bnot_2_input_type *in, bnot_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_FSUB_2(TargetCoreType *core, fsub_2_input_type *in, fsub_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_FCMP_2(TargetCoreType *core, fcmp_2_input_type *in, fcmp_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_FADD_2(TargetCoreType *core, fadd_2_input_type *in, fadd_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_FMUL_2(TargetCoreType *core, fmul_2_input_type *in, fmul_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_FDIV_2(TargetCoreType *core, fdiv_2_input_type *in, fdiv_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_FTOI(TargetCoreType *core, ftoi_input_type *in, ftoi_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_ROUND(TargetCoreType *core, round_input_type *in, round_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SCCND(TargetCoreType *core, sccnd_input_type *in, sccnd_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BMCND_1(TargetCoreType *core, bmcnd_1_input_type *in, bmcnd_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BNOT_1(TargetCoreType *core, bnot_1_input_type *in, bnot_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SHLR_3(TargetCoreType *core, shlr_3_input_type *in, shlr_3_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SHAR_3(TargetCoreType *core, shar_3_input_type *in, shar_3_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SHLL_3(TargetCoreType *core, shll_3_input_type *in, shll_3_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BMCND_2(TargetCoreType *core, bmcnd_2_input_type *in, bmcnd_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BNOT_3(TargetCoreType *core, bnot_3_input_type *in, bnot_3_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MULHI(TargetCoreType *core, mulhi_input_type *in, mulhi_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MULLO(TargetCoreType *core, mullo_input_type *in, mullo_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MACHI(TargetCoreType *core, machi_input_type *in, machi_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MACLO(TargetCoreType *core, maclo_input_type *in, maclo_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MVTACHI(TargetCoreType *core, mvtachi_input_type *in, mvtachi_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MVTACLO(TargetCoreType *core, mvtaclo_input_type *in, mvtaclo_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_RACW(TargetCoreType *core, racw_input_type *in, racw_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MVFACHI(TargetCoreType *core, mvfachi_input_type *in, mvfachi_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MVFACMI(TargetCoreType *core, mvfacmi_input_type *in, mvfacmi_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MOV_14(TargetCoreType *core, mov_14_input_type *in, mov_14_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MOV_15(TargetCoreType *core, mov_15_input_type *in, mov_15_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MOVU_4(TargetCoreType *core, movu_4_input_type *in, movu_4_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SHLR_2(TargetCoreType *core, shlr_2_input_type *in, shlr_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SHAR_2(TargetCoreType *core, shar_2_input_type *in, shar_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SHLL_2(TargetCoreType *core, shll_2_input_type *in, shll_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_ROTR_2(TargetCoreType *core, rotr_2_input_type *in, rotr_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_REVW(TargetCoreType *core, revw_input_type *in, revw_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_ROTL_2(TargetCoreType *core, rotl_2_input_type *in, rotl_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_REVL(TargetCoreType *core, revl_input_type *in, revl_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MVTC_2(TargetCoreType *core, mvtc_2_input_type *in, mvtc_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MVFC(TargetCoreType *core, mvfc_input_type *in, mvfc_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_ROTR_1(TargetCoreType *core, rotr_1_input_type *in, rotr_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_ROTL_1(TargetCoreType *core, rotl_1_input_type *in, rotl_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_FADD_1(TargetCoreType *core, fadd_1_input_type *in, fadd_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_FCMP_1(TargetCoreType *core, fcmp_1_input_type *in, fcmp_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_FDIV_1(TargetCoreType *core, fdiv_1_input_type *in, fdiv_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_FMUL_1(TargetCoreType *core, fmul_1_input_type *in, fmul_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_FSUB_1(TargetCoreType *core, fsub_1_input_type *in, fsub_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_ADC_1(TargetCoreType *core, adc_1_input_type *in, adc_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_DIV_1(TargetCoreType *core, div_1_input_type *in, div_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_DIVU_1(TargetCoreType *core, divu_1_input_type *in, divu_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_EMUL_1(TargetCoreType *core, emul_1_input_type *in, emul_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_EMULU_1(TargetCoreType *core, emulu_1_input_type *in, emulu_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MAX_1(TargetCoreType *core, max_1_input_type *in, max_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MIN_1(TargetCoreType *core, min_1_input_type *in, min_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_STNZ_1(TargetCoreType *core, stnz_1_input_type *in, stnz_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_STZ_1(TargetCoreType *core, stz_1_input_type *in, stz_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_TST_1(TargetCoreType *core, tst_1_input_type *in, tst_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_XOR_1(TargetCoreType *core, xor_1_input_type *in, xor_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MVTC_1(TargetCoreType *core, mvtc_1_input_type *in, mvtc_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MOV_10(TargetCoreType *core, mov_10_input_type *in, mov_10_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MOV_12(TargetCoreType *core, mov_12_input_type *in, mov_12_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MOVU_3(TargetCoreType *core, movu_3_input_type *in, movu_3_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_ADD_4(TargetCoreType *core, add_4_input_type *in, add_4_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_AND_4(TargetCoreType *core, and_4_input_type *in, and_4_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MUL_4(TargetCoreType *core, mul_4_input_type *in, mul_4_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_OR_4(TargetCoreType *core, or_4_input_type *in, or_4_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_SUB_3(TargetCoreType *core, sub_3_input_type *in, sub_3_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BCLR_1(TargetCoreType *core, bclr_1_input_type *in, bclr_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BSET_1(TargetCoreType *core, bset_1_input_type *in, bset_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_BTST_1(TargetCoreType *core, btst_1_input_type *in, btst_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_PUSH_2(TargetCoreType *core, push_2_input_type *in, push_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MOV_6(TargetCoreType *core, mov_6_input_type *in, mov_6_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MOV_8(TargetCoreType *core, mov_8_input_type *in, mov_8_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MOV_7(TargetCoreType *core, mov_7_input_type *in, mov_7_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MOV_9(TargetCoreType *core, mov_9_input_type *in, mov_9_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MOV_11(TargetCoreType *core, mov_11_input_type *in, mov_11_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MOV_13(TargetCoreType *core, mov_13_input_type *in, mov_13_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_FSQRT(TargetCoreType *core, fsqrt_input_type *in, fsqrt_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_FTOU(TargetCoreType *core, ftou_input_type *in, ftou_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_UTOF_1(TargetCoreType *core, utof_1_input_type *in, utof_1_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_UTOF_1X(TargetCoreType *core, utof_1x_input_type *in, utof_1x_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MOVCO(TargetCoreType *core, movco_input_type *in, movco_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MOVLI(TargetCoreType *core, movli_input_type *in, movli_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_EMACA(TargetCoreType *core, emaca_input_type *in, emaca_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_EMSBA(TargetCoreType *core, emsba_input_type *in, emsba_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_EMULA(TargetCoreType *core, emula_input_type *in, emula_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MACLH(TargetCoreType *core, maclh_input_type *in, maclh_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MSBHI(TargetCoreType *core, msbhi_input_type *in, msbhi_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MSBLH(TargetCoreType *core, msblh_input_type *in, msblh_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MSBLO(TargetCoreType *core, msblo_input_type *in, msblo_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MULLH(TargetCoreType *core, mullh_input_type *in, mullh_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MVFACGU(TargetCoreType *core, mvfacgu_input_type *in, mvfacgu_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MVFACLO(TargetCoreType *core, mvfaclo_input_type *in, mvfaclo_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_MVTACGU(TargetCoreType *core, mvtacgu_input_type *in, mvtacgu_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_RACL(TargetCoreType *core, racl_input_type *in, racl_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_RDACL(TargetCoreType *core, rdacl_input_type *in, rdacl_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_RDACW(TargetCoreType *core, rdacw_input_type *in, rdacw_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_FADD_3(TargetCoreType *core, fadd_3_input_type *in, fadd_3_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_FMUL_3(TargetCoreType *core, fmul_3_input_type *in, fmul_3_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_FSUB_3(TargetCoreType *core, fsub_3_input_type *in, fsub_3_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_STNZ_2(TargetCoreType *core, stnz_2_input_type *in, stnz_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

static inline void DBG_STZ_2(TargetCoreType *core, stz_2_input_type *in, stz_2_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
		": "
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

#endif /* !_RX_PSEUDO_CODE_DEBUG_H_ */