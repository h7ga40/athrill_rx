#ifndef _{{ ns|upper }}MC_DECODER_H_
#define _{{ ns|upper }}MC_DECODER_H_

#include <stdint.h>

typedef uint8_t {{ ns }}uint8;
typedef uint16_t {{ ns }}uint16;
typedef uint32_t {{ ns }}uint24;
typedef uint32_t {{ ns }}uint32;

#define {{ ns|upper }}OP_CODE_FORMAT_NUM	{{ ns|upper }}OP_CODE_FORMAT_UNKNOWN

typedef enum {
	{% for inst in instruction_decoders -%}
		{{ ns|upper }}OP_CODE_FORMAT_{{ inst.name|upper }},
	{% endfor -%}
	{{ ns|upper }}OP_CODE_FORMAT_UNKNOWN,
} {{ ns|capitalize|trim('_') }}OpCodeFormatId;

typedef enum {
	{% for inst in instruction_decoders -%}
		{{ ns|capitalize|trim('_') }}OpCodeId_{{ inst.name }},
	{% endfor -%}
	{{ ns|capitalize|trim('_') }}OpCodeId_Num,
} {{ ns|capitalize|trim('_') }}OpCodeId;

typedef struct {
	{{ ns|capitalize|trim('_') }}OpCodeFormatId	format_id;
	{{ ns|capitalize|trim('_') }}OpCodeId		code_id;
} {{ ns|capitalize|trim('_') }}OperationCodeType;


{% for inst in instruction_decoders %}
typedef struct {
{%- for field in inst.field_decoders %}
	{{ ns }}uint{{ field.type_bit_size }} {{ field.name }};	/* {% for sf in field.subfield_decoders %}{{ sf.start_bit_in_instruction }}-{{ sf.end_bit_in_instruction }}{% if not loop.last %}, {% endif %}{% endfor %} */
{%- else %}
	uint8_t _dummy;
{%- endfor %}
} {{ ns|capitalize|trim('_') }}OpCodeFormatType_{{ inst.name }};
{% endfor %}

typedef struct {
	{{ ns|capitalize|trim('_') }}OpCodeFormatId type_id;
	union {
	{%- for inst in instruction_decoders %}
		{{ ns|capitalize|trim('_') }}OpCodeFormatType_{{ inst.name }} {{ ns }}{{ inst.name }};
	{%- endfor %}
	} code;
	uint8_t size;
} {{ ns|capitalize|trim('_') }}OpDecodedCodeType;

#define {{ ns|upper }}OP_DECODE_MAX	(4)

extern int {{ ns }}op_parse({{ ns }}uint16 code[{{ ns|upper }}OP_DECODE_MAX], {{ ns|capitalize|trim('_') }}OpDecodedCodeType *decoded_code, {{ ns|capitalize|trim('_') }}OperationCodeType *optype);

struct TargetCore;
typedef struct {
	int clocks;
	int (*exec) (struct TargetCore *cpu);
} {{ ns|capitalize|trim('_') }}OpExecType;

extern {{ ns|capitalize|trim('_') }}OpExecType {{ ns }}op_exec_table[{{ ns|capitalize|trim('_') }}OpCodeId_Num];
{% for inst in instruction_decoders %}
extern int {{ ns }}op_exec_{{ inst.name }}(struct TargetCore *core);
{%- endfor %}

#endif /* !_{{ ns|upper }}MC_DECODER_H_ */
