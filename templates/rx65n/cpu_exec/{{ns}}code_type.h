#ifndef _{{ ns|upper }}PSEUDO_CODE_TYPE_H_
#define _{{ ns|upper }}PSEUDO_CODE_TYPE_H_

#include "cpu_common/{{ ns }}code_common_type.h"

{% for inst in instruction_decoders -%}

typedef struct {
	char* instrName;
{%- if inst.inputs is defined %}
{%-   for key, value in inst.inputs.items() %}
	{{value}}	{{key}};
{%-   endfor %}
{%- endif %}
} {{ inst.name }}_input_type;

typedef struct {
	uint32	next_address;
{%- if inst.outputs is defined %}
{%-   for key, value in inst.outputs.items() %}
	{{value}}	{{key}};
{%-   endfor %}
{%- endif %}
	CodeStatusType		status;
	CodeCondPassedType	passed;
} {{ inst.name }}_output_type;

{% endfor -%}


#endif /* !_{{ ns|upper }}PSEUDO_CODE_TYPE_H_ */
