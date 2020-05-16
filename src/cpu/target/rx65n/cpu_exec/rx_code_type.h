#ifndef _RX_PSEUDO_CODE_TYPE_H_
#define _RX_PSEUDO_CODE_TYPE_H_

#include "cpu_common/rx_code_common_type.h"

typedef struct {
	char* instrName;
} brk_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} brk_output_type;

typedef struct {
	char* instrName;
} rts_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} rts_output_type;

typedef struct {
	char* instrName;
} nop_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} nop_output_type;

typedef struct {
	char* instrName;
} bra_a_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} bra_a_output_type;

typedef struct {
	char* instrName;
} bsr_a_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} bsr_a_output_type;

typedef struct {
	char* instrName;
} sub_2x_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} sub_2x_output_type;

typedef struct {
	char* instrName;
} cmp_4x_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} cmp_4x_output_type;

typedef struct {
	char* instrName;
} add_2x_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} add_2x_output_type;

typedef struct {
	char* instrName;
} mul_3x_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mul_3x_output_type;

typedef struct {
	char* instrName;
} and_3x_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} and_3x_output_type;

typedef struct {
	char* instrName;
} or_3x_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} or_3x_output_type;

typedef struct {
	char* instrName;
} sbb_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} sbb_2_output_type;

typedef struct {
	char* instrName;
} adc_3_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} adc_3_output_type;

typedef struct {
	char* instrName;
} div_2x_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} div_2x_output_type;

typedef struct {
	char* instrName;
} divu_2x_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} divu_2x_output_type;

typedef struct {
	char* instrName;
} emul_2x_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} emul_2x_output_type;

typedef struct {
	char* instrName;
} emulu_2x_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} emulu_2x_output_type;

typedef struct {
	char* instrName;
} itof_1x_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} itof_1x_output_type;

typedef struct {
	char* instrName;
} max_2x_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} max_2x_output_type;

typedef struct {
	char* instrName;
} min_2x_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} min_2x_output_type;

typedef struct {
	char* instrName;
} tst_2x_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} tst_2x_output_type;

typedef struct {
	char* instrName;
} xchg_1x_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} xchg_1x_output_type;

typedef struct {
	char* instrName;
} xor_2x_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} xor_2x_output_type;

typedef struct {
	char* instrName;
} bra_s_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} bra_s_output_type;

typedef struct {
	char* instrName;
} bcnd_s_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} bcnd_s_output_type;

typedef struct {
	char* instrName;
} bra_b_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} bra_b_output_type;

typedef struct {
	char* instrName;
} bcnd_b_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} bcnd_b_output_type;

typedef struct {
	char* instrName;
} bra_w_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} bra_w_output_type;

typedef struct {
	char* instrName;
} bsr_w_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} bsr_w_output_type;

typedef struct {
	char* instrName;
} bcnd_w_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} bcnd_w_output_type;

typedef struct {
	char* instrName;
} rtsd_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} rtsd_2_output_type;

typedef struct {
	char* instrName;
} mov_4_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mov_4_output_type;

typedef struct {
	char* instrName;
} sub_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} sub_2_output_type;

typedef struct {
	char* instrName;
} cmp_4_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} cmp_4_output_type;

typedef struct {
	char* instrName;
} add_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} add_2_output_type;

typedef struct {
	char* instrName;
} mul_3_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mul_3_output_type;

typedef struct {
	char* instrName;
} and_3_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} and_3_output_type;

typedef struct {
	char* instrName;
} or_3_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} or_3_output_type;

typedef struct {
	char* instrName;
} movu_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} movu_2_output_type;

typedef struct {
	char* instrName;
} sub_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} sub_1_output_type;

typedef struct {
	char* instrName;
} cmp_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} cmp_1_output_type;

typedef struct {
	char* instrName;
} add_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} add_1_output_type;

typedef struct {
	char* instrName;
} mul_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mul_1_output_type;

typedef struct {
	char* instrName;
} and_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} and_1_output_type;

typedef struct {
	char* instrName;
} or_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} or_1_output_type;

typedef struct {
	char* instrName;
} mov_3_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mov_3_output_type;

typedef struct {
	char* instrName;
} rtsd_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} rtsd_1_output_type;

typedef struct {
	char* instrName;
} shlr_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} shlr_1_output_type;

typedef struct {
	char* instrName;
} shar_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} shar_1_output_type;

typedef struct {
	char* instrName;
} shll_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} shll_1_output_type;

typedef struct {
	char* instrName;
} pushm_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} pushm_output_type;

typedef struct {
	char* instrName;
} popm_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} popm_output_type;

typedef struct {
	char* instrName;
} add_3_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} add_3_output_type;

