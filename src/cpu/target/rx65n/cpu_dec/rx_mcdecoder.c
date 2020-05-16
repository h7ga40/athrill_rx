#include "rx_mcdecoder.h"

#include <stdbool.h>

/* types */

typedef struct {
    rx_uint8 *code;
    RxOpDecodedCodeType *decoded_code;
    RxOperationCodeType *optype;
    rx_uint8 code8x1;
    rx_uint16 code16x1;
    rx_uint24 code24x1;
    rx_uint32 code32x1;
} OpDecodeContext;

/* op constants */
/* brk */
#define OP_FB_MASK_BRK (0x000000ffl) /* fixed bits mask */
#define OP_FB_BRK (0x00000000l) /* fixed bits */
/* rts */
#define OP_FB_MASK_RTS (0x000000ffl) /* fixed bits mask */
#define OP_FB_RTS (0x00000002l) /* fixed bits */
/* nop */
#define OP_FB_MASK_NOP (0x000000ffl) /* fixed bits mask */
#define OP_FB_NOP (0x00000003l) /* fixed bits */
/* bra_a */
#define OP_FB_MASK_BRA_A (0xff000000l) /* fixed bits mask */
#define OP_FB_BRA_A (0x04000000l) /* fixed bits */
    /* 0th subfield of the field 'pcdsp' */
    #define OP_SF_MASK_BRA_A_PCDSP_0 (0x00ffffffl) /* subfield mask */
    #define OP_SF_EBII_BRA_A_PCDSP_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BRA_A_PCDSP_0 (0) /* subfield end bit position in field */
/* bsr_a */
#define OP_FB_MASK_BSR_A (0xff000000l) /* fixed bits mask */
#define OP_FB_BSR_A (0x05000000l) /* fixed bits */
    /* 0th subfield of the field 'pcdsp' */
    #define OP_SF_MASK_BSR_A_PCDSP_0 (0x00ffffffl) /* subfield mask */
    #define OP_SF_EBII_BSR_A_PCDSP_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BSR_A_PCDSP_0 (0) /* subfield end bit position in field */
/* sub_2x */
#define OP_FB_MASK_SUB_2X (0x00ff3c00l) /* fixed bits mask */
#define OP_FB_SUB_2X (0x00060000l) /* fixed bits */
    /* 0th subfield of the field 'mi' */
    #define OP_SF_MASK_SUB_2X_MI_0 (0x0000c000l) /* subfield mask */
    #define OP_SF_EBII_SUB_2X_MI_0 (14) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SUB_2X_MI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_SUB_2X_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_SUB_2X_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SUB_2X_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_SUB_2X_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_SUB_2X_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SUB_2X_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_SUB_2X_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_SUB_2X_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SUB_2X_RD_0 (0) /* subfield end bit position in field */
/* cmp_4x */
#define OP_FB_MASK_CMP_4X (0x00ff3c00l) /* fixed bits mask */
#define OP_FB_CMP_4X (0x00060400l) /* fixed bits */
    /* 0th subfield of the field 'mi' */
    #define OP_SF_MASK_CMP_4X_MI_0 (0x0000c000l) /* subfield mask */
    #define OP_SF_EBII_CMP_4X_MI_0 (14) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_CMP_4X_MI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_CMP_4X_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_CMP_4X_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_CMP_4X_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_CMP_4X_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_CMP_4X_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_CMP_4X_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_CMP_4X_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_CMP_4X_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_CMP_4X_RS2_0 (0) /* subfield end bit position in field */
/* add_2x */
#define OP_FB_MASK_ADD_2X (0x00ff3c00l) /* fixed bits mask */
#define OP_FB_ADD_2X (0x00060800l) /* fixed bits */
    /* 0th subfield of the field 'mi' */
    #define OP_SF_MASK_ADD_2X_MI_0 (0x0000c000l) /* subfield mask */
    #define OP_SF_EBII_ADD_2X_MI_0 (14) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ADD_2X_MI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_ADD_2X_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_ADD_2X_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ADD_2X_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_ADD_2X_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_ADD_2X_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ADD_2X_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_ADD_2X_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_ADD_2X_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ADD_2X_RD_0 (0) /* subfield end bit position in field */
/* mul_3x */
#define OP_FB_MASK_MUL_3X (0x00ff3c00l) /* fixed bits mask */
#define OP_FB_MUL_3X (0x00060c00l) /* fixed bits */
    /* 0th subfield of the field 'mi' */
    #define OP_SF_MASK_MUL_3X_MI_0 (0x0000c000l) /* subfield mask */
    #define OP_SF_EBII_MUL_3X_MI_0 (14) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MUL_3X_MI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_MUL_3X_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_MUL_3X_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MUL_3X_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MUL_3X_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MUL_3X_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MUL_3X_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MUL_3X_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MUL_3X_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MUL_3X_RD_0 (0) /* subfield end bit position in field */
/* and_3x */
#define OP_FB_MASK_AND_3X (0x00ff3c00l) /* fixed bits mask */
#define OP_FB_AND_3X (0x00061000l) /* fixed bits */
    /* 0th subfield of the field 'mi' */
    #define OP_SF_MASK_AND_3X_MI_0 (0x0000c000l) /* subfield mask */
    #define OP_SF_EBII_AND_3X_MI_0 (14) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_AND_3X_MI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_AND_3X_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_AND_3X_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_AND_3X_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_AND_3X_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_AND_3X_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_AND_3X_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_AND_3X_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_AND_3X_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_AND_3X_RD_0 (0) /* subfield end bit position in field */
/* or_3x */
#define OP_FB_MASK_OR_3X (0x00ff3c00l) /* fixed bits mask */
#define OP_FB_OR_3X (0x00061400l) /* fixed bits */
    /* 0th subfield of the field 'mi' */
    #define OP_SF_MASK_OR_3X_MI_0 (0x0000c000l) /* subfield mask */
    #define OP_SF_EBII_OR_3X_MI_0 (14) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_OR_3X_MI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_OR_3X_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_OR_3X_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_OR_3X_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_OR_3X_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_OR_3X_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_OR_3X_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_OR_3X_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_OR_3X_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_OR_3X_RD_0 (0) /* subfield end bit position in field */
/* sbb_2 */
#define OP_FB_MASK_SBB_2 (0x00fffc00l) /* fixed bits mask */
#define OP_FB_SBB_2 (0x0006a000l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_SBB_2_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_SBB_2_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SBB_2_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_SBB_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_SBB_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SBB_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_SBB_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_SBB_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SBB_2_RD_0 (0) /* subfield end bit position in field */
/* adc_3 */
#define OP_FB_MASK_ADC_3 (0xff3cff00l) /* fixed bits mask */
#define OP_FB_ADC_3 (0x06200200l) /* fixed bits */
    /* 0th subfield of the field 'mi' */
    #define OP_SF_MASK_ADC_3_MI_0 (0x00c00000l) /* subfield mask */
    #define OP_SF_EBII_ADC_3_MI_0 (22) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ADC_3_MI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_ADC_3_LD_0 (0x00030000l) /* subfield mask */
    #define OP_SF_EBII_ADC_3_LD_0 (16) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ADC_3_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_ADC_3_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_ADC_3_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ADC_3_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_ADC_3_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_ADC_3_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ADC_3_RD_0 (0) /* subfield end bit position in field */
/* div_2x */
#define OP_FB_MASK_DIV_2X (0xff3cff00l) /* fixed bits mask */
#define OP_FB_DIV_2X (0x06200800l) /* fixed bits */
    /* 0th subfield of the field 'mi' */
    #define OP_SF_MASK_DIV_2X_MI_0 (0x00c00000l) /* subfield mask */
    #define OP_SF_EBII_DIV_2X_MI_0 (22) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_DIV_2X_MI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_DIV_2X_LD_0 (0x00030000l) /* subfield mask */
    #define OP_SF_EBII_DIV_2X_LD_0 (16) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_DIV_2X_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_DIV_2X_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_DIV_2X_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_DIV_2X_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_DIV_2X_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_DIV_2X_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_DIV_2X_RD_0 (0) /* subfield end bit position in field */
/* divu_2x */
#define OP_FB_MASK_DIVU_2X (0xff3cff00l) /* fixed bits mask */
#define OP_FB_DIVU_2X (0x06200900l) /* fixed bits */
    /* 0th subfield of the field 'mi' */
    #define OP_SF_MASK_DIVU_2X_MI_0 (0x00c00000l) /* subfield mask */
    #define OP_SF_EBII_DIVU_2X_MI_0 (22) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_DIVU_2X_MI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_DIVU_2X_LD_0 (0x00030000l) /* subfield mask */
    #define OP_SF_EBII_DIVU_2X_LD_0 (16) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_DIVU_2X_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_DIVU_2X_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_DIVU_2X_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_DIVU_2X_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_DIVU_2X_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_DIVU_2X_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_DIVU_2X_RD_0 (0) /* subfield end bit position in field */
/* emul_2x */
#define OP_FB_MASK_EMUL_2X (0xff3cff00l) /* fixed bits mask */
#define OP_FB_EMUL_2X (0x06200600l) /* fixed bits */
    /* 0th subfield of the field 'mi' */
    #define OP_SF_MASK_EMUL_2X_MI_0 (0x00c00000l) /* subfield mask */
    #define OP_SF_EBII_EMUL_2X_MI_0 (22) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_EMUL_2X_MI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_EMUL_2X_LD_0 (0x00030000l) /* subfield mask */
    #define OP_SF_EBII_EMUL_2X_LD_0 (16) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_EMUL_2X_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_EMUL_2X_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_EMUL_2X_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_EMUL_2X_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_EMUL_2X_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_EMUL_2X_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_EMUL_2X_RD_0 (0) /* subfield end bit position in field */
/* emulu_2x */
#define OP_FB_MASK_EMULU_2X (0xff3cff00l) /* fixed bits mask */
#define OP_FB_EMULU_2X (0x06200700l) /* fixed bits */
    /* 0th subfield of the field 'mi' */
    #define OP_SF_MASK_EMULU_2X_MI_0 (0x00c00000l) /* subfield mask */
    #define OP_SF_EBII_EMULU_2X_MI_0 (22) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_EMULU_2X_MI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_EMULU_2X_LD_0 (0x00030000l) /* subfield mask */
    #define OP_SF_EBII_EMULU_2X_LD_0 (16) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_EMULU_2X_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_EMULU_2X_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_EMULU_2X_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_EMULU_2X_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_EMULU_2X_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_EMULU_2X_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_EMULU_2X_RD_0 (0) /* subfield end bit position in field */
/* itof_1x */
#define OP_FB_MASK_ITOF_1X (0xff3cff00l) /* fixed bits mask */
#define OP_FB_ITOF_1X (0x06201100l) /* fixed bits */
    /* 0th subfield of the field 'mi' */
    #define OP_SF_MASK_ITOF_1X_MI_0 (0x00c00000l) /* subfield mask */
    #define OP_SF_EBII_ITOF_1X_MI_0 (22) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ITOF_1X_MI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_ITOF_1X_LD_0 (0x00030000l) /* subfield mask */
    #define OP_SF_EBII_ITOF_1X_LD_0 (16) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ITOF_1X_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_ITOF_1X_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_ITOF_1X_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ITOF_1X_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_ITOF_1X_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_ITOF_1X_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ITOF_1X_RD_0 (0) /* subfield end bit position in field */
/* max_2x */
#define OP_FB_MASK_MAX_2X (0xff3cff00l) /* fixed bits mask */
#define OP_FB_MAX_2X (0x06200400l) /* fixed bits */
    /* 0th subfield of the field 'mi' */
    #define OP_SF_MASK_MAX_2X_MI_0 (0x00c00000l) /* subfield mask */
    #define OP_SF_EBII_MAX_2X_MI_0 (22) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MAX_2X_MI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_MAX_2X_LD_0 (0x00030000l) /* subfield mask */
    #define OP_SF_EBII_MAX_2X_LD_0 (16) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MAX_2X_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MAX_2X_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MAX_2X_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MAX_2X_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MAX_2X_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MAX_2X_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MAX_2X_RD_0 (0) /* subfield end bit position in field */
/* min_2x */
#define OP_FB_MASK_MIN_2X (0xff3cff00l) /* fixed bits mask */
#define OP_FB_MIN_2X (0x06200500l) /* fixed bits */
    /* 0th subfield of the field 'mi' */
    #define OP_SF_MASK_MIN_2X_MI_0 (0x00c00000l) /* subfield mask */
    #define OP_SF_EBII_MIN_2X_MI_0 (22) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MIN_2X_MI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_MIN_2X_LD_0 (0x00030000l) /* subfield mask */
    #define OP_SF_EBII_MIN_2X_LD_0 (16) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MIN_2X_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MIN_2X_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MIN_2X_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MIN_2X_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MIN_2X_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MIN_2X_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MIN_2X_RD_0 (0) /* subfield end bit position in field */
/* tst_2x */
#define OP_FB_MASK_TST_2X (0xff3cff00l) /* fixed bits mask */
#define OP_FB_TST_2X (0x06200c00l) /* fixed bits */
    /* 0th subfield of the field 'mi' */
    #define OP_SF_MASK_TST_2X_MI_0 (0x00c00000l) /* subfield mask */
    #define OP_SF_EBII_TST_2X_MI_0 (22) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_TST_2X_MI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_TST_2X_LD_0 (0x00030000l) /* subfield mask */
    #define OP_SF_EBII_TST_2X_LD_0 (16) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_TST_2X_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_TST_2X_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_TST_2X_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_TST_2X_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_TST_2X_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_TST_2X_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_TST_2X_RS2_0 (0) /* subfield end bit position in field */
/* xchg_1x */
#define OP_FB_MASK_XCHG_1X (0xff3cff00l) /* fixed bits mask */
#define OP_FB_XCHG_1X (0x06201000l) /* fixed bits */
    /* 0th subfield of the field 'mi' */
    #define OP_SF_MASK_XCHG_1X_MI_0 (0x00c00000l) /* subfield mask */
    #define OP_SF_EBII_XCHG_1X_MI_0 (22) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_XCHG_1X_MI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_XCHG_1X_LD_0 (0x00030000l) /* subfield mask */
    #define OP_SF_EBII_XCHG_1X_LD_0 (16) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_XCHG_1X_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_XCHG_1X_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_XCHG_1X_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_XCHG_1X_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_XCHG_1X_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_XCHG_1X_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_XCHG_1X_RD_0 (0) /* subfield end bit position in field */
/* xor_2x */
#define OP_FB_MASK_XOR_2X (0xff3cff00l) /* fixed bits mask */
#define OP_FB_XOR_2X (0x06200d00l) /* fixed bits */
    /* 0th subfield of the field 'mi' */
    #define OP_SF_MASK_XOR_2X_MI_0 (0x00c00000l) /* subfield mask */
    #define OP_SF_EBII_XOR_2X_MI_0 (22) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_XOR_2X_MI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_XOR_2X_LD_0 (0x00030000l) /* subfield mask */
    #define OP_SF_EBII_XOR_2X_LD_0 (16) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_XOR_2X_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_XOR_2X_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_XOR_2X_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_XOR_2X_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_XOR_2X_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_XOR_2X_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_XOR_2X_RD_0 (0) /* subfield end bit position in field */
/* bra_s */
#define OP_FB_MASK_BRA_S (0x000000f8l) /* fixed bits mask */
#define OP_FB_BRA_S (0x00000008l) /* fixed bits */
    /* 0th subfield of the field 'dsp' */
    #define OP_SF_MASK_BRA_S_DSP_0 (0x00000007l) /* subfield mask */
    #define OP_SF_EBII_BRA_S_DSP_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BRA_S_DSP_0 (0) /* subfield end bit position in field */
/* bcnd_s */
#define OP_FB_MASK_BCND_S (0x000000f0l) /* fixed bits mask */
#define OP_FB_BCND_S (0x00000010l) /* fixed bits */
    /* 0th subfield of the field 'cd' */
    #define OP_SF_MASK_BCND_S_CD_0 (0x00000008l) /* subfield mask */
    #define OP_SF_EBII_BCND_S_CD_0 (3) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BCND_S_CD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'dsp' */
    #define OP_SF_MASK_BCND_S_DSP_0 (0x00000007l) /* subfield mask */
    #define OP_SF_EBII_BCND_S_DSP_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BCND_S_DSP_0 (0) /* subfield end bit position in field */
/* bra_b */
#define OP_FB_MASK_BRA_B (0x0000ff00l) /* fixed bits mask */
#define OP_FB_BRA_B (0x00002e00l) /* fixed bits */
    /* 0th subfield of the field 'pcdsp' */
    #define OP_SF_MASK_BRA_B_PCDSP_0 (0x000000ffl) /* subfield mask */
    #define OP_SF_EBII_BRA_B_PCDSP_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BRA_B_PCDSP_0 (0) /* subfield end bit position in field */
/* bcnd_b */
#define OP_FB_MASK_BCND_B (0x0000f000l) /* fixed bits mask */
#define OP_FB_BCND_B (0x00002000l) /* fixed bits */
    /* 0th subfield of the field 'cd' */
    #define OP_SF_MASK_BCND_B_CD_0 (0x00000f00l) /* subfield mask */
    #define OP_SF_EBII_BCND_B_CD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BCND_B_CD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'pcdsp' */
    #define OP_SF_MASK_BCND_B_PCDSP_0 (0x000000ffl) /* subfield mask */
    #define OP_SF_EBII_BCND_B_PCDSP_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BCND_B_PCDSP_0 (0) /* subfield end bit position in field */
/* bra_w */
#define OP_FB_MASK_BRA_W (0x00ff0000l) /* fixed bits mask */
#define OP_FB_BRA_W (0x00380000l) /* fixed bits */
    /* 0th subfield of the field 'pcdsp' */
    #define OP_SF_MASK_BRA_W_PCDSP_0 (0x0000ffffl) /* subfield mask */
    #define OP_SF_EBII_BRA_W_PCDSP_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BRA_W_PCDSP_0 (0) /* subfield end bit position in field */
/* bsr_w */
#define OP_FB_MASK_BSR_W (0x00ff0000l) /* fixed bits mask */
#define OP_FB_BSR_W (0x00390000l) /* fixed bits */
    /* 0th subfield of the field 'pcdsp' */
    #define OP_SF_MASK_BSR_W_PCDSP_0 (0x0000ffffl) /* subfield mask */
    #define OP_SF_EBII_BSR_W_PCDSP_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BSR_W_PCDSP_0 (0) /* subfield end bit position in field */
/* bcnd_w */
#define OP_FB_MASK_BCND_W (0x00fe0000l) /* fixed bits mask */
#define OP_FB_BCND_W (0x003a0000l) /* fixed bits */
    /* 0th subfield of the field 'cd' */
    #define OP_SF_MASK_BCND_W_CD_0 (0x00010000l) /* subfield mask */
    #define OP_SF_EBII_BCND_W_CD_0 (16) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BCND_W_CD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'pcdsp' */
    #define OP_SF_MASK_BCND_W_PCDSP_0 (0x0000ffffl) /* subfield mask */
    #define OP_SF_EBII_BCND_W_PCDSP_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BCND_W_PCDSP_0 (0) /* subfield end bit position in field */
/* rtsd_2 */
#define OP_FB_MASK_RTSD_2 (0x0000ff00l) /* fixed bits mask */
#define OP_FB_RTSD_2 (0x00003f00l) /* fixed bits */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_RTSD_2_RD_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_RTSD_2_RD_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_RTSD_2_RD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd2' */
    #define OP_SF_MASK_RTSD_2_RD2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_RTSD_2_RD2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_RTSD_2_RD2_0 (0) /* subfield end bit position in field */
/* mov_4 */
#define OP_FB_MASK_MOV_4 (0x0000fc00l) /* fixed bits mask */
#define OP_FB_MOV_4 (0x00003c00l) /* fixed bits */
    /* 0th subfield of the field 'sz' */
    #define OP_SF_MASK_MOV_4_SZ_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_MOV_4_SZ_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_4_SZ_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'dsp' */
    #define OP_SF_MASK_MOV_4_DSP_0 (0x00000080l) /* subfield mask */
    #define OP_SF_EBII_MOV_4_DSP_0 (7) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_4_DSP_0 (4) /* subfield end bit position in field */
    /* 1th subfield of the field 'dsp' */
    #define OP_SF_MASK_MOV_4_DSP_1 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MOV_4_DSP_1 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_4_DSP_1 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MOV_4_RD_0 (0x00000070l) /* subfield mask */
    #define OP_SF_EBII_MOV_4_RD_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_4_RD_0 (0) /* subfield end bit position in field */
/* sub_2 */
#define OP_FB_MASK_SUB_2 (0x0000fc00l) /* fixed bits mask */
#define OP_FB_SUB_2 (0x00004000l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_SUB_2_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_SUB_2_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SUB_2_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_SUB_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_SUB_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SUB_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_SUB_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_SUB_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SUB_2_RD_0 (0) /* subfield end bit position in field */
/* cmp_4 */
#define OP_FB_MASK_CMP_4 (0x0000fc00l) /* fixed bits mask */
#define OP_FB_CMP_4 (0x00004400l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_CMP_4_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_CMP_4_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_CMP_4_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_CMP_4_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_CMP_4_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_CMP_4_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_CMP_4_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_CMP_4_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_CMP_4_RS2_0 (0) /* subfield end bit position in field */
/* add_2 */
#define OP_FB_MASK_ADD_2 (0x0000fc00l) /* fixed bits mask */
#define OP_FB_ADD_2 (0x00004800l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_ADD_2_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_ADD_2_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ADD_2_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_ADD_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_ADD_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ADD_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_ADD_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_ADD_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ADD_2_RD_0 (0) /* subfield end bit position in field */
/* mul_3 */
#define OP_FB_MASK_MUL_3 (0x0000fc00l) /* fixed bits mask */
#define OP_FB_MUL_3 (0x00004c00l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_MUL_3_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_MUL_3_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MUL_3_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MUL_3_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MUL_3_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MUL_3_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MUL_3_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MUL_3_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MUL_3_RD_0 (0) /* subfield end bit position in field */
/* and_3 */
#define OP_FB_MASK_AND_3 (0x0000fc00l) /* fixed bits mask */
#define OP_FB_AND_3 (0x00005000l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_AND_3_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_AND_3_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_AND_3_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_AND_3_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_AND_3_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_AND_3_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_AND_3_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_AND_3_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_AND_3_RD_0 (0) /* subfield end bit position in field */
/* or_3 */
#define OP_FB_MASK_OR_3 (0x0000fc00l) /* fixed bits mask */
#define OP_FB_OR_3 (0x00005400l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_OR_3_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_OR_3_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_OR_3_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_OR_3_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_OR_3_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_OR_3_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_OR_3_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_OR_3_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_OR_3_RD_0 (0) /* subfield end bit position in field */
/* movu_2 */
#define OP_FB_MASK_MOVU_2 (0x0000f800l) /* fixed bits mask */
#define OP_FB_MOVU_2 (0x00005800l) /* fixed bits */
    /* 0th subfield of the field 'sz' */
    #define OP_SF_MASK_MOVU_2_SZ_0 (0x00000400l) /* subfield mask */
    #define OP_SF_EBII_MOVU_2_SZ_0 (10) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOVU_2_SZ_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_MOVU_2_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_MOVU_2_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOVU_2_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MOVU_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MOVU_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOVU_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MOVU_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MOVU_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOVU_2_RD_0 (0) /* subfield end bit position in field */
/* sub_1 */
#define OP_FB_MASK_SUB_1 (0x0000ff00l) /* fixed bits mask */
#define OP_FB_SUB_1 (0x00006000l) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_SUB_1_IMM_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_SUB_1_IMM_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SUB_1_IMM_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_SUB_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_SUB_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SUB_1_RD_0 (0) /* subfield end bit position in field */
/* cmp_1 */
#define OP_FB_MASK_CMP_1 (0x0000ff00l) /* fixed bits mask */
#define OP_FB_CMP_1 (0x00006100l) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_CMP_1_IMM_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_CMP_1_IMM_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_CMP_1_IMM_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_CMP_1_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_CMP_1_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_CMP_1_RS2_0 (0) /* subfield end bit position in field */
/* add_1 */
#define OP_FB_MASK_ADD_1 (0x0000ff00l) /* fixed bits mask */
#define OP_FB_ADD_1 (0x00006200l) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_ADD_1_IMM_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_ADD_1_IMM_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ADD_1_IMM_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_ADD_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_ADD_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ADD_1_RD_0 (0) /* subfield end bit position in field */
/* mul_1 */
#define OP_FB_MASK_MUL_1 (0x0000ff00l) /* fixed bits mask */
#define OP_FB_MUL_1 (0x00006300l) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_MUL_1_IMM_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MUL_1_IMM_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MUL_1_IMM_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MUL_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MUL_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MUL_1_RD_0 (0) /* subfield end bit position in field */
/* and_1 */
#define OP_FB_MASK_AND_1 (0x0000ff00l) /* fixed bits mask */
#define OP_FB_AND_1 (0x00006400l) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_AND_1_IMM_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_AND_1_IMM_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_AND_1_IMM_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_AND_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_AND_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_AND_1_RD_0 (0) /* subfield end bit position in field */
/* or_1 */
#define OP_FB_MASK_OR_1 (0x0000ff00l) /* fixed bits mask */
#define OP_FB_OR_1 (0x00006500l) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_OR_1_IMM_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_OR_1_IMM_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_OR_1_IMM_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_OR_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_OR_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_OR_1_RD_0 (0) /* subfield end bit position in field */
/* mov_3 */
#define OP_FB_MASK_MOV_3 (0x0000ff00l) /* fixed bits mask */
#define OP_FB_MOV_3 (0x00006600l) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_MOV_3_IMM_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MOV_3_IMM_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_3_IMM_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MOV_3_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MOV_3_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_3_RD_0 (0) /* subfield end bit position in field */
/* rtsd_1 */
#define OP_FB_MASK_RTSD_1 (0x0000ff00l) /* fixed bits mask */
#define OP_FB_RTSD_1 (0x00006700l) /* fixed bits */
    /* 0th subfield of the field 'uimm' */
    #define OP_SF_MASK_RTSD_1_UIMM_0 (0x000000ffl) /* subfield mask */
    #define OP_SF_EBII_RTSD_1_UIMM_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_RTSD_1_UIMM_0 (0) /* subfield end bit position in field */
/* shlr_1 */
#define OP_FB_MASK_SHLR_1 (0x0000fe00l) /* fixed bits mask */
#define OP_FB_SHLR_1 (0x00006800l) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_SHLR_1_IMM_0 (0x000001f0l) /* subfield mask */
    #define OP_SF_EBII_SHLR_1_IMM_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SHLR_1_IMM_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_SHLR_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_SHLR_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SHLR_1_RD_0 (0) /* subfield end bit position in field */
/* shar_1 */
#define OP_FB_MASK_SHAR_1 (0x0000fe00l) /* fixed bits mask */
#define OP_FB_SHAR_1 (0x00006a00l) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_SHAR_1_IMM_0 (0x000001f0l) /* subfield mask */
    #define OP_SF_EBII_SHAR_1_IMM_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SHAR_1_IMM_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_SHAR_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_SHAR_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SHAR_1_RD_0 (0) /* subfield end bit position in field */
/* shll_1 */
#define OP_FB_MASK_SHLL_1 (0x0000fe00l) /* fixed bits mask */
#define OP_FB_SHLL_1 (0x00006c00l) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_SHLL_1_IMM_0 (0x000001f0l) /* subfield mask */
    #define OP_SF_EBII_SHLL_1_IMM_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SHLL_1_IMM_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_SHLL_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_SHLL_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SHLL_1_RD_0 (0) /* subfield end bit position in field */
/* pushm */
#define OP_FB_MASK_PUSHM (0x0000ff00l) /* fixed bits mask */
#define OP_FB_PUSHM (0x00006e00l) /* fixed bits */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_PUSHM_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_PUSHM_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_PUSHM_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_PUSHM_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_PUSHM_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_PUSHM_RS2_0 (0) /* subfield end bit position in field */
/* popm */
#define OP_FB_MASK_POPM (0x0000ff00l) /* fixed bits mask */
#define OP_FB_POPM (0x00006f00l) /* fixed bits */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_POPM_RD_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_POPM_RD_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_POPM_RD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd2' */
    #define OP_SF_MASK_POPM_RD2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_POPM_RD2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_POPM_RD2_0 (0) /* subfield end bit position in field */
/* add_3 */
#define OP_FB_MASK_ADD_3 (0x0000fc00l) /* fixed bits mask */
#define OP_FB_ADD_3 (0x00007000l) /* fixed bits */
    /* 0th subfield of the field 'li' */
    #define OP_SF_MASK_ADD_3_LI_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_ADD_3_LI_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ADD_3_LI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_ADD_3_RS2_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_ADD_3_RS2_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ADD_3_RS2_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_ADD_3_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_ADD_3_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ADD_3_RD_0 (0) /* subfield end bit position in field */
/* cmp_2 */
#define OP_FB_MASK_CMP_2 (0x00fff000l) /* fixed bits mask */
#define OP_FB_CMP_2 (0x00755000l) /* fixed bits */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_CMP_2_RS2_0 (0x00000f00l) /* subfield mask */
    #define OP_SF_EBII_CMP_2_RS2_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_CMP_2_RS2_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'uimm' */
    #define OP_SF_MASK_CMP_2_UIMM_0 (0x000000ffl) /* subfield mask */
    #define OP_SF_EBII_CMP_2_UIMM_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_CMP_2_UIMM_0 (0) /* subfield end bit position in field */
/* int */
#define OP_FB_MASK_INT (0x00ffff00l) /* fixed bits mask */
#define OP_FB_INT (0x00756000l) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_INT_IMM_0 (0x000000ffl) /* subfield mask */
    #define OP_SF_EBII_INT_IMM_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_INT_IMM_0 (0) /* subfield end bit position in field */
/* mov_5 */
#define OP_FB_MASK_MOV_5 (0x00fff000l) /* fixed bits mask */
#define OP_FB_MOV_5 (0x00754000l) /* fixed bits */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MOV_5_RD_0 (0x00000f00l) /* subfield mask */
    #define OP_SF_EBII_MOV_5_RD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_5_RD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'uimm' */
    #define OP_SF_MASK_MOV_5_UIMM_0 (0x000000ffl) /* subfield mask */
    #define OP_SF_EBII_MOV_5_UIMM_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_5_UIMM_0 (0) /* subfield end bit position in field */
/* mvtipl */
#define OP_FB_MASK_MVTIPL (0x00fffff0l) /* fixed bits mask */
#define OP_FB_MVTIPL (0x00757000l) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_MVTIPL_IMM_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MVTIPL_IMM_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVTIPL_IMM_0 (0) /* subfield end bit position in field */
/* and_2 */
#define OP_FB_MASK_AND_2 (0x0000fcf0l) /* fixed bits mask */
#define OP_FB_AND_2 (0x00007420l) /* fixed bits */
    /* 0th subfield of the field 'li' */
    #define OP_SF_MASK_AND_2_LI_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_AND_2_LI_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_AND_2_LI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_AND_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_AND_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_AND_2_RD_0 (0) /* subfield end bit position in field */
/* cmp_3 */
#define OP_FB_MASK_CMP_3 (0x0000fcf0l) /* fixed bits mask */
#define OP_FB_CMP_3 (0x00007400l) /* fixed bits */
    /* 0th subfield of the field 'li' */
    #define OP_SF_MASK_CMP_3_LI_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_CMP_3_LI_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_CMP_3_LI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_CMP_3_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_CMP_3_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_CMP_3_RS2_0 (0) /* subfield end bit position in field */
/* mul_2 */
#define OP_FB_MASK_MUL_2 (0x0000fcf0l) /* fixed bits mask */
#define OP_FB_MUL_2 (0x00007410l) /* fixed bits */
    /* 0th subfield of the field 'li' */
    #define OP_SF_MASK_MUL_2_LI_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_MUL_2_LI_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MUL_2_LI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MUL_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MUL_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MUL_2_RD_0 (0) /* subfield end bit position in field */
/* or_2 */
#define OP_FB_MASK_OR_2 (0x0000fcf0l) /* fixed bits mask */
#define OP_FB_OR_2 (0x00007430l) /* fixed bits */
    /* 0th subfield of the field 'li' */
    #define OP_SF_MASK_OR_2_LI_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_OR_2_LI_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_OR_2_LI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_OR_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_OR_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_OR_2_RD_0 (0) /* subfield end bit position in field */
/* bset_3 */
#define OP_FB_MASK_BSET_3 (0x0000fe00l) /* fixed bits mask */
#define OP_FB_BSET_3 (0x00007800l) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_BSET_3_IMM_0 (0x000001f0l) /* subfield mask */
    #define OP_SF_EBII_BSET_3_IMM_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BSET_3_IMM_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_BSET_3_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_BSET_3_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BSET_3_RD_0 (0) /* subfield end bit position in field */
/* bclr_3 */
#define OP_FB_MASK_BCLR_3 (0x0000fe00l) /* fixed bits mask */
#define OP_FB_BCLR_3 (0x00007a00l) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_BCLR_3_IMM_0 (0x000001f0l) /* subfield mask */
    #define OP_SF_EBII_BCLR_3_IMM_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BCLR_3_IMM_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_BCLR_3_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_BCLR_3_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BCLR_3_RD_0 (0) /* subfield end bit position in field */
/* btst_3 */
#define OP_FB_MASK_BTST_3 (0x0000fe00l) /* fixed bits mask */
#define OP_FB_BTST_3 (0x00007c00l) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_BTST_3_IMM_0 (0x000001f0l) /* subfield mask */
    #define OP_SF_EBII_BTST_3_IMM_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BTST_3_IMM_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_BTST_3_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_BTST_3_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BTST_3_RS2_0 (0) /* subfield end bit position in field */
/* abs_1 */
#define OP_FB_MASK_ABS_1 (0x0000fff0l) /* fixed bits mask */
#define OP_FB_ABS_1 (0x00007e20l) /* fixed bits */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_ABS_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_ABS_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ABS_1_RD_0 (0) /* subfield end bit position in field */
/* neg_1 */
#define OP_FB_MASK_NEG_1 (0x0000fff0l) /* fixed bits mask */
#define OP_FB_NEG_1 (0x00007e10l) /* fixed bits */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_NEG_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_NEG_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_NEG_1_RD_0 (0) /* subfield end bit position in field */
/* not_1 */
#define OP_FB_MASK_NOT_1 (0x0000fff0l) /* fixed bits mask */
#define OP_FB_NOT_1 (0x00007e00l) /* fixed bits */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_NOT_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_NOT_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_NOT_1_RD_0 (0) /* subfield end bit position in field */
/* rolc */
#define OP_FB_MASK_ROLC (0x0000fff0l) /* fixed bits mask */
#define OP_FB_ROLC (0x00007e50l) /* fixed bits */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_ROLC_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_ROLC_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ROLC_RD_0 (0) /* subfield end bit position in field */
/* pop */
#define OP_FB_MASK_POP (0x0000fff0l) /* fixed bits mask */
#define OP_FB_POP (0x00007eb0l) /* fixed bits */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_POP_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_POP_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_POP_RD_0 (0) /* subfield end bit position in field */
/* popc */
#define OP_FB_MASK_POPC (0x0000fff0l) /* fixed bits mask */
#define OP_FB_POPC (0x00007ee0l) /* fixed bits */
    /* 0th subfield of the field 'cr' */
    #define OP_SF_MASK_POPC_CR_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_POPC_CR_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_POPC_CR_0 (0) /* subfield end bit position in field */
/* rorc */
#define OP_FB_MASK_RORC (0x0000fff0l) /* fixed bits mask */
#define OP_FB_RORC (0x00007e40l) /* fixed bits */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_RORC_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_RORC_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_RORC_RD_0 (0) /* subfield end bit position in field */
/* push_1 */
#define OP_FB_MASK_PUSH_1 (0x0000ffc0l) /* fixed bits mask */
#define OP_FB_PUSH_1 (0x00007e80l) /* fixed bits */
    /* 0th subfield of the field 'sz' */
    #define OP_SF_MASK_PUSH_1_SZ_0 (0x00000030l) /* subfield mask */
    #define OP_SF_EBII_PUSH_1_SZ_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_PUSH_1_SZ_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_PUSH_1_RS_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_PUSH_1_RS_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_PUSH_1_RS_0 (0) /* subfield end bit position in field */
/* pushc */
#define OP_FB_MASK_PUSHC (0x0000fff0l) /* fixed bits mask */
#define OP_FB_PUSHC (0x00007ec0l) /* fixed bits */
    /* 0th subfield of the field 'cr' */
    #define OP_SF_MASK_PUSHC_CR_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_PUSHC_CR_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_PUSHC_CR_0 (0) /* subfield end bit position in field */
/* sat */
#define OP_FB_MASK_SAT (0x0000fff0l) /* fixed bits mask */
#define OP_FB_SAT (0x00007e30l) /* fixed bits */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_SAT_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_SAT_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SAT_RD_0 (0) /* subfield end bit position in field */
/* jmp */
#define OP_FB_MASK_JMP (0x0000fff0l) /* fixed bits mask */
#define OP_FB_JMP (0x00007f00l) /* fixed bits */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_JMP_RS_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_JMP_RS_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_JMP_RS_0 (0) /* subfield end bit position in field */
/* jsr */
#define OP_FB_MASK_JSR (0x0000fff0l) /* fixed bits mask */
#define OP_FB_JSR (0x00007f10l) /* fixed bits */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_JSR_RS_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_JSR_RS_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_JSR_RS_0 (0) /* subfield end bit position in field */
/* bra_l */
#define OP_FB_MASK_BRA_L (0x0000fff0l) /* fixed bits mask */
#define OP_FB_BRA_L (0x00007f40l) /* fixed bits */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_BRA_L_RS_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_BRA_L_RS_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BRA_L_RS_0 (0) /* subfield end bit position in field */
/* bsr_l */
#define OP_FB_MASK_BSR_L (0x0000fff0l) /* fixed bits mask */
#define OP_FB_BSR_L (0x00007f50l) /* fixed bits */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_BSR_L_RS_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_BSR_L_RS_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BSR_L_RS_0 (0) /* subfield end bit position in field */
/* scmpu */
#define OP_FB_MASK_SCMPU (0x0000ffffl) /* fixed bits mask */
#define OP_FB_SCMPU (0x00007f83l) /* fixed bits */
/* suntil_b */
#define OP_FB_MASK_SUNTIL_B (0x0000ffffl) /* fixed bits mask */
#define OP_FB_SUNTIL_B (0x00007f80l) /* fixed bits */
/* suntil_w */
#define OP_FB_MASK_SUNTIL_W (0x0000ffffl) /* fixed bits mask */
#define OP_FB_SUNTIL_W (0x00007f81l) /* fixed bits */
/* suntil_l */
#define OP_FB_MASK_SUNTIL_L (0x0000ffffl) /* fixed bits mask */
#define OP_FB_SUNTIL_L (0x00007f82l) /* fixed bits */
/* smovu */
#define OP_FB_MASK_SMOVU (0x0000ffffl) /* fixed bits mask */
#define OP_FB_SMOVU (0x00007f87l) /* fixed bits */
/* swhile_b */
#define OP_FB_MASK_SWHILE_B (0x0000ffffl) /* fixed bits mask */
#define OP_FB_SWHILE_B (0x00007f84l) /* fixed bits */
/* swhile_w */
#define OP_FB_MASK_SWHILE_W (0x0000ffffl) /* fixed bits mask */
#define OP_FB_SWHILE_W (0x00007f85l) /* fixed bits */
/* swhile_l */
#define OP_FB_MASK_SWHILE_L (0x0000ffffl) /* fixed bits mask */
#define OP_FB_SWHILE_L (0x00007f86l) /* fixed bits */
/* smovb */
#define OP_FB_MASK_SMOVB (0x0000ffffl) /* fixed bits mask */
#define OP_FB_SMOVB (0x00007f8bl) /* fixed bits */
/* sstr_b */
#define OP_FB_MASK_SSTR_B (0x0000ffffl) /* fixed bits mask */
#define OP_FB_SSTR_B (0x00007f88l) /* fixed bits */
/* sstr_w */
#define OP_FB_MASK_SSTR_W (0x0000ffffl) /* fixed bits mask */
#define OP_FB_SSTR_W (0x00007f89l) /* fixed bits */
/* sstr_l */
#define OP_FB_MASK_SSTR_L (0x0000ffffl) /* fixed bits mask */
#define OP_FB_SSTR_L (0x00007f8al) /* fixed bits */
/* smovf */
#define OP_FB_MASK_SMOVF (0x0000ffffl) /* fixed bits mask */
#define OP_FB_SMOVF (0x00007f8fl) /* fixed bits */
/* rmpa */
#define OP_FB_MASK_RMPA (0x0000fffcl) /* fixed bits mask */
#define OP_FB_RMPA (0x00007f8cl) /* fixed bits */
    /* 0th subfield of the field 'sz' */
    #define OP_SF_MASK_RMPA_SZ_0 (0x00000003l) /* subfield mask */
    #define OP_SF_EBII_RMPA_SZ_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_RMPA_SZ_0 (0) /* subfield end bit position in field */
/* satr */
#define OP_FB_MASK_SATR (0x0000ffffl) /* fixed bits mask */
#define OP_FB_SATR (0x00007f93l) /* fixed bits */
/* rtfi */
#define OP_FB_MASK_RTFI (0x0000ffffl) /* fixed bits mask */
#define OP_FB_RTFI (0x00007f94l) /* fixed bits */
/* rte */
#define OP_FB_MASK_RTE (0x0000ffffl) /* fixed bits mask */
#define OP_FB_RTE (0x00007f95l) /* fixed bits */
/* wait */
#define OP_FB_MASK_WAIT (0x0000ffffl) /* fixed bits mask */
#define OP_FB_WAIT (0x00007f96l) /* fixed bits */
/* setpsw */
#define OP_FB_MASK_SETPSW (0x0000fff0l) /* fixed bits mask */
#define OP_FB_SETPSW (0x00007fa0l) /* fixed bits */
    /* 0th subfield of the field 'cb' */
    #define OP_SF_MASK_SETPSW_CB_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_SETPSW_CB_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SETPSW_CB_0 (0) /* subfield end bit position in field */
/* clrpsw */
#define OP_FB_MASK_CLRPSW (0x0000fff0l) /* fixed bits mask */
#define OP_FB_CLRPSW (0x00007fb0l) /* fixed bits */
    /* 0th subfield of the field 'cb' */
    #define OP_SF_MASK_CLRPSW_CB_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_CLRPSW_CB_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_CLRPSW_CB_0 (0) /* subfield end bit position in field */
/* movu_1 */
#define OP_FB_MASK_MOVU_1 (0x0000f000l) /* fixed bits mask */
#define OP_FB_MOVU_1 (0x0000b000l) /* fixed bits */
    /* 0th subfield of the field 'sz' */
    #define OP_SF_MASK_MOVU_1_SZ_0 (0x00000800l) /* subfield mask */
    #define OP_SF_EBII_MOVU_1_SZ_0 (11) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOVU_1_SZ_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'dsp' */
    #define OP_SF_MASK_MOVU_1_DSP_0 (0x00000780l) /* subfield mask */
    #define OP_SF_EBII_MOVU_1_DSP_0 (7) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOVU_1_DSP_0 (1) /* subfield end bit position in field */
    /* 1th subfield of the field 'dsp' */
    #define OP_SF_MASK_MOVU_1_DSP_1 (0x00000008l) /* subfield mask */
    #define OP_SF_EBII_MOVU_1_DSP_1 (3) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOVU_1_DSP_1 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MOVU_1_RS_0 (0x00000070l) /* subfield mask */
    #define OP_SF_EBII_MOVU_1_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOVU_1_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MOVU_1_RD_0 (0x00000007l) /* subfield mask */
    #define OP_SF_EBII_MOVU_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOVU_1_RD_0 (0) /* subfield end bit position in field */
/* mov_1 */
#define OP_FB_MASK_MOV_1 (0x0000c800l) /* fixed bits mask */
#define OP_FB_MOV_1 (0x00008000l) /* fixed bits */
    /* 0th subfield of the field 'sz' */
    #define OP_SF_MASK_MOV_1_SZ_0 (0x00003000l) /* subfield mask */
    #define OP_SF_EBII_MOV_1_SZ_0 (12) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_1_SZ_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'dsp' */
    #define OP_SF_MASK_MOV_1_DSP_0 (0x00000780l) /* subfield mask */
    #define OP_SF_EBII_MOV_1_DSP_0 (7) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_1_DSP_0 (1) /* subfield end bit position in field */
    /* 1th subfield of the field 'dsp' */
    #define OP_SF_MASK_MOV_1_DSP_1 (0x00000008l) /* subfield mask */
    #define OP_SF_EBII_MOV_1_DSP_1 (3) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_1_DSP_1 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MOV_1_RD_0 (0x00000070l) /* subfield mask */
    #define OP_SF_EBII_MOV_1_RD_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_1_RD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MOV_1_RS_0 (0x00000007l) /* subfield mask */
    #define OP_SF_EBII_MOV_1_RS_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_1_RS_0 (0) /* subfield end bit position in field */
/* mov_2 */
#define OP_FB_MASK_MOV_2 (0x0000c800l) /* fixed bits mask */
#define OP_FB_MOV_2 (0x00008800l) /* fixed bits */
    /* 0th subfield of the field 'sz' */
    #define OP_SF_MASK_MOV_2_SZ_0 (0x00003000l) /* subfield mask */
    #define OP_SF_EBII_MOV_2_SZ_0 (12) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_2_SZ_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'dsp' */
    #define OP_SF_MASK_MOV_2_DSP_0 (0x00000780l) /* subfield mask */
    #define OP_SF_EBII_MOV_2_DSP_0 (7) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_2_DSP_0 (1) /* subfield end bit position in field */
    /* 1th subfield of the field 'dsp' */
    #define OP_SF_MASK_MOV_2_DSP_1 (0x00000008l) /* subfield mask */
    #define OP_SF_EBII_MOV_2_DSP_1 (3) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_2_DSP_1 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MOV_2_RS_0 (0x00000070l) /* subfield mask */
    #define OP_SF_EBII_MOV_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MOV_2_RD_0 (0x00000007l) /* subfield mask */
    #define OP_SF_EBII_MOV_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_2_RD_0 (0) /* subfield end bit position in field */
/* sbb_1 */
#define OP_FB_MASK_SBB_1 (0x00fffc00l) /* fixed bits mask */
#define OP_FB_SBB_1 (0x00fc0000l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_SBB_1_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_SBB_1_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SBB_1_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_SBB_1_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_SBB_1_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SBB_1_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_SBB_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_SBB_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SBB_1_RD_0 (0) /* subfield end bit position in field */
/* neg_2 */
#define OP_FB_MASK_NEG_2 (0x00ffff00l) /* fixed bits mask */
#define OP_FB_NEG_2 (0x00fc0700l) /* fixed bits */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_NEG_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_NEG_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_NEG_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_NEG_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_NEG_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_NEG_2_RD_0 (0) /* subfield end bit position in field */
/* adc_2 */
#define OP_FB_MASK_ADC_2 (0x00fffc00l) /* fixed bits mask */
#define OP_FB_ADC_2 (0x00fc0800l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_ADC_2_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_ADC_2_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ADC_2_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_ADC_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_ADC_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ADC_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_ADC_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_ADC_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ADC_2_RD_0 (0) /* subfield end bit position in field */
/* abs_2 */
#define OP_FB_MASK_ABS_2 (0x00ffff00l) /* fixed bits mask */
#define OP_FB_ABS_2 (0x00fc0f00l) /* fixed bits */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_ABS_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_ABS_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ABS_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_ABS_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_ABS_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ABS_2_RD_0 (0) /* subfield end bit position in field */
/* not_2 */
#define OP_FB_MASK_NOT_2 (0x00ffff00l) /* fixed bits mask */
#define OP_FB_NOT_2 (0x00fc3b00l) /* fixed bits */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_NOT_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_NOT_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_NOT_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_NOT_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_NOT_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_NOT_2_RD_0 (0) /* subfield end bit position in field */
/* bset_4 */
#define OP_FB_MASK_BSET_4 (0x00fffc00l) /* fixed bits mask */
#define OP_FB_BSET_4 (0x00fc6000l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_BSET_4_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_BSET_4_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BSET_4_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_BSET_4_RD_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_BSET_4_RD_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BSET_4_RD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_BSET_4_RS_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_BSET_4_RS_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BSET_4_RS_0 (0) /* subfield end bit position in field */
/* bclr_4 */
#define OP_FB_MASK_BCLR_4 (0x00fffc00l) /* fixed bits mask */
#define OP_FB_BCLR_4 (0x00fc6400l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_BCLR_4_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_BCLR_4_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BCLR_4_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_BCLR_4_RD_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_BCLR_4_RD_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BCLR_4_RD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_BCLR_4_RS_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_BCLR_4_RS_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BCLR_4_RS_0 (0) /* subfield end bit position in field */
/* btst_4 */
#define OP_FB_MASK_BTST_4 (0x00fffc00l) /* fixed bits mask */
#define OP_FB_BTST_4 (0x00fc6800l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_BTST_4_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_BTST_4_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BTST_4_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_BTST_4_RS2_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_BTST_4_RS2_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BTST_4_RS2_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_BTST_4_RS_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_BTST_4_RS_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BTST_4_RS_0 (0) /* subfield end bit position in field */
/* bnot_4 */
#define OP_FB_MASK_BNOT_4 (0x00fffc00l) /* fixed bits mask */
#define OP_FB_BNOT_4 (0x00fc6c00l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_BNOT_4_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_BNOT_4_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BNOT_4_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_BNOT_4_RD_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_BNOT_4_RD_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BNOT_4_RD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_BNOT_4_RS_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_BNOT_4_RS_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BNOT_4_RS_0 (0) /* subfield end bit position in field */
/* max_2 */
#define OP_FB_MASK_MAX_2 (0x00fffc00l) /* fixed bits mask */
#define OP_FB_MAX_2 (0x00fc1000l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_MAX_2_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_MAX_2_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MAX_2_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MAX_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MAX_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MAX_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MAX_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MAX_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MAX_2_RD_0 (0) /* subfield end bit position in field */
/* min_2 */
#define OP_FB_MASK_MIN_2 (0x00fffc00l) /* fixed bits mask */
#define OP_FB_MIN_2 (0x00fc1400l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_MIN_2_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_MIN_2_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MIN_2_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MIN_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MIN_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MIN_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MIN_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MIN_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MIN_2_RD_0 (0) /* subfield end bit position in field */
/* emul_2 */
#define OP_FB_MASK_EMUL_2 (0x00fffc00l) /* fixed bits mask */
#define OP_FB_EMUL_2 (0x00fc1800l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_EMUL_2_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_EMUL_2_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_EMUL_2_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_EMUL_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_EMUL_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_EMUL_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_EMUL_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_EMUL_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_EMUL_2_RD_0 (0) /* subfield end bit position in field */
/* emulu_2 */
#define OP_FB_MASK_EMULU_2 (0x00fffc00l) /* fixed bits mask */
#define OP_FB_EMULU_2 (0x00fc1c00l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_EMULU_2_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_EMULU_2_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_EMULU_2_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_EMULU_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_EMULU_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_EMULU_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_EMULU_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_EMULU_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_EMULU_2_RD_0 (0) /* subfield end bit position in field */
/* div_2 */
#define OP_FB_MASK_DIV_2 (0x00fffc00l) /* fixed bits mask */
#define OP_FB_DIV_2 (0x00fc2000l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_DIV_2_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_DIV_2_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_DIV_2_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_DIV_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_DIV_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_DIV_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_DIV_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_DIV_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_DIV_2_RD_0 (0) /* subfield end bit position in field */
/* divu_2 */
#define OP_FB_MASK_DIVU_2 (0x00fffc00l) /* fixed bits mask */
#define OP_FB_DIVU_2 (0x00fc2400l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_DIVU_2_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_DIVU_2_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_DIVU_2_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_DIVU_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_DIVU_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_DIVU_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_DIVU_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_DIVU_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_DIVU_2_RD_0 (0) /* subfield end bit position in field */
/* tst_2 */
#define OP_FB_MASK_TST_2 (0x00fffc00l) /* fixed bits mask */
#define OP_FB_TST_2 (0x00fc3000l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_TST_2_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_TST_2_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_TST_2_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_TST_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_TST_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_TST_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_TST_2_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_TST_2_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_TST_2_RS2_0 (0) /* subfield end bit position in field */
/* xor_2 */
#define OP_FB_MASK_XOR_2 (0x00fffc00l) /* fixed bits mask */
#define OP_FB_XOR_2 (0x00fc3400l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_XOR_2_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_XOR_2_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_XOR_2_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_XOR_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_XOR_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_XOR_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_XOR_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_XOR_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_XOR_2_RD_0 (0) /* subfield end bit position in field */
/* xchg_1 */
#define OP_FB_MASK_XCHG_1 (0x00fffc00l) /* fixed bits mask */
#define OP_FB_XCHG_1 (0x00fc4000l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_XCHG_1_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_XCHG_1_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_XCHG_1_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_XCHG_1_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_XCHG_1_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_XCHG_1_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_XCHG_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_XCHG_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_XCHG_1_RD_0 (0) /* subfield end bit position in field */
/* itof_1 */
#define OP_FB_MASK_ITOF_1 (0x00fffc00l) /* fixed bits mask */
#define OP_FB_ITOF_1 (0x00fc4400l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_ITOF_1_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_ITOF_1_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ITOF_1_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_ITOF_1_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_ITOF_1_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ITOF_1_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_ITOF_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_ITOF_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ITOF_1_RD_0 (0) /* subfield end bit position in field */
/* bset_2 */
#define OP_FB_MASK_BSET_2 (0x00fffc00l) /* fixed bits mask */
#define OP_FB_BSET_2 (0x00fc6000l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_BSET_2_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_BSET_2_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BSET_2_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_BSET_2_RD_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_BSET_2_RD_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BSET_2_RD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_BSET_2_RS_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_BSET_2_RS_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BSET_2_RS_0 (0) /* subfield end bit position in field */
/* bclr_2 */
#define OP_FB_MASK_BCLR_2 (0x00fffc00l) /* fixed bits mask */
#define OP_FB_BCLR_2 (0x00fc6400l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_BCLR_2_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_BCLR_2_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BCLR_2_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_BCLR_2_RD_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_BCLR_2_RD_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BCLR_2_RD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_BCLR_2_RS_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_BCLR_2_RS_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BCLR_2_RS_0 (0) /* subfield end bit position in field */
/* btst_2 */
#define OP_FB_MASK_BTST_2 (0x00fffc00l) /* fixed bits mask */
#define OP_FB_BTST_2 (0x00fc6800l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_BTST_2_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_BTST_2_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BTST_2_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_BTST_2_RS2_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_BTST_2_RS2_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BTST_2_RS2_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_BTST_2_RS_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_BTST_2_RS_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BTST_2_RS_0 (0) /* subfield end bit position in field */
/* bnot_2 */
#define OP_FB_MASK_BNOT_2 (0x00fffc00l) /* fixed bits mask */
#define OP_FB_BNOT_2 (0x00fc6c00l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_BNOT_2_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_BNOT_2_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BNOT_2_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_BNOT_2_RD_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_BNOT_2_RD_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BNOT_2_RD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_BNOT_2_RS_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_BNOT_2_RS_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BNOT_2_RS_0 (0) /* subfield end bit position in field */
/* fsub_2 */
#define OP_FB_MASK_FSUB_2 (0x00fffc00l) /* fixed bits mask */
#define OP_FB_FSUB_2 (0x00fc8000l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_FSUB_2_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_FSUB_2_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FSUB_2_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_FSUB_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_FSUB_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FSUB_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_FSUB_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_FSUB_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FSUB_2_RD_0 (0) /* subfield end bit position in field */
/* fcmp_2 */
#define OP_FB_MASK_FCMP_2 (0x00fffc00l) /* fixed bits mask */
#define OP_FB_FCMP_2 (0x00fc8400l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_FCMP_2_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_FCMP_2_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FCMP_2_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_FCMP_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_FCMP_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FCMP_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_FCMP_2_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_FCMP_2_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FCMP_2_RS2_0 (0) /* subfield end bit position in field */
/* fadd_2 */
#define OP_FB_MASK_FADD_2 (0x00fffc00l) /* fixed bits mask */
#define OP_FB_FADD_2 (0x00fc8800l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_FADD_2_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_FADD_2_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FADD_2_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_FADD_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_FADD_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FADD_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_FADD_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_FADD_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FADD_2_RD_0 (0) /* subfield end bit position in field */
/* fmul_2 */
#define OP_FB_MASK_FMUL_2 (0x00fffc00l) /* fixed bits mask */
#define OP_FB_FMUL_2 (0x00fc8c00l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_FMUL_2_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_FMUL_2_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FMUL_2_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_FMUL_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_FMUL_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FMUL_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_FMUL_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_FMUL_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FMUL_2_RD_0 (0) /* subfield end bit position in field */
/* fdiv_2 */
#define OP_FB_MASK_FDIV_2 (0x00fffc00l) /* fixed bits mask */
#define OP_FB_FDIV_2 (0x00fc9000l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_FDIV_2_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_FDIV_2_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FDIV_2_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_FDIV_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_FDIV_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FDIV_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_FDIV_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_FDIV_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FDIV_2_RD_0 (0) /* subfield end bit position in field */
/* ftoi */
#define OP_FB_MASK_FTOI (0x00fffc00l) /* fixed bits mask */
#define OP_FB_FTOI (0x00fc9400l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_FTOI_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_FTOI_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FTOI_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_FTOI_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_FTOI_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FTOI_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_FTOI_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_FTOI_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FTOI_RD_0 (0) /* subfield end bit position in field */
/* round */
#define OP_FB_MASK_ROUND (0x00fffc00l) /* fixed bits mask */
#define OP_FB_ROUND (0x00fc9800l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_ROUND_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_ROUND_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ROUND_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_ROUND_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_ROUND_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ROUND_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_ROUND_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_ROUND_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ROUND_RD_0 (0) /* subfield end bit position in field */
/* sccnd */
#define OP_FB_MASK_SCCND (0x00fff000l) /* fixed bits mask */
#define OP_FB_SCCND (0x00fcd000l) /* fixed bits */
    /* 0th subfield of the field 'sz' */
    #define OP_SF_MASK_SCCND_SZ_0 (0x00000c00l) /* subfield mask */
    #define OP_SF_EBII_SCCND_SZ_0 (10) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SCCND_SZ_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'id' */
    #define OP_SF_MASK_SCCND_ID_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_SCCND_ID_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SCCND_ID_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_SCCND_RD_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_SCCND_RD_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SCCND_RD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'cd' */
    #define OP_SF_MASK_SCCND_CD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_SCCND_CD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SCCND_CD_0 (0) /* subfield end bit position in field */
/* bmcnd_1 */
#define OP_FB_MASK_BMCND_1 (0x00ffe000l) /* fixed bits mask */
#define OP_FB_BMCND_1 (0x00fce000l) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_BMCND_1_IMM_0 (0x00001c00l) /* subfield mask */
    #define OP_SF_EBII_BMCND_1_IMM_0 (10) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BMCND_1_IMM_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_BMCND_1_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_BMCND_1_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BMCND_1_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_BMCND_1_RD_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_BMCND_1_RD_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BMCND_1_RD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'cd' */
    #define OP_SF_MASK_BMCND_1_CD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_BMCND_1_CD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BMCND_1_CD_0 (0) /* subfield end bit position in field */
/* bnot_1 */
#define OP_FB_MASK_BNOT_1 (0x00ffe00fl) /* fixed bits mask */
#define OP_FB_BNOT_1 (0x00fce00fl) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_BNOT_1_IMM_0 (0x00001c00l) /* subfield mask */
    #define OP_SF_EBII_BNOT_1_IMM_0 (10) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BNOT_1_IMM_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'id' */
    #define OP_SF_MASK_BNOT_1_ID_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_BNOT_1_ID_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BNOT_1_ID_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_BNOT_1_RD_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_BNOT_1_RD_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BNOT_1_RD_0 (0) /* subfield end bit position in field */
/* shlr_3 */
#define OP_FB_MASK_SHLR_3 (0x00ffe000l) /* fixed bits mask */
#define OP_FB_SHLR_3 (0x00fd8000l) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_SHLR_3_IMM_0 (0x00001f00l) /* subfield mask */
    #define OP_SF_EBII_SHLR_3_IMM_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SHLR_3_IMM_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_SHLR_3_RS2_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_SHLR_3_RS2_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SHLR_3_RS2_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_SHLR_3_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_SHLR_3_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SHLR_3_RD_0 (0) /* subfield end bit position in field */
/* shar_3 */
#define OP_FB_MASK_SHAR_3 (0x00ffe000l) /* fixed bits mask */
#define OP_FB_SHAR_3 (0x00fda000l) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_SHAR_3_IMM_0 (0x00001f00l) /* subfield mask */
    #define OP_SF_EBII_SHAR_3_IMM_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SHAR_3_IMM_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_SHAR_3_RS2_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_SHAR_3_RS2_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SHAR_3_RS2_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_SHAR_3_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_SHAR_3_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SHAR_3_RD_0 (0) /* subfield end bit position in field */
/* shll_3 */
#define OP_FB_MASK_SHLL_3 (0x00ffe000l) /* fixed bits mask */
#define OP_FB_SHLL_3 (0x00fdc000l) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_SHLL_3_IMM_0 (0x00001f00l) /* subfield mask */
    #define OP_SF_EBII_SHLL_3_IMM_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SHLL_3_IMM_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_SHLL_3_RS2_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_SHLL_3_RS2_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SHLL_3_RS2_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_SHLL_3_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_SHLL_3_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SHLL_3_RD_0 (0) /* subfield end bit position in field */
/* bmcnd_2 */
#define OP_FB_MASK_BMCND_2 (0x00ffe000l) /* fixed bits mask */
#define OP_FB_BMCND_2 (0x00fde000l) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_BMCND_2_IMM_0 (0x00001f00l) /* subfield mask */
    #define OP_SF_EBII_BMCND_2_IMM_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BMCND_2_IMM_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'cd' */
    #define OP_SF_MASK_BMCND_2_CD_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_BMCND_2_CD_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BMCND_2_CD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_BMCND_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_BMCND_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BMCND_2_RD_0 (0) /* subfield end bit position in field */
/* bnot_3 */
#define OP_FB_MASK_BNOT_3 (0x00ffe0f0l) /* fixed bits mask */
#define OP_FB_BNOT_3 (0x00fde0f0l) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_BNOT_3_IMM_0 (0x00001f00l) /* subfield mask */
    #define OP_SF_EBII_BNOT_3_IMM_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BNOT_3_IMM_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_BNOT_3_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_BNOT_3_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BNOT_3_RD_0 (0) /* subfield end bit position in field */
/* mulhi */
#define OP_FB_MASK_MULHI (0x00fff700l) /* fixed bits mask */
#define OP_FB_MULHI (0x00fd0000l) /* fixed bits */
    /* 0th subfield of the field 'a' */
    #define OP_SF_MASK_MULHI_A_0 (0x00000800l) /* subfield mask */
    #define OP_SF_EBII_MULHI_A_0 (11) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MULHI_A_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MULHI_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MULHI_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MULHI_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_MULHI_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MULHI_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MULHI_RS2_0 (0) /* subfield end bit position in field */
/* mullo */
#define OP_FB_MASK_MULLO (0x00fff700l) /* fixed bits mask */
#define OP_FB_MULLO (0x00fd0100l) /* fixed bits */
    /* 0th subfield of the field 'a' */
    #define OP_SF_MASK_MULLO_A_0 (0x00000800l) /* subfield mask */
    #define OP_SF_EBII_MULLO_A_0 (11) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MULLO_A_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MULLO_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MULLO_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MULLO_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_MULLO_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MULLO_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MULLO_RS2_0 (0) /* subfield end bit position in field */
/* machi */
#define OP_FB_MASK_MACHI (0x00fff700l) /* fixed bits mask */
#define OP_FB_MACHI (0x00fd0400l) /* fixed bits */
    /* 0th subfield of the field 'a' */
    #define OP_SF_MASK_MACHI_A_0 (0x00000800l) /* subfield mask */
    #define OP_SF_EBII_MACHI_A_0 (11) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MACHI_A_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MACHI_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MACHI_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MACHI_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_MACHI_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MACHI_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MACHI_RS2_0 (0) /* subfield end bit position in field */
/* maclo */
#define OP_FB_MASK_MACLO (0x00fff700l) /* fixed bits mask */
#define OP_FB_MACLO (0x00fd0500l) /* fixed bits */
    /* 0th subfield of the field 'a' */
    #define OP_SF_MASK_MACLO_A_0 (0x00000800l) /* subfield mask */
    #define OP_SF_EBII_MACLO_A_0 (11) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MACLO_A_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MACLO_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MACLO_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MACLO_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_MACLO_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MACLO_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MACLO_RS2_0 (0) /* subfield end bit position in field */
/* mvtachi */
#define OP_FB_MASK_MVTACHI (0x00ffff70l) /* fixed bits mask */
#define OP_FB_MVTACHI (0x00fd1700l) /* fixed bits */
    /* 0th subfield of the field 'a' */
    #define OP_SF_MASK_MVTACHI_A_0 (0x00000080l) /* subfield mask */
    #define OP_SF_EBII_MVTACHI_A_0 (7) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVTACHI_A_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MVTACHI_RS_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MVTACHI_RS_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVTACHI_RS_0 (0) /* subfield end bit position in field */
/* mvtaclo */
#define OP_FB_MASK_MVTACLO (0x00ffff70l) /* fixed bits mask */
#define OP_FB_MVTACLO (0x00fd1710l) /* fixed bits */
    /* 0th subfield of the field 'a' */
    #define OP_SF_MASK_MVTACLO_A_0 (0x00000080l) /* subfield mask */
    #define OP_SF_EBII_MVTACLO_A_0 (7) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVTACLO_A_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MVTACLO_RS_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MVTACLO_RS_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVTACLO_RS_0 (0) /* subfield end bit position in field */
/* racw */
#define OP_FB_MASK_RACW (0x00ffff6fl) /* fixed bits mask */
#define OP_FB_RACW (0x00fd1800l) /* fixed bits */
    /* 0th subfield of the field 'a' */
    #define OP_SF_MASK_RACW_A_0 (0x00000080l) /* subfield mask */
    #define OP_SF_EBII_RACW_A_0 (7) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_RACW_A_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_RACW_IMM_0 (0x00000010l) /* subfield mask */
    #define OP_SF_EBII_RACW_IMM_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_RACW_IMM_0 (0) /* subfield end bit position in field */
/* mvfachi */
#define OP_FB_MASK_MVFACHI (0x00fffe30l) /* fixed bits mask */
#define OP_FB_MVFACHI (0x00fd1e00l) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_MVFACHI_IMM_0 (0x00000100l) /* subfield mask */
    #define OP_SF_EBII_MVFACHI_IMM_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVFACHI_IMM_0 (1) /* subfield end bit position in field */
    /* 1th subfield of the field 'imm' */
    #define OP_SF_MASK_MVFACHI_IMM_1 (0x00000040l) /* subfield mask */
    #define OP_SF_EBII_MVFACHI_IMM_1 (6) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVFACHI_IMM_1 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'a' */
    #define OP_SF_MASK_MVFACHI_A_0 (0x00000080l) /* subfield mask */
    #define OP_SF_EBII_MVFACHI_A_0 (7) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVFACHI_A_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MVFACHI_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MVFACHI_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVFACHI_RD_0 (0) /* subfield end bit position in field */
/* mvfacmi */
#define OP_FB_MASK_MVFACMI (0x00fffe30l) /* fixed bits mask */
#define OP_FB_MVFACMI (0x00fd1e20l) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_MVFACMI_IMM_0 (0x00000100l) /* subfield mask */
    #define OP_SF_EBII_MVFACMI_IMM_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVFACMI_IMM_0 (1) /* subfield end bit position in field */
    /* 1th subfield of the field 'imm' */
    #define OP_SF_MASK_MVFACMI_IMM_1 (0x00000040l) /* subfield mask */
    #define OP_SF_EBII_MVFACMI_IMM_1 (6) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVFACMI_IMM_1 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'a' */
    #define OP_SF_MASK_MVFACMI_A_0 (0x00000080l) /* subfield mask */
    #define OP_SF_EBII_MVFACMI_A_0 (7) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVFACMI_A_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MVFACMI_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MVFACMI_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVFACMI_RD_0 (0) /* subfield end bit position in field */
/* mov_14 */
#define OP_FB_MASK_MOV_14 (0x00fff000l) /* fixed bits mask */
#define OP_FB_MOV_14 (0x00fd2000l) /* fixed bits */
    /* 0th subfield of the field 'ad' */
    #define OP_SF_MASK_MOV_14_AD_0 (0x00000c00l) /* subfield mask */
    #define OP_SF_EBII_MOV_14_AD_0 (10) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_14_AD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'sz' */
    #define OP_SF_MASK_MOV_14_SZ_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_MOV_14_SZ_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_14_SZ_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MOV_14_RD_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MOV_14_RD_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_14_RD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MOV_14_RS_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MOV_14_RS_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_14_RS_0 (0) /* subfield end bit position in field */
/* mov_15 */
#define OP_FB_MASK_MOV_15 (0x00fff000l) /* fixed bits mask */
#define OP_FB_MOV_15 (0x00fd2000l) /* fixed bits */
    /* 0th subfield of the field 'ad' */
    #define OP_SF_MASK_MOV_15_AD_0 (0x00000c00l) /* subfield mask */
    #define OP_SF_EBII_MOV_15_AD_0 (10) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_15_AD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'sz' */
    #define OP_SF_MASK_MOV_15_SZ_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_MOV_15_SZ_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_15_SZ_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MOV_15_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MOV_15_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_15_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MOV_15_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MOV_15_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_15_RD_0 (0) /* subfield end bit position in field */
/* movu_4 */
#define OP_FB_MASK_MOVU_4 (0x00fff200l) /* fixed bits mask */
#define OP_FB_MOVU_4 (0x00fd3000l) /* fixed bits */
    /* 0th subfield of the field 'ad' */
    #define OP_SF_MASK_MOVU_4_AD_0 (0x00000c00l) /* subfield mask */
    #define OP_SF_EBII_MOVU_4_AD_0 (10) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOVU_4_AD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'sz' */
    #define OP_SF_MASK_MOVU_4_SZ_0 (0x00000100l) /* subfield mask */
    #define OP_SF_EBII_MOVU_4_SZ_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOVU_4_SZ_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MOVU_4_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MOVU_4_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOVU_4_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MOVU_4_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MOVU_4_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOVU_4_RD_0 (0) /* subfield end bit position in field */
/* shlr_2 */
#define OP_FB_MASK_SHLR_2 (0x00ffff00l) /* fixed bits mask */
#define OP_FB_SHLR_2 (0x00fd6000l) /* fixed bits */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_SHLR_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_SHLR_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SHLR_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_SHLR_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_SHLR_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SHLR_2_RD_0 (0) /* subfield end bit position in field */
/* shar_2 */
#define OP_FB_MASK_SHAR_2 (0x00ffff00l) /* fixed bits mask */
#define OP_FB_SHAR_2 (0x00fd6100l) /* fixed bits */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_SHAR_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_SHAR_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SHAR_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_SHAR_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_SHAR_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SHAR_2_RD_0 (0) /* subfield end bit position in field */
/* shll_2 */
#define OP_FB_MASK_SHLL_2 (0x00ffff00l) /* fixed bits mask */
#define OP_FB_SHLL_2 (0x00fd6200l) /* fixed bits */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_SHLL_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_SHLL_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SHLL_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_SHLL_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_SHLL_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SHLL_2_RD_0 (0) /* subfield end bit position in field */
/* rotr_2 */
#define OP_FB_MASK_ROTR_2 (0x00ffff00l) /* fixed bits mask */
#define OP_FB_ROTR_2 (0x00fd6400l) /* fixed bits */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_ROTR_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_ROTR_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ROTR_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_ROTR_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_ROTR_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ROTR_2_RD_0 (0) /* subfield end bit position in field */
/* revw */
#define OP_FB_MASK_REVW (0x00ffff00l) /* fixed bits mask */
#define OP_FB_REVW (0x00fd6500l) /* fixed bits */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_REVW_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_REVW_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_REVW_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_REVW_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_REVW_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_REVW_RD_0 (0) /* subfield end bit position in field */
/* rotl_2 */
#define OP_FB_MASK_ROTL_2 (0x00ffff00l) /* fixed bits mask */
#define OP_FB_ROTL_2 (0x00fd6600l) /* fixed bits */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_ROTL_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_ROTL_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ROTL_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_ROTL_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_ROTL_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ROTL_2_RD_0 (0) /* subfield end bit position in field */
/* revl */
#define OP_FB_MASK_REVL (0x00ffff00l) /* fixed bits mask */
#define OP_FB_REVL (0x00fd6700l) /* fixed bits */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_REVL_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_REVL_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_REVL_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_REVL_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_REVL_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_REVL_RD_0 (0) /* subfield end bit position in field */
/* mvtc_2 */
#define OP_FB_MASK_MVTC_2 (0x00ffff00l) /* fixed bits mask */
#define OP_FB_MVTC_2 (0x00fd6800l) /* fixed bits */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MVTC_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MVTC_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVTC_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'cr' */
    #define OP_SF_MASK_MVTC_2_CR_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MVTC_2_CR_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVTC_2_CR_0 (0) /* subfield end bit position in field */
/* mvfc */
#define OP_FB_MASK_MVFC (0x00ffff00l) /* fixed bits mask */
#define OP_FB_MVFC (0x00fd6a00l) /* fixed bits */
    /* 0th subfield of the field 'cr' */
    #define OP_SF_MASK_MVFC_CR_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MVFC_CR_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVFC_CR_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MVFC_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MVFC_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVFC_RD_0 (0) /* subfield end bit position in field */
/* rotr_1 */
#define OP_FB_MASK_ROTR_1 (0x00fffe00l) /* fixed bits mask */
#define OP_FB_ROTR_1 (0x00fd6c00l) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_ROTR_1_IMM_0 (0x000001f0l) /* subfield mask */
    #define OP_SF_EBII_ROTR_1_IMM_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ROTR_1_IMM_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_ROTR_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_ROTR_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ROTR_1_RD_0 (0) /* subfield end bit position in field */
/* rotl_1 */
#define OP_FB_MASK_ROTL_1 (0x00fffe00l) /* fixed bits mask */
#define OP_FB_ROTL_1 (0x00fd6e00l) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_ROTL_1_IMM_0 (0x000001f0l) /* subfield mask */
    #define OP_SF_EBII_ROTL_1_IMM_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ROTL_1_IMM_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_ROTL_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_ROTL_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ROTL_1_RD_0 (0) /* subfield end bit position in field */
/* fadd_1 */
#define OP_FB_MASK_FADD_1 (0x00fffff0l) /* fixed bits mask */
#define OP_FB_FADD_1 (0x00fd7220l) /* fixed bits */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_FADD_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_FADD_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FADD_1_RD_0 (0) /* subfield end bit position in field */
/* fcmp_1 */
#define OP_FB_MASK_FCMP_1 (0x00fffff0l) /* fixed bits mask */
#define OP_FB_FCMP_1 (0x00fd7210l) /* fixed bits */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_FCMP_1_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_FCMP_1_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FCMP_1_RS2_0 (0) /* subfield end bit position in field */
/* fdiv_1 */
#define OP_FB_MASK_FDIV_1 (0x00fffff0l) /* fixed bits mask */
#define OP_FB_FDIV_1 (0x00fd7240l) /* fixed bits */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_FDIV_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_FDIV_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FDIV_1_RD_0 (0) /* subfield end bit position in field */
/* fmul_1 */
#define OP_FB_MASK_FMUL_1 (0x00fffff0l) /* fixed bits mask */
#define OP_FB_FMUL_1 (0x00fd7230l) /* fixed bits */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_FMUL_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_FMUL_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FMUL_1_RD_0 (0) /* subfield end bit position in field */
/* fsub_1 */
#define OP_FB_MASK_FSUB_1 (0x00fffff0l) /* fixed bits mask */
#define OP_FB_FSUB_1 (0x00fd7200l) /* fixed bits */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_FSUB_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_FSUB_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FSUB_1_RD_0 (0) /* subfield end bit position in field */
/* adc_1 */
#define OP_FB_MASK_ADC_1 (0x00fff3f0l) /* fixed bits mask */
#define OP_FB_ADC_1 (0x00fd7020l) /* fixed bits */
    /* 0th subfield of the field 'li' */
    #define OP_SF_MASK_ADC_1_LI_0 (0x00000c00l) /* subfield mask */
    #define OP_SF_EBII_ADC_1_LI_0 (10) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ADC_1_LI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_ADC_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_ADC_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ADC_1_RD_0 (0) /* subfield end bit position in field */
/* div_1 */
#define OP_FB_MASK_DIV_1 (0x00fff3f0l) /* fixed bits mask */
#define OP_FB_DIV_1 (0x00fd7080l) /* fixed bits */
    /* 0th subfield of the field 'li' */
    #define OP_SF_MASK_DIV_1_LI_0 (0x00000c00l) /* subfield mask */
    #define OP_SF_EBII_DIV_1_LI_0 (10) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_DIV_1_LI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_DIV_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_DIV_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_DIV_1_RD_0 (0) /* subfield end bit position in field */
/* divu_1 */
#define OP_FB_MASK_DIVU_1 (0x00fff3f0l) /* fixed bits mask */
#define OP_FB_DIVU_1 (0x00fd7090l) /* fixed bits */
    /* 0th subfield of the field 'li' */
    #define OP_SF_MASK_DIVU_1_LI_0 (0x00000c00l) /* subfield mask */
    #define OP_SF_EBII_DIVU_1_LI_0 (10) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_DIVU_1_LI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_DIVU_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_DIVU_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_DIVU_1_RD_0 (0) /* subfield end bit position in field */
/* emul_1 */
#define OP_FB_MASK_EMUL_1 (0x00fff3f0l) /* fixed bits mask */
#define OP_FB_EMUL_1 (0x00fd7060l) /* fixed bits */
    /* 0th subfield of the field 'li' */
    #define OP_SF_MASK_EMUL_1_LI_0 (0x00000c00l) /* subfield mask */
    #define OP_SF_EBII_EMUL_1_LI_0 (10) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_EMUL_1_LI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_EMUL_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_EMUL_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_EMUL_1_RD_0 (0) /* subfield end bit position in field */
/* emulu_1 */
#define OP_FB_MASK_EMULU_1 (0x00fff3f0l) /* fixed bits mask */
#define OP_FB_EMULU_1 (0x00fd7070l) /* fixed bits */
    /* 0th subfield of the field 'li' */
    #define OP_SF_MASK_EMULU_1_LI_0 (0x00000c00l) /* subfield mask */
    #define OP_SF_EBII_EMULU_1_LI_0 (10) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_EMULU_1_LI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_EMULU_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_EMULU_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_EMULU_1_RD_0 (0) /* subfield end bit position in field */
/* max_1 */
#define OP_FB_MASK_MAX_1 (0x00fff3f0l) /* fixed bits mask */
#define OP_FB_MAX_1 (0x00fd7040l) /* fixed bits */
    /* 0th subfield of the field 'li' */
    #define OP_SF_MASK_MAX_1_LI_0 (0x00000c00l) /* subfield mask */
    #define OP_SF_EBII_MAX_1_LI_0 (10) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MAX_1_LI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MAX_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MAX_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MAX_1_RD_0 (0) /* subfield end bit position in field */
/* min_1 */
#define OP_FB_MASK_MIN_1 (0x00fff3f0l) /* fixed bits mask */
#define OP_FB_MIN_1 (0x00fd7050l) /* fixed bits */
    /* 0th subfield of the field 'li' */
    #define OP_SF_MASK_MIN_1_LI_0 (0x00000c00l) /* subfield mask */
    #define OP_SF_EBII_MIN_1_LI_0 (10) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MIN_1_LI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MIN_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MIN_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MIN_1_RD_0 (0) /* subfield end bit position in field */
/* stnz_1 */
#define OP_FB_MASK_STNZ_1 (0x00fff3f0l) /* fixed bits mask */
#define OP_FB_STNZ_1 (0x00fd70f0l) /* fixed bits */
    /* 0th subfield of the field 'li' */
    #define OP_SF_MASK_STNZ_1_LI_0 (0x00000c00l) /* subfield mask */
    #define OP_SF_EBII_STNZ_1_LI_0 (10) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_STNZ_1_LI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_STNZ_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_STNZ_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_STNZ_1_RD_0 (0) /* subfield end bit position in field */
/* stz_1 */
#define OP_FB_MASK_STZ_1 (0x00fff3f0l) /* fixed bits mask */
#define OP_FB_STZ_1 (0x00fd70e0l) /* fixed bits */
    /* 0th subfield of the field 'li' */
    #define OP_SF_MASK_STZ_1_LI_0 (0x00000c00l) /* subfield mask */
    #define OP_SF_EBII_STZ_1_LI_0 (10) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_STZ_1_LI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_STZ_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_STZ_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_STZ_1_RD_0 (0) /* subfield end bit position in field */
/* tst_1 */
#define OP_FB_MASK_TST_1 (0x00fff3f0l) /* fixed bits mask */
#define OP_FB_TST_1 (0x00fd70c0l) /* fixed bits */
    /* 0th subfield of the field 'li' */
    #define OP_SF_MASK_TST_1_LI_0 (0x00000c00l) /* subfield mask */
    #define OP_SF_EBII_TST_1_LI_0 (10) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_TST_1_LI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_TST_1_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_TST_1_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_TST_1_RS2_0 (0) /* subfield end bit position in field */
/* xor_1 */
#define OP_FB_MASK_XOR_1 (0x00fff3f0l) /* fixed bits mask */
#define OP_FB_XOR_1 (0x00fd70d0l) /* fixed bits */
    /* 0th subfield of the field 'li' */
    #define OP_SF_MASK_XOR_1_LI_0 (0x00000c00l) /* subfield mask */
    #define OP_SF_EBII_XOR_1_LI_0 (10) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_XOR_1_LI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_XOR_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_XOR_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_XOR_1_RD_0 (0) /* subfield end bit position in field */
/* mvtc_1 */
#define OP_FB_MASK_MVTC_1 (0x00fff3f0l) /* fixed bits mask */
#define OP_FB_MVTC_1 (0x00fd7300l) /* fixed bits */
    /* 0th subfield of the field 'li' */
    #define OP_SF_MASK_MVTC_1_LI_0 (0x00000c00l) /* subfield mask */
    #define OP_SF_EBII_MVTC_1_LI_0 (10) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVTC_1_LI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'cr' */
    #define OP_SF_MASK_MVTC_1_CR_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MVTC_1_CR_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVTC_1_CR_0 (0) /* subfield end bit position in field */
/* mov_10 */
#define OP_FB_MASK_MOV_10 (0x00ffc000l) /* fixed bits mask */
#define OP_FB_MOV_10 (0x00fe4000l) /* fixed bits */
    /* 0th subfield of the field 'sz' */
    #define OP_SF_MASK_MOV_10_SZ_0 (0x00003000l) /* subfield mask */
    #define OP_SF_EBII_MOV_10_SZ_0 (12) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_10_SZ_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'ri' */
    #define OP_SF_MASK_MOV_10_RI_0 (0x00000f00l) /* subfield mask */
    #define OP_SF_EBII_MOV_10_RI_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_10_RI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rb' */
    #define OP_SF_MASK_MOV_10_RB_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MOV_10_RB_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_10_RB_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MOV_10_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MOV_10_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_10_RD_0 (0) /* subfield end bit position in field */
/* mov_12 */
#define OP_FB_MASK_MOV_12 (0x00ffc000l) /* fixed bits mask */
#define OP_FB_MOV_12 (0x00fe0000l) /* fixed bits */
    /* 0th subfield of the field 'sz' */
    #define OP_SF_MASK_MOV_12_SZ_0 (0x00003000l) /* subfield mask */
    #define OP_SF_EBII_MOV_12_SZ_0 (12) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_12_SZ_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'ri' */
    #define OP_SF_MASK_MOV_12_RI_0 (0x00000f00l) /* subfield mask */
    #define OP_SF_EBII_MOV_12_RI_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_12_RI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rb' */
    #define OP_SF_MASK_MOV_12_RB_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MOV_12_RB_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_12_RB_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MOV_12_RS_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MOV_12_RS_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_12_RS_0 (0) /* subfield end bit position in field */
/* movu_3 */
#define OP_FB_MASK_MOVU_3 (0x00ffe000l) /* fixed bits mask */
#define OP_FB_MOVU_3 (0x00fec000l) /* fixed bits */
    /* 0th subfield of the field 'sz' */
    #define OP_SF_MASK_MOVU_3_SZ_0 (0x00001000l) /* subfield mask */
    #define OP_SF_EBII_MOVU_3_SZ_0 (12) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOVU_3_SZ_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'ri' */
    #define OP_SF_MASK_MOVU_3_RI_0 (0x00000f00l) /* subfield mask */
    #define OP_SF_EBII_MOVU_3_RI_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOVU_3_RI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rb' */
    #define OP_SF_MASK_MOVU_3_RB_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MOVU_3_RB_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOVU_3_RB_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MOVU_3_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MOVU_3_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOVU_3_RD_0 (0) /* subfield end bit position in field */
/* add_4 */
#define OP_FB_MASK_ADD_4 (0x00fff000l) /* fixed bits mask */
#define OP_FB_ADD_4 (0x00ff2000l) /* fixed bits */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_ADD_4_RD_0 (0x00000f00l) /* subfield mask */
    #define OP_SF_EBII_ADD_4_RD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ADD_4_RD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_ADD_4_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_ADD_4_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ADD_4_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_ADD_4_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_ADD_4_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_ADD_4_RS2_0 (0) /* subfield end bit position in field */
/* and_4 */
#define OP_FB_MASK_AND_4 (0x00fff000l) /* fixed bits mask */
#define OP_FB_AND_4 (0x00ff4000l) /* fixed bits */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_AND_4_RD_0 (0x00000f00l) /* subfield mask */
    #define OP_SF_EBII_AND_4_RD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_AND_4_RD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_AND_4_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_AND_4_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_AND_4_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_AND_4_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_AND_4_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_AND_4_RS2_0 (0) /* subfield end bit position in field */
/* mul_4 */
#define OP_FB_MASK_MUL_4 (0x00fff000l) /* fixed bits mask */
#define OP_FB_MUL_4 (0x00ff3000l) /* fixed bits */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MUL_4_RD_0 (0x00000f00l) /* subfield mask */
    #define OP_SF_EBII_MUL_4_RD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MUL_4_RD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MUL_4_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MUL_4_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MUL_4_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_MUL_4_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MUL_4_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MUL_4_RS2_0 (0) /* subfield end bit position in field */
/* or_4 */
#define OP_FB_MASK_OR_4 (0x00fff000l) /* fixed bits mask */
#define OP_FB_OR_4 (0x00ff5000l) /* fixed bits */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_OR_4_RD_0 (0x00000f00l) /* subfield mask */
    #define OP_SF_EBII_OR_4_RD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_OR_4_RD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_OR_4_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_OR_4_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_OR_4_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_OR_4_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_OR_4_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_OR_4_RS2_0 (0) /* subfield end bit position in field */
/* sub_3 */
#define OP_FB_MASK_SUB_3 (0x00fff000l) /* fixed bits mask */
#define OP_FB_SUB_3 (0x00ff0000l) /* fixed bits */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_SUB_3_RD_0 (0x00000f00l) /* subfield mask */
    #define OP_SF_EBII_SUB_3_RD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SUB_3_RD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_SUB_3_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_SUB_3_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SUB_3_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_SUB_3_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_SUB_3_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_SUB_3_RS2_0 (0) /* subfield end bit position in field */
/* bclr_1 */
#define OP_FB_MASK_BCLR_1 (0x0000fc08l) /* fixed bits mask */
#define OP_FB_BCLR_1 (0x0000f008l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_BCLR_1_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_BCLR_1_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BCLR_1_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_BCLR_1_RD_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_BCLR_1_RD_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BCLR_1_RD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_BCLR_1_IMM_0 (0x00000007l) /* subfield mask */
    #define OP_SF_EBII_BCLR_1_IMM_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BCLR_1_IMM_0 (0) /* subfield end bit position in field */
/* bset_1 */
#define OP_FB_MASK_BSET_1 (0x0000fc00l) /* fixed bits mask */
#define OP_FB_BSET_1 (0x0000f000l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_BSET_1_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_BSET_1_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BSET_1_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_BSET_1_RD_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_BSET_1_RD_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BSET_1_RD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_BSET_1_RS_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_BSET_1_RS_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BSET_1_RS_0 (0) /* subfield end bit position in field */
/* btst_1 */
#define OP_FB_MASK_BTST_1 (0x0000fc08l) /* fixed bits mask */
#define OP_FB_BTST_1 (0x0000f400l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_BTST_1_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_BTST_1_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BTST_1_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_BTST_1_RS2_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_BTST_1_RS2_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BTST_1_RS2_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_BTST_1_IMM_0 (0x00000007l) /* subfield mask */
    #define OP_SF_EBII_BTST_1_IMM_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_BTST_1_IMM_0 (0) /* subfield end bit position in field */
/* push_2 */
#define OP_FB_MASK_PUSH_2 (0x0000fc0cl) /* fixed bits mask */
#define OP_FB_PUSH_2 (0x0000f408l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_PUSH_2_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_PUSH_2_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_PUSH_2_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_PUSH_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_PUSH_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_PUSH_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'sz' */
    #define OP_SF_MASK_PUSH_2_SZ_0 (0x00000003l) /* subfield mask */
    #define OP_SF_EBII_PUSH_2_SZ_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_PUSH_2_SZ_0 (0) /* subfield end bit position in field */
/* mov_6 */
#define OP_FB_MASK_MOV_6 (0x0000ff03l) /* fixed bits mask */
#define OP_FB_MOV_6 (0x0000fb02l) /* fixed bits */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MOV_6_RD_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MOV_6_RD_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_6_RD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'li' */
    #define OP_SF_MASK_MOV_6_LI_0 (0x0000000cl) /* subfield mask */
    #define OP_SF_EBII_MOV_6_LI_0 (2) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_6_LI_0 (0) /* subfield end bit position in field */
/* mov_8 */
#define OP_FB_MASK_MOV_8 (0x0000fc00l) /* fixed bits mask */
#define OP_FB_MOV_8 (0x0000f800l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_MOV_8_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_MOV_8_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_8_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MOV_8_RD_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MOV_8_RD_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_8_RD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'li' */
    #define OP_SF_MASK_MOV_8_LI_0 (0x0000000cl) /* subfield mask */
    #define OP_SF_EBII_MOV_8_LI_0 (2) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_8_LI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'sz' */
    #define OP_SF_MASK_MOV_8_SZ_0 (0x00000003l) /* subfield mask */
    #define OP_SF_EBII_MOV_8_SZ_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_8_SZ_0 (0) /* subfield end bit position in field */
/* mov_7 */
#define OP_FB_MASK_MOV_7 (0x0000cf00l) /* fixed bits mask */
#define OP_FB_MOV_7 (0x0000cf00l) /* fixed bits */
    /* 0th subfield of the field 'sz' */
    #define OP_SF_MASK_MOV_7_SZ_0 (0x00003000l) /* subfield mask */
    #define OP_SF_EBII_MOV_7_SZ_0 (12) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_7_SZ_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MOV_7_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MOV_7_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_7_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MOV_7_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MOV_7_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_7_RD_0 (0) /* subfield end bit position in field */
/* mov_9 */
#define OP_FB_MASK_MOV_9 (0x0000cc00l) /* fixed bits mask */
#define OP_FB_MOV_9 (0x0000cc00l) /* fixed bits */
    /* 0th subfield of the field 'sz' */
    #define OP_SF_MASK_MOV_9_SZ_0 (0x00003000l) /* subfield mask */
    #define OP_SF_EBII_MOV_9_SZ_0 (12) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_9_SZ_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_MOV_9_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_MOV_9_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_9_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MOV_9_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MOV_9_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_9_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MOV_9_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MOV_9_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_9_RD_0 (0) /* subfield end bit position in field */
/* mov_11 */
#define OP_FB_MASK_MOV_11 (0x0000c300l) /* fixed bits mask */
#define OP_FB_MOV_11 (0x0000c300l) /* fixed bits */
    /* 0th subfield of the field 'sz' */
    #define OP_SF_MASK_MOV_11_SZ_0 (0x00003000l) /* subfield mask */
    #define OP_SF_EBII_MOV_11_SZ_0 (12) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_11_SZ_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_MOV_11_LD_0 (0x00000c00l) /* subfield mask */
    #define OP_SF_EBII_MOV_11_LD_0 (10) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_11_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MOV_11_RD_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MOV_11_RD_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_11_RD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MOV_11_RS_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MOV_11_RS_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_11_RS_0 (0) /* subfield end bit position in field */
/* mov_13 */
#define OP_FB_MASK_MOV_13 (0x0000c000l) /* fixed bits mask */
#define OP_FB_MOV_13 (0x0000c000l) /* fixed bits */
    /* 0th subfield of the field 'sz' */
    #define OP_SF_MASK_MOV_13_SZ_0 (0x00003000l) /* subfield mask */
    #define OP_SF_EBII_MOV_13_SZ_0 (12) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_13_SZ_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'ldd' */
    #define OP_SF_MASK_MOV_13_LDD_0 (0x00000c00l) /* subfield mask */
    #define OP_SF_EBII_MOV_13_LDD_0 (10) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_13_LDD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'lds' */
    #define OP_SF_MASK_MOV_13_LDS_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_MOV_13_LDS_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_13_LDS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MOV_13_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MOV_13_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_13_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MOV_13_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MOV_13_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOV_13_RD_0 (0) /* subfield end bit position in field */
/* fsqrt */
#define OP_FB_MASK_FSQRT (0x00fffc00l) /* fixed bits mask */
#define OP_FB_FSQRT (0x00fca000l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_FSQRT_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_FSQRT_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FSQRT_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_FSQRT_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_FSQRT_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FSQRT_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_FSQRT_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_FSQRT_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FSQRT_RD_0 (0) /* subfield end bit position in field */
/* ftou */
#define OP_FB_MASK_FTOU (0x00fffc00l) /* fixed bits mask */
#define OP_FB_FTOU (0x00fca400l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_FTOU_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_FTOU_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FTOU_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_FTOU_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_FTOU_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FTOU_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_FTOU_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_FTOU_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FTOU_RD_0 (0) /* subfield end bit position in field */
/* utof_1 */
#define OP_FB_MASK_UTOF_1 (0x00fffc00l) /* fixed bits mask */
#define OP_FB_UTOF_1 (0x00fc5400l) /* fixed bits */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_UTOF_1_LD_0 (0x00000300l) /* subfield mask */
    #define OP_SF_EBII_UTOF_1_LD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_UTOF_1_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_UTOF_1_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_UTOF_1_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_UTOF_1_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_UTOF_1_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_UTOF_1_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_UTOF_1_RD_0 (0) /* subfield end bit position in field */
/* utof_1x */
#define OP_FB_MASK_UTOF_1X (0xff3cff00l) /* fixed bits mask */
#define OP_FB_UTOF_1X (0x06201500l) /* fixed bits */
    /* 0th subfield of the field 'mi' */
    #define OP_SF_MASK_UTOF_1X_MI_0 (0x00c00000l) /* subfield mask */
    #define OP_SF_EBII_UTOF_1X_MI_0 (22) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_UTOF_1X_MI_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'ld' */
    #define OP_SF_MASK_UTOF_1X_LD_0 (0x00030000l) /* subfield mask */
    #define OP_SF_EBII_UTOF_1X_LD_0 (16) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_UTOF_1X_LD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_UTOF_1X_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_UTOF_1X_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_UTOF_1X_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_UTOF_1X_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_UTOF_1X_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_UTOF_1X_RD_0 (0) /* subfield end bit position in field */
/* movco */
#define OP_FB_MASK_MOVCO (0x00ffff00l) /* fixed bits mask */
#define OP_FB_MOVCO (0x00fd2700l) /* fixed bits */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MOVCO_RD_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MOVCO_RD_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOVCO_RD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MOVCO_RS_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MOVCO_RS_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOVCO_RS_0 (0) /* subfield end bit position in field */
/* movli */
#define OP_FB_MASK_MOVLI (0x00ffff00l) /* fixed bits mask */
#define OP_FB_MOVLI (0x00fd2f00l) /* fixed bits */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MOVLI_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MOVLI_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOVLI_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MOVLI_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MOVLI_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MOVLI_RD_0 (0) /* subfield end bit position in field */
/* emaca */
#define OP_FB_MASK_EMACA (0x00fff700l) /* fixed bits mask */
#define OP_FB_EMACA (0x00fd0700l) /* fixed bits */
    /* 0th subfield of the field 'a' */
    #define OP_SF_MASK_EMACA_A_0 (0x00000800l) /* subfield mask */
    #define OP_SF_EBII_EMACA_A_0 (11) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_EMACA_A_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_EMACA_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_EMACA_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_EMACA_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_EMACA_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_EMACA_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_EMACA_RS2_0 (0) /* subfield end bit position in field */
/* emsba */
#define OP_FB_MASK_EMSBA (0x00fff700l) /* fixed bits mask */
#define OP_FB_EMSBA (0x00fd4700l) /* fixed bits */
    /* 0th subfield of the field 'a' */
    #define OP_SF_MASK_EMSBA_A_0 (0x00000800l) /* subfield mask */
    #define OP_SF_EBII_EMSBA_A_0 (11) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_EMSBA_A_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_EMSBA_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_EMSBA_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_EMSBA_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_EMSBA_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_EMSBA_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_EMSBA_RS2_0 (0) /* subfield end bit position in field */
/* emula */
#define OP_FB_MASK_EMULA (0x00fff700l) /* fixed bits mask */
#define OP_FB_EMULA (0x00fd0700l) /* fixed bits */
    /* 0th subfield of the field 'a' */
    #define OP_SF_MASK_EMULA_A_0 (0x00000800l) /* subfield mask */
    #define OP_SF_EBII_EMULA_A_0 (11) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_EMULA_A_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_EMULA_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_EMULA_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_EMULA_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_EMULA_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_EMULA_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_EMULA_RS2_0 (0) /* subfield end bit position in field */
/* maclh */
#define OP_FB_MASK_MACLH (0x00fff700l) /* fixed bits mask */
#define OP_FB_MACLH (0x00fd0700l) /* fixed bits */
    /* 0th subfield of the field 'a' */
    #define OP_SF_MASK_MACLH_A_0 (0x00000800l) /* subfield mask */
    #define OP_SF_EBII_MACLH_A_0 (11) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MACLH_A_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MACLH_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MACLH_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MACLH_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_MACLH_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MACLH_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MACLH_RS2_0 (0) /* subfield end bit position in field */
/* msbhi */
#define OP_FB_MASK_MSBHI (0x00fff700l) /* fixed bits mask */
#define OP_FB_MSBHI (0x00fd4700l) /* fixed bits */
    /* 0th subfield of the field 'a' */
    #define OP_SF_MASK_MSBHI_A_0 (0x00000800l) /* subfield mask */
    #define OP_SF_EBII_MSBHI_A_0 (11) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MSBHI_A_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MSBHI_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MSBHI_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MSBHI_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_MSBHI_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MSBHI_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MSBHI_RS2_0 (0) /* subfield end bit position in field */
/* msblh */
#define OP_FB_MASK_MSBLH (0x00fff700l) /* fixed bits mask */
#define OP_FB_MSBLH (0x00fd4600l) /* fixed bits */
    /* 0th subfield of the field 'a' */
    #define OP_SF_MASK_MSBLH_A_0 (0x00000800l) /* subfield mask */
    #define OP_SF_EBII_MSBLH_A_0 (11) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MSBLH_A_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MSBLH_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MSBLH_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MSBLH_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_MSBLH_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MSBLH_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MSBLH_RS2_0 (0) /* subfield end bit position in field */
/* msblo */
#define OP_FB_MASK_MSBLO (0x00fff700l) /* fixed bits mask */
#define OP_FB_MSBLO (0x00fd4500l) /* fixed bits */
    /* 0th subfield of the field 'a' */
    #define OP_SF_MASK_MSBLO_A_0 (0x00000800l) /* subfield mask */
    #define OP_SF_EBII_MSBLO_A_0 (11) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MSBLO_A_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MSBLO_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MSBLO_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MSBLO_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_MSBLO_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MSBLO_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MSBLO_RS2_0 (0) /* subfield end bit position in field */
/* mullh */
#define OP_FB_MASK_MULLH (0x00fff700l) /* fixed bits mask */
#define OP_FB_MULLH (0x00fd0200l) /* fixed bits */
    /* 0th subfield of the field 'a' */
    #define OP_SF_MASK_MULLH_A_0 (0x00000800l) /* subfield mask */
    #define OP_SF_EBII_MULLH_A_0 (11) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MULLH_A_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MULLH_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_MULLH_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MULLH_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_MULLH_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MULLH_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MULLH_RS2_0 (0) /* subfield end bit position in field */
/* mvfacgu */
#define OP_FB_MASK_MVFACGU (0x00fffe30l) /* fixed bits mask */
#define OP_FB_MVFACGU (0x00fd1e30l) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_MVFACGU_IMM_0 (0x00000100l) /* subfield mask */
    #define OP_SF_EBII_MVFACGU_IMM_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVFACGU_IMM_0 (1) /* subfield end bit position in field */
    /* 1th subfield of the field 'imm' */
    #define OP_SF_MASK_MVFACGU_IMM_1 (0x00000040l) /* subfield mask */
    #define OP_SF_EBII_MVFACGU_IMM_1 (6) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVFACGU_IMM_1 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'a' */
    #define OP_SF_MASK_MVFACGU_A_0 (0x00000080l) /* subfield mask */
    #define OP_SF_EBII_MVFACGU_A_0 (7) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVFACGU_A_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MVFACGU_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MVFACGU_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVFACGU_RD_0 (0) /* subfield end bit position in field */
/* mvfaclo */
#define OP_FB_MASK_MVFACLO (0x00fffe30l) /* fixed bits mask */
#define OP_FB_MVFACLO (0x00fd1e10l) /* fixed bits */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_MVFACLO_IMM_0 (0x00000100l) /* subfield mask */
    #define OP_SF_EBII_MVFACLO_IMM_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVFACLO_IMM_0 (1) /* subfield end bit position in field */
    /* 1th subfield of the field 'imm' */
    #define OP_SF_MASK_MVFACLO_IMM_1 (0x00000040l) /* subfield mask */
    #define OP_SF_EBII_MVFACLO_IMM_1 (6) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVFACLO_IMM_1 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'a' */
    #define OP_SF_MASK_MVFACLO_A_0 (0x00000080l) /* subfield mask */
    #define OP_SF_EBII_MVFACLO_A_0 (7) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVFACLO_A_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_MVFACLO_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MVFACLO_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVFACLO_RD_0 (0) /* subfield end bit position in field */
/* mvtacgu */
#define OP_FB_MASK_MVTACGU (0x00ffff70l) /* fixed bits mask */
#define OP_FB_MVTACGU (0x00fd1730l) /* fixed bits */
    /* 0th subfield of the field 'a' */
    #define OP_SF_MASK_MVTACGU_A_0 (0x00000080l) /* subfield mask */
    #define OP_SF_EBII_MVTACGU_A_0 (7) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVTACGU_A_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_MVTACGU_RS_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_MVTACGU_RS_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_MVTACGU_RS_0 (0) /* subfield end bit position in field */
/* racl */
#define OP_FB_MASK_RACL (0x00ffff6fl) /* fixed bits mask */
#define OP_FB_RACL (0x00fd1900l) /* fixed bits */
    /* 0th subfield of the field 'a' */
    #define OP_SF_MASK_RACL_A_0 (0x00000080l) /* subfield mask */
    #define OP_SF_EBII_RACL_A_0 (7) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_RACL_A_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_RACL_IMM_0 (0x00000010l) /* subfield mask */
    #define OP_SF_EBII_RACL_IMM_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_RACL_IMM_0 (0) /* subfield end bit position in field */
/* rdacl */
#define OP_FB_MASK_RDACL (0x00ffff6fl) /* fixed bits mask */
#define OP_FB_RDACL (0x00fd1940l) /* fixed bits */
    /* 0th subfield of the field 'a' */
    #define OP_SF_MASK_RDACL_A_0 (0x00000080l) /* subfield mask */
    #define OP_SF_EBII_RDACL_A_0 (7) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_RDACL_A_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_RDACL_IMM_0 (0x00000010l) /* subfield mask */
    #define OP_SF_EBII_RDACL_IMM_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_RDACL_IMM_0 (0) /* subfield end bit position in field */
/* rdacw */
#define OP_FB_MASK_RDACW (0x00ffff6fl) /* fixed bits mask */
#define OP_FB_RDACW (0x00fd1840l) /* fixed bits */
    /* 0th subfield of the field 'a' */
    #define OP_SF_MASK_RDACW_A_0 (0x00000080l) /* subfield mask */
    #define OP_SF_EBII_RDACW_A_0 (7) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_RDACW_A_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'imm' */
    #define OP_SF_MASK_RDACW_IMM_0 (0x00000010l) /* subfield mask */
    #define OP_SF_EBII_RDACW_IMM_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_RDACW_IMM_0 (0) /* subfield end bit position in field */
/* fadd_3 */
#define OP_FB_MASK_FADD_3 (0x00fff000l) /* fixed bits mask */
#define OP_FB_FADD_3 (0x00ffa000l) /* fixed bits */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_FADD_3_RD_0 (0x00000f00l) /* subfield mask */
    #define OP_SF_EBII_FADD_3_RD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FADD_3_RD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_FADD_3_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_FADD_3_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FADD_3_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_FADD_3_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_FADD_3_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FADD_3_RS2_0 (0) /* subfield end bit position in field */
/* fmul_3 */
#define OP_FB_MASK_FMUL_3 (0x00fff000l) /* fixed bits mask */
#define OP_FB_FMUL_3 (0x00ffb000l) /* fixed bits */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_FMUL_3_RD_0 (0x00000f00l) /* subfield mask */
    #define OP_SF_EBII_FMUL_3_RD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FMUL_3_RD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_FMUL_3_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_FMUL_3_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FMUL_3_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_FMUL_3_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_FMUL_3_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FMUL_3_RS2_0 (0) /* subfield end bit position in field */
/* fsub_3 */
#define OP_FB_MASK_FSUB_3 (0x00fff000l) /* fixed bits mask */
#define OP_FB_FSUB_3 (0x00ff8000l) /* fixed bits */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_FSUB_3_RD_0 (0x00000f00l) /* subfield mask */
    #define OP_SF_EBII_FSUB_3_RD_0 (8) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FSUB_3_RD_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_FSUB_3_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_FSUB_3_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FSUB_3_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rs2' */
    #define OP_SF_MASK_FSUB_3_RS2_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_FSUB_3_RS2_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_FSUB_3_RS2_0 (0) /* subfield end bit position in field */
/* stnz_2 */
#define OP_FB_MASK_STNZ_2 (0x00ffff00l) /* fixed bits mask */
#define OP_FB_STNZ_2 (0x00fc4f00l) /* fixed bits */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_STNZ_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_STNZ_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_STNZ_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_STNZ_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_STNZ_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_STNZ_2_RD_0 (0) /* subfield end bit position in field */
/* stz_2 */
#define OP_FB_MASK_STZ_2 (0x00ffff00l) /* fixed bits mask */
#define OP_FB_STZ_2 (0x00fc4b00l) /* fixed bits */
    /* 0th subfield of the field 'rs' */
    #define OP_SF_MASK_STZ_2_RS_0 (0x000000f0l) /* subfield mask */
    #define OP_SF_EBII_STZ_2_RS_0 (4) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_STZ_2_RS_0 (0) /* subfield end bit position in field */
    /* 0th subfield of the field 'rd' */
    #define OP_SF_MASK_STZ_2_RD_0 (0x0000000fl) /* subfield mask */
    #define OP_SF_EBII_STZ_2_RD_0 (0) /* subfield end bit position in instruction */
    #define OP_SF_EBIF_STZ_2_RD_0 (0) /* subfield end bit position in field */

/* macros */
#define BIT_ELEMENT(value, element_index) (((value) & (1 << (element_index))) >> element_index)

/* function declarations */
static rx_uint32 setbit_count(rx_uint32 value);

static int decision_node_code8x1_0(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code8x1_1(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code8x1_2(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code8x1_3(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code8x1_4(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code8x1_5(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code8x1_6(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code8x1_7(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_0(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_1(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_2(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_3(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_4(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_5(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_6(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_7(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_8(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_9(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_10(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_11(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_12(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_13(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_14(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_15(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_16(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_17(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_18(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_19(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_20(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_21(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_22(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_23(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_24(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_25(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_26(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_27(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_28(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_29(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_30(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_31(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_32(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_33(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_34(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_35(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_36(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_37(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_38(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_39(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_40(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_41(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_42(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_43(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_44(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_45(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_46(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_47(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_48(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_49(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_50(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_51(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_52(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_53(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_54(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_55(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_56(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_57(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_58(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_59(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_60(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_61(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_62(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_63(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_64(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_65(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_66(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_67(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_68(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_69(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_70(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_71(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_72(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_73(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_74(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_75(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_76(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_77(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_78(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_79(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_80(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_81(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_82(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_83(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_84(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_85(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_86(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_87(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_88(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_89(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_90(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_91(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_92(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_93(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_94(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_95(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_96(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_97(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_98(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_99(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_100(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_101(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_102(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_103(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_104(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_105(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_106(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_107(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_108(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_109(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_110(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_111(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code16x1_112(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_0(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_1(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_2(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_3(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_4(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_5(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_6(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_7(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_8(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_9(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_10(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_11(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_12(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_13(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_14(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_15(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_16(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_17(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_18(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_19(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_20(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_21(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_22(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_23(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_24(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_25(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_26(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_27(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_28(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_29(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_30(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_31(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_32(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_33(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_34(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_35(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_36(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_37(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_38(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_39(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_40(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_41(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_42(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_43(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_44(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_45(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_46(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_47(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_48(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_49(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_50(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_51(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_52(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_53(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_54(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_55(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_56(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_57(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_58(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_59(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_60(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_61(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_62(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_63(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_64(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_65(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_66(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_67(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_68(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_69(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_70(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_71(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_72(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_73(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_74(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_75(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_76(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_77(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_78(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_79(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_80(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_81(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_82(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_83(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_84(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_85(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_86(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_87(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_88(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_89(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_90(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_91(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_92(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_93(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_94(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_95(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_96(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_97(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_98(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_99(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_100(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_101(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_102(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_103(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_104(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_105(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_106(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_107(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_108(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_109(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_110(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_111(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_112(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_113(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_114(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_115(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_116(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_117(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_118(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_119(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_120(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_121(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_122(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_123(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_124(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_125(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_126(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_127(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_128(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_129(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_130(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_131(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_132(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_133(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_134(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_135(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_136(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_137(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_138(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_139(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_140(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_141(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_142(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_143(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_144(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_145(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_146(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_147(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_148(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_149(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_150(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_151(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_152(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_153(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_154(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_155(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_156(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_157(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_158(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_159(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_160(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_161(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_162(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_163(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_164(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_165(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_166(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_167(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code24x1_168(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code32x1_0(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code32x1_1(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code32x1_2(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code32x1_3(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code32x1_4(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code32x1_5(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code32x1_6(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code32x1_7(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code32x1_8(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code32x1_9(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code32x1_10(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code32x1_11(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code32x1_12(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code32x1_13(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code32x1_14(OpDecodeContext *context, rx_uint32 code);
static int decision_node_code32x1_15(OpDecodeContext *context, rx_uint32 code);

static int op_parse_brk(OpDecodeContext *context);
static int op_parse_rts(OpDecodeContext *context);
static int op_parse_nop(OpDecodeContext *context);
static int op_parse_bra_a(OpDecodeContext *context);
static int op_parse_bsr_a(OpDecodeContext *context);
static int op_parse_sub_2x(OpDecodeContext *context);
static int op_parse_cmp_4x(OpDecodeContext *context);
static int op_parse_add_2x(OpDecodeContext *context);
static int op_parse_mul_3x(OpDecodeContext *context);
static int op_parse_and_3x(OpDecodeContext *context);
static int op_parse_or_3x(OpDecodeContext *context);
static int op_parse_sbb_2(OpDecodeContext *context);
static int op_parse_adc_3(OpDecodeContext *context);
static int op_parse_div_2x(OpDecodeContext *context);
static int op_parse_divu_2x(OpDecodeContext *context);
static int op_parse_emul_2x(OpDecodeContext *context);
static int op_parse_emulu_2x(OpDecodeContext *context);
static int op_parse_itof_1x(OpDecodeContext *context);
static int op_parse_max_2x(OpDecodeContext *context);
static int op_parse_min_2x(OpDecodeContext *context);
static int op_parse_tst_2x(OpDecodeContext *context);
static int op_parse_xchg_1x(OpDecodeContext *context);
static int op_parse_xor_2x(OpDecodeContext *context);
static int op_parse_bra_s(OpDecodeContext *context);
static int op_parse_bcnd_s(OpDecodeContext *context);
static int op_parse_bra_b(OpDecodeContext *context);
static int op_parse_bcnd_b(OpDecodeContext *context);
static int op_parse_bra_w(OpDecodeContext *context);
static int op_parse_bsr_w(OpDecodeContext *context);
static int op_parse_bcnd_w(OpDecodeContext *context);
static int op_parse_rtsd_2(OpDecodeContext *context);
static int op_parse_mov_4(OpDecodeContext *context);
static int op_parse_sub_2(OpDecodeContext *context);
static int op_parse_cmp_4(OpDecodeContext *context);
static int op_parse_add_2(OpDecodeContext *context);
static int op_parse_mul_3(OpDecodeContext *context);
static int op_parse_and_3(OpDecodeContext *context);
static int op_parse_or_3(OpDecodeContext *context);
static int op_parse_movu_2(OpDecodeContext *context);
static int op_parse_sub_1(OpDecodeContext *context);
static int op_parse_cmp_1(OpDecodeContext *context);
static int op_parse_add_1(OpDecodeContext *context);
static int op_parse_mul_1(OpDecodeContext *context);
static int op_parse_and_1(OpDecodeContext *context);
static int op_parse_or_1(OpDecodeContext *context);
static int op_parse_mov_3(OpDecodeContext *context);
static int op_parse_rtsd_1(OpDecodeContext *context);
static int op_parse_shlr_1(OpDecodeContext *context);
static int op_parse_shar_1(OpDecodeContext *context);
static int op_parse_shll_1(OpDecodeContext *context);
static int op_parse_pushm(OpDecodeContext *context);
static int op_parse_popm(OpDecodeContext *context);
static int op_parse_add_3(OpDecodeContext *context);
static int op_parse_cmp_2(OpDecodeContext *context);
static int op_parse_int(OpDecodeContext *context);
static int op_parse_mov_5(OpDecodeContext *context);
static int op_parse_mvtipl(OpDecodeContext *context);
static int op_parse_and_2(OpDecodeContext *context);
static int op_parse_cmp_3(OpDecodeContext *context);
static int op_parse_mul_2(OpDecodeContext *context);
static int op_parse_or_2(OpDecodeContext *context);
static int op_parse_bset_3(OpDecodeContext *context);
static int op_parse_bclr_3(OpDecodeContext *context);
static int op_parse_btst_3(OpDecodeContext *context);
static int op_parse_abs_1(OpDecodeContext *context);
static int op_parse_neg_1(OpDecodeContext *context);
static int op_parse_not_1(OpDecodeContext *context);
static int op_parse_rolc(OpDecodeContext *context);
static int op_parse_pop(OpDecodeContext *context);
static int op_parse_popc(OpDecodeContext *context);
static int op_parse_rorc(OpDecodeContext *context);
static int op_parse_push_1(OpDecodeContext *context);
static int op_parse_pushc(OpDecodeContext *context);
static int op_parse_sat(OpDecodeContext *context);
static int op_parse_jmp(OpDecodeContext *context);
static int op_parse_jsr(OpDecodeContext *context);
static int op_parse_bra_l(OpDecodeContext *context);
static int op_parse_bsr_l(OpDecodeContext *context);
static int op_parse_scmpu(OpDecodeContext *context);
static int op_parse_suntil_b(OpDecodeContext *context);
static int op_parse_suntil_w(OpDecodeContext *context);
static int op_parse_suntil_l(OpDecodeContext *context);
static int op_parse_smovu(OpDecodeContext *context);
static int op_parse_swhile_b(OpDecodeContext *context);
static int op_parse_swhile_w(OpDecodeContext *context);
static int op_parse_swhile_l(OpDecodeContext *context);
static int op_parse_smovb(OpDecodeContext *context);
static int op_parse_sstr_b(OpDecodeContext *context);
static int op_parse_sstr_w(OpDecodeContext *context);
static int op_parse_sstr_l(OpDecodeContext *context);
static int op_parse_smovf(OpDecodeContext *context);
static int op_parse_rmpa(OpDecodeContext *context);
static int op_parse_satr(OpDecodeContext *context);
static int op_parse_rtfi(OpDecodeContext *context);
static int op_parse_rte(OpDecodeContext *context);
static int op_parse_wait(OpDecodeContext *context);
static int op_parse_setpsw(OpDecodeContext *context);
static int op_parse_clrpsw(OpDecodeContext *context);
static int op_parse_movu_1(OpDecodeContext *context);
static int op_parse_mov_1(OpDecodeContext *context);
static int op_parse_mov_2(OpDecodeContext *context);
static int op_parse_sbb_1(OpDecodeContext *context);
static int op_parse_neg_2(OpDecodeContext *context);
static int op_parse_adc_2(OpDecodeContext *context);
static int op_parse_abs_2(OpDecodeContext *context);
static int op_parse_not_2(OpDecodeContext *context);
static int op_parse_bset_4(OpDecodeContext *context);
static int op_parse_bclr_4(OpDecodeContext *context);
static int op_parse_btst_4(OpDecodeContext *context);
static int op_parse_bnot_4(OpDecodeContext *context);
static int op_parse_max_2(OpDecodeContext *context);
static int op_parse_min_2(OpDecodeContext *context);
static int op_parse_emul_2(OpDecodeContext *context);
static int op_parse_emulu_2(OpDecodeContext *context);
static int op_parse_div_2(OpDecodeContext *context);
static int op_parse_divu_2(OpDecodeContext *context);
static int op_parse_tst_2(OpDecodeContext *context);
static int op_parse_xor_2(OpDecodeContext *context);
static int op_parse_xchg_1(OpDecodeContext *context);
static int op_parse_itof_1(OpDecodeContext *context);
static int op_parse_bset_2(OpDecodeContext *context);
static int op_parse_bclr_2(OpDecodeContext *context);
static int op_parse_btst_2(OpDecodeContext *context);
static int op_parse_bnot_2(OpDecodeContext *context);
static int op_parse_fsub_2(OpDecodeContext *context);
static int op_parse_fcmp_2(OpDecodeContext *context);
static int op_parse_fadd_2(OpDecodeContext *context);
static int op_parse_fmul_2(OpDecodeContext *context);
static int op_parse_fdiv_2(OpDecodeContext *context);
static int op_parse_ftoi(OpDecodeContext *context);
static int op_parse_round(OpDecodeContext *context);
static int op_parse_sccnd(OpDecodeContext *context);
static int op_parse_bmcnd_1(OpDecodeContext *context);
static int op_parse_bnot_1(OpDecodeContext *context);
static int op_parse_shlr_3(OpDecodeContext *context);
static int op_parse_shar_3(OpDecodeContext *context);
static int op_parse_shll_3(OpDecodeContext *context);
static int op_parse_bmcnd_2(OpDecodeContext *context);
static int op_parse_bnot_3(OpDecodeContext *context);
static int op_parse_mulhi(OpDecodeContext *context);
static int op_parse_mullo(OpDecodeContext *context);
static int op_parse_machi(OpDecodeContext *context);
static int op_parse_maclo(OpDecodeContext *context);
static int op_parse_mvtachi(OpDecodeContext *context);
static int op_parse_mvtaclo(OpDecodeContext *context);
static int op_parse_racw(OpDecodeContext *context);
static int op_parse_mvfachi(OpDecodeContext *context);
static int op_parse_mvfacmi(OpDecodeContext *context);
static int op_parse_mov_14(OpDecodeContext *context);
static int op_parse_mov_15(OpDecodeContext *context);
static int op_parse_movu_4(OpDecodeContext *context);
static int op_parse_shlr_2(OpDecodeContext *context);
static int op_parse_shar_2(OpDecodeContext *context);
static int op_parse_shll_2(OpDecodeContext *context);
static int op_parse_rotr_2(OpDecodeContext *context);
static int op_parse_revw(OpDecodeContext *context);
static int op_parse_rotl_2(OpDecodeContext *context);
static int op_parse_revl(OpDecodeContext *context);
static int op_parse_mvtc_2(OpDecodeContext *context);
static int op_parse_mvfc(OpDecodeContext *context);
static int op_parse_rotr_1(OpDecodeContext *context);
static int op_parse_rotl_1(OpDecodeContext *context);
static int op_parse_fadd_1(OpDecodeContext *context);
static int op_parse_fcmp_1(OpDecodeContext *context);
static int op_parse_fdiv_1(OpDecodeContext *context);
static int op_parse_fmul_1(OpDecodeContext *context);
static int op_parse_fsub_1(OpDecodeContext *context);
static int op_parse_adc_1(OpDecodeContext *context);
static int op_parse_div_1(OpDecodeContext *context);
static int op_parse_divu_1(OpDecodeContext *context);
static int op_parse_emul_1(OpDecodeContext *context);
static int op_parse_emulu_1(OpDecodeContext *context);
static int op_parse_max_1(OpDecodeContext *context);
static int op_parse_min_1(OpDecodeContext *context);
static int op_parse_stnz_1(OpDecodeContext *context);
static int op_parse_stz_1(OpDecodeContext *context);
static int op_parse_tst_1(OpDecodeContext *context);
static int op_parse_xor_1(OpDecodeContext *context);
static int op_parse_mvtc_1(OpDecodeContext *context);
static int op_parse_mov_10(OpDecodeContext *context);
static int op_parse_mov_12(OpDecodeContext *context);
static int op_parse_movu_3(OpDecodeContext *context);
static int op_parse_add_4(OpDecodeContext *context);
static int op_parse_and_4(OpDecodeContext *context);
static int op_parse_mul_4(OpDecodeContext *context);
static int op_parse_or_4(OpDecodeContext *context);
static int op_parse_sub_3(OpDecodeContext *context);
static int op_parse_bclr_1(OpDecodeContext *context);
static int op_parse_bset_1(OpDecodeContext *context);
static int op_parse_btst_1(OpDecodeContext *context);
static int op_parse_push_2(OpDecodeContext *context);
static int op_parse_mov_6(OpDecodeContext *context);
static int op_parse_mov_8(OpDecodeContext *context);
static int op_parse_mov_7(OpDecodeContext *context);
static int op_parse_mov_9(OpDecodeContext *context);
static int op_parse_mov_11(OpDecodeContext *context);
static int op_parse_mov_13(OpDecodeContext *context);
static int op_parse_fsqrt(OpDecodeContext *context);
static int op_parse_ftou(OpDecodeContext *context);
static int op_parse_utof_1(OpDecodeContext *context);
static int op_parse_utof_1x(OpDecodeContext *context);
static int op_parse_movco(OpDecodeContext *context);
static int op_parse_movli(OpDecodeContext *context);
static int op_parse_emaca(OpDecodeContext *context);
static int op_parse_emsba(OpDecodeContext *context);
static int op_parse_emula(OpDecodeContext *context);
static int op_parse_maclh(OpDecodeContext *context);
static int op_parse_msbhi(OpDecodeContext *context);
static int op_parse_msblh(OpDecodeContext *context);
static int op_parse_msblo(OpDecodeContext *context);
static int op_parse_mullh(OpDecodeContext *context);
static int op_parse_mvfacgu(OpDecodeContext *context);
static int op_parse_mvfaclo(OpDecodeContext *context);
static int op_parse_mvtacgu(OpDecodeContext *context);
static int op_parse_racl(OpDecodeContext *context);
static int op_parse_rdacl(OpDecodeContext *context);
static int op_parse_rdacw(OpDecodeContext *context);
static int op_parse_fadd_3(OpDecodeContext *context);
static int op_parse_fmul_3(OpDecodeContext *context);
static int op_parse_fsub_3(OpDecodeContext *context);
static int op_parse_stnz_2(OpDecodeContext *context);
static int op_parse_stz_2(OpDecodeContext *context);

/* functions for conditions */
static rx_uint32 setbit_count(rx_uint32 value) {
    rx_uint32 count = 0;
    while (value) {
        count += value & 1;
        value >>= 1;
    }
    return count;
}

/* individual op parse functions */

/* brk */
static int op_parse_brk(OpDecodeContext *context) {
    if ((context->code8x1 & OP_FB_MASK_BRK) != OP_FB_BRK) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_brk;
    context->optype->format_id = RX_OP_CODE_FORMAT_BRK;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BRK;

    return 0;
}

/* rts */
static int op_parse_rts(OpDecodeContext *context) {
    if ((context->code8x1 & OP_FB_MASK_RTS) != OP_FB_RTS) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_rts;
    context->optype->format_id = RX_OP_CODE_FORMAT_RTS;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_RTS;

    return 0;
}

/* nop */
static int op_parse_nop(OpDecodeContext *context) {
    if ((context->code8x1 & OP_FB_MASK_NOP) != OP_FB_NOP) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_nop;
    context->optype->format_id = RX_OP_CODE_FORMAT_NOP;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_NOP;

    return 0;
}

/* bra_a */
static int op_parse_bra_a(OpDecodeContext *context) {
    if ((context->code32x1 & OP_FB_MASK_BRA_A) != OP_FB_BRA_A) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_bra_a;
    context->optype->format_id = RX_OP_CODE_FORMAT_BRA_A;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BRA_A;
    context->decoded_code->code.rx_bra_a.pcdsp =
        (((context->code32x1 & OP_SF_MASK_BRA_A_PCDSP_0) >> OP_SF_EBII_BRA_A_PCDSP_0) << OP_SF_EBIF_BRA_A_PCDSP_0);

    return 0;
}

/* bsr_a */
static int op_parse_bsr_a(OpDecodeContext *context) {
    if ((context->code32x1 & OP_FB_MASK_BSR_A) != OP_FB_BSR_A) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_bsr_a;
    context->optype->format_id = RX_OP_CODE_FORMAT_BSR_A;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BSR_A;
    context->decoded_code->code.rx_bsr_a.pcdsp =
        (((context->code32x1 & OP_SF_MASK_BSR_A_PCDSP_0) >> OP_SF_EBII_BSR_A_PCDSP_0) << OP_SF_EBIF_BSR_A_PCDSP_0);

    return 0;
}

/* sub_2x */
static int op_parse_sub_2x(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_SUB_2X) != OP_FB_SUB_2X) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_sub_2x;
    context->optype->format_id = RX_OP_CODE_FORMAT_SUB_2X;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SUB_2X;
    context->decoded_code->code.rx_sub_2x.mi =
        (((context->code24x1 & OP_SF_MASK_SUB_2X_MI_0) >> OP_SF_EBII_SUB_2X_MI_0) << OP_SF_EBIF_SUB_2X_MI_0);
    context->decoded_code->code.rx_sub_2x.ld =
        (((context->code24x1 & OP_SF_MASK_SUB_2X_LD_0) >> OP_SF_EBII_SUB_2X_LD_0) << OP_SF_EBIF_SUB_2X_LD_0);
    context->decoded_code->code.rx_sub_2x.rs =
        (((context->code24x1 & OP_SF_MASK_SUB_2X_RS_0) >> OP_SF_EBII_SUB_2X_RS_0) << OP_SF_EBIF_SUB_2X_RS_0);
    context->decoded_code->code.rx_sub_2x.rd =
        (((context->code24x1 & OP_SF_MASK_SUB_2X_RD_0) >> OP_SF_EBII_SUB_2X_RD_0) << OP_SF_EBIF_SUB_2X_RD_0);

    return 0;
}

/* cmp_4x */
static int op_parse_cmp_4x(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_CMP_4X) != OP_FB_CMP_4X) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_cmp_4x;
    context->optype->format_id = RX_OP_CODE_FORMAT_CMP_4X;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_CMP_4X;
    context->decoded_code->code.rx_cmp_4x.mi =
        (((context->code24x1 & OP_SF_MASK_CMP_4X_MI_0) >> OP_SF_EBII_CMP_4X_MI_0) << OP_SF_EBIF_CMP_4X_MI_0);
    context->decoded_code->code.rx_cmp_4x.ld =
        (((context->code24x1 & OP_SF_MASK_CMP_4X_LD_0) >> OP_SF_EBII_CMP_4X_LD_0) << OP_SF_EBIF_CMP_4X_LD_0);
    context->decoded_code->code.rx_cmp_4x.rs =
        (((context->code24x1 & OP_SF_MASK_CMP_4X_RS_0) >> OP_SF_EBII_CMP_4X_RS_0) << OP_SF_EBIF_CMP_4X_RS_0);
    context->decoded_code->code.rx_cmp_4x.rs2 =
        (((context->code24x1 & OP_SF_MASK_CMP_4X_RS2_0) >> OP_SF_EBII_CMP_4X_RS2_0) << OP_SF_EBIF_CMP_4X_RS2_0);

    return 0;
}

/* add_2x */
static int op_parse_add_2x(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_ADD_2X) != OP_FB_ADD_2X) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_add_2x;
    context->optype->format_id = RX_OP_CODE_FORMAT_ADD_2X;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_ADD_2X;
    context->decoded_code->code.rx_add_2x.mi =
        (((context->code24x1 & OP_SF_MASK_ADD_2X_MI_0) >> OP_SF_EBII_ADD_2X_MI_0) << OP_SF_EBIF_ADD_2X_MI_0);
    context->decoded_code->code.rx_add_2x.ld =
        (((context->code24x1 & OP_SF_MASK_ADD_2X_LD_0) >> OP_SF_EBII_ADD_2X_LD_0) << OP_SF_EBIF_ADD_2X_LD_0);
    context->decoded_code->code.rx_add_2x.rs =
        (((context->code24x1 & OP_SF_MASK_ADD_2X_RS_0) >> OP_SF_EBII_ADD_2X_RS_0) << OP_SF_EBIF_ADD_2X_RS_0);
    context->decoded_code->code.rx_add_2x.rd =
        (((context->code24x1 & OP_SF_MASK_ADD_2X_RD_0) >> OP_SF_EBII_ADD_2X_RD_0) << OP_SF_EBIF_ADD_2X_RD_0);

    return 0;
}

/* mul_3x */
static int op_parse_mul_3x(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MUL_3X) != OP_FB_MUL_3X) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mul_3x;
    context->optype->format_id = RX_OP_CODE_FORMAT_MUL_3X;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MUL_3X;
    context->decoded_code->code.rx_mul_3x.mi =
        (((context->code24x1 & OP_SF_MASK_MUL_3X_MI_0) >> OP_SF_EBII_MUL_3X_MI_0) << OP_SF_EBIF_MUL_3X_MI_0);
    context->decoded_code->code.rx_mul_3x.ld =
        (((context->code24x1 & OP_SF_MASK_MUL_3X_LD_0) >> OP_SF_EBII_MUL_3X_LD_0) << OP_SF_EBIF_MUL_3X_LD_0);
    context->decoded_code->code.rx_mul_3x.rs =
        (((context->code24x1 & OP_SF_MASK_MUL_3X_RS_0) >> OP_SF_EBII_MUL_3X_RS_0) << OP_SF_EBIF_MUL_3X_RS_0);
    context->decoded_code->code.rx_mul_3x.rd =
        (((context->code24x1 & OP_SF_MASK_MUL_3X_RD_0) >> OP_SF_EBII_MUL_3X_RD_0) << OP_SF_EBIF_MUL_3X_RD_0);

    return 0;
}

/* and_3x */
static int op_parse_and_3x(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_AND_3X) != OP_FB_AND_3X) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_and_3x;
    context->optype->format_id = RX_OP_CODE_FORMAT_AND_3X;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_AND_3X;
    context->decoded_code->code.rx_and_3x.mi =
        (((context->code24x1 & OP_SF_MASK_AND_3X_MI_0) >> OP_SF_EBII_AND_3X_MI_0) << OP_SF_EBIF_AND_3X_MI_0);
    context->decoded_code->code.rx_and_3x.ld =
        (((context->code24x1 & OP_SF_MASK_AND_3X_LD_0) >> OP_SF_EBII_AND_3X_LD_0) << OP_SF_EBIF_AND_3X_LD_0);
    context->decoded_code->code.rx_and_3x.rs =
        (((context->code24x1 & OP_SF_MASK_AND_3X_RS_0) >> OP_SF_EBII_AND_3X_RS_0) << OP_SF_EBIF_AND_3X_RS_0);
    context->decoded_code->code.rx_and_3x.rd =
        (((context->code24x1 & OP_SF_MASK_AND_3X_RD_0) >> OP_SF_EBII_AND_3X_RD_0) << OP_SF_EBIF_AND_3X_RD_0);

    return 0;
}

/* or_3x */
static int op_parse_or_3x(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_OR_3X) != OP_FB_OR_3X) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_or_3x;
    context->optype->format_id = RX_OP_CODE_FORMAT_OR_3X;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_OR_3X;
    context->decoded_code->code.rx_or_3x.mi =
        (((context->code24x1 & OP_SF_MASK_OR_3X_MI_0) >> OP_SF_EBII_OR_3X_MI_0) << OP_SF_EBIF_OR_3X_MI_0);
    context->decoded_code->code.rx_or_3x.ld =
        (((context->code24x1 & OP_SF_MASK_OR_3X_LD_0) >> OP_SF_EBII_OR_3X_LD_0) << OP_SF_EBIF_OR_3X_LD_0);
    context->decoded_code->code.rx_or_3x.rs =
        (((context->code24x1 & OP_SF_MASK_OR_3X_RS_0) >> OP_SF_EBII_OR_3X_RS_0) << OP_SF_EBIF_OR_3X_RS_0);
    context->decoded_code->code.rx_or_3x.rd =
        (((context->code24x1 & OP_SF_MASK_OR_3X_RD_0) >> OP_SF_EBII_OR_3X_RD_0) << OP_SF_EBIF_OR_3X_RD_0);

    return 0;
}

/* sbb_2 */
static int op_parse_sbb_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_SBB_2) != OP_FB_SBB_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_sbb_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_SBB_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SBB_2;
    context->decoded_code->code.rx_sbb_2.ld =
        (((context->code24x1 & OP_SF_MASK_SBB_2_LD_0) >> OP_SF_EBII_SBB_2_LD_0) << OP_SF_EBIF_SBB_2_LD_0);
    context->decoded_code->code.rx_sbb_2.rs =
        (((context->code24x1 & OP_SF_MASK_SBB_2_RS_0) >> OP_SF_EBII_SBB_2_RS_0) << OP_SF_EBIF_SBB_2_RS_0);
    context->decoded_code->code.rx_sbb_2.rd =
        (((context->code24x1 & OP_SF_MASK_SBB_2_RD_0) >> OP_SF_EBII_SBB_2_RD_0) << OP_SF_EBIF_SBB_2_RD_0);

    return 0;
}

/* adc_3 */
static int op_parse_adc_3(OpDecodeContext *context) {
    if ((context->code32x1 & OP_FB_MASK_ADC_3) != OP_FB_ADC_3) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_adc_3;
    context->optype->format_id = RX_OP_CODE_FORMAT_ADC_3;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_ADC_3;
    context->decoded_code->code.rx_adc_3.mi =
        (((context->code32x1 & OP_SF_MASK_ADC_3_MI_0) >> OP_SF_EBII_ADC_3_MI_0) << OP_SF_EBIF_ADC_3_MI_0);
    context->decoded_code->code.rx_adc_3.ld =
        (((context->code32x1 & OP_SF_MASK_ADC_3_LD_0) >> OP_SF_EBII_ADC_3_LD_0) << OP_SF_EBIF_ADC_3_LD_0);
    context->decoded_code->code.rx_adc_3.rs =
        (((context->code32x1 & OP_SF_MASK_ADC_3_RS_0) >> OP_SF_EBII_ADC_3_RS_0) << OP_SF_EBIF_ADC_3_RS_0);
    context->decoded_code->code.rx_adc_3.rd =
        (((context->code32x1 & OP_SF_MASK_ADC_3_RD_0) >> OP_SF_EBII_ADC_3_RD_0) << OP_SF_EBIF_ADC_3_RD_0);

    return 0;
}

/* div_2x */
static int op_parse_div_2x(OpDecodeContext *context) {
    if ((context->code32x1 & OP_FB_MASK_DIV_2X) != OP_FB_DIV_2X) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_div_2x;
    context->optype->format_id = RX_OP_CODE_FORMAT_DIV_2X;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_DIV_2X;
    context->decoded_code->code.rx_div_2x.mi =
        (((context->code32x1 & OP_SF_MASK_DIV_2X_MI_0) >> OP_SF_EBII_DIV_2X_MI_0) << OP_SF_EBIF_DIV_2X_MI_0);
    context->decoded_code->code.rx_div_2x.ld =
        (((context->code32x1 & OP_SF_MASK_DIV_2X_LD_0) >> OP_SF_EBII_DIV_2X_LD_0) << OP_SF_EBIF_DIV_2X_LD_0);
    context->decoded_code->code.rx_div_2x.rs =
        (((context->code32x1 & OP_SF_MASK_DIV_2X_RS_0) >> OP_SF_EBII_DIV_2X_RS_0) << OP_SF_EBIF_DIV_2X_RS_0);
    context->decoded_code->code.rx_div_2x.rd =
        (((context->code32x1 & OP_SF_MASK_DIV_2X_RD_0) >> OP_SF_EBII_DIV_2X_RD_0) << OP_SF_EBIF_DIV_2X_RD_0);

    return 0;
}

/* divu_2x */
static int op_parse_divu_2x(OpDecodeContext *context) {
    if ((context->code32x1 & OP_FB_MASK_DIVU_2X) != OP_FB_DIVU_2X) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_divu_2x;
    context->optype->format_id = RX_OP_CODE_FORMAT_DIVU_2X;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_DIVU_2X;
    context->decoded_code->code.rx_divu_2x.mi =
        (((context->code32x1 & OP_SF_MASK_DIVU_2X_MI_0) >> OP_SF_EBII_DIVU_2X_MI_0) << OP_SF_EBIF_DIVU_2X_MI_0);
    context->decoded_code->code.rx_divu_2x.ld =
        (((context->code32x1 & OP_SF_MASK_DIVU_2X_LD_0) >> OP_SF_EBII_DIVU_2X_LD_0) << OP_SF_EBIF_DIVU_2X_LD_0);
    context->decoded_code->code.rx_divu_2x.rs =
        (((context->code32x1 & OP_SF_MASK_DIVU_2X_RS_0) >> OP_SF_EBII_DIVU_2X_RS_0) << OP_SF_EBIF_DIVU_2X_RS_0);
    context->decoded_code->code.rx_divu_2x.rd =
        (((context->code32x1 & OP_SF_MASK_DIVU_2X_RD_0) >> OP_SF_EBII_DIVU_2X_RD_0) << OP_SF_EBIF_DIVU_2X_RD_0);

    return 0;
}

/* emul_2x */
static int op_parse_emul_2x(OpDecodeContext *context) {
    if ((context->code32x1 & OP_FB_MASK_EMUL_2X) != OP_FB_EMUL_2X) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_emul_2x;
    context->optype->format_id = RX_OP_CODE_FORMAT_EMUL_2X;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_EMUL_2X;
    context->decoded_code->code.rx_emul_2x.mi =
        (((context->code32x1 & OP_SF_MASK_EMUL_2X_MI_0) >> OP_SF_EBII_EMUL_2X_MI_0) << OP_SF_EBIF_EMUL_2X_MI_0);
    context->decoded_code->code.rx_emul_2x.ld =
        (((context->code32x1 & OP_SF_MASK_EMUL_2X_LD_0) >> OP_SF_EBII_EMUL_2X_LD_0) << OP_SF_EBIF_EMUL_2X_LD_0);
    context->decoded_code->code.rx_emul_2x.rs =
        (((context->code32x1 & OP_SF_MASK_EMUL_2X_RS_0) >> OP_SF_EBII_EMUL_2X_RS_0) << OP_SF_EBIF_EMUL_2X_RS_0);
    context->decoded_code->code.rx_emul_2x.rd =
        (((context->code32x1 & OP_SF_MASK_EMUL_2X_RD_0) >> OP_SF_EBII_EMUL_2X_RD_0) << OP_SF_EBIF_EMUL_2X_RD_0);

    return 0;
}

/* emulu_2x */
static int op_parse_emulu_2x(OpDecodeContext *context) {
    if ((context->code32x1 & OP_FB_MASK_EMULU_2X) != OP_FB_EMULU_2X) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_emulu_2x;
    context->optype->format_id = RX_OP_CODE_FORMAT_EMULU_2X;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_EMULU_2X;
    context->decoded_code->code.rx_emulu_2x.mi =
        (((context->code32x1 & OP_SF_MASK_EMULU_2X_MI_0) >> OP_SF_EBII_EMULU_2X_MI_0) << OP_SF_EBIF_EMULU_2X_MI_0);
    context->decoded_code->code.rx_emulu_2x.ld =
        (((context->code32x1 & OP_SF_MASK_EMULU_2X_LD_0) >> OP_SF_EBII_EMULU_2X_LD_0) << OP_SF_EBIF_EMULU_2X_LD_0);
    context->decoded_code->code.rx_emulu_2x.rs =
        (((context->code32x1 & OP_SF_MASK_EMULU_2X_RS_0) >> OP_SF_EBII_EMULU_2X_RS_0) << OP_SF_EBIF_EMULU_2X_RS_0);
    context->decoded_code->code.rx_emulu_2x.rd =
        (((context->code32x1 & OP_SF_MASK_EMULU_2X_RD_0) >> OP_SF_EBII_EMULU_2X_RD_0) << OP_SF_EBIF_EMULU_2X_RD_0);

    return 0;
}

/* itof_1x */
static int op_parse_itof_1x(OpDecodeContext *context) {
    if ((context->code32x1 & OP_FB_MASK_ITOF_1X) != OP_FB_ITOF_1X) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_itof_1x;
    context->optype->format_id = RX_OP_CODE_FORMAT_ITOF_1X;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_ITOF_1X;
    context->decoded_code->code.rx_itof_1x.mi =
        (((context->code32x1 & OP_SF_MASK_ITOF_1X_MI_0) >> OP_SF_EBII_ITOF_1X_MI_0) << OP_SF_EBIF_ITOF_1X_MI_0);
    context->decoded_code->code.rx_itof_1x.ld =
        (((context->code32x1 & OP_SF_MASK_ITOF_1X_LD_0) >> OP_SF_EBII_ITOF_1X_LD_0) << OP_SF_EBIF_ITOF_1X_LD_0);
    context->decoded_code->code.rx_itof_1x.rs =
        (((context->code32x1 & OP_SF_MASK_ITOF_1X_RS_0) >> OP_SF_EBII_ITOF_1X_RS_0) << OP_SF_EBIF_ITOF_1X_RS_0);
    context->decoded_code->code.rx_itof_1x.rd =
        (((context->code32x1 & OP_SF_MASK_ITOF_1X_RD_0) >> OP_SF_EBII_ITOF_1X_RD_0) << OP_SF_EBIF_ITOF_1X_RD_0);

    return 0;
}

/* max_2x */
static int op_parse_max_2x(OpDecodeContext *context) {
    if ((context->code32x1 & OP_FB_MASK_MAX_2X) != OP_FB_MAX_2X) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_max_2x;
    context->optype->format_id = RX_OP_CODE_FORMAT_MAX_2X;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MAX_2X;
    context->decoded_code->code.rx_max_2x.mi =
        (((context->code32x1 & OP_SF_MASK_MAX_2X_MI_0) >> OP_SF_EBII_MAX_2X_MI_0) << OP_SF_EBIF_MAX_2X_MI_0);
    context->decoded_code->code.rx_max_2x.ld =
        (((context->code32x1 & OP_SF_MASK_MAX_2X_LD_0) >> OP_SF_EBII_MAX_2X_LD_0) << OP_SF_EBIF_MAX_2X_LD_0);
    context->decoded_code->code.rx_max_2x.rs =
        (((context->code32x1 & OP_SF_MASK_MAX_2X_RS_0) >> OP_SF_EBII_MAX_2X_RS_0) << OP_SF_EBIF_MAX_2X_RS_0);
    context->decoded_code->code.rx_max_2x.rd =
        (((context->code32x1 & OP_SF_MASK_MAX_2X_RD_0) >> OP_SF_EBII_MAX_2X_RD_0) << OP_SF_EBIF_MAX_2X_RD_0);

    return 0;
}

/* min_2x */
static int op_parse_min_2x(OpDecodeContext *context) {
    if ((context->code32x1 & OP_FB_MASK_MIN_2X) != OP_FB_MIN_2X) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_min_2x;
    context->optype->format_id = RX_OP_CODE_FORMAT_MIN_2X;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MIN_2X;
    context->decoded_code->code.rx_min_2x.mi =
        (((context->code32x1 & OP_SF_MASK_MIN_2X_MI_0) >> OP_SF_EBII_MIN_2X_MI_0) << OP_SF_EBIF_MIN_2X_MI_0);
    context->decoded_code->code.rx_min_2x.ld =
        (((context->code32x1 & OP_SF_MASK_MIN_2X_LD_0) >> OP_SF_EBII_MIN_2X_LD_0) << OP_SF_EBIF_MIN_2X_LD_0);
    context->decoded_code->code.rx_min_2x.rs =
        (((context->code32x1 & OP_SF_MASK_MIN_2X_RS_0) >> OP_SF_EBII_MIN_2X_RS_0) << OP_SF_EBIF_MIN_2X_RS_0);
    context->decoded_code->code.rx_min_2x.rd =
        (((context->code32x1 & OP_SF_MASK_MIN_2X_RD_0) >> OP_SF_EBII_MIN_2X_RD_0) << OP_SF_EBIF_MIN_2X_RD_0);

    return 0;
}

/* tst_2x */
static int op_parse_tst_2x(OpDecodeContext *context) {
    if ((context->code32x1 & OP_FB_MASK_TST_2X) != OP_FB_TST_2X) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_tst_2x;
    context->optype->format_id = RX_OP_CODE_FORMAT_TST_2X;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_TST_2X;
    context->decoded_code->code.rx_tst_2x.mi =
        (((context->code32x1 & OP_SF_MASK_TST_2X_MI_0) >> OP_SF_EBII_TST_2X_MI_0) << OP_SF_EBIF_TST_2X_MI_0);
    context->decoded_code->code.rx_tst_2x.ld =
        (((context->code32x1 & OP_SF_MASK_TST_2X_LD_0) >> OP_SF_EBII_TST_2X_LD_0) << OP_SF_EBIF_TST_2X_LD_0);
    context->decoded_code->code.rx_tst_2x.rs =
        (((context->code32x1 & OP_SF_MASK_TST_2X_RS_0) >> OP_SF_EBII_TST_2X_RS_0) << OP_SF_EBIF_TST_2X_RS_0);
    context->decoded_code->code.rx_tst_2x.rs2 =
        (((context->code32x1 & OP_SF_MASK_TST_2X_RS2_0) >> OP_SF_EBII_TST_2X_RS2_0) << OP_SF_EBIF_TST_2X_RS2_0);

    return 0;
}

/* xchg_1x */
static int op_parse_xchg_1x(OpDecodeContext *context) {
    if ((context->code32x1 & OP_FB_MASK_XCHG_1X) != OP_FB_XCHG_1X) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_xchg_1x;
    context->optype->format_id = RX_OP_CODE_FORMAT_XCHG_1X;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_XCHG_1X;
    context->decoded_code->code.rx_xchg_1x.mi =
        (((context->code32x1 & OP_SF_MASK_XCHG_1X_MI_0) >> OP_SF_EBII_XCHG_1X_MI_0) << OP_SF_EBIF_XCHG_1X_MI_0);
    context->decoded_code->code.rx_xchg_1x.ld =
        (((context->code32x1 & OP_SF_MASK_XCHG_1X_LD_0) >> OP_SF_EBII_XCHG_1X_LD_0) << OP_SF_EBIF_XCHG_1X_LD_0);
    context->decoded_code->code.rx_xchg_1x.rs =
        (((context->code32x1 & OP_SF_MASK_XCHG_1X_RS_0) >> OP_SF_EBII_XCHG_1X_RS_0) << OP_SF_EBIF_XCHG_1X_RS_0);
    context->decoded_code->code.rx_xchg_1x.rd =
        (((context->code32x1 & OP_SF_MASK_XCHG_1X_RD_0) >> OP_SF_EBII_XCHG_1X_RD_0) << OP_SF_EBIF_XCHG_1X_RD_0);

    return 0;
}

/* xor_2x */
static int op_parse_xor_2x(OpDecodeContext *context) {
    if ((context->code32x1 & OP_FB_MASK_XOR_2X) != OP_FB_XOR_2X) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_xor_2x;
    context->optype->format_id = RX_OP_CODE_FORMAT_XOR_2X;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_XOR_2X;
    context->decoded_code->code.rx_xor_2x.mi =
        (((context->code32x1 & OP_SF_MASK_XOR_2X_MI_0) >> OP_SF_EBII_XOR_2X_MI_0) << OP_SF_EBIF_XOR_2X_MI_0);
    context->decoded_code->code.rx_xor_2x.ld =
        (((context->code32x1 & OP_SF_MASK_XOR_2X_LD_0) >> OP_SF_EBII_XOR_2X_LD_0) << OP_SF_EBIF_XOR_2X_LD_0);
    context->decoded_code->code.rx_xor_2x.rs =
        (((context->code32x1 & OP_SF_MASK_XOR_2X_RS_0) >> OP_SF_EBII_XOR_2X_RS_0) << OP_SF_EBIF_XOR_2X_RS_0);
    context->decoded_code->code.rx_xor_2x.rd =
        (((context->code32x1 & OP_SF_MASK_XOR_2X_RD_0) >> OP_SF_EBII_XOR_2X_RD_0) << OP_SF_EBIF_XOR_2X_RD_0);

    return 0;
}

/* bra_s */
static int op_parse_bra_s(OpDecodeContext *context) {
    if ((context->code8x1 & OP_FB_MASK_BRA_S) != OP_FB_BRA_S) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_bra_s;
    context->optype->format_id = RX_OP_CODE_FORMAT_BRA_S;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BRA_S;
    context->decoded_code->code.rx_bra_s.dsp =
        (((context->code8x1 & OP_SF_MASK_BRA_S_DSP_0) >> OP_SF_EBII_BRA_S_DSP_0) << OP_SF_EBIF_BRA_S_DSP_0);

    return 0;
}

/* bcnd_s */
static int op_parse_bcnd_s(OpDecodeContext *context) {
    if ((context->code8x1 & OP_FB_MASK_BCND_S) != OP_FB_BCND_S) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_bcnd_s;
    context->optype->format_id = RX_OP_CODE_FORMAT_BCND_S;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BCND_S;
    context->decoded_code->code.rx_bcnd_s.cd =
        (((context->code8x1 & OP_SF_MASK_BCND_S_CD_0) >> OP_SF_EBII_BCND_S_CD_0) << OP_SF_EBIF_BCND_S_CD_0);
    context->decoded_code->code.rx_bcnd_s.dsp =
        (((context->code8x1 & OP_SF_MASK_BCND_S_DSP_0) >> OP_SF_EBII_BCND_S_DSP_0) << OP_SF_EBIF_BCND_S_DSP_0);

    return 0;
}

/* bra_b */
static int op_parse_bra_b(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_BRA_B) != OP_FB_BRA_B) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_bra_b;
    context->optype->format_id = RX_OP_CODE_FORMAT_BRA_B;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BRA_B;
    context->decoded_code->code.rx_bra_b.pcdsp =
        (((context->code16x1 & OP_SF_MASK_BRA_B_PCDSP_0) >> OP_SF_EBII_BRA_B_PCDSP_0) << OP_SF_EBIF_BRA_B_PCDSP_0);

    return 0;
}

/* bcnd_b */
static int op_parse_bcnd_b(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_BCND_B) != OP_FB_BCND_B) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_bcnd_b;
    context->optype->format_id = RX_OP_CODE_FORMAT_BCND_B;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BCND_B;
    context->decoded_code->code.rx_bcnd_b.cd =
        (((context->code16x1 & OP_SF_MASK_BCND_B_CD_0) >> OP_SF_EBII_BCND_B_CD_0) << OP_SF_EBIF_BCND_B_CD_0);
    context->decoded_code->code.rx_bcnd_b.pcdsp =
        (((context->code16x1 & OP_SF_MASK_BCND_B_PCDSP_0) >> OP_SF_EBII_BCND_B_PCDSP_0) << OP_SF_EBIF_BCND_B_PCDSP_0);

    return 0;
}

/* bra_w */
static int op_parse_bra_w(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_BRA_W) != OP_FB_BRA_W) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_bra_w;
    context->optype->format_id = RX_OP_CODE_FORMAT_BRA_W;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BRA_W;
    context->decoded_code->code.rx_bra_w.pcdsp =
        (((context->code24x1 & OP_SF_MASK_BRA_W_PCDSP_0) >> OP_SF_EBII_BRA_W_PCDSP_0) << OP_SF_EBIF_BRA_W_PCDSP_0);

    return 0;
}

/* bsr_w */
static int op_parse_bsr_w(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_BSR_W) != OP_FB_BSR_W) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_bsr_w;
    context->optype->format_id = RX_OP_CODE_FORMAT_BSR_W;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BSR_W;
    context->decoded_code->code.rx_bsr_w.pcdsp =
        (((context->code24x1 & OP_SF_MASK_BSR_W_PCDSP_0) >> OP_SF_EBII_BSR_W_PCDSP_0) << OP_SF_EBIF_BSR_W_PCDSP_0);

    return 0;
}

/* bcnd_w */
static int op_parse_bcnd_w(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_BCND_W) != OP_FB_BCND_W) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_bcnd_w;
    context->optype->format_id = RX_OP_CODE_FORMAT_BCND_W;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BCND_W;
    context->decoded_code->code.rx_bcnd_w.cd =
        (((context->code24x1 & OP_SF_MASK_BCND_W_CD_0) >> OP_SF_EBII_BCND_W_CD_0) << OP_SF_EBIF_BCND_W_CD_0);
    context->decoded_code->code.rx_bcnd_w.pcdsp =
        (((context->code24x1 & OP_SF_MASK_BCND_W_PCDSP_0) >> OP_SF_EBII_BCND_W_PCDSP_0) << OP_SF_EBIF_BCND_W_PCDSP_0);

    return 0;
}

/* rtsd_2 */
static int op_parse_rtsd_2(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_RTSD_2) != OP_FB_RTSD_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_rtsd_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_RTSD_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_RTSD_2;
    context->decoded_code->code.rx_rtsd_2.rd =
        (((context->code16x1 & OP_SF_MASK_RTSD_2_RD_0) >> OP_SF_EBII_RTSD_2_RD_0) << OP_SF_EBIF_RTSD_2_RD_0);
    context->decoded_code->code.rx_rtsd_2.rd2 =
        (((context->code16x1 & OP_SF_MASK_RTSD_2_RD2_0) >> OP_SF_EBII_RTSD_2_RD2_0) << OP_SF_EBIF_RTSD_2_RD2_0);

    return 0;
}

/* mov_4 */
static int op_parse_mov_4(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_MOV_4) != OP_FB_MOV_4) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mov_4;
    context->optype->format_id = RX_OP_CODE_FORMAT_MOV_4;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MOV_4;
    context->decoded_code->code.rx_mov_4.sz =
        (((context->code16x1 & OP_SF_MASK_MOV_4_SZ_0) >> OP_SF_EBII_MOV_4_SZ_0) << OP_SF_EBIF_MOV_4_SZ_0);
    context->decoded_code->code.rx_mov_4.dsp =
        (((context->code16x1 & OP_SF_MASK_MOV_4_DSP_0) >> OP_SF_EBII_MOV_4_DSP_0) << OP_SF_EBIF_MOV_4_DSP_0)
        | (((context->code16x1 & OP_SF_MASK_MOV_4_DSP_1) >> OP_SF_EBII_MOV_4_DSP_1) << OP_SF_EBIF_MOV_4_DSP_1);
    context->decoded_code->code.rx_mov_4.rd =
        (((context->code16x1 & OP_SF_MASK_MOV_4_RD_0) >> OP_SF_EBII_MOV_4_RD_0) << OP_SF_EBIF_MOV_4_RD_0);

    return 0;
}

/* sub_2 */
static int op_parse_sub_2(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_SUB_2) != OP_FB_SUB_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_sub_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_SUB_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SUB_2;
    context->decoded_code->code.rx_sub_2.ld =
        (((context->code16x1 & OP_SF_MASK_SUB_2_LD_0) >> OP_SF_EBII_SUB_2_LD_0) << OP_SF_EBIF_SUB_2_LD_0);
    context->decoded_code->code.rx_sub_2.rs =
        (((context->code16x1 & OP_SF_MASK_SUB_2_RS_0) >> OP_SF_EBII_SUB_2_RS_0) << OP_SF_EBIF_SUB_2_RS_0);
    context->decoded_code->code.rx_sub_2.rd =
        (((context->code16x1 & OP_SF_MASK_SUB_2_RD_0) >> OP_SF_EBII_SUB_2_RD_0) << OP_SF_EBIF_SUB_2_RD_0);

    return 0;
}

/* cmp_4 */
static int op_parse_cmp_4(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_CMP_4) != OP_FB_CMP_4) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_cmp_4;
    context->optype->format_id = RX_OP_CODE_FORMAT_CMP_4;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_CMP_4;
    context->decoded_code->code.rx_cmp_4.ld =
        (((context->code16x1 & OP_SF_MASK_CMP_4_LD_0) >> OP_SF_EBII_CMP_4_LD_0) << OP_SF_EBIF_CMP_4_LD_0);
    context->decoded_code->code.rx_cmp_4.rs =
        (((context->code16x1 & OP_SF_MASK_CMP_4_RS_0) >> OP_SF_EBII_CMP_4_RS_0) << OP_SF_EBIF_CMP_4_RS_0);
    context->decoded_code->code.rx_cmp_4.rs2 =
        (((context->code16x1 & OP_SF_MASK_CMP_4_RS2_0) >> OP_SF_EBII_CMP_4_RS2_0) << OP_SF_EBIF_CMP_4_RS2_0);

    return 0;
}

/* add_2 */
static int op_parse_add_2(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_ADD_2) != OP_FB_ADD_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_add_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_ADD_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_ADD_2;
    context->decoded_code->code.rx_add_2.ld =
        (((context->code16x1 & OP_SF_MASK_ADD_2_LD_0) >> OP_SF_EBII_ADD_2_LD_0) << OP_SF_EBIF_ADD_2_LD_0);
    context->decoded_code->code.rx_add_2.rs =
        (((context->code16x1 & OP_SF_MASK_ADD_2_RS_0) >> OP_SF_EBII_ADD_2_RS_0) << OP_SF_EBIF_ADD_2_RS_0);
    context->decoded_code->code.rx_add_2.rd =
        (((context->code16x1 & OP_SF_MASK_ADD_2_RD_0) >> OP_SF_EBII_ADD_2_RD_0) << OP_SF_EBIF_ADD_2_RD_0);

    return 0;
}

/* mul_3 */
static int op_parse_mul_3(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_MUL_3) != OP_FB_MUL_3) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mul_3;
    context->optype->format_id = RX_OP_CODE_FORMAT_MUL_3;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MUL_3;
    context->decoded_code->code.rx_mul_3.ld =
        (((context->code16x1 & OP_SF_MASK_MUL_3_LD_0) >> OP_SF_EBII_MUL_3_LD_0) << OP_SF_EBIF_MUL_3_LD_0);
    context->decoded_code->code.rx_mul_3.rs =
        (((context->code16x1 & OP_SF_MASK_MUL_3_RS_0) >> OP_SF_EBII_MUL_3_RS_0) << OP_SF_EBIF_MUL_3_RS_0);
    context->decoded_code->code.rx_mul_3.rd =
        (((context->code16x1 & OP_SF_MASK_MUL_3_RD_0) >> OP_SF_EBII_MUL_3_RD_0) << OP_SF_EBIF_MUL_3_RD_0);

    return 0;
}

/* and_3 */
static int op_parse_and_3(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_AND_3) != OP_FB_AND_3) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_and_3;
    context->optype->format_id = RX_OP_CODE_FORMAT_AND_3;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_AND_3;
    context->decoded_code->code.rx_and_3.ld =
        (((context->code16x1 & OP_SF_MASK_AND_3_LD_0) >> OP_SF_EBII_AND_3_LD_0) << OP_SF_EBIF_AND_3_LD_0);
    context->decoded_code->code.rx_and_3.rs =
        (((context->code16x1 & OP_SF_MASK_AND_3_RS_0) >> OP_SF_EBII_AND_3_RS_0) << OP_SF_EBIF_AND_3_RS_0);
    context->decoded_code->code.rx_and_3.rd =
        (((context->code16x1 & OP_SF_MASK_AND_3_RD_0) >> OP_SF_EBII_AND_3_RD_0) << OP_SF_EBIF_AND_3_RD_0);

    return 0;
}

/* or_3 */
static int op_parse_or_3(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_OR_3) != OP_FB_OR_3) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_or_3;
    context->optype->format_id = RX_OP_CODE_FORMAT_OR_3;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_OR_3;
    context->decoded_code->code.rx_or_3.ld =
        (((context->code16x1 & OP_SF_MASK_OR_3_LD_0) >> OP_SF_EBII_OR_3_LD_0) << OP_SF_EBIF_OR_3_LD_0);
    context->decoded_code->code.rx_or_3.rs =
        (((context->code16x1 & OP_SF_MASK_OR_3_RS_0) >> OP_SF_EBII_OR_3_RS_0) << OP_SF_EBIF_OR_3_RS_0);
    context->decoded_code->code.rx_or_3.rd =
        (((context->code16x1 & OP_SF_MASK_OR_3_RD_0) >> OP_SF_EBII_OR_3_RD_0) << OP_SF_EBIF_OR_3_RD_0);

    return 0;
}

/* movu_2 */
static int op_parse_movu_2(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_MOVU_2) != OP_FB_MOVU_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_movu_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_MOVU_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MOVU_2;
    context->decoded_code->code.rx_movu_2.sz =
        (((context->code16x1 & OP_SF_MASK_MOVU_2_SZ_0) >> OP_SF_EBII_MOVU_2_SZ_0) << OP_SF_EBIF_MOVU_2_SZ_0);
    context->decoded_code->code.rx_movu_2.ld =
        (((context->code16x1 & OP_SF_MASK_MOVU_2_LD_0) >> OP_SF_EBII_MOVU_2_LD_0) << OP_SF_EBIF_MOVU_2_LD_0);
    context->decoded_code->code.rx_movu_2.rs =
        (((context->code16x1 & OP_SF_MASK_MOVU_2_RS_0) >> OP_SF_EBII_MOVU_2_RS_0) << OP_SF_EBIF_MOVU_2_RS_0);
    context->decoded_code->code.rx_movu_2.rd =
        (((context->code16x1 & OP_SF_MASK_MOVU_2_RD_0) >> OP_SF_EBII_MOVU_2_RD_0) << OP_SF_EBIF_MOVU_2_RD_0);

    return 0;
}

/* sub_1 */
static int op_parse_sub_1(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_SUB_1) != OP_FB_SUB_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_sub_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_SUB_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SUB_1;
    context->decoded_code->code.rx_sub_1.imm =
        (((context->code16x1 & OP_SF_MASK_SUB_1_IMM_0) >> OP_SF_EBII_SUB_1_IMM_0) << OP_SF_EBIF_SUB_1_IMM_0);
    context->decoded_code->code.rx_sub_1.rd =
        (((context->code16x1 & OP_SF_MASK_SUB_1_RD_0) >> OP_SF_EBII_SUB_1_RD_0) << OP_SF_EBIF_SUB_1_RD_0);

    return 0;
}

/* cmp_1 */
static int op_parse_cmp_1(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_CMP_1) != OP_FB_CMP_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_cmp_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_CMP_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_CMP_1;
    context->decoded_code->code.rx_cmp_1.imm =
        (((context->code16x1 & OP_SF_MASK_CMP_1_IMM_0) >> OP_SF_EBII_CMP_1_IMM_0) << OP_SF_EBIF_CMP_1_IMM_0);
    context->decoded_code->code.rx_cmp_1.rs2 =
        (((context->code16x1 & OP_SF_MASK_CMP_1_RS2_0) >> OP_SF_EBII_CMP_1_RS2_0) << OP_SF_EBIF_CMP_1_RS2_0);

    return 0;
}

/* add_1 */
static int op_parse_add_1(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_ADD_1) != OP_FB_ADD_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_add_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_ADD_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_ADD_1;
    context->decoded_code->code.rx_add_1.imm =
        (((context->code16x1 & OP_SF_MASK_ADD_1_IMM_0) >> OP_SF_EBII_ADD_1_IMM_0) << OP_SF_EBIF_ADD_1_IMM_0);
    context->decoded_code->code.rx_add_1.rd =
        (((context->code16x1 & OP_SF_MASK_ADD_1_RD_0) >> OP_SF_EBII_ADD_1_RD_0) << OP_SF_EBIF_ADD_1_RD_0);

    return 0;
}

/* mul_1 */
static int op_parse_mul_1(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_MUL_1) != OP_FB_MUL_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mul_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_MUL_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MUL_1;
    context->decoded_code->code.rx_mul_1.imm =
        (((context->code16x1 & OP_SF_MASK_MUL_1_IMM_0) >> OP_SF_EBII_MUL_1_IMM_0) << OP_SF_EBIF_MUL_1_IMM_0);
    context->decoded_code->code.rx_mul_1.rd =
        (((context->code16x1 & OP_SF_MASK_MUL_1_RD_0) >> OP_SF_EBII_MUL_1_RD_0) << OP_SF_EBIF_MUL_1_RD_0);

    return 0;
}

/* and_1 */
static int op_parse_and_1(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_AND_1) != OP_FB_AND_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_and_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_AND_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_AND_1;
    context->decoded_code->code.rx_and_1.imm =
        (((context->code16x1 & OP_SF_MASK_AND_1_IMM_0) >> OP_SF_EBII_AND_1_IMM_0) << OP_SF_EBIF_AND_1_IMM_0);
    context->decoded_code->code.rx_and_1.rd =
        (((context->code16x1 & OP_SF_MASK_AND_1_RD_0) >> OP_SF_EBII_AND_1_RD_0) << OP_SF_EBIF_AND_1_RD_0);

    return 0;
}

/* or_1 */
static int op_parse_or_1(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_OR_1) != OP_FB_OR_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_or_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_OR_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_OR_1;
    context->decoded_code->code.rx_or_1.imm =
        (((context->code16x1 & OP_SF_MASK_OR_1_IMM_0) >> OP_SF_EBII_OR_1_IMM_0) << OP_SF_EBIF_OR_1_IMM_0);
    context->decoded_code->code.rx_or_1.rd =
        (((context->code16x1 & OP_SF_MASK_OR_1_RD_0) >> OP_SF_EBII_OR_1_RD_0) << OP_SF_EBIF_OR_1_RD_0);

    return 0;
}

/* mov_3 */
static int op_parse_mov_3(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_MOV_3) != OP_FB_MOV_3) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mov_3;
    context->optype->format_id = RX_OP_CODE_FORMAT_MOV_3;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MOV_3;
    context->decoded_code->code.rx_mov_3.imm =
        (((context->code16x1 & OP_SF_MASK_MOV_3_IMM_0) >> OP_SF_EBII_MOV_3_IMM_0) << OP_SF_EBIF_MOV_3_IMM_0);
    context->decoded_code->code.rx_mov_3.rd =
        (((context->code16x1 & OP_SF_MASK_MOV_3_RD_0) >> OP_SF_EBII_MOV_3_RD_0) << OP_SF_EBIF_MOV_3_RD_0);

    return 0;
}

/* rtsd_1 */
static int op_parse_rtsd_1(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_RTSD_1) != OP_FB_RTSD_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_rtsd_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_RTSD_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_RTSD_1;
    context->decoded_code->code.rx_rtsd_1.uimm =
        (((context->code16x1 & OP_SF_MASK_RTSD_1_UIMM_0) >> OP_SF_EBII_RTSD_1_UIMM_0) << OP_SF_EBIF_RTSD_1_UIMM_0);

    return 0;
}

/* shlr_1 */
static int op_parse_shlr_1(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_SHLR_1) != OP_FB_SHLR_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_shlr_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_SHLR_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SHLR_1;
    context->decoded_code->code.rx_shlr_1.imm =
        (((context->code16x1 & OP_SF_MASK_SHLR_1_IMM_0) >> OP_SF_EBII_SHLR_1_IMM_0) << OP_SF_EBIF_SHLR_1_IMM_0);
    context->decoded_code->code.rx_shlr_1.rd =
        (((context->code16x1 & OP_SF_MASK_SHLR_1_RD_0) >> OP_SF_EBII_SHLR_1_RD_0) << OP_SF_EBIF_SHLR_1_RD_0);

    return 0;
}

/* shar_1 */
static int op_parse_shar_1(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_SHAR_1) != OP_FB_SHAR_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_shar_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_SHAR_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SHAR_1;
    context->decoded_code->code.rx_shar_1.imm =
        (((context->code16x1 & OP_SF_MASK_SHAR_1_IMM_0) >> OP_SF_EBII_SHAR_1_IMM_0) << OP_SF_EBIF_SHAR_1_IMM_0);
    context->decoded_code->code.rx_shar_1.rd =
        (((context->code16x1 & OP_SF_MASK_SHAR_1_RD_0) >> OP_SF_EBII_SHAR_1_RD_0) << OP_SF_EBIF_SHAR_1_RD_0);

    return 0;
}

/* shll_1 */
static int op_parse_shll_1(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_SHLL_1) != OP_FB_SHLL_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_shll_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_SHLL_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SHLL_1;
    context->decoded_code->code.rx_shll_1.imm =
        (((context->code16x1 & OP_SF_MASK_SHLL_1_IMM_0) >> OP_SF_EBII_SHLL_1_IMM_0) << OP_SF_EBIF_SHLL_1_IMM_0);
    context->decoded_code->code.rx_shll_1.rd =
        (((context->code16x1 & OP_SF_MASK_SHLL_1_RD_0) >> OP_SF_EBII_SHLL_1_RD_0) << OP_SF_EBIF_SHLL_1_RD_0);

    return 0;
}

/* pushm */
static int op_parse_pushm(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_PUSHM) != OP_FB_PUSHM) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_pushm;
    context->optype->format_id = RX_OP_CODE_FORMAT_PUSHM;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_PUSHM;
    context->decoded_code->code.rx_pushm.rs =
        (((context->code16x1 & OP_SF_MASK_PUSHM_RS_0) >> OP_SF_EBII_PUSHM_RS_0) << OP_SF_EBIF_PUSHM_RS_0);
    context->decoded_code->code.rx_pushm.rs2 =
        (((context->code16x1 & OP_SF_MASK_PUSHM_RS2_0) >> OP_SF_EBII_PUSHM_RS2_0) << OP_SF_EBIF_PUSHM_RS2_0);

    return 0;
}

/* popm */
static int op_parse_popm(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_POPM) != OP_FB_POPM) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_popm;
    context->optype->format_id = RX_OP_CODE_FORMAT_POPM;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_POPM;
    context->decoded_code->code.rx_popm.rd =
        (((context->code16x1 & OP_SF_MASK_POPM_RD_0) >> OP_SF_EBII_POPM_RD_0) << OP_SF_EBIF_POPM_RD_0);
    context->decoded_code->code.rx_popm.rd2 =
        (((context->code16x1 & OP_SF_MASK_POPM_RD2_0) >> OP_SF_EBII_POPM_RD2_0) << OP_SF_EBIF_POPM_RD2_0);

    return 0;
}

/* add_3 */
static int op_parse_add_3(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_ADD_3) != OP_FB_ADD_3) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_add_3;
    context->optype->format_id = RX_OP_CODE_FORMAT_ADD_3;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_ADD_3;
    context->decoded_code->code.rx_add_3.li =
        (((context->code16x1 & OP_SF_MASK_ADD_3_LI_0) >> OP_SF_EBII_ADD_3_LI_0) << OP_SF_EBIF_ADD_3_LI_0);
    context->decoded_code->code.rx_add_3.rs2 =
        (((context->code16x1 & OP_SF_MASK_ADD_3_RS2_0) >> OP_SF_EBII_ADD_3_RS2_0) << OP_SF_EBIF_ADD_3_RS2_0);
    context->decoded_code->code.rx_add_3.rd =
        (((context->code16x1 & OP_SF_MASK_ADD_3_RD_0) >> OP_SF_EBII_ADD_3_RD_0) << OP_SF_EBIF_ADD_3_RD_0);

    return 0;
}

/* cmp_2 */
static int op_parse_cmp_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_CMP_2) != OP_FB_CMP_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_cmp_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_CMP_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_CMP_2;
    context->decoded_code->code.rx_cmp_2.rs2 =
        (((context->code24x1 & OP_SF_MASK_CMP_2_RS2_0) >> OP_SF_EBII_CMP_2_RS2_0) << OP_SF_EBIF_CMP_2_RS2_0);
    context->decoded_code->code.rx_cmp_2.uimm =
        (((context->code24x1 & OP_SF_MASK_CMP_2_UIMM_0) >> OP_SF_EBII_CMP_2_UIMM_0) << OP_SF_EBIF_CMP_2_UIMM_0);

    return 0;
}

/* int */
static int op_parse_int(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_INT) != OP_FB_INT) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_int;
    context->optype->format_id = RX_OP_CODE_FORMAT_INT;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_INT;
    context->decoded_code->code.rx_int.imm =
        (((context->code24x1 & OP_SF_MASK_INT_IMM_0) >> OP_SF_EBII_INT_IMM_0) << OP_SF_EBIF_INT_IMM_0);

    return 0;
}

/* mov_5 */
static int op_parse_mov_5(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MOV_5) != OP_FB_MOV_5) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mov_5;
    context->optype->format_id = RX_OP_CODE_FORMAT_MOV_5;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MOV_5;
    context->decoded_code->code.rx_mov_5.rd =
        (((context->code24x1 & OP_SF_MASK_MOV_5_RD_0) >> OP_SF_EBII_MOV_5_RD_0) << OP_SF_EBIF_MOV_5_RD_0);
    context->decoded_code->code.rx_mov_5.uimm =
        (((context->code24x1 & OP_SF_MASK_MOV_5_UIMM_0) >> OP_SF_EBII_MOV_5_UIMM_0) << OP_SF_EBIF_MOV_5_UIMM_0);

    return 0;
}

/* mvtipl */
static int op_parse_mvtipl(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MVTIPL) != OP_FB_MVTIPL) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mvtipl;
    context->optype->format_id = RX_OP_CODE_FORMAT_MVTIPL;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MVTIPL;
    context->decoded_code->code.rx_mvtipl.imm =
        (((context->code24x1 & OP_SF_MASK_MVTIPL_IMM_0) >> OP_SF_EBII_MVTIPL_IMM_0) << OP_SF_EBIF_MVTIPL_IMM_0);

    return 0;
}

/* and_2 */
static int op_parse_and_2(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_AND_2) != OP_FB_AND_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_and_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_AND_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_AND_2;
    context->decoded_code->code.rx_and_2.li =
        (((context->code16x1 & OP_SF_MASK_AND_2_LI_0) >> OP_SF_EBII_AND_2_LI_0) << OP_SF_EBIF_AND_2_LI_0);
    context->decoded_code->code.rx_and_2.rd =
        (((context->code16x1 & OP_SF_MASK_AND_2_RD_0) >> OP_SF_EBII_AND_2_RD_0) << OP_SF_EBIF_AND_2_RD_0);

    return 0;
}

/* cmp_3 */
static int op_parse_cmp_3(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_CMP_3) != OP_FB_CMP_3) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_cmp_3;
    context->optype->format_id = RX_OP_CODE_FORMAT_CMP_3;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_CMP_3;
    context->decoded_code->code.rx_cmp_3.li =
        (((context->code16x1 & OP_SF_MASK_CMP_3_LI_0) >> OP_SF_EBII_CMP_3_LI_0) << OP_SF_EBIF_CMP_3_LI_0);
    context->decoded_code->code.rx_cmp_3.rs2 =
        (((context->code16x1 & OP_SF_MASK_CMP_3_RS2_0) >> OP_SF_EBII_CMP_3_RS2_0) << OP_SF_EBIF_CMP_3_RS2_0);

    return 0;
}

/* mul_2 */
static int op_parse_mul_2(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_MUL_2) != OP_FB_MUL_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mul_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_MUL_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MUL_2;
    context->decoded_code->code.rx_mul_2.li =
        (((context->code16x1 & OP_SF_MASK_MUL_2_LI_0) >> OP_SF_EBII_MUL_2_LI_0) << OP_SF_EBIF_MUL_2_LI_0);
    context->decoded_code->code.rx_mul_2.rd =
        (((context->code16x1 & OP_SF_MASK_MUL_2_RD_0) >> OP_SF_EBII_MUL_2_RD_0) << OP_SF_EBIF_MUL_2_RD_0);

    return 0;
}

/* or_2 */
static int op_parse_or_2(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_OR_2) != OP_FB_OR_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_or_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_OR_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_OR_2;
    context->decoded_code->code.rx_or_2.li =
        (((context->code16x1 & OP_SF_MASK_OR_2_LI_0) >> OP_SF_EBII_OR_2_LI_0) << OP_SF_EBIF_OR_2_LI_0);
    context->decoded_code->code.rx_or_2.rd =
        (((context->code16x1 & OP_SF_MASK_OR_2_RD_0) >> OP_SF_EBII_OR_2_RD_0) << OP_SF_EBIF_OR_2_RD_0);

    return 0;
}

/* bset_3 */
static int op_parse_bset_3(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_BSET_3) != OP_FB_BSET_3) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_bset_3;
    context->optype->format_id = RX_OP_CODE_FORMAT_BSET_3;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BSET_3;
    context->decoded_code->code.rx_bset_3.imm =
        (((context->code16x1 & OP_SF_MASK_BSET_3_IMM_0) >> OP_SF_EBII_BSET_3_IMM_0) << OP_SF_EBIF_BSET_3_IMM_0);
    context->decoded_code->code.rx_bset_3.rd =
        (((context->code16x1 & OP_SF_MASK_BSET_3_RD_0) >> OP_SF_EBII_BSET_3_RD_0) << OP_SF_EBIF_BSET_3_RD_0);

    return 0;
}

/* bclr_3 */
static int op_parse_bclr_3(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_BCLR_3) != OP_FB_BCLR_3) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_bclr_3;
    context->optype->format_id = RX_OP_CODE_FORMAT_BCLR_3;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BCLR_3;
    context->decoded_code->code.rx_bclr_3.imm =
        (((context->code16x1 & OP_SF_MASK_BCLR_3_IMM_0) >> OP_SF_EBII_BCLR_3_IMM_0) << OP_SF_EBIF_BCLR_3_IMM_0);
    context->decoded_code->code.rx_bclr_3.rd =
        (((context->code16x1 & OP_SF_MASK_BCLR_3_RD_0) >> OP_SF_EBII_BCLR_3_RD_0) << OP_SF_EBIF_BCLR_3_RD_0);

    return 0;
}

/* btst_3 */
static int op_parse_btst_3(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_BTST_3) != OP_FB_BTST_3) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_btst_3;
    context->optype->format_id = RX_OP_CODE_FORMAT_BTST_3;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BTST_3;
    context->decoded_code->code.rx_btst_3.imm =
        (((context->code16x1 & OP_SF_MASK_BTST_3_IMM_0) >> OP_SF_EBII_BTST_3_IMM_0) << OP_SF_EBIF_BTST_3_IMM_0);
    context->decoded_code->code.rx_btst_3.rs2 =
        (((context->code16x1 & OP_SF_MASK_BTST_3_RS2_0) >> OP_SF_EBII_BTST_3_RS2_0) << OP_SF_EBIF_BTST_3_RS2_0);

    return 0;
}

/* abs_1 */
static int op_parse_abs_1(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_ABS_1) != OP_FB_ABS_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_abs_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_ABS_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_ABS_1;
    context->decoded_code->code.rx_abs_1.rd =
        (((context->code16x1 & OP_SF_MASK_ABS_1_RD_0) >> OP_SF_EBII_ABS_1_RD_0) << OP_SF_EBIF_ABS_1_RD_0);

    return 0;
}

/* neg_1 */
static int op_parse_neg_1(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_NEG_1) != OP_FB_NEG_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_neg_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_NEG_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_NEG_1;
    context->decoded_code->code.rx_neg_1.rd =
        (((context->code16x1 & OP_SF_MASK_NEG_1_RD_0) >> OP_SF_EBII_NEG_1_RD_0) << OP_SF_EBIF_NEG_1_RD_0);

    return 0;
}

/* not_1 */
static int op_parse_not_1(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_NOT_1) != OP_FB_NOT_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_not_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_NOT_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_NOT_1;
    context->decoded_code->code.rx_not_1.rd =
        (((context->code16x1 & OP_SF_MASK_NOT_1_RD_0) >> OP_SF_EBII_NOT_1_RD_0) << OP_SF_EBIF_NOT_1_RD_0);

    return 0;
}

/* rolc */
static int op_parse_rolc(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_ROLC) != OP_FB_ROLC) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_rolc;
    context->optype->format_id = RX_OP_CODE_FORMAT_ROLC;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_ROLC;
    context->decoded_code->code.rx_rolc.rd =
        (((context->code16x1 & OP_SF_MASK_ROLC_RD_0) >> OP_SF_EBII_ROLC_RD_0) << OP_SF_EBIF_ROLC_RD_0);

    return 0;
}

/* pop */
static int op_parse_pop(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_POP) != OP_FB_POP) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_pop;
    context->optype->format_id = RX_OP_CODE_FORMAT_POP;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_POP;
    context->decoded_code->code.rx_pop.rd =
        (((context->code16x1 & OP_SF_MASK_POP_RD_0) >> OP_SF_EBII_POP_RD_0) << OP_SF_EBIF_POP_RD_0);

    return 0;
}

/* popc */
static int op_parse_popc(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_POPC) != OP_FB_POPC) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_popc;
    context->optype->format_id = RX_OP_CODE_FORMAT_POPC;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_POPC;
    context->decoded_code->code.rx_popc.cr =
        (((context->code16x1 & OP_SF_MASK_POPC_CR_0) >> OP_SF_EBII_POPC_CR_0) << OP_SF_EBIF_POPC_CR_0);

    return 0;
}

/* rorc */
static int op_parse_rorc(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_RORC) != OP_FB_RORC) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_rorc;
    context->optype->format_id = RX_OP_CODE_FORMAT_RORC;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_RORC;
    context->decoded_code->code.rx_rorc.rd =
        (((context->code16x1 & OP_SF_MASK_RORC_RD_0) >> OP_SF_EBII_RORC_RD_0) << OP_SF_EBIF_RORC_RD_0);

    return 0;
}

/* push_1 */
static int op_parse_push_1(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_PUSH_1) != OP_FB_PUSH_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_push_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_PUSH_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_PUSH_1;
    context->decoded_code->code.rx_push_1.sz =
        (((context->code16x1 & OP_SF_MASK_PUSH_1_SZ_0) >> OP_SF_EBII_PUSH_1_SZ_0) << OP_SF_EBIF_PUSH_1_SZ_0);
    context->decoded_code->code.rx_push_1.rs =
        (((context->code16x1 & OP_SF_MASK_PUSH_1_RS_0) >> OP_SF_EBII_PUSH_1_RS_0) << OP_SF_EBIF_PUSH_1_RS_0);

    return 0;
}

/* pushc */
static int op_parse_pushc(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_PUSHC) != OP_FB_PUSHC) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_pushc;
    context->optype->format_id = RX_OP_CODE_FORMAT_PUSHC;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_PUSHC;
    context->decoded_code->code.rx_pushc.cr =
        (((context->code16x1 & OP_SF_MASK_PUSHC_CR_0) >> OP_SF_EBII_PUSHC_CR_0) << OP_SF_EBIF_PUSHC_CR_0);

    return 0;
}

/* sat */
static int op_parse_sat(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_SAT) != OP_FB_SAT) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_sat;
    context->optype->format_id = RX_OP_CODE_FORMAT_SAT;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SAT;
    context->decoded_code->code.rx_sat.rd =
        (((context->code16x1 & OP_SF_MASK_SAT_RD_0) >> OP_SF_EBII_SAT_RD_0) << OP_SF_EBIF_SAT_RD_0);

    return 0;
}

/* jmp */
static int op_parse_jmp(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_JMP) != OP_FB_JMP) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_jmp;
    context->optype->format_id = RX_OP_CODE_FORMAT_JMP;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_JMP;
    context->decoded_code->code.rx_jmp.rs =
        (((context->code16x1 & OP_SF_MASK_JMP_RS_0) >> OP_SF_EBII_JMP_RS_0) << OP_SF_EBIF_JMP_RS_0);

    return 0;
}

/* jsr */
static int op_parse_jsr(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_JSR) != OP_FB_JSR) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_jsr;
    context->optype->format_id = RX_OP_CODE_FORMAT_JSR;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_JSR;
    context->decoded_code->code.rx_jsr.rs =
        (((context->code16x1 & OP_SF_MASK_JSR_RS_0) >> OP_SF_EBII_JSR_RS_0) << OP_SF_EBIF_JSR_RS_0);

    return 0;
}

/* bra_l */
static int op_parse_bra_l(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_BRA_L) != OP_FB_BRA_L) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_bra_l;
    context->optype->format_id = RX_OP_CODE_FORMAT_BRA_L;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BRA_L;
    context->decoded_code->code.rx_bra_l.rs =
        (((context->code16x1 & OP_SF_MASK_BRA_L_RS_0) >> OP_SF_EBII_BRA_L_RS_0) << OP_SF_EBIF_BRA_L_RS_0);

    return 0;
}

/* bsr_l */
static int op_parse_bsr_l(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_BSR_L) != OP_FB_BSR_L) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_bsr_l;
    context->optype->format_id = RX_OP_CODE_FORMAT_BSR_L;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BSR_L;
    context->decoded_code->code.rx_bsr_l.rs =
        (((context->code16x1 & OP_SF_MASK_BSR_L_RS_0) >> OP_SF_EBII_BSR_L_RS_0) << OP_SF_EBIF_BSR_L_RS_0);

    return 0;
}

/* scmpu */
static int op_parse_scmpu(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_SCMPU) != OP_FB_SCMPU) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_scmpu;
    context->optype->format_id = RX_OP_CODE_FORMAT_SCMPU;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SCMPU;

    return 0;
}

/* suntil_b */
static int op_parse_suntil_b(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_SUNTIL_B) != OP_FB_SUNTIL_B) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_suntil_b;
    context->optype->format_id = RX_OP_CODE_FORMAT_SUNTIL_B;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SUNTIL_B;

    return 0;
}

/* suntil_w */
static int op_parse_suntil_w(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_SUNTIL_W) != OP_FB_SUNTIL_W) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_suntil_w;
    context->optype->format_id = RX_OP_CODE_FORMAT_SUNTIL_W;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SUNTIL_W;

    return 0;
}

/* suntil_l */
static int op_parse_suntil_l(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_SUNTIL_L) != OP_FB_SUNTIL_L) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_suntil_l;
    context->optype->format_id = RX_OP_CODE_FORMAT_SUNTIL_L;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SUNTIL_L;

    return 0;
}

/* smovu */
static int op_parse_smovu(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_SMOVU) != OP_FB_SMOVU) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_smovu;
    context->optype->format_id = RX_OP_CODE_FORMAT_SMOVU;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SMOVU;

    return 0;
}

/* swhile_b */
static int op_parse_swhile_b(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_SWHILE_B) != OP_FB_SWHILE_B) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_swhile_b;
    context->optype->format_id = RX_OP_CODE_FORMAT_SWHILE_B;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SWHILE_B;

    return 0;
}

/* swhile_w */
static int op_parse_swhile_w(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_SWHILE_W) != OP_FB_SWHILE_W) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_swhile_w;
    context->optype->format_id = RX_OP_CODE_FORMAT_SWHILE_W;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SWHILE_W;

    return 0;
}

/* swhile_l */
static int op_parse_swhile_l(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_SWHILE_L) != OP_FB_SWHILE_L) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_swhile_l;
    context->optype->format_id = RX_OP_CODE_FORMAT_SWHILE_L;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SWHILE_L;

    return 0;
}

/* smovb */
static int op_parse_smovb(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_SMOVB) != OP_FB_SMOVB) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_smovb;
    context->optype->format_id = RX_OP_CODE_FORMAT_SMOVB;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SMOVB;

    return 0;
}

/* sstr_b */
static int op_parse_sstr_b(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_SSTR_B) != OP_FB_SSTR_B) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_sstr_b;
    context->optype->format_id = RX_OP_CODE_FORMAT_SSTR_B;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SSTR_B;

    return 0;
}

/* sstr_w */
static int op_parse_sstr_w(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_SSTR_W) != OP_FB_SSTR_W) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_sstr_w;
    context->optype->format_id = RX_OP_CODE_FORMAT_SSTR_W;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SSTR_W;

    return 0;
}

/* sstr_l */
static int op_parse_sstr_l(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_SSTR_L) != OP_FB_SSTR_L) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_sstr_l;
    context->optype->format_id = RX_OP_CODE_FORMAT_SSTR_L;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SSTR_L;

    return 0;
}

/* smovf */
static int op_parse_smovf(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_SMOVF) != OP_FB_SMOVF) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_smovf;
    context->optype->format_id = RX_OP_CODE_FORMAT_SMOVF;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SMOVF;

    return 0;
}

/* rmpa */
static int op_parse_rmpa(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_RMPA) != OP_FB_RMPA) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_rmpa;
    context->optype->format_id = RX_OP_CODE_FORMAT_RMPA;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_RMPA;
    context->decoded_code->code.rx_rmpa.sz =
        (((context->code16x1 & OP_SF_MASK_RMPA_SZ_0) >> OP_SF_EBII_RMPA_SZ_0) << OP_SF_EBIF_RMPA_SZ_0);

    return 0;
}

/* satr */
static int op_parse_satr(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_SATR) != OP_FB_SATR) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_satr;
    context->optype->format_id = RX_OP_CODE_FORMAT_SATR;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SATR;

    return 0;
}

/* rtfi */
static int op_parse_rtfi(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_RTFI) != OP_FB_RTFI) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_rtfi;
    context->optype->format_id = RX_OP_CODE_FORMAT_RTFI;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_RTFI;

    return 0;
}

/* rte */
static int op_parse_rte(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_RTE) != OP_FB_RTE) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_rte;
    context->optype->format_id = RX_OP_CODE_FORMAT_RTE;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_RTE;

    return 0;
}

/* wait */
static int op_parse_wait(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_WAIT) != OP_FB_WAIT) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_wait;
    context->optype->format_id = RX_OP_CODE_FORMAT_WAIT;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_WAIT;

    return 0;
}

/* setpsw */
static int op_parse_setpsw(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_SETPSW) != OP_FB_SETPSW) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_setpsw;
    context->optype->format_id = RX_OP_CODE_FORMAT_SETPSW;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SETPSW;
    context->decoded_code->code.rx_setpsw.cb =
        (((context->code16x1 & OP_SF_MASK_SETPSW_CB_0) >> OP_SF_EBII_SETPSW_CB_0) << OP_SF_EBIF_SETPSW_CB_0);

    return 0;
}

/* clrpsw */
static int op_parse_clrpsw(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_CLRPSW) != OP_FB_CLRPSW) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_clrpsw;
    context->optype->format_id = RX_OP_CODE_FORMAT_CLRPSW;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_CLRPSW;
    context->decoded_code->code.rx_clrpsw.cb =
        (((context->code16x1 & OP_SF_MASK_CLRPSW_CB_0) >> OP_SF_EBII_CLRPSW_CB_0) << OP_SF_EBIF_CLRPSW_CB_0);

    return 0;
}

/* movu_1 */
static int op_parse_movu_1(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_MOVU_1) != OP_FB_MOVU_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_movu_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_MOVU_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MOVU_1;
    context->decoded_code->code.rx_movu_1.sz =
        (((context->code16x1 & OP_SF_MASK_MOVU_1_SZ_0) >> OP_SF_EBII_MOVU_1_SZ_0) << OP_SF_EBIF_MOVU_1_SZ_0);
    context->decoded_code->code.rx_movu_1.dsp =
        (((context->code16x1 & OP_SF_MASK_MOVU_1_DSP_0) >> OP_SF_EBII_MOVU_1_DSP_0) << OP_SF_EBIF_MOVU_1_DSP_0)
        | (((context->code16x1 & OP_SF_MASK_MOVU_1_DSP_1) >> OP_SF_EBII_MOVU_1_DSP_1) << OP_SF_EBIF_MOVU_1_DSP_1);
    context->decoded_code->code.rx_movu_1.rs =
        (((context->code16x1 & OP_SF_MASK_MOVU_1_RS_0) >> OP_SF_EBII_MOVU_1_RS_0) << OP_SF_EBIF_MOVU_1_RS_0);
    context->decoded_code->code.rx_movu_1.rd =
        (((context->code16x1 & OP_SF_MASK_MOVU_1_RD_0) >> OP_SF_EBII_MOVU_1_RD_0) << OP_SF_EBIF_MOVU_1_RD_0);

    return 0;
}

/* mov_1 */
static int op_parse_mov_1(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_MOV_1) != OP_FB_MOV_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mov_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_MOV_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MOV_1;
    context->decoded_code->code.rx_mov_1.sz =
        (((context->code16x1 & OP_SF_MASK_MOV_1_SZ_0) >> OP_SF_EBII_MOV_1_SZ_0) << OP_SF_EBIF_MOV_1_SZ_0);
    context->decoded_code->code.rx_mov_1.dsp =
        (((context->code16x1 & OP_SF_MASK_MOV_1_DSP_0) >> OP_SF_EBII_MOV_1_DSP_0) << OP_SF_EBIF_MOV_1_DSP_0)
        | (((context->code16x1 & OP_SF_MASK_MOV_1_DSP_1) >> OP_SF_EBII_MOV_1_DSP_1) << OP_SF_EBIF_MOV_1_DSP_1);
    context->decoded_code->code.rx_mov_1.rd =
        (((context->code16x1 & OP_SF_MASK_MOV_1_RD_0) >> OP_SF_EBII_MOV_1_RD_0) << OP_SF_EBIF_MOV_1_RD_0);
    context->decoded_code->code.rx_mov_1.rs =
        (((context->code16x1 & OP_SF_MASK_MOV_1_RS_0) >> OP_SF_EBII_MOV_1_RS_0) << OP_SF_EBIF_MOV_1_RS_0);

    return 0;
}

/* mov_2 */
static int op_parse_mov_2(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_MOV_2) != OP_FB_MOV_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mov_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_MOV_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MOV_2;
    context->decoded_code->code.rx_mov_2.sz =
        (((context->code16x1 & OP_SF_MASK_MOV_2_SZ_0) >> OP_SF_EBII_MOV_2_SZ_0) << OP_SF_EBIF_MOV_2_SZ_0);
    context->decoded_code->code.rx_mov_2.dsp =
        (((context->code16x1 & OP_SF_MASK_MOV_2_DSP_0) >> OP_SF_EBII_MOV_2_DSP_0) << OP_SF_EBIF_MOV_2_DSP_0)
        | (((context->code16x1 & OP_SF_MASK_MOV_2_DSP_1) >> OP_SF_EBII_MOV_2_DSP_1) << OP_SF_EBIF_MOV_2_DSP_1);
    context->decoded_code->code.rx_mov_2.rs =
        (((context->code16x1 & OP_SF_MASK_MOV_2_RS_0) >> OP_SF_EBII_MOV_2_RS_0) << OP_SF_EBIF_MOV_2_RS_0);
    context->decoded_code->code.rx_mov_2.rd =
        (((context->code16x1 & OP_SF_MASK_MOV_2_RD_0) >> OP_SF_EBII_MOV_2_RD_0) << OP_SF_EBIF_MOV_2_RD_0);

    return 0;
}

/* sbb_1 */
static int op_parse_sbb_1(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_SBB_1) != OP_FB_SBB_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_sbb_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_SBB_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SBB_1;
    context->decoded_code->code.rx_sbb_1.ld =
        (((context->code24x1 & OP_SF_MASK_SBB_1_LD_0) >> OP_SF_EBII_SBB_1_LD_0) << OP_SF_EBIF_SBB_1_LD_0);
    context->decoded_code->code.rx_sbb_1.rs =
        (((context->code24x1 & OP_SF_MASK_SBB_1_RS_0) >> OP_SF_EBII_SBB_1_RS_0) << OP_SF_EBIF_SBB_1_RS_0);
    context->decoded_code->code.rx_sbb_1.rd =
        (((context->code24x1 & OP_SF_MASK_SBB_1_RD_0) >> OP_SF_EBII_SBB_1_RD_0) << OP_SF_EBIF_SBB_1_RD_0);

    return 0;
}

/* neg_2 */
static int op_parse_neg_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_NEG_2) != OP_FB_NEG_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_neg_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_NEG_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_NEG_2;
    context->decoded_code->code.rx_neg_2.rs =
        (((context->code24x1 & OP_SF_MASK_NEG_2_RS_0) >> OP_SF_EBII_NEG_2_RS_0) << OP_SF_EBIF_NEG_2_RS_0);
    context->decoded_code->code.rx_neg_2.rd =
        (((context->code24x1 & OP_SF_MASK_NEG_2_RD_0) >> OP_SF_EBII_NEG_2_RD_0) << OP_SF_EBIF_NEG_2_RD_0);

    return 0;
}

/* adc_2 */
static int op_parse_adc_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_ADC_2) != OP_FB_ADC_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_adc_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_ADC_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_ADC_2;
    context->decoded_code->code.rx_adc_2.ld =
        (((context->code24x1 & OP_SF_MASK_ADC_2_LD_0) >> OP_SF_EBII_ADC_2_LD_0) << OP_SF_EBIF_ADC_2_LD_0);
    context->decoded_code->code.rx_adc_2.rs =
        (((context->code24x1 & OP_SF_MASK_ADC_2_RS_0) >> OP_SF_EBII_ADC_2_RS_0) << OP_SF_EBIF_ADC_2_RS_0);
    context->decoded_code->code.rx_adc_2.rd =
        (((context->code24x1 & OP_SF_MASK_ADC_2_RD_0) >> OP_SF_EBII_ADC_2_RD_0) << OP_SF_EBIF_ADC_2_RD_0);

    return 0;
}

/* abs_2 */
static int op_parse_abs_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_ABS_2) != OP_FB_ABS_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_abs_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_ABS_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_ABS_2;
    context->decoded_code->code.rx_abs_2.rs =
        (((context->code24x1 & OP_SF_MASK_ABS_2_RS_0) >> OP_SF_EBII_ABS_2_RS_0) << OP_SF_EBIF_ABS_2_RS_0);
    context->decoded_code->code.rx_abs_2.rd =
        (((context->code24x1 & OP_SF_MASK_ABS_2_RD_0) >> OP_SF_EBII_ABS_2_RD_0) << OP_SF_EBIF_ABS_2_RD_0);

    return 0;
}

/* not_2 */
static int op_parse_not_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_NOT_2) != OP_FB_NOT_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_not_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_NOT_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_NOT_2;
    context->decoded_code->code.rx_not_2.rs =
        (((context->code24x1 & OP_SF_MASK_NOT_2_RS_0) >> OP_SF_EBII_NOT_2_RS_0) << OP_SF_EBIF_NOT_2_RS_0);
    context->decoded_code->code.rx_not_2.rd =
        (((context->code24x1 & OP_SF_MASK_NOT_2_RD_0) >> OP_SF_EBII_NOT_2_RD_0) << OP_SF_EBIF_NOT_2_RD_0);

    return 0;
}

/* bset_4 */
static int op_parse_bset_4(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_BSET_4) != OP_FB_BSET_4) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_bset_4;
    context->optype->format_id = RX_OP_CODE_FORMAT_BSET_4;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BSET_4;
    context->decoded_code->code.rx_bset_4.ld =
        (((context->code24x1 & OP_SF_MASK_BSET_4_LD_0) >> OP_SF_EBII_BSET_4_LD_0) << OP_SF_EBIF_BSET_4_LD_0);
    context->decoded_code->code.rx_bset_4.rd =
        (((context->code24x1 & OP_SF_MASK_BSET_4_RD_0) >> OP_SF_EBII_BSET_4_RD_0) << OP_SF_EBIF_BSET_4_RD_0);
    context->decoded_code->code.rx_bset_4.rs =
        (((context->code24x1 & OP_SF_MASK_BSET_4_RS_0) >> OP_SF_EBII_BSET_4_RS_0) << OP_SF_EBIF_BSET_4_RS_0);

    return 0;
}

/* bclr_4 */
static int op_parse_bclr_4(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_BCLR_4) != OP_FB_BCLR_4) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_bclr_4;
    context->optype->format_id = RX_OP_CODE_FORMAT_BCLR_4;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BCLR_4;
    context->decoded_code->code.rx_bclr_4.ld =
        (((context->code24x1 & OP_SF_MASK_BCLR_4_LD_0) >> OP_SF_EBII_BCLR_4_LD_0) << OP_SF_EBIF_BCLR_4_LD_0);
    context->decoded_code->code.rx_bclr_4.rd =
        (((context->code24x1 & OP_SF_MASK_BCLR_4_RD_0) >> OP_SF_EBII_BCLR_4_RD_0) << OP_SF_EBIF_BCLR_4_RD_0);
    context->decoded_code->code.rx_bclr_4.rs =
        (((context->code24x1 & OP_SF_MASK_BCLR_4_RS_0) >> OP_SF_EBII_BCLR_4_RS_0) << OP_SF_EBIF_BCLR_4_RS_0);

    return 0;
}

/* btst_4 */
static int op_parse_btst_4(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_BTST_4) != OP_FB_BTST_4) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_btst_4;
    context->optype->format_id = RX_OP_CODE_FORMAT_BTST_4;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BTST_4;
    context->decoded_code->code.rx_btst_4.ld =
        (((context->code24x1 & OP_SF_MASK_BTST_4_LD_0) >> OP_SF_EBII_BTST_4_LD_0) << OP_SF_EBIF_BTST_4_LD_0);
    context->decoded_code->code.rx_btst_4.rs2 =
        (((context->code24x1 & OP_SF_MASK_BTST_4_RS2_0) >> OP_SF_EBII_BTST_4_RS2_0) << OP_SF_EBIF_BTST_4_RS2_0);
    context->decoded_code->code.rx_btst_4.rs =
        (((context->code24x1 & OP_SF_MASK_BTST_4_RS_0) >> OP_SF_EBII_BTST_4_RS_0) << OP_SF_EBIF_BTST_4_RS_0);

    return 0;
}

/* bnot_4 */
static int op_parse_bnot_4(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_BNOT_4) != OP_FB_BNOT_4) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_bnot_4;
    context->optype->format_id = RX_OP_CODE_FORMAT_BNOT_4;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BNOT_4;
    context->decoded_code->code.rx_bnot_4.ld =
        (((context->code24x1 & OP_SF_MASK_BNOT_4_LD_0) >> OP_SF_EBII_BNOT_4_LD_0) << OP_SF_EBIF_BNOT_4_LD_0);
    context->decoded_code->code.rx_bnot_4.rd =
        (((context->code24x1 & OP_SF_MASK_BNOT_4_RD_0) >> OP_SF_EBII_BNOT_4_RD_0) << OP_SF_EBIF_BNOT_4_RD_0);
    context->decoded_code->code.rx_bnot_4.rs =
        (((context->code24x1 & OP_SF_MASK_BNOT_4_RS_0) >> OP_SF_EBII_BNOT_4_RS_0) << OP_SF_EBIF_BNOT_4_RS_0);

    return 0;
}

/* max_2 */
static int op_parse_max_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MAX_2) != OP_FB_MAX_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_max_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_MAX_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MAX_2;
    context->decoded_code->code.rx_max_2.ld =
        (((context->code24x1 & OP_SF_MASK_MAX_2_LD_0) >> OP_SF_EBII_MAX_2_LD_0) << OP_SF_EBIF_MAX_2_LD_0);
    context->decoded_code->code.rx_max_2.rs =
        (((context->code24x1 & OP_SF_MASK_MAX_2_RS_0) >> OP_SF_EBII_MAX_2_RS_0) << OP_SF_EBIF_MAX_2_RS_0);
    context->decoded_code->code.rx_max_2.rd =
        (((context->code24x1 & OP_SF_MASK_MAX_2_RD_0) >> OP_SF_EBII_MAX_2_RD_0) << OP_SF_EBIF_MAX_2_RD_0);

    return 0;
}

/* min_2 */
static int op_parse_min_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MIN_2) != OP_FB_MIN_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_min_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_MIN_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MIN_2;
    context->decoded_code->code.rx_min_2.ld =
        (((context->code24x1 & OP_SF_MASK_MIN_2_LD_0) >> OP_SF_EBII_MIN_2_LD_0) << OP_SF_EBIF_MIN_2_LD_0);
    context->decoded_code->code.rx_min_2.rs =
        (((context->code24x1 & OP_SF_MASK_MIN_2_RS_0) >> OP_SF_EBII_MIN_2_RS_0) << OP_SF_EBIF_MIN_2_RS_0);
    context->decoded_code->code.rx_min_2.rd =
        (((context->code24x1 & OP_SF_MASK_MIN_2_RD_0) >> OP_SF_EBII_MIN_2_RD_0) << OP_SF_EBIF_MIN_2_RD_0);

    return 0;
}

/* emul_2 */
static int op_parse_emul_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_EMUL_2) != OP_FB_EMUL_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_emul_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_EMUL_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_EMUL_2;
    context->decoded_code->code.rx_emul_2.ld =
        (((context->code24x1 & OP_SF_MASK_EMUL_2_LD_0) >> OP_SF_EBII_EMUL_2_LD_0) << OP_SF_EBIF_EMUL_2_LD_0);
    context->decoded_code->code.rx_emul_2.rs =
        (((context->code24x1 & OP_SF_MASK_EMUL_2_RS_0) >> OP_SF_EBII_EMUL_2_RS_0) << OP_SF_EBIF_EMUL_2_RS_0);
    context->decoded_code->code.rx_emul_2.rd =
        (((context->code24x1 & OP_SF_MASK_EMUL_2_RD_0) >> OP_SF_EBII_EMUL_2_RD_0) << OP_SF_EBIF_EMUL_2_RD_0);

    return 0;
}

/* emulu_2 */
static int op_parse_emulu_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_EMULU_2) != OP_FB_EMULU_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_emulu_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_EMULU_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_EMULU_2;
    context->decoded_code->code.rx_emulu_2.ld =
        (((context->code24x1 & OP_SF_MASK_EMULU_2_LD_0) >> OP_SF_EBII_EMULU_2_LD_0) << OP_SF_EBIF_EMULU_2_LD_0);
    context->decoded_code->code.rx_emulu_2.rs =
        (((context->code24x1 & OP_SF_MASK_EMULU_2_RS_0) >> OP_SF_EBII_EMULU_2_RS_0) << OP_SF_EBIF_EMULU_2_RS_0);
    context->decoded_code->code.rx_emulu_2.rd =
        (((context->code24x1 & OP_SF_MASK_EMULU_2_RD_0) >> OP_SF_EBII_EMULU_2_RD_0) << OP_SF_EBIF_EMULU_2_RD_0);

    return 0;
}

/* div_2 */
static int op_parse_div_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_DIV_2) != OP_FB_DIV_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_div_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_DIV_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_DIV_2;
    context->decoded_code->code.rx_div_2.ld =
        (((context->code24x1 & OP_SF_MASK_DIV_2_LD_0) >> OP_SF_EBII_DIV_2_LD_0) << OP_SF_EBIF_DIV_2_LD_0);
    context->decoded_code->code.rx_div_2.rs =
        (((context->code24x1 & OP_SF_MASK_DIV_2_RS_0) >> OP_SF_EBII_DIV_2_RS_0) << OP_SF_EBIF_DIV_2_RS_0);
    context->decoded_code->code.rx_div_2.rd =
        (((context->code24x1 & OP_SF_MASK_DIV_2_RD_0) >> OP_SF_EBII_DIV_2_RD_0) << OP_SF_EBIF_DIV_2_RD_0);

    return 0;
}

/* divu_2 */
static int op_parse_divu_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_DIVU_2) != OP_FB_DIVU_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_divu_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_DIVU_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_DIVU_2;
    context->decoded_code->code.rx_divu_2.ld =
        (((context->code24x1 & OP_SF_MASK_DIVU_2_LD_0) >> OP_SF_EBII_DIVU_2_LD_0) << OP_SF_EBIF_DIVU_2_LD_0);
    context->decoded_code->code.rx_divu_2.rs =
        (((context->code24x1 & OP_SF_MASK_DIVU_2_RS_0) >> OP_SF_EBII_DIVU_2_RS_0) << OP_SF_EBIF_DIVU_2_RS_0);
    context->decoded_code->code.rx_divu_2.rd =
        (((context->code24x1 & OP_SF_MASK_DIVU_2_RD_0) >> OP_SF_EBII_DIVU_2_RD_0) << OP_SF_EBIF_DIVU_2_RD_0);

    return 0;
}

/* tst_2 */
static int op_parse_tst_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_TST_2) != OP_FB_TST_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_tst_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_TST_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_TST_2;
    context->decoded_code->code.rx_tst_2.ld =
        (((context->code24x1 & OP_SF_MASK_TST_2_LD_0) >> OP_SF_EBII_TST_2_LD_0) << OP_SF_EBIF_TST_2_LD_0);
    context->decoded_code->code.rx_tst_2.rs =
        (((context->code24x1 & OP_SF_MASK_TST_2_RS_0) >> OP_SF_EBII_TST_2_RS_0) << OP_SF_EBIF_TST_2_RS_0);
    context->decoded_code->code.rx_tst_2.rs2 =
        (((context->code24x1 & OP_SF_MASK_TST_2_RS2_0) >> OP_SF_EBII_TST_2_RS2_0) << OP_SF_EBIF_TST_2_RS2_0);

    return 0;
}

/* xor_2 */
static int op_parse_xor_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_XOR_2) != OP_FB_XOR_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_xor_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_XOR_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_XOR_2;
    context->decoded_code->code.rx_xor_2.ld =
        (((context->code24x1 & OP_SF_MASK_XOR_2_LD_0) >> OP_SF_EBII_XOR_2_LD_0) << OP_SF_EBIF_XOR_2_LD_0);
    context->decoded_code->code.rx_xor_2.rs =
        (((context->code24x1 & OP_SF_MASK_XOR_2_RS_0) >> OP_SF_EBII_XOR_2_RS_0) << OP_SF_EBIF_XOR_2_RS_0);
    context->decoded_code->code.rx_xor_2.rd =
        (((context->code24x1 & OP_SF_MASK_XOR_2_RD_0) >> OP_SF_EBII_XOR_2_RD_0) << OP_SF_EBIF_XOR_2_RD_0);

    return 0;
}

/* xchg_1 */
static int op_parse_xchg_1(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_XCHG_1) != OP_FB_XCHG_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_xchg_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_XCHG_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_XCHG_1;
    context->decoded_code->code.rx_xchg_1.ld =
        (((context->code24x1 & OP_SF_MASK_XCHG_1_LD_0) >> OP_SF_EBII_XCHG_1_LD_0) << OP_SF_EBIF_XCHG_1_LD_0);
    context->decoded_code->code.rx_xchg_1.rs =
        (((context->code24x1 & OP_SF_MASK_XCHG_1_RS_0) >> OP_SF_EBII_XCHG_1_RS_0) << OP_SF_EBIF_XCHG_1_RS_0);
    context->decoded_code->code.rx_xchg_1.rd =
        (((context->code24x1 & OP_SF_MASK_XCHG_1_RD_0) >> OP_SF_EBII_XCHG_1_RD_0) << OP_SF_EBIF_XCHG_1_RD_0);

    return 0;
}

/* itof_1 */
static int op_parse_itof_1(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_ITOF_1) != OP_FB_ITOF_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_itof_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_ITOF_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_ITOF_1;
    context->decoded_code->code.rx_itof_1.ld =
        (((context->code24x1 & OP_SF_MASK_ITOF_1_LD_0) >> OP_SF_EBII_ITOF_1_LD_0) << OP_SF_EBIF_ITOF_1_LD_0);
    context->decoded_code->code.rx_itof_1.rs =
        (((context->code24x1 & OP_SF_MASK_ITOF_1_RS_0) >> OP_SF_EBII_ITOF_1_RS_0) << OP_SF_EBIF_ITOF_1_RS_0);
    context->decoded_code->code.rx_itof_1.rd =
        (((context->code24x1 & OP_SF_MASK_ITOF_1_RD_0) >> OP_SF_EBII_ITOF_1_RD_0) << OP_SF_EBIF_ITOF_1_RD_0);

    return 0;
}

/* bset_2 */
static int op_parse_bset_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_BSET_2) != OP_FB_BSET_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_bset_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_BSET_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BSET_2;
    context->decoded_code->code.rx_bset_2.ld =
        (((context->code24x1 & OP_SF_MASK_BSET_2_LD_0) >> OP_SF_EBII_BSET_2_LD_0) << OP_SF_EBIF_BSET_2_LD_0);
    context->decoded_code->code.rx_bset_2.rd =
        (((context->code24x1 & OP_SF_MASK_BSET_2_RD_0) >> OP_SF_EBII_BSET_2_RD_0) << OP_SF_EBIF_BSET_2_RD_0);
    context->decoded_code->code.rx_bset_2.rs =
        (((context->code24x1 & OP_SF_MASK_BSET_2_RS_0) >> OP_SF_EBII_BSET_2_RS_0) << OP_SF_EBIF_BSET_2_RS_0);

    return 0;
}

/* bclr_2 */
static int op_parse_bclr_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_BCLR_2) != OP_FB_BCLR_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_bclr_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_BCLR_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BCLR_2;
    context->decoded_code->code.rx_bclr_2.ld =
        (((context->code24x1 & OP_SF_MASK_BCLR_2_LD_0) >> OP_SF_EBII_BCLR_2_LD_0) << OP_SF_EBIF_BCLR_2_LD_0);
    context->decoded_code->code.rx_bclr_2.rd =
        (((context->code24x1 & OP_SF_MASK_BCLR_2_RD_0) >> OP_SF_EBII_BCLR_2_RD_0) << OP_SF_EBIF_BCLR_2_RD_0);
    context->decoded_code->code.rx_bclr_2.rs =
        (((context->code24x1 & OP_SF_MASK_BCLR_2_RS_0) >> OP_SF_EBII_BCLR_2_RS_0) << OP_SF_EBIF_BCLR_2_RS_0);

    return 0;
}

/* btst_2 */
static int op_parse_btst_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_BTST_2) != OP_FB_BTST_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_btst_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_BTST_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BTST_2;
    context->decoded_code->code.rx_btst_2.ld =
        (((context->code24x1 & OP_SF_MASK_BTST_2_LD_0) >> OP_SF_EBII_BTST_2_LD_0) << OP_SF_EBIF_BTST_2_LD_0);
    context->decoded_code->code.rx_btst_2.rs2 =
        (((context->code24x1 & OP_SF_MASK_BTST_2_RS2_0) >> OP_SF_EBII_BTST_2_RS2_0) << OP_SF_EBIF_BTST_2_RS2_0);
    context->decoded_code->code.rx_btst_2.rs =
        (((context->code24x1 & OP_SF_MASK_BTST_2_RS_0) >> OP_SF_EBII_BTST_2_RS_0) << OP_SF_EBIF_BTST_2_RS_0);

    return 0;
}

/* bnot_2 */
static int op_parse_bnot_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_BNOT_2) != OP_FB_BNOT_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_bnot_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_BNOT_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BNOT_2;
    context->decoded_code->code.rx_bnot_2.ld =
        (((context->code24x1 & OP_SF_MASK_BNOT_2_LD_0) >> OP_SF_EBII_BNOT_2_LD_0) << OP_SF_EBIF_BNOT_2_LD_0);
    context->decoded_code->code.rx_bnot_2.rd =
        (((context->code24x1 & OP_SF_MASK_BNOT_2_RD_0) >> OP_SF_EBII_BNOT_2_RD_0) << OP_SF_EBIF_BNOT_2_RD_0);
    context->decoded_code->code.rx_bnot_2.rs =
        (((context->code24x1 & OP_SF_MASK_BNOT_2_RS_0) >> OP_SF_EBII_BNOT_2_RS_0) << OP_SF_EBIF_BNOT_2_RS_0);

    return 0;
}

/* fsub_2 */
static int op_parse_fsub_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_FSUB_2) != OP_FB_FSUB_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_fsub_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_FSUB_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_FSUB_2;
    context->decoded_code->code.rx_fsub_2.ld =
        (((context->code24x1 & OP_SF_MASK_FSUB_2_LD_0) >> OP_SF_EBII_FSUB_2_LD_0) << OP_SF_EBIF_FSUB_2_LD_0);
    context->decoded_code->code.rx_fsub_2.rs =
        (((context->code24x1 & OP_SF_MASK_FSUB_2_RS_0) >> OP_SF_EBII_FSUB_2_RS_0) << OP_SF_EBIF_FSUB_2_RS_0);
    context->decoded_code->code.rx_fsub_2.rd =
        (((context->code24x1 & OP_SF_MASK_FSUB_2_RD_0) >> OP_SF_EBII_FSUB_2_RD_0) << OP_SF_EBIF_FSUB_2_RD_0);

    return 0;
}

/* fcmp_2 */
static int op_parse_fcmp_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_FCMP_2) != OP_FB_FCMP_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_fcmp_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_FCMP_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_FCMP_2;
    context->decoded_code->code.rx_fcmp_2.ld =
        (((context->code24x1 & OP_SF_MASK_FCMP_2_LD_0) >> OP_SF_EBII_FCMP_2_LD_0) << OP_SF_EBIF_FCMP_2_LD_0);
    context->decoded_code->code.rx_fcmp_2.rs =
        (((context->code24x1 & OP_SF_MASK_FCMP_2_RS_0) >> OP_SF_EBII_FCMP_2_RS_0) << OP_SF_EBIF_FCMP_2_RS_0);
    context->decoded_code->code.rx_fcmp_2.rs2 =
        (((context->code24x1 & OP_SF_MASK_FCMP_2_RS2_0) >> OP_SF_EBII_FCMP_2_RS2_0) << OP_SF_EBIF_FCMP_2_RS2_0);

    return 0;
}

/* fadd_2 */
static int op_parse_fadd_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_FADD_2) != OP_FB_FADD_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_fadd_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_FADD_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_FADD_2;
    context->decoded_code->code.rx_fadd_2.ld =
        (((context->code24x1 & OP_SF_MASK_FADD_2_LD_0) >> OP_SF_EBII_FADD_2_LD_0) << OP_SF_EBIF_FADD_2_LD_0);
    context->decoded_code->code.rx_fadd_2.rs =
        (((context->code24x1 & OP_SF_MASK_FADD_2_RS_0) >> OP_SF_EBII_FADD_2_RS_0) << OP_SF_EBIF_FADD_2_RS_0);
    context->decoded_code->code.rx_fadd_2.rd =
        (((context->code24x1 & OP_SF_MASK_FADD_2_RD_0) >> OP_SF_EBII_FADD_2_RD_0) << OP_SF_EBIF_FADD_2_RD_0);

    return 0;
}

/* fmul_2 */
static int op_parse_fmul_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_FMUL_2) != OP_FB_FMUL_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_fmul_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_FMUL_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_FMUL_2;
    context->decoded_code->code.rx_fmul_2.ld =
        (((context->code24x1 & OP_SF_MASK_FMUL_2_LD_0) >> OP_SF_EBII_FMUL_2_LD_0) << OP_SF_EBIF_FMUL_2_LD_0);
    context->decoded_code->code.rx_fmul_2.rs =
        (((context->code24x1 & OP_SF_MASK_FMUL_2_RS_0) >> OP_SF_EBII_FMUL_2_RS_0) << OP_SF_EBIF_FMUL_2_RS_0);
    context->decoded_code->code.rx_fmul_2.rd =
        (((context->code24x1 & OP_SF_MASK_FMUL_2_RD_0) >> OP_SF_EBII_FMUL_2_RD_0) << OP_SF_EBIF_FMUL_2_RD_0);

    return 0;
}

/* fdiv_2 */
static int op_parse_fdiv_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_FDIV_2) != OP_FB_FDIV_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_fdiv_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_FDIV_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_FDIV_2;
    context->decoded_code->code.rx_fdiv_2.ld =
        (((context->code24x1 & OP_SF_MASK_FDIV_2_LD_0) >> OP_SF_EBII_FDIV_2_LD_0) << OP_SF_EBIF_FDIV_2_LD_0);
    context->decoded_code->code.rx_fdiv_2.rs =
        (((context->code24x1 & OP_SF_MASK_FDIV_2_RS_0) >> OP_SF_EBII_FDIV_2_RS_0) << OP_SF_EBIF_FDIV_2_RS_0);
    context->decoded_code->code.rx_fdiv_2.rd =
        (((context->code24x1 & OP_SF_MASK_FDIV_2_RD_0) >> OP_SF_EBII_FDIV_2_RD_0) << OP_SF_EBIF_FDIV_2_RD_0);

    return 0;
}

/* ftoi */
static int op_parse_ftoi(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_FTOI) != OP_FB_FTOI) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_ftoi;
    context->optype->format_id = RX_OP_CODE_FORMAT_FTOI;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_FTOI;
    context->decoded_code->code.rx_ftoi.ld =
        (((context->code24x1 & OP_SF_MASK_FTOI_LD_0) >> OP_SF_EBII_FTOI_LD_0) << OP_SF_EBIF_FTOI_LD_0);
    context->decoded_code->code.rx_ftoi.rs =
        (((context->code24x1 & OP_SF_MASK_FTOI_RS_0) >> OP_SF_EBII_FTOI_RS_0) << OP_SF_EBIF_FTOI_RS_0);
    context->decoded_code->code.rx_ftoi.rd =
        (((context->code24x1 & OP_SF_MASK_FTOI_RD_0) >> OP_SF_EBII_FTOI_RD_0) << OP_SF_EBIF_FTOI_RD_0);

    return 0;
}

/* round */
static int op_parse_round(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_ROUND) != OP_FB_ROUND) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_round;
    context->optype->format_id = RX_OP_CODE_FORMAT_ROUND;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_ROUND;
    context->decoded_code->code.rx_round.ld =
        (((context->code24x1 & OP_SF_MASK_ROUND_LD_0) >> OP_SF_EBII_ROUND_LD_0) << OP_SF_EBIF_ROUND_LD_0);
    context->decoded_code->code.rx_round.rs =
        (((context->code24x1 & OP_SF_MASK_ROUND_RS_0) >> OP_SF_EBII_ROUND_RS_0) << OP_SF_EBIF_ROUND_RS_0);
    context->decoded_code->code.rx_round.rd =
        (((context->code24x1 & OP_SF_MASK_ROUND_RD_0) >> OP_SF_EBII_ROUND_RD_0) << OP_SF_EBIF_ROUND_RD_0);

    return 0;
}

/* sccnd */
static int op_parse_sccnd(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_SCCND) != OP_FB_SCCND) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_sccnd;
    context->optype->format_id = RX_OP_CODE_FORMAT_SCCND;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SCCND;
    context->decoded_code->code.rx_sccnd.sz =
        (((context->code24x1 & OP_SF_MASK_SCCND_SZ_0) >> OP_SF_EBII_SCCND_SZ_0) << OP_SF_EBIF_SCCND_SZ_0);
    context->decoded_code->code.rx_sccnd.id =
        (((context->code24x1 & OP_SF_MASK_SCCND_ID_0) >> OP_SF_EBII_SCCND_ID_0) << OP_SF_EBIF_SCCND_ID_0);
    context->decoded_code->code.rx_sccnd.rd =
        (((context->code24x1 & OP_SF_MASK_SCCND_RD_0) >> OP_SF_EBII_SCCND_RD_0) << OP_SF_EBIF_SCCND_RD_0);
    context->decoded_code->code.rx_sccnd.cd =
        (((context->code24x1 & OP_SF_MASK_SCCND_CD_0) >> OP_SF_EBII_SCCND_CD_0) << OP_SF_EBIF_SCCND_CD_0);

    return 0;
}

/* bmcnd_1 */
static int op_parse_bmcnd_1(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_BMCND_1) != OP_FB_BMCND_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_bmcnd_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_BMCND_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BMCND_1;
    context->decoded_code->code.rx_bmcnd_1.imm =
        (((context->code24x1 & OP_SF_MASK_BMCND_1_IMM_0) >> OP_SF_EBII_BMCND_1_IMM_0) << OP_SF_EBIF_BMCND_1_IMM_0);
    context->decoded_code->code.rx_bmcnd_1.ld =
        (((context->code24x1 & OP_SF_MASK_BMCND_1_LD_0) >> OP_SF_EBII_BMCND_1_LD_0) << OP_SF_EBIF_BMCND_1_LD_0);
    context->decoded_code->code.rx_bmcnd_1.rd =
        (((context->code24x1 & OP_SF_MASK_BMCND_1_RD_0) >> OP_SF_EBII_BMCND_1_RD_0) << OP_SF_EBIF_BMCND_1_RD_0);
    context->decoded_code->code.rx_bmcnd_1.cd =
        (((context->code24x1 & OP_SF_MASK_BMCND_1_CD_0) >> OP_SF_EBII_BMCND_1_CD_0) << OP_SF_EBIF_BMCND_1_CD_0);

    return 0;
}

/* bnot_1 */
static int op_parse_bnot_1(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_BNOT_1) != OP_FB_BNOT_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_bnot_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_BNOT_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BNOT_1;
    context->decoded_code->code.rx_bnot_1.imm =
        (((context->code24x1 & OP_SF_MASK_BNOT_1_IMM_0) >> OP_SF_EBII_BNOT_1_IMM_0) << OP_SF_EBIF_BNOT_1_IMM_0);
    context->decoded_code->code.rx_bnot_1.id =
        (((context->code24x1 & OP_SF_MASK_BNOT_1_ID_0) >> OP_SF_EBII_BNOT_1_ID_0) << OP_SF_EBIF_BNOT_1_ID_0);
    context->decoded_code->code.rx_bnot_1.rd =
        (((context->code24x1 & OP_SF_MASK_BNOT_1_RD_0) >> OP_SF_EBII_BNOT_1_RD_0) << OP_SF_EBIF_BNOT_1_RD_0);

    return 0;
}

/* shlr_3 */
static int op_parse_shlr_3(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_SHLR_3) != OP_FB_SHLR_3) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_shlr_3;
    context->optype->format_id = RX_OP_CODE_FORMAT_SHLR_3;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SHLR_3;
    context->decoded_code->code.rx_shlr_3.imm =
        (((context->code24x1 & OP_SF_MASK_SHLR_3_IMM_0) >> OP_SF_EBII_SHLR_3_IMM_0) << OP_SF_EBIF_SHLR_3_IMM_0);
    context->decoded_code->code.rx_shlr_3.rs2 =
        (((context->code24x1 & OP_SF_MASK_SHLR_3_RS2_0) >> OP_SF_EBII_SHLR_3_RS2_0) << OP_SF_EBIF_SHLR_3_RS2_0);
    context->decoded_code->code.rx_shlr_3.rd =
        (((context->code24x1 & OP_SF_MASK_SHLR_3_RD_0) >> OP_SF_EBII_SHLR_3_RD_0) << OP_SF_EBIF_SHLR_3_RD_0);

    return 0;
}

/* shar_3 */
static int op_parse_shar_3(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_SHAR_3) != OP_FB_SHAR_3) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_shar_3;
    context->optype->format_id = RX_OP_CODE_FORMAT_SHAR_3;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SHAR_3;
    context->decoded_code->code.rx_shar_3.imm =
        (((context->code24x1 & OP_SF_MASK_SHAR_3_IMM_0) >> OP_SF_EBII_SHAR_3_IMM_0) << OP_SF_EBIF_SHAR_3_IMM_0);
    context->decoded_code->code.rx_shar_3.rs2 =
        (((context->code24x1 & OP_SF_MASK_SHAR_3_RS2_0) >> OP_SF_EBII_SHAR_3_RS2_0) << OP_SF_EBIF_SHAR_3_RS2_0);
    context->decoded_code->code.rx_shar_3.rd =
        (((context->code24x1 & OP_SF_MASK_SHAR_3_RD_0) >> OP_SF_EBII_SHAR_3_RD_0) << OP_SF_EBIF_SHAR_3_RD_0);

    return 0;
}

/* shll_3 */
static int op_parse_shll_3(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_SHLL_3) != OP_FB_SHLL_3) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_shll_3;
    context->optype->format_id = RX_OP_CODE_FORMAT_SHLL_3;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SHLL_3;
    context->decoded_code->code.rx_shll_3.imm =
        (((context->code24x1 & OP_SF_MASK_SHLL_3_IMM_0) >> OP_SF_EBII_SHLL_3_IMM_0) << OP_SF_EBIF_SHLL_3_IMM_0);
    context->decoded_code->code.rx_shll_3.rs2 =
        (((context->code24x1 & OP_SF_MASK_SHLL_3_RS2_0) >> OP_SF_EBII_SHLL_3_RS2_0) << OP_SF_EBIF_SHLL_3_RS2_0);
    context->decoded_code->code.rx_shll_3.rd =
        (((context->code24x1 & OP_SF_MASK_SHLL_3_RD_0) >> OP_SF_EBII_SHLL_3_RD_0) << OP_SF_EBIF_SHLL_3_RD_0);

    return 0;
}

/* bmcnd_2 */
static int op_parse_bmcnd_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_BMCND_2) != OP_FB_BMCND_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_bmcnd_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_BMCND_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BMCND_2;
    context->decoded_code->code.rx_bmcnd_2.imm =
        (((context->code24x1 & OP_SF_MASK_BMCND_2_IMM_0) >> OP_SF_EBII_BMCND_2_IMM_0) << OP_SF_EBIF_BMCND_2_IMM_0);
    context->decoded_code->code.rx_bmcnd_2.cd =
        (((context->code24x1 & OP_SF_MASK_BMCND_2_CD_0) >> OP_SF_EBII_BMCND_2_CD_0) << OP_SF_EBIF_BMCND_2_CD_0);
    context->decoded_code->code.rx_bmcnd_2.rd =
        (((context->code24x1 & OP_SF_MASK_BMCND_2_RD_0) >> OP_SF_EBII_BMCND_2_RD_0) << OP_SF_EBIF_BMCND_2_RD_0);

    return 0;
}

/* bnot_3 */
static int op_parse_bnot_3(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_BNOT_3) != OP_FB_BNOT_3) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_bnot_3;
    context->optype->format_id = RX_OP_CODE_FORMAT_BNOT_3;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BNOT_3;
    context->decoded_code->code.rx_bnot_3.imm =
        (((context->code24x1 & OP_SF_MASK_BNOT_3_IMM_0) >> OP_SF_EBII_BNOT_3_IMM_0) << OP_SF_EBIF_BNOT_3_IMM_0);
    context->decoded_code->code.rx_bnot_3.rd =
        (((context->code24x1 & OP_SF_MASK_BNOT_3_RD_0) >> OP_SF_EBII_BNOT_3_RD_0) << OP_SF_EBIF_BNOT_3_RD_0);

    return 0;
}

/* mulhi */
static int op_parse_mulhi(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MULHI) != OP_FB_MULHI) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mulhi;
    context->optype->format_id = RX_OP_CODE_FORMAT_MULHI;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MULHI;
    context->decoded_code->code.rx_mulhi.a =
        (((context->code24x1 & OP_SF_MASK_MULHI_A_0) >> OP_SF_EBII_MULHI_A_0) << OP_SF_EBIF_MULHI_A_0);
    context->decoded_code->code.rx_mulhi.rs =
        (((context->code24x1 & OP_SF_MASK_MULHI_RS_0) >> OP_SF_EBII_MULHI_RS_0) << OP_SF_EBIF_MULHI_RS_0);
    context->decoded_code->code.rx_mulhi.rs2 =
        (((context->code24x1 & OP_SF_MASK_MULHI_RS2_0) >> OP_SF_EBII_MULHI_RS2_0) << OP_SF_EBIF_MULHI_RS2_0);

    return 0;
}

/* mullo */
static int op_parse_mullo(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MULLO) != OP_FB_MULLO) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mullo;
    context->optype->format_id = RX_OP_CODE_FORMAT_MULLO;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MULLO;
    context->decoded_code->code.rx_mullo.a =
        (((context->code24x1 & OP_SF_MASK_MULLO_A_0) >> OP_SF_EBII_MULLO_A_0) << OP_SF_EBIF_MULLO_A_0);
    context->decoded_code->code.rx_mullo.rs =
        (((context->code24x1 & OP_SF_MASK_MULLO_RS_0) >> OP_SF_EBII_MULLO_RS_0) << OP_SF_EBIF_MULLO_RS_0);
    context->decoded_code->code.rx_mullo.rs2 =
        (((context->code24x1 & OP_SF_MASK_MULLO_RS2_0) >> OP_SF_EBII_MULLO_RS2_0) << OP_SF_EBIF_MULLO_RS2_0);

    return 0;
}

/* machi */
static int op_parse_machi(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MACHI) != OP_FB_MACHI) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_machi;
    context->optype->format_id = RX_OP_CODE_FORMAT_MACHI;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MACHI;
    context->decoded_code->code.rx_machi.a =
        (((context->code24x1 & OP_SF_MASK_MACHI_A_0) >> OP_SF_EBII_MACHI_A_0) << OP_SF_EBIF_MACHI_A_0);
    context->decoded_code->code.rx_machi.rs =
        (((context->code24x1 & OP_SF_MASK_MACHI_RS_0) >> OP_SF_EBII_MACHI_RS_0) << OP_SF_EBIF_MACHI_RS_0);
    context->decoded_code->code.rx_machi.rs2 =
        (((context->code24x1 & OP_SF_MASK_MACHI_RS2_0) >> OP_SF_EBII_MACHI_RS2_0) << OP_SF_EBIF_MACHI_RS2_0);

    return 0;
}

/* maclo */
static int op_parse_maclo(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MACLO) != OP_FB_MACLO) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_maclo;
    context->optype->format_id = RX_OP_CODE_FORMAT_MACLO;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MACLO;
    context->decoded_code->code.rx_maclo.a =
        (((context->code24x1 & OP_SF_MASK_MACLO_A_0) >> OP_SF_EBII_MACLO_A_0) << OP_SF_EBIF_MACLO_A_0);
    context->decoded_code->code.rx_maclo.rs =
        (((context->code24x1 & OP_SF_MASK_MACLO_RS_0) >> OP_SF_EBII_MACLO_RS_0) << OP_SF_EBIF_MACLO_RS_0);
    context->decoded_code->code.rx_maclo.rs2 =
        (((context->code24x1 & OP_SF_MASK_MACLO_RS2_0) >> OP_SF_EBII_MACLO_RS2_0) << OP_SF_EBIF_MACLO_RS2_0);

    return 0;
}

/* mvtachi */
static int op_parse_mvtachi(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MVTACHI) != OP_FB_MVTACHI) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mvtachi;
    context->optype->format_id = RX_OP_CODE_FORMAT_MVTACHI;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MVTACHI;
    context->decoded_code->code.rx_mvtachi.a =
        (((context->code24x1 & OP_SF_MASK_MVTACHI_A_0) >> OP_SF_EBII_MVTACHI_A_0) << OP_SF_EBIF_MVTACHI_A_0);
    context->decoded_code->code.rx_mvtachi.rs =
        (((context->code24x1 & OP_SF_MASK_MVTACHI_RS_0) >> OP_SF_EBII_MVTACHI_RS_0) << OP_SF_EBIF_MVTACHI_RS_0);

    return 0;
}

/* mvtaclo */
static int op_parse_mvtaclo(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MVTACLO) != OP_FB_MVTACLO) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mvtaclo;
    context->optype->format_id = RX_OP_CODE_FORMAT_MVTACLO;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MVTACLO;
    context->decoded_code->code.rx_mvtaclo.a =
        (((context->code24x1 & OP_SF_MASK_MVTACLO_A_0) >> OP_SF_EBII_MVTACLO_A_0) << OP_SF_EBIF_MVTACLO_A_0);
    context->decoded_code->code.rx_mvtaclo.rs =
        (((context->code24x1 & OP_SF_MASK_MVTACLO_RS_0) >> OP_SF_EBII_MVTACLO_RS_0) << OP_SF_EBIF_MVTACLO_RS_0);

    return 0;
}

/* racw */
static int op_parse_racw(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_RACW) != OP_FB_RACW) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_racw;
    context->optype->format_id = RX_OP_CODE_FORMAT_RACW;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_RACW;
    context->decoded_code->code.rx_racw.a =
        (((context->code24x1 & OP_SF_MASK_RACW_A_0) >> OP_SF_EBII_RACW_A_0) << OP_SF_EBIF_RACW_A_0);
    context->decoded_code->code.rx_racw.imm =
        (((context->code24x1 & OP_SF_MASK_RACW_IMM_0) >> OP_SF_EBII_RACW_IMM_0) << OP_SF_EBIF_RACW_IMM_0);

    return 0;
}

/* mvfachi */
static int op_parse_mvfachi(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MVFACHI) != OP_FB_MVFACHI) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mvfachi;
    context->optype->format_id = RX_OP_CODE_FORMAT_MVFACHI;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MVFACHI;
    context->decoded_code->code.rx_mvfachi.imm =
        (((context->code24x1 & OP_SF_MASK_MVFACHI_IMM_0) >> OP_SF_EBII_MVFACHI_IMM_0) << OP_SF_EBIF_MVFACHI_IMM_0)
        | (((context->code24x1 & OP_SF_MASK_MVFACHI_IMM_1) >> OP_SF_EBII_MVFACHI_IMM_1) << OP_SF_EBIF_MVFACHI_IMM_1);
    context->decoded_code->code.rx_mvfachi.a =
        (((context->code24x1 & OP_SF_MASK_MVFACHI_A_0) >> OP_SF_EBII_MVFACHI_A_0) << OP_SF_EBIF_MVFACHI_A_0);
    context->decoded_code->code.rx_mvfachi.rd =
        (((context->code24x1 & OP_SF_MASK_MVFACHI_RD_0) >> OP_SF_EBII_MVFACHI_RD_0) << OP_SF_EBIF_MVFACHI_RD_0);

    return 0;
}

/* mvfacmi */
static int op_parse_mvfacmi(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MVFACMI) != OP_FB_MVFACMI) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mvfacmi;
    context->optype->format_id = RX_OP_CODE_FORMAT_MVFACMI;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MVFACMI;
    context->decoded_code->code.rx_mvfacmi.imm =
        (((context->code24x1 & OP_SF_MASK_MVFACMI_IMM_0) >> OP_SF_EBII_MVFACMI_IMM_0) << OP_SF_EBIF_MVFACMI_IMM_0)
        | (((context->code24x1 & OP_SF_MASK_MVFACMI_IMM_1) >> OP_SF_EBII_MVFACMI_IMM_1) << OP_SF_EBIF_MVFACMI_IMM_1);
    context->decoded_code->code.rx_mvfacmi.a =
        (((context->code24x1 & OP_SF_MASK_MVFACMI_A_0) >> OP_SF_EBII_MVFACMI_A_0) << OP_SF_EBIF_MVFACMI_A_0);
    context->decoded_code->code.rx_mvfacmi.rd =
        (((context->code24x1 & OP_SF_MASK_MVFACMI_RD_0) >> OP_SF_EBII_MVFACMI_RD_0) << OP_SF_EBIF_MVFACMI_RD_0);

    return 0;
}

/* mov_14 */
static int op_parse_mov_14(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MOV_14) != OP_FB_MOV_14) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mov_14;
    context->optype->format_id = RX_OP_CODE_FORMAT_MOV_14;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MOV_14;
    context->decoded_code->code.rx_mov_14.ad =
        (((context->code24x1 & OP_SF_MASK_MOV_14_AD_0) >> OP_SF_EBII_MOV_14_AD_0) << OP_SF_EBIF_MOV_14_AD_0);
    context->decoded_code->code.rx_mov_14.sz =
        (((context->code24x1 & OP_SF_MASK_MOV_14_SZ_0) >> OP_SF_EBII_MOV_14_SZ_0) << OP_SF_EBIF_MOV_14_SZ_0);
    context->decoded_code->code.rx_mov_14.rd =
        (((context->code24x1 & OP_SF_MASK_MOV_14_RD_0) >> OP_SF_EBII_MOV_14_RD_0) << OP_SF_EBIF_MOV_14_RD_0);
    context->decoded_code->code.rx_mov_14.rs =
        (((context->code24x1 & OP_SF_MASK_MOV_14_RS_0) >> OP_SF_EBII_MOV_14_RS_0) << OP_SF_EBIF_MOV_14_RS_0);

    return 0;
}

/* mov_15 */
static int op_parse_mov_15(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MOV_15) != OP_FB_MOV_15) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mov_15;
    context->optype->format_id = RX_OP_CODE_FORMAT_MOV_15;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MOV_15;
    context->decoded_code->code.rx_mov_15.ad =
        (((context->code24x1 & OP_SF_MASK_MOV_15_AD_0) >> OP_SF_EBII_MOV_15_AD_0) << OP_SF_EBIF_MOV_15_AD_0);
    context->decoded_code->code.rx_mov_15.sz =
        (((context->code24x1 & OP_SF_MASK_MOV_15_SZ_0) >> OP_SF_EBII_MOV_15_SZ_0) << OP_SF_EBIF_MOV_15_SZ_0);
    context->decoded_code->code.rx_mov_15.rs =
        (((context->code24x1 & OP_SF_MASK_MOV_15_RS_0) >> OP_SF_EBII_MOV_15_RS_0) << OP_SF_EBIF_MOV_15_RS_0);
    context->decoded_code->code.rx_mov_15.rd =
        (((context->code24x1 & OP_SF_MASK_MOV_15_RD_0) >> OP_SF_EBII_MOV_15_RD_0) << OP_SF_EBIF_MOV_15_RD_0);

    return 0;
}

/* movu_4 */
static int op_parse_movu_4(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MOVU_4) != OP_FB_MOVU_4) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_movu_4;
    context->optype->format_id = RX_OP_CODE_FORMAT_MOVU_4;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MOVU_4;
    context->decoded_code->code.rx_movu_4.ad =
        (((context->code24x1 & OP_SF_MASK_MOVU_4_AD_0) >> OP_SF_EBII_MOVU_4_AD_0) << OP_SF_EBIF_MOVU_4_AD_0);
    context->decoded_code->code.rx_movu_4.sz =
        (((context->code24x1 & OP_SF_MASK_MOVU_4_SZ_0) >> OP_SF_EBII_MOVU_4_SZ_0) << OP_SF_EBIF_MOVU_4_SZ_0);
    context->decoded_code->code.rx_movu_4.rs =
        (((context->code24x1 & OP_SF_MASK_MOVU_4_RS_0) >> OP_SF_EBII_MOVU_4_RS_0) << OP_SF_EBIF_MOVU_4_RS_0);
    context->decoded_code->code.rx_movu_4.rd =
        (((context->code24x1 & OP_SF_MASK_MOVU_4_RD_0) >> OP_SF_EBII_MOVU_4_RD_0) << OP_SF_EBIF_MOVU_4_RD_0);

    return 0;
}

/* shlr_2 */
static int op_parse_shlr_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_SHLR_2) != OP_FB_SHLR_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_shlr_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_SHLR_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SHLR_2;
    context->decoded_code->code.rx_shlr_2.rs =
        (((context->code24x1 & OP_SF_MASK_SHLR_2_RS_0) >> OP_SF_EBII_SHLR_2_RS_0) << OP_SF_EBIF_SHLR_2_RS_0);
    context->decoded_code->code.rx_shlr_2.rd =
        (((context->code24x1 & OP_SF_MASK_SHLR_2_RD_0) >> OP_SF_EBII_SHLR_2_RD_0) << OP_SF_EBIF_SHLR_2_RD_0);

    return 0;
}

/* shar_2 */
static int op_parse_shar_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_SHAR_2) != OP_FB_SHAR_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_shar_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_SHAR_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SHAR_2;
    context->decoded_code->code.rx_shar_2.rs =
        (((context->code24x1 & OP_SF_MASK_SHAR_2_RS_0) >> OP_SF_EBII_SHAR_2_RS_0) << OP_SF_EBIF_SHAR_2_RS_0);
    context->decoded_code->code.rx_shar_2.rd =
        (((context->code24x1 & OP_SF_MASK_SHAR_2_RD_0) >> OP_SF_EBII_SHAR_2_RD_0) << OP_SF_EBIF_SHAR_2_RD_0);

    return 0;
}

/* shll_2 */
static int op_parse_shll_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_SHLL_2) != OP_FB_SHLL_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_shll_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_SHLL_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SHLL_2;
    context->decoded_code->code.rx_shll_2.rs =
        (((context->code24x1 & OP_SF_MASK_SHLL_2_RS_0) >> OP_SF_EBII_SHLL_2_RS_0) << OP_SF_EBIF_SHLL_2_RS_0);
    context->decoded_code->code.rx_shll_2.rd =
        (((context->code24x1 & OP_SF_MASK_SHLL_2_RD_0) >> OP_SF_EBII_SHLL_2_RD_0) << OP_SF_EBIF_SHLL_2_RD_0);

    return 0;
}

/* rotr_2 */
static int op_parse_rotr_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_ROTR_2) != OP_FB_ROTR_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_rotr_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_ROTR_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_ROTR_2;
    context->decoded_code->code.rx_rotr_2.rs =
        (((context->code24x1 & OP_SF_MASK_ROTR_2_RS_0) >> OP_SF_EBII_ROTR_2_RS_0) << OP_SF_EBIF_ROTR_2_RS_0);
    context->decoded_code->code.rx_rotr_2.rd =
        (((context->code24x1 & OP_SF_MASK_ROTR_2_RD_0) >> OP_SF_EBII_ROTR_2_RD_0) << OP_SF_EBIF_ROTR_2_RD_0);

    return 0;
}

/* revw */
static int op_parse_revw(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_REVW) != OP_FB_REVW) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_revw;
    context->optype->format_id = RX_OP_CODE_FORMAT_REVW;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_REVW;
    context->decoded_code->code.rx_revw.rs =
        (((context->code24x1 & OP_SF_MASK_REVW_RS_0) >> OP_SF_EBII_REVW_RS_0) << OP_SF_EBIF_REVW_RS_0);
    context->decoded_code->code.rx_revw.rd =
        (((context->code24x1 & OP_SF_MASK_REVW_RD_0) >> OP_SF_EBII_REVW_RD_0) << OP_SF_EBIF_REVW_RD_0);

    return 0;
}

/* rotl_2 */
static int op_parse_rotl_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_ROTL_2) != OP_FB_ROTL_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_rotl_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_ROTL_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_ROTL_2;
    context->decoded_code->code.rx_rotl_2.rs =
        (((context->code24x1 & OP_SF_MASK_ROTL_2_RS_0) >> OP_SF_EBII_ROTL_2_RS_0) << OP_SF_EBIF_ROTL_2_RS_0);
    context->decoded_code->code.rx_rotl_2.rd =
        (((context->code24x1 & OP_SF_MASK_ROTL_2_RD_0) >> OP_SF_EBII_ROTL_2_RD_0) << OP_SF_EBIF_ROTL_2_RD_0);

    return 0;
}

/* revl */
static int op_parse_revl(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_REVL) != OP_FB_REVL) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_revl;
    context->optype->format_id = RX_OP_CODE_FORMAT_REVL;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_REVL;
    context->decoded_code->code.rx_revl.rs =
        (((context->code24x1 & OP_SF_MASK_REVL_RS_0) >> OP_SF_EBII_REVL_RS_0) << OP_SF_EBIF_REVL_RS_0);
    context->decoded_code->code.rx_revl.rd =
        (((context->code24x1 & OP_SF_MASK_REVL_RD_0) >> OP_SF_EBII_REVL_RD_0) << OP_SF_EBIF_REVL_RD_0);

    return 0;
}

/* mvtc_2 */
static int op_parse_mvtc_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MVTC_2) != OP_FB_MVTC_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mvtc_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_MVTC_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MVTC_2;
    context->decoded_code->code.rx_mvtc_2.rs =
        (((context->code24x1 & OP_SF_MASK_MVTC_2_RS_0) >> OP_SF_EBII_MVTC_2_RS_0) << OP_SF_EBIF_MVTC_2_RS_0);
    context->decoded_code->code.rx_mvtc_2.cr =
        (((context->code24x1 & OP_SF_MASK_MVTC_2_CR_0) >> OP_SF_EBII_MVTC_2_CR_0) << OP_SF_EBIF_MVTC_2_CR_0);

    return 0;
}

/* mvfc */
static int op_parse_mvfc(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MVFC) != OP_FB_MVFC) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mvfc;
    context->optype->format_id = RX_OP_CODE_FORMAT_MVFC;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MVFC;
    context->decoded_code->code.rx_mvfc.cr =
        (((context->code24x1 & OP_SF_MASK_MVFC_CR_0) >> OP_SF_EBII_MVFC_CR_0) << OP_SF_EBIF_MVFC_CR_0);
    context->decoded_code->code.rx_mvfc.rd =
        (((context->code24x1 & OP_SF_MASK_MVFC_RD_0) >> OP_SF_EBII_MVFC_RD_0) << OP_SF_EBIF_MVFC_RD_0);

    return 0;
}

/* rotr_1 */
static int op_parse_rotr_1(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_ROTR_1) != OP_FB_ROTR_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_rotr_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_ROTR_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_ROTR_1;
    context->decoded_code->code.rx_rotr_1.imm =
        (((context->code24x1 & OP_SF_MASK_ROTR_1_IMM_0) >> OP_SF_EBII_ROTR_1_IMM_0) << OP_SF_EBIF_ROTR_1_IMM_0);
    context->decoded_code->code.rx_rotr_1.rd =
        (((context->code24x1 & OP_SF_MASK_ROTR_1_RD_0) >> OP_SF_EBII_ROTR_1_RD_0) << OP_SF_EBIF_ROTR_1_RD_0);

    return 0;
}

/* rotl_1 */
static int op_parse_rotl_1(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_ROTL_1) != OP_FB_ROTL_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_rotl_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_ROTL_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_ROTL_1;
    context->decoded_code->code.rx_rotl_1.imm =
        (((context->code24x1 & OP_SF_MASK_ROTL_1_IMM_0) >> OP_SF_EBII_ROTL_1_IMM_0) << OP_SF_EBIF_ROTL_1_IMM_0);
    context->decoded_code->code.rx_rotl_1.rd =
        (((context->code24x1 & OP_SF_MASK_ROTL_1_RD_0) >> OP_SF_EBII_ROTL_1_RD_0) << OP_SF_EBIF_ROTL_1_RD_0);

    return 0;
}

/* fadd_1 */
static int op_parse_fadd_1(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_FADD_1) != OP_FB_FADD_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_fadd_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_FADD_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_FADD_1;
    context->decoded_code->code.rx_fadd_1.rd =
        (((context->code24x1 & OP_SF_MASK_FADD_1_RD_0) >> OP_SF_EBII_FADD_1_RD_0) << OP_SF_EBIF_FADD_1_RD_0);

    return 0;
}

/* fcmp_1 */
static int op_parse_fcmp_1(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_FCMP_1) != OP_FB_FCMP_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_fcmp_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_FCMP_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_FCMP_1;
    context->decoded_code->code.rx_fcmp_1.rs2 =
        (((context->code24x1 & OP_SF_MASK_FCMP_1_RS2_0) >> OP_SF_EBII_FCMP_1_RS2_0) << OP_SF_EBIF_FCMP_1_RS2_0);

    return 0;
}

/* fdiv_1 */
static int op_parse_fdiv_1(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_FDIV_1) != OP_FB_FDIV_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_fdiv_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_FDIV_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_FDIV_1;
    context->decoded_code->code.rx_fdiv_1.rd =
        (((context->code24x1 & OP_SF_MASK_FDIV_1_RD_0) >> OP_SF_EBII_FDIV_1_RD_0) << OP_SF_EBIF_FDIV_1_RD_0);

    return 0;
}

/* fmul_1 */
static int op_parse_fmul_1(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_FMUL_1) != OP_FB_FMUL_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_fmul_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_FMUL_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_FMUL_1;
    context->decoded_code->code.rx_fmul_1.rd =
        (((context->code24x1 & OP_SF_MASK_FMUL_1_RD_0) >> OP_SF_EBII_FMUL_1_RD_0) << OP_SF_EBIF_FMUL_1_RD_0);

    return 0;
}

/* fsub_1 */
static int op_parse_fsub_1(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_FSUB_1) != OP_FB_FSUB_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_fsub_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_FSUB_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_FSUB_1;
    context->decoded_code->code.rx_fsub_1.rd =
        (((context->code24x1 & OP_SF_MASK_FSUB_1_RD_0) >> OP_SF_EBII_FSUB_1_RD_0) << OP_SF_EBIF_FSUB_1_RD_0);

    return 0;
}

/* adc_1 */
static int op_parse_adc_1(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_ADC_1) != OP_FB_ADC_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_adc_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_ADC_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_ADC_1;
    context->decoded_code->code.rx_adc_1.li =
        (((context->code24x1 & OP_SF_MASK_ADC_1_LI_0) >> OP_SF_EBII_ADC_1_LI_0) << OP_SF_EBIF_ADC_1_LI_0);
    context->decoded_code->code.rx_adc_1.rd =
        (((context->code24x1 & OP_SF_MASK_ADC_1_RD_0) >> OP_SF_EBII_ADC_1_RD_0) << OP_SF_EBIF_ADC_1_RD_0);

    return 0;
}

/* div_1 */
static int op_parse_div_1(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_DIV_1) != OP_FB_DIV_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_div_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_DIV_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_DIV_1;
    context->decoded_code->code.rx_div_1.li =
        (((context->code24x1 & OP_SF_MASK_DIV_1_LI_0) >> OP_SF_EBII_DIV_1_LI_0) << OP_SF_EBIF_DIV_1_LI_0);
    context->decoded_code->code.rx_div_1.rd =
        (((context->code24x1 & OP_SF_MASK_DIV_1_RD_0) >> OP_SF_EBII_DIV_1_RD_0) << OP_SF_EBIF_DIV_1_RD_0);

    return 0;
}

/* divu_1 */
static int op_parse_divu_1(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_DIVU_1) != OP_FB_DIVU_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_divu_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_DIVU_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_DIVU_1;
    context->decoded_code->code.rx_divu_1.li =
        (((context->code24x1 & OP_SF_MASK_DIVU_1_LI_0) >> OP_SF_EBII_DIVU_1_LI_0) << OP_SF_EBIF_DIVU_1_LI_0);
    context->decoded_code->code.rx_divu_1.rd =
        (((context->code24x1 & OP_SF_MASK_DIVU_1_RD_0) >> OP_SF_EBII_DIVU_1_RD_0) << OP_SF_EBIF_DIVU_1_RD_0);

    return 0;
}

/* emul_1 */
static int op_parse_emul_1(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_EMUL_1) != OP_FB_EMUL_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_emul_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_EMUL_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_EMUL_1;
    context->decoded_code->code.rx_emul_1.li =
        (((context->code24x1 & OP_SF_MASK_EMUL_1_LI_0) >> OP_SF_EBII_EMUL_1_LI_0) << OP_SF_EBIF_EMUL_1_LI_0);
    context->decoded_code->code.rx_emul_1.rd =
        (((context->code24x1 & OP_SF_MASK_EMUL_1_RD_0) >> OP_SF_EBII_EMUL_1_RD_0) << OP_SF_EBIF_EMUL_1_RD_0);

    return 0;
}

/* emulu_1 */
static int op_parse_emulu_1(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_EMULU_1) != OP_FB_EMULU_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_emulu_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_EMULU_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_EMULU_1;
    context->decoded_code->code.rx_emulu_1.li =
        (((context->code24x1 & OP_SF_MASK_EMULU_1_LI_0) >> OP_SF_EBII_EMULU_1_LI_0) << OP_SF_EBIF_EMULU_1_LI_0);
    context->decoded_code->code.rx_emulu_1.rd =
        (((context->code24x1 & OP_SF_MASK_EMULU_1_RD_0) >> OP_SF_EBII_EMULU_1_RD_0) << OP_SF_EBIF_EMULU_1_RD_0);

    return 0;
}

/* max_1 */
static int op_parse_max_1(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MAX_1) != OP_FB_MAX_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_max_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_MAX_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MAX_1;
    context->decoded_code->code.rx_max_1.li =
        (((context->code24x1 & OP_SF_MASK_MAX_1_LI_0) >> OP_SF_EBII_MAX_1_LI_0) << OP_SF_EBIF_MAX_1_LI_0);
    context->decoded_code->code.rx_max_1.rd =
        (((context->code24x1 & OP_SF_MASK_MAX_1_RD_0) >> OP_SF_EBII_MAX_1_RD_0) << OP_SF_EBIF_MAX_1_RD_0);

    return 0;
}

/* min_1 */
static int op_parse_min_1(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MIN_1) != OP_FB_MIN_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_min_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_MIN_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MIN_1;
    context->decoded_code->code.rx_min_1.li =
        (((context->code24x1 & OP_SF_MASK_MIN_1_LI_0) >> OP_SF_EBII_MIN_1_LI_0) << OP_SF_EBIF_MIN_1_LI_0);
    context->decoded_code->code.rx_min_1.rd =
        (((context->code24x1 & OP_SF_MASK_MIN_1_RD_0) >> OP_SF_EBII_MIN_1_RD_0) << OP_SF_EBIF_MIN_1_RD_0);

    return 0;
}

/* stnz_1 */
static int op_parse_stnz_1(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_STNZ_1) != OP_FB_STNZ_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_stnz_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_STNZ_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_STNZ_1;
    context->decoded_code->code.rx_stnz_1.li =
        (((context->code24x1 & OP_SF_MASK_STNZ_1_LI_0) >> OP_SF_EBII_STNZ_1_LI_0) << OP_SF_EBIF_STNZ_1_LI_0);
    context->decoded_code->code.rx_stnz_1.rd =
        (((context->code24x1 & OP_SF_MASK_STNZ_1_RD_0) >> OP_SF_EBII_STNZ_1_RD_0) << OP_SF_EBIF_STNZ_1_RD_0);

    return 0;
}

/* stz_1 */
static int op_parse_stz_1(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_STZ_1) != OP_FB_STZ_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_stz_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_STZ_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_STZ_1;
    context->decoded_code->code.rx_stz_1.li =
        (((context->code24x1 & OP_SF_MASK_STZ_1_LI_0) >> OP_SF_EBII_STZ_1_LI_0) << OP_SF_EBIF_STZ_1_LI_0);
    context->decoded_code->code.rx_stz_1.rd =
        (((context->code24x1 & OP_SF_MASK_STZ_1_RD_0) >> OP_SF_EBII_STZ_1_RD_0) << OP_SF_EBIF_STZ_1_RD_0);

    return 0;
}

/* tst_1 */
static int op_parse_tst_1(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_TST_1) != OP_FB_TST_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_tst_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_TST_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_TST_1;
    context->decoded_code->code.rx_tst_1.li =
        (((context->code24x1 & OP_SF_MASK_TST_1_LI_0) >> OP_SF_EBII_TST_1_LI_0) << OP_SF_EBIF_TST_1_LI_0);
    context->decoded_code->code.rx_tst_1.rs2 =
        (((context->code24x1 & OP_SF_MASK_TST_1_RS2_0) >> OP_SF_EBII_TST_1_RS2_0) << OP_SF_EBIF_TST_1_RS2_0);

    return 0;
}

/* xor_1 */
static int op_parse_xor_1(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_XOR_1) != OP_FB_XOR_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_xor_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_XOR_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_XOR_1;
    context->decoded_code->code.rx_xor_1.li =
        (((context->code24x1 & OP_SF_MASK_XOR_1_LI_0) >> OP_SF_EBII_XOR_1_LI_0) << OP_SF_EBIF_XOR_1_LI_0);
    context->decoded_code->code.rx_xor_1.rd =
        (((context->code24x1 & OP_SF_MASK_XOR_1_RD_0) >> OP_SF_EBII_XOR_1_RD_0) << OP_SF_EBIF_XOR_1_RD_0);

    return 0;
}

/* mvtc_1 */
static int op_parse_mvtc_1(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MVTC_1) != OP_FB_MVTC_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mvtc_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_MVTC_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MVTC_1;
    context->decoded_code->code.rx_mvtc_1.li =
        (((context->code24x1 & OP_SF_MASK_MVTC_1_LI_0) >> OP_SF_EBII_MVTC_1_LI_0) << OP_SF_EBIF_MVTC_1_LI_0);
    context->decoded_code->code.rx_mvtc_1.cr =
        (((context->code24x1 & OP_SF_MASK_MVTC_1_CR_0) >> OP_SF_EBII_MVTC_1_CR_0) << OP_SF_EBIF_MVTC_1_CR_0);

    return 0;
}

/* mov_10 */
static int op_parse_mov_10(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MOV_10) != OP_FB_MOV_10) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mov_10;
    context->optype->format_id = RX_OP_CODE_FORMAT_MOV_10;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MOV_10;
    context->decoded_code->code.rx_mov_10.sz =
        (((context->code24x1 & OP_SF_MASK_MOV_10_SZ_0) >> OP_SF_EBII_MOV_10_SZ_0) << OP_SF_EBIF_MOV_10_SZ_0);
    context->decoded_code->code.rx_mov_10.ri =
        (((context->code24x1 & OP_SF_MASK_MOV_10_RI_0) >> OP_SF_EBII_MOV_10_RI_0) << OP_SF_EBIF_MOV_10_RI_0);
    context->decoded_code->code.rx_mov_10.rb =
        (((context->code24x1 & OP_SF_MASK_MOV_10_RB_0) >> OP_SF_EBII_MOV_10_RB_0) << OP_SF_EBIF_MOV_10_RB_0);
    context->decoded_code->code.rx_mov_10.rd =
        (((context->code24x1 & OP_SF_MASK_MOV_10_RD_0) >> OP_SF_EBII_MOV_10_RD_0) << OP_SF_EBIF_MOV_10_RD_0);

    return 0;
}

/* mov_12 */
static int op_parse_mov_12(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MOV_12) != OP_FB_MOV_12) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mov_12;
    context->optype->format_id = RX_OP_CODE_FORMAT_MOV_12;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MOV_12;
    context->decoded_code->code.rx_mov_12.sz =
        (((context->code24x1 & OP_SF_MASK_MOV_12_SZ_0) >> OP_SF_EBII_MOV_12_SZ_0) << OP_SF_EBIF_MOV_12_SZ_0);
    context->decoded_code->code.rx_mov_12.ri =
        (((context->code24x1 & OP_SF_MASK_MOV_12_RI_0) >> OP_SF_EBII_MOV_12_RI_0) << OP_SF_EBIF_MOV_12_RI_0);
    context->decoded_code->code.rx_mov_12.rb =
        (((context->code24x1 & OP_SF_MASK_MOV_12_RB_0) >> OP_SF_EBII_MOV_12_RB_0) << OP_SF_EBIF_MOV_12_RB_0);
    context->decoded_code->code.rx_mov_12.rs =
        (((context->code24x1 & OP_SF_MASK_MOV_12_RS_0) >> OP_SF_EBII_MOV_12_RS_0) << OP_SF_EBIF_MOV_12_RS_0);

    return 0;
}

/* movu_3 */
static int op_parse_movu_3(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MOVU_3) != OP_FB_MOVU_3) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_movu_3;
    context->optype->format_id = RX_OP_CODE_FORMAT_MOVU_3;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MOVU_3;
    context->decoded_code->code.rx_movu_3.sz =
        (((context->code24x1 & OP_SF_MASK_MOVU_3_SZ_0) >> OP_SF_EBII_MOVU_3_SZ_0) << OP_SF_EBIF_MOVU_3_SZ_0);
    context->decoded_code->code.rx_movu_3.ri =
        (((context->code24x1 & OP_SF_MASK_MOVU_3_RI_0) >> OP_SF_EBII_MOVU_3_RI_0) << OP_SF_EBIF_MOVU_3_RI_0);
    context->decoded_code->code.rx_movu_3.rb =
        (((context->code24x1 & OP_SF_MASK_MOVU_3_RB_0) >> OP_SF_EBII_MOVU_3_RB_0) << OP_SF_EBIF_MOVU_3_RB_0);
    context->decoded_code->code.rx_movu_3.rd =
        (((context->code24x1 & OP_SF_MASK_MOVU_3_RD_0) >> OP_SF_EBII_MOVU_3_RD_0) << OP_SF_EBIF_MOVU_3_RD_0);

    return 0;
}

/* add_4 */
static int op_parse_add_4(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_ADD_4) != OP_FB_ADD_4) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_add_4;
    context->optype->format_id = RX_OP_CODE_FORMAT_ADD_4;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_ADD_4;
    context->decoded_code->code.rx_add_4.rd =
        (((context->code24x1 & OP_SF_MASK_ADD_4_RD_0) >> OP_SF_EBII_ADD_4_RD_0) << OP_SF_EBIF_ADD_4_RD_0);
    context->decoded_code->code.rx_add_4.rs =
        (((context->code24x1 & OP_SF_MASK_ADD_4_RS_0) >> OP_SF_EBII_ADD_4_RS_0) << OP_SF_EBIF_ADD_4_RS_0);
    context->decoded_code->code.rx_add_4.rs2 =
        (((context->code24x1 & OP_SF_MASK_ADD_4_RS2_0) >> OP_SF_EBII_ADD_4_RS2_0) << OP_SF_EBIF_ADD_4_RS2_0);

    return 0;
}

/* and_4 */
static int op_parse_and_4(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_AND_4) != OP_FB_AND_4) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_and_4;
    context->optype->format_id = RX_OP_CODE_FORMAT_AND_4;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_AND_4;
    context->decoded_code->code.rx_and_4.rd =
        (((context->code24x1 & OP_SF_MASK_AND_4_RD_0) >> OP_SF_EBII_AND_4_RD_0) << OP_SF_EBIF_AND_4_RD_0);
    context->decoded_code->code.rx_and_4.rs =
        (((context->code24x1 & OP_SF_MASK_AND_4_RS_0) >> OP_SF_EBII_AND_4_RS_0) << OP_SF_EBIF_AND_4_RS_0);
    context->decoded_code->code.rx_and_4.rs2 =
        (((context->code24x1 & OP_SF_MASK_AND_4_RS2_0) >> OP_SF_EBII_AND_4_RS2_0) << OP_SF_EBIF_AND_4_RS2_0);

    return 0;
}

/* mul_4 */
static int op_parse_mul_4(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MUL_4) != OP_FB_MUL_4) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mul_4;
    context->optype->format_id = RX_OP_CODE_FORMAT_MUL_4;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MUL_4;
    context->decoded_code->code.rx_mul_4.rd =
        (((context->code24x1 & OP_SF_MASK_MUL_4_RD_0) >> OP_SF_EBII_MUL_4_RD_0) << OP_SF_EBIF_MUL_4_RD_0);
    context->decoded_code->code.rx_mul_4.rs =
        (((context->code24x1 & OP_SF_MASK_MUL_4_RS_0) >> OP_SF_EBII_MUL_4_RS_0) << OP_SF_EBIF_MUL_4_RS_0);
    context->decoded_code->code.rx_mul_4.rs2 =
        (((context->code24x1 & OP_SF_MASK_MUL_4_RS2_0) >> OP_SF_EBII_MUL_4_RS2_0) << OP_SF_EBIF_MUL_4_RS2_0);

    return 0;
}

/* or_4 */
static int op_parse_or_4(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_OR_4) != OP_FB_OR_4) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_or_4;
    context->optype->format_id = RX_OP_CODE_FORMAT_OR_4;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_OR_4;
    context->decoded_code->code.rx_or_4.rd =
        (((context->code24x1 & OP_SF_MASK_OR_4_RD_0) >> OP_SF_EBII_OR_4_RD_0) << OP_SF_EBIF_OR_4_RD_0);
    context->decoded_code->code.rx_or_4.rs =
        (((context->code24x1 & OP_SF_MASK_OR_4_RS_0) >> OP_SF_EBII_OR_4_RS_0) << OP_SF_EBIF_OR_4_RS_0);
    context->decoded_code->code.rx_or_4.rs2 =
        (((context->code24x1 & OP_SF_MASK_OR_4_RS2_0) >> OP_SF_EBII_OR_4_RS2_0) << OP_SF_EBIF_OR_4_RS2_0);

    return 0;
}

/* sub_3 */
static int op_parse_sub_3(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_SUB_3) != OP_FB_SUB_3) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_sub_3;
    context->optype->format_id = RX_OP_CODE_FORMAT_SUB_3;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_SUB_3;
    context->decoded_code->code.rx_sub_3.rd =
        (((context->code24x1 & OP_SF_MASK_SUB_3_RD_0) >> OP_SF_EBII_SUB_3_RD_0) << OP_SF_EBIF_SUB_3_RD_0);
    context->decoded_code->code.rx_sub_3.rs =
        (((context->code24x1 & OP_SF_MASK_SUB_3_RS_0) >> OP_SF_EBII_SUB_3_RS_0) << OP_SF_EBIF_SUB_3_RS_0);
    context->decoded_code->code.rx_sub_3.rs2 =
        (((context->code24x1 & OP_SF_MASK_SUB_3_RS2_0) >> OP_SF_EBII_SUB_3_RS2_0) << OP_SF_EBIF_SUB_3_RS2_0);

    return 0;
}

/* bclr_1 */
static int op_parse_bclr_1(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_BCLR_1) != OP_FB_BCLR_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_bclr_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_BCLR_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BCLR_1;
    context->decoded_code->code.rx_bclr_1.ld =
        (((context->code16x1 & OP_SF_MASK_BCLR_1_LD_0) >> OP_SF_EBII_BCLR_1_LD_0) << OP_SF_EBIF_BCLR_1_LD_0);
    context->decoded_code->code.rx_bclr_1.rd =
        (((context->code16x1 & OP_SF_MASK_BCLR_1_RD_0) >> OP_SF_EBII_BCLR_1_RD_0) << OP_SF_EBIF_BCLR_1_RD_0);
    context->decoded_code->code.rx_bclr_1.imm =
        (((context->code16x1 & OP_SF_MASK_BCLR_1_IMM_0) >> OP_SF_EBII_BCLR_1_IMM_0) << OP_SF_EBIF_BCLR_1_IMM_0);

    return 0;
}

/* bset_1 */
static int op_parse_bset_1(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_BSET_1) != OP_FB_BSET_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_bset_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_BSET_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BSET_1;
    context->decoded_code->code.rx_bset_1.ld =
        (((context->code16x1 & OP_SF_MASK_BSET_1_LD_0) >> OP_SF_EBII_BSET_1_LD_0) << OP_SF_EBIF_BSET_1_LD_0);
    context->decoded_code->code.rx_bset_1.rd =
        (((context->code16x1 & OP_SF_MASK_BSET_1_RD_0) >> OP_SF_EBII_BSET_1_RD_0) << OP_SF_EBIF_BSET_1_RD_0);
    context->decoded_code->code.rx_bset_1.rs =
        (((context->code16x1 & OP_SF_MASK_BSET_1_RS_0) >> OP_SF_EBII_BSET_1_RS_0) << OP_SF_EBIF_BSET_1_RS_0);

    return 0;
}

/* btst_1 */
static int op_parse_btst_1(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_BTST_1) != OP_FB_BTST_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_btst_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_BTST_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_BTST_1;
    context->decoded_code->code.rx_btst_1.ld =
        (((context->code16x1 & OP_SF_MASK_BTST_1_LD_0) >> OP_SF_EBII_BTST_1_LD_0) << OP_SF_EBIF_BTST_1_LD_0);
    context->decoded_code->code.rx_btst_1.rs2 =
        (((context->code16x1 & OP_SF_MASK_BTST_1_RS2_0) >> OP_SF_EBII_BTST_1_RS2_0) << OP_SF_EBIF_BTST_1_RS2_0);
    context->decoded_code->code.rx_btst_1.imm =
        (((context->code16x1 & OP_SF_MASK_BTST_1_IMM_0) >> OP_SF_EBII_BTST_1_IMM_0) << OP_SF_EBIF_BTST_1_IMM_0);

    return 0;
}

/* push_2 */
static int op_parse_push_2(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_PUSH_2) != OP_FB_PUSH_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_push_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_PUSH_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_PUSH_2;
    context->decoded_code->code.rx_push_2.ld =
        (((context->code16x1 & OP_SF_MASK_PUSH_2_LD_0) >> OP_SF_EBII_PUSH_2_LD_0) << OP_SF_EBIF_PUSH_2_LD_0);
    context->decoded_code->code.rx_push_2.rs =
        (((context->code16x1 & OP_SF_MASK_PUSH_2_RS_0) >> OP_SF_EBII_PUSH_2_RS_0) << OP_SF_EBIF_PUSH_2_RS_0);
    context->decoded_code->code.rx_push_2.sz =
        (((context->code16x1 & OP_SF_MASK_PUSH_2_SZ_0) >> OP_SF_EBII_PUSH_2_SZ_0) << OP_SF_EBIF_PUSH_2_SZ_0);

    return 0;
}

/* mov_6 */
static int op_parse_mov_6(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_MOV_6) != OP_FB_MOV_6) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mov_6;
    context->optype->format_id = RX_OP_CODE_FORMAT_MOV_6;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MOV_6;
    context->decoded_code->code.rx_mov_6.rd =
        (((context->code16x1 & OP_SF_MASK_MOV_6_RD_0) >> OP_SF_EBII_MOV_6_RD_0) << OP_SF_EBIF_MOV_6_RD_0);
    context->decoded_code->code.rx_mov_6.li =
        (((context->code16x1 & OP_SF_MASK_MOV_6_LI_0) >> OP_SF_EBII_MOV_6_LI_0) << OP_SF_EBIF_MOV_6_LI_0);

    return 0;
}

/* mov_8 */
static int op_parse_mov_8(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_MOV_8) != OP_FB_MOV_8) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mov_8;
    context->optype->format_id = RX_OP_CODE_FORMAT_MOV_8;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MOV_8;
    context->decoded_code->code.rx_mov_8.ld =
        (((context->code16x1 & OP_SF_MASK_MOV_8_LD_0) >> OP_SF_EBII_MOV_8_LD_0) << OP_SF_EBIF_MOV_8_LD_0);
    context->decoded_code->code.rx_mov_8.rd =
        (((context->code16x1 & OP_SF_MASK_MOV_8_RD_0) >> OP_SF_EBII_MOV_8_RD_0) << OP_SF_EBIF_MOV_8_RD_0);
    context->decoded_code->code.rx_mov_8.li =
        (((context->code16x1 & OP_SF_MASK_MOV_8_LI_0) >> OP_SF_EBII_MOV_8_LI_0) << OP_SF_EBIF_MOV_8_LI_0);
    context->decoded_code->code.rx_mov_8.sz =
        (((context->code16x1 & OP_SF_MASK_MOV_8_SZ_0) >> OP_SF_EBII_MOV_8_SZ_0) << OP_SF_EBIF_MOV_8_SZ_0);

    return 0;
}

/* mov_7 */
static int op_parse_mov_7(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_MOV_7) != OP_FB_MOV_7) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mov_7;
    context->optype->format_id = RX_OP_CODE_FORMAT_MOV_7;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MOV_7;
    context->decoded_code->code.rx_mov_7.sz =
        (((context->code16x1 & OP_SF_MASK_MOV_7_SZ_0) >> OP_SF_EBII_MOV_7_SZ_0) << OP_SF_EBIF_MOV_7_SZ_0);
    context->decoded_code->code.rx_mov_7.rs =
        (((context->code16x1 & OP_SF_MASK_MOV_7_RS_0) >> OP_SF_EBII_MOV_7_RS_0) << OP_SF_EBIF_MOV_7_RS_0);
    context->decoded_code->code.rx_mov_7.rd =
        (((context->code16x1 & OP_SF_MASK_MOV_7_RD_0) >> OP_SF_EBII_MOV_7_RD_0) << OP_SF_EBIF_MOV_7_RD_0);

    return 0;
}

/* mov_9 */
static int op_parse_mov_9(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_MOV_9) != OP_FB_MOV_9) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mov_9;
    context->optype->format_id = RX_OP_CODE_FORMAT_MOV_9;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MOV_9;
    context->decoded_code->code.rx_mov_9.sz =
        (((context->code16x1 & OP_SF_MASK_MOV_9_SZ_0) >> OP_SF_EBII_MOV_9_SZ_0) << OP_SF_EBIF_MOV_9_SZ_0);
    context->decoded_code->code.rx_mov_9.ld =
        (((context->code16x1 & OP_SF_MASK_MOV_9_LD_0) >> OP_SF_EBII_MOV_9_LD_0) << OP_SF_EBIF_MOV_9_LD_0);
    context->decoded_code->code.rx_mov_9.rs =
        (((context->code16x1 & OP_SF_MASK_MOV_9_RS_0) >> OP_SF_EBII_MOV_9_RS_0) << OP_SF_EBIF_MOV_9_RS_0);
    context->decoded_code->code.rx_mov_9.rd =
        (((context->code16x1 & OP_SF_MASK_MOV_9_RD_0) >> OP_SF_EBII_MOV_9_RD_0) << OP_SF_EBIF_MOV_9_RD_0);

    return 0;
}

/* mov_11 */
static int op_parse_mov_11(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_MOV_11) != OP_FB_MOV_11) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mov_11;
    context->optype->format_id = RX_OP_CODE_FORMAT_MOV_11;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MOV_11;
    context->decoded_code->code.rx_mov_11.sz =
        (((context->code16x1 & OP_SF_MASK_MOV_11_SZ_0) >> OP_SF_EBII_MOV_11_SZ_0) << OP_SF_EBIF_MOV_11_SZ_0);
    context->decoded_code->code.rx_mov_11.ld =
        (((context->code16x1 & OP_SF_MASK_MOV_11_LD_0) >> OP_SF_EBII_MOV_11_LD_0) << OP_SF_EBIF_MOV_11_LD_0);
    context->decoded_code->code.rx_mov_11.rd =
        (((context->code16x1 & OP_SF_MASK_MOV_11_RD_0) >> OP_SF_EBII_MOV_11_RD_0) << OP_SF_EBIF_MOV_11_RD_0);
    context->decoded_code->code.rx_mov_11.rs =
        (((context->code16x1 & OP_SF_MASK_MOV_11_RS_0) >> OP_SF_EBII_MOV_11_RS_0) << OP_SF_EBIF_MOV_11_RS_0);

    return 0;
}

/* mov_13 */
static int op_parse_mov_13(OpDecodeContext *context) {
    if ((context->code16x1 & OP_FB_MASK_MOV_13) != OP_FB_MOV_13) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mov_13;
    context->optype->format_id = RX_OP_CODE_FORMAT_MOV_13;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MOV_13;
    context->decoded_code->code.rx_mov_13.sz =
        (((context->code16x1 & OP_SF_MASK_MOV_13_SZ_0) >> OP_SF_EBII_MOV_13_SZ_0) << OP_SF_EBIF_MOV_13_SZ_0);
    context->decoded_code->code.rx_mov_13.ldd =
        (((context->code16x1 & OP_SF_MASK_MOV_13_LDD_0) >> OP_SF_EBII_MOV_13_LDD_0) << OP_SF_EBIF_MOV_13_LDD_0);
    context->decoded_code->code.rx_mov_13.lds =
        (((context->code16x1 & OP_SF_MASK_MOV_13_LDS_0) >> OP_SF_EBII_MOV_13_LDS_0) << OP_SF_EBIF_MOV_13_LDS_0);
    context->decoded_code->code.rx_mov_13.rs =
        (((context->code16x1 & OP_SF_MASK_MOV_13_RS_0) >> OP_SF_EBII_MOV_13_RS_0) << OP_SF_EBIF_MOV_13_RS_0);
    context->decoded_code->code.rx_mov_13.rd =
        (((context->code16x1 & OP_SF_MASK_MOV_13_RD_0) >> OP_SF_EBII_MOV_13_RD_0) << OP_SF_EBIF_MOV_13_RD_0);

    return 0;
}

/* fsqrt */
static int op_parse_fsqrt(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_FSQRT) != OP_FB_FSQRT) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_fsqrt;
    context->optype->format_id = RX_OP_CODE_FORMAT_FSQRT;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_FSQRT;
    context->decoded_code->code.rx_fsqrt.ld =
        (((context->code24x1 & OP_SF_MASK_FSQRT_LD_0) >> OP_SF_EBII_FSQRT_LD_0) << OP_SF_EBIF_FSQRT_LD_0);
    context->decoded_code->code.rx_fsqrt.rs =
        (((context->code24x1 & OP_SF_MASK_FSQRT_RS_0) >> OP_SF_EBII_FSQRT_RS_0) << OP_SF_EBIF_FSQRT_RS_0);
    context->decoded_code->code.rx_fsqrt.rd =
        (((context->code24x1 & OP_SF_MASK_FSQRT_RD_0) >> OP_SF_EBII_FSQRT_RD_0) << OP_SF_EBIF_FSQRT_RD_0);

    return 0;
}

/* ftou */
static int op_parse_ftou(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_FTOU) != OP_FB_FTOU) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_ftou;
    context->optype->format_id = RX_OP_CODE_FORMAT_FTOU;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_FTOU;
    context->decoded_code->code.rx_ftou.ld =
        (((context->code24x1 & OP_SF_MASK_FTOU_LD_0) >> OP_SF_EBII_FTOU_LD_0) << OP_SF_EBIF_FTOU_LD_0);
    context->decoded_code->code.rx_ftou.rs =
        (((context->code24x1 & OP_SF_MASK_FTOU_RS_0) >> OP_SF_EBII_FTOU_RS_0) << OP_SF_EBIF_FTOU_RS_0);
    context->decoded_code->code.rx_ftou.rd =
        (((context->code24x1 & OP_SF_MASK_FTOU_RD_0) >> OP_SF_EBII_FTOU_RD_0) << OP_SF_EBIF_FTOU_RD_0);

    return 0;
}

/* utof_1 */
static int op_parse_utof_1(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_UTOF_1) != OP_FB_UTOF_1) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_utof_1;
    context->optype->format_id = RX_OP_CODE_FORMAT_UTOF_1;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_UTOF_1;
    context->decoded_code->code.rx_utof_1.ld =
        (((context->code24x1 & OP_SF_MASK_UTOF_1_LD_0) >> OP_SF_EBII_UTOF_1_LD_0) << OP_SF_EBIF_UTOF_1_LD_0);
    context->decoded_code->code.rx_utof_1.rs =
        (((context->code24x1 & OP_SF_MASK_UTOF_1_RS_0) >> OP_SF_EBII_UTOF_1_RS_0) << OP_SF_EBIF_UTOF_1_RS_0);
    context->decoded_code->code.rx_utof_1.rd =
        (((context->code24x1 & OP_SF_MASK_UTOF_1_RD_0) >> OP_SF_EBII_UTOF_1_RD_0) << OP_SF_EBIF_UTOF_1_RD_0);

    return 0;
}

/* utof_1x */
static int op_parse_utof_1x(OpDecodeContext *context) {
    if ((context->code32x1 & OP_FB_MASK_UTOF_1X) != OP_FB_UTOF_1X) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_utof_1x;
    context->optype->format_id = RX_OP_CODE_FORMAT_UTOF_1X;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_UTOF_1X;
    context->decoded_code->code.rx_utof_1x.mi =
        (((context->code32x1 & OP_SF_MASK_UTOF_1X_MI_0) >> OP_SF_EBII_UTOF_1X_MI_0) << OP_SF_EBIF_UTOF_1X_MI_0);
    context->decoded_code->code.rx_utof_1x.ld =
        (((context->code32x1 & OP_SF_MASK_UTOF_1X_LD_0) >> OP_SF_EBII_UTOF_1X_LD_0) << OP_SF_EBIF_UTOF_1X_LD_0);
    context->decoded_code->code.rx_utof_1x.rs =
        (((context->code32x1 & OP_SF_MASK_UTOF_1X_RS_0) >> OP_SF_EBII_UTOF_1X_RS_0) << OP_SF_EBIF_UTOF_1X_RS_0);
    context->decoded_code->code.rx_utof_1x.rd =
        (((context->code32x1 & OP_SF_MASK_UTOF_1X_RD_0) >> OP_SF_EBII_UTOF_1X_RD_0) << OP_SF_EBIF_UTOF_1X_RD_0);

    return 0;
}

/* movco */
static int op_parse_movco(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MOVCO) != OP_FB_MOVCO) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_movco;
    context->optype->format_id = RX_OP_CODE_FORMAT_MOVCO;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MOVCO;
    context->decoded_code->code.rx_movco.rd =
        (((context->code24x1 & OP_SF_MASK_MOVCO_RD_0) >> OP_SF_EBII_MOVCO_RD_0) << OP_SF_EBIF_MOVCO_RD_0);
    context->decoded_code->code.rx_movco.rs =
        (((context->code24x1 & OP_SF_MASK_MOVCO_RS_0) >> OP_SF_EBII_MOVCO_RS_0) << OP_SF_EBIF_MOVCO_RS_0);

    return 0;
}

/* movli */
static int op_parse_movli(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MOVLI) != OP_FB_MOVLI) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_movli;
    context->optype->format_id = RX_OP_CODE_FORMAT_MOVLI;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MOVLI;
    context->decoded_code->code.rx_movli.rs =
        (((context->code24x1 & OP_SF_MASK_MOVLI_RS_0) >> OP_SF_EBII_MOVLI_RS_0) << OP_SF_EBIF_MOVLI_RS_0);
    context->decoded_code->code.rx_movli.rd =
        (((context->code24x1 & OP_SF_MASK_MOVLI_RD_0) >> OP_SF_EBII_MOVLI_RD_0) << OP_SF_EBIF_MOVLI_RD_0);

    return 0;
}

/* emaca */
static int op_parse_emaca(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_EMACA) != OP_FB_EMACA) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_emaca;
    context->optype->format_id = RX_OP_CODE_FORMAT_EMACA;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_EMACA;
    context->decoded_code->code.rx_emaca.a =
        (((context->code24x1 & OP_SF_MASK_EMACA_A_0) >> OP_SF_EBII_EMACA_A_0) << OP_SF_EBIF_EMACA_A_0);
    context->decoded_code->code.rx_emaca.rs =
        (((context->code24x1 & OP_SF_MASK_EMACA_RS_0) >> OP_SF_EBII_EMACA_RS_0) << OP_SF_EBIF_EMACA_RS_0);
    context->decoded_code->code.rx_emaca.rs2 =
        (((context->code24x1 & OP_SF_MASK_EMACA_RS2_0) >> OP_SF_EBII_EMACA_RS2_0) << OP_SF_EBIF_EMACA_RS2_0);

    return 0;
}

/* emsba */
static int op_parse_emsba(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_EMSBA) != OP_FB_EMSBA) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_emsba;
    context->optype->format_id = RX_OP_CODE_FORMAT_EMSBA;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_EMSBA;
    context->decoded_code->code.rx_emsba.a =
        (((context->code24x1 & OP_SF_MASK_EMSBA_A_0) >> OP_SF_EBII_EMSBA_A_0) << OP_SF_EBIF_EMSBA_A_0);
    context->decoded_code->code.rx_emsba.rs =
        (((context->code24x1 & OP_SF_MASK_EMSBA_RS_0) >> OP_SF_EBII_EMSBA_RS_0) << OP_SF_EBIF_EMSBA_RS_0);
    context->decoded_code->code.rx_emsba.rs2 =
        (((context->code24x1 & OP_SF_MASK_EMSBA_RS2_0) >> OP_SF_EBII_EMSBA_RS2_0) << OP_SF_EBIF_EMSBA_RS2_0);

    return 0;
}

/* emula */
static int op_parse_emula(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_EMULA) != OP_FB_EMULA) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_emula;
    context->optype->format_id = RX_OP_CODE_FORMAT_EMULA;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_EMULA;
    context->decoded_code->code.rx_emula.a =
        (((context->code24x1 & OP_SF_MASK_EMULA_A_0) >> OP_SF_EBII_EMULA_A_0) << OP_SF_EBIF_EMULA_A_0);
    context->decoded_code->code.rx_emula.rs =
        (((context->code24x1 & OP_SF_MASK_EMULA_RS_0) >> OP_SF_EBII_EMULA_RS_0) << OP_SF_EBIF_EMULA_RS_0);
    context->decoded_code->code.rx_emula.rs2 =
        (((context->code24x1 & OP_SF_MASK_EMULA_RS2_0) >> OP_SF_EBII_EMULA_RS2_0) << OP_SF_EBIF_EMULA_RS2_0);

    return 0;
}

/* maclh */
static int op_parse_maclh(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MACLH) != OP_FB_MACLH) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_maclh;
    context->optype->format_id = RX_OP_CODE_FORMAT_MACLH;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MACLH;
    context->decoded_code->code.rx_maclh.a =
        (((context->code24x1 & OP_SF_MASK_MACLH_A_0) >> OP_SF_EBII_MACLH_A_0) << OP_SF_EBIF_MACLH_A_0);
    context->decoded_code->code.rx_maclh.rs =
        (((context->code24x1 & OP_SF_MASK_MACLH_RS_0) >> OP_SF_EBII_MACLH_RS_0) << OP_SF_EBIF_MACLH_RS_0);
    context->decoded_code->code.rx_maclh.rs2 =
        (((context->code24x1 & OP_SF_MASK_MACLH_RS2_0) >> OP_SF_EBII_MACLH_RS2_0) << OP_SF_EBIF_MACLH_RS2_0);

    return 0;
}

/* msbhi */
static int op_parse_msbhi(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MSBHI) != OP_FB_MSBHI) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_msbhi;
    context->optype->format_id = RX_OP_CODE_FORMAT_MSBHI;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MSBHI;
    context->decoded_code->code.rx_msbhi.a =
        (((context->code24x1 & OP_SF_MASK_MSBHI_A_0) >> OP_SF_EBII_MSBHI_A_0) << OP_SF_EBIF_MSBHI_A_0);
    context->decoded_code->code.rx_msbhi.rs =
        (((context->code24x1 & OP_SF_MASK_MSBHI_RS_0) >> OP_SF_EBII_MSBHI_RS_0) << OP_SF_EBIF_MSBHI_RS_0);
    context->decoded_code->code.rx_msbhi.rs2 =
        (((context->code24x1 & OP_SF_MASK_MSBHI_RS2_0) >> OP_SF_EBII_MSBHI_RS2_0) << OP_SF_EBIF_MSBHI_RS2_0);

    return 0;
}

/* msblh */
static int op_parse_msblh(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MSBLH) != OP_FB_MSBLH) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_msblh;
    context->optype->format_id = RX_OP_CODE_FORMAT_MSBLH;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MSBLH;
    context->decoded_code->code.rx_msblh.a =
        (((context->code24x1 & OP_SF_MASK_MSBLH_A_0) >> OP_SF_EBII_MSBLH_A_0) << OP_SF_EBIF_MSBLH_A_0);
    context->decoded_code->code.rx_msblh.rs =
        (((context->code24x1 & OP_SF_MASK_MSBLH_RS_0) >> OP_SF_EBII_MSBLH_RS_0) << OP_SF_EBIF_MSBLH_RS_0);
    context->decoded_code->code.rx_msblh.rs2 =
        (((context->code24x1 & OP_SF_MASK_MSBLH_RS2_0) >> OP_SF_EBII_MSBLH_RS2_0) << OP_SF_EBIF_MSBLH_RS2_0);

    return 0;
}

/* msblo */
static int op_parse_msblo(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MSBLO) != OP_FB_MSBLO) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_msblo;
    context->optype->format_id = RX_OP_CODE_FORMAT_MSBLO;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MSBLO;
    context->decoded_code->code.rx_msblo.a =
        (((context->code24x1 & OP_SF_MASK_MSBLO_A_0) >> OP_SF_EBII_MSBLO_A_0) << OP_SF_EBIF_MSBLO_A_0);
    context->decoded_code->code.rx_msblo.rs =
        (((context->code24x1 & OP_SF_MASK_MSBLO_RS_0) >> OP_SF_EBII_MSBLO_RS_0) << OP_SF_EBIF_MSBLO_RS_0);
    context->decoded_code->code.rx_msblo.rs2 =
        (((context->code24x1 & OP_SF_MASK_MSBLO_RS2_0) >> OP_SF_EBII_MSBLO_RS2_0) << OP_SF_EBIF_MSBLO_RS2_0);

    return 0;
}

/* mullh */
static int op_parse_mullh(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MULLH) != OP_FB_MULLH) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mullh;
    context->optype->format_id = RX_OP_CODE_FORMAT_MULLH;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MULLH;
    context->decoded_code->code.rx_mullh.a =
        (((context->code24x1 & OP_SF_MASK_MULLH_A_0) >> OP_SF_EBII_MULLH_A_0) << OP_SF_EBIF_MULLH_A_0);
    context->decoded_code->code.rx_mullh.rs =
        (((context->code24x1 & OP_SF_MASK_MULLH_RS_0) >> OP_SF_EBII_MULLH_RS_0) << OP_SF_EBIF_MULLH_RS_0);
    context->decoded_code->code.rx_mullh.rs2 =
        (((context->code24x1 & OP_SF_MASK_MULLH_RS2_0) >> OP_SF_EBII_MULLH_RS2_0) << OP_SF_EBIF_MULLH_RS2_0);

    return 0;
}

/* mvfacgu */
static int op_parse_mvfacgu(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MVFACGU) != OP_FB_MVFACGU) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mvfacgu;
    context->optype->format_id = RX_OP_CODE_FORMAT_MVFACGU;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MVFACGU;
    context->decoded_code->code.rx_mvfacgu.imm =
        (((context->code24x1 & OP_SF_MASK_MVFACGU_IMM_0) >> OP_SF_EBII_MVFACGU_IMM_0) << OP_SF_EBIF_MVFACGU_IMM_0)
        | (((context->code24x1 & OP_SF_MASK_MVFACGU_IMM_1) >> OP_SF_EBII_MVFACGU_IMM_1) << OP_SF_EBIF_MVFACGU_IMM_1);
    context->decoded_code->code.rx_mvfacgu.a =
        (((context->code24x1 & OP_SF_MASK_MVFACGU_A_0) >> OP_SF_EBII_MVFACGU_A_0) << OP_SF_EBIF_MVFACGU_A_0);
    context->decoded_code->code.rx_mvfacgu.rd =
        (((context->code24x1 & OP_SF_MASK_MVFACGU_RD_0) >> OP_SF_EBII_MVFACGU_RD_0) << OP_SF_EBIF_MVFACGU_RD_0);

    return 0;
}

/* mvfaclo */
static int op_parse_mvfaclo(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MVFACLO) != OP_FB_MVFACLO) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mvfaclo;
    context->optype->format_id = RX_OP_CODE_FORMAT_MVFACLO;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MVFACLO;
    context->decoded_code->code.rx_mvfaclo.imm =
        (((context->code24x1 & OP_SF_MASK_MVFACLO_IMM_0) >> OP_SF_EBII_MVFACLO_IMM_0) << OP_SF_EBIF_MVFACLO_IMM_0)
        | (((context->code24x1 & OP_SF_MASK_MVFACLO_IMM_1) >> OP_SF_EBII_MVFACLO_IMM_1) << OP_SF_EBIF_MVFACLO_IMM_1);
    context->decoded_code->code.rx_mvfaclo.a =
        (((context->code24x1 & OP_SF_MASK_MVFACLO_A_0) >> OP_SF_EBII_MVFACLO_A_0) << OP_SF_EBIF_MVFACLO_A_0);
    context->decoded_code->code.rx_mvfaclo.rd =
        (((context->code24x1 & OP_SF_MASK_MVFACLO_RD_0) >> OP_SF_EBII_MVFACLO_RD_0) << OP_SF_EBIF_MVFACLO_RD_0);

    return 0;
}

/* mvtacgu */
static int op_parse_mvtacgu(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_MVTACGU) != OP_FB_MVTACGU) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_mvtacgu;
    context->optype->format_id = RX_OP_CODE_FORMAT_MVTACGU;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_MVTACGU;
    context->decoded_code->code.rx_mvtacgu.a =
        (((context->code24x1 & OP_SF_MASK_MVTACGU_A_0) >> OP_SF_EBII_MVTACGU_A_0) << OP_SF_EBIF_MVTACGU_A_0);
    context->decoded_code->code.rx_mvtacgu.rs =
        (((context->code24x1 & OP_SF_MASK_MVTACGU_RS_0) >> OP_SF_EBII_MVTACGU_RS_0) << OP_SF_EBIF_MVTACGU_RS_0);

    return 0;
}

/* racl */
static int op_parse_racl(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_RACL) != OP_FB_RACL) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_racl;
    context->optype->format_id = RX_OP_CODE_FORMAT_RACL;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_RACL;
    context->decoded_code->code.rx_racl.a =
        (((context->code24x1 & OP_SF_MASK_RACL_A_0) >> OP_SF_EBII_RACL_A_0) << OP_SF_EBIF_RACL_A_0);
    context->decoded_code->code.rx_racl.imm =
        (((context->code24x1 & OP_SF_MASK_RACL_IMM_0) >> OP_SF_EBII_RACL_IMM_0) << OP_SF_EBIF_RACL_IMM_0);

    return 0;
}

/* rdacl */
static int op_parse_rdacl(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_RDACL) != OP_FB_RDACL) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_rdacl;
    context->optype->format_id = RX_OP_CODE_FORMAT_RDACL;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_RDACL;
    context->decoded_code->code.rx_rdacl.a =
        (((context->code24x1 & OP_SF_MASK_RDACL_A_0) >> OP_SF_EBII_RDACL_A_0) << OP_SF_EBIF_RDACL_A_0);
    context->decoded_code->code.rx_rdacl.imm =
        (((context->code24x1 & OP_SF_MASK_RDACL_IMM_0) >> OP_SF_EBII_RDACL_IMM_0) << OP_SF_EBIF_RDACL_IMM_0);

    return 0;
}

/* rdacw */
static int op_parse_rdacw(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_RDACW) != OP_FB_RDACW) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_rdacw;
    context->optype->format_id = RX_OP_CODE_FORMAT_RDACW;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_RDACW;
    context->decoded_code->code.rx_rdacw.a =
        (((context->code24x1 & OP_SF_MASK_RDACW_A_0) >> OP_SF_EBII_RDACW_A_0) << OP_SF_EBIF_RDACW_A_0);
    context->decoded_code->code.rx_rdacw.imm =
        (((context->code24x1 & OP_SF_MASK_RDACW_IMM_0) >> OP_SF_EBII_RDACW_IMM_0) << OP_SF_EBIF_RDACW_IMM_0);

    return 0;
}

/* fadd_3 */
static int op_parse_fadd_3(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_FADD_3) != OP_FB_FADD_3) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_fadd_3;
    context->optype->format_id = RX_OP_CODE_FORMAT_FADD_3;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_FADD_3;
    context->decoded_code->code.rx_fadd_3.rd =
        (((context->code24x1 & OP_SF_MASK_FADD_3_RD_0) >> OP_SF_EBII_FADD_3_RD_0) << OP_SF_EBIF_FADD_3_RD_0);
    context->decoded_code->code.rx_fadd_3.rs =
        (((context->code24x1 & OP_SF_MASK_FADD_3_RS_0) >> OP_SF_EBII_FADD_3_RS_0) << OP_SF_EBIF_FADD_3_RS_0);
    context->decoded_code->code.rx_fadd_3.rs2 =
        (((context->code24x1 & OP_SF_MASK_FADD_3_RS2_0) >> OP_SF_EBII_FADD_3_RS2_0) << OP_SF_EBIF_FADD_3_RS2_0);

    return 0;
}

/* fmul_3 */
static int op_parse_fmul_3(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_FMUL_3) != OP_FB_FMUL_3) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_fmul_3;
    context->optype->format_id = RX_OP_CODE_FORMAT_FMUL_3;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_FMUL_3;
    context->decoded_code->code.rx_fmul_3.rd =
        (((context->code24x1 & OP_SF_MASK_FMUL_3_RD_0) >> OP_SF_EBII_FMUL_3_RD_0) << OP_SF_EBIF_FMUL_3_RD_0);
    context->decoded_code->code.rx_fmul_3.rs =
        (((context->code24x1 & OP_SF_MASK_FMUL_3_RS_0) >> OP_SF_EBII_FMUL_3_RS_0) << OP_SF_EBIF_FMUL_3_RS_0);
    context->decoded_code->code.rx_fmul_3.rs2 =
        (((context->code24x1 & OP_SF_MASK_FMUL_3_RS2_0) >> OP_SF_EBII_FMUL_3_RS2_0) << OP_SF_EBIF_FMUL_3_RS2_0);

    return 0;
}

/* fsub_3 */
static int op_parse_fsub_3(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_FSUB_3) != OP_FB_FSUB_3) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_fsub_3;
    context->optype->format_id = RX_OP_CODE_FORMAT_FSUB_3;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_FSUB_3;
    context->decoded_code->code.rx_fsub_3.rd =
        (((context->code24x1 & OP_SF_MASK_FSUB_3_RD_0) >> OP_SF_EBII_FSUB_3_RD_0) << OP_SF_EBIF_FSUB_3_RD_0);
    context->decoded_code->code.rx_fsub_3.rs =
        (((context->code24x1 & OP_SF_MASK_FSUB_3_RS_0) >> OP_SF_EBII_FSUB_3_RS_0) << OP_SF_EBIF_FSUB_3_RS_0);
    context->decoded_code->code.rx_fsub_3.rs2 =
        (((context->code24x1 & OP_SF_MASK_FSUB_3_RS2_0) >> OP_SF_EBII_FSUB_3_RS2_0) << OP_SF_EBIF_FSUB_3_RS2_0);

    return 0;
}

/* stnz_2 */
static int op_parse_stnz_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_STNZ_2) != OP_FB_STNZ_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_stnz_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_STNZ_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_STNZ_2;
    context->decoded_code->code.rx_stnz_2.rs =
        (((context->code24x1 & OP_SF_MASK_STNZ_2_RS_0) >> OP_SF_EBII_STNZ_2_RS_0) << OP_SF_EBIF_STNZ_2_RS_0);
    context->decoded_code->code.rx_stnz_2.rd =
        (((context->code24x1 & OP_SF_MASK_STNZ_2_RD_0) >> OP_SF_EBII_STNZ_2_RD_0) << OP_SF_EBIF_STNZ_2_RD_0);

    return 0;
}

/* stz_2 */
static int op_parse_stz_2(OpDecodeContext *context) {
    if ((context->code24x1 & OP_FB_MASK_STZ_2) != OP_FB_STZ_2) {
        return 1;
    }

    context->optype->code_id = RxOpCodeId_stz_2;
    context->optype->format_id = RX_OP_CODE_FORMAT_STZ_2;
    context->decoded_code->type_id = RX_OP_CODE_FORMAT_STZ_2;
    context->decoded_code->code.rx_stz_2.rs =
        (((context->code24x1 & OP_SF_MASK_STZ_2_RS_0) >> OP_SF_EBII_STZ_2_RS_0) << OP_SF_EBIF_STZ_2_RS_0);
    context->decoded_code->code.rx_stz_2.rd =
        (((context->code24x1 & OP_SF_MASK_STZ_2_RD_0) >> OP_SF_EBII_STZ_2_RD_0) << OP_SF_EBIF_STZ_2_RD_0);

    return 0;
}


/* decision node functions */

static int decision_node_code8x1_0(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x000000f0) {
    case 0x00000000:
        if (decision_node_code8x1_1(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000010:
        if (decision_node_code8x1_7(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code8x1_1(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000008) {
    case 0x00000000:
        if (decision_node_code8x1_2(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000008:
        if (decision_node_code8x1_6(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code8x1_2(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000007) {
    case 0x00000000:
        if (decision_node_code8x1_3(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000002:
        if (decision_node_code8x1_4(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000003:
        if (decision_node_code8x1_5(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code8x1_3(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_brk(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code8x1_4(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_rts(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code8x1_5(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_nop(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code8x1_6(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_bra_s(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code8x1_7(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_bcnd_s(context) == 0) {
        return 0;
    }

    return 1;
}


static int decision_node_code16x1_0(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000800) {
    case 0x00000000:
        if (decision_node_code16x1_1(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000800:
        if (decision_node_code16x1_31(context, code) == 0) {
            return 0;
        }
        break;
    }

    if (decision_node_code16x1_107(context, code) == 0) {
        return 0;
    }
    return 1;
}

static int decision_node_code16x1_1(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00003400) {
    case 0x00000000:
        if (decision_node_code16x1_2(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000400:
        if (decision_node_code16x1_3(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00001000:
        if (decision_node_code16x1_4(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00001400:
        if (decision_node_code16x1_5(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00002000:
        if (decision_node_code16x1_6(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00002400:
        if (decision_node_code16x1_11(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00003000:
        if (decision_node_code16x1_16(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00003400:
        if (decision_node_code16x1_21(context, code) == 0) {
            return 0;
        }
        break;
    }

    if (decision_node_code16x1_30(context, code) == 0) {
        return 0;
    }
    return 1;
}

static int decision_node_code16x1_2(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_sub_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_3(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_cmp_4(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_4(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_and_3(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_5(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_or_3(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_6(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x0000c300) {
    case 0x00004000:
        if (decision_node_code16x1_7(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00004100:
        if (decision_node_code16x1_8(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00004200:
        if (decision_node_code16x1_9(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00004300:
        if (decision_node_code16x1_10(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code16x1_7(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_sub_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_8(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_cmp_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_9(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_add_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_10(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mul_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_11(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x0000c300) {
    case 0x00004000:
        if (decision_node_code16x1_12(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00004100:
        if (decision_node_code16x1_13(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00004200:
        if (decision_node_code16x1_14(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00004300:
        if (decision_node_code16x1_15(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code16x1_12(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_and_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_13(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_or_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_14(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mov_3(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_15(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_rtsd_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_16(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x0000c000) {
    case 0x00004000:
        if (decision_node_code16x1_17(context, code) == 0) {
            return 0;
        }
        break;
    case 0x0000c000:
        if (decision_node_code16x1_18(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code16x1_17(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_add_3(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_18(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000008) {
    case 0x00000008:
        if (decision_node_code16x1_19(context, code) == 0) {
            return 0;
        }
        break;
    }

    if (decision_node_code16x1_20(context, code) == 0) {
        return 0;
    }
    return 1;
}

static int decision_node_code16x1_19(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_bclr_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_20(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_bset_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_21(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x0000c000) {
    case 0x00004000:
        if (decision_node_code16x1_22(context, code) == 0) {
            return 0;
        }
        break;
    case 0x0000c000:
        if (decision_node_code16x1_27(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code16x1_22(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x000000f0) {
    case 0x00000000:
        if (decision_node_code16x1_23(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000010:
        if (decision_node_code16x1_24(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000020:
        if (decision_node_code16x1_25(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000030:
        if (decision_node_code16x1_26(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code16x1_23(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_cmp_3(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_24(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mul_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_25(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_and_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_26(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_or_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_27(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000008) {
    case 0x00000000:
        if (decision_node_code16x1_28(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000008:
        if (decision_node_code16x1_29(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code16x1_28(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_btst_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_29(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_push_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_30(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mov_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_31(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00003000) {
    case 0x00000000:
        if (decision_node_code16x1_32(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00001000:
        if (decision_node_code16x1_35(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00002000:
        if (decision_node_code16x1_36(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00003000:
        if (decision_node_code16x1_44(context, code) == 0) {
            return 0;
        }
        break;
    }

    if (decision_node_code16x1_101(context, code) == 0) {
        return 0;
    }
    return 1;
}

static int decision_node_code16x1_32(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x0000c400) {
    case 0x00004000:
        if (decision_node_code16x1_33(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00004400:
        if (decision_node_code16x1_34(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code16x1_33(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_add_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_34(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mul_3(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_35(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_movu_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_36(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x0000c600) {
    case 0x00000600:
        if (decision_node_code16x1_37(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00004000:
        if (decision_node_code16x1_38(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00004200:
        if (decision_node_code16x1_39(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00004400:
        if (decision_node_code16x1_40(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00004600:
        if (decision_node_code16x1_41(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code16x1_37(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_bra_b(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_38(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_shlr_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_39(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_shar_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_40(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_shll_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_41(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000100) {
    case 0x00000000:
        if (decision_node_code16x1_42(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000100:
        if (decision_node_code16x1_43(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code16x1_42(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_pushm(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_43(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_popm(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_44(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000100) {
    case 0x00000000:
        if (decision_node_code16x1_45(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000100:
        if (decision_node_code16x1_60(context, code) == 0) {
            return 0;
        }
        break;
    }

    if (decision_node_code16x1_94(context, code) == 0) {
        return 0;
    }
    return 1;
}

static int decision_node_code16x1_45(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x0000c6c0) {
    case 0x00004600:
        if (decision_node_code16x1_46(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00004640:
        if (decision_node_code16x1_51(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00004680:
        if (decision_node_code16x1_54(context, code) == 0) {
            return 0;
        }
        break;
    case 0x000046c0:
        if (decision_node_code16x1_57(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code16x1_46(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000030) {
    case 0x00000000:
        if (decision_node_code16x1_47(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000010:
        if (decision_node_code16x1_48(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000020:
        if (decision_node_code16x1_49(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000030:
        if (decision_node_code16x1_50(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code16x1_47(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_not_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_48(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_neg_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_49(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_abs_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_50(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_sat(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_51(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000030) {
    case 0x00000000:
        if (decision_node_code16x1_52(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000010:
        if (decision_node_code16x1_53(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code16x1_52(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_rorc(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_53(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_rolc(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_54(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000030) {
    case 0x00000030:
        if (decision_node_code16x1_55(context, code) == 0) {
            return 0;
        }
        break;
    }

    if (decision_node_code16x1_56(context, code) == 0) {
        return 0;
    }
    return 1;
}

static int decision_node_code16x1_55(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_pop(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_56(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_push_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_57(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000030) {
    case 0x00000000:
        if (decision_node_code16x1_58(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000020:
        if (decision_node_code16x1_59(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code16x1_58(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_pushc(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_59(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_popc(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_60(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x000000f0) {
    case 0x00000000:
        if (decision_node_code16x1_61(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000010:
        if (decision_node_code16x1_62(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000040:
        if (decision_node_code16x1_63(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000050:
        if (decision_node_code16x1_64(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000080:
        if (decision_node_code16x1_65(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000090:
        if (decision_node_code16x1_84(context, code) == 0) {
            return 0;
        }
        break;
    case 0x000000a0:
        if (decision_node_code16x1_89(context, code) == 0) {
            return 0;
        }
        break;
    case 0x000000b0:
        if (decision_node_code16x1_90(context, code) == 0) {
            return 0;
        }
        break;
    }

    if (decision_node_code16x1_91(context, code) == 0) {
        return 0;
    }
    return 1;
}

static int decision_node_code16x1_61(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_jmp(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_62(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_jsr(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_63(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_bra_l(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_64(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_bsr_l(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_65(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x0000c60c) {
    case 0x00004600:
        if (decision_node_code16x1_66(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00004604:
        if (decision_node_code16x1_71(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00004608:
        if (decision_node_code16x1_76(context, code) == 0) {
            return 0;
        }
        break;
    case 0x0000460c:
        if (decision_node_code16x1_81(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code16x1_66(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000003) {
    case 0x00000000:
        if (decision_node_code16x1_67(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000001:
        if (decision_node_code16x1_68(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000002:
        if (decision_node_code16x1_69(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000003:
        if (decision_node_code16x1_70(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code16x1_67(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_suntil_b(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_68(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_suntil_w(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_69(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_suntil_l(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_70(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_scmpu(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_71(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000003) {
    case 0x00000000:
        if (decision_node_code16x1_72(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000001:
        if (decision_node_code16x1_73(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000002:
        if (decision_node_code16x1_74(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000003:
        if (decision_node_code16x1_75(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code16x1_72(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_swhile_b(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_73(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_swhile_w(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_74(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_swhile_l(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_75(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_smovu(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_76(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000003) {
    case 0x00000000:
        if (decision_node_code16x1_77(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000001:
        if (decision_node_code16x1_78(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000002:
        if (decision_node_code16x1_79(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000003:
        if (decision_node_code16x1_80(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code16x1_77(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_sstr_b(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_78(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_sstr_w(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_79(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_sstr_l(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_80(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_smovb(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_81(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000003) {
    case 0x00000003:
        if (decision_node_code16x1_82(context, code) == 0) {
            return 0;
        }
        break;
    }

    if (decision_node_code16x1_83(context, code) == 0) {
        return 0;
    }
    return 1;
}

static int decision_node_code16x1_82(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_smovf(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_83(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_rmpa(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_84(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x0000c60f) {
    case 0x00004603:
        if (decision_node_code16x1_85(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00004604:
        if (decision_node_code16x1_86(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00004605:
        if (decision_node_code16x1_87(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00004606:
        if (decision_node_code16x1_88(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code16x1_85(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_satr(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_86(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_rtfi(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_87(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_rte(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_88(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_wait(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_89(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_setpsw(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_90(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_clrpsw(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_91(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x0000c600) {
    case 0x00000600:
        if (decision_node_code16x1_92(context, code) == 0) {
            return 0;
        }
        break;
    case 0x0000c200:
        if (decision_node_code16x1_93(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code16x1_92(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_rtsd_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_93(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mov_6(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_94(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x0000c400) {
    case 0x00000400:
        if (decision_node_code16x1_95(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00004000:
        if (decision_node_code16x1_96(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00004400:
        if (decision_node_code16x1_99(context, code) == 0) {
            return 0;
        }
        break;
    case 0x0000c000:
        if (decision_node_code16x1_100(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code16x1_95(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mov_4(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_96(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000200) {
    case 0x00000000:
        if (decision_node_code16x1_97(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000200:
        if (decision_node_code16x1_98(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code16x1_97(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_bset_3(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_98(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_bclr_3(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_99(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_btst_3(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_100(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mov_8(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_101(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x0000c000) {
    case 0x00008000:
        if (decision_node_code16x1_102(context, code) == 0) {
            return 0;
        }
        break;
    case 0x0000c000:
        if (decision_node_code16x1_103(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code16x1_102(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mov_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_103(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000400) {
    case 0x00000400:
        if (decision_node_code16x1_104(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code16x1_104(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000300) {
    case 0x00000300:
        if (decision_node_code16x1_105(context, code) == 0) {
            return 0;
        }
        break;
    }

    if (decision_node_code16x1_106(context, code) == 0) {
        return 0;
    }
    return 1;
}

static int decision_node_code16x1_105(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mov_7(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_106(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mov_9(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_107(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x0000c000) {
    case 0x00000000:
        if (decision_node_code16x1_108(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00008000:
        if (decision_node_code16x1_109(context, code) == 0) {
            return 0;
        }
        break;
    case 0x0000c000:
        if (decision_node_code16x1_110(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code16x1_108(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_bcnd_b(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_109(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_movu_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_110(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000300) {
    case 0x00000300:
        if (decision_node_code16x1_111(context, code) == 0) {
            return 0;
        }
        break;
    }

    if (decision_node_code16x1_112(context, code) == 0) {
        return 0;
    }
    return 1;
}

static int decision_node_code16x1_111(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mov_11(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code16x1_112(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mov_13(context) == 0) {
        return 0;
    }

    return 1;
}


static int decision_node_code24x1_0(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00010000) {
    case 0x00000000:
        if (decision_node_code24x1_1(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00010000:
        if (decision_node_code24x1_70(context, code) == 0) {
            return 0;
        }
        break;
    }

    if (decision_node_code24x1_168(context, code) == 0) {
        return 0;
    }
    return 1;
}

static int decision_node_code24x1_1(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00002000) {
    case 0x00000000:
        if (decision_node_code24x1_2(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00002000:
        if (decision_node_code24x1_42(context, code) == 0) {
            return 0;
        }
        break;
    }

    if (decision_node_code24x1_65(context, code) == 0) {
        return 0;
    }
    return 1;
}

static int decision_node_code24x1_2(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00001000) {
    case 0x00000000:
        if (decision_node_code24x1_3(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00001000:
        if (decision_node_code24x1_24(context, code) == 0) {
            return 0;
        }
        break;
    }

    if (decision_node_code24x1_41(context, code) == 0) {
        return 0;
    }
    return 1;
}

static int decision_node_code24x1_3(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00fe0c00) {
    case 0x00060000:
        if (decision_node_code24x1_4(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00060400:
        if (decision_node_code24x1_5(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00060800:
        if (decision_node_code24x1_6(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00060c00:
        if (decision_node_code24x1_7(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00fc0000:
        if (decision_node_code24x1_8(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00fc0400:
        if (decision_node_code24x1_12(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00fc0800:
        if (decision_node_code24x1_16(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00fc0c00:
        if (decision_node_code24x1_20(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_4(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_sub_2x(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_5(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_cmp_4x(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_6(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_add_2x(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_7(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mul_3x(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_8(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x0000c000) {
    case 0x00000000:
        if (decision_node_code24x1_9(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00004000:
        if (decision_node_code24x1_10(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00008000:
        if (decision_node_code24x1_11(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_9(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_sbb_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_10(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_xchg_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_11(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_fsub_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_12(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x0000c000) {
    case 0x00000000:
        if (decision_node_code24x1_13(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00004000:
        if (decision_node_code24x1_14(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00008000:
        if (decision_node_code24x1_15(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_13(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_neg_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_14(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_itof_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_15(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_fcmp_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_16(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x0000c000) {
    case 0x00000000:
        if (decision_node_code24x1_17(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00004000:
        if (decision_node_code24x1_18(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00008000:
        if (decision_node_code24x1_19(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_17(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_adc_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_18(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_stz_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_19(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_fadd_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_20(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x0000c000) {
    case 0x00000000:
        if (decision_node_code24x1_21(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00004000:
        if (decision_node_code24x1_22(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00008000:
        if (decision_node_code24x1_23(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_21(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_abs_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_22(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_stnz_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_23(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_fmul_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_24(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000c00) {
    case 0x00000000:
        if (decision_node_code24x1_25(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000400:
        if (decision_node_code24x1_30(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000800:
        if (decision_node_code24x1_36(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000c00:
        if (decision_node_code24x1_39(context, code) == 0) {
            return 0;
        }
        break;
    }

    if (decision_node_code24x1_40(context, code) == 0) {
        return 0;
    }
    return 1;
}

static int decision_node_code24x1_25(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00fe0000) {
    case 0x00060000:
        if (decision_node_code24x1_26(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00fc0000:
        if (decision_node_code24x1_27(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_26(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_and_3x(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_27(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x0000c000) {
    case 0x00000000:
        if (decision_node_code24x1_28(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00008000:
        if (decision_node_code24x1_29(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_28(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_max_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_29(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_fdiv_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_30(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00fe0000) {
    case 0x00060000:
        if (decision_node_code24x1_31(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00fc0000:
        if (decision_node_code24x1_32(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_31(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_or_3x(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_32(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x0000c000) {
    case 0x00000000:
        if (decision_node_code24x1_33(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00004000:
        if (decision_node_code24x1_34(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00008000:
        if (decision_node_code24x1_35(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_33(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_min_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_34(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_utof_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_35(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_ftoi(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_36(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00fec000) {
    case 0x00fc0000:
        if (decision_node_code24x1_37(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00fc8000:
        if (decision_node_code24x1_38(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_37(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_emul_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_38(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_round(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_39(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_emulu_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_40(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_sccnd(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_41(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_movu_3(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_42(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00fec000) {
    case 0x00068000:
        if (decision_node_code24x1_43(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00fc0000:
        if (decision_node_code24x1_44(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00fc4000:
        if (decision_node_code24x1_50(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00fc8000:
        if (decision_node_code24x1_59(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00fcc000:
        if (decision_node_code24x1_62(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_43(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_sbb_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_44(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00001c00) {
    case 0x00000000:
        if (decision_node_code24x1_45(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000400:
        if (decision_node_code24x1_46(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00001000:
        if (decision_node_code24x1_47(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00001400:
        if (decision_node_code24x1_48(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00001800:
        if (decision_node_code24x1_49(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_45(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_div_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_46(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_divu_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_47(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_tst_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_48(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_xor_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_49(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_not_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_50(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00001c00) {
    case 0x00000000:
        if (decision_node_code24x1_51(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000400:
        if (decision_node_code24x1_53(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000800:
        if (decision_node_code24x1_55(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000c00:
        if (decision_node_code24x1_57(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_51(OpDecodeContext *context, rx_uint32 code) {


    if (decision_node_code24x1_52(context, code) == 0) {
        return 0;
    }
    return 1;
}

static int decision_node_code24x1_52(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_bset_4(context) == 0) {
        return 0;
    }
    if (op_parse_bset_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_53(OpDecodeContext *context, rx_uint32 code) {


    if (decision_node_code24x1_54(context, code) == 0) {
        return 0;
    }
    return 1;
}

static int decision_node_code24x1_54(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_bclr_4(context) == 0) {
        return 0;
    }
    if (op_parse_bclr_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_55(OpDecodeContext *context, rx_uint32 code) {


    if (decision_node_code24x1_56(context, code) == 0) {
        return 0;
    }
    return 1;
}

static int decision_node_code24x1_56(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_btst_4(context) == 0) {
        return 0;
    }
    if (op_parse_btst_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_57(OpDecodeContext *context, rx_uint32 code) {


    if (decision_node_code24x1_58(context, code) == 0) {
        return 0;
    }
    return 1;
}

static int decision_node_code24x1_58(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_bnot_4(context) == 0) {
        return 0;
    }
    if (op_parse_bnot_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_59(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00001c00) {
    case 0x00000000:
        if (decision_node_code24x1_60(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000400:
        if (decision_node_code24x1_61(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_60(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_fsqrt(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_61(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_ftou(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_62(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x0000000f) {
    case 0x0000000f:
        if (decision_node_code24x1_63(context, code) == 0) {
            return 0;
        }
        break;
    }

    if (decision_node_code24x1_64(context, code) == 0) {
        return 0;
    }
    return 1;
}

static int decision_node_code24x1_63(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_bnot_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_64(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_bmcnd_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_65(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00fe0000) {
    case 0x00380000:
        if (decision_node_code24x1_66(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00fe0000:
        if (decision_node_code24x1_67(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_66(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_bra_w(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_67(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x0000c000) {
    case 0x00000000:
        if (decision_node_code24x1_68(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00004000:
        if (decision_node_code24x1_69(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_68(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mov_12(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_69(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mov_10(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_70(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x0000e000) {
    case 0x00000000:
        if (decision_node_code24x1_71(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00002000:
        if (decision_node_code24x1_97(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00004000:
        if (decision_node_code24x1_106(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00006000:
        if (decision_node_code24x1_116(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00008000:
        if (decision_node_code24x1_154(context, code) == 0) {
            return 0;
        }
        break;
    case 0x0000a000:
        if (decision_node_code24x1_157(context, code) == 0) {
            return 0;
        }
        break;
    case 0x0000c000:
        if (decision_node_code24x1_162(context, code) == 0) {
            return 0;
        }
        break;
    case 0x0000e000:
        if (decision_node_code24x1_163(context, code) == 0) {
            return 0;
        }
        break;
    }

    if (decision_node_code24x1_167(context, code) == 0) {
        return 0;
    }
    return 1;
}

static int decision_node_code24x1_71(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00fe1000) {
    case 0x00fc0000:
        if (decision_node_code24x1_72(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00fc1000:
        if (decision_node_code24x1_80(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00fe0000:
        if (decision_node_code24x1_96(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_72(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000700) {
    case 0x00000000:
        if (decision_node_code24x1_73(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000100:
        if (decision_node_code24x1_74(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000200:
        if (decision_node_code24x1_75(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000400:
        if (decision_node_code24x1_76(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000500:
        if (decision_node_code24x1_77(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000700:
        if (decision_node_code24x1_78(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_73(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mulhi(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_74(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mullo(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_75(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mullh(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_76(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_machi(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_77(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_maclo(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_78(OpDecodeContext *context, rx_uint32 code) {


    if (decision_node_code24x1_79(context, code) == 0) {
        return 0;
    }
    return 1;
}

static int decision_node_code24x1_79(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_emaca(context) == 0) {
        return 0;
    }
    if (op_parse_emula(context) == 0) {
        return 0;
    }
    if (op_parse_maclh(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_80(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000e20) {
    case 0x00000600:
        if (decision_node_code24x1_81(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000620:
        if (decision_node_code24x1_84(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000800:
        if (decision_node_code24x1_85(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000e00:
        if (decision_node_code24x1_90(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000e20:
        if (decision_node_code24x1_93(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_81(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000150) {
    case 0x00000100:
        if (decision_node_code24x1_82(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000110:
        if (decision_node_code24x1_83(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_82(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mvtachi(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_83(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mvtaclo(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_84(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mvtacgu(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_85(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x0000014f) {
    case 0x00000000:
        if (decision_node_code24x1_86(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000040:
        if (decision_node_code24x1_87(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000100:
        if (decision_node_code24x1_88(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000140:
        if (decision_node_code24x1_89(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_86(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_racw(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_87(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_rdacw(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_88(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_racl(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_89(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_rdacl(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_90(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000010) {
    case 0x00000000:
        if (decision_node_code24x1_91(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000010:
        if (decision_node_code24x1_92(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_91(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mvfachi(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_92(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mvfaclo(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_93(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000010) {
    case 0x00000000:
        if (decision_node_code24x1_94(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000010:
        if (decision_node_code24x1_95(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_94(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mvfacmi(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_95(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mvfacgu(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_96(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_sub_3(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_97(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00fe1000) {
    case 0x00fc0000:
        if (decision_node_code24x1_98(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00fc1000:
        if (decision_node_code24x1_103(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00fe0000:
        if (decision_node_code24x1_104(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00fe1000:
        if (decision_node_code24x1_105(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_98(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000f00) {
    case 0x00000700:
        if (decision_node_code24x1_99(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000f00:
        if (decision_node_code24x1_100(context, code) == 0) {
            return 0;
        }
        break;
    }

    if (decision_node_code24x1_101(context, code) == 0) {
        return 0;
    }
    return 1;
}

static int decision_node_code24x1_99(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_movco(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_100(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_movli(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_101(OpDecodeContext *context, rx_uint32 code) {


    if (decision_node_code24x1_102(context, code) == 0) {
        return 0;
    }
    return 1;
}

static int decision_node_code24x1_102(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mov_14(context) == 0) {
        return 0;
    }
    if (op_parse_mov_15(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_103(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_movu_4(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_104(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_add_4(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_105(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mul_4(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_106(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00fe1000) {
    case 0x00740000:
        if (decision_node_code24x1_107(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00741000:
        if (decision_node_code24x1_108(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00fc0000:
        if (decision_node_code24x1_109(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00fe0000:
        if (decision_node_code24x1_114(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00fe1000:
        if (decision_node_code24x1_115(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_107(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mov_5(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_108(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_cmp_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_109(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000700) {
    case 0x00000500:
        if (decision_node_code24x1_110(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000600:
        if (decision_node_code24x1_111(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000700:
        if (decision_node_code24x1_112(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_110(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_msblo(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_111(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_msblh(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_112(OpDecodeContext *context, rx_uint32 code) {


    if (decision_node_code24x1_113(context, code) == 0) {
        return 0;
    }
    return 1;
}

static int decision_node_code24x1_113(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_emsba(context) == 0) {
        return 0;
    }
    if (op_parse_msbhi(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_114(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_and_4(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_115(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_or_4(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_116(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00fe1200) {
    case 0x00740000:
        if (decision_node_code24x1_117(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00741000:
        if (decision_node_code24x1_118(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00fc0000:
        if (decision_node_code24x1_119(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00fc0200:
        if (decision_node_code24x1_128(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00fc1000:
        if (decision_node_code24x1_135(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00fc1200:
        if (decision_node_code24x1_147(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_117(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_int(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_118(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mvtipl(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_119(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000c00) {
    case 0x00000000:
        if (decision_node_code24x1_120(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000400:
        if (decision_node_code24x1_123(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000800:
        if (decision_node_code24x1_126(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000c00:
        if (decision_node_code24x1_127(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_120(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000100) {
    case 0x00000000:
        if (decision_node_code24x1_121(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000100:
        if (decision_node_code24x1_122(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_121(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_shlr_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_122(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_shar_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_123(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000100) {
    case 0x00000000:
        if (decision_node_code24x1_124(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000100:
        if (decision_node_code24x1_125(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_124(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_rotr_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_125(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_revw(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_126(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mvtc_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_127(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_rotr_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_128(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000c00) {
    case 0x00000000:
        if (decision_node_code24x1_129(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000400:
        if (decision_node_code24x1_130(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000800:
        if (decision_node_code24x1_133(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000c00:
        if (decision_node_code24x1_134(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_129(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_shll_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_130(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00000100) {
    case 0x00000000:
        if (decision_node_code24x1_131(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000100:
        if (decision_node_code24x1_132(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_131(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_rotl_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_132(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_revl(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_133(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mvfc(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_134(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_rotl_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_135(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x000001f0) {
    case 0x00000020:
        if (decision_node_code24x1_136(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000040:
        if (decision_node_code24x1_137(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000050:
        if (decision_node_code24x1_138(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000060:
        if (decision_node_code24x1_139(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000070:
        if (decision_node_code24x1_140(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000080:
        if (decision_node_code24x1_141(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000090:
        if (decision_node_code24x1_142(context, code) == 0) {
            return 0;
        }
        break;
    case 0x000000c0:
        if (decision_node_code24x1_143(context, code) == 0) {
            return 0;
        }
        break;
    case 0x000000d0:
        if (decision_node_code24x1_144(context, code) == 0) {
            return 0;
        }
        break;
    case 0x000000e0:
        if (decision_node_code24x1_145(context, code) == 0) {
            return 0;
        }
        break;
    case 0x000000f0:
        if (decision_node_code24x1_146(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_136(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_adc_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_137(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_max_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_138(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_min_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_139(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_emul_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_140(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_emulu_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_141(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_div_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_142(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_divu_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_143(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_tst_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_144(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_xor_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_145(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_stz_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_146(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_stnz_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_147(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x000001f0) {
    case 0x00000000:
        if (decision_node_code24x1_148(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000010:
        if (decision_node_code24x1_149(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000020:
        if (decision_node_code24x1_150(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000030:
        if (decision_node_code24x1_151(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000040:
        if (decision_node_code24x1_152(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00000100:
        if (decision_node_code24x1_153(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_148(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_fsub_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_149(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_fcmp_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_150(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_fadd_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_151(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_fmul_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_152(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_fdiv_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_153(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_mvtc_1(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_154(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00fe0000) {
    case 0x00fc0000:
        if (decision_node_code24x1_155(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00fe0000:
        if (decision_node_code24x1_156(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_155(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_shlr_3(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_156(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_fsub_3(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_157(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00fe0000) {
    case 0x00fc0000:
        if (decision_node_code24x1_158(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00fe0000:
        if (decision_node_code24x1_159(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_158(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_shar_3(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_159(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00001000) {
    case 0x00000000:
        if (decision_node_code24x1_160(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00001000:
        if (decision_node_code24x1_161(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_160(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_fadd_3(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_161(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_fmul_3(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_162(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_shll_3(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_163(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x00fe0000) {
    case 0x00fc0000:
        if (decision_node_code24x1_164(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code24x1_164(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x000000f0) {
    case 0x000000f0:
        if (decision_node_code24x1_165(context, code) == 0) {
            return 0;
        }
        break;
    }

    if (decision_node_code24x1_166(context, code) == 0) {
        return 0;
    }
    return 1;
}

static int decision_node_code24x1_165(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_bnot_3(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_166(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_bmcnd_2(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_167(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_bsr_w(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code24x1_168(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_bcnd_w(context) == 0) {
        return 0;
    }

    return 1;
}


static int decision_node_code32x1_0(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0x003cff00) {
    case 0x00200200:
        if (decision_node_code32x1_1(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00200400:
        if (decision_node_code32x1_2(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00200500:
        if (decision_node_code32x1_3(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00200600:
        if (decision_node_code32x1_4(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00200700:
        if (decision_node_code32x1_5(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00200800:
        if (decision_node_code32x1_6(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00200900:
        if (decision_node_code32x1_7(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00200c00:
        if (decision_node_code32x1_8(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00200d00:
        if (decision_node_code32x1_9(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00201000:
        if (decision_node_code32x1_10(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00201100:
        if (decision_node_code32x1_11(context, code) == 0) {
            return 0;
        }
        break;
    case 0x00201500:
        if (decision_node_code32x1_12(context, code) == 0) {
            return 0;
        }
        break;
    }

    if (decision_node_code32x1_13(context, code) == 0) {
        return 0;
    }
    return 1;
}

static int decision_node_code32x1_1(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_adc_3(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code32x1_2(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_max_2x(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code32x1_3(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_min_2x(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code32x1_4(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_emul_2x(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code32x1_5(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_emulu_2x(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code32x1_6(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_div_2x(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code32x1_7(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_divu_2x(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code32x1_8(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_tst_2x(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code32x1_9(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_xor_2x(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code32x1_10(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_xchg_1x(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code32x1_11(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_itof_1x(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code32x1_12(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_utof_1x(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code32x1_13(OpDecodeContext *context, rx_uint32 code) {

    switch (code & 0xff000000) {
    case 0x04000000:
        if (decision_node_code32x1_14(context, code) == 0) {
            return 0;
        }
        break;
    case 0x05000000:
        if (decision_node_code32x1_15(context, code) == 0) {
            return 0;
        }
        break;
    }

    return 1;
}

static int decision_node_code32x1_14(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_bra_a(context) == 0) {
        return 0;
    }

    return 1;
}

static int decision_node_code32x1_15(OpDecodeContext *context, rx_uint32 code) {

    if (op_parse_bsr_a(context) == 0) {
        return 0;
    }

    return 1;
}



/* op parse function */
int rx_op_parse(rx_uint16 code[RX_OP_DECODE_MAX], RxOpDecodedCodeType *decoded_code, RxOperationCodeType *optype) {
    OpDecodeContext context;
    context.code = &code[0];
    context.decoded_code = decoded_code;
    context.optype = optype;

    context.code32x1 = ((code[3] << 24) | (code[2] << 16) | (code[1] << 8) | code[0]);

    context.code24x1 = context.code32x1;
    context.code16x1 = context.code32x1;
    context.code8x1 = context.code32x1;

    if (decision_node_code8x1_0(&context, context.code8x1) == 0) {
        return 0;
    }

    if (decision_node_code16x1_0(&context, context.code16x1) == 0) {
        return 0;
    }

    if (decision_node_code24x1_0(&context, context.code24x1) == 0) {
        return 0;
    }

    if (decision_node_code32x1_0(&context, context.code32x1) == 0) {
        return 0;
    }

    return 1;
}

RxOpExecType rx_op_exec_table[RxOpCodeId_Num] = {
    { 1, rx_op_exec_brk },		/* brk */
    { 1, rx_op_exec_rts },		/* rts */
    { 1, rx_op_exec_nop },		/* nop */
    { 1, rx_op_exec_bra_a },		/* bra_a */
    { 1, rx_op_exec_bsr_a },		/* bsr_a */
    { 1, rx_op_exec_sub_2x },		/* sub_2x */
    { 1, rx_op_exec_cmp_4x },		/* cmp_4x */
    { 1, rx_op_exec_add_2x },		/* add_2x */
    { 1, rx_op_exec_mul_3x },		/* mul_3x */
    { 1, rx_op_exec_and_3x },		/* and_3x */
    { 1, rx_op_exec_or_3x },		/* or_3x */
    { 1, rx_op_exec_sbb_2 },		/* sbb_2 */
    { 1, rx_op_exec_adc_3 },		/* adc_3 */
    { 1, rx_op_exec_div_2x },		/* div_2x */
    { 1, rx_op_exec_divu_2x },		/* divu_2x */
    { 1, rx_op_exec_emul_2x },		/* emul_2x */
    { 1, rx_op_exec_emulu_2x },		/* emulu_2x */
    { 1, rx_op_exec_itof_1x },		/* itof_1x */
    { 1, rx_op_exec_max_2x },		/* max_2x */
    { 1, rx_op_exec_min_2x },		/* min_2x */
    { 1, rx_op_exec_tst_2x },		/* tst_2x */
    { 1, rx_op_exec_xchg_1x },		/* xchg_1x */
    { 1, rx_op_exec_xor_2x },		/* xor_2x */
    { 1, rx_op_exec_bra_s },		/* bra_s */
    { 1, rx_op_exec_bcnd_s },		/* bcnd_s */
    { 1, rx_op_exec_bra_b },		/* bra_b */
    { 1, rx_op_exec_bcnd_b },		/* bcnd_b */
    { 1, rx_op_exec_bra_w },		/* bra_w */
    { 1, rx_op_exec_bsr_w },		/* bsr_w */
    { 1, rx_op_exec_bcnd_w },		/* bcnd_w */
    { 1, rx_op_exec_rtsd_2 },		/* rtsd_2 */
    { 1, rx_op_exec_mov_4 },		/* mov_4 */
    { 1, rx_op_exec_sub_2 },		/* sub_2 */
    { 1, rx_op_exec_cmp_4 },		/* cmp_4 */
    { 1, rx_op_exec_add_2 },		/* add_2 */
    { 1, rx_op_exec_mul_3 },		/* mul_3 */
    { 1, rx_op_exec_and_3 },		/* and_3 */
    { 1, rx_op_exec_or_3 },		/* or_3 */
    { 1, rx_op_exec_movu_2 },		/* movu_2 */
    { 1, rx_op_exec_sub_1 },		/* sub_1 */
    { 1, rx_op_exec_cmp_1 },		/* cmp_1 */
    { 1, rx_op_exec_add_1 },		/* add_1 */
    { 1, rx_op_exec_mul_1 },		/* mul_1 */
    { 1, rx_op_exec_and_1 },		/* and_1 */
    { 1, rx_op_exec_or_1 },		/* or_1 */
    { 1, rx_op_exec_mov_3 },		/* mov_3 */
    { 1, rx_op_exec_rtsd_1 },		/* rtsd_1 */
    { 1, rx_op_exec_shlr_1 },		/* shlr_1 */
    { 1, rx_op_exec_shar_1 },		/* shar_1 */
    { 1, rx_op_exec_shll_1 },		/* shll_1 */
    { 1, rx_op_exec_pushm },		/* pushm */
    { 1, rx_op_exec_popm },		/* popm */
    { 1, rx_op_exec_add_3 },		/* add_3 */
    { 1, rx_op_exec_cmp_2 },		/* cmp_2 */
    { 1, rx_op_exec_int },		/* int */
    { 1, rx_op_exec_mov_5 },		/* mov_5 */
    { 1, rx_op_exec_mvtipl },		/* mvtipl */
    { 1, rx_op_exec_and_2 },		/* and_2 */
    { 1, rx_op_exec_cmp_3 },		/* cmp_3 */
    { 1, rx_op_exec_mul_2 },		/* mul_2 */
    { 1, rx_op_exec_or_2 },		/* or_2 */
    { 1, rx_op_exec_bset_3 },		/* bset_3 */
    { 1, rx_op_exec_bclr_3 },		/* bclr_3 */
    { 1, rx_op_exec_btst_3 },		/* btst_3 */
    { 1, rx_op_exec_abs_1 },		/* abs_1 */
    { 1, rx_op_exec_neg_1 },		/* neg_1 */
    { 1, rx_op_exec_not_1 },		/* not_1 */
    { 1, rx_op_exec_rolc },		/* rolc */
    { 1, rx_op_exec_pop },		/* pop */
    { 1, rx_op_exec_popc },		/* popc */
    { 1, rx_op_exec_rorc },		/* rorc */
    { 1, rx_op_exec_push_1 },		/* push_1 */
    { 1, rx_op_exec_pushc },		/* pushc */
    { 1, rx_op_exec_sat },		/* sat */
    { 1, rx_op_exec_jmp },		/* jmp */
    { 1, rx_op_exec_jsr },		/* jsr */
    { 1, rx_op_exec_bra_l },		/* bra_l */
    { 1, rx_op_exec_bsr_l },		/* bsr_l */
    { 1, rx_op_exec_scmpu },		/* scmpu */
    { 1, rx_op_exec_suntil_b },		/* suntil_b */
    { 1, rx_op_exec_suntil_w },		/* suntil_w */
    { 1, rx_op_exec_suntil_l },		/* suntil_l */
    { 1, rx_op_exec_smovu },		/* smovu */
    { 1, rx_op_exec_swhile_b },		/* swhile_b */
    { 1, rx_op_exec_swhile_w },		/* swhile_w */
    { 1, rx_op_exec_swhile_l },		/* swhile_l */
    { 1, rx_op_exec_smovb },		/* smovb */
    { 1, rx_op_exec_sstr_b },		/* sstr_b */
    { 1, rx_op_exec_sstr_w },		/* sstr_w */
    { 1, rx_op_exec_sstr_l },		/* sstr_l */
    { 1, rx_op_exec_smovf },		/* smovf */
    { 1, rx_op_exec_rmpa },		/* rmpa */
    { 1, rx_op_exec_satr },		/* satr */
    { 1, rx_op_exec_rtfi },		/* rtfi */
    { 1, rx_op_exec_rte },		/* rte */
    { 1, rx_op_exec_wait },		/* wait */
    { 1, rx_op_exec_setpsw },		/* setpsw */
    { 1, rx_op_exec_clrpsw },		/* clrpsw */
    { 1, rx_op_exec_movu_1 },		/* movu_1 */
    { 1, rx_op_exec_mov_1 },		/* mov_1 */
    { 1, rx_op_exec_mov_2 },		/* mov_2 */
    { 1, rx_op_exec_sbb_1 },		/* sbb_1 */
    { 1, rx_op_exec_neg_2 },		/* neg_2 */
    { 1, rx_op_exec_adc_2 },		/* adc_2 */
    { 1, rx_op_exec_abs_2 },		/* abs_2 */
    { 1, rx_op_exec_not_2 },		/* not_2 */
    { 1, rx_op_exec_bset_4 },		/* bset_4 */
    { 1, rx_op_exec_bclr_4 },		/* bclr_4 */
    { 1, rx_op_exec_btst_4 },		/* btst_4 */
    { 1, rx_op_exec_bnot_4 },		/* bnot_4 */
    { 1, rx_op_exec_max_2 },		/* max_2 */
    { 1, rx_op_exec_min_2 },		/* min_2 */
    { 1, rx_op_exec_emul_2 },		/* emul_2 */
    { 1, rx_op_exec_emulu_2 },		/* emulu_2 */
    { 1, rx_op_exec_div_2 },		/* div_2 */
    { 1, rx_op_exec_divu_2 },		/* divu_2 */
    { 1, rx_op_exec_tst_2 },		/* tst_2 */
    { 1, rx_op_exec_xor_2 },		/* xor_2 */
    { 1, rx_op_exec_xchg_1 },		/* xchg_1 */
    { 1, rx_op_exec_itof_1 },		/* itof_1 */
    { 1, rx_op_exec_bset_2 },		/* bset_2 */
    { 1, rx_op_exec_bclr_2 },		/* bclr_2 */
    { 1, rx_op_exec_btst_2 },		/* btst_2 */
    { 1, rx_op_exec_bnot_2 },		/* bnot_2 */
    { 1, rx_op_exec_fsub_2 },		/* fsub_2 */
    { 1, rx_op_exec_fcmp_2 },		/* fcmp_2 */
    { 1, rx_op_exec_fadd_2 },		/* fadd_2 */
    { 1, rx_op_exec_fmul_2 },		/* fmul_2 */
    { 1, rx_op_exec_fdiv_2 },		/* fdiv_2 */
    { 1, rx_op_exec_ftoi },		/* ftoi */
    { 1, rx_op_exec_round },		/* round */
    { 1, rx_op_exec_sccnd },		/* sccnd */
    { 1, rx_op_exec_bmcnd_1 },		/* bmcnd_1 */
    { 1, rx_op_exec_bnot_1 },		/* bnot_1 */
    { 1, rx_op_exec_shlr_3 },		/* shlr_3 */
    { 1, rx_op_exec_shar_3 },		/* shar_3 */
    { 1, rx_op_exec_shll_3 },		/* shll_3 */
    { 1, rx_op_exec_bmcnd_2 },		/* bmcnd_2 */
    { 1, rx_op_exec_bnot_3 },		/* bnot_3 */
    { 1, rx_op_exec_mulhi },		/* mulhi */
    { 1, rx_op_exec_mullo },		/* mullo */
    { 1, rx_op_exec_machi },		/* machi */
    { 1, rx_op_exec_maclo },		/* maclo */
    { 1, rx_op_exec_mvtachi },		/* mvtachi */
    { 1, rx_op_exec_mvtaclo },		/* mvtaclo */
    { 1, rx_op_exec_racw },		/* racw */
    { 1, rx_op_exec_mvfachi },		/* mvfachi */
    { 1, rx_op_exec_mvfacmi },		/* mvfacmi */
    { 1, rx_op_exec_mov_14 },		/* mov_14 */
    { 1, rx_op_exec_mov_15 },		/* mov_15 */
    { 1, rx_op_exec_movu_4 },		/* movu_4 */
    { 1, rx_op_exec_shlr_2 },		/* shlr_2 */
    { 1, rx_op_exec_shar_2 },		/* shar_2 */
    { 1, rx_op_exec_shll_2 },		/* shll_2 */
    { 1, rx_op_exec_rotr_2 },		/* rotr_2 */
    { 1, rx_op_exec_revw },		/* revw */
    { 1, rx_op_exec_rotl_2 },		/* rotl_2 */
    { 1, rx_op_exec_revl },		/* revl */
    { 1, rx_op_exec_mvtc_2 },		/* mvtc_2 */
    { 1, rx_op_exec_mvfc },		/* mvfc */
    { 1, rx_op_exec_rotr_1 },		/* rotr_1 */
    { 1, rx_op_exec_rotl_1 },		/* rotl_1 */
    { 1, rx_op_exec_fadd_1 },		/* fadd_1 */
    { 1, rx_op_exec_fcmp_1 },		/* fcmp_1 */
    { 1, rx_op_exec_fdiv_1 },		/* fdiv_1 */
    { 1, rx_op_exec_fmul_1 },		/* fmul_1 */
    { 1, rx_op_exec_fsub_1 },		/* fsub_1 */
    { 1, rx_op_exec_adc_1 },		/* adc_1 */
    { 1, rx_op_exec_div_1 },		/* div_1 */
    { 1, rx_op_exec_divu_1 },		/* divu_1 */
    { 1, rx_op_exec_emul_1 },		/* emul_1 */
    { 1, rx_op_exec_emulu_1 },		/* emulu_1 */
    { 1, rx_op_exec_max_1 },		/* max_1 */
    { 1, rx_op_exec_min_1 },		/* min_1 */
    { 1, rx_op_exec_stnz_1 },		/* stnz_1 */
    { 1, rx_op_exec_stz_1 },		/* stz_1 */
    { 1, rx_op_exec_tst_1 },		/* tst_1 */
    { 1, rx_op_exec_xor_1 },		/* xor_1 */
    { 1, rx_op_exec_mvtc_1 },		/* mvtc_1 */
    { 1, rx_op_exec_mov_10 },		/* mov_10 */
    { 1, rx_op_exec_mov_12 },		/* mov_12 */
    { 1, rx_op_exec_movu_3 },		/* movu_3 */
    { 1, rx_op_exec_add_4 },		/* add_4 */
    { 1, rx_op_exec_and_4 },		/* and_4 */
    { 1, rx_op_exec_mul_4 },		/* mul_4 */
    { 1, rx_op_exec_or_4 },		/* or_4 */
    { 1, rx_op_exec_sub_3 },		/* sub_3 */
    { 1, rx_op_exec_bclr_1 },		/* bclr_1 */
    { 1, rx_op_exec_bset_1 },		/* bset_1 */
    { 1, rx_op_exec_btst_1 },		/* btst_1 */
    { 1, rx_op_exec_push_2 },		/* push_2 */
    { 1, rx_op_exec_mov_6 },		/* mov_6 */
    { 1, rx_op_exec_mov_8 },		/* mov_8 */
    { 1, rx_op_exec_mov_7 },		/* mov_7 */
    { 1, rx_op_exec_mov_9 },		/* mov_9 */
    { 1, rx_op_exec_mov_11 },		/* mov_11 */
    { 1, rx_op_exec_mov_13 },		/* mov_13 */
    { 1, rx_op_exec_fsqrt },		/* fsqrt */
    { 1, rx_op_exec_ftou },		/* ftou */
    { 1, rx_op_exec_utof_1 },		/* utof_1 */
    { 1, rx_op_exec_utof_1x },		/* utof_1x */
    { 1, rx_op_exec_movco },		/* movco */
    { 1, rx_op_exec_movli },		/* movli */
    { 1, rx_op_exec_emaca },		/* emaca */
    { 1, rx_op_exec_emsba },		/* emsba */
    { 1, rx_op_exec_emula },		/* emula */
    { 1, rx_op_exec_maclh },		/* maclh */
    { 1, rx_op_exec_msbhi },		/* msbhi */
    { 1, rx_op_exec_msblh },		/* msblh */
    { 1, rx_op_exec_msblo },		/* msblo */
    { 1, rx_op_exec_mullh },		/* mullh */
    { 1, rx_op_exec_mvfacgu },		/* mvfacgu */
    { 1, rx_op_exec_mvfaclo },		/* mvfaclo */
    { 1, rx_op_exec_mvtacgu },		/* mvtacgu */
    { 1, rx_op_exec_racl },		/* racl */
    { 1, rx_op_exec_rdacl },		/* rdacl */
    { 1, rx_op_exec_rdacw },		/* rdacw */
    { 1, rx_op_exec_fadd_3 },		/* fadd_3 */
    { 1, rx_op_exec_fmul_3 },		/* fmul_3 */
    { 1, rx_op_exec_fsub_3 },		/* fsub_3 */
    { 1, rx_op_exec_stnz_2 },		/* stnz_2 */
    { 1, rx_op_exec_stz_2 },		/* stz_2 */
};