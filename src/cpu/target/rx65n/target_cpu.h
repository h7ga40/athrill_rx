#ifndef _CPU_REGISTER_H_
#define _CPU_REGISTER_H_

#include "cpu_dec/op_dec.h"
#include "std_types.h"


typedef enum {

	CpuRegId_0 = 0,
	CpuRegId_SP = 0,
	CpuRegId_1,
	CpuRegId_2,
	CpuRegId_3,
	CpuRegId_4,
	CpuRegId_5,
	CpuRegId_6,
	CpuRegId_7,
	CpuRegId_8,
	CpuRegId_9,
	CpuRegId_10,
	CpuRegId_11,
	CpuRegId_12,
	CpuRegId_13,
	CpuRegId_14,
	CpuRegId_15,
} CpuRegIdType;
#define CpuRegId_NUM	CpuRegId_15

typedef union {
	struct{
		uint32	c : 1;
		uint32	z : 1;
		uint32	s : 1;
		uint32	o : 1;
		uint32 : 12;
		uint32	i : 1;
		uint32	u : 1;
		uint32 : 2;
		uint32	pm : 1;
		uint32 : 3;
		uint32	ipl : 4;
		uint32 : 4;
	};
	uint32 value;
} CpuPswType;

//typedef uint8_t int72_t[9];
//typedef uint8_t uint72_t[9];
//typedef uint8_t int73_t[10];
typedef int64_t int72_t;
typedef uint64_t uint72_t;
typedef int64_t int73_t;

extern uint72_t MAKE_UINT72(unsigned char v9,
	unsigned char v8, unsigned char v7, unsigned char v6, unsigned char v5,
	unsigned char v4, unsigned char v3, unsigned char v2, unsigned char v1);
extern int73_t MAKE_INT73(signed char s, unsigned char v9,
	unsigned char v8, unsigned char v7, unsigned char v6, unsigned char v5,
	unsigned char v4, unsigned char v3, unsigned char v2, unsigned char v1);
extern uint32_t hi_ui72(uint72_t value);
extern uint32_t lo_ui72(uint72_t value);

typedef struct {
	sint32	r[CpuRegId_NUM];
	uint32	isp;		// 割り込みスタックポインタ
	uint32	usp;		// ユーザスタックポインタ
	uint32	intb;		// 割り込みテーブルレジスタ
	uint32	pc;			// プログラムカウンタ
	CpuPswType	psw;	// プロセッサステータスワード
	uint32	bpc;		// バックアップPC
	CpuPswType	bpsw;	// バックアップPSW
	uint32	fintv;		// 高速割り込みベクタレジスタ
	uint32	fpsw;		// 浮動小数点ステータスワード
	uint32	extb;		// 例外テーブルレジスタ
	union {
		struct
		{
			uint72_t acc0;
			uint72_t acc1;
		};
		uint72_t	acc[2];	// アキュムレータ0
	};
} CpuRegisterType;

typedef enum {
	CpuMemoryAccess_NONE = 0,
	CpuMemoryAccess_READ,
	CpuMemoryAccess_WRITE,
	CpuMemoryAccess_EXEC,
} CpuMemoryAccessType;

typedef struct TargetCore {
	CoreIdType			core_id;
	CpuRegisterType 	reg;
	bool				is_halt;
	uint8 				current_code[OP_DECODE_MAX];
	uint8				code_size;
	OpDecodedCodeType	decoded_code;
	uint8_t				li;
	uint8_t				*int_base;
} TargetCoreType;

static inline uint32 cpu_get_pc(const TargetCoreType *core)
{
	return core->reg.pc;
}

static inline uint32 cpu_get_sp(const TargetCoreType *core)
{
	return core->reg.r[3];
}

#endif /* _CPU_REGISTER_H_ */
