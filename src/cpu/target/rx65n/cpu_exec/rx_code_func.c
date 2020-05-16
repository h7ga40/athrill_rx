#include "cpu_exec/rx_code_debug.h"
#include "cpu_dec/rx_mcdecoder.h"
#include "target_cpu.h"
#include "bus.h"
#include "rx_code_func.h"

#define SET_TRI_REG(r1, r2, r3, v1, v2 ,v3) do { *r1 = v1; *r2 = v2; *r3 = v3; } while(0)

int MultiplyAccumulateB(struct TargetCore *core,
	unsigned long *R6, unsigned long *R5, unsigned long *R4,
	unsigned long *R1, unsigned long *R2)
{
	Std_ReturnType err;
	int8_t src1, src2;

	err = bus_get_data8(core->core_id, (uint32)R1, (uint8_t *)&src1);
	if (err != STD_E_OK) {
		return -1;
	}
	err = bus_get_data8(core->core_id, (uint32)R2, (uint8_t *)&src2);
	if (err != STD_E_OK) {
		return -1;
	}

	int64_t temp = (int64_t)src1 * (int64_t)src2;
	*R6 = temp >> 64;
	*R5 = temp >> 32;
	*R4 = temp;
}

int MultiplyAccumulateW(struct TargetCore *core,
	unsigned long *R6, unsigned long *R5, unsigned long *R4,
	unsigned long *R1, unsigned long *R2)
{
	Std_ReturnType err;
	int16_t src1, src2;

	err = bus_get_data16(core->core_id, (uint32)R1, (uint16_t *)&src1);
	if (err != STD_E_OK) {
		return -1;
	}
	err = bus_get_data16(core->core_id, (uint32)R2, (uint16_t *)&src2);
	if (err != STD_E_OK) {
		return -1;
	}

	int64_t temp = (int64_t)src1 * (int64_t)src2;
	*R6 = temp >> 64;
	*R5 = temp >> 32;
	*R4 = temp;
}

int MultiplyAccumulateL(struct TargetCore *core,
	unsigned long *R6, unsigned long *R5, unsigned long *R4,
	unsigned long *R1, unsigned long *R2)
{
	Std_ReturnType err;
	int32_t src1, src2;

	err = bus_get_data32(core->core_id, (uint32)R1, (uint32 *)&src1);
	if (err != STD_E_OK) {
		return -1;
	}
	err = bus_get_data32(core->core_id, (uint32)R2, (uint32 *)&src2);
	if (err != STD_E_OK) {
		return -1;
	}

	int64_t temp = (int64_t)src1 * (int64_t)src2;
	*R6 = temp >> 64;
	*R5 = temp >> 32;
	*R4 = temp;
}


int MultiplyAccumulate(struct TargetCore *core, OpSizeType sz,
	unsigned long *R6, unsigned long *R5, unsigned long *R4,
	unsigned long *R1, unsigned long *R2)
{
	switch (sz) {
	case OpSize_B:
		return MultiplyAccumulateB(core, R6, R5, R4, R1, R2);
	case OpSize_W:
		return MultiplyAccumulateW(core, R6, R5, R4, R1, R2);
	case OpSize_L:
		return MultiplyAccumulateL(core, R6, R5, R4, R1, R2);
	}
	return -1;
}

static uint32_t ReverseWordData(uint32_t src)
{
	return ((src & 0x00FF0000) << 8 /* >> 16 << 24 */)
		| ((src & 0xFF000000) >> 8 /* >> 24 << 16 */)
		| ((src & 0x000000FF) << 8 /* >> 0 << 8 */)
		| ((src & 0x0000FF00) >> 8 /* >> 8 << 0 */);
}

static uint32_t ReverseLongwordData(uint32_t src)
{
	return ((src & 0x000000FF) << 24 /* >> 0 << 24 */)
		| ((src & 0x0000FF00) << 8 /* >> 8 << 16 */)
		| ((src & 0x00FF0000) >> 8 /* >> 16 << 8 */)
		| ((src & 0xFF000000) >> 24 /* >> 24 << 0 */);
}

