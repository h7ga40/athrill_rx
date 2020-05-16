#ifndef _{{ ns|upper }}PSEUDO_CODE_FUNC_H_
#define _{{ ns|upper }}PSEUDO_CODE_FUNC_H_

#include "{{ ns }}code_type.h"

{% for inst in instruction_decoders -%}
extern int {{ ns }}op_exec_{{inst.name}}(struct TargetCore *core,  {{ inst.name }}_input_type *in, {{ inst.name }}_output_type *out);
{% endfor -%}

#endif /* !_{{ ns|upper }}PSEUDO_CODE_FUNC_H_ */
