#ifndef _RX_MC_DECODER_H_
#define _RX_MC_DECODER_H_

#include <stdint.h>

typedef uint8_t rx_uint8;
typedef uint16_t rx_uint16;
typedef uint32_t rx_uint24;
typedef uint32_t rx_uint32;

#define RX_OP_CODE_FORMAT_NUM	RX_OP_CODE_FORMAT_UNKNOWN

typedef enum {
	RX_OP_CODE_FORMAT_BRK,
	RX_OP_CODE_FORMAT_RTS,
	RX_OP_CODE_FORMAT_NOP,
	RX_OP_CODE_FORMAT_BRA_A,
	RX_OP_CODE_FORMAT_BSR_A,
	RX_OP_CODE_FORMAT_SUB_2X,
	RX_OP_CODE_FORMAT_CMP_4X,
	RX_OP_CODE_FORMAT_ADD_2X,
	RX_OP_CODE_FORMAT_MUL_3X,
	RX_OP_CODE_FORMAT_AND_3X,
	RX_OP_CODE_FORMAT_OR_3X,
	RX_OP_CODE_FORMAT_SBB_2,
	RX_OP_CODE_FORMAT_ADC_3,
	RX_OP_CODE_FORMAT_DIV_2X,
	RX_OP_CODE_FORMAT_DIVU_2X,
	RX_OP_CODE_FORMAT_EMUL_2X,
	RX_OP_CODE_FORMAT_EMULU_2X,
	RX_OP_CODE_FORMAT_ITOF_1X,
	RX_OP_CODE_FORMAT_MAX_2X,
	RX_OP_CODE_FORMAT_MIN_2X,
	RX_OP_CODE_FORMAT_TST_2X,
	RX_OP_CODE_FORMAT_XCHG_1X,
	RX_OP_CODE_FORMAT_XOR_2X,
	RX_OP_CODE_FORMAT_BRA_S,
	RX_OP_CODE_FORMAT_BCND_S,
	RX_OP_CODE_FORMAT_BRA_B,
	RX_OP_CODE_FORMAT_BCND_B,
	RX_OP_CODE_FORMAT_BRA_W,
	RX_OP_CODE_FORMAT_BSR_W,
	RX_OP_CODE_FORMAT_BCND_W,
	RX_OP_CODE_FORMAT_RTSD_2,
	RX_OP_CODE_FORMAT_MOV_4,
	RX_OP_CODE_FORMAT_SUB_2,
	RX_OP_CODE_FORMAT_CMP_4,
	RX_OP_CODE_FORMAT_ADD_2,
	RX_OP_CODE_FORMAT_MUL_3,
	RX_OP_CODE_FORMAT_AND_3,
	RX_OP_CODE_FORMAT_OR_3,
	RX_OP_CODE_FORMAT_MOVU_2,
	RX_OP_CODE_FORMAT_SUB_1,
	RX_OP_CODE_FORMAT_CMP_1,
	RX_OP_CODE_FORMAT_ADD_1,
	RX_OP_CODE_FORMAT_MUL_1,
	RX_OP_CODE_FORMAT_AND_1,
	RX_OP_CODE_FORMAT_OR_1,
	RX_OP_CODE_FORMAT_MOV_3,
	RX_OP_CODE_FORMAT_RTSD_1,
	RX_OP_CODE_FORMAT_SHLR_1,
	RX_OP_CODE_FORMAT_SHAR_1,
	RX_OP_CODE_FORMAT_SHLL_1,
	RX_OP_CODE_FORMAT_PUSHM,
	RX_OP_CODE_FORMAT_POPM,
	RX_OP_CODE_FORMAT_ADD_3,
	RX_OP_CODE_FORMAT_CMP_2,
	RX_OP_CODE_FORMAT_INT,
	RX_OP_CODE_FORMAT_MOV_5,
	RX_OP_CODE_FORMAT_MVTIPL,
	RX_OP_CODE_FORMAT_AND_2,
	RX_OP_CODE_FORMAT_CMP_3,
	RX_OP_CODE_FORMAT_MUL_2,
	RX_OP_CODE_FORMAT_OR_2,
	RX_OP_CODE_FORMAT_BSET_3,
	RX_OP_CODE_FORMAT_BCLR_3,
	RX_OP_CODE_FORMAT_BTST_3,
	RX_OP_CODE_FORMAT_ABS_1,
	RX_OP_CODE_FORMAT_NEG_1,
	RX_OP_CODE_FORMAT_NOT_1,
	RX_OP_CODE_FORMAT_ROLC,
	RX_OP_CODE_FORMAT_POP,
	RX_OP_CODE_FORMAT_POPC,
	RX_OP_CODE_FORMAT_RORC,
	RX_OP_CODE_FORMAT_PUSH_1,
	RX_OP_CODE_FORMAT_PUSHC,
	RX_OP_CODE_FORMAT_SAT,
	RX_OP_CODE_FORMAT_JMP,
	RX_OP_CODE_FORMAT_JSR,
	RX_OP_CODE_FORMAT_BRA_L,
	RX_OP_CODE_FORMAT_BSR_L,
	RX_OP_CODE_FORMAT_SCMPU,
	RX_OP_CODE_FORMAT_SUNTIL_B,
	RX_OP_CODE_FORMAT_SUNTIL_W,
	RX_OP_CODE_FORMAT_SUNTIL_L,
	RX_OP_CODE_FORMAT_SMOVU,
	RX_OP_CODE_FORMAT_SWHILE_B,
	RX_OP_CODE_FORMAT_SWHILE_W,
	RX_OP_CODE_FORMAT_SWHILE_L,
	RX_OP_CODE_FORMAT_SMOVB,
	RX_OP_CODE_FORMAT_SSTR_B,
	RX_OP_CODE_FORMAT_SSTR_W,
	RX_OP_CODE_FORMAT_SSTR_L,
	RX_OP_CODE_FORMAT_SMOVF,
	RX_OP_CODE_FORMAT_RMPA,
	RX_OP_CODE_FORMAT_SATR,
	RX_OP_CODE_FORMAT_RTFI,
	RX_OP_CODE_FORMAT_RTE,
	RX_OP_CODE_FORMAT_WAIT,
	RX_OP_CODE_FORMAT_SETPSW,
	RX_OP_CODE_FORMAT_CLRPSW,
	RX_OP_CODE_FORMAT_MOVU_1,
	RX_OP_CODE_FORMAT_MOV_1,
	RX_OP_CODE_FORMAT_MOV_2,
	RX_OP_CODE_FORMAT_SBB_1,
	RX_OP_CODE_FORMAT_NEG_2,
	RX_OP_CODE_FORMAT_ADC_2,
	RX_OP_CODE_FORMAT_ABS_2,
	RX_OP_CODE_FORMAT_NOT_2,
	RX_OP_CODE_FORMAT_BSET_4,
	RX_OP_CODE_FORMAT_BCLR_4,
	RX_OP_CODE_FORMAT_BTST_4,
	RX_OP_CODE_FORMAT_BNOT_4,
	RX_OP_CODE_FORMAT_MAX_2,
	RX_OP_CODE_FORMAT_MIN_2,
	RX_OP_CODE_FORMAT_EMUL_2,
	RX_OP_CODE_FORMAT_EMULU_2,
	RX_OP_CODE_FORMAT_DIV_2,
	RX_OP_CODE_FORMAT_DIVU_2,
	RX_OP_CODE_FORMAT_TST_2,
	RX_OP_CODE_FORMAT_XOR_2,
	RX_OP_CODE_FORMAT_XCHG_1,
	RX_OP_CODE_FORMAT_ITOF_1,
	RX_OP_CODE_FORMAT_BSET_2,
	RX_OP_CODE_FORMAT_BCLR_2,
	RX_OP_CODE_FORMAT_BTST_2,
	RX_OP_CODE_FORMAT_BNOT_2,
	RX_OP_CODE_FORMAT_FSUB_2,
	RX_OP_CODE_FORMAT_FCMP_2,
	RX_OP_CODE_FORMAT_FADD_2,
	RX_OP_CODE_FORMAT_FMUL_2,
	RX_OP_CODE_FORMAT_FDIV_2,
	RX_OP_CODE_FORMAT_FTOI,
	RX_OP_CODE_FORMAT_ROUND,
	RX_OP_CODE_FORMAT_SCCND,
	RX_OP_CODE_FORMAT_BMCND_1,
	RX_OP_CODE_FORMAT_BNOT_1,
	RX_OP_CODE_FORMAT_SHLR_3,
	RX_OP_CODE_FORMAT_SHAR_3,
	RX_OP_CODE_FORMAT_SHLL_3,
	RX_OP_CODE_FORMAT_BMCND_2,
	RX_OP_CODE_FORMAT_BNOT_3,
	RX_OP_CODE_FORMAT_MULHI,
	RX_OP_CODE_FORMAT_MULLO,
	RX_OP_CODE_FORMAT_MACHI,
	RX_OP_CODE_FORMAT_MACLO,
	RX_OP_CODE_FORMAT_MVTACHI,
	RX_OP_CODE_FORMAT_MVTACLO,
	RX_OP_CODE_FORMAT_RACW,
	RX_OP_CODE_FORMAT_MVFACHI,
	RX_OP_CODE_FORMAT_MVFACMI,
	RX_OP_CODE_FORMAT_MOV_14,
	RX_OP_CODE_FORMAT_MOV_15,
	RX_OP_CODE_FORMAT_MOVU_4,
	RX_OP_CODE_FORMAT_SHLR_2,
	RX_OP_CODE_FORMAT_SHAR_2,
	RX_OP_CODE_FORMAT_SHLL_2,
	RX_OP_CODE_FORMAT_ROTR_2,
	RX_OP_CODE_FORMAT_REVW,
	RX_OP_CODE_FORMAT_ROTL_2,
	RX_OP_CODE_FORMAT_REVL,
	RX_OP_CODE_FORMAT_MVTC_2,
	RX_OP_CODE_FORMAT_MVFC,
	RX_OP_CODE_FORMAT_ROTR_1,
	RX_OP_CODE_FORMAT_ROTL_1,
	RX_OP_CODE_FORMAT_FADD_1,
	RX_OP_CODE_FORMAT_FCMP_1,
	RX_OP_CODE_FORMAT_FDIV_1,
	RX_OP_CODE_FORMAT_FMUL_1,
	RX_OP_CODE_FORMAT_FSUB_1,
	RX_OP_CODE_FORMAT_ADC_1,
	RX_OP_CODE_FORMAT_DIV_1,
	RX_OP_CODE_FORMAT_DIVU_1,
	RX_OP_CODE_FORMAT_EMUL_1,
	RX_OP_CODE_FORMAT_EMULU_1,
	RX_OP_CODE_FORMAT_MAX_1,
	RX_OP_CODE_FORMAT_MIN_1,
	RX_OP_CODE_FORMAT_STNZ_1,
	RX_OP_CODE_FORMAT_STZ_1,
	RX_OP_CODE_FORMAT_TST_1,
	RX_OP_CODE_FORMAT_XOR_1,
	RX_OP_CODE_FORMAT_MVTC_1,
	RX_OP_CODE_FORMAT_MOV_10,
	RX_OP_CODE_FORMAT_MOV_12,
	RX_OP_CODE_FORMAT_MOVU_3,
	RX_OP_CODE_FORMAT_ADD_4,
	RX_OP_CODE_FORMAT_AND_4,
	RX_OP_CODE_FORMAT_MUL_4,
	RX_OP_CODE_FORMAT_OR_4,
	RX_OP_CODE_FORMAT_SUB_3,
	RX_OP_CODE_FORMAT_BCLR_1,
	RX_OP_CODE_FORMAT_BSET_1,
	RX_OP_CODE_FORMAT_BTST_1,
	RX_OP_CODE_FORMAT_PUSH_2,
	RX_OP_CODE_FORMAT_MOV_6,
	RX_OP_CODE_FORMAT_MOV_8,
	RX_OP_CODE_FORMAT_MOV_7,
	RX_OP_CODE_FORMAT_MOV_9,
	RX_OP_CODE_FORMAT_MOV_11,
	RX_OP_CODE_FORMAT_MOV_13,
	RX_OP_CODE_FORMAT_FSQRT,
	RX_OP_CODE_FORMAT_FTOU,
	RX_OP_CODE_FORMAT_UTOF_1,
	RX_OP_CODE_FORMAT_UTOF_1X,
	RX_OP_CODE_FORMAT_MOVCO,
	RX_OP_CODE_FORMAT_MOVLI,
	RX_OP_CODE_FORMAT_EMACA,
	RX_OP_CODE_FORMAT_EMSBA,
	RX_OP_CODE_FORMAT_EMULA,
	RX_OP_CODE_FORMAT_MACLH,
	RX_OP_CODE_FORMAT_MSBHI,
	RX_OP_CODE_FORMAT_MSBLH,
	RX_OP_CODE_FORMAT_MSBLO,
	RX_OP_CODE_FORMAT_MULLH,
	RX_OP_CODE_FORMAT_MVFACGU,
	RX_OP_CODE_FORMAT_MVFACLO,
	RX_OP_CODE_FORMAT_MVTACGU,
	RX_OP_CODE_FORMAT_RACL,
	RX_OP_CODE_FORMAT_RDACL,
	RX_OP_CODE_FORMAT_RDACW,
	RX_OP_CODE_FORMAT_FADD_3,
	RX_OP_CODE_FORMAT_FMUL_3,
	RX_OP_CODE_FORMAT_FSUB_3,
	RX_OP_CODE_FORMAT_STNZ_2,
	RX_OP_CODE_FORMAT_STZ_2,
	RX_OP_CODE_FORMAT_UNKNOWN,
} RxOpCodeFormatId;

