#ifndef _{{ ns|upper }}PSEUDO_CODE_DEBUG_H_
#define _{{ ns|upper }}PSEUDO_CODE_DEBUG_H_

#include "dbg_log.h"
#include "{{ ns }}code_type.h"

{% for inst in instruction_decoders -%}
static inline void DBG_{{ inst.name|upper }}(TargetCoreType *core, {{ inst.name }}_input_type *in, {{ inst.name }}_output_type *out)
{
	DBG_PRINT((DBG_EXEC_OP_BUF(), DBG_EXEC_OP_BUF_LEN(),
		DBG_FMT_STR
{%- if inst.inputs is defined %}
{%-   for key, value in inst.inputs.items() %}
		DBG_FMT_{{value}}
{%-   endfor %}
{%- endif %}
		": "
{%- if inst.outputs is defined %}
{%-   for key, value in inst.outputs.items() %}
		DBG_FMT_{{value}}
{%-   endfor %}
{%- endif %}
		DBG_FMT_CodeStatusType 
		DBG_FMT_CodeCondPassedType "\n",
		in->instrName,
{%- if inst.inputs is defined %}
{%-   for key, value in inst.inputs.items() %}
		DBG_ARG_{{value}}(&in->{{key}}),
{%-   endfor %}
{%- endif %}
{%- if inst.outputs is defined %}
{%-   for key, value in inst.outputs.items() %}
		DBG_ARG_{{value}}(&out->{{key}}),
{%-   endfor %}
{%- endif %}
		DBG_ARG_CodeStatusType(&out->status),
		DBG_ARG_CodeCondPassedType(&out->passed)
	));
}

{% endfor -%}

#endif /* !_{{ ns|upper }}PSEUDO_CODE_DEBUG_H_ */