int rx_op_exec_brk(struct TargetCore *core)
{
	RxOpCodeFormatType_brk *op = &core->decoded_code.code.rx_brk;

	brk_input_type in;
	brk_output_type out;

	//TODO arguments setting..
	in.instrName = "BRK";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	Std_ReturnType err;
unsigned long tmp0, tmp1;
uint8_t *IntBase = core->int_base;

tmp0 = core->reg.psw.value;
core->reg.psw.u = 0;
core->reg.psw.i = 0;
core->reg.psw.pm = 0;
tmp1 = core->reg.pc + 1;
core->reg.pc = *IntBase;
core->reg.r[CpuRegId_SP] = core->reg.r[CpuRegId_SP] - 4;
err = bus_put_data32(core->core_id, core->reg.r[CpuRegId_SP], tmp0);
if (err != STD_E_OK) {
	return -1;
}

core->reg.r[CpuRegId_SP] = core->reg.r[CpuRegId_SP] - 4;
err = bus_put_data32(core->core_id, core->reg.r[CpuRegId_SP], tmp1);
if (err != STD_E_OK) {
	return -1;
}




	DBG_BRK(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_rts(struct TargetCore *core)
{
	RxOpCodeFormatType_rts *op = &core->decoded_code.code.rx_rts;

	rts_input_type in;
	rts_output_type out;

	//TODO arguments setting..
	in.instrName = "RTS";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	Std_ReturnType err;

err = bus_get_data32(core->core_id, core->reg.r[CpuRegId_SP], &core->reg.pc);
if (err != STD_E_OK) {
	return -1;
}

core->reg.r[CpuRegId_SP] = core->reg.r[CpuRegId_SP] + 4;



	DBG_RTS(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_nop(struct TargetCore *core)
{
	RxOpCodeFormatType_nop *op = &core->decoded_code.code.rx_nop;

	nop_input_type in;
	nop_output_type out;

	//TODO arguments setting..
	in.instrName = "NOP";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	
/* no operation */



	DBG_NOP(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_bra_a(struct TargetCore *core)
{
	RxOpCodeFormatType_bra_a *op = &core->decoded_code.code.rx_bra_a;

	bra_a_input_type in;
	bra_a_output_type out;

	//TODO arguments setting..
	in.instrName = "BRA_A";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->pcdsp];

core->reg.pc = core->reg.pc + src;



	DBG_BRA_A(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_bsr_a(struct TargetCore *core)
{
	RxOpCodeFormatType_bsr_a *op = &core->decoded_code.code.rx_bsr_a;

	bsr_a_input_type in;
	bsr_a_output_type out;

	//TODO arguments setting..
	in.instrName = "BSR_A";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	Std_ReturnType err;
uint32_t src = core->reg.r[op->pcdsp];

core->reg.r[CpuRegId_SP] = core->reg.r[CpuRegId_SP] - 4;
err = bus_put_data32(core->core_id, core->reg.r[CpuRegId_SP], (core->reg.pc + 4));
if (err != STD_E_OK) {
	return -1;
}

core->reg.pc = core->reg.pc + src;



	DBG_BSR_A(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_sub_2x(struct TargetCore *core)
{
	RxOpCodeFormatType_sub_2x *op = &core->decoded_code.code.rx_sub_2x;

	sub_2x_input_type in;
	sub_2x_output_type out;

	//TODO arguments setting..
	in.instrName = "SUB_2X";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	MemExType memex;
DispLenType ld;
uint32_t src = core->reg.r[op->rs];
uint32_t dest = core->reg.r[op->rd];

switch (op->mi) {
case 0: memex = MemEx_B; break;
case 1: memex = MemEx_W; break;
case 2: memex = MemEx_L; break;
case 3: memex = MemEx_UW; break;
default: return -1;
}
switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = dest - src;

core->reg.r[op->rd] = dest;


	DBG_SUB_2X(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_cmp_4x(struct TargetCore *core)
{
	RxOpCodeFormatType_cmp_4x *op = &core->decoded_code.code.rx_cmp_4x;

	cmp_4x_input_type in;
	cmp_4x_output_type out;

	//TODO arguments setting..
	in.instrName = "CMP_4X";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	MemExType memex;
DispLenType ld;
uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];

switch (op->mi) {
case 0: memex = MemEx_B; break;
case 1: memex = MemEx_W; break;
case 2: memex = MemEx_L; break;
case 3: memex = MemEx_UW; break;
default: return -1;
}
switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
src2 - src;



	DBG_CMP_4X(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_add_2x(struct TargetCore *core)
{
	RxOpCodeFormatType_add_2x *op = &core->decoded_code.code.rx_add_2x;

	add_2x_input_type in;
	add_2x_output_type out;

	//TODO arguments setting..
	in.instrName = "ADD_2X";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

dest = dest + src;

core->reg.r[op->rd] = dest;


	DBG_ADD_2X(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mul_3x(struct TargetCore *core)
{
	RxOpCodeFormatType_mul_3x *op = &core->decoded_code.code.rx_mul_3x;

	mul_3x_input_type in;
	mul_3x_output_type out;

	//TODO arguments setting..
	in.instrName = "MUL_3X";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	MemExType memex;
DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->mi) {
case 0: memex = MemEx_B; break;
case 1: memex = MemEx_W; break;
case 2: memex = MemEx_L; break;
case 3: memex = MemEx_UW; break;
default: return -1;
}
switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = src * dest;

core->reg.r[op->rd] = dest;


	DBG_MUL_3X(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_and_3x(struct TargetCore *core)
{
	RxOpCodeFormatType_and_3x *op = &core->decoded_code.code.rx_and_3x;

	and_3x_input_type in;
	and_3x_output_type out;

	//TODO arguments setting..
	in.instrName = "AND_3X";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = dest & src;

core->reg.r[op->rd] = dest;


	DBG_AND_3X(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_or_3x(struct TargetCore *core)
{
	RxOpCodeFormatType_or_3x *op = &core->decoded_code.code.rx_or_3x;

	or_3x_input_type in;
	or_3x_output_type out;

	//TODO arguments setting..
	in.instrName = "OR_3X";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	MemExType memex;
DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->mi) {
case 0: memex = MemEx_B; break;
case 1: memex = MemEx_W; break;
case 2: memex = MemEx_L; break;
case 3: memex = MemEx_UW; break;
default: return -1;
}
switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = dest | src;

core->reg.r[op->rd] = dest;


	DBG_OR_3X(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_sbb_2(struct TargetCore *core)
{
	RxOpCodeFormatType_sbb_2 *op = &core->decoded_code.code.rx_sbb_2;

	sbb_2_input_type in;
	sbb_2_output_type out;

	//TODO arguments setting..
	in.instrName = "SBB_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_none; break;
default: return -1;
}
dest = dest - src - !core->reg.psw.c;

core->reg.r[op->rd] = dest;


	DBG_SBB_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_adc_3(struct TargetCore *core)
{
	RxOpCodeFormatType_adc_3 *op = &core->decoded_code.code.rx_adc_3;

	adc_3_input_type in;
	adc_3_output_type out;

	//TODO arguments setting..
	in.instrName = "ADC_3";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	MemExType memex;
DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->mi) {
case 0: memex = MemEx_none; break;
case 1: memex = MemEx_none; break;
case 2: memex = MemEx_L; break;
case 3: memex = MemEx_none; break;
default: return -1;
}
switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_none; break;
default: return -1;
}
dest = dest + src + core->reg.psw.c;

core->reg.r[op->rd] = dest;


	DBG_ADC_3(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_div_2x(struct TargetCore *core)
{
	RxOpCodeFormatType_div_2x *op = &core->decoded_code.code.rx_div_2x;

	div_2x_input_type in;
	div_2x_output_type out;

	//TODO arguments setting..
	in.instrName = "DIV_2X";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	MemExType memex;
DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->mi) {
case 0: memex = MemEx_B; break;
case 1: memex = MemEx_W; break;
case 2: memex = MemEx_L; break;
case 3: memex = MemEx_UW; break;
default: return -1;
}
switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = dest / src;

core->reg.r[op->rd] = dest;


	DBG_DIV_2X(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_divu_2x(struct TargetCore *core)
{
	RxOpCodeFormatType_divu_2x *op = &core->decoded_code.code.rx_divu_2x;

	divu_2x_input_type in;
	divu_2x_output_type out;

	//TODO arguments setting..
	in.instrName = "DIVU_2X";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	MemExType memex;
DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->mi) {
case 0: memex = MemEx_B; break;
case 1: memex = MemEx_W; break;
case 2: memex = MemEx_L; break;
case 3: memex = MemEx_UW; break;
default: return -1;
}
switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = dest / src;

core->reg.r[op->rd] = dest;


	DBG_DIVU_2X(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_emul_2x(struct TargetCore *core)
{
	RxOpCodeFormatType_emul_2x *op = &core->decoded_code.code.rx_emul_2x;

	emul_2x_input_type in;
	emul_2x_output_type out;

	//TODO arguments setting..
	in.instrName = "EMUL_2X";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	MemExType memex;
DispLenType ld;
uint64_t dest64;
uint32_t dest = core->reg.r[op->rd];
uint32_t dest2 = core->reg.r[op->rd + 1];
uint32_t src = core->reg.r[op->rs];

switch (op->mi) {
case 0: memex = MemEx_B; break;
case 1: memex = MemEx_W; break;
case 2: memex = MemEx_L; break;
case 3: memex = MemEx_UW; break;
default: return -1;
}
switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest64 = dest * src;

core->reg.r[op->rd] = dest64 & 0xFFFFFFFF;
core->reg.r[op->rd + 1] = dest64 >> 32;


	DBG_EMUL_2X(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_emulu_2x(struct TargetCore *core)
{
	RxOpCodeFormatType_emulu_2x *op = &core->decoded_code.code.rx_emulu_2x;

	emulu_2x_input_type in;
	emulu_2x_output_type out;

	//TODO arguments setting..
	in.instrName = "EMULU_2X";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	MemExType memex;
DispLenType ld;
uint64_t dest64;
uint32_t dest = core->reg.r[op->rd];
uint32_t dest2 = core->reg.r[op->rd + 1];
uint32_t src = core->reg.r[op->rs];

switch (op->mi) {
case 0: memex = MemEx_B; break;
case 1: memex = MemEx_W; break;
case 2: memex = MemEx_L; break;
case 3: memex = MemEx_UW; break;
default: return -1;
}
switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest64 = dest * src;

core->reg.r[op->rd] = dest64 & 0xFFFFFFFF;
core->reg.r[op->rd + 1] = dest64 >> 32;


	DBG_EMULU_2X(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_itof_1x(struct TargetCore *core)
{
	RxOpCodeFormatType_itof_1x *op = &core->decoded_code.code.rx_itof_1x;

	itof_1x_input_type in;
	itof_1x_output_type out;

	//TODO arguments setting..
	in.instrName = "ITOF_1X";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	MemExType memex;
DispLenType ld;

switch (op->mi) {
case 0: memex = MemEx_B; break;
case 1: memex = MemEx_W; break;
case 2: memex = MemEx_L; break;
case 3: memex = MemEx_UW; break;
default: return -1;
}
switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}



	DBG_ITOF_1X(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_max_2x(struct TargetCore *core)
{
	RxOpCodeFormatType_max_2x *op = &core->decoded_code.code.rx_max_2x;

	max_2x_input_type in;
	max_2x_output_type out;

	//TODO arguments setting..
	in.instrName = "MAX_2X";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	MemExType memex;
DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->mi) {
case 0: memex = MemEx_B; break;
case 1: memex = MemEx_W; break;
case 2: memex = MemEx_L; break;
case 3: memex = MemEx_UW; break;
default: return -1;
}
switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
if (src > dest)
dest = src;

core->reg.r[op->rd] = dest;


	DBG_MAX_2X(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_min_2x(struct TargetCore *core)
{
	RxOpCodeFormatType_min_2x *op = &core->decoded_code.code.rx_min_2x;

	min_2x_input_type in;
	min_2x_output_type out;

	//TODO arguments setting..
	in.instrName = "MIN_2X";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	MemExType memex;
DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->mi) {
case 0: memex = MemEx_B; break;
case 1: memex = MemEx_W; break;
case 2: memex = MemEx_L; break;
case 3: memex = MemEx_UW; break;
default: return -1;
}
switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
if (src < dest)
dest = src;

core->reg.r[op->rd] = dest;


	DBG_MIN_2X(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_tst_2x(struct TargetCore *core)
{
	RxOpCodeFormatType_tst_2x *op = &core->decoded_code.code.rx_tst_2x;

	tst_2x_input_type in;
	tst_2x_output_type out;

	//TODO arguments setting..
	in.instrName = "TST_2X";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	MemExType memex;
DispLenType ld;
uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];

switch (op->mi) {
case 0: memex = MemEx_B; break;
case 1: memex = MemEx_W; break;
case 2: memex = MemEx_L; break;
case 3: memex = MemEx_UW; break;
default: return -1;
}
switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
src2 & src;



	DBG_TST_2X(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_xchg_1x(struct TargetCore *core)
{
	RxOpCodeFormatType_xchg_1x *op = &core->decoded_code.code.rx_xchg_1x;

	xchg_1x_input_type in;
	xchg_1x_output_type out;

	//TODO arguments setting..
	in.instrName = "XCHG_1X";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	unsigned long tmp;
MemExType memex;
DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->mi) {
case 0: memex = MemEx_B; break;
case 1: memex = MemEx_W; break;
case 2: memex = MemEx_L; break;
case 3: memex = MemEx_UW; break;
default: return -1;
}
switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
tmp = src;
src = dest;
dest = tmp;

core->reg.r[op->rd] = dest;


	DBG_XCHG_1X(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_xor_2x(struct TargetCore *core)
{
	RxOpCodeFormatType_xor_2x *op = &core->decoded_code.code.rx_xor_2x;

	xor_2x_input_type in;
	xor_2x_output_type out;

	//TODO arguments setting..
	in.instrName = "XOR_2X";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	MemExType memex;
DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->mi) {
case 0: memex = MemEx_B; break;
case 1: memex = MemEx_W; break;
case 2: memex = MemEx_L; break;
case 3: memex = MemEx_UW; break;
default: return -1;
}
switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = dest ^ src;

core->reg.r[op->rd] = dest;


	DBG_XOR_2X(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_bra_s(struct TargetCore *core)
{
	RxOpCodeFormatType_bra_s *op = &core->decoded_code.code.rx_bra_s;

	bra_s_input_type in;
	bra_s_output_type out;

	//TODO arguments setting..
	in.instrName = "BRA_S";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src;

switch (op->dsp) {
case 0: src = 8; break;
case 1: src = 9; break;
case 2: src = 10; break;
case 3: src = 3; break;
case 4: src = 4; break;
case 5: src = 5; break;
case 6: src = 6; break;
case 7: src = 7; break;
default: return -1;
}
core->reg.pc = core->reg.pc + src;



	DBG_BRA_S(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_bcnd_s(struct TargetCore *core)
{
	RxOpCodeFormatType_bcnd_s *op = &core->decoded_code.code.rx_bcnd_s;

	bcnd_s_input_type in;
	bcnd_s_output_type out;

	//TODO arguments setting..
	in.instrName = "BCND_S";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	bool Cnd;
uint32_t src;

switch (op->cd) {
case 0: Cnd = core->reg.psw.z == 1; break;
case 1: Cnd = core->reg.psw.z == 0; break;
default: return -1;
}
switch (op->dsp) {
case 0: src = 8; break;
case 1: src = 9; break;
case 2: src = 10; break;
case 3: src = 3; break;
case 4: src = 4; break;
case 5: src = 5; break;
case 6: src = 6; break;
case 7: src = 7; break;
default: return -1;
}
if (Cnd)
core->reg.pc = core->reg.pc + src;



	DBG_BCND_S(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_bra_b(struct TargetCore *core)
{
	RxOpCodeFormatType_bra_b *op = &core->decoded_code.code.rx_bra_b;

	bra_b_input_type in;
	bra_b_output_type out;

	//TODO arguments setting..
	in.instrName = "BRA_B";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->pcdsp];

core->reg.pc = core->reg.pc + src;



	DBG_BRA_B(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_bcnd_b(struct TargetCore *core)
{
	RxOpCodeFormatType_bcnd_b *op = &core->decoded_code.code.rx_bcnd_b;

	bcnd_b_input_type in;
	bcnd_b_output_type out;

	//TODO arguments setting..
	in.instrName = "BCND_B";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	bool Cnd;
uint32_t src = core->reg.r[op->pcdsp];

switch (op->cd) {
case 0: Cnd = core->reg.psw.z == 1; break;
case 1: Cnd = core->reg.psw.z == 0; break;
case 2: Cnd = core->reg.psw.c == 1; break;
case 3: Cnd = core->reg.psw.c == 0; break;
case 4: Cnd = core->reg.psw.s == 0; break;
case 5: Cnd = (core->reg.psw.c & ~core->reg.psw.z) == 0; break;
case 6: Cnd = core->reg.psw.s == 0; break;
case 7: Cnd = core->reg.psw.s == 1; break;
case 8: Cnd = (core->reg.psw.s ^ core->reg.psw.o) == 0; break;
case 9: Cnd = (core->reg.psw.s ^ core->reg.psw.o) == 1; break;
case 10: Cnd = ((core->reg.psw.s ^ core->reg.psw.o) | core->reg.psw.z) == 0; break;
case 11: Cnd = ((core->reg.psw.s ^ core->reg.psw.o) | core->reg.psw.z) == 1; break;
case 12: Cnd = core->reg.psw.o == 1; break;
case 13: Cnd = core->reg.psw.o == 0; break;
default: return -1;
}
if (Cnd)
core->reg.pc = core->reg.pc + src;



	DBG_BCND_B(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_bra_w(struct TargetCore *core)
{
	RxOpCodeFormatType_bra_w *op = &core->decoded_code.code.rx_bra_w;

	bra_w_input_type in;
	bra_w_output_type out;

	//TODO arguments setting..
	in.instrName = "BRA_W";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->pcdsp];

core->reg.pc = core->reg.pc + src;



	DBG_BRA_W(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_bsr_w(struct TargetCore *core)
{
	RxOpCodeFormatType_bsr_w *op = &core->decoded_code.code.rx_bsr_w;

	bsr_w_input_type in;
	bsr_w_output_type out;

	//TODO arguments setting..
	in.instrName = "BSR_W";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	Std_ReturnType err;
uint32_t src = core->reg.r[op->pcdsp];

core->reg.r[CpuRegId_SP] = core->reg.r[CpuRegId_SP] - 4;
err = bus_put_data32(core->core_id, core->reg.r[CpuRegId_SP], (core->reg.pc + 3));
if (err != STD_E_OK) {
	return -1;
}

core->reg.pc = core->reg.pc + src;



	DBG_BSR_W(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_bcnd_w(struct TargetCore *core)
{
	RxOpCodeFormatType_bcnd_w *op = &core->decoded_code.code.rx_bcnd_w;

	bcnd_w_input_type in;
	bcnd_w_output_type out;

	//TODO arguments setting..
	in.instrName = "BCND_W";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	bool Cnd;
uint32_t src = core->reg.r[op->pcdsp];

switch (op->cd) {
case 0: Cnd = core->reg.psw.z == 1; break;
case 1: Cnd = core->reg.psw.z == 0; break;
default: return -1;
}
if (Cnd)
core->reg.pc = core->reg.pc + src;



	DBG_BCND_W(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_rtsd_2(struct TargetCore *core)
{
	RxOpCodeFormatType_rtsd_2 *op = &core->decoded_code.code.rx_rtsd_2;

	rtsd_2_input_type in;
	rtsd_2_output_type out;

	//TODO arguments setting..
	in.instrName = "RTSD_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	Std_ReturnType err;
unsigned long tmp;
signed char i;
uint32_t dest = core->reg.r[op->rd];
uint32_t dest2 = core->reg.r[op->rd2];

uint32_t src = *(uint8_t *)&core->current_code[3];
core->reg.r[CpuRegId_SP] = core->reg.r[CpuRegId_SP] + ( src - ( op->rd2 - op->rd +1 ) * 4 );
for ( i = op->rd; i <= op->rd2; i++ ) {
err = bus_get_data32(core->core_id, core->reg.r[CpuRegId_SP], &tmp);
if (err != STD_E_OK) {
	return -1;
}

core->reg.r[CpuRegId_SP] = core->reg.r[CpuRegId_SP] + 4;
core->reg.r[i] = tmp;
}
err = bus_get_data32(core->core_id, core->reg.r[CpuRegId_SP], &core->reg.pc);
if (err != STD_E_OK) {
	return -1;
}

core->reg.r[CpuRegId_SP] = core->reg.r[CpuRegId_SP] + 4;



	DBG_RTSD_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mov_4(struct TargetCore *core)
{
	RxOpCodeFormatType_mov_4 *op = &core->decoded_code.code.rx_mov_4;

	mov_4_input_type in;
	mov_4_output_type out;

	//TODO arguments setting..
	in.instrName = "MOV_4";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->dsp];
uint32_t dest = core->reg.r[op->rd];

dest = src;

core->reg.r[op->rd] = dest;


	DBG_MOV_4(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_sub_2(struct TargetCore *core)
{
	RxOpCodeFormatType_sub_2 *op = &core->decoded_code.code.rx_sub_2;

	sub_2_input_type in;
	sub_2_output_type out;

	//TODO arguments setting..
	in.instrName = "SUB_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = dest - src;

core->reg.r[op->rd] = dest;


	DBG_SUB_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_cmp_4(struct TargetCore *core)
{
	RxOpCodeFormatType_cmp_4 *op = &core->decoded_code.code.rx_cmp_4;

	cmp_4_input_type in;
	cmp_4_output_type out;

	//TODO arguments setting..
	in.instrName = "CMP_4";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
src2 - src;



	DBG_CMP_4(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_add_2(struct TargetCore *core)
{
	RxOpCodeFormatType_add_2 *op = &core->decoded_code.code.rx_add_2;

	add_2_input_type in;
	add_2_output_type out;

	//TODO arguments setting..
	in.instrName = "ADD_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = dest + src;

core->reg.r[op->rd] = dest;


	DBG_ADD_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mul_3(struct TargetCore *core)
{
	RxOpCodeFormatType_mul_3 *op = &core->decoded_code.code.rx_mul_3;

	mul_3_input_type in;
	mul_3_output_type out;

	//TODO arguments setting..
	in.instrName = "MUL_3";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = src * dest;

core->reg.r[op->rd] = dest;


	DBG_MUL_3(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_and_3(struct TargetCore *core)
{
	RxOpCodeFormatType_and_3 *op = &core->decoded_code.code.rx_and_3;

	and_3_input_type in;
	and_3_output_type out;

	//TODO arguments setting..
	in.instrName = "AND_3";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = dest & src;

core->reg.r[op->rd] = dest;


	DBG_AND_3(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_or_3(struct TargetCore *core)
{
	RxOpCodeFormatType_or_3 *op = &core->decoded_code.code.rx_or_3;

	or_3_input_type in;
	or_3_output_type out;

	//TODO arguments setting..
	in.instrName = "OR_3";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = dest | src;

core->reg.r[op->rd] = dest;


	DBG_OR_3(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_movu_2(struct TargetCore *core)
{
	RxOpCodeFormatType_movu_2 *op = &core->decoded_code.code.rx_movu_2;

	movu_2_input_type in;
	movu_2_output_type out;

	//TODO arguments setting..
	in.instrName = "MOVU_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	OpSizeType sz;
DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->sz) {
case 0: sz = OpSize_B; break;
case 1: sz = OpSize_W; break;
default: return -1;
}
switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = src;

core->reg.r[op->rd] = dest;


	DBG_MOVU_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_sub_1(struct TargetCore *core)
{
	RxOpCodeFormatType_sub_1 *op = &core->decoded_code.code.rx_sub_1;

	sub_1_input_type in;
	sub_1_output_type out;

	//TODO arguments setting..
	in.instrName = "SUB_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->imm];
uint32_t dest = core->reg.r[op->rd];

dest = dest - src;

core->reg.r[op->rd] = dest;


	DBG_SUB_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_cmp_1(struct TargetCore *core)
{
	RxOpCodeFormatType_cmp_1 *op = &core->decoded_code.code.rx_cmp_1;

	cmp_1_input_type in;
	cmp_1_output_type out;

	//TODO arguments setting..
	in.instrName = "CMP_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->imm];
uint32_t src2 = core->reg.r[op->rs2];

src2 - src;



	DBG_CMP_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_add_1(struct TargetCore *core)
{
	RxOpCodeFormatType_add_1 *op = &core->decoded_code.code.rx_add_1;

	add_1_input_type in;
	add_1_output_type out;

	//TODO arguments setting..
	in.instrName = "ADD_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->imm];
uint32_t dest = core->reg.r[op->rd];

dest = dest + src;

core->reg.r[op->rd] = dest;


	DBG_ADD_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mul_1(struct TargetCore *core)
{
	RxOpCodeFormatType_mul_1 *op = &core->decoded_code.code.rx_mul_1;

	mul_1_input_type in;
	mul_1_output_type out;

	//TODO arguments setting..
	in.instrName = "MUL_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->imm];
uint32_t dest = core->reg.r[op->rd];

dest = src * dest;

core->reg.r[op->rd] = dest;


	DBG_MUL_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_and_1(struct TargetCore *core)
{
	RxOpCodeFormatType_and_1 *op = &core->decoded_code.code.rx_and_1;

	and_1_input_type in;
	and_1_output_type out;

	//TODO arguments setting..
	in.instrName = "AND_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->imm];
uint32_t dest = core->reg.r[op->rd];

dest = dest & src;

core->reg.r[op->rd] = dest;


	DBG_AND_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_or_1(struct TargetCore *core)
{
	RxOpCodeFormatType_or_1 *op = &core->decoded_code.code.rx_or_1;

	or_1_input_type in;
	or_1_output_type out;

	//TODO arguments setting..
	in.instrName = "OR_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->imm];
uint32_t dest = core->reg.r[op->rd];

dest = dest | src;

core->reg.r[op->rd] = dest;


	DBG_OR_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mov_3(struct TargetCore *core)
{
	RxOpCodeFormatType_mov_3 *op = &core->decoded_code.code.rx_mov_3;

	mov_3_input_type in;
	mov_3_output_type out;

	//TODO arguments setting..
	in.instrName = "MOV_3";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->imm];
uint32_t dest = core->reg.r[op->rd];

dest = src;

core->reg.r[op->rd] = dest;


	DBG_MOV_3(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_rtsd_1(struct TargetCore *core)
{
	RxOpCodeFormatType_rtsd_1 *op = &core->decoded_code.code.rx_rtsd_1;

	rtsd_1_input_type in;
	rtsd_1_output_type out;

	//TODO arguments setting..
	in.instrName = "RTSD_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	Std_ReturnType err;
uint32_t src = core->reg.r[op->uimm];

core->reg.r[CpuRegId_SP] = core->reg.r[CpuRegId_SP] + src;
err = bus_get_data32(core->core_id, core->reg.r[CpuRegId_SP], &core->reg.pc);
if (err != STD_E_OK) {
	return -1;
}

core->reg.r[CpuRegId_SP] = core->reg.r[CpuRegId_SP] + 4;



	DBG_RTSD_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_shlr_1(struct TargetCore *core)
{
	RxOpCodeFormatType_shlr_1 *op = &core->decoded_code.code.rx_shlr_1;

	shlr_1_input_type in;
	shlr_1_output_type out;

	//TODO arguments setting..
	in.instrName = "SHLR_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->imm];
uint32_t dest = core->reg.r[op->rd];

dest = (unsigned long)dest >> (src & 31);

core->reg.r[op->rd] = dest;


	DBG_SHLR_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_shar_1(struct TargetCore *core)
{
	RxOpCodeFormatType_shar_1 *op = &core->decoded_code.code.rx_shar_1;

	shar_1_input_type in;
	shar_1_output_type out;

	//TODO arguments setting..
	in.instrName = "SHAR_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->imm];
uint32_t dest = core->reg.r[op->rd];

dest = (signed long)dest >> (src & 31);

core->reg.r[op->rd] = dest;


	DBG_SHAR_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_shll_1(struct TargetCore *core)
{
	RxOpCodeFormatType_shll_1 *op = &core->decoded_code.code.rx_shll_1;

	shll_1_input_type in;
	shll_1_output_type out;

	//TODO arguments setting..
	in.instrName = "SHLL_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->imm];
uint32_t dest = core->reg.r[op->rd];

dest = dest << (src & 31);

core->reg.r[op->rd] = dest;


	DBG_SHLL_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_pushm(struct TargetCore *core)
{
	RxOpCodeFormatType_pushm *op = &core->decoded_code.code.rx_pushm;

	pushm_input_type in;
	pushm_output_type out;

	//TODO arguments setting..
	in.instrName = "PUSHM";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	Std_ReturnType err;
unsigned long tmp;
signed char i;
uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];

for ( i = op->rs2; i >= op->rs; i-- ) {
tmp = core->reg.r[i];
core->reg.r[CpuRegId_SP] = core->reg.r[CpuRegId_SP] - 4;
err = bus_put_data32(core->core_id, core->reg.r[CpuRegId_SP], tmp);
if (err != STD_E_OK) {
	return -1;
}

}



	DBG_PUSHM(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_popm(struct TargetCore *core)
{
	RxOpCodeFormatType_popm *op = &core->decoded_code.code.rx_popm;

	popm_input_type in;
	popm_output_type out;

	//TODO arguments setting..
	in.instrName = "POPM";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	Std_ReturnType err;
unsigned long tmp;
signed char i;
uint32_t dest = core->reg.r[op->rd];
uint32_t dest2 = core->reg.r[op->rd2];

for ( i = op->rd; i <= op->rd2; i++ ) {
err = bus_get_data32(core->core_id, core->reg.r[CpuRegId_SP], &tmp);
if (err != STD_E_OK) {
	return -1;
}

core->reg.r[CpuRegId_SP] = core->reg.r[CpuRegId_SP] + 4;
core->reg.r[i] = tmp;
}



	DBG_POPM(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_add_3(struct TargetCore *core)
{
	RxOpCodeFormatType_add_3 *op = &core->decoded_code.code.rx_add_3;

	add_3_input_type in;
	add_3_output_type out;

	//TODO arguments setting..
	in.instrName = "ADD_3";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	ImLenType li;
uint32_t dest = core->reg.r[op->rd];
uint32_t src2 = core->reg.r[op->rs2];

switch (op->li) {
case 0: li = ImLen_imm32; break;
case 1: li = ImLen_simm8; break;
case 2: li = ImLen_simm16; break;
case 3: li = ImLen_simm24; break;
default: return -1;
}
int im_len = 0;
switch (li) {
case ImLen_imm32: im_len = 4; break;
case ImLen_simm8: im_len = 1; break;
case ImLen_simm16: im_len = 2; break;
case ImLen_simm24: im_len = 3; break;
}
uint32_t src = *(uint8_t *)&core->current_code[3 + im_len];
dest = src2 + src;

core->reg.r[op->rd] = dest;


	DBG_ADD_3(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_cmp_2(struct TargetCore *core)
{
	RxOpCodeFormatType_cmp_2 *op = &core->decoded_code.code.rx_cmp_2;

	cmp_2_input_type in;
	cmp_2_output_type out;

	//TODO arguments setting..
	in.instrName = "CMP_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->uimm];
uint32_t src2 = core->reg.r[op->rs2];

src2 - src;



	DBG_CMP_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_int(struct TargetCore *core)
{
	RxOpCodeFormatType_int *op = &core->decoded_code.code.rx_int;

	int_input_type in;
	int_output_type out;

	//TODO arguments setting..
	in.instrName = "INT";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	Std_ReturnType err;
unsigned long tmp0, tmp1;
uint32_t src = core->reg.r[op->imm];
uint8_t *IntBase = core->int_base;

tmp0 = core->reg.psw.value;
core->reg.psw.u = 0;
core->reg.psw.i = 0;
core->reg.psw.pm = 0;
tmp1 = core->reg.pc + 3;
core->reg.pc = *(IntBase + src * 4);
core->reg.r[CpuRegId_SP] = core->reg.r[CpuRegId_SP] - 4;
err = bus_put_data32(core->core_id, core->reg.r[CpuRegId_SP], tmp0);
if (err != STD_E_OK) {
	return -1;
}

core->reg.r[CpuRegId_SP] = core->reg.r[CpuRegId_SP] - 4;
err = bus_put_data32(core->core_id, core->reg.r[CpuRegId_SP], tmp1);
if (err != STD_E_OK) {
	return -1;
}




	DBG_INT(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mov_5(struct TargetCore *core)
{
	RxOpCodeFormatType_mov_5 *op = &core->decoded_code.code.rx_mov_5;

	mov_5_input_type in;
	mov_5_output_type out;

	//TODO arguments setting..
	in.instrName = "MOV_5";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->uimm];
uint32_t dest = core->reg.r[op->rd];

dest = src;

core->reg.r[op->rd] = dest;


	DBG_MOV_5(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mvtipl(struct TargetCore *core)
{
	RxOpCodeFormatType_mvtipl *op = &core->decoded_code.code.rx_mvtipl;

	mvtipl_input_type in;
	mvtipl_output_type out;

	//TODO arguments setting..
	in.instrName = "MVTIPL";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->imm];

core->reg.psw.ipl = src;



	DBG_MVTIPL(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_and_2(struct TargetCore *core)
{
	RxOpCodeFormatType_and_2 *op = &core->decoded_code.code.rx_and_2;

	and_2_input_type in;
	and_2_output_type out;

	//TODO arguments setting..
	in.instrName = "AND_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	ImLenType li;
uint32_t dest = core->reg.r[op->rd];

switch (op->li) {
case 0: li = ImLen_imm32; break;
case 1: li = ImLen_simm8; break;
case 2: li = ImLen_simm16; break;
case 3: li = ImLen_simm24; break;
default: return -1;
}
int im_len = 0;
switch (li) {
case ImLen_imm32: im_len = 4; break;
case ImLen_simm8: im_len = 1; break;
case ImLen_simm16: im_len = 2; break;
case ImLen_simm24: im_len = 3; break;
}
uint32_t src = *(uint8_t *)&core->current_code[3 + im_len];
dest = dest & src;

core->reg.r[op->rd] = dest;


	DBG_AND_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_cmp_3(struct TargetCore *core)
{
	RxOpCodeFormatType_cmp_3 *op = &core->decoded_code.code.rx_cmp_3;

	cmp_3_input_type in;
	cmp_3_output_type out;

	//TODO arguments setting..
	in.instrName = "CMP_3";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	ImLenType li;
uint32_t src2 = core->reg.r[op->rs2];

switch (op->li) {
case 0: li = ImLen_imm32; break;
case 1: li = ImLen_simm8; break;
case 2: li = ImLen_simm16; break;
case 3: li = ImLen_simm24; break;
default: return -1;
}
int im_len = 0;
switch (li) {
case ImLen_imm32: im_len = 4; break;
case ImLen_simm8: im_len = 1; break;
case ImLen_simm16: im_len = 2; break;
case ImLen_simm24: im_len = 3; break;
}
uint32_t src = *(uint8_t *)&core->current_code[3 + im_len];
src2 - src;



	DBG_CMP_3(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mul_2(struct TargetCore *core)
{
	RxOpCodeFormatType_mul_2 *op = &core->decoded_code.code.rx_mul_2;

	mul_2_input_type in;
	mul_2_output_type out;

	//TODO arguments setting..
	in.instrName = "MUL_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	ImLenType li;
uint32_t dest = core->reg.r[op->rd];

switch (op->li) {
case 0: li = ImLen_imm32; break;
case 1: li = ImLen_simm8; break;
case 2: li = ImLen_simm16; break;
case 3: li = ImLen_simm24; break;
default: return -1;
}
int im_len = 0;
switch (li) {
case ImLen_imm32: im_len = 4; break;
case ImLen_simm8: im_len = 1; break;
case ImLen_simm16: im_len = 2; break;
case ImLen_simm24: im_len = 3; break;
}
uint32_t src = *(uint8_t *)&core->current_code[3 + im_len];
dest = src * dest;

core->reg.r[op->rd] = dest;


	DBG_MUL_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_or_2(struct TargetCore *core)
{
	RxOpCodeFormatType_or_2 *op = &core->decoded_code.code.rx_or_2;

	or_2_input_type in;
	or_2_output_type out;

	//TODO arguments setting..
	in.instrName = "OR_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	ImLenType li;
uint32_t dest = core->reg.r[op->rd];

switch (op->li) {
case 0: li = ImLen_imm32; break;
case 1: li = ImLen_simm8; break;
case 2: li = ImLen_simm16; break;
case 3: li = ImLen_simm24; break;
default: return -1;
}
int im_len = 0;
switch (li) {
case ImLen_imm32: im_len = 4; break;
case ImLen_simm8: im_len = 1; break;
case ImLen_simm16: im_len = 2; break;
case ImLen_simm24: im_len = 3; break;
}
uint32_t src = *(uint8_t *)&core->current_code[3 + im_len];
dest = dest | src;

core->reg.r[op->rd] = dest;


	DBG_OR_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_bset_3(struct TargetCore *core)
{
	RxOpCodeFormatType_bset_3 *op = &core->decoded_code.code.rx_bset_3;

	bset_3_input_type in;
	bset_3_output_type out;

	//TODO arguments setting..
	in.instrName = "BSET_3";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->imm];
uint32_t dest = core->reg.r[op->rd];

dest |= (1 << (src & 7));

core->reg.r[op->rd] = dest;


	DBG_BSET_3(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_bclr_3(struct TargetCore *core)
{
	RxOpCodeFormatType_bclr_3 *op = &core->decoded_code.code.rx_bclr_3;

	bclr_3_input_type in;
	bclr_3_output_type out;

	//TODO arguments setting..
	in.instrName = "BCLR_3";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->imm];
uint32_t dest = core->reg.r[op->rd];

dest &= ~(1 << (src & 7));

core->reg.r[op->rd] = dest;


	DBG_BCLR_3(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_btst_3(struct TargetCore *core)
{
	RxOpCodeFormatType_btst_3 *op = &core->decoded_code.code.rx_btst_3;

	btst_3_input_type in;
	btst_3_output_type out;

	//TODO arguments setting..
	in.instrName = "BTST_3";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->imm];
uint32_t src2 = core->reg.r[op->rs2];

core->reg.psw.z = ~((src2 >> (src & 7)) & 1);
core->reg.psw.c = ((src2 >> (src & 7)) & 1);



	DBG_BTST_3(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_abs_1(struct TargetCore *core)
{
	RxOpCodeFormatType_abs_1 *op = &core->decoded_code.code.rx_abs_1;

	abs_1_input_type in;
	abs_1_output_type out;

	//TODO arguments setting..
	in.instrName = "ABS_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	int32_t dest = core->reg.r[op->rd];

if (dest < 0)
dest = -dest;

core->reg.r[op->rd] = dest;


	DBG_ABS_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_neg_1(struct TargetCore *core)
{
	RxOpCodeFormatType_neg_1 *op = &core->decoded_code.code.rx_neg_1;

	neg_1_input_type in;
	neg_1_output_type out;

	//TODO arguments setting..
	in.instrName = "NEG_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	int32_t dest = core->reg.r[op->rd];

dest = -dest;

core->reg.r[op->rd] = dest;


	DBG_NEG_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_not_1(struct TargetCore *core)
{
	RxOpCodeFormatType_not_1 *op = &core->decoded_code.code.rx_not_1;

	not_1_input_type in;
	not_1_output_type out;

	//TODO arguments setting..
	in.instrName = "NOT_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];

dest = ~dest;

core->reg.r[op->rd] = dest;


	DBG_NOT_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_rolc(struct TargetCore *core)
{
	RxOpCodeFormatType_rolc *op = &core->decoded_code.code.rx_rolc;

	rolc_input_type in;
	rolc_output_type out;

	//TODO arguments setting..
	in.instrName = "ROLC";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];

dest <<= 1;
if ( core->reg.psw.c == 0 ) { dest &= 0xFFFFFFFE; }
else { dest |= 0x00000001; }

core->reg.r[op->rd] = dest;


	DBG_ROLC(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_pop(struct TargetCore *core)
{
	RxOpCodeFormatType_pop *op = &core->decoded_code.code.rx_pop;

	pop_input_type in;
	pop_output_type out;

	//TODO arguments setting..
	in.instrName = "POP";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	Std_ReturnType err;
unsigned long tmp;
uint32_t dest = core->reg.r[op->rd];

err = bus_get_data32(core->core_id, core->reg.r[CpuRegId_SP], &tmp);
if (err != STD_E_OK) {
	return -1;
}

core->reg.r[CpuRegId_SP] = core->reg.r[CpuRegId_SP] + 4;
dest = tmp;

core->reg.r[op->rd] = dest;


	DBG_POP(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_popc(struct TargetCore *core)
{
	RxOpCodeFormatType_popc *op = &core->decoded_code.code.rx_popc;

	popc_input_type in;
	popc_output_type out;

	//TODO arguments setting..
	in.instrName = "POPC";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	Std_ReturnType err;
unsigned long tmp;
CtrlRegType cr;

switch (op->cr) {
case 0: cr = CtrlReg_PSW; break;
case 1: cr = CtrlReg_none; break;
case 2: cr = CtrlReg_USP; break;
case 3: cr = CtrlReg_FPSW; break;
case 4: cr = CtrlReg_none; break;
case 5: cr = CtrlReg_none; break;
case 6: cr = CtrlReg_none; break;
case 7: cr = CtrlReg_none; break;
case 8: cr = CtrlReg_BPSW; break;
case 9: cr = CtrlReg_BPC; break;
case 10: cr = CtrlReg_ISP; break;
case 11: cr = CtrlReg_FINTV; break;
case 12: cr = CtrlReg_INTB; break;
case 13: cr = CtrlReg_EXTB; break;
case 14: cr = CtrlReg_none; break;
case 15: cr = CtrlReg_none; break;
default: return -1;
}
uint32_t dest;
switch (cr) {
case CtrlReg_PSW: dest = core->reg.psw.value; break;
case CtrlReg_USP: dest = core->reg.usp; break;
case CtrlReg_FPSW: dest = core->reg.fpsw; break;
case CtrlReg_BPSW: dest = core->reg.bpsw.value; break;
case CtrlReg_BPC: dest = core->reg.bpc; break;
case CtrlReg_ISP: dest = core->reg.isp; break;
case CtrlReg_FINTV: dest = core->reg.fintv; break;
case CtrlReg_INTB: dest = core->reg.intb; break;
case CtrlReg_EXTB: dest = core->reg.extb; break;
}
err = bus_get_data32(core->core_id, core->reg.r[CpuRegId_SP], &tmp);
if (err != STD_E_OK) {
	return -1;
}

core->reg.r[CpuRegId_SP] = core->reg.r[CpuRegId_SP] + 4;
dest = tmp;

switch (cr) {
case CtrlReg_PSW: core->reg.psw.value = dest; break;
case CtrlReg_USP: core->reg.usp = dest; break;
case CtrlReg_FPSW: core->reg.fpsw = dest; break;
case CtrlReg_BPSW: core->reg.bpsw.value = dest; break;
case CtrlReg_BPC: core->reg.bpc = dest; break;
case CtrlReg_ISP: core->reg.isp = dest; break;
case CtrlReg_FINTV: core->reg.fintv = dest; break;
case CtrlReg_INTB: core->reg.intb = dest; break;
case CtrlReg_EXTB: core->reg.extb = dest; break;
}


	DBG_POPC(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_rorc(struct TargetCore *core)
{
	RxOpCodeFormatType_rorc *op = &core->decoded_code.code.rx_rorc;

	rorc_input_type in;
	rorc_output_type out;

	//TODO arguments setting..
	in.instrName = "RORC";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];

dest >>= 1;
if ( core->reg.psw.c == 0 ) { dest &= 0x7FFFFFFF; }
else { dest |= 0x80000000; }

core->reg.r[op->rd] = dest;


	DBG_RORC(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_push_1(struct TargetCore *core)
{
	RxOpCodeFormatType_push_1 *op = &core->decoded_code.code.rx_push_1;

	push_1_input_type in;
	push_1_output_type out;

	//TODO arguments setting..
	in.instrName = "PUSH_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	Std_ReturnType err;
unsigned long tmp;
uint32_t src = core->reg.r[op->rs];

tmp = src;
core->reg.r[CpuRegId_SP] = core->reg.r[CpuRegId_SP] - 4;
err = bus_put_data32(core->core_id, core->reg.r[CpuRegId_SP], tmp);
if (err != STD_E_OK) {
	return -1;
}




	DBG_PUSH_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_pushc(struct TargetCore *core)
{
	RxOpCodeFormatType_pushc *op = &core->decoded_code.code.rx_pushc;

	pushc_input_type in;
	pushc_output_type out;

	//TODO arguments setting..
	in.instrName = "PUSHC";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	Std_ReturnType err;
unsigned long tmp;
CtrlRegType cr;

switch (op->cr) {
case 0: cr = CtrlReg_PSW; break;
case 1: cr = CtrlReg_none; break;
case 2: cr = CtrlReg_USP; break;
case 3: cr = CtrlReg_FPSW; break;
case 4: cr = CtrlReg_none; break;
case 5: cr = CtrlReg_none; break;
case 6: cr = CtrlReg_none; break;
case 7: cr = CtrlReg_none; break;
case 8: cr = CtrlReg_BPSW; break;
case 9: cr = CtrlReg_BPC; break;
case 10: cr = CtrlReg_ISP; break;
case 11: cr = CtrlReg_FINTV; break;
case 12: cr = CtrlReg_INTB; break;
case 13: cr = CtrlReg_EXTB; break;
case 14: cr = CtrlReg_none; break;
case 15: cr = CtrlReg_none; break;
default: return -1;
}
uint32_t src;
switch (cr) {
case CtrlReg_PSW: src = core->reg.psw.value; break;
case CtrlReg_USP: src = core->reg.usp; break;
case CtrlReg_FPSW: src = core->reg.fpsw; break;
case CtrlReg_BPSW: src = core->reg.bpsw.value; break;
case CtrlReg_BPC: src = core->reg.bpc; break;
case CtrlReg_ISP: src = core->reg.isp; break;
case CtrlReg_FINTV: src = core->reg.fintv; break;
case CtrlReg_INTB: src = core->reg.intb; break;
case CtrlReg_EXTB: src = core->reg.extb; break;
}
tmp = src;
core->reg.r[CpuRegId_SP] = core->reg.r[CpuRegId_SP] - 4;
err = bus_put_data32(core->core_id, core->reg.r[CpuRegId_SP], tmp);
if (err != STD_E_OK) {
	return -1;
}


switch (cr) {
case CtrlReg_PSW: core->reg.psw.value = src; break;
case CtrlReg_USP: core->reg.usp = src; break;
case CtrlReg_FPSW: core->reg.fpsw = src; break;
case CtrlReg_BPSW: core->reg.bpsw.value = src; break;
case CtrlReg_BPC: core->reg.bpc = src; break;
case CtrlReg_ISP: core->reg.isp = src; break;
case CtrlReg_FINTV: core->reg.fintv = src; break;
case CtrlReg_INTB: core->reg.intb = src; break;
case CtrlReg_EXTB: core->reg.extb = src; break;
}


	DBG_PUSHC(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_sat(struct TargetCore *core)
{
	RxOpCodeFormatType_sat *op = &core->decoded_code.code.rx_sat;

	sat_input_type in;
	sat_output_type out;

	//TODO arguments setting..
	in.instrName = "SAT";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];

if (core->reg.psw.o == 1 && core->reg.psw.s == 1)
dest = 0x7FFFFFFF;
else if (core->reg.psw.o == 1 && core->reg.psw.s == 0)
dest = 0x80000000;

core->reg.r[op->rd] = dest;


	DBG_SAT(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_jmp(struct TargetCore *core)
{
	RxOpCodeFormatType_jmp *op = &core->decoded_code.code.rx_jmp;

	jmp_input_type in;
	jmp_output_type out;

	//TODO arguments setting..
	in.instrName = "JMP";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->rs];

core->reg.pc = src;



	DBG_JMP(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_jsr(struct TargetCore *core)
{
	RxOpCodeFormatType_jsr *op = &core->decoded_code.code.rx_jsr;

	jsr_input_type in;
	jsr_output_type out;

	//TODO arguments setting..
	in.instrName = "JSR";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	Std_ReturnType err;
uint32_t src = core->reg.r[op->rs];

core->reg.r[CpuRegId_SP] = core->reg.r[CpuRegId_SP] - 4;
err = bus_put_data32(core->core_id, core->reg.r[CpuRegId_SP], (core->reg.pc + 2));
if (err != STD_E_OK) {
	return -1;
}

core->reg.pc = src;



	DBG_JSR(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_bra_l(struct TargetCore *core)
{
	RxOpCodeFormatType_bra_l *op = &core->decoded_code.code.rx_bra_l;

	bra_l_input_type in;
	bra_l_output_type out;

	//TODO arguments setting..
	in.instrName = "BRA_L";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->rs];

core->reg.pc = core->reg.pc + src;



	DBG_BRA_L(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_bsr_l(struct TargetCore *core)
{
	RxOpCodeFormatType_bsr_l *op = &core->decoded_code.code.rx_bsr_l;

	bsr_l_input_type in;
	bsr_l_output_type out;

	//TODO arguments setting..
	in.instrName = "BSR_L";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	Std_ReturnType err;
uint32_t src = core->reg.r[op->rs];

core->reg.r[CpuRegId_SP] = core->reg.r[CpuRegId_SP] - 4;
err = bus_put_data32(core->core_id, core->reg.r[CpuRegId_SP], (core->reg.pc + 2));
if (err != STD_E_OK) {
	return -1;
}

core->reg.pc = core->reg.pc + src;



	DBG_BSR_L(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_scmpu(struct TargetCore *core)
{
	RxOpCodeFormatType_scmpu *op = &core->decoded_code.code.rx_scmpu;

	scmpu_input_type in;
	scmpu_output_type out;

	//TODO arguments setting..
	in.instrName = "SCMPU";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	unsigned char *R2, *R1, tmp0, tmp1;
unsigned long R3;

R1 = core->reg.r[1];
R3 = core->reg.r[3];
R2 = core->reg.r[2];
while (R3 != 0) {
tmp0 = *R1++;
tmp1 = *R2++;
R3--;
if (tmp0 != tmp1 || tmp0 == '\0') {
break;
}
}

core->reg.r[1] = R1;
core->reg.r[3] = R3;
core->reg.r[2] = R2;


	DBG_SCMPU(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_suntil_b(struct TargetCore *core)
{
	RxOpCodeFormatType_suntil_b *op = &core->decoded_code.code.rx_suntil_b;

	suntil_b_input_type in;
	suntil_b_output_type out;

	//TODO arguments setting..
	in.instrName = "SUNTIL_B";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	unsigned char *R1;
unsigned long R2, R3, tmp;

R1 = core->reg.r[1];
R3 = core->reg.r[3];
R2 = core->reg.r[2];
while (R3 != 0) {
tmp = (unsigned long) *R1++;
R3--;
if (tmp == R2) {
break;
}
}

core->reg.r[1] = R1;
core->reg.r[3] = R3;
core->reg.r[2] = R2;


	DBG_SUNTIL_B(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_suntil_w(struct TargetCore *core)
{
	RxOpCodeFormatType_suntil_w *op = &core->decoded_code.code.rx_suntil_w;

	suntil_w_input_type in;
	suntil_w_output_type out;

	//TODO arguments setting..
	in.instrName = "SUNTIL_W";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	unsigned short *R1;
unsigned long R2, R3, tmp;

R1 = core->reg.r[1];
R3 = core->reg.r[3];
R2 = core->reg.r[2];
while (R3 != 0) {
tmp = (unsigned long) *R1++;
R3--;
if (tmp == R2) {
break;
}
}

core->reg.r[1] = R1;
core->reg.r[3] = R3;
core->reg.r[2] = R2;


	DBG_SUNTIL_W(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_suntil_l(struct TargetCore *core)
{
	RxOpCodeFormatType_suntil_l *op = &core->decoded_code.code.rx_suntil_l;

	suntil_l_input_type in;
	suntil_l_output_type out;

	//TODO arguments setting..
	in.instrName = "SUNTIL_L";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	unsigned long *R1;
unsigned long R2, R3, tmp;

R1 = core->reg.r[1];
R3 = core->reg.r[3];
R2 = core->reg.r[2];
while (R3 != 0) {
tmp = (unsigned long) *R1++;
R3--;
if (tmp == R2) {
break;
}
}

core->reg.r[1] = R1;
core->reg.r[3] = R3;
core->reg.r[2] = R2;


	DBG_SUNTIL_L(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_smovu(struct TargetCore *core)
{
	RxOpCodeFormatType_smovu *op = &core->decoded_code.code.rx_smovu;

	smovu_input_type in;
	smovu_output_type out;

	//TODO arguments setting..
	in.instrName = "SMOVU";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	unsigned char *R1, *R2, tmp;
unsigned long R3;

R1 = core->reg.r[1];
R3 = core->reg.r[3];
R2 = core->reg.r[2];
while (R3 != 0) {
tmp = *R2++;
*R1++ = tmp;
R3--;
if (tmp == '\0') {
break;
}
}

core->reg.r[1] = R1;
core->reg.r[3] = R3;
core->reg.r[2] = R2;


	DBG_SMOVU(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_swhile_b(struct TargetCore *core)
{
	RxOpCodeFormatType_swhile_b *op = &core->decoded_code.code.rx_swhile_b;

	swhile_b_input_type in;
	swhile_b_output_type out;

	//TODO arguments setting..
	in.instrName = "SWHILE_B";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	unsigned char *R1;
unsigned long R2, R3, tmp;

R1 = core->reg.r[1];
R3 = core->reg.r[3];
R2 = core->reg.r[2];
while (R3 != 0) {
tmp = (unsigned long)*R1++;
R3--;
if (tmp != R2) {
break;
}
}

core->reg.r[1] = R1;
core->reg.r[3] = R3;
core->reg.r[2] = R2;


	DBG_SWHILE_B(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_swhile_w(struct TargetCore *core)
{
	RxOpCodeFormatType_swhile_w *op = &core->decoded_code.code.rx_swhile_w;

	swhile_w_input_type in;
	swhile_w_output_type out;

	//TODO arguments setting..
	in.instrName = "SWHILE_W";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	unsigned short *R1;
unsigned long R2, R3, tmp;

R1 = core->reg.r[1];
R3 = core->reg.r[3];
R2 = core->reg.r[2];
while (R3 != 0) {
tmp = (unsigned long)*R1++;
R3--;
if (tmp != R2) {
break;
}
}

core->reg.r[1] = R1;
core->reg.r[3] = R3;
core->reg.r[2] = R2;


	DBG_SWHILE_W(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_swhile_l(struct TargetCore *core)
{
	RxOpCodeFormatType_swhile_l *op = &core->decoded_code.code.rx_swhile_l;

	swhile_l_input_type in;
	swhile_l_output_type out;

	//TODO arguments setting..
	in.instrName = "SWHILE_L";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	unsigned long *R1;
unsigned long R2, R3, tmp;

R1 = core->reg.r[1];
R3 = core->reg.r[3];
R2 = core->reg.r[2];
while (R3 != 0) {
tmp = (unsigned long)*R1++;
R3--;
if (tmp != R2) {
break;
}
}

core->reg.r[1] = R1;
core->reg.r[3] = R3;
core->reg.r[2] = R2;


	DBG_SWHILE_L(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_smovb(struct TargetCore *core)
{
	RxOpCodeFormatType_smovb *op = &core->decoded_code.code.rx_smovb;

	smovb_input_type in;
	smovb_output_type out;

	//TODO arguments setting..
	in.instrName = "SMOVB";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	unsigned char *R1, *R2;
unsigned long R3;

R1 = core->reg.r[1];
R3 = core->reg.r[3];
R2 = core->reg.r[2];
while (R3 != 0) {
*R1-- = *R2--;
R3 = R3 - 1;
}

core->reg.r[1] = R1;
core->reg.r[3] = R3;
core->reg.r[2] = R2;


	DBG_SMOVB(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_sstr_b(struct TargetCore *core)
{
	RxOpCodeFormatType_sstr_b *op = &core->decoded_code.code.rx_sstr_b;

	sstr_b_input_type in;
	sstr_b_output_type out;

	//TODO arguments setting..
	in.instrName = "SSTR_B";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	unsigned char *R1, R2;
unsigned long R3;

R1 = core->reg.r[1];
R3 = core->reg.r[3];
R2 = core->reg.r[2];
while (R3 != 0) {
*R1++ = R2;
R3 = R3 - 1;
}

core->reg.r[1] = R1;
core->reg.r[3] = R3;
core->reg.r[2] = R2;


	DBG_SSTR_B(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_sstr_w(struct TargetCore *core)
{
	RxOpCodeFormatType_sstr_w *op = &core->decoded_code.code.rx_sstr_w;

	sstr_w_input_type in;
	sstr_w_output_type out;

	//TODO arguments setting..
	in.instrName = "SSTR_W";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	unsigned short *R1, R2;
unsigned long R3;

R1 = core->reg.r[1];
R3 = core->reg.r[3];
R2 = core->reg.r[2];
while (R3 != 0) {
*R1++ = R2;
R3 = R3 - 1;
}

core->reg.r[1] = R1;
core->reg.r[3] = R3;
core->reg.r[2] = R2;


	DBG_SSTR_W(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_sstr_l(struct TargetCore *core)
{
	RxOpCodeFormatType_sstr_l *op = &core->decoded_code.code.rx_sstr_l;

	sstr_l_input_type in;
	sstr_l_output_type out;

	//TODO arguments setting..
	in.instrName = "SSTR_L";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	unsigned long *R1, R2;
unsigned long R3;

R1 = core->reg.r[1];
R3 = core->reg.r[3];
R2 = core->reg.r[2];
while (R3 != 0) {
*R1++ = R2;
R3 = R3 - 1;
}

core->reg.r[1] = R1;
core->reg.r[3] = R3;
core->reg.r[2] = R2;


	DBG_SSTR_L(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_smovf(struct TargetCore *core)
{
	RxOpCodeFormatType_smovf *op = &core->decoded_code.code.rx_smovf;

	smovf_input_type in;
	smovf_output_type out;

	//TODO arguments setting..
	in.instrName = "SMOVF";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	unsigned char *R1, *R2;
unsigned long R3;

R1 = core->reg.r[1];
R3 = core->reg.r[3];
R2 = core->reg.r[2];
while ( R3 != 0 ) {
*R1++ = *R2++;
R3 = R3 - 1;
}

core->reg.r[1] = R1;
core->reg.r[3] = R3;
core->reg.r[2] = R2;


	DBG_SMOVF(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_rmpa(struct TargetCore *core)
{
	RxOpCodeFormatType_rmpa *op = &core->decoded_code.code.rx_rmpa;

	rmpa_input_type in;
	rmpa_output_type out;

	//TODO arguments setting..
	in.instrName = "RMPA";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	unsigned long *R1, *R2;
unsigned long R3, R4, R5, R6;
OpSizeType n;

switch (op->sz) {
case 0: n = OpSize_B; break;
case 1: n = OpSize_L; break;
case 2: n = OpSize_W; break;
case 3: n = OpSize_none; break;
default: return -1;
}
R3 = core->reg.r[3];
R4 = core->reg.r[4];
R5 = core->reg.r[5];
R6 = core->reg.r[6];
R1 = core->reg.r[1];
R2 = core->reg.r[2];
while (R3 != 0) {
MultiplyAccumulate(core, op->sz, &R6, &R5, &R4, R1, R2);
R1 = R1 + n;
R2 = R2 + n;
R3 = R3 - 1;
}

core->reg.r[3] = R3;
core->reg.r[4] = R4;
core->reg.r[5] = R5;
core->reg.r[6] = R6;
core->reg.r[1] = R1;
core->reg.r[2] = R2;


	DBG_RMPA(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_satr(struct TargetCore *core)
{
	RxOpCodeFormatType_satr *op = &core->decoded_code.code.rx_satr;

	satr_input_type in;
	satr_output_type out;

	//TODO arguments setting..
	in.instrName = "SATR";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	unsigned long R3, R4, R5, R6;

R4 = core->reg.r[4];
R5 = core->reg.r[5];
R6 = core->reg.r[6];
if ( core->reg.psw.o == 1 && core->reg.psw.s == 0 )
SET_TRI_REG(&R6, &R5, &R4, 0x00000000, 0x7FFFFFFF, 0xFFFFFFFF);
else if ( core->reg.psw.o == 1 && core->reg.psw.s == 1 )
SET_TRI_REG(&R6, &R5, &R4, 0xFFFFFFFF, 0x80000000, 0x00000000);

core->reg.r[4] = R4;
core->reg.r[5] = R5;
core->reg.r[6] = R6;


	DBG_SATR(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_rtfi(struct TargetCore *core)
{
	RxOpCodeFormatType_rtfi *op = &core->decoded_code.code.rx_rtfi;

	rtfi_input_type in;
	rtfi_output_type out;

	//TODO arguments setting..
	in.instrName = "RTFI";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	
core->reg.psw.value = core->reg.bpsw.value;
core->reg.pc = core->reg.bpc;
core->li = 0;



	DBG_RTFI(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_rte(struct TargetCore *core)
{
	RxOpCodeFormatType_rte *op = &core->decoded_code.code.rx_rte;

	rte_input_type in;
	rte_output_type out;

	//TODO arguments setting..
	in.instrName = "RTE";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	Std_ReturnType err;
unsigned long tmp;

err = bus_get_data32(core->core_id, core->reg.r[CpuRegId_SP], &core->reg.pc);
if (err != STD_E_OK) {
	return -1;
}

core->reg.r[CpuRegId_SP] = core->reg.r[CpuRegId_SP] + 4;
err = bus_get_data32(core->core_id, core->reg.r[CpuRegId_SP], &tmp);
if (err != STD_E_OK) {
	return -1;
}

core->reg.r[CpuRegId_SP] = core->reg.r[CpuRegId_SP] + 4;
core->reg.psw.value = tmp;
core->li = 0;



	DBG_RTE(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_wait(struct TargetCore *core)
{
	RxOpCodeFormatType_wait *op = &core->decoded_code.code.rx_wait;

	wait_input_type in;
	wait_output_type out;

	//TODO arguments setting..
	in.instrName = "WAIT";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	
/* wait */



	DBG_WAIT(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_setpsw(struct TargetCore *core)
{
	RxOpCodeFormatType_setpsw *op = &core->decoded_code.code.rx_setpsw;

	setpsw_input_type in;
	setpsw_output_type out;

	//TODO arguments setting..
	in.instrName = "SETPSW";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	PswFlagType cb;

switch (op->cb) {
case 0: cb = PswFlag_C; break;
case 1: cb = PswFlag_Z; break;
case 2: cb = PswFlag_S; break;
case 3: cb = PswFlag_O; break;
case 4: cb = PswFlag_none; break;
case 5: cb = PswFlag_none; break;
case 6: cb = PswFlag_none; break;
case 7: cb = PswFlag_none; break;
case 8: cb = PswFlag_I; break;
case 9: cb = PswFlag_U; break;
default: return -1;
}
uint32_t dest;
switch (cb) {
case PswFlag_C: dest = core->reg.psw.c; break;
case PswFlag_Z: dest = core->reg.psw.z; break;
case PswFlag_S: dest = core->reg.psw.s; break;
case PswFlag_O: dest = core->reg.psw.o; break;
case PswFlag_I: dest = core->reg.psw.i; break;
case PswFlag_U: dest = core->reg.psw.u; break;
}
dest = 1;

switch (cb) {
case PswFlag_C: core->reg.psw.c = dest; break;
case PswFlag_Z: core->reg.psw.z = dest; break;
case PswFlag_S: core->reg.psw.s = dest; break;
case PswFlag_O: core->reg.psw.o = dest; break;
case PswFlag_I: core->reg.psw.i = dest; break;
case PswFlag_U: core->reg.psw.u = dest; break;
}


	DBG_SETPSW(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_clrpsw(struct TargetCore *core)
{
	RxOpCodeFormatType_clrpsw *op = &core->decoded_code.code.rx_clrpsw;

	clrpsw_input_type in;
	clrpsw_output_type out;

	//TODO arguments setting..
	in.instrName = "CLRPSW";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	PswFlagType cb;

switch (op->cb) {
case 0: cb = PswFlag_C; break;
case 1: cb = PswFlag_Z; break;
case 2: cb = PswFlag_S; break;
case 3: cb = PswFlag_O; break;
case 4: cb = PswFlag_none; break;
case 5: cb = PswFlag_none; break;
case 6: cb = PswFlag_none; break;
case 7: cb = PswFlag_none; break;
case 8: cb = PswFlag_I; break;
case 9: cb = PswFlag_U; break;
default: return -1;
}
uint32_t dest;
switch (cb) {
case PswFlag_C: dest = core->reg.psw.c; break;
case PswFlag_Z: dest = core->reg.psw.z; break;
case PswFlag_S: dest = core->reg.psw.s; break;
case PswFlag_O: dest = core->reg.psw.o; break;
case PswFlag_I: dest = core->reg.psw.i; break;
case PswFlag_U: dest = core->reg.psw.u; break;
}
dest = 0;

switch (cb) {
case PswFlag_C: core->reg.psw.c = dest; break;
case PswFlag_Z: core->reg.psw.z = dest; break;
case PswFlag_S: core->reg.psw.s = dest; break;
case PswFlag_O: core->reg.psw.o = dest; break;
case PswFlag_I: core->reg.psw.i = dest; break;
case PswFlag_U: core->reg.psw.u = dest; break;
}


	DBG_CLRPSW(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_movu_1(struct TargetCore *core)
{
	RxOpCodeFormatType_movu_1 *op = &core->decoded_code.code.rx_movu_1;

	movu_1_input_type in;
	movu_1_output_type out;

	//TODO arguments setting..
	in.instrName = "MOVU_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

dest = src;

core->reg.r[op->rd] = dest;


	DBG_MOVU_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mov_1(struct TargetCore *core)
{
	RxOpCodeFormatType_mov_1 *op = &core->decoded_code.code.rx_mov_1;

	mov_1_input_type in;
	mov_1_output_type out;

	//TODO arguments setting..
	in.instrName = "MOV_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

dest = src;

core->reg.r[op->rd] = dest;


	DBG_MOV_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mov_2(struct TargetCore *core)
{
	RxOpCodeFormatType_mov_2 *op = &core->decoded_code.code.rx_mov_2;

	mov_2_input_type in;
	mov_2_output_type out;

	//TODO arguments setting..
	in.instrName = "MOV_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

dest = src;

core->reg.r[op->rd] = dest;


	DBG_MOV_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_sbb_1(struct TargetCore *core)
{
	RxOpCodeFormatType_sbb_1 *op = &core->decoded_code.code.rx_sbb_1;

	sbb_1_input_type in;
	sbb_1_output_type out;

	//TODO arguments setting..
	in.instrName = "SBB_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_none; break;
case 1: ld = DispLen_none; break;
case 2: ld = DispLen_none; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = dest - src - !core->reg.psw.c;

core->reg.r[op->rd] = dest;


	DBG_SBB_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_neg_2(struct TargetCore *core)
{
	RxOpCodeFormatType_neg_2 *op = &core->decoded_code.code.rx_neg_2;

	neg_2_input_type in;
	neg_2_output_type out;

	//TODO arguments setting..
	in.instrName = "NEG_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	int32_t src = core->reg.r[op->rs];
int32_t dest = core->reg.r[op->rd];

dest = -src;

core->reg.r[op->rd] = dest;


	DBG_NEG_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_adc_2(struct TargetCore *core)
{
	RxOpCodeFormatType_adc_2 *op = &core->decoded_code.code.rx_adc_2;

	adc_2_input_type in;
	adc_2_output_type out;

	//TODO arguments setting..
	in.instrName = "ADC_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_none; break;
case 1: ld = DispLen_none; break;
case 2: ld = DispLen_none; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = dest + src + core->reg.psw.c;

core->reg.r[op->rd] = dest;


	DBG_ADC_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_abs_2(struct TargetCore *core)
{
	RxOpCodeFormatType_abs_2 *op = &core->decoded_code.code.rx_abs_2;

	abs_2_input_type in;
	abs_2_output_type out;

	//TODO arguments setting..
	in.instrName = "ABS_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	int32_t src = core->reg.r[op->rs];
int32_t dest = core->reg.r[op->rd];

if (src < 0)
dest = -src;
else
dest = src;

core->reg.r[op->rd] = dest;


	DBG_ABS_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_not_2(struct TargetCore *core)
{
	RxOpCodeFormatType_not_2 *op = &core->decoded_code.code.rx_not_2;

	not_2_input_type in;
	not_2_output_type out;

	//TODO arguments setting..
	in.instrName = "NOT_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

dest = ~src;

core->reg.r[op->rd] = dest;


	DBG_NOT_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_bset_4(struct TargetCore *core)
{
	RxOpCodeFormatType_bset_4 *op = &core->decoded_code.code.rx_bset_4;

	bset_4_input_type in;
	bset_4_output_type out;

	//TODO arguments setting..
	in.instrName = "BSET_4";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_none; break;
case 1: ld = DispLen_none; break;
case 2: ld = DispLen_none; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest |= (1 << (src & 7));

core->reg.r[op->rd] = dest;


	DBG_BSET_4(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_bclr_4(struct TargetCore *core)
{
	RxOpCodeFormatType_bclr_4 *op = &core->decoded_code.code.rx_bclr_4;

	bclr_4_input_type in;
	bclr_4_output_type out;

	//TODO arguments setting..
	in.instrName = "BCLR_4";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_none; break;
case 1: ld = DispLen_none; break;
case 2: ld = DispLen_none; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest &= ~(1 << (src & 7));

core->reg.r[op->rd] = dest;


	DBG_BCLR_4(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_btst_4(struct TargetCore *core)
{
	RxOpCodeFormatType_btst_4 *op = &core->decoded_code.code.rx_btst_4;

	btst_4_input_type in;
	btst_4_output_type out;

	//TODO arguments setting..
	in.instrName = "BTST_4";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];

switch (op->ld) {
case 0: ld = DispLen_none; break;
case 1: ld = DispLen_none; break;
case 2: ld = DispLen_none; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
core->reg.psw.z = ~((src2 >> (src & 7)) & 1);
core->reg.psw.c = ((src2 >> (src & 7)) & 1);



	DBG_BTST_4(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_bnot_4(struct TargetCore *core)
{
	RxOpCodeFormatType_bnot_4 *op = &core->decoded_code.code.rx_bnot_4;

	bnot_4_input_type in;
	bnot_4_output_type out;

	//TODO arguments setting..
	in.instrName = "BNOT_4";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_none; break;
case 1: ld = DispLen_none; break;
case 2: ld = DispLen_none; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest ^= (1 << (src & 7));

core->reg.r[op->rd] = dest;


	DBG_BNOT_4(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_max_2(struct TargetCore *core)
{
	RxOpCodeFormatType_max_2 *op = &core->decoded_code.code.rx_max_2;

	max_2_input_type in;
	max_2_output_type out;

	//TODO arguments setting..
	in.instrName = "MAX_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
if (src > dest)
dest = src;

core->reg.r[op->rd] = dest;


	DBG_MAX_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_min_2(struct TargetCore *core)
{
	RxOpCodeFormatType_min_2 *op = &core->decoded_code.code.rx_min_2;

	min_2_input_type in;
	min_2_output_type out;

	//TODO arguments setting..
	in.instrName = "MIN_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
if (src < dest)
dest = src;

core->reg.r[op->rd] = dest;


	DBG_MIN_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_emul_2(struct TargetCore *core)
{
	RxOpCodeFormatType_emul_2 *op = &core->decoded_code.code.rx_emul_2;

	emul_2_input_type in;
	emul_2_output_type out;

	//TODO arguments setting..
	in.instrName = "EMUL_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint64_t dest64;
uint32_t dest = core->reg.r[op->rd];
uint32_t dest2 = core->reg.r[op->rd + 1];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest64 = dest * src;

core->reg.r[op->rd] = dest64 & 0xFFFFFFFF;
core->reg.r[op->rd + 1] = dest64 >> 32;


	DBG_EMUL_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_emulu_2(struct TargetCore *core)
{
	RxOpCodeFormatType_emulu_2 *op = &core->decoded_code.code.rx_emulu_2;

	emulu_2_input_type in;
	emulu_2_output_type out;

	//TODO arguments setting..
	in.instrName = "EMULU_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint64_t dest64;
uint32_t dest = core->reg.r[op->rd];
uint32_t dest2 = core->reg.r[op->rd + 1];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest64 = dest * src;

core->reg.r[op->rd] = dest64 & 0xFFFFFFFF;
core->reg.r[op->rd + 1] = dest64 >> 32;


	DBG_EMULU_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_div_2(struct TargetCore *core)
{
	RxOpCodeFormatType_div_2 *op = &core->decoded_code.code.rx_div_2;

	div_2_input_type in;
	div_2_output_type out;

	//TODO arguments setting..
	in.instrName = "DIV_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = dest / src;

core->reg.r[op->rd] = dest;


	DBG_DIV_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_divu_2(struct TargetCore *core)
{
	RxOpCodeFormatType_divu_2 *op = &core->decoded_code.code.rx_divu_2;

	divu_2_input_type in;
	divu_2_output_type out;

	//TODO arguments setting..
	in.instrName = "DIVU_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = dest / src;

core->reg.r[op->rd] = dest;


	DBG_DIVU_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_tst_2(struct TargetCore *core)
{
	RxOpCodeFormatType_tst_2 *op = &core->decoded_code.code.rx_tst_2;

	tst_2_input_type in;
	tst_2_output_type out;

	//TODO arguments setting..
	in.instrName = "TST_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
src2 & src;



	DBG_TST_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_xor_2(struct TargetCore *core)
{
	RxOpCodeFormatType_xor_2 *op = &core->decoded_code.code.rx_xor_2;

	xor_2_input_type in;
	xor_2_output_type out;

	//TODO arguments setting..
	in.instrName = "XOR_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = dest ^ src;

core->reg.r[op->rd] = dest;


	DBG_XOR_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_xchg_1(struct TargetCore *core)
{
	RxOpCodeFormatType_xchg_1 *op = &core->decoded_code.code.rx_xchg_1;

	xchg_1_input_type in;
	xchg_1_output_type out;

	//TODO arguments setting..
	in.instrName = "XCHG_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	unsigned long tmp;
DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
tmp = src;
src = dest;
dest = tmp;

core->reg.r[op->rd] = dest;


	DBG_XCHG_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_itof_1(struct TargetCore *core)
{
	RxOpCodeFormatType_itof_1 *op = &core->decoded_code.code.rx_itof_1;

	itof_1_input_type in;
	itof_1_output_type out;

	//TODO arguments setting..
	in.instrName = "ITOF_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = (float)src;

core->reg.r[op->rd] = dest;


	DBG_ITOF_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_bset_2(struct TargetCore *core)
{
	RxOpCodeFormatType_bset_2 *op = &core->decoded_code.code.rx_bset_2;

	bset_2_input_type in;
	bset_2_output_type out;

	//TODO arguments setting..
	in.instrName = "BSET_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_none; break;
default: return -1;
}
dest |= (1 << (src & 7));

core->reg.r[op->rd] = dest;


	DBG_BSET_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_bclr_2(struct TargetCore *core)
{
	RxOpCodeFormatType_bclr_2 *op = &core->decoded_code.code.rx_bclr_2;

	bclr_2_input_type in;
	bclr_2_output_type out;

	//TODO arguments setting..
	in.instrName = "BCLR_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_none; break;
default: return -1;
}
dest &= ~(1 << (src & 7));

core->reg.r[op->rd] = dest;


	DBG_BCLR_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_btst_2(struct TargetCore *core)
{
	RxOpCodeFormatType_btst_2 *op = &core->decoded_code.code.rx_btst_2;

	btst_2_input_type in;
	btst_2_output_type out;

	//TODO arguments setting..
	in.instrName = "BTST_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_none; break;
default: return -1;
}
core->reg.psw.z = ~((src2 >> (src & 7)) & 1);
core->reg.psw.c = ((src2 >> (src & 7)) & 1);



	DBG_BTST_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_bnot_2(struct TargetCore *core)
{
	RxOpCodeFormatType_bnot_2 *op = &core->decoded_code.code.rx_bnot_2;

	bnot_2_input_type in;
	bnot_2_output_type out;

	//TODO arguments setting..
	in.instrName = "BNOT_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_none; break;
default: return -1;
}
dest ^= (1 << (src & 7));

core->reg.r[op->rd] = dest;


	DBG_BNOT_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_fsub_2(struct TargetCore *core)
{
	RxOpCodeFormatType_fsub_2 *op = &core->decoded_code.code.rx_fsub_2;

	fsub_2_input_type in;
	fsub_2_output_type out;

	//TODO arguments setting..
	in.instrName = "FSUB_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = dest - src;

core->reg.r[op->rd] = dest;


	DBG_FSUB_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_fcmp_2(struct TargetCore *core)
{
	RxOpCodeFormatType_fcmp_2 *op = &core->decoded_code.code.rx_fcmp_2;

	fcmp_2_input_type in;
	fcmp_2_output_type out;

	//TODO arguments setting..
	in.instrName = "FCMP_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
src2 - src;



	DBG_FCMP_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_fadd_2(struct TargetCore *core)
{
	RxOpCodeFormatType_fadd_2 *op = &core->decoded_code.code.rx_fadd_2;

	fadd_2_input_type in;
	fadd_2_output_type out;

	//TODO arguments setting..
	in.instrName = "FADD_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = dest + src;

core->reg.r[op->rd] = dest;


	DBG_FADD_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_fmul_2(struct TargetCore *core)
{
	RxOpCodeFormatType_fmul_2 *op = &core->decoded_code.code.rx_fmul_2;

	fmul_2_input_type in;
	fmul_2_output_type out;

	//TODO arguments setting..
	in.instrName = "FMUL_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = dest * src;

core->reg.r[op->rd] = dest;


	DBG_FMUL_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_fdiv_2(struct TargetCore *core)
{
	RxOpCodeFormatType_fdiv_2 *op = &core->decoded_code.code.rx_fdiv_2;

	fdiv_2_input_type in;
	fdiv_2_output_type out;

	//TODO arguments setting..
	in.instrName = "FDIV_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = dest / src;

core->reg.r[op->rd] = dest;


	DBG_FDIV_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_ftoi(struct TargetCore *core)
{
	RxOpCodeFormatType_ftoi *op = &core->decoded_code.code.rx_ftoi;

	ftoi_input_type in;
	ftoi_output_type out;

	//TODO arguments setting..
	in.instrName = "FTOI";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = (signed long)src;

core->reg.r[op->rd] = dest;


	DBG_FTOI(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_round(struct TargetCore *core)
{
	RxOpCodeFormatType_round *op = &core->decoded_code.code.rx_round;

	round_input_type in;
	round_output_type out;

	//TODO arguments setting..
	in.instrName = "ROUND";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = (signed long)src;

core->reg.r[op->rd] = dest;


	DBG_ROUND(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_sccnd(struct TargetCore *core)
{
	RxOpCodeFormatType_sccnd *op = &core->decoded_code.code.rx_sccnd;

	sccnd_input_type in;
	sccnd_output_type out;

	//TODO arguments setting..
	in.instrName = "SCCND";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	bool Cnd;
uint32_t dest = core->reg.r[op->rd];

switch (op->cd) {
case 0: Cnd = core->reg.psw.z == 1; break;
case 1: Cnd = core->reg.psw.z == 0; break;
case 2: Cnd = core->reg.psw.c == 1; break;
case 3: Cnd = core->reg.psw.c == 0; break;
case 4: Cnd = core->reg.psw.s == 0; break;
case 5: Cnd = (core->reg.psw.c & ~core->reg.psw.z) == 0; break;
case 6: Cnd = core->reg.psw.s == 0; break;
case 7: Cnd = core->reg.psw.s == 1; break;
case 8: Cnd = (core->reg.psw.s ^ core->reg.psw.o) == 0; break;
case 9: Cnd = (core->reg.psw.s ^ core->reg.psw.o) == 1; break;
case 10: Cnd = ((core->reg.psw.s ^ core->reg.psw.o) | core->reg.psw.z) == 0; break;
case 11: Cnd = ((core->reg.psw.s ^ core->reg.psw.o) | core->reg.psw.z) == 1; break;
case 12: Cnd = core->reg.psw.o == 1; break;
case 13: Cnd = core->reg.psw.o == 0; break;
default: return -1;
}
if ( Cnd )
dest = 1;
else
dest = 0;

core->reg.r[op->rd] = dest;


	DBG_SCCND(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_bmcnd_1(struct TargetCore *core)
{
	RxOpCodeFormatType_bmcnd_1 *op = &core->decoded_code.code.rx_bmcnd_1;

	bmcnd_1_input_type in;
	bmcnd_1_output_type out;

	//TODO arguments setting..
	in.instrName = "BMCND_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->imm];
DispLenType ld;
bool Cnd;
uint32_t dest = core->reg.r[op->rd];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_none; break;
default: return -1;
}
switch (op->cd) {
case 0: Cnd = core->reg.psw.z == 1; break;
case 1: Cnd = core->reg.psw.z == 0; break;
case 2: Cnd = core->reg.psw.c == 1; break;
case 3: Cnd = core->reg.psw.c == 0; break;
case 4: Cnd = core->reg.psw.s == 0; break;
case 5: Cnd = (core->reg.psw.c & ~core->reg.psw.z) == 0; break;
case 6: Cnd = core->reg.psw.s == 0; break;
case 7: Cnd = core->reg.psw.s == 1; break;
case 8: Cnd = (core->reg.psw.s ^ core->reg.psw.o) == 0; break;
case 9: Cnd = (core->reg.psw.s ^ core->reg.psw.o) == 1; break;
case 10: Cnd = ((core->reg.psw.s ^ core->reg.psw.o) | core->reg.psw.z) == 0; break;
case 11: Cnd = ((core->reg.psw.s ^ core->reg.psw.o) | core->reg.psw.z) == 1; break;
case 12: Cnd = core->reg.psw.o == 1; break;
case 13: Cnd = core->reg.psw.o == 0; break;
default: return -1;
}
if (Cnd)
dest |= (1 << (src & 7));
else
dest &= ~(1 << (src & 7));

core->reg.r[op->rd] = dest;


	DBG_BMCND_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_bnot_1(struct TargetCore *core)
{
	RxOpCodeFormatType_bnot_1 *op = &core->decoded_code.code.rx_bnot_1;

	bnot_1_input_type in;
	bnot_1_output_type out;

	//TODO arguments setting..
	in.instrName = "BNOT_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->imm];
uint32_t dest = core->reg.r[op->rd];

dest ^= (1 << (src & 7));

core->reg.r[op->rd] = dest;


	DBG_BNOT_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_shlr_3(struct TargetCore *core)
{
	RxOpCodeFormatType_shlr_3 *op = &core->decoded_code.code.rx_shlr_3;

	shlr_3_input_type in;
	shlr_3_output_type out;

	//TODO arguments setting..
	in.instrName = "SHLR_3";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->imm];
uint32_t dest = core->reg.r[op->rd];
uint32_t src2 = core->reg.r[op->rs2];

dest = (unsigned long)src2 >> (src & 31);

core->reg.r[op->rd] = dest;


	DBG_SHLR_3(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_shar_3(struct TargetCore *core)
{
	RxOpCodeFormatType_shar_3 *op = &core->decoded_code.code.rx_shar_3;

	shar_3_input_type in;
	shar_3_output_type out;

	//TODO arguments setting..
	in.instrName = "SHAR_3";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->imm];
uint32_t dest = core->reg.r[op->rd];
uint32_t src2 = core->reg.r[op->rs2];

dest = (signed long)src2 >> (src & 31);

core->reg.r[op->rd] = dest;


	DBG_SHAR_3(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_shll_3(struct TargetCore *core)
{
	RxOpCodeFormatType_shll_3 *op = &core->decoded_code.code.rx_shll_3;

	shll_3_input_type in;
	shll_3_output_type out;

	//TODO arguments setting..
	in.instrName = "SHLL_3";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->imm];
uint32_t dest = core->reg.r[op->rd];
uint32_t src2 = core->reg.r[op->rs2];

dest = src2 << (src & 31);

core->reg.r[op->rd] = dest;


	DBG_SHLL_3(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_bmcnd_2(struct TargetCore *core)
{
	RxOpCodeFormatType_bmcnd_2 *op = &core->decoded_code.code.rx_bmcnd_2;

	bmcnd_2_input_type in;
	bmcnd_2_output_type out;

	//TODO arguments setting..
	in.instrName = "BMCND_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->imm];
bool Cnd;
uint32_t dest = core->reg.r[op->rd];

switch (op->cd) {
case 0: Cnd = core->reg.psw.z == 1; break;
case 1: Cnd = core->reg.psw.z == 0; break;
case 2: Cnd = core->reg.psw.c == 1; break;
case 3: Cnd = core->reg.psw.c == 0; break;
case 4: Cnd = core->reg.psw.s == 0; break;
case 5: Cnd = (core->reg.psw.c & ~core->reg.psw.z) == 0; break;
case 6: Cnd = core->reg.psw.s == 0; break;
case 7: Cnd = core->reg.psw.s == 1; break;
case 8: Cnd = (core->reg.psw.s ^ core->reg.psw.o) == 0; break;
case 9: Cnd = (core->reg.psw.s ^ core->reg.psw.o) == 1; break;
case 10: Cnd = ((core->reg.psw.s ^ core->reg.psw.o) | core->reg.psw.z) == 0; break;
case 11: Cnd = ((core->reg.psw.s ^ core->reg.psw.o) | core->reg.psw.z) == 1; break;
case 12: Cnd = core->reg.psw.o == 1; break;
case 13: Cnd = core->reg.psw.o == 0; break;
default: return -1;
}
if (Cnd)
dest |= (1 << (src & 7));
else
dest &= ~(1 << (src & 7));

core->reg.r[op->rd] = dest;


	DBG_BMCND_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_bnot_3(struct TargetCore *core)
{
	RxOpCodeFormatType_bnot_3 *op = &core->decoded_code.code.rx_bnot_3;

	bnot_3_input_type in;
	bnot_3_output_type out;

	//TODO arguments setting..
	in.instrName = "BNOT_3";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->imm];
uint32_t dest = core->reg.r[op->rd];

dest ^= (1 << (src & 7));

core->reg.r[op->rd] = dest;


	DBG_BNOT_3(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mulhi(struct TargetCore *core)
{
	RxOpCodeFormatType_mulhi *op = &core->decoded_code.code.rx_mulhi;

	mulhi_input_type in;
	mulhi_output_type out;

	//TODO arguments setting..
	in.instrName = "MULHI";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	signed short tmp1, tmp2;
int72_t tmp3;
uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];
uint32_t Adest = core->reg.acc[op->a];

tmp1 = (signed short)(src >> 16);
tmp2 = (signed short)(src2 >> 16);
tmp3 = (signed long)tmp1 * (signed long)tmp2;
Adest = (tmp3 << 16);



	DBG_MULHI(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mullo(struct TargetCore *core)
{
	RxOpCodeFormatType_mullo *op = &core->decoded_code.code.rx_mullo;

	mullo_input_type in;
	mullo_output_type out;

	//TODO arguments setting..
	in.instrName = "MULLO";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	signed short tmp1, tmp2;
int72_t tmp3;
uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];
uint32_t Adest = core->reg.acc[op->a];

tmp1 = (signed short)src;
tmp2 = (signed short)src2;
tmp3 = (signed long)tmp1 * (signed long)tmp2;
Adest = (tmp3 << 16);



	DBG_MULLO(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_machi(struct TargetCore *core)
{
	RxOpCodeFormatType_machi *op = &core->decoded_code.code.rx_machi;

	machi_input_type in;
	machi_output_type out;

	//TODO arguments setting..
	in.instrName = "MACHI";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	signed short tmp1, tmp2;
int72_t tmp3;
uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];
uint32_t Adest = core->reg.acc[op->a];

tmp1 = (signed short)(src >> 16);
tmp2 = (signed short)(src2 >> 16);
tmp3 = (signed long)tmp1 * (signed long)tmp2;
Adest = Adest + (tmp3 << 16);



	DBG_MACHI(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_maclo(struct TargetCore *core)
{
	RxOpCodeFormatType_maclo *op = &core->decoded_code.code.rx_maclo;

	maclo_input_type in;
	maclo_output_type out;

	//TODO arguments setting..
	in.instrName = "MACLO";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	signed short tmp1, tmp2;
int72_t tmp3;
uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];
uint32_t Adest = core->reg.acc[op->a];

tmp1 = (signed short)src;
tmp2 = (signed short)src2;
tmp3 = (signed long)tmp1 * (signed long)tmp2;
Adest = Adest + (tmp3 << 16);



	DBG_MACLO(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mvtachi(struct TargetCore *core)
{
	RxOpCodeFormatType_mvtachi *op = &core->decoded_code.code.rx_mvtachi;

	mvtachi_input_type in;
	mvtachi_output_type out;

	//TODO arguments setting..
	in.instrName = "MVTACHI";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->rs];
uint32_t Adest = core->reg.acc[op->a];

Adest = (Adest & MAKE_UINT72(0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF)) | ((int72_t)src << 32);



	DBG_MVTACHI(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mvtaclo(struct TargetCore *core)
{
	RxOpCodeFormatType_mvtaclo *op = &core->decoded_code.code.rx_mvtaclo;

	mvtaclo_input_type in;
	mvtaclo_output_type out;

	//TODO arguments setting..
	in.instrName = "MVTACLO";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->rs];
uint32_t Adest = core->reg.acc[op->a];

Adest = (Adest & MAKE_UINT72(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00)) | (uint72_t)src;



	DBG_MVTACLO(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_racw(struct TargetCore *core)
{
	RxOpCodeFormatType_racw *op = &core->decoded_code.code.rx_racw;

	racw_input_type in;
	racw_output_type out;

	//TODO arguments setting..
	in.instrName = "RACW";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	int72_t tmp;
int73_t tmp73;
uint32_t src = core->reg.r[op->imm];
uint32_t Adest = core->reg.acc[op->a];

tmp = (int72_t) Adest << src;
tmp73 = (int73_t) tmp + MAKE_INT73(0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00);
if (tmp73 > (int73_t)MAKE_INT73(0x0, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0x00, 0x00, 0x00, 0x00))
Adest = MAKE_UINT72(0x00, 0x00, 0x00, 0x7F, 0xFF, 0x00, 0x00, 0x00, 0x00);
else if (tmp73 < (int73_t)MAKE_INT73(0x1, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00))
Adest = MAKE_UINT72(0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00);
else
Adest = tmp & MAKE_UINT72(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00);



	DBG_RACW(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mvfachi(struct TargetCore *core)
{
	RxOpCodeFormatType_mvfachi *op = &core->decoded_code.code.rx_mvfachi;

	mvfachi_input_type in;
	mvfachi_output_type out;

	//TODO arguments setting..
	in.instrName = "MVFACHI";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	int72_t tmp;
uint32_t src = core->reg.r[op->imm];
uint32_t dest = core->reg.r[op->rd];
uint32_t Asrc = core->reg.acc[op->a];

tmp = (int72_t)Asrc << src;
dest = (signed long)(tmp >> 32);

core->reg.r[op->rd] = dest;


	DBG_MVFACHI(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mvfacmi(struct TargetCore *core)
{
	RxOpCodeFormatType_mvfacmi *op = &core->decoded_code.code.rx_mvfacmi;

	mvfacmi_input_type in;
	mvfacmi_output_type out;

	//TODO arguments setting..
	in.instrName = "MVFACMI";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	int72_t tmp;
uint32_t src = core->reg.r[op->imm];
uint32_t dest = core->reg.r[op->rd];
uint32_t Asrc = core->reg.acc[op->a];

tmp = (int72_t)Asrc << src;
dest = (signed long)(Asrc >> 16);

core->reg.r[op->rd] = dest;


	DBG_MVFACMI(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mov_14(struct TargetCore *core)
{
	RxOpCodeFormatType_mov_14 *op = &core->decoded_code.code.rx_mov_14;

	mov_14_input_type in;
	mov_14_output_type out;

	//TODO arguments setting..
	in.instrName = "MOV_14";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

dest = src;

core->reg.r[op->rd] = dest;


	DBG_MOV_14(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mov_15(struct TargetCore *core)
{
	RxOpCodeFormatType_mov_15 *op = &core->decoded_code.code.rx_mov_15;

	mov_15_input_type in;
	mov_15_output_type out;

	//TODO arguments setting..
	in.instrName = "MOV_15";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

dest = src;

core->reg.r[op->rd] = dest;


	DBG_MOV_15(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_movu_4(struct TargetCore *core)
{
	RxOpCodeFormatType_movu_4 *op = &core->decoded_code.code.rx_movu_4;

	movu_4_input_type in;
	movu_4_output_type out;

	//TODO arguments setting..
	in.instrName = "MOVU_4";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

dest = src;

core->reg.r[op->rd] = dest;


	DBG_MOVU_4(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_shlr_2(struct TargetCore *core)
{
	RxOpCodeFormatType_shlr_2 *op = &core->decoded_code.code.rx_shlr_2;

	shlr_2_input_type in;
	shlr_2_output_type out;

	//TODO arguments setting..
	in.instrName = "SHLR_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

dest = (unsigned long)dest >> (src & 31);

core->reg.r[op->rd] = dest;


	DBG_SHLR_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_shar_2(struct TargetCore *core)
{
	RxOpCodeFormatType_shar_2 *op = &core->decoded_code.code.rx_shar_2;

	shar_2_input_type in;
	shar_2_output_type out;

	//TODO arguments setting..
	in.instrName = "SHAR_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

dest = (signed long)dest >> (src & 31);

core->reg.r[op->rd] = dest;


	DBG_SHAR_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_shll_2(struct TargetCore *core)
{
	RxOpCodeFormatType_shll_2 *op = &core->decoded_code.code.rx_shll_2;

	shll_2_input_type in;
	shll_2_output_type out;

	//TODO arguments setting..
	in.instrName = "SHLL_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

dest = dest << (src & 31);

core->reg.r[op->rd] = dest;


	DBG_SHLL_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_rotr_2(struct TargetCore *core)
{
	RxOpCodeFormatType_rotr_2 *op = &core->decoded_code.code.rx_rotr_2;

	rotr_2_input_type in;
	rotr_2_output_type out;

	//TODO arguments setting..
	in.instrName = "ROTR_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	unsigned long tmp0, tmp1;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

tmp0 = src & 31;
tmp1 = (unsigned long) dest >> tmp0;
dest = (dest << (32 - tmp0)) | tmp1;

core->reg.r[op->rd] = dest;


	DBG_ROTR_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_revw(struct TargetCore *core)
{
	RxOpCodeFormatType_revw *op = &core->decoded_code.code.rx_revw;

	revw_input_type in;
	revw_output_type out;

	//TODO arguments setting..
	in.instrName = "REVW";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

dest = ReverseWordData(src);

core->reg.r[op->rd] = dest;


	DBG_REVW(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_rotl_2(struct TargetCore *core)
{
	RxOpCodeFormatType_rotl_2 *op = &core->decoded_code.code.rx_rotl_2;

	rotl_2_input_type in;
	rotl_2_output_type out;

	//TODO arguments setting..
	in.instrName = "ROTL_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	unsigned long tmp0, tmp1;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

tmp0 = src & 31;
tmp1 = dest << tmp0;
dest = ((unsigned long)dest >> (32 - tmp0)) | tmp1;

core->reg.r[op->rd] = dest;


	DBG_ROTL_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_revl(struct TargetCore *core)
{
	RxOpCodeFormatType_revl *op = &core->decoded_code.code.rx_revl;

	revl_input_type in;
	revl_output_type out;

	//TODO arguments setting..
	in.instrName = "REVL";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

dest = ReverseLongwordData(src);

core->reg.r[op->rd] = dest;


	DBG_REVL(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mvtc_2(struct TargetCore *core)
{
	RxOpCodeFormatType_mvtc_2 *op = &core->decoded_code.code.rx_mvtc_2;

	mvtc_2_input_type in;
	mvtc_2_output_type out;

	//TODO arguments setting..
	in.instrName = "MVTC_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	CtrlRegType cr;
uint32_t src = core->reg.r[op->rs];

switch (op->cr) {
case 0: cr = CtrlReg_PSW; break;
case 1: cr = CtrlReg_none; break;
case 2: cr = CtrlReg_USP; break;
case 3: cr = CtrlReg_FPSW; break;
case 4: cr = CtrlReg_none; break;
case 5: cr = CtrlReg_none; break;
case 6: cr = CtrlReg_none; break;
case 7: cr = CtrlReg_none; break;
case 8: cr = CtrlReg_BPSW; break;
case 9: cr = CtrlReg_BPC; break;
case 10: cr = CtrlReg_ISP; break;
case 11: cr = CtrlReg_FINTV; break;
case 12: cr = CtrlReg_INTB; break;
case 13: cr = CtrlReg_EXTB; break;
case 14: cr = CtrlReg_none; break;
case 15: cr = CtrlReg_none; break;
default: return -1;
}
uint32_t dest;
switch (cr) {
case CtrlReg_PSW: dest = core->reg.psw.value; break;
case CtrlReg_USP: dest = core->reg.usp; break;
case CtrlReg_FPSW: dest = core->reg.fpsw; break;
case CtrlReg_BPSW: dest = core->reg.bpsw.value; break;
case CtrlReg_BPC: dest = core->reg.bpc; break;
case CtrlReg_ISP: dest = core->reg.isp; break;
case CtrlReg_FINTV: dest = core->reg.fintv; break;
case CtrlReg_INTB: dest = core->reg.intb; break;
case CtrlReg_EXTB: dest = core->reg.extb; break;
}
dest = src;

switch (cr) {
case CtrlReg_PSW: core->reg.psw.value = dest; break;
case CtrlReg_USP: core->reg.usp = dest; break;
case CtrlReg_FPSW: core->reg.fpsw = dest; break;
case CtrlReg_BPSW: core->reg.bpsw.value = dest; break;
case CtrlReg_BPC: core->reg.bpc = dest; break;
case CtrlReg_ISP: core->reg.isp = dest; break;
case CtrlReg_FINTV: core->reg.fintv = dest; break;
case CtrlReg_INTB: core->reg.intb = dest; break;
case CtrlReg_EXTB: core->reg.extb = dest; break;
}


	DBG_MVTC_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mvfc(struct TargetCore *core)
{
	RxOpCodeFormatType_mvfc *op = &core->decoded_code.code.rx_mvfc;

	mvfc_input_type in;
	mvfc_output_type out;

	//TODO arguments setting..
	in.instrName = "MVFC";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	CtrlRegType cr;
uint32_t dest = core->reg.r[op->rd];

switch (op->cr) {
case 0: cr = CtrlReg_PSW; break;
case 1: cr = CtrlReg_none; break;
case 2: cr = CtrlReg_USP; break;
case 3: cr = CtrlReg_FPSW; break;
case 4: cr = CtrlReg_none; break;
case 5: cr = CtrlReg_none; break;
case 6: cr = CtrlReg_none; break;
case 7: cr = CtrlReg_none; break;
case 8: cr = CtrlReg_BPSW; break;
case 9: cr = CtrlReg_BPC; break;
case 10: cr = CtrlReg_ISP; break;
case 11: cr = CtrlReg_FINTV; break;
case 12: cr = CtrlReg_INTB; break;
case 13: cr = CtrlReg_EXTB; break;
case 14: cr = CtrlReg_none; break;
case 15: cr = CtrlReg_none; break;
default: return -1;
}
uint32_t src;
switch (cr) {
case CtrlReg_PSW: src = core->reg.psw.value; break;
case CtrlReg_USP: src = core->reg.usp; break;
case CtrlReg_FPSW: src = core->reg.fpsw; break;
case CtrlReg_BPSW: src = core->reg.bpsw.value; break;
case CtrlReg_BPC: src = core->reg.bpc; break;
case CtrlReg_ISP: src = core->reg.isp; break;
case CtrlReg_FINTV: src = core->reg.fintv; break;
case CtrlReg_INTB: src = core->reg.intb; break;
case CtrlReg_EXTB: src = core->reg.extb; break;
}
dest = src;

switch (cr) {
case CtrlReg_PSW: core->reg.psw.value = src; break;
case CtrlReg_USP: core->reg.usp = src; break;
case CtrlReg_FPSW: core->reg.fpsw = src; break;
case CtrlReg_BPSW: core->reg.bpsw.value = src; break;
case CtrlReg_BPC: core->reg.bpc = src; break;
case CtrlReg_ISP: core->reg.isp = src; break;
case CtrlReg_FINTV: core->reg.fintv = src; break;
case CtrlReg_INTB: core->reg.intb = src; break;
case CtrlReg_EXTB: core->reg.extb = src; break;
}
core->reg.r[op->rd] = dest;


	DBG_MVFC(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_rotr_1(struct TargetCore *core)
{
	RxOpCodeFormatType_rotr_1 *op = &core->decoded_code.code.rx_rotr_1;

	rotr_1_input_type in;
	rotr_1_output_type out;

	//TODO arguments setting..
	in.instrName = "ROTR_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	unsigned long tmp0, tmp1;
uint32_t src = core->reg.r[op->imm];
uint32_t dest = core->reg.r[op->rd];

tmp0 = src & 31;
tmp1 = (unsigned long)dest >> tmp0;
dest = ((unsigned long)dest >> (32 - tmp0)) | tmp1;

core->reg.r[op->rd] = dest;


	DBG_ROTR_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_rotl_1(struct TargetCore *core)
{
	RxOpCodeFormatType_rotl_1 *op = &core->decoded_code.code.rx_rotl_1;

	rotl_1_input_type in;
	rotl_1_output_type out;

	//TODO arguments setting..
	in.instrName = "ROTL_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	unsigned long tmp0, tmp1;
uint32_t src = core->reg.r[op->imm];
uint32_t dest = core->reg.r[op->rd];

tmp0 = src & 31;
tmp1 = dest << tmp0;
dest = ((unsigned long) dest >> (32 - tmp0)) | tmp1;

core->reg.r[op->rd] = dest;


	DBG_ROTL_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_fadd_1(struct TargetCore *core)
{
	RxOpCodeFormatType_fadd_1 *op = &core->decoded_code.code.rx_fadd_1;

	fadd_1_input_type in;
	fadd_1_output_type out;

	//TODO arguments setting..
	in.instrName = "FADD_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];

uint32_t src = *(uint32_t *)&core->current_code[7];
dest = dest + src;

core->reg.r[op->rd] = dest;


	DBG_FADD_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_fcmp_1(struct TargetCore *core)
{
	RxOpCodeFormatType_fcmp_1 *op = &core->decoded_code.code.rx_fcmp_1;

	fcmp_1_input_type in;
	fcmp_1_output_type out;

	//TODO arguments setting..
	in.instrName = "FCMP_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src2 = core->reg.r[op->rs2];

uint32_t src = *(uint32_t *)&core->current_code[7];
src2 - src;



	DBG_FCMP_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_fdiv_1(struct TargetCore *core)
{
	RxOpCodeFormatType_fdiv_1 *op = &core->decoded_code.code.rx_fdiv_1;

	fdiv_1_input_type in;
	fdiv_1_output_type out;

	//TODO arguments setting..
	in.instrName = "FDIV_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];

uint32_t src = *(uint32_t *)&core->current_code[7];
dest = dest / src;

core->reg.r[op->rd] = dest;


	DBG_FDIV_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_fmul_1(struct TargetCore *core)
{
	RxOpCodeFormatType_fmul_1 *op = &core->decoded_code.code.rx_fmul_1;

	fmul_1_input_type in;
	fmul_1_output_type out;

	//TODO arguments setting..
	in.instrName = "FMUL_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];

uint32_t src = *(uint32_t *)&core->current_code[7];
dest = dest * src;

core->reg.r[op->rd] = dest;


	DBG_FMUL_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_fsub_1(struct TargetCore *core)
{
	RxOpCodeFormatType_fsub_1 *op = &core->decoded_code.code.rx_fsub_1;

	fsub_1_input_type in;
	fsub_1_output_type out;

	//TODO arguments setting..
	in.instrName = "FSUB_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];

uint32_t src = *(uint32_t *)&core->current_code[7];
dest = dest - src;

core->reg.r[op->rd] = dest;


	DBG_FSUB_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_adc_1(struct TargetCore *core)
{
	RxOpCodeFormatType_adc_1 *op = &core->decoded_code.code.rx_adc_1;

	adc_1_input_type in;
	adc_1_output_type out;

	//TODO arguments setting..
	in.instrName = "ADC_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	ImLenType li;
uint32_t dest = core->reg.r[op->rd];

switch (op->li) {
case 0: li = ImLen_imm32; break;
case 1: li = ImLen_simm8; break;
case 2: li = ImLen_simm16; break;
case 3: li = ImLen_simm24; break;
default: return -1;
}
int im_len = 0;
switch (li) {
case ImLen_imm32: im_len = 4; break;
case ImLen_simm8: im_len = 1; break;
case ImLen_simm16: im_len = 2; break;
case ImLen_simm24: im_len = 3; break;
}
uint32_t src = *(uint8_t *)&core->current_code[4 + im_len];
dest = dest + src + core->reg.psw.c;

core->reg.r[op->rd] = dest;


	DBG_ADC_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_div_1(struct TargetCore *core)
{
	RxOpCodeFormatType_div_1 *op = &core->decoded_code.code.rx_div_1;

	div_1_input_type in;
	div_1_output_type out;

	//TODO arguments setting..
	in.instrName = "DIV_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	ImLenType li;
uint32_t dest = core->reg.r[op->rd];

switch (op->li) {
case 0: li = ImLen_imm32; break;
case 1: li = ImLen_simm8; break;
case 2: li = ImLen_simm16; break;
case 3: li = ImLen_simm24; break;
default: return -1;
}
int im_len = 0;
switch (li) {
case ImLen_imm32: im_len = 4; break;
case ImLen_simm8: im_len = 1; break;
case ImLen_simm16: im_len = 2; break;
case ImLen_simm24: im_len = 3; break;
}
uint32_t src = *(uint8_t *)&core->current_code[4 + im_len];
dest = dest / src;

core->reg.r[op->rd] = dest;


	DBG_DIV_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_divu_1(struct TargetCore *core)
{
	RxOpCodeFormatType_divu_1 *op = &core->decoded_code.code.rx_divu_1;

	divu_1_input_type in;
	divu_1_output_type out;

	//TODO arguments setting..
	in.instrName = "DIVU_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	ImLenType li;
uint32_t dest = core->reg.r[op->rd];

switch (op->li) {
case 0: li = ImLen_imm32; break;
case 1: li = ImLen_simm8; break;
case 2: li = ImLen_simm16; break;
case 3: li = ImLen_simm24; break;
default: return -1;
}
int im_len = 0;
switch (li) {
case ImLen_imm32: im_len = 4; break;
case ImLen_simm8: im_len = 1; break;
case ImLen_simm16: im_len = 2; break;
case ImLen_simm24: im_len = 3; break;
}
uint32_t src = *(uint8_t *)&core->current_code[4 + im_len];
dest = dest / src;

core->reg.r[op->rd] = dest;


	DBG_DIVU_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_emul_1(struct TargetCore *core)
{
	RxOpCodeFormatType_emul_1 *op = &core->decoded_code.code.rx_emul_1;

	emul_1_input_type in;
	emul_1_output_type out;

	//TODO arguments setting..
	in.instrName = "EMUL_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	ImLenType li;
uint64_t dest64;
uint32_t dest = core->reg.r[op->rd];
uint32_t dest2 = core->reg.r[op->rd + 1];

switch (op->li) {
case 0: li = ImLen_imm32; break;
case 1: li = ImLen_simm8; break;
case 2: li = ImLen_simm16; break;
case 3: li = ImLen_simm24; break;
default: return -1;
}
int im_len = 0;
switch (li) {
case ImLen_imm32: im_len = 4; break;
case ImLen_simm8: im_len = 1; break;
case ImLen_simm16: im_len = 2; break;
case ImLen_simm24: im_len = 3; break;
}
uint32_t src = *(uint8_t *)&core->current_code[4 + im_len];
dest64 = dest * src;

core->reg.r[op->rd] = dest64 & 0xFFFFFFFF;
core->reg.r[op->rd + 1] = dest64 >> 32;


	DBG_EMUL_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_emulu_1(struct TargetCore *core)
{
	RxOpCodeFormatType_emulu_1 *op = &core->decoded_code.code.rx_emulu_1;

	emulu_1_input_type in;
	emulu_1_output_type out;

	//TODO arguments setting..
	in.instrName = "EMULU_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	ImLenType li;
uint64_t dest64;
uint32_t dest = core->reg.r[op->rd];
uint32_t dest2 = core->reg.r[op->rd + 1];

switch (op->li) {
case 0: li = ImLen_imm32; break;
case 1: li = ImLen_simm8; break;
case 2: li = ImLen_simm16; break;
case 3: li = ImLen_simm24; break;
default: return -1;
}
int im_len = 0;
switch (li) {
case ImLen_imm32: im_len = 4; break;
case ImLen_simm8: im_len = 1; break;
case ImLen_simm16: im_len = 2; break;
case ImLen_simm24: im_len = 3; break;
}
uint32_t src = *(uint8_t *)&core->current_code[4 + im_len];
dest64 = dest * src;

core->reg.r[op->rd] = dest64 & 0xFFFFFFFF;
core->reg.r[op->rd + 1] = dest64 >> 32;


	DBG_EMULU_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_max_1(struct TargetCore *core)
{
	RxOpCodeFormatType_max_1 *op = &core->decoded_code.code.rx_max_1;

	max_1_input_type in;
	max_1_output_type out;

	//TODO arguments setting..
	in.instrName = "MAX_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	ImLenType li;
uint32_t dest = core->reg.r[op->rd];

switch (op->li) {
case 0: li = ImLen_imm32; break;
case 1: li = ImLen_simm8; break;
case 2: li = ImLen_simm16; break;
case 3: li = ImLen_simm24; break;
default: return -1;
}
int im_len = 0;
switch (li) {
case ImLen_imm32: im_len = 4; break;
case ImLen_simm8: im_len = 1; break;
case ImLen_simm16: im_len = 2; break;
case ImLen_simm24: im_len = 3; break;
}
uint32_t src = *(uint8_t *)&core->current_code[4 + im_len];
if (src > dest)
dest = src;

core->reg.r[op->rd] = dest;


	DBG_MAX_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_min_1(struct TargetCore *core)
{
	RxOpCodeFormatType_min_1 *op = &core->decoded_code.code.rx_min_1;

	min_1_input_type in;
	min_1_output_type out;

	//TODO arguments setting..
	in.instrName = "MIN_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	ImLenType li;
uint32_t dest = core->reg.r[op->rd];

switch (op->li) {
case 0: li = ImLen_imm32; break;
case 1: li = ImLen_simm8; break;
case 2: li = ImLen_simm16; break;
case 3: li = ImLen_simm24; break;
default: return -1;
}
int im_len = 0;
switch (li) {
case ImLen_imm32: im_len = 4; break;
case ImLen_simm8: im_len = 1; break;
case ImLen_simm16: im_len = 2; break;
case ImLen_simm24: im_len = 3; break;
}
uint32_t src = *(uint8_t *)&core->current_code[4 + im_len];
if (src < dest)
dest = src;

core->reg.r[op->rd] = dest;


	DBG_MIN_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_stnz_1(struct TargetCore *core)
{
	RxOpCodeFormatType_stnz_1 *op = &core->decoded_code.code.rx_stnz_1;

	stnz_1_input_type in;
	stnz_1_output_type out;

	//TODO arguments setting..
	in.instrName = "STNZ_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	ImLenType li;
uint32_t dest = core->reg.r[op->rd];

switch (op->li) {
case 0: li = ImLen_imm32; break;
case 1: li = ImLen_simm8; break;
case 2: li = ImLen_simm16; break;
case 3: li = ImLen_simm24; break;
default: return -1;
}
int im_len = 0;
switch (li) {
case ImLen_imm32: im_len = 4; break;
case ImLen_simm8: im_len = 1; break;
case ImLen_simm16: im_len = 2; break;
case ImLen_simm24: im_len = 3; break;
}
uint32_t src = *(uint8_t *)&core->current_code[4 + im_len];
if (core->reg.psw.z == 0)
dest = src;

core->reg.r[op->rd] = dest;


	DBG_STNZ_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_stz_1(struct TargetCore *core)
{
	RxOpCodeFormatType_stz_1 *op = &core->decoded_code.code.rx_stz_1;

	stz_1_input_type in;
	stz_1_output_type out;

	//TODO arguments setting..
	in.instrName = "STZ_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	ImLenType li;
uint32_t dest = core->reg.r[op->rd];

switch (op->li) {
case 0: li = ImLen_imm32; break;
case 1: li = ImLen_simm8; break;
case 2: li = ImLen_simm16; break;
case 3: li = ImLen_simm24; break;
default: return -1;
}
int im_len = 0;
switch (li) {
case ImLen_imm32: im_len = 4; break;
case ImLen_simm8: im_len = 1; break;
case ImLen_simm16: im_len = 2; break;
case ImLen_simm24: im_len = 3; break;
}
uint32_t src = *(uint8_t *)&core->current_code[4 + im_len];
if (core->reg.psw.z == 1)
dest = src;

core->reg.r[op->rd] = dest;


	DBG_STZ_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_tst_1(struct TargetCore *core)
{
	RxOpCodeFormatType_tst_1 *op = &core->decoded_code.code.rx_tst_1;

	tst_1_input_type in;
	tst_1_output_type out;

	//TODO arguments setting..
	in.instrName = "TST_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	ImLenType li;
uint32_t src2 = core->reg.r[op->rs2];

switch (op->li) {
case 0: li = ImLen_imm32; break;
case 1: li = ImLen_simm8; break;
case 2: li = ImLen_simm16; break;
case 3: li = ImLen_simm24; break;
default: return -1;
}
int im_len = 0;
switch (li) {
case ImLen_imm32: im_len = 4; break;
case ImLen_simm8: im_len = 1; break;
case ImLen_simm16: im_len = 2; break;
case ImLen_simm24: im_len = 3; break;
}
uint32_t src = *(uint8_t *)&core->current_code[4 + im_len];
src2 & src;



	DBG_TST_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_xor_1(struct TargetCore *core)
{
	RxOpCodeFormatType_xor_1 *op = &core->decoded_code.code.rx_xor_1;

	xor_1_input_type in;
	xor_1_output_type out;

	//TODO arguments setting..
	in.instrName = "XOR_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	ImLenType li;
uint32_t dest = core->reg.r[op->rd];

switch (op->li) {
case 0: li = ImLen_imm32; break;
case 1: li = ImLen_simm8; break;
case 2: li = ImLen_simm16; break;
case 3: li = ImLen_simm24; break;
default: return -1;
}
int im_len = 0;
switch (li) {
case ImLen_imm32: im_len = 4; break;
case ImLen_simm8: im_len = 1; break;
case ImLen_simm16: im_len = 2; break;
case ImLen_simm24: im_len = 3; break;
}
uint32_t src = *(uint8_t *)&core->current_code[4 + im_len];
dest = dest ^ src;

core->reg.r[op->rd] = dest;


	DBG_XOR_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mvtc_1(struct TargetCore *core)
{
	RxOpCodeFormatType_mvtc_1 *op = &core->decoded_code.code.rx_mvtc_1;

	mvtc_1_input_type in;
	mvtc_1_output_type out;

	//TODO arguments setting..
	in.instrName = "MVTC_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	ImLenType li;
CtrlRegType cr;

switch (op->li) {
case 0: li = ImLen_imm32; break;
case 1: li = ImLen_simm8; break;
case 2: li = ImLen_simm16; break;
case 3: li = ImLen_simm24; break;
default: return -1;
}
switch (op->cr) {
case 0: cr = CtrlReg_PSW; break;
case 1: cr = CtrlReg_none; break;
case 2: cr = CtrlReg_USP; break;
case 3: cr = CtrlReg_FPSW; break;
case 4: cr = CtrlReg_none; break;
case 5: cr = CtrlReg_none; break;
case 6: cr = CtrlReg_none; break;
case 7: cr = CtrlReg_none; break;
case 8: cr = CtrlReg_BPSW; break;
case 9: cr = CtrlReg_BPC; break;
case 10: cr = CtrlReg_ISP; break;
case 11: cr = CtrlReg_FINTV; break;
case 12: cr = CtrlReg_INTB; break;
case 13: cr = CtrlReg_EXTB; break;
case 14: cr = CtrlReg_none; break;
case 15: cr = CtrlReg_none; break;
default: return -1;
}
uint32_t dest;
switch (cr) {
case CtrlReg_PSW: dest = core->reg.psw.value; break;
case CtrlReg_USP: dest = core->reg.usp; break;
case CtrlReg_FPSW: dest = core->reg.fpsw; break;
case CtrlReg_BPSW: dest = core->reg.bpsw.value; break;
case CtrlReg_BPC: dest = core->reg.bpc; break;
case CtrlReg_ISP: dest = core->reg.isp; break;
case CtrlReg_FINTV: dest = core->reg.fintv; break;
case CtrlReg_INTB: dest = core->reg.intb; break;
case CtrlReg_EXTB: dest = core->reg.extb; break;
}
int im_len = 0;
switch (li) {
case ImLen_imm32: im_len = 4; break;
case ImLen_simm8: im_len = 1; break;
case ImLen_simm16: im_len = 2; break;
case ImLen_simm24: im_len = 3; break;
}
uint32_t src = *(uint8_t *)&core->current_code[4 + im_len];
dest = src;

switch (cr) {
case CtrlReg_PSW: core->reg.psw.value = dest; break;
case CtrlReg_USP: core->reg.usp = dest; break;
case CtrlReg_FPSW: core->reg.fpsw = dest; break;
case CtrlReg_BPSW: core->reg.bpsw.value = dest; break;
case CtrlReg_BPC: core->reg.bpc = dest; break;
case CtrlReg_ISP: core->reg.isp = dest; break;
case CtrlReg_FINTV: core->reg.fintv = dest; break;
case CtrlReg_INTB: core->reg.intb = dest; break;
case CtrlReg_EXTB: core->reg.extb = dest; break;
}


	DBG_MVTC_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mov_10(struct TargetCore *core)
{
	RxOpCodeFormatType_mov_10 *op = &core->decoded_code.code.rx_mov_10;

	mov_10_input_type in;
	mov_10_output_type out;

	//TODO arguments setting..
	in.instrName = "MOV_10";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	OpSizeType sz;
uint32_t src_index = core->reg.r[op->ri];
uint8_t src_base = core->reg.r[op->rb];
uint32_t dest = core->reg.r[op->rd];

switch (op->sz) {
case 0: sz = OpSize_B; break;
case 1: sz = OpSize_W; break;
case 2: sz = OpSize_L; break;
default: return -1;
}
uint32_t src = bus_get_data(core, sz, src_base, src_index);
dest = src;

bus_put_data(core, sz, src_base, src_index, src);
core->reg.r[op->rd] = dest;


	DBG_MOV_10(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mov_12(struct TargetCore *core)
{
	RxOpCodeFormatType_mov_12 *op = &core->decoded_code.code.rx_mov_12;

	mov_12_input_type in;
	mov_12_output_type out;

	//TODO arguments setting..
	in.instrName = "MOV_12";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	OpSizeType sz;
uint32_t dest_index = core->reg.r[op->ri];
uint8_t dest_base = core->reg.r[op->rb];
uint32_t src = core->reg.r[op->rs];

switch (op->sz) {
case 0: sz = OpSize_B; break;
case 1: sz = OpSize_W; break;
case 2: sz = OpSize_L; break;
default: return -1;
}
uint32_t dest = bus_get_data(core, sz, dest_base, dest_index);
dest = src;

bus_put_data(core, sz, dest_base, dest_index, dest);


	DBG_MOV_12(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_movu_3(struct TargetCore *core)
{
	RxOpCodeFormatType_movu_3 *op = &core->decoded_code.code.rx_movu_3;

	movu_3_input_type in;
	movu_3_output_type out;

	//TODO arguments setting..
	in.instrName = "MOVU_3";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	OpSizeType sz;
uint32_t src_index = core->reg.r[op->ri];
uint8_t src_base = core->reg.r[op->rb];
uint32_t dest = core->reg.r[op->rd];

switch (op->sz) {
case 0: sz = OpSize_B; break;
case 1: sz = OpSize_W; break;
case 2: sz = OpSize_L; break;
default: return -1;
}
uint32_t src = bus_get_data(core, sz, src_base, src_index);
dest = src;

bus_put_data(core, sz, src_base, src_index, src);
core->reg.r[op->rd] = dest;


	DBG_MOVU_3(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_add_4(struct TargetCore *core)
{
	RxOpCodeFormatType_add_4 *op = &core->decoded_code.code.rx_add_4;

	add_4_input_type in;
	add_4_output_type out;

	//TODO arguments setting..
	in.instrName = "ADD_4";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];

dest = src2 + src;

core->reg.r[op->rd] = dest;


	DBG_ADD_4(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_and_4(struct TargetCore *core)
{
	RxOpCodeFormatType_and_4 *op = &core->decoded_code.code.rx_and_4;

	and_4_input_type in;
	and_4_output_type out;

	//TODO arguments setting..
	in.instrName = "AND_4";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];

dest = src2 & src;

core->reg.r[op->rd] = dest;


	DBG_AND_4(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mul_4(struct TargetCore *core)
{
	RxOpCodeFormatType_mul_4 *op = &core->decoded_code.code.rx_mul_4;

	mul_4_input_type in;
	mul_4_output_type out;

	//TODO arguments setting..
	in.instrName = "MUL_4";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];

dest = src * src2;

core->reg.r[op->rd] = dest;


	DBG_MUL_4(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_or_4(struct TargetCore *core)
{
	RxOpCodeFormatType_or_4 *op = &core->decoded_code.code.rx_or_4;

	or_4_input_type in;
	or_4_output_type out;

	//TODO arguments setting..
	in.instrName = "OR_4";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];

dest = src2 | src;

core->reg.r[op->rd] = dest;


	DBG_OR_4(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_sub_3(struct TargetCore *core)
{
	RxOpCodeFormatType_sub_3 *op = &core->decoded_code.code.rx_sub_3;

	sub_3_input_type in;
	sub_3_output_type out;

	//TODO arguments setting..
	in.instrName = "SUB_3";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];

dest = src2 - src;

core->reg.r[op->rd] = dest;


	DBG_SUB_3(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_bclr_1(struct TargetCore *core)
{
	RxOpCodeFormatType_bclr_1 *op = &core->decoded_code.code.rx_bclr_1;

	bclr_1_input_type in;
	bclr_1_output_type out;

	//TODO arguments setting..
	in.instrName = "BCLR_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t src = core->reg.r[op->imm];
uint32_t dest = core->reg.r[op->rd];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_none; break;
default: return -1;
}
dest &= ~(1 << (src & 7));

core->reg.r[op->rd] = dest;


	DBG_BCLR_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_bset_1(struct TargetCore *core)
{
	RxOpCodeFormatType_bset_1 *op = &core->decoded_code.code.rx_bset_1;

	bset_1_input_type in;
	bset_1_output_type out;

	//TODO arguments setting..
	in.instrName = "BSET_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_none; break;
case 1: ld = DispLen_none; break;
case 2: ld = DispLen_none; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest |= (1 << (src & 7));

core->reg.r[op->rd] = dest;


	DBG_BSET_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_btst_1(struct TargetCore *core)
{
	RxOpCodeFormatType_btst_1 *op = &core->decoded_code.code.rx_btst_1;

	btst_1_input_type in;
	btst_1_output_type out;

	//TODO arguments setting..
	in.instrName = "BTST_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t src = core->reg.r[op->imm];
uint32_t src2 = core->reg.r[op->rs2];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_none; break;
default: return -1;
}
core->reg.psw.z = ~((src2 >> (src & 7)) & 1);
core->reg.psw.c = ((src2 >> (src & 7)) & 1);



	DBG_BTST_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_push_2(struct TargetCore *core)
{
	RxOpCodeFormatType_push_2 *op = &core->decoded_code.code.rx_push_2;

	push_2_input_type in;
	push_2_output_type out;

	//TODO arguments setting..
	in.instrName = "PUSH_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_none; break;
default: return -1;
}



	DBG_PUSH_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mov_6(struct TargetCore *core)
{
	RxOpCodeFormatType_mov_6 *op = &core->decoded_code.code.rx_mov_6;

	mov_6_input_type in;
	mov_6_output_type out;

	//TODO arguments setting..
	in.instrName = "MOV_6";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	ImLenType li;
uint32_t dest = core->reg.r[op->rd];

switch (op->li) {
case 0: li = ImLen_imm32; break;
case 1: li = ImLen_simm8; break;
case 2: li = ImLen_simm16; break;
case 3: li = ImLen_simm24; break;
default: return -1;
}
int im_len = 0;
switch (li) {
case ImLen_imm32: im_len = 4; break;
case ImLen_simm8: im_len = 1; break;
case ImLen_simm16: im_len = 2; break;
case ImLen_simm24: im_len = 3; break;
}
uint32_t src = *(uint8_t *)&core->current_code[3 + im_len];
dest = src;

core->reg.r[op->rd] = dest;


	DBG_MOV_6(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mov_8(struct TargetCore *core)
{
	RxOpCodeFormatType_mov_8 *op = &core->decoded_code.code.rx_mov_8;

	mov_8_input_type in;
	mov_8_output_type out;

	//TODO arguments setting..
	in.instrName = "MOV_8";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
ImLenType li;
uint32_t dest = core->reg.r[op->rd];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_none; break;
default: return -1;
}
switch (op->li) {
case 0: li = ImLen_imm32; break;
case 1: li = ImLen_simm8; break;
case 2: li = ImLen_simm16; break;
case 3: li = ImLen_simm24; break;
default: return -1;
}
int im_len = 0;
switch (li) {
case ImLen_imm32: im_len = 4; break;
case ImLen_simm8: im_len = 1; break;
case ImLen_simm16: im_len = 2; break;
case ImLen_simm24: im_len = 3; break;
}
uint32_t src = *(uint8_t *)&core->current_code[3 + im_len];
dest = src;

core->reg.r[op->rd] = dest;


	DBG_MOV_8(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mov_7(struct TargetCore *core)
{
	RxOpCodeFormatType_mov_7 *op = &core->decoded_code.code.rx_mov_7;

	mov_7_input_type in;
	mov_7_output_type out;

	//TODO arguments setting..
	in.instrName = "MOV_7";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

dest = src;

core->reg.r[op->rd] = dest;


	DBG_MOV_7(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mov_9(struct TargetCore *core)
{
	RxOpCodeFormatType_mov_9 *op = &core->decoded_code.code.rx_mov_9;

	mov_9_input_type in;
	mov_9_output_type out;

	//TODO arguments setting..
	in.instrName = "MOV_9";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_none; break;
default: return -1;
}
dest = src;

core->reg.r[op->rd] = dest;


	DBG_MOV_9(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mov_11(struct TargetCore *core)
{
	RxOpCodeFormatType_mov_11 *op = &core->decoded_code.code.rx_mov_11;

	mov_11_input_type in;
	mov_11_output_type out;

	//TODO arguments setting..
	in.instrName = "MOV_11";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_none; break;
default: return -1;
}
dest = src;

core->reg.r[op->rd] = dest;


	DBG_MOV_11(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mov_13(struct TargetCore *core)
{
	RxOpCodeFormatType_mov_13 *op = &core->decoded_code.code.rx_mov_13;

	mov_13_input_type in;
	mov_13_output_type out;

	//TODO arguments setting..
	in.instrName = "MOV_13";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ldd;
DispLenType lds;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ldd) {
case 0: ldd = DispLen_disp0; break;
case 1: ldd = DispLen_disp8; break;
case 2: ldd = DispLen_disp16; break;
case 3: ldd = DispLen_none; break;
default: return -1;
}
switch (op->lds) {
case 0: lds = DispLen_disp0; break;
case 1: lds = DispLen_disp8; break;
case 2: lds = DispLen_disp16; break;
case 3: lds = DispLen_none; break;
default: return -1;
}
dest = src;

core->reg.r[op->rd] = dest;


	DBG_MOV_13(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_fsqrt(struct TargetCore *core)
{
	RxOpCodeFormatType_fsqrt *op = &core->decoded_code.code.rx_fsqrt;

	fsqrt_input_type in;
	fsqrt_output_type out;

	//TODO arguments setting..
	in.instrName = "FSQRT";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = sqrt(src);

core->reg.r[op->rd] = dest;


	DBG_FSQRT(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_ftou(struct TargetCore *core)
{
	RxOpCodeFormatType_ftou *op = &core->decoded_code.code.rx_ftou;

	ftou_input_type in;
	ftou_output_type out;

	//TODO arguments setting..
	in.instrName = "FTOU";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = (unsigned long)src;

core->reg.r[op->rd] = dest;


	DBG_FTOU(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_utof_1(struct TargetCore *core)
{
	RxOpCodeFormatType_utof_1 *op = &core->decoded_code.code.rx_utof_1;

	utof_1_input_type in;
	utof_1_output_type out;

	//TODO arguments setting..
	in.instrName = "UTOF_1";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = (float)(unsigned long)src;

core->reg.r[op->rd] = dest;


	DBG_UTOF_1(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_utof_1x(struct TargetCore *core)
{
	RxOpCodeFormatType_utof_1x *op = &core->decoded_code.code.rx_utof_1x;

	utof_1x_input_type in;
	utof_1x_output_type out;

	//TODO arguments setting..
	in.instrName = "UTOF_1X";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	MemExType memex;
DispLenType ld;
uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

switch (op->mi) {
case 0: memex = MemEx_B; break;
case 1: memex = MemEx_W; break;
case 2: memex = MemEx_L; break;
case 3: memex = MemEx_UW; break;
default: return -1;
}
switch (op->ld) {
case 0: ld = DispLen_disp0; break;
case 1: ld = DispLen_disp8; break;
case 2: ld = DispLen_disp16; break;
case 3: ld = DispLen_register; break;
default: return -1;
}
dest = (float)(unsigned long)src;

core->reg.r[op->rd] = dest;


	DBG_UTOF_1X(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_movco(struct TargetCore *core)
{
	RxOpCodeFormatType_movco *op = &core->decoded_code.code.rx_movco;

	movco_input_type in;
	movco_output_type out;

	//TODO arguments setting..
	in.instrName = "MOVCO";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

if (core->li == 1) { dest = src; src = 0; }
else { src = 1; }
core->li = 0;

core->reg.r[op->rd] = dest;


	DBG_MOVCO(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_movli(struct TargetCore *core)
{
	RxOpCodeFormatType_movli *op = &core->decoded_code.code.rx_movli;

	movli_input_type in;
	movli_output_type out;

	//TODO arguments setting..
	in.instrName = "MOVLI";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];

core->li = 1;
dest = src;

core->reg.r[op->rd] = dest;


	DBG_MOVLI(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_emaca(struct TargetCore *core)
{
	RxOpCodeFormatType_emaca *op = &core->decoded_code.code.rx_emaca;

	emaca_input_type in;
	emaca_output_type out;

	//TODO arguments setting..
	in.instrName = "EMACA";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	int72_t tmp;
uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];
uint32_t Adest = core->reg.acc[op->a];

tmp = (signed long) src * (signed long) src2;
Adest = Adest + tmp;



	DBG_EMACA(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_emsba(struct TargetCore *core)
{
	RxOpCodeFormatType_emsba *op = &core->decoded_code.code.rx_emsba;

	emsba_input_type in;
	emsba_output_type out;

	//TODO arguments setting..
	in.instrName = "EMSBA";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	int72_t tmp;
uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];
uint32_t Adest = core->reg.acc[op->a];

tmp = (signed long) src * (signed long) src2;
Adest = Adest - tmp;



	DBG_EMSBA(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_emula(struct TargetCore *core)
{
	RxOpCodeFormatType_emula *op = &core->decoded_code.code.rx_emula;

	emula_input_type in;
	emula_output_type out;

	//TODO arguments setting..
	in.instrName = "EMULA";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];
uint32_t Adest = core->reg.acc[op->a];

Adest = (signed long) src * (signed long) src2;



	DBG_EMULA(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_maclh(struct TargetCore *core)
{
	RxOpCodeFormatType_maclh *op = &core->decoded_code.code.rx_maclh;

	maclh_input_type in;
	maclh_output_type out;

	//TODO arguments setting..
	in.instrName = "MACLH";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	signed short tmp1, tmp2;
int72_t tmp3;
uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];
uint32_t Adest = core->reg.acc[op->a];

tmp1 = (signed short)src;
tmp2 = (signed short)(src2 >> 16);
tmp3 = (signed long)tmp1 * (signed long)tmp2;
Adest = Adest + (tmp3 << 16);



	DBG_MACLH(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_msbhi(struct TargetCore *core)
{
	RxOpCodeFormatType_msbhi *op = &core->decoded_code.code.rx_msbhi;

	msbhi_input_type in;
	msbhi_output_type out;

	//TODO arguments setting..
	in.instrName = "MSBHI";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	signed short tmp1, tmp2;
int72_t tmp3;
uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];
uint32_t Adest = core->reg.acc[op->a];

tmp1 = (signed short)(src >> 16);
tmp2 = (signed short)(src2 >> 16);
tmp3 = (signed long)tmp1 * (signed long)tmp2;
Adest = Adest - (tmp3 << 16);



	DBG_MSBHI(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_msblh(struct TargetCore *core)
{
	RxOpCodeFormatType_msblh *op = &core->decoded_code.code.rx_msblh;

	msblh_input_type in;
	msblh_output_type out;

	//TODO arguments setting..
	in.instrName = "MSBLH";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	signed short tmp1, tmp2;
int72_t tmp3;
uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];
uint32_t Adest = core->reg.acc[op->a];

tmp1 = (signed short)src;
tmp2 = (signed short)(src2 >> 16);
tmp3 = (signed long)tmp1 * (signed long)tmp2;
Adest = Adest - (tmp3 << 16);



	DBG_MSBLH(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_msblo(struct TargetCore *core)
{
	RxOpCodeFormatType_msblo *op = &core->decoded_code.code.rx_msblo;

	msblo_input_type in;
	msblo_output_type out;

	//TODO arguments setting..
	in.instrName = "MSBLO";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	signed short tmp1, tmp2;
int72_t tmp3;
uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];
uint32_t Adest = core->reg.acc[op->a];

tmp1 = (signed short)src;
tmp2 = (signed short)src2;
tmp3 = (signed long)tmp1 * (signed long)tmp2;
Adest = Adest - (tmp3 << 16);



	DBG_MSBLO(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mullh(struct TargetCore *core)
{
	RxOpCodeFormatType_mullh *op = &core->decoded_code.code.rx_mullh;

	mullh_input_type in;
	mullh_output_type out;

	//TODO arguments setting..
	in.instrName = "MULLH";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	signed short tmp1, tmp2;
int72_t tmp3;
uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];
uint32_t Adest = core->reg.acc[op->a];

tmp1 = (signed short)src;
tmp2 = (signed short)(src2 >> 16);
tmp3 = (signed long)tmp1 * (signed long)tmp2;
Adest = (tmp3 << 16);



	DBG_MULLH(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mvfacgu(struct TargetCore *core)
{
	RxOpCodeFormatType_mvfacgu *op = &core->decoded_code.code.rx_mvfacgu;

	mvfacgu_input_type in;
	mvfacgu_output_type out;

	//TODO arguments setting..
	in.instrName = "MVFACGU";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	int72_t tmp;
uint32_t src = core->reg.r[op->imm];
uint32_t dest = core->reg.r[op->rd];
uint32_t Asrc = core->reg.acc[op->a];

tmp = (int72_t)Asrc << src;
dest = (signed long)(tmp >> 64);

core->reg.r[op->rd] = dest;


	DBG_MVFACGU(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mvfaclo(struct TargetCore *core)
{
	RxOpCodeFormatType_mvfaclo *op = &core->decoded_code.code.rx_mvfaclo;

	mvfaclo_input_type in;
	mvfaclo_output_type out;

	//TODO arguments setting..
	in.instrName = "MVFACLO";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	int72_t tmp;
uint32_t src = core->reg.r[op->imm];
uint32_t dest = core->reg.r[op->rd];
uint32_t Asrc = core->reg.acc[op->a];

tmp = (int72_t)Asrc << src;
dest = (signed long)tmp;

core->reg.r[op->rd] = dest;


	DBG_MVFACLO(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_mvtacgu(struct TargetCore *core)
{
	RxOpCodeFormatType_mvtacgu *op = &core->decoded_code.code.rx_mvtacgu;

	mvtacgu_input_type in;
	mvtacgu_output_type out;

	//TODO arguments setting..
	in.instrName = "MVTACGU";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t src = core->reg.r[op->rs];
uint32_t Adest = core->reg.acc[op->a];

Adest = (Adest & MAKE_UINT72(0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF)) | ((int72_t)src << 64);



	DBG_MVTACGU(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_racl(struct TargetCore *core)
{
	RxOpCodeFormatType_racl *op = &core->decoded_code.code.rx_racl;

	racl_input_type in;
	racl_output_type out;

	//TODO arguments setting..
	in.instrName = "RACL";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	int72_t tmp;
int73_t tmp73;
uint32_t src = core->reg.r[op->imm];
uint32_t Adest = core->reg.acc[op->a];

tmp = (int72_t)Adest << src;
tmp73 = (int73_t)tmp + MAKE_INT73(0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00);
if (tmp73 > (int73_t)MAKE_INT73(0x0, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00))
Adest = MAKE_UINT72(0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00);
else if (tmp73 < (int73_t)MAKE_INT73(0x1, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00))
Adest = MAKE_UINT72(0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
else
Adest = tmp & MAKE_UINT72(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00);



	DBG_RACL(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_rdacl(struct TargetCore *core)
{
	RxOpCodeFormatType_rdacl *op = &core->decoded_code.code.rx_rdacl;

	rdacl_input_type in;
	rdacl_output_type out;

	//TODO arguments setting..
	in.instrName = "RDACL";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	int72_t tmp;
uint32_t src = core->reg.r[op->imm];
uint32_t Adest = core->reg.acc[op->a];

tmp = (int72_t)Adest << src;
if (tmp > (int72_t)MAKE_UINT72(0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00))
Adest = MAKE_UINT72(0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00);
else if (tmp < (int72_t)MAKE_UINT72(0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00))
Adest = MAKE_UINT72(0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
else
Adest = tmp & MAKE_UINT72(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00);



	DBG_RDACL(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_rdacw(struct TargetCore *core)
{
	RxOpCodeFormatType_rdacw *op = &core->decoded_code.code.rx_rdacw;

	rdacw_input_type in;
	rdacw_output_type out;

	//TODO arguments setting..
	in.instrName = "RDACW";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	int72_t tmp;
uint32_t src = core->reg.r[op->imm];
uint32_t Adest = core->reg.acc[op->a];

tmp = (int72_t)Adest << src;
if (tmp > (int72_t)MAKE_UINT72(0x00, 0x00, 0x00, 0x7F, 0xFF, 0x00, 0x00, 0x00, 0x00))
Adest = MAKE_UINT72(0x00, 0x00, 0x00, 0x7F, 0xFF, 0x00, 0x00, 0x00, 0x00);
else if (tmp < (int72_t)MAKE_UINT72(0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00))
Adest = MAKE_UINT72(0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00);
else
Adest = tmp & MAKE_UINT72(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00);



	DBG_RDACW(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_fadd_3(struct TargetCore *core)
{
	RxOpCodeFormatType_fadd_3 *op = &core->decoded_code.code.rx_fadd_3;

	fadd_3_input_type in;
	fadd_3_output_type out;

	//TODO arguments setting..
	in.instrName = "FADD_3";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];

dest = src2 + src;

core->reg.r[op->rd] = dest;


	DBG_FADD_3(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_fmul_3(struct TargetCore *core)
{
	RxOpCodeFormatType_fmul_3 *op = &core->decoded_code.code.rx_fmul_3;

	fmul_3_input_type in;
	fmul_3_output_type out;

	//TODO arguments setting..
	in.instrName = "FMUL_3";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];

dest = src2 * src;

core->reg.r[op->rd] = dest;


	DBG_FMUL_3(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_fsub_3(struct TargetCore *core)
{
	RxOpCodeFormatType_fsub_3 *op = &core->decoded_code.code.rx_fsub_3;

	fsub_3_input_type in;
	fsub_3_output_type out;

	//TODO arguments setting..
	in.instrName = "FSUB_3";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	uint32_t dest = core->reg.r[op->rd];
uint32_t src = core->reg.r[op->rs];
uint32_t src2 = core->reg.r[op->rs2];

dest = src2 - src;

core->reg.r[op->rd] = dest;


	DBG_FSUB_3(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_stnz_2(struct TargetCore *core)
{
	RxOpCodeFormatType_stnz_2 *op = &core->decoded_code.code.rx_stnz_2;

	stnz_2_input_type in;
	stnz_2_output_type out;

	//TODO arguments setting..
	in.instrName = "STNZ_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	



	DBG_STNZ_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
int rx_op_exec_stz_2(struct TargetCore *core)
{
	RxOpCodeFormatType_stz_2 *op = &core->decoded_code.code.rx_stz_2;

	stz_2_input_type in;
	stz_2_output_type out;

	//TODO arguments setting..
	in.instrName = "STZ_2";

	out.next_address = core->reg.pc;
	out.passed = FALSE;

	int ret = 0;

	



	DBG_STZ_2(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
