#include "rx_pseudo_code_func.h"

int rx_op_exec_brk(struct TargetCore *core,  brk_input_type *in, brk_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_rts(struct TargetCore *core,  rts_input_type *in, rts_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_nop(struct TargetCore *core,  nop_input_type *in, nop_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_bra_a(struct TargetCore *core,  bra_a_input_type *in, bra_a_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_bsr_a(struct TargetCore *core,  bsr_a_input_type *in, bsr_a_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_sub_2x(struct TargetCore *core,  sub_2x_input_type *in, sub_2x_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_cmp_4x(struct TargetCore *core,  cmp_4x_input_type *in, cmp_4x_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_add_2x(struct TargetCore *core,  add_2x_input_type *in, add_2x_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mul_3x(struct TargetCore *core,  mul_3x_input_type *in, mul_3x_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_and_3x(struct TargetCore *core,  and_3x_input_type *in, and_3x_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_or_3x(struct TargetCore *core,  or_3x_input_type *in, or_3x_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_sbb_2(struct TargetCore *core,  sbb_2_input_type *in, sbb_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_adc_3(struct TargetCore *core,  adc_3_input_type *in, adc_3_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_div_2x(struct TargetCore *core,  div_2x_input_type *in, div_2x_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_divu_2x(struct TargetCore *core,  divu_2x_input_type *in, divu_2x_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_emul_2x(struct TargetCore *core,  emul_2x_input_type *in, emul_2x_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_emulu_2x(struct TargetCore *core,  emulu_2x_input_type *in, emulu_2x_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_itof_1x(struct TargetCore *core,  itof_1x_input_type *in, itof_1x_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_max_2x(struct TargetCore *core,  max_2x_input_type *in, max_2x_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_min_2x(struct TargetCore *core,  min_2x_input_type *in, min_2x_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_tst_2x(struct TargetCore *core,  tst_2x_input_type *in, tst_2x_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_xchg_1x(struct TargetCore *core,  xchg_1x_input_type *in, xchg_1x_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_xor_2x(struct TargetCore *core,  xor_2x_input_type *in, xor_2x_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_bra_s(struct TargetCore *core,  bra_s_input_type *in, bra_s_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_bcnd_s(struct TargetCore *core,  bcnd_s_input_type *in, bcnd_s_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_bra_b(struct TargetCore *core,  bra_b_input_type *in, bra_b_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_bcnd_b(struct TargetCore *core,  bcnd_b_input_type *in, bcnd_b_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_bra_w(struct TargetCore *core,  bra_w_input_type *in, bra_w_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_bsr_w(struct TargetCore *core,  bsr_w_input_type *in, bsr_w_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_bcnd_w(struct TargetCore *core,  bcnd_w_input_type *in, bcnd_w_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_rtsd_2(struct TargetCore *core,  rtsd_2_input_type *in, rtsd_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mov_4(struct TargetCore *core,  mov_4_input_type *in, mov_4_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_sub_2(struct TargetCore *core,  sub_2_input_type *in, sub_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_cmp_4(struct TargetCore *core,  cmp_4_input_type *in, cmp_4_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_add_2(struct TargetCore *core,  add_2_input_type *in, add_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mul_3(struct TargetCore *core,  mul_3_input_type *in, mul_3_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_and_3(struct TargetCore *core,  and_3_input_type *in, and_3_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_or_3(struct TargetCore *core,  or_3_input_type *in, or_3_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_movu_2(struct TargetCore *core,  movu_2_input_type *in, movu_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_sub_1(struct TargetCore *core,  sub_1_input_type *in, sub_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_cmp_1(struct TargetCore *core,  cmp_1_input_type *in, cmp_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_add_1(struct TargetCore *core,  add_1_input_type *in, add_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mul_1(struct TargetCore *core,  mul_1_input_type *in, mul_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_and_1(struct TargetCore *core,  and_1_input_type *in, and_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_or_1(struct TargetCore *core,  or_1_input_type *in, or_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mov_3(struct TargetCore *core,  mov_3_input_type *in, mov_3_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_rtsd_1(struct TargetCore *core,  rtsd_1_input_type *in, rtsd_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_shlr_1(struct TargetCore *core,  shlr_1_input_type *in, shlr_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_shar_1(struct TargetCore *core,  shar_1_input_type *in, shar_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_shll_1(struct TargetCore *core,  shll_1_input_type *in, shll_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_pushm(struct TargetCore *core,  pushm_input_type *in, pushm_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_popm(struct TargetCore *core,  popm_input_type *in, popm_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_add_3(struct TargetCore *core,  add_3_input_type *in, add_3_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_cmp_2(struct TargetCore *core,  cmp_2_input_type *in, cmp_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_int(struct TargetCore *core,  int_input_type *in, int_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mov_5(struct TargetCore *core,  mov_5_input_type *in, mov_5_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mvtipl(struct TargetCore *core,  mvtipl_input_type *in, mvtipl_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_and_2(struct TargetCore *core,  and_2_input_type *in, and_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_cmp_3(struct TargetCore *core,  cmp_3_input_type *in, cmp_3_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mul_2(struct TargetCore *core,  mul_2_input_type *in, mul_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_or_2(struct TargetCore *core,  or_2_input_type *in, or_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_bset_3(struct TargetCore *core,  bset_3_input_type *in, bset_3_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_bclr_3(struct TargetCore *core,  bclr_3_input_type *in, bclr_3_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_btst_3(struct TargetCore *core,  btst_3_input_type *in, btst_3_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_abs_1(struct TargetCore *core,  abs_1_input_type *in, abs_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_neg_1(struct TargetCore *core,  neg_1_input_type *in, neg_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_not_1(struct TargetCore *core,  not_1_input_type *in, not_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_rolc(struct TargetCore *core,  rolc_input_type *in, rolc_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_pop(struct TargetCore *core,  pop_input_type *in, pop_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_popc(struct TargetCore *core,  popc_input_type *in, popc_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_rorc(struct TargetCore *core,  rorc_input_type *in, rorc_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_push_1(struct TargetCore *core,  push_1_input_type *in, push_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_pushc(struct TargetCore *core,  pushc_input_type *in, pushc_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_sat(struct TargetCore *core,  sat_input_type *in, sat_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_jmp(struct TargetCore *core,  jmp_input_type *in, jmp_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_jsr(struct TargetCore *core,  jsr_input_type *in, jsr_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_bra_l(struct TargetCore *core,  bra_l_input_type *in, bra_l_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_bsr_l(struct TargetCore *core,  bsr_l_input_type *in, bsr_l_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_scmpu(struct TargetCore *core,  scmpu_input_type *in, scmpu_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_suntil_b(struct TargetCore *core,  suntil_b_input_type *in, suntil_b_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_suntil_w(struct TargetCore *core,  suntil_w_input_type *in, suntil_w_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_suntil_l(struct TargetCore *core,  suntil_l_input_type *in, suntil_l_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_smovu(struct TargetCore *core,  smovu_input_type *in, smovu_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_swhile_b(struct TargetCore *core,  swhile_b_input_type *in, swhile_b_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_swhile_w(struct TargetCore *core,  swhile_w_input_type *in, swhile_w_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_swhile_l(struct TargetCore *core,  swhile_l_input_type *in, swhile_l_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_smovb(struct TargetCore *core,  smovb_input_type *in, smovb_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_sstr_b(struct TargetCore *core,  sstr_b_input_type *in, sstr_b_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_sstr_w(struct TargetCore *core,  sstr_w_input_type *in, sstr_w_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_sstr_l(struct TargetCore *core,  sstr_l_input_type *in, sstr_l_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_smovf(struct TargetCore *core,  smovf_input_type *in, smovf_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_rmpa(struct TargetCore *core,  rmpa_input_type *in, rmpa_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_satr(struct TargetCore *core,  satr_input_type *in, satr_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_rtfi(struct TargetCore *core,  rtfi_input_type *in, rtfi_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_rte(struct TargetCore *core,  rte_input_type *in, rte_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_wait(struct TargetCore *core,  wait_input_type *in, wait_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_setpsw(struct TargetCore *core,  setpsw_input_type *in, setpsw_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_clrpsw(struct TargetCore *core,  clrpsw_input_type *in, clrpsw_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_movu_1(struct TargetCore *core,  movu_1_input_type *in, movu_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mov_1(struct TargetCore *core,  mov_1_input_type *in, mov_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mov_2(struct TargetCore *core,  mov_2_input_type *in, mov_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_sbb_1(struct TargetCore *core,  sbb_1_input_type *in, sbb_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_neg_2(struct TargetCore *core,  neg_2_input_type *in, neg_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_adc_2(struct TargetCore *core,  adc_2_input_type *in, adc_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_abs_2(struct TargetCore *core,  abs_2_input_type *in, abs_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_not_2(struct TargetCore *core,  not_2_input_type *in, not_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_bset_4(struct TargetCore *core,  bset_4_input_type *in, bset_4_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_bclr_4(struct TargetCore *core,  bclr_4_input_type *in, bclr_4_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_btst_4(struct TargetCore *core,  btst_4_input_type *in, btst_4_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_bnot_4(struct TargetCore *core,  bnot_4_input_type *in, bnot_4_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_max_2(struct TargetCore *core,  max_2_input_type *in, max_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_min_2(struct TargetCore *core,  min_2_input_type *in, min_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_emul_2(struct TargetCore *core,  emul_2_input_type *in, emul_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_emulu_2(struct TargetCore *core,  emulu_2_input_type *in, emulu_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_div_2(struct TargetCore *core,  div_2_input_type *in, div_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_divu_2(struct TargetCore *core,  divu_2_input_type *in, divu_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_tst_2(struct TargetCore *core,  tst_2_input_type *in, tst_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_xor_2(struct TargetCore *core,  xor_2_input_type *in, xor_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_xchg_1(struct TargetCore *core,  xchg_1_input_type *in, xchg_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_itof_1(struct TargetCore *core,  itof_1_input_type *in, itof_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_bset_2(struct TargetCore *core,  bset_2_input_type *in, bset_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_bclr_2(struct TargetCore *core,  bclr_2_input_type *in, bclr_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_btst_2(struct TargetCore *core,  btst_2_input_type *in, btst_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_bnot_2(struct TargetCore *core,  bnot_2_input_type *in, bnot_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_fsub_2(struct TargetCore *core,  fsub_2_input_type *in, fsub_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_fcmp_2(struct TargetCore *core,  fcmp_2_input_type *in, fcmp_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_fadd_2(struct TargetCore *core,  fadd_2_input_type *in, fadd_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_fmul_2(struct TargetCore *core,  fmul_2_input_type *in, fmul_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_fdiv_2(struct TargetCore *core,  fdiv_2_input_type *in, fdiv_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_ftoi(struct TargetCore *core,  ftoi_input_type *in, ftoi_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_round(struct TargetCore *core,  round_input_type *in, round_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_sccnd(struct TargetCore *core,  sccnd_input_type *in, sccnd_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_bmcnd_1(struct TargetCore *core,  bmcnd_1_input_type *in, bmcnd_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_bnot_1(struct TargetCore *core,  bnot_1_input_type *in, bnot_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_shlr_3(struct TargetCore *core,  shlr_3_input_type *in, shlr_3_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_shar_3(struct TargetCore *core,  shar_3_input_type *in, shar_3_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_shll_3(struct TargetCore *core,  shll_3_input_type *in, shll_3_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_bmcnd_2(struct TargetCore *core,  bmcnd_2_input_type *in, bmcnd_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_bnot_3(struct TargetCore *core,  bnot_3_input_type *in, bnot_3_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mulhi(struct TargetCore *core,  mulhi_input_type *in, mulhi_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mullo(struct TargetCore *core,  mullo_input_type *in, mullo_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_machi(struct TargetCore *core,  machi_input_type *in, machi_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_maclo(struct TargetCore *core,  maclo_input_type *in, maclo_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mvtachi(struct TargetCore *core,  mvtachi_input_type *in, mvtachi_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mvtaclo(struct TargetCore *core,  mvtaclo_input_type *in, mvtaclo_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_racw(struct TargetCore *core,  racw_input_type *in, racw_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mvfachi(struct TargetCore *core,  mvfachi_input_type *in, mvfachi_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mvfacmi(struct TargetCore *core,  mvfacmi_input_type *in, mvfacmi_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mov_14(struct TargetCore *core,  mov_14_input_type *in, mov_14_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mov_15(struct TargetCore *core,  mov_15_input_type *in, mov_15_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_movu_4(struct TargetCore *core,  movu_4_input_type *in, movu_4_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_shlr_2(struct TargetCore *core,  shlr_2_input_type *in, shlr_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_shar_2(struct TargetCore *core,  shar_2_input_type *in, shar_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_shll_2(struct TargetCore *core,  shll_2_input_type *in, shll_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_rotr_2(struct TargetCore *core,  rotr_2_input_type *in, rotr_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_revw(struct TargetCore *core,  revw_input_type *in, revw_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_rotl_2(struct TargetCore *core,  rotl_2_input_type *in, rotl_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_revl(struct TargetCore *core,  revl_input_type *in, revl_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mvtc_2(struct TargetCore *core,  mvtc_2_input_type *in, mvtc_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mvfc(struct TargetCore *core,  mvfc_input_type *in, mvfc_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_rotr_1(struct TargetCore *core,  rotr_1_input_type *in, rotr_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_rotl_1(struct TargetCore *core,  rotl_1_input_type *in, rotl_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_fadd_1(struct TargetCore *core,  fadd_1_input_type *in, fadd_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_fcmp_1(struct TargetCore *core,  fcmp_1_input_type *in, fcmp_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_fdiv_1(struct TargetCore *core,  fdiv_1_input_type *in, fdiv_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_fmul_1(struct TargetCore *core,  fmul_1_input_type *in, fmul_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_fsub_1(struct TargetCore *core,  fsub_1_input_type *in, fsub_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_adc_1(struct TargetCore *core,  adc_1_input_type *in, adc_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_div_1(struct TargetCore *core,  div_1_input_type *in, div_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_divu_1(struct TargetCore *core,  divu_1_input_type *in, divu_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_emul_1(struct TargetCore *core,  emul_1_input_type *in, emul_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_emulu_1(struct TargetCore *core,  emulu_1_input_type *in, emulu_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_max_1(struct TargetCore *core,  max_1_input_type *in, max_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_min_1(struct TargetCore *core,  min_1_input_type *in, min_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_stnz_1(struct TargetCore *core,  stnz_1_input_type *in, stnz_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_stz_1(struct TargetCore *core,  stz_1_input_type *in, stz_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_tst_1(struct TargetCore *core,  tst_1_input_type *in, tst_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_xor_1(struct TargetCore *core,  xor_1_input_type *in, xor_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mvtc_1(struct TargetCore *core,  mvtc_1_input_type *in, mvtc_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mov_10(struct TargetCore *core,  mov_10_input_type *in, mov_10_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mov_12(struct TargetCore *core,  mov_12_input_type *in, mov_12_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_movu_3(struct TargetCore *core,  movu_3_input_type *in, movu_3_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_add_4(struct TargetCore *core,  add_4_input_type *in, add_4_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_and_4(struct TargetCore *core,  and_4_input_type *in, and_4_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mul_4(struct TargetCore *core,  mul_4_input_type *in, mul_4_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_or_4(struct TargetCore *core,  or_4_input_type *in, or_4_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_sub_3(struct TargetCore *core,  sub_3_input_type *in, sub_3_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_bclr_1(struct TargetCore *core,  bclr_1_input_type *in, bclr_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_bset_1(struct TargetCore *core,  bset_1_input_type *in, bset_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_btst_1(struct TargetCore *core,  btst_1_input_type *in, btst_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_push_2(struct TargetCore *core,  push_2_input_type *in, push_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mov_6(struct TargetCore *core,  mov_6_input_type *in, mov_6_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mov_8(struct TargetCore *core,  mov_8_input_type *in, mov_8_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mov_7(struct TargetCore *core,  mov_7_input_type *in, mov_7_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mov_9(struct TargetCore *core,  mov_9_input_type *in, mov_9_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mov_11(struct TargetCore *core,  mov_11_input_type *in, mov_11_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mov_13(struct TargetCore *core,  mov_13_input_type *in, mov_13_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_fsqrt(struct TargetCore *core,  fsqrt_input_type *in, fsqrt_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_ftou(struct TargetCore *core,  ftou_input_type *in, ftou_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_utof_1(struct TargetCore *core,  utof_1_input_type *in, utof_1_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_utof_1x(struct TargetCore *core,  utof_1x_input_type *in, utof_1x_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_movco(struct TargetCore *core,  movco_input_type *in, movco_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_movli(struct TargetCore *core,  movli_input_type *in, movli_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_emaca(struct TargetCore *core,  emaca_input_type *in, emaca_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_emsba(struct TargetCore *core,  emsba_input_type *in, emsba_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_emula(struct TargetCore *core,  emula_input_type *in, emula_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_maclh(struct TargetCore *core,  maclh_input_type *in, maclh_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_msbhi(struct TargetCore *core,  msbhi_input_type *in, msbhi_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_msblh(struct TargetCore *core,  msblh_input_type *in, msblh_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_msblo(struct TargetCore *core,  msblo_input_type *in, msblo_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mullh(struct TargetCore *core,  mullh_input_type *in, mullh_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mvfacgu(struct TargetCore *core,  mvfacgu_input_type *in, mvfacgu_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mvfaclo(struct TargetCore *core,  mvfaclo_input_type *in, mvfaclo_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_mvtacgu(struct TargetCore *core,  mvtacgu_input_type *in, mvtacgu_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_racl(struct TargetCore *core,  racl_input_type *in, racl_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_rdacl(struct TargetCore *core,  rdacl_input_type *in, rdacl_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_rdacw(struct TargetCore *core,  rdacw_input_type *in, rdacw_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_fadd_3(struct TargetCore *core,  fadd_3_input_type *in, fadd_3_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_fmul_3(struct TargetCore *core,  fmul_3_input_type *in, fmul_3_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_fsub_3(struct TargetCore *core,  fsub_3_input_type *in, fsub_3_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_stnz_2(struct TargetCore *core,  stnz_2_input_type *in, stnz_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
int rx_op_exec_stz_2(struct TargetCore *core,  stz_2_input_type *in, stz_2_output_type *out)
{
	int ret = 0;
	uint32 result;
	uint32 *status = cpu_get_status(core);
	out->next_address = core->pc + INST_ARM_SIZE;
	out->passed = ConditionPassed(in->cond, *status);
	if (out->passed != FALSE) {
        result = in->Rm.regData;
		cpu_set_reg(core, in->Rd.regId, result);
		if (in->Rd.regId != CpuRegId_PC) {
            ret = 0;
		}
		else {
			ret = ALUWritePC(&out->next_address, status, result);
		}
		out->Rd.regData = result;
	}
	out->status = *status;
	return ret;
}
