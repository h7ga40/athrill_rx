#include "cpu_exec/{{ ns }}code_debug.h"
#include "cpu_dec/{{ ns }}mcdecoder.h"
#include "target_cpu.h"
#include "bus.h"
#include "{{ ns }}code_func.h"

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

{% for inst in instruction_decoders -%}

int {{ ns }}op_exec_{{inst.name}}(struct TargetCore *core)
{
	{{ ns|capitalize|trim('_') }}OpCodeFormatType_{{inst.name}} *op = &core->decoded_code.code.{{ ns }}{{inst.name}};

	{{inst.name}}_input_type in;
	{{inst.name}}_output_type out;

{%- if inst.outputs is defined %}
	out.status = *cpu_get_status(core);
{%- endif %}

	//TODO arguments setting..
	in.instrName = "{{inst.name|upper}}";
{% if inst.inputs is defined %}
	{% for key, value in inst.inputs.items() %}
	in.{{key}} = op->{{key}};
	{% endfor %}
{% endif %}
	out.next_address = core->reg.pc;
	out.passed = FALSE;
{% if inst.outputs is defined %}
	{%- for key, value in inst.outputs.items() %}
	out.{{key}} = -1;
	{%- endfor %}
{% endif %}
	int ret = 0;
{% if inst.extras.operation is defined %}
	{{ inst.extras.operation|formatoperation(inst) }}
{% endif %}
	DBG_{{ inst.name|upper}}(core, &in, &out);

	core->reg.pc = out.next_address;
	return ret;
}
{% endfor -%}