typedef struct {
	char* instrName;
} cmp_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} cmp_2_output_type;

typedef struct {
	char* instrName;
} int_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} int_output_type;

typedef struct {
	char* instrName;
} mov_5_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mov_5_output_type;

typedef struct {
	char* instrName;
} mvtipl_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mvtipl_output_type;

typedef struct {
	char* instrName;
} and_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} and_2_output_type;

typedef struct {
	char* instrName;
} cmp_3_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} cmp_3_output_type;

typedef struct {
	char* instrName;
} mul_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mul_2_output_type;

typedef struct {
	char* instrName;
} or_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} or_2_output_type;

typedef struct {
	char* instrName;
} bset_3_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} bset_3_output_type;

typedef struct {
	char* instrName;
} bclr_3_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} bclr_3_output_type;

typedef struct {
	char* instrName;
} btst_3_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} btst_3_output_type;

typedef struct {
	char* instrName;
} abs_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} abs_1_output_type;

typedef struct {
	char* instrName;
} neg_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} neg_1_output_type;

typedef struct {
	char* instrName;
} not_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} not_1_output_type;

typedef struct {
	char* instrName;
} rolc_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} rolc_output_type;

typedef struct {
	char* instrName;
} pop_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} pop_output_type;

typedef struct {
	char* instrName;
} popc_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} popc_output_type;

typedef struct {
	char* instrName;
} rorc_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} rorc_output_type;

typedef struct {
	char* instrName;
} push_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} push_1_output_type;

typedef struct {
	char* instrName;
} pushc_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} pushc_output_type;

typedef struct {
	char* instrName;
} sat_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} sat_output_type;

typedef struct {
	char* instrName;
} jmp_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} jmp_output_type;

typedef struct {
	char* instrName;
} jsr_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} jsr_output_type;

typedef struct {
	char* instrName;
} bra_l_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} bra_l_output_type;

typedef struct {
	char* instrName;
} bsr_l_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} bsr_l_output_type;

typedef struct {
	char* instrName;
} scmpu_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} scmpu_output_type;

typedef struct {
	char* instrName;
} suntil_b_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} suntil_b_output_type;

typedef struct {
	char* instrName;
} suntil_w_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} suntil_w_output_type;

typedef struct {
	char* instrName;
} suntil_l_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} suntil_l_output_type;

typedef struct {
	char* instrName;
} smovu_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} smovu_output_type;

typedef struct {
	char* instrName;
} swhile_b_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} swhile_b_output_type;

typedef struct {
	char* instrName;
} swhile_w_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} swhile_w_output_type;

typedef struct {
	char* instrName;
} swhile_l_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} swhile_l_output_type;

typedef struct {
	char* instrName;
} smovb_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} smovb_output_type;

typedef struct {
	char* instrName;
} sstr_b_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} sstr_b_output_type;

typedef struct {
	char* instrName;
} sstr_w_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} sstr_w_output_type;

typedef struct {
	char* instrName;
} sstr_l_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} sstr_l_output_type;

typedef struct {
	char* instrName;
} smovf_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} smovf_output_type;

typedef struct {
	char* instrName;
} rmpa_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} rmpa_output_type;

typedef struct {
	char* instrName;
} satr_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} satr_output_type;

typedef struct {
	char* instrName;
} rtfi_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} rtfi_output_type;

typedef struct {
	char* instrName;
} rte_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} rte_output_type;

typedef struct {
	char* instrName;
} wait_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} wait_output_type;

typedef struct {
	char* instrName;
} setpsw_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} setpsw_output_type;

typedef struct {
	char* instrName;
} clrpsw_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} clrpsw_output_type;

typedef struct {
	char* instrName;
} movu_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} movu_1_output_type;

typedef struct {
	char* instrName;
} mov_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mov_1_output_type;

typedef struct {
	char* instrName;
} mov_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mov_2_output_type;

typedef struct {
	char* instrName;
} sbb_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} sbb_1_output_type;

typedef struct {
	char* instrName;
} neg_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} neg_2_output_type;

typedef struct {
	char* instrName;
} adc_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} adc_2_output_type;

typedef struct {
	char* instrName;
} abs_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} abs_2_output_type;

typedef struct {
	char* instrName;
} not_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} not_2_output_type;

typedef struct {
	char* instrName;
} bset_4_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} bset_4_output_type;

typedef struct {
	char* instrName;
} bclr_4_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} bclr_4_output_type;

typedef struct {
	char* instrName;
} btst_4_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} btst_4_output_type;

typedef struct {
	char* instrName;
} bnot_4_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} bnot_4_output_type;