typedef enum {
	RxOpCodeId_brk,
	RxOpCodeId_rts,
	RxOpCodeId_nop,
	RxOpCodeId_bra_a,
	RxOpCodeId_bsr_a,
	RxOpCodeId_sub_2x,
	RxOpCodeId_cmp_4x,
	RxOpCodeId_add_2x,
	RxOpCodeId_mul_3x,
	RxOpCodeId_and_3x,
	RxOpCodeId_or_3x,
	RxOpCodeId_sbb_2,
	RxOpCodeId_adc_3,
	RxOpCodeId_div_2x,
	RxOpCodeId_divu_2x,
	RxOpCodeId_emul_2x,
	RxOpCodeId_emulu_2x,
	RxOpCodeId_itof_1x,
	RxOpCodeId_max_2x,
	RxOpCodeId_min_2x,
	RxOpCodeId_tst_2x,
	RxOpCodeId_xchg_1x,
	RxOpCodeId_xor_2x,
	RxOpCodeId_bra_s,
	RxOpCodeId_bcnd_s,
	RxOpCodeId_bra_b,
	RxOpCodeId_bcnd_b,
	RxOpCodeId_bra_w,
	RxOpCodeId_bsr_w,
	RxOpCodeId_bcnd_w,
	RxOpCodeId_rtsd_2,
	RxOpCodeId_mov_4,
	RxOpCodeId_sub_2,
	RxOpCodeId_cmp_4,
	RxOpCodeId_add_2,
	RxOpCodeId_mul_3,
	RxOpCodeId_and_3,
	RxOpCodeId_or_3,
	RxOpCodeId_movu_2,
	RxOpCodeId_sub_1,
	RxOpCodeId_cmp_1,
	RxOpCodeId_add_1,
	RxOpCodeId_mul_1,
	RxOpCodeId_and_1,
	RxOpCodeId_or_1,
	RxOpCodeId_mov_3,
	RxOpCodeId_rtsd_1,
	RxOpCodeId_shlr_1,
	RxOpCodeId_shar_1,
	RxOpCodeId_shll_1,
	RxOpCodeId_pushm,
	RxOpCodeId_popm,
	RxOpCodeId_add_3,
	RxOpCodeId_cmp_2,
	RxOpCodeId_int,
	RxOpCodeId_mov_5,
	RxOpCodeId_mvtipl,
	RxOpCodeId_and_2,
	RxOpCodeId_cmp_3,
	RxOpCodeId_mul_2,
	RxOpCodeId_or_2,
	RxOpCodeId_bset_3,
	RxOpCodeId_bclr_3,
	RxOpCodeId_btst_3,
	RxOpCodeId_abs_1,
	RxOpCodeId_neg_1,
	RxOpCodeId_not_1,
	RxOpCodeId_rolc,
	RxOpCodeId_pop,
	RxOpCodeId_popc,
	RxOpCodeId_rorc,
	RxOpCodeId_push_1,
	RxOpCodeId_pushc,
	RxOpCodeId_sat,
	RxOpCodeId_jmp,
	RxOpCodeId_jsr,
	RxOpCodeId_bra_l,
	RxOpCodeId_bsr_l,
	RxOpCodeId_scmpu,
	RxOpCodeId_suntil_b,
	RxOpCodeId_suntil_w,
	RxOpCodeId_suntil_l,
	RxOpCodeId_smovu,
	RxOpCodeId_swhile_b,
	RxOpCodeId_swhile_w,
	RxOpCodeId_swhile_l,
	RxOpCodeId_smovb,
	RxOpCodeId_sstr_b,
	RxOpCodeId_sstr_w,
	RxOpCodeId_sstr_l,
	RxOpCodeId_smovf,
	RxOpCodeId_rmpa,
	RxOpCodeId_satr,
	RxOpCodeId_rtfi,
	RxOpCodeId_rte,
	RxOpCodeId_wait,
	RxOpCodeId_setpsw,
	RxOpCodeId_clrpsw,
	RxOpCodeId_movu_1,
	RxOpCodeId_mov_1,
	RxOpCodeId_mov_2,
	RxOpCodeId_sbb_1,
	RxOpCodeId_neg_2,
	RxOpCodeId_adc_2,
	RxOpCodeId_abs_2,
	RxOpCodeId_not_2,
	RxOpCodeId_bset_4,
	RxOpCodeId_bclr_4,
	RxOpCodeId_btst_4,
	RxOpCodeId_bnot_4,
	RxOpCodeId_max_2,
	RxOpCodeId_min_2,
	RxOpCodeId_emul_2,
	RxOpCodeId_emulu_2,
	RxOpCodeId_div_2,
	RxOpCodeId_divu_2,
	RxOpCodeId_tst_2,
	RxOpCodeId_xor_2,
	RxOpCodeId_xchg_1,
	RxOpCodeId_itof_1,
	RxOpCodeId_bset_2,
	RxOpCodeId_bclr_2,
	RxOpCodeId_btst_2,
	RxOpCodeId_bnot_2,
	RxOpCodeId_fsub_2,
	RxOpCodeId_fcmp_2,
	RxOpCodeId_fadd_2,
	RxOpCodeId_fmul_2,
	RxOpCodeId_fdiv_2,
	RxOpCodeId_ftoi,
	RxOpCodeId_round,
	RxOpCodeId_sccnd,
	RxOpCodeId_bmcnd_1,
	RxOpCodeId_bnot_1,
	RxOpCodeId_shlr_3,
	RxOpCodeId_shar_3,
	RxOpCodeId_shll_3,
	RxOpCodeId_bmcnd_2,
	RxOpCodeId_bnot_3,
	RxOpCodeId_mulhi,
	RxOpCodeId_mullo,
	RxOpCodeId_machi,
	RxOpCodeId_maclo,
	RxOpCodeId_mvtachi,
	RxOpCodeId_mvtaclo,
	RxOpCodeId_racw,
	RxOpCodeId_mvfachi,
	RxOpCodeId_mvfacmi,
	RxOpCodeId_mov_14,
	RxOpCodeId_mov_15,
	RxOpCodeId_movu_4,
	RxOpCodeId_shlr_2,
	RxOpCodeId_shar_2,
	RxOpCodeId_shll_2,
	RxOpCodeId_rotr_2,
	RxOpCodeId_revw,
	RxOpCodeId_rotl_2,
	RxOpCodeId_revl,
	RxOpCodeId_mvtc_2,
	RxOpCodeId_mvfc,
	RxOpCodeId_rotr_1,
	RxOpCodeId_rotl_1,
	RxOpCodeId_fadd_1,
	RxOpCodeId_fcmp_1,
	RxOpCodeId_fdiv_1,
	RxOpCodeId_fmul_1,
	RxOpCodeId_fsub_1,
	RxOpCodeId_adc_1,
	RxOpCodeId_div_1,
	RxOpCodeId_divu_1,
	RxOpCodeId_emul_1,
	RxOpCodeId_emulu_1,
	RxOpCodeId_max_1,
	RxOpCodeId_min_1,
	RxOpCodeId_stnz_1,
	RxOpCodeId_stz_1,
	RxOpCodeId_tst_1,
	RxOpCodeId_xor_1,
	RxOpCodeId_mvtc_1,
	RxOpCodeId_mov_10,
	RxOpCodeId_mov_12,
	RxOpCodeId_movu_3,
	RxOpCodeId_add_4,
	RxOpCodeId_and_4,
	RxOpCodeId_mul_4,
	RxOpCodeId_or_4,
	RxOpCodeId_sub_3,
	RxOpCodeId_bclr_1,
	RxOpCodeId_bset_1,
	RxOpCodeId_btst_1,
	RxOpCodeId_push_2,
	RxOpCodeId_mov_6,
	RxOpCodeId_mov_8,
	RxOpCodeId_mov_7,
	RxOpCodeId_mov_9,
	RxOpCodeId_mov_11,
	RxOpCodeId_mov_13,
	RxOpCodeId_fsqrt,
	RxOpCodeId_ftou,
	RxOpCodeId_utof_1,
	RxOpCodeId_utof_1x,
	RxOpCodeId_movco,
	RxOpCodeId_movli,
	RxOpCodeId_emaca,
	RxOpCodeId_emsba,
	RxOpCodeId_emula,
	RxOpCodeId_maclh,
	RxOpCodeId_msbhi,
	RxOpCodeId_msblh,
	RxOpCodeId_msblo,
	RxOpCodeId_mullh,
	RxOpCodeId_mvfacgu,
	RxOpCodeId_mvfaclo,
	RxOpCodeId_mvtacgu,
	RxOpCodeId_racl,
	RxOpCodeId_rdacl,
	RxOpCodeId_rdacw,
	RxOpCodeId_fadd_3,
	RxOpCodeId_fmul_3,
	RxOpCodeId_fsub_3,
	RxOpCodeId_stnz_2,
	RxOpCodeId_stz_2,
	RxOpCodeId_Num,
} RxOpCodeId;