typedef struct {
	char* instrName;
} max_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} max_2_output_type;

typedef struct {
	char* instrName;
} min_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} min_2_output_type;

typedef struct {
	char* instrName;
} emul_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} emul_2_output_type;

typedef struct {
	char* instrName;
} emulu_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} emulu_2_output_type;

typedef struct {
	char* instrName;
} div_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} div_2_output_type;

typedef struct {
	char* instrName;
} divu_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} divu_2_output_type;

typedef struct {
	char* instrName;
} tst_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} tst_2_output_type;

typedef struct {
	char* instrName;
} xor_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} xor_2_output_type;

typedef struct {
	char* instrName;
} xchg_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} xchg_1_output_type;

typedef struct {
	char* instrName;
} itof_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} itof_1_output_type;

typedef struct {
	char* instrName;
} bset_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} bset_2_output_type;

typedef struct {
	char* instrName;
} bclr_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} bclr_2_output_type;

typedef struct {
	char* instrName;
} btst_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} btst_2_output_type;

typedef struct {
	char* instrName;
} bnot_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} bnot_2_output_type;

typedef struct {
	char* instrName;
} fsub_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} fsub_2_output_type;

typedef struct {
	char* instrName;
} fcmp_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} fcmp_2_output_type;

typedef struct {
	char* instrName;
} fadd_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} fadd_2_output_type;

typedef struct {
	char* instrName;
} fmul_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} fmul_2_output_type;

typedef struct {
	char* instrName;
} fdiv_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} fdiv_2_output_type;

typedef struct {
	char* instrName;
} ftoi_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} ftoi_output_type;

typedef struct {
	char* instrName;
} round_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} round_output_type;

typedef struct {
	char* instrName;
} sccnd_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} sccnd_output_type;

typedef struct {
	char* instrName;
} bmcnd_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} bmcnd_1_output_type;

typedef struct {
	char* instrName;
} bnot_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} bnot_1_output_type;

typedef struct {
	char* instrName;
} shlr_3_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} shlr_3_output_type;

typedef struct {
	char* instrName;
} shar_3_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} shar_3_output_type;

typedef struct {
	char* instrName;
} shll_3_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} shll_3_output_type;

typedef struct {
	char* instrName;
} bmcnd_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} bmcnd_2_output_type;

typedef struct {
	char* instrName;
} bnot_3_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} bnot_3_output_type;

typedef struct {
	char* instrName;
} mulhi_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mulhi_output_type;

typedef struct {
	char* instrName;
} mullo_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mullo_output_type;

typedef struct {
	char* instrName;
} machi_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} machi_output_type;

typedef struct {
	char* instrName;
} maclo_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} maclo_output_type;

typedef struct {
	char* instrName;
} mvtachi_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mvtachi_output_type;

typedef struct {
	char* instrName;
} mvtaclo_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mvtaclo_output_type;

typedef struct {
	char* instrName;
} racw_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} racw_output_type;

typedef struct {
	char* instrName;
} mvfachi_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mvfachi_output_type;

typedef struct {
	char* instrName;
} mvfacmi_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mvfacmi_output_type;

typedef struct {
	char* instrName;
} mov_14_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mov_14_output_type;

typedef struct {
	char* instrName;
} mov_15_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mov_15_output_type;

typedef struct {
	char* instrName;
} movu_4_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} movu_4_output_type;

typedef struct {
	char* instrName;
} shlr_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} shlr_2_output_type;

typedef struct {
	char* instrName;
} shar_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} shar_2_output_type;

typedef struct {
	char* instrName;
} shll_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} shll_2_output_type;

typedef struct {
	char* instrName;
} rotr_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} rotr_2_output_type;

typedef struct {
	char* instrName;
} revw_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} revw_output_type;

typedef struct {
	char* instrName;
} rotl_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} rotl_2_output_type;

typedef struct {
	char* instrName;
} revl_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} revl_output_type;

typedef struct {
	char* instrName;
} mvtc_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mvtc_2_output_type;

typedef struct {
	char* instrName;
} mvfc_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mvfc_output_type;

typedef struct {
	char* instrName;
} rotr_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} rotr_1_output_type;

typedef struct {
	char* instrName;
} rotl_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} rotl_1_output_type;

typedef struct {
	char* instrName;
} fadd_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} fadd_1_output_type;

typedef struct {
	char* instrName;
} fcmp_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} fcmp_1_output_type;

typedef struct {
	char* instrName;
} fdiv_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} fdiv_1_output_type;

typedef struct {
	char* instrName;
} fmul_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} fmul_1_output_type;

typedef struct {
	char* instrName;
} fsub_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} fsub_1_output_type;

typedef struct {
	char* instrName;
} adc_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} adc_1_output_type;

typedef struct {
	char* instrName;
} div_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} div_1_output_type;

typedef struct {
	char* instrName;
} divu_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} divu_1_output_type;

typedef struct {
	char* instrName;
} emul_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} emul_1_output_type;

typedef struct {
	char* instrName;
} emulu_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} emulu_1_output_type;

typedef struct {
	char* instrName;
} max_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} max_1_output_type;

typedef struct {
	char* instrName;
} min_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} min_1_output_type;

typedef struct {
	char* instrName;
} stnz_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} stnz_1_output_type;

typedef struct {
	char* instrName;
} stz_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} stz_1_output_type;

typedef struct {
	char* instrName;
} tst_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} tst_1_output_type;

typedef struct {
	char* instrName;
} xor_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} xor_1_output_type;

typedef struct {
	char* instrName;
} mvtc_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mvtc_1_output_type;

typedef struct {
	char* instrName;
} mov_10_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mov_10_output_type;

typedef struct {
	char* instrName;
} mov_12_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mov_12_output_type;

typedef struct {
	char* instrName;
} movu_3_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} movu_3_output_type;

typedef struct {
	char* instrName;
} add_4_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} add_4_output_type;

typedef struct {
	char* instrName;
} and_4_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} and_4_output_type;

typedef struct {
	char* instrName;
} mul_4_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mul_4_output_type;

typedef struct {
	char* instrName;
} or_4_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} or_4_output_type;

typedef struct {
	char* instrName;
} sub_3_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} sub_3_output_type;

typedef struct {
	char* instrName;
} bclr_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} bclr_1_output_type;

typedef struct {
	char* instrName;
} bset_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} bset_1_output_type;

typedef struct {
	char* instrName;
} btst_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} btst_1_output_type;

typedef struct {
	char* instrName;
} push_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} push_2_output_type;

typedef struct {
	char* instrName;
} mov_6_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mov_6_output_type;

typedef struct {
	char* instrName;
} mov_8_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mov_8_output_type;

typedef struct {
	char* instrName;
} mov_7_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mov_7_output_type;

typedef struct {
	char* instrName;
} mov_9_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mov_9_output_type;

typedef struct {
	char* instrName;
} mov_11_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mov_11_output_type;

typedef struct {
	char* instrName;
} mov_13_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mov_13_output_type;

typedef struct {
	char* instrName;
} fsqrt_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} fsqrt_output_type;

typedef struct {
	char* instrName;
} ftou_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} ftou_output_type;

typedef struct {
	char* instrName;
} utof_1_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} utof_1_output_type;

typedef struct {
	char* instrName;
} utof_1x_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} utof_1x_output_type;

typedef struct {
	char* instrName;
} movco_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} movco_output_type;

typedef struct {
	char* instrName;
} movli_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} movli_output_type;

typedef struct {
	char* instrName;
} emaca_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} emaca_output_type;

typedef struct {
	char* instrName;
} emsba_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} emsba_output_type;

typedef struct {
	char* instrName;
} emula_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} emula_output_type;

typedef struct {
	char* instrName;
} maclh_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} maclh_output_type;

typedef struct {
	char* instrName;
} msbhi_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} msbhi_output_type;

typedef struct {
	char* instrName;
} msblh_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} msblh_output_type;

typedef struct {
	char* instrName;
} msblo_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} msblo_output_type;

typedef struct {
	char* instrName;
} mullh_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mullh_output_type;

typedef struct {
	char* instrName;
} mvfacgu_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mvfacgu_output_type;

typedef struct {
	char* instrName;
} mvfaclo_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mvfaclo_output_type;

typedef struct {
	char* instrName;
} mvtacgu_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} mvtacgu_output_type;

typedef struct {
	char* instrName;
} racl_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} racl_output_type;

typedef struct {
	char* instrName;
} rdacl_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} rdacl_output_type;

typedef struct {
	char* instrName;
} rdacw_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} rdacw_output_type;

typedef struct {
	char* instrName;
} fadd_3_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} fadd_3_output_type;

typedef struct {
	char* instrName;
} fmul_3_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} fmul_3_output_type;

typedef struct {
	char* instrName;
} fsub_3_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} fsub_3_output_type;

typedef struct {
	char* instrName;
} stnz_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} stnz_2_output_type;

typedef struct {
	char* instrName;
} stz_2_input_type;

typedef struct {
	uint32	next_address;
	CodeStatusType		status;
	CodeCondPassedType	passed;
} stz_2_output_type;

#endif /* !_RX_PSEUDO_CODE_TYPE_H_ */