typedef struct {
	RxOpCodeFormatId	format_id;
	RxOpCodeId		code_id;
} RxOperationCodeType;



typedef struct {
	uint8_t _dummy;
} RxOpCodeFormatType_brk;

typedef struct {
	uint8_t _dummy;
} RxOpCodeFormatType_rts;

typedef struct {
	uint8_t _dummy;
} RxOpCodeFormatType_nop;

typedef struct {
	rx_uint32 pcdsp;	/* 23-0 */
} RxOpCodeFormatType_bra_a;

typedef struct {
	rx_uint32 pcdsp;	/* 23-0 */
} RxOpCodeFormatType_bsr_a;

typedef struct {
	rx_uint8 mi;	/* 15-14 */
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_sub_2x;

typedef struct {
	rx_uint8 mi;	/* 15-14 */
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_cmp_4x;

typedef struct {
	rx_uint8 mi;	/* 15-14 */
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_add_2x;

typedef struct {
	rx_uint8 mi;	/* 15-14 */
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_mul_3x;

typedef struct {
	rx_uint8 mi;	/* 15-14 */
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_and_3x;

typedef struct {
	rx_uint8 mi;	/* 15-14 */
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_or_3x;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_sbb_2;

typedef struct {
	rx_uint8 mi;	/* 23-22 */
	rx_uint8 ld;	/* 17-16 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_adc_3;

typedef struct {
	rx_uint8 mi;	/* 23-22 */
	rx_uint8 ld;	/* 17-16 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_div_2x;

typedef struct {
	rx_uint8 mi;	/* 23-22 */
	rx_uint8 ld;	/* 17-16 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_divu_2x;

typedef struct {
	rx_uint8 mi;	/* 23-22 */
	rx_uint8 ld;	/* 17-16 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_emul_2x;

typedef struct {
	rx_uint8 mi;	/* 23-22 */
	rx_uint8 ld;	/* 17-16 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_emulu_2x;

typedef struct {
	rx_uint8 mi;	/* 23-22 */
	rx_uint8 ld;	/* 17-16 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_itof_1x;

typedef struct {
	rx_uint8 mi;	/* 23-22 */
	rx_uint8 ld;	/* 17-16 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_max_2x;

typedef struct {
	rx_uint8 mi;	/* 23-22 */
	rx_uint8 ld;	/* 17-16 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_min_2x;

typedef struct {
	rx_uint8 mi;	/* 23-22 */
	rx_uint8 ld;	/* 17-16 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_tst_2x;

typedef struct {
	rx_uint8 mi;	/* 23-22 */
	rx_uint8 ld;	/* 17-16 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_xchg_1x;

typedef struct {
	rx_uint8 mi;	/* 23-22 */
	rx_uint8 ld;	/* 17-16 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_xor_2x;

typedef struct {
	rx_uint8 dsp;	/* 2-0 */
} RxOpCodeFormatType_bra_s;

typedef struct {
	rx_uint8 cd;	/* 3-3 */
	rx_uint8 dsp;	/* 2-0 */
} RxOpCodeFormatType_bcnd_s;

typedef struct {
	rx_uint8 pcdsp;	/* 7-0 */
} RxOpCodeFormatType_bra_b;

typedef struct {
	rx_uint8 cd;	/* 11-8 */
	rx_uint8 pcdsp;	/* 7-0 */
} RxOpCodeFormatType_bcnd_b;

typedef struct {
	rx_uint16 pcdsp;	/* 15-0 */
} RxOpCodeFormatType_bra_w;

typedef struct {
	rx_uint16 pcdsp;	/* 15-0 */
} RxOpCodeFormatType_bsr_w;

typedef struct {
	rx_uint8 cd;	/* 16-16 */
	rx_uint16 pcdsp;	/* 15-0 */
} RxOpCodeFormatType_bcnd_w;

typedef struct {
	rx_uint8 rd;	/* 7-4 */
	rx_uint8 rd2;	/* 3-0 */
} RxOpCodeFormatType_rtsd_2;

typedef struct {
	rx_uint8 sz;	/* 9-8 */
	rx_uint8 dsp;	/* 7-7, 3-0 */
	rx_uint8 rd;	/* 6-4 */
} RxOpCodeFormatType_mov_4;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_sub_2;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_cmp_4;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_add_2;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_mul_3;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_and_3;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_or_3;

typedef struct {
	rx_uint8 sz;	/* 10-10 */
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_movu_2;

typedef struct {
	rx_uint8 imm;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_sub_1;

typedef struct {
	rx_uint8 imm;	/* 7-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_cmp_1;

typedef struct {
	rx_uint8 imm;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_add_1;

typedef struct {
	rx_uint8 imm;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_mul_1;

typedef struct {
	rx_uint8 imm;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_and_1;

typedef struct {
	rx_uint8 imm;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_or_1;

typedef struct {
	rx_uint8 imm;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_mov_3;

typedef struct {
	rx_uint8 uimm;	/* 7-0 */
} RxOpCodeFormatType_rtsd_1;

typedef struct {
	rx_uint8 imm;	/* 8-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_shlr_1;

typedef struct {
	rx_uint8 imm;	/* 8-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_shar_1;

typedef struct {
	rx_uint8 imm;	/* 8-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_shll_1;

typedef struct {
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_pushm;

typedef struct {
	rx_uint8 rd;	/* 7-4 */
	rx_uint8 rd2;	/* 3-0 */
} RxOpCodeFormatType_popm;

typedef struct {
	rx_uint8 li;	/* 9-8 */
	rx_uint8 rs2;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_add_3;

typedef struct {
	rx_uint8 rs2;	/* 11-8 */
	rx_uint8 uimm;	/* 7-0 */
} RxOpCodeFormatType_cmp_2;

typedef struct {
	rx_uint8 imm;	/* 7-0 */
} RxOpCodeFormatType_int;

typedef struct {
	rx_uint8 rd;	/* 11-8 */
	rx_uint8 uimm;	/* 7-0 */
} RxOpCodeFormatType_mov_5;

typedef struct {
	rx_uint8 imm;	/* 3-0 */
} RxOpCodeFormatType_mvtipl;

typedef struct {
	rx_uint8 li;	/* 9-8 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_and_2;

typedef struct {
	rx_uint8 li;	/* 9-8 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_cmp_3;

typedef struct {
	rx_uint8 li;	/* 9-8 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_mul_2;

typedef struct {
	rx_uint8 li;	/* 9-8 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_or_2;

typedef struct {
	rx_uint8 imm;	/* 8-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_bset_3;

typedef struct {
	rx_uint8 imm;	/* 8-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_bclr_3;

typedef struct {
	rx_uint8 imm;	/* 8-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_btst_3;

typedef struct {
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_abs_1;

typedef struct {
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_neg_1;

typedef struct {
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_not_1;

typedef struct {
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_rolc;

typedef struct {
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_pop;

typedef struct {
	rx_uint8 cr;	/* 3-0 */
} RxOpCodeFormatType_popc;

typedef struct {
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_rorc;

typedef struct {
	rx_uint8 sz;	/* 5-4 */
	rx_uint8 rs;	/* 3-0 */
} RxOpCodeFormatType_push_1;

typedef struct {
	rx_uint8 cr;	/* 3-0 */
} RxOpCodeFormatType_pushc;

typedef struct {
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_sat;

typedef struct {
	rx_uint8 rs;	/* 3-0 */
} RxOpCodeFormatType_jmp;

typedef struct {
	rx_uint8 rs;	/* 3-0 */
} RxOpCodeFormatType_jsr;

typedef struct {
	rx_uint8 rs;	/* 3-0 */
} RxOpCodeFormatType_bra_l;

typedef struct {
	rx_uint8 rs;	/* 3-0 */
} RxOpCodeFormatType_bsr_l;

typedef struct {
	uint8_t _dummy;
} RxOpCodeFormatType_scmpu;

typedef struct {
	uint8_t _dummy;
} RxOpCodeFormatType_suntil_b;

typedef struct {
	uint8_t _dummy;
} RxOpCodeFormatType_suntil_w;

typedef struct {
	uint8_t _dummy;
} RxOpCodeFormatType_suntil_l;

typedef struct {
	uint8_t _dummy;
} RxOpCodeFormatType_smovu;

typedef struct {
	uint8_t _dummy;
} RxOpCodeFormatType_swhile_b;

typedef struct {
	uint8_t _dummy;
} RxOpCodeFormatType_swhile_w;

typedef struct {
	uint8_t _dummy;
} RxOpCodeFormatType_swhile_l;

typedef struct {
	uint8_t _dummy;
} RxOpCodeFormatType_smovb;

typedef struct {
	uint8_t _dummy;
} RxOpCodeFormatType_sstr_b;

typedef struct {
	uint8_t _dummy;
} RxOpCodeFormatType_sstr_w;

typedef struct {
	uint8_t _dummy;
} RxOpCodeFormatType_sstr_l;

typedef struct {
	uint8_t _dummy;
} RxOpCodeFormatType_smovf;

typedef struct {
	rx_uint8 sz;	/* 1-0 */
} RxOpCodeFormatType_rmpa;

typedef struct {
	uint8_t _dummy;
} RxOpCodeFormatType_satr;

typedef struct {
	uint8_t _dummy;
} RxOpCodeFormatType_rtfi;

typedef struct {
	uint8_t _dummy;
} RxOpCodeFormatType_rte;

typedef struct {
	uint8_t _dummy;
} RxOpCodeFormatType_wait;

typedef struct {
	rx_uint8 cb;	/* 3-0 */
} RxOpCodeFormatType_setpsw;

typedef struct {
	rx_uint8 cb;	/* 3-0 */
} RxOpCodeFormatType_clrpsw;

typedef struct {
	rx_uint8 sz;	/* 11-11 */
	rx_uint8 dsp;	/* 10-7, 3-3 */
	rx_uint8 rs;	/* 6-4 */
	rx_uint8 rd;	/* 2-0 */
} RxOpCodeFormatType_movu_1;

typedef struct {
	rx_uint8 sz;	/* 13-12 */
	rx_uint8 dsp;	/* 10-7, 3-3 */
	rx_uint8 rd;	/* 6-4 */
	rx_uint8 rs;	/* 2-0 */
} RxOpCodeFormatType_mov_1;

typedef struct {
	rx_uint8 sz;	/* 13-12 */
	rx_uint8 dsp;	/* 10-7, 3-3 */
	rx_uint8 rs;	/* 6-4 */
	rx_uint8 rd;	/* 2-0 */
} RxOpCodeFormatType_mov_2;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_sbb_1;

typedef struct {
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_neg_2;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_adc_2;

typedef struct {
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_abs_2;

typedef struct {
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_not_2;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rd;	/* 7-4 */
	rx_uint8 rs;	/* 3-0 */
} RxOpCodeFormatType_bset_4;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rd;	/* 7-4 */
	rx_uint8 rs;	/* 3-0 */
} RxOpCodeFormatType_bclr_4;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs2;	/* 7-4 */
	rx_uint8 rs;	/* 3-0 */
} RxOpCodeFormatType_btst_4;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rd;	/* 7-4 */
	rx_uint8 rs;	/* 3-0 */
} RxOpCodeFormatType_bnot_4;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_max_2;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_min_2;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_emul_2;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_emulu_2;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_div_2;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_divu_2;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_tst_2;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_xor_2;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_xchg_1;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_itof_1;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rd;	/* 7-4 */
	rx_uint8 rs;	/* 3-0 */
} RxOpCodeFormatType_bset_2;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rd;	/* 7-4 */
	rx_uint8 rs;	/* 3-0 */
} RxOpCodeFormatType_bclr_2;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs2;	/* 7-4 */
	rx_uint8 rs;	/* 3-0 */
} RxOpCodeFormatType_btst_2;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rd;	/* 7-4 */
	rx_uint8 rs;	/* 3-0 */
} RxOpCodeFormatType_bnot_2;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_fsub_2;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_fcmp_2;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_fadd_2;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_fmul_2;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_fdiv_2;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_ftoi;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_round;

typedef struct {
	rx_uint8 sz;	/* 11-10 */
	rx_uint8 id;	/* 9-8 */
	rx_uint8 rd;	/* 7-4 */
	rx_uint8 cd;	/* 3-0 */
} RxOpCodeFormatType_sccnd;

typedef struct {
	rx_uint8 imm;	/* 12-10 */
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rd;	/* 7-4 */
	rx_uint8 cd;	/* 3-0 */
} RxOpCodeFormatType_bmcnd_1;

typedef struct {
	rx_uint8 imm;	/* 12-10 */
	rx_uint8 id;	/* 9-8 */
	rx_uint8 rd;	/* 7-4 */
} RxOpCodeFormatType_bnot_1;

typedef struct {
	rx_uint8 imm;	/* 12-8 */
	rx_uint8 rs2;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_shlr_3;

typedef struct {
	rx_uint8 imm;	/* 12-8 */
	rx_uint8 rs2;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_shar_3;

typedef struct {
	rx_uint8 imm;	/* 12-8 */
	rx_uint8 rs2;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_shll_3;

typedef struct {
	rx_uint8 imm;	/* 12-8 */
	rx_uint8 cd;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_bmcnd_2;

typedef struct {
	rx_uint8 imm;	/* 12-8 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_bnot_3;

typedef struct {
	rx_uint8 a;	/* 11-11 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_mulhi;

typedef struct {
	rx_uint8 a;	/* 11-11 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_mullo;

typedef struct {
	rx_uint8 a;	/* 11-11 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_machi;

typedef struct {
	rx_uint8 a;	/* 11-11 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_maclo;

typedef struct {
	rx_uint8 a;	/* 7-7 */
	rx_uint8 rs;	/* 3-0 */
} RxOpCodeFormatType_mvtachi;

typedef struct {
	rx_uint8 a;	/* 7-7 */
	rx_uint8 rs;	/* 3-0 */
} RxOpCodeFormatType_mvtaclo;

typedef struct {
	rx_uint8 a;	/* 7-7 */
	rx_uint8 imm;	/* 4-4 */
} RxOpCodeFormatType_racw;

typedef struct {
	rx_uint8 imm;	/* 8-8, 6-6 */
	rx_uint8 a;	/* 7-7 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_mvfachi;

typedef struct {
	rx_uint8 imm;	/* 8-8, 6-6 */
	rx_uint8 a;	/* 7-7 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_mvfacmi;

typedef struct {
	rx_uint8 ad;	/* 11-10 */
	rx_uint8 sz;	/* 9-8 */
	rx_uint8 rd;	/* 7-4 */
	rx_uint8 rs;	/* 3-0 */
} RxOpCodeFormatType_mov_14;

typedef struct {
	rx_uint8 ad;	/* 11-10 */
	rx_uint8 sz;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_mov_15;

typedef struct {
	rx_uint8 ad;	/* 11-10 */
	rx_uint8 sz;	/* 8-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_movu_4;

typedef struct {
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_shlr_2;

typedef struct {
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_shar_2;

typedef struct {
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_shll_2;

typedef struct {
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_rotr_2;

typedef struct {
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_revw;

typedef struct {
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_rotl_2;

typedef struct {
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_revl;

typedef struct {
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 cr;	/* 3-0 */
} RxOpCodeFormatType_mvtc_2;

typedef struct {
	rx_uint8 cr;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_mvfc;

typedef struct {
	rx_uint8 imm;	/* 8-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_rotr_1;

typedef struct {
	rx_uint8 imm;	/* 8-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_rotl_1;

typedef struct {
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_fadd_1;

typedef struct {
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_fcmp_1;

typedef struct {
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_fdiv_1;

typedef struct {
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_fmul_1;

typedef struct {
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_fsub_1;

typedef struct {
	rx_uint8 li;	/* 11-10 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_adc_1;

typedef struct {
	rx_uint8 li;	/* 11-10 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_div_1;

typedef struct {
	rx_uint8 li;	/* 11-10 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_divu_1;

typedef struct {
	rx_uint8 li;	/* 11-10 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_emul_1;

typedef struct {
	rx_uint8 li;	/* 11-10 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_emulu_1;

typedef struct {
	rx_uint8 li;	/* 11-10 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_max_1;

typedef struct {
	rx_uint8 li;	/* 11-10 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_min_1;

typedef struct {
	rx_uint8 li;	/* 11-10 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_stnz_1;

typedef struct {
	rx_uint8 li;	/* 11-10 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_stz_1;

typedef struct {
	rx_uint8 li;	/* 11-10 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_tst_1;

typedef struct {
	rx_uint8 li;	/* 11-10 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_xor_1;

typedef struct {
	rx_uint8 li;	/* 11-10 */
	rx_uint8 cr;	/* 3-0 */
} RxOpCodeFormatType_mvtc_1;

typedef struct {
	rx_uint8 sz;	/* 13-12 */
	rx_uint8 ri;	/* 11-8 */
	rx_uint8 rb;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_mov_10;

typedef struct {
	rx_uint8 sz;	/* 13-12 */
	rx_uint8 ri;	/* 11-8 */
	rx_uint8 rb;	/* 7-4 */
	rx_uint8 rs;	/* 3-0 */
} RxOpCodeFormatType_mov_12;

typedef struct {
	rx_uint8 sz;	/* 12-12 */
	rx_uint8 ri;	/* 11-8 */
	rx_uint8 rb;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_movu_3;

typedef struct {
	rx_uint8 rd;	/* 11-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_add_4;

typedef struct {
	rx_uint8 rd;	/* 11-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_and_4;

typedef struct {
	rx_uint8 rd;	/* 11-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_mul_4;

typedef struct {
	rx_uint8 rd;	/* 11-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_or_4;

typedef struct {
	rx_uint8 rd;	/* 11-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_sub_3;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rd;	/* 7-4 */
	rx_uint8 imm;	/* 2-0 */
} RxOpCodeFormatType_bclr_1;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rd;	/* 7-4 */
	rx_uint8 rs;	/* 3-0 */
} RxOpCodeFormatType_bset_1;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs2;	/* 7-4 */
	rx_uint8 imm;	/* 2-0 */
} RxOpCodeFormatType_btst_1;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 sz;	/* 1-0 */
} RxOpCodeFormatType_push_2;

typedef struct {
	rx_uint8 rd;	/* 7-4 */
	rx_uint8 li;	/* 3-2 */
} RxOpCodeFormatType_mov_6;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rd;	/* 7-4 */
	rx_uint8 li;	/* 3-2 */
	rx_uint8 sz;	/* 1-0 */
} RxOpCodeFormatType_mov_8;

typedef struct {
	rx_uint8 sz;	/* 13-12 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_mov_7;

typedef struct {
	rx_uint8 sz;	/* 13-12 */
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_mov_9;

typedef struct {
	rx_uint8 sz;	/* 13-12 */
	rx_uint8 ld;	/* 11-10 */
	rx_uint8 rd;	/* 7-4 */
	rx_uint8 rs;	/* 3-0 */
} RxOpCodeFormatType_mov_11;

typedef struct {
	rx_uint8 sz;	/* 13-12 */
	rx_uint8 ldd;	/* 11-10 */
	rx_uint8 lds;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_mov_13;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_fsqrt;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_ftou;

typedef struct {
	rx_uint8 ld;	/* 9-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_utof_1;

typedef struct {
	rx_uint8 mi;	/* 23-22 */
	rx_uint8 ld;	/* 17-16 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_utof_1x;

typedef struct {
	rx_uint8 rd;	/* 7-4 */
	rx_uint8 rs;	/* 3-0 */
} RxOpCodeFormatType_movco;

typedef struct {
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_movli;

typedef struct {
	rx_uint8 a;	/* 11-11 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_emaca;

typedef struct {
	rx_uint8 a;	/* 11-11 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_emsba;

typedef struct {
	rx_uint8 a;	/* 11-11 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_emula;

typedef struct {
	rx_uint8 a;	/* 11-11 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_maclh;

typedef struct {
	rx_uint8 a;	/* 11-11 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_msbhi;

typedef struct {
	rx_uint8 a;	/* 11-11 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_msblh;

typedef struct {
	rx_uint8 a;	/* 11-11 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_msblo;

typedef struct {
	rx_uint8 a;	/* 11-11 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_mullh;

typedef struct {
	rx_uint8 imm;	/* 8-8, 6-6 */
	rx_uint8 a;	/* 7-7 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_mvfacgu;

typedef struct {
	rx_uint8 imm;	/* 8-8, 6-6 */
	rx_uint8 a;	/* 7-7 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_mvfaclo;

typedef struct {
	rx_uint8 a;	/* 7-7 */
	rx_uint8 rs;	/* 3-0 */
} RxOpCodeFormatType_mvtacgu;

typedef struct {
	rx_uint8 a;	/* 7-7 */
	rx_uint8 imm;	/* 4-4 */
} RxOpCodeFormatType_racl;

typedef struct {
	rx_uint8 a;	/* 7-7 */
	rx_uint8 imm;	/* 4-4 */
} RxOpCodeFormatType_rdacl;

typedef struct {
	rx_uint8 a;	/* 7-7 */
	rx_uint8 imm;	/* 4-4 */
} RxOpCodeFormatType_rdacw;

typedef struct {
	rx_uint8 rd;	/* 11-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_fadd_3;

typedef struct {
	rx_uint8 rd;	/* 11-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_fmul_3;

typedef struct {
	rx_uint8 rd;	/* 11-8 */
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rs2;	/* 3-0 */
} RxOpCodeFormatType_fsub_3;

typedef struct {
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_stnz_2;

typedef struct {
	rx_uint8 rs;	/* 7-4 */
	rx_uint8 rd;	/* 3-0 */
} RxOpCodeFormatType_stz_2;


typedef struct {
	RxOpCodeFormatId type_id;
	union {
		RxOpCodeFormatType_brk rx_brk;
		RxOpCodeFormatType_rts rx_rts;
		RxOpCodeFormatType_nop rx_nop;
		RxOpCodeFormatType_bra_a rx_bra_a;
		RxOpCodeFormatType_bsr_a rx_bsr_a;
		RxOpCodeFormatType_sub_2x rx_sub_2x;
		RxOpCodeFormatType_cmp_4x rx_cmp_4x;
		RxOpCodeFormatType_add_2x rx_add_2x;
		RxOpCodeFormatType_mul_3x rx_mul_3x;
		RxOpCodeFormatType_and_3x rx_and_3x;
		RxOpCodeFormatType_or_3x rx_or_3x;
		RxOpCodeFormatType_sbb_2 rx_sbb_2;
		RxOpCodeFormatType_adc_3 rx_adc_3;
		RxOpCodeFormatType_div_2x rx_div_2x;
		RxOpCodeFormatType_divu_2x rx_divu_2x;
		RxOpCodeFormatType_emul_2x rx_emul_2x;
		RxOpCodeFormatType_emulu_2x rx_emulu_2x;
		RxOpCodeFormatType_itof_1x rx_itof_1x;
		RxOpCodeFormatType_max_2x rx_max_2x;
		RxOpCodeFormatType_min_2x rx_min_2x;
		RxOpCodeFormatType_tst_2x rx_tst_2x;
		RxOpCodeFormatType_xchg_1x rx_xchg_1x;
		RxOpCodeFormatType_xor_2x rx_xor_2x;
		RxOpCodeFormatType_bra_s rx_bra_s;
		RxOpCodeFormatType_bcnd_s rx_bcnd_s;
		RxOpCodeFormatType_bra_b rx_bra_b;
		RxOpCodeFormatType_bcnd_b rx_bcnd_b;
		RxOpCodeFormatType_bra_w rx_bra_w;
		RxOpCodeFormatType_bsr_w rx_bsr_w;
		RxOpCodeFormatType_bcnd_w rx_bcnd_w;
		RxOpCodeFormatType_rtsd_2 rx_rtsd_2;
		RxOpCodeFormatType_mov_4 rx_mov_4;
		RxOpCodeFormatType_sub_2 rx_sub_2;
		RxOpCodeFormatType_cmp_4 rx_cmp_4;
		RxOpCodeFormatType_add_2 rx_add_2;
		RxOpCodeFormatType_mul_3 rx_mul_3;
		RxOpCodeFormatType_and_3 rx_and_3;
		RxOpCodeFormatType_or_3 rx_or_3;
		RxOpCodeFormatType_movu_2 rx_movu_2;
		RxOpCodeFormatType_sub_1 rx_sub_1;
		RxOpCodeFormatType_cmp_1 rx_cmp_1;
		RxOpCodeFormatType_add_1 rx_add_1;
		RxOpCodeFormatType_mul_1 rx_mul_1;
		RxOpCodeFormatType_and_1 rx_and_1;
		RxOpCodeFormatType_or_1 rx_or_1;
		RxOpCodeFormatType_mov_3 rx_mov_3;
		RxOpCodeFormatType_rtsd_1 rx_rtsd_1;
		RxOpCodeFormatType_shlr_1 rx_shlr_1;
		RxOpCodeFormatType_shar_1 rx_shar_1;
		RxOpCodeFormatType_shll_1 rx_shll_1;
		RxOpCodeFormatType_pushm rx_pushm;
		RxOpCodeFormatType_popm rx_popm;
		RxOpCodeFormatType_add_3 rx_add_3;
		RxOpCodeFormatType_cmp_2 rx_cmp_2;
		RxOpCodeFormatType_int rx_int;
		RxOpCodeFormatType_mov_5 rx_mov_5;
		RxOpCodeFormatType_mvtipl rx_mvtipl;
		RxOpCodeFormatType_and_2 rx_and_2;
		RxOpCodeFormatType_cmp_3 rx_cmp_3;
		RxOpCodeFormatType_mul_2 rx_mul_2;
		RxOpCodeFormatType_or_2 rx_or_2;
		RxOpCodeFormatType_bset_3 rx_bset_3;
		RxOpCodeFormatType_bclr_3 rx_bclr_3;
		RxOpCodeFormatType_btst_3 rx_btst_3;
		RxOpCodeFormatType_abs_1 rx_abs_1;
		RxOpCodeFormatType_neg_1 rx_neg_1;
		RxOpCodeFormatType_not_1 rx_not_1;
		RxOpCodeFormatType_rolc rx_rolc;
		RxOpCodeFormatType_pop rx_pop;
		RxOpCodeFormatType_popc rx_popc;
		RxOpCodeFormatType_rorc rx_rorc;
		RxOpCodeFormatType_push_1 rx_push_1;
		RxOpCodeFormatType_pushc rx_pushc;
		RxOpCodeFormatType_sat rx_sat;
		RxOpCodeFormatType_jmp rx_jmp;
		RxOpCodeFormatType_jsr rx_jsr;
		RxOpCodeFormatType_bra_l rx_bra_l;
		RxOpCodeFormatType_bsr_l rx_bsr_l;
		RxOpCodeFormatType_scmpu rx_scmpu;
		RxOpCodeFormatType_suntil_b rx_suntil_b;
		RxOpCodeFormatType_suntil_w rx_suntil_w;
		RxOpCodeFormatType_suntil_l rx_suntil_l;
		RxOpCodeFormatType_smovu rx_smovu;
		RxOpCodeFormatType_swhile_b rx_swhile_b;
		RxOpCodeFormatType_swhile_w rx_swhile_w;
		RxOpCodeFormatType_swhile_l rx_swhile_l;
		RxOpCodeFormatType_smovb rx_smovb;
		RxOpCodeFormatType_sstr_b rx_sstr_b;
		RxOpCodeFormatType_sstr_w rx_sstr_w;
		RxOpCodeFormatType_sstr_l rx_sstr_l;
		RxOpCodeFormatType_smovf rx_smovf;
		RxOpCodeFormatType_rmpa rx_rmpa;
		RxOpCodeFormatType_satr rx_satr;
		RxOpCodeFormatType_rtfi rx_rtfi;
		RxOpCodeFormatType_rte rx_rte;
		RxOpCodeFormatType_wait rx_wait;
		RxOpCodeFormatType_setpsw rx_setpsw;
		RxOpCodeFormatType_clrpsw rx_clrpsw;
		RxOpCodeFormatType_movu_1 rx_movu_1;
		RxOpCodeFormatType_mov_1 rx_mov_1;
		RxOpCodeFormatType_mov_2 rx_mov_2;
		RxOpCodeFormatType_sbb_1 rx_sbb_1;
		RxOpCodeFormatType_neg_2 rx_neg_2;
		RxOpCodeFormatType_adc_2 rx_adc_2;
		RxOpCodeFormatType_abs_2 rx_abs_2;
		RxOpCodeFormatType_not_2 rx_not_2;
		RxOpCodeFormatType_bset_4 rx_bset_4;
		RxOpCodeFormatType_bclr_4 rx_bclr_4;
		RxOpCodeFormatType_btst_4 rx_btst_4;
		RxOpCodeFormatType_bnot_4 rx_bnot_4;
		RxOpCodeFormatType_max_2 rx_max_2;
		RxOpCodeFormatType_min_2 rx_min_2;
		RxOpCodeFormatType_emul_2 rx_emul_2;
		RxOpCodeFormatType_emulu_2 rx_emulu_2;
		RxOpCodeFormatType_div_2 rx_div_2;
		RxOpCodeFormatType_divu_2 rx_divu_2;
		RxOpCodeFormatType_tst_2 rx_tst_2;
		RxOpCodeFormatType_xor_2 rx_xor_2;
		RxOpCodeFormatType_xchg_1 rx_xchg_1;
		RxOpCodeFormatType_itof_1 rx_itof_1;
		RxOpCodeFormatType_bset_2 rx_bset_2;
		RxOpCodeFormatType_bclr_2 rx_bclr_2;
		RxOpCodeFormatType_btst_2 rx_btst_2;
		RxOpCodeFormatType_bnot_2 rx_bnot_2;
		RxOpCodeFormatType_fsub_2 rx_fsub_2;
		RxOpCodeFormatType_fcmp_2 rx_fcmp_2;
		RxOpCodeFormatType_fadd_2 rx_fadd_2;
		RxOpCodeFormatType_fmul_2 rx_fmul_2;
		RxOpCodeFormatType_fdiv_2 rx_fdiv_2;
		RxOpCodeFormatType_ftoi rx_ftoi;
		RxOpCodeFormatType_round rx_round;
		RxOpCodeFormatType_sccnd rx_sccnd;
		RxOpCodeFormatType_bmcnd_1 rx_bmcnd_1;
		RxOpCodeFormatType_bnot_1 rx_bnot_1;
		RxOpCodeFormatType_shlr_3 rx_shlr_3;
		RxOpCodeFormatType_shar_3 rx_shar_3;
		RxOpCodeFormatType_shll_3 rx_shll_3;
		RxOpCodeFormatType_bmcnd_2 rx_bmcnd_2;
		RxOpCodeFormatType_bnot_3 rx_bnot_3;
		RxOpCodeFormatType_mulhi rx_mulhi;
		RxOpCodeFormatType_mullo rx_mullo;
		RxOpCodeFormatType_machi rx_machi;
		RxOpCodeFormatType_maclo rx_maclo;
		RxOpCodeFormatType_mvtachi rx_mvtachi;
		RxOpCodeFormatType_mvtaclo rx_mvtaclo;
		RxOpCodeFormatType_racw rx_racw;
		RxOpCodeFormatType_mvfachi rx_mvfachi;
		RxOpCodeFormatType_mvfacmi rx_mvfacmi;
		RxOpCodeFormatType_mov_14 rx_mov_14;
		RxOpCodeFormatType_mov_15 rx_mov_15;
		RxOpCodeFormatType_movu_4 rx_movu_4;
		RxOpCodeFormatType_shlr_2 rx_shlr_2;
		RxOpCodeFormatType_shar_2 rx_shar_2;
		RxOpCodeFormatType_shll_2 rx_shll_2;
		RxOpCodeFormatType_rotr_2 rx_rotr_2;
		RxOpCodeFormatType_revw rx_revw;
		RxOpCodeFormatType_rotl_2 rx_rotl_2;
		RxOpCodeFormatType_revl rx_revl;
		RxOpCodeFormatType_mvtc_2 rx_mvtc_2;
		RxOpCodeFormatType_mvfc rx_mvfc;
		RxOpCodeFormatType_rotr_1 rx_rotr_1;
		RxOpCodeFormatType_rotl_1 rx_rotl_1;
		RxOpCodeFormatType_fadd_1 rx_fadd_1;
		RxOpCodeFormatType_fcmp_1 rx_fcmp_1;
		RxOpCodeFormatType_fdiv_1 rx_fdiv_1;
		RxOpCodeFormatType_fmul_1 rx_fmul_1;
		RxOpCodeFormatType_fsub_1 rx_fsub_1;
		RxOpCodeFormatType_adc_1 rx_adc_1;
		RxOpCodeFormatType_div_1 rx_div_1;
		RxOpCodeFormatType_divu_1 rx_divu_1;
		RxOpCodeFormatType_emul_1 rx_emul_1;
		RxOpCodeFormatType_emulu_1 rx_emulu_1;
		RxOpCodeFormatType_max_1 rx_max_1;
		RxOpCodeFormatType_min_1 rx_min_1;
		RxOpCodeFormatType_stnz_1 rx_stnz_1;
		RxOpCodeFormatType_stz_1 rx_stz_1;
		RxOpCodeFormatType_tst_1 rx_tst_1;
		RxOpCodeFormatType_xor_1 rx_xor_1;
		RxOpCodeFormatType_mvtc_1 rx_mvtc_1;
		RxOpCodeFormatType_mov_10 rx_mov_10;
		RxOpCodeFormatType_mov_12 rx_mov_12;
		RxOpCodeFormatType_movu_3 rx_movu_3;
		RxOpCodeFormatType_add_4 rx_add_4;
		RxOpCodeFormatType_and_4 rx_and_4;
		RxOpCodeFormatType_mul_4 rx_mul_4;
		RxOpCodeFormatType_or_4 rx_or_4;
		RxOpCodeFormatType_sub_3 rx_sub_3;
		RxOpCodeFormatType_bclr_1 rx_bclr_1;
		RxOpCodeFormatType_bset_1 rx_bset_1;
		RxOpCodeFormatType_btst_1 rx_btst_1;
		RxOpCodeFormatType_push_2 rx_push_2;
		RxOpCodeFormatType_mov_6 rx_mov_6;
		RxOpCodeFormatType_mov_8 rx_mov_8;
		RxOpCodeFormatType_mov_7 rx_mov_7;
		RxOpCodeFormatType_mov_9 rx_mov_9;
		RxOpCodeFormatType_mov_11 rx_mov_11;
		RxOpCodeFormatType_mov_13 rx_mov_13;
		RxOpCodeFormatType_fsqrt rx_fsqrt;
		RxOpCodeFormatType_ftou rx_ftou;
		RxOpCodeFormatType_utof_1 rx_utof_1;
		RxOpCodeFormatType_utof_1x rx_utof_1x;
		RxOpCodeFormatType_movco rx_movco;
		RxOpCodeFormatType_movli rx_movli;
		RxOpCodeFormatType_emaca rx_emaca;
		RxOpCodeFormatType_emsba rx_emsba;
		RxOpCodeFormatType_emula rx_emula;
		RxOpCodeFormatType_maclh rx_maclh;
		RxOpCodeFormatType_msbhi rx_msbhi;
		RxOpCodeFormatType_msblh rx_msblh;
		RxOpCodeFormatType_msblo rx_msblo;
		RxOpCodeFormatType_mullh rx_mullh;
		RxOpCodeFormatType_mvfacgu rx_mvfacgu;
		RxOpCodeFormatType_mvfaclo rx_mvfaclo;
		RxOpCodeFormatType_mvtacgu rx_mvtacgu;
		RxOpCodeFormatType_racl rx_racl;
		RxOpCodeFormatType_rdacl rx_rdacl;
		RxOpCodeFormatType_rdacw rx_rdacw;
		RxOpCodeFormatType_fadd_3 rx_fadd_3;
		RxOpCodeFormatType_fmul_3 rx_fmul_3;
		RxOpCodeFormatType_fsub_3 rx_fsub_3;
		RxOpCodeFormatType_stnz_2 rx_stnz_2;
		RxOpCodeFormatType_stz_2 rx_stz_2;
	} code;
	uint8_t size;
} RxOpDecodedCodeType;

#define RX_OP_DECODE_MAX	(4)

extern int rx_op_parse(rx_uint16 code[RX_OP_DECODE_MAX], RxOpDecodedCodeType *decoded_code, RxOperationCodeType *optype);

struct TargetCore;
typedef struct {
	int clocks;
	int (*exec) (struct TargetCore *cpu);
} RxOpExecType;

extern RxOpExecType rx_op_exec_table[RxOpCodeId_Num];

extern int rx_op_exec_brk(struct TargetCore *core);
extern int rx_op_exec_rts(struct TargetCore *core);
extern int rx_op_exec_nop(struct TargetCore *core);
extern int rx_op_exec_bra_a(struct TargetCore *core);
extern int rx_op_exec_bsr_a(struct TargetCore *core);
extern int rx_op_exec_sub_2x(struct TargetCore *core);
extern int rx_op_exec_cmp_4x(struct TargetCore *core);
extern int rx_op_exec_add_2x(struct TargetCore *core);
extern int rx_op_exec_mul_3x(struct TargetCore *core);
extern int rx_op_exec_and_3x(struct TargetCore *core);
extern int rx_op_exec_or_3x(struct TargetCore *core);
extern int rx_op_exec_sbb_2(struct TargetCore *core);
extern int rx_op_exec_adc_3(struct TargetCore *core);
extern int rx_op_exec_div_2x(struct TargetCore *core);
extern int rx_op_exec_divu_2x(struct TargetCore *core);
extern int rx_op_exec_emul_2x(struct TargetCore *core);
extern int rx_op_exec_emulu_2x(struct TargetCore *core);
extern int rx_op_exec_itof_1x(struct TargetCore *core);
extern int rx_op_exec_max_2x(struct TargetCore *core);
extern int rx_op_exec_min_2x(struct TargetCore *core);
extern int rx_op_exec_tst_2x(struct TargetCore *core);
extern int rx_op_exec_xchg_1x(struct TargetCore *core);
extern int rx_op_exec_xor_2x(struct TargetCore *core);
extern int rx_op_exec_bra_s(struct TargetCore *core);
extern int rx_op_exec_bcnd_s(struct TargetCore *core);
extern int rx_op_exec_bra_b(struct TargetCore *core);
extern int rx_op_exec_bcnd_b(struct TargetCore *core);
extern int rx_op_exec_bra_w(struct TargetCore *core);
extern int rx_op_exec_bsr_w(struct TargetCore *core);
extern int rx_op_exec_bcnd_w(struct TargetCore *core);
extern int rx_op_exec_rtsd_2(struct TargetCore *core);
extern int rx_op_exec_mov_4(struct TargetCore *core);
extern int rx_op_exec_sub_2(struct TargetCore *core);
extern int rx_op_exec_cmp_4(struct TargetCore *core);
extern int rx_op_exec_add_2(struct TargetCore *core);
extern int rx_op_exec_mul_3(struct TargetCore *core);
extern int rx_op_exec_and_3(struct TargetCore *core);
extern int rx_op_exec_or_3(struct TargetCore *core);
extern int rx_op_exec_movu_2(struct TargetCore *core);
extern int rx_op_exec_sub_1(struct TargetCore *core);
extern int rx_op_exec_cmp_1(struct TargetCore *core);
extern int rx_op_exec_add_1(struct TargetCore *core);
extern int rx_op_exec_mul_1(struct TargetCore *core);
extern int rx_op_exec_and_1(struct TargetCore *core);
extern int rx_op_exec_or_1(struct TargetCore *core);
extern int rx_op_exec_mov_3(struct TargetCore *core);
extern int rx_op_exec_rtsd_1(struct TargetCore *core);
extern int rx_op_exec_shlr_1(struct TargetCore *core);
extern int rx_op_exec_shar_1(struct TargetCore *core);
extern int rx_op_exec_shll_1(struct TargetCore *core);
extern int rx_op_exec_pushm(struct TargetCore *core);
extern int rx_op_exec_popm(struct TargetCore *core);
extern int rx_op_exec_add_3(struct TargetCore *core);
extern int rx_op_exec_cmp_2(struct TargetCore *core);
extern int rx_op_exec_int(struct TargetCore *core);
extern int rx_op_exec_mov_5(struct TargetCore *core);
extern int rx_op_exec_mvtipl(struct TargetCore *core);
extern int rx_op_exec_and_2(struct TargetCore *core);
extern int rx_op_exec_cmp_3(struct TargetCore *core);
extern int rx_op_exec_mul_2(struct TargetCore *core);
extern int rx_op_exec_or_2(struct TargetCore *core);
extern int rx_op_exec_bset_3(struct TargetCore *core);
extern int rx_op_exec_bclr_3(struct TargetCore *core);
extern int rx_op_exec_btst_3(struct TargetCore *core);
extern int rx_op_exec_abs_1(struct TargetCore *core);
extern int rx_op_exec_neg_1(struct TargetCore *core);
extern int rx_op_exec_not_1(struct TargetCore *core);
extern int rx_op_exec_rolc(struct TargetCore *core);
extern int rx_op_exec_pop(struct TargetCore *core);
extern int rx_op_exec_popc(struct TargetCore *core);
extern int rx_op_exec_rorc(struct TargetCore *core);
extern int rx_op_exec_push_1(struct TargetCore *core);
extern int rx_op_exec_pushc(struct TargetCore *core);
extern int rx_op_exec_sat(struct TargetCore *core);
extern int rx_op_exec_jmp(struct TargetCore *core);
extern int rx_op_exec_jsr(struct TargetCore *core);
extern int rx_op_exec_bra_l(struct TargetCore *core);
extern int rx_op_exec_bsr_l(struct TargetCore *core);
extern int rx_op_exec_scmpu(struct TargetCore *core);
extern int rx_op_exec_suntil_b(struct TargetCore *core);
extern int rx_op_exec_suntil_w(struct TargetCore *core);
extern int rx_op_exec_suntil_l(struct TargetCore *core);
extern int rx_op_exec_smovu(struct TargetCore *core);
extern int rx_op_exec_swhile_b(struct TargetCore *core);
extern int rx_op_exec_swhile_w(struct TargetCore *core);
extern int rx_op_exec_swhile_l(struct TargetCore *core);
extern int rx_op_exec_smovb(struct TargetCore *core);
extern int rx_op_exec_sstr_b(struct TargetCore *core);
extern int rx_op_exec_sstr_w(struct TargetCore *core);
extern int rx_op_exec_sstr_l(struct TargetCore *core);
extern int rx_op_exec_smovf(struct TargetCore *core);
extern int rx_op_exec_rmpa(struct TargetCore *core);
extern int rx_op_exec_satr(struct TargetCore *core);
extern int rx_op_exec_rtfi(struct TargetCore *core);
extern int rx_op_exec_rte(struct TargetCore *core);
extern int rx_op_exec_wait(struct TargetCore *core);
extern int rx_op_exec_setpsw(struct TargetCore *core);
extern int rx_op_exec_clrpsw(struct TargetCore *core);
extern int rx_op_exec_movu_1(struct TargetCore *core);
extern int rx_op_exec_mov_1(struct TargetCore *core);
extern int rx_op_exec_mov_2(struct TargetCore *core);
extern int rx_op_exec_sbb_1(struct TargetCore *core);
extern int rx_op_exec_neg_2(struct TargetCore *core);
extern int rx_op_exec_adc_2(struct TargetCore *core);
extern int rx_op_exec_abs_2(struct TargetCore *core);
extern int rx_op_exec_not_2(struct TargetCore *core);
extern int rx_op_exec_bset_4(struct TargetCore *core);
extern int rx_op_exec_bclr_4(struct TargetCore *core);
extern int rx_op_exec_btst_4(struct TargetCore *core);
extern int rx_op_exec_bnot_4(struct TargetCore *core);
extern int rx_op_exec_max_2(struct TargetCore *core);
extern int rx_op_exec_min_2(struct TargetCore *core);
extern int rx_op_exec_emul_2(struct TargetCore *core);
extern int rx_op_exec_emulu_2(struct TargetCore *core);
extern int rx_op_exec_div_2(struct TargetCore *core);
extern int rx_op_exec_divu_2(struct TargetCore *core);
extern int rx_op_exec_tst_2(struct TargetCore *core);
extern int rx_op_exec_xor_2(struct TargetCore *core);
extern int rx_op_exec_xchg_1(struct TargetCore *core);
extern int rx_op_exec_itof_1(struct TargetCore *core);
extern int rx_op_exec_bset_2(struct TargetCore *core);
extern int rx_op_exec_bclr_2(struct TargetCore *core);
extern int rx_op_exec_btst_2(struct TargetCore *core);
extern int rx_op_exec_bnot_2(struct TargetCore *core);
extern int rx_op_exec_fsub_2(struct TargetCore *core);
extern int rx_op_exec_fcmp_2(struct TargetCore *core);
extern int rx_op_exec_fadd_2(struct TargetCore *core);
extern int rx_op_exec_fmul_2(struct TargetCore *core);
extern int rx_op_exec_fdiv_2(struct TargetCore *core);
extern int rx_op_exec_ftoi(struct TargetCore *core);
extern int rx_op_exec_round(struct TargetCore *core);
extern int rx_op_exec_sccnd(struct TargetCore *core);
extern int rx_op_exec_bmcnd_1(struct TargetCore *core);
extern int rx_op_exec_bnot_1(struct TargetCore *core);
extern int rx_op_exec_shlr_3(struct TargetCore *core);
extern int rx_op_exec_shar_3(struct TargetCore *core);
extern int rx_op_exec_shll_3(struct TargetCore *core);
extern int rx_op_exec_bmcnd_2(struct TargetCore *core);
extern int rx_op_exec_bnot_3(struct TargetCore *core);
extern int rx_op_exec_mulhi(struct TargetCore *core);
extern int rx_op_exec_mullo(struct TargetCore *core);
extern int rx_op_exec_machi(struct TargetCore *core);
extern int rx_op_exec_maclo(struct TargetCore *core);
extern int rx_op_exec_mvtachi(struct TargetCore *core);
extern int rx_op_exec_mvtaclo(struct TargetCore *core);
extern int rx_op_exec_racw(struct TargetCore *core);
extern int rx_op_exec_mvfachi(struct TargetCore *core);
extern int rx_op_exec_mvfacmi(struct TargetCore *core);
extern int rx_op_exec_mov_14(struct TargetCore *core);
extern int rx_op_exec_mov_15(struct TargetCore *core);
extern int rx_op_exec_movu_4(struct TargetCore *core);
extern int rx_op_exec_shlr_2(struct TargetCore *core);
extern int rx_op_exec_shar_2(struct TargetCore *core);
extern int rx_op_exec_shll_2(struct TargetCore *core);
extern int rx_op_exec_rotr_2(struct TargetCore *core);
extern int rx_op_exec_revw(struct TargetCore *core);
extern int rx_op_exec_rotl_2(struct TargetCore *core);
extern int rx_op_exec_revl(struct TargetCore *core);
extern int rx_op_exec_mvtc_2(struct TargetCore *core);
extern int rx_op_exec_mvfc(struct TargetCore *core);
extern int rx_op_exec_rotr_1(struct TargetCore *core);
extern int rx_op_exec_rotl_1(struct TargetCore *core);
extern int rx_op_exec_fadd_1(struct TargetCore *core);
extern int rx_op_exec_fcmp_1(struct TargetCore *core);
extern int rx_op_exec_fdiv_1(struct TargetCore *core);
extern int rx_op_exec_fmul_1(struct TargetCore *core);
extern int rx_op_exec_fsub_1(struct TargetCore *core);
extern int rx_op_exec_adc_1(struct TargetCore *core);
extern int rx_op_exec_div_1(struct TargetCore *core);
extern int rx_op_exec_divu_1(struct TargetCore *core);
extern int rx_op_exec_emul_1(struct TargetCore *core);
extern int rx_op_exec_emulu_1(struct TargetCore *core);
extern int rx_op_exec_max_1(struct TargetCore *core);
extern int rx_op_exec_min_1(struct TargetCore *core);
extern int rx_op_exec_stnz_1(struct TargetCore *core);
extern int rx_op_exec_stz_1(struct TargetCore *core);
extern int rx_op_exec_tst_1(struct TargetCore *core);
extern int rx_op_exec_xor_1(struct TargetCore *core);
extern int rx_op_exec_mvtc_1(struct TargetCore *core);
extern int rx_op_exec_mov_10(struct TargetCore *core);
extern int rx_op_exec_mov_12(struct TargetCore *core);
extern int rx_op_exec_movu_3(struct TargetCore *core);
extern int rx_op_exec_add_4(struct TargetCore *core);
extern int rx_op_exec_and_4(struct TargetCore *core);
extern int rx_op_exec_mul_4(struct TargetCore *core);
extern int rx_op_exec_or_4(struct TargetCore *core);
extern int rx_op_exec_sub_3(struct TargetCore *core);
extern int rx_op_exec_bclr_1(struct TargetCore *core);
extern int rx_op_exec_bset_1(struct TargetCore *core);
extern int rx_op_exec_btst_1(struct TargetCore *core);
extern int rx_op_exec_push_2(struct TargetCore *core);
extern int rx_op_exec_mov_6(struct TargetCore *core);
extern int rx_op_exec_mov_8(struct TargetCore *core);
extern int rx_op_exec_mov_7(struct TargetCore *core);
extern int rx_op_exec_mov_9(struct TargetCore *core);
extern int rx_op_exec_mov_11(struct TargetCore *core);
extern int rx_op_exec_mov_13(struct TargetCore *core);
extern int rx_op_exec_fsqrt(struct TargetCore *core);
extern int rx_op_exec_ftou(struct TargetCore *core);
extern int rx_op_exec_utof_1(struct TargetCore *core);
extern int rx_op_exec_utof_1x(struct TargetCore *core);
extern int rx_op_exec_movco(struct TargetCore *core);
extern int rx_op_exec_movli(struct TargetCore *core);
extern int rx_op_exec_emaca(struct TargetCore *core);
extern int rx_op_exec_emsba(struct TargetCore *core);
extern int rx_op_exec_emula(struct TargetCore *core);
extern int rx_op_exec_maclh(struct TargetCore *core);
extern int rx_op_exec_msbhi(struct TargetCore *core);
extern int rx_op_exec_msblh(struct TargetCore *core);
extern int rx_op_exec_msblo(struct TargetCore *core);
extern int rx_op_exec_mullh(struct TargetCore *core);
extern int rx_op_exec_mvfacgu(struct TargetCore *core);
extern int rx_op_exec_mvfaclo(struct TargetCore *core);
extern int rx_op_exec_mvtacgu(struct TargetCore *core);
extern int rx_op_exec_racl(struct TargetCore *core);
extern int rx_op_exec_rdacl(struct TargetCore *core);
extern int rx_op_exec_rdacw(struct TargetCore *core);
extern int rx_op_exec_fadd_3(struct TargetCore *core);
extern int rx_op_exec_fmul_3(struct TargetCore *core);
extern int rx_op_exec_fsub_3(struct TargetCore *core);
extern int rx_op_exec_stnz_2(struct TargetCore *core);
extern int rx_op_exec_stz_2(struct TargetCore *core);

#endif /* !_RX_MC_DECODER_H_ */