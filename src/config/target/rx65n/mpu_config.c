#include "mpu.h"
#include "cpu_config.h"

#define MPU_ADDRESS_REGION_START_INX_RAM		(0x00000000)
#define MPU_ADDRESS_REGION_END_INX_RAM			(0x0003FFFF)
#define MPU_ADDRESS_REGION_START_INX_PH0		(0x00080000)
#define MPU_ADDRESS_REGION_END_INX_PH0			(0x000A3FFF)
#define MPU_ADDRESS_REGION_START_INX_SBRAM		(0x000A4000)
#define MPU_ADDRESS_REGION_END_INX_SBRAM		(0x000A5FFF)
#define MPU_ADDRESS_REGION_START_INX_PH1		(0x000A6000)
#define MPU_ADDRESS_REGION_END_INX_PH1			(0x000FFFFF)
#define MPU_ADDRESS_REGION_START_INX_DTROM		(0x00100000)
#define MPU_ADDRESS_REGION_END_INX_DTROM		(0x00107FFF)
#define MPU_ADDRESS_REGION_START_INX_FACI		(0x007E0000)
#define MPU_ADDRESS_REGION_END_INX_FACI		(0x007F0003)
#define MPU_ADDRESS_REGION_START_INX_PH2		(0x007FC000)
#define MPU_ADDRESS_REGION_END_INX_PH2			(0x007FFFFF)
#define MPU_ADDRESS_REGION_START_INX_EXRAM		(0x00800000)
#define MPU_ADDRESS_REGION_END_INX_EXRAM		(0x0085FFFF)
#define MPU_ADDRESS_REGION_START_INX_OPROM		(0xFE7F5D00)
#define MPU_ADDRESS_REGION_END_INX_OPROM		(0xFE7F5D7F)
#define MPU_ADDRESS_REGION_START_INX_OPROMR	(0xFE7F7D00)
#define MPU_ADDRESS_REGION_END_INX_OPROMR		(0xFE7F7D7F)
#define MPU_ADDRESS_REGION_START_INX_ROM		(0xFFE00000)
#define MPU_ADDRESS_REGION_END_INX_ROM			(0xFFFFFFFF)

static uint8 memory_data_RAM[MPU_ADDRESS_REGION_END_INX_RAM + 1 - MPU_ADDRESS_REGION_START_INX_RAM];
static uint8 memory_data_PH0[MPU_ADDRESS_REGION_END_INX_PH0 + 1 - MPU_ADDRESS_REGION_START_INX_PH0];
static uint8 memory_data_SBRAM[MPU_ADDRESS_REGION_END_INX_SBRAM + 1 - MPU_ADDRESS_REGION_START_INX_SBRAM];
static uint8 memory_data_PH1[MPU_ADDRESS_REGION_END_INX_PH1 + 1 - MPU_ADDRESS_REGION_START_INX_PH1];
static uint8 memory_data_DTROM[MPU_ADDRESS_REGION_END_INX_DTROM + 1 - MPU_ADDRESS_REGION_START_INX_DTROM];
static uint8 memory_data_FACI[MPU_ADDRESS_REGION_END_INX_FACI + 1 - MPU_ADDRESS_REGION_START_INX_FACI];
static uint8 memory_data_PH2[MPU_ADDRESS_REGION_END_INX_PH2 + 1 - MPU_ADDRESS_REGION_START_INX_PH2];
static uint8 memory_data_EXRAM[MPU_ADDRESS_REGION_END_INX_EXRAM + 1 - MPU_ADDRESS_REGION_START_INX_EXRAM];
static uint8 memory_data_OPROM[MPU_ADDRESS_REGION_END_INX_OPROM + 1 - MPU_ADDRESS_REGION_START_INX_OPROM];
static uint8 memory_data_OPROMR[MPU_ADDRESS_REGION_END_INX_OPROMR + 1 - MPU_ADDRESS_REGION_START_INX_OPROMR];
static uint8 memory_data_ROM[MPU_ADDRESS_REGION_END_INX_ROM + 1 - MPU_ADDRESS_REGION_START_INX_ROM];

MpuAddressMapType mpu_address_map = {
	.map = {
		/*
		 * INDEX 0:RAM
		 */
		{
				.type = GLOBAL_MEMORY,
				.is_malloc = FALSE,
				.permission = MPU_ADDRESS_REGION_PERM_ALL,
				.start = MPU_ADDRESS_REGION_START_INX_RAM,
				.size = sizeof(memory_data_RAM),
				.mask = MPU_ADDRESS_REGION_MASK_ALL,
				.data = memory_data_RAM,
				.ops = &default_memory_operation
		},
		/*
		 * INDEX 1:周辺I/Oレジスタ
		 */
		{
				.type = GLOBAL_MEMORY,
				.is_malloc = FALSE,
				.permission = MPU_ADDRESS_REGION_PERM_ALL,
				.start = MPU_ADDRESS_REGION_START_INX_PH0,
				.size = sizeof(memory_data_PH0),
				.mask = MPU_ADDRESS_REGION_MASK_ALL,
				.data = memory_data_PH0,
				.ops = &default_memory_operation
		},
		/*
		 * INDEX 2:SBRAM
		 */
		{
				.type = GLOBAL_MEMORY,
				.is_malloc = FALSE,
				.permission = MPU_ADDRESS_REGION_PERM_ALL,
				.start = MPU_ADDRESS_REGION_START_INX_SBRAM,
				.size = sizeof(memory_data_SBRAM),
				.mask = MPU_ADDRESS_REGION_MASK_ALL,
				.data = memory_data_SBRAM,
				.ops = &default_memory_operation
		},
		/*
		 * INDEX 0:周辺I/Oレジスタ
		 */
		{
				.type = GLOBAL_MEMORY,
				.is_malloc = FALSE,
				.permission = MPU_ADDRESS_REGION_PERM_ALL,
				.start = MPU_ADDRESS_REGION_START_INX_PH1,
				.size = sizeof(memory_data_PH1),
				.mask = MPU_ADDRESS_REGION_MASK_ALL,
				.data = memory_data_PH1,
				.ops = &default_memory_operation
		},
		/*
		 * INDEX 0:データフラッシュメモリ
		 */
		{
				.type = GLOBAL_MEMORY,
				.is_malloc = FALSE,
				.permission = MPU_ADDRESS_REGION_PERM_ALL,
				.start = MPU_ADDRESS_REGION_START_INX_DTROM,
				.size = sizeof(memory_data_DTROM),
				.mask = MPU_ADDRESS_REGION_MASK_ALL,
				.data = memory_data_DTROM,
				.ops = &default_memory_operation
		},
		/*
		 * INDEX 0:FACI
		 */
		{
				.type = GLOBAL_MEMORY,
				.is_malloc = FALSE,
				.permission = MPU_ADDRESS_REGION_PERM_ALL,
				.start = MPU_ADDRESS_REGION_START_INX_FACI,
				.size = sizeof(memory_data_FACI),
				.mask = MPU_ADDRESS_REGION_MASK_ALL,
				.data = memory_data_FACI,
				.ops = &default_memory_operation
		},
		/*
		 * INDEX 0:PH2
		 */
		{
				.type = GLOBAL_MEMORY,
				.is_malloc = FALSE,
				.permission = MPU_ADDRESS_REGION_PERM_ALL,
				.start = MPU_ADDRESS_REGION_START_INX_PH2,
				.size = sizeof(memory_data_PH2),
				.mask = MPU_ADDRESS_REGION_MASK_ALL,
				.data = memory_data_PH2,
				.ops = &default_memory_operation
		},
		/*
		 * INDEX 0:EXRAM
		 */
		{
				.type = GLOBAL_MEMORY,
				.is_malloc = FALSE,
				.permission = MPU_ADDRESS_REGION_PERM_ALL,
				.start = MPU_ADDRESS_REGION_START_INX_EXRAM,
				.size = sizeof(memory_data_EXRAM),
				.mask = MPU_ADDRESS_REGION_MASK_ALL,
				.data = memory_data_EXRAM,
				.ops = &default_memory_operation
		},
		/*
		 * INDEX 0:OPROM
		 */
		{
				.type = GLOBAL_MEMORY,
				.is_malloc = FALSE,
				.permission = MPU_ADDRESS_REGION_PERM_ALL,
				.start = MPU_ADDRESS_REGION_START_INX_OPROM,
				.size = sizeof(memory_data_OPROM),
				.mask = MPU_ADDRESS_REGION_MASK_ALL,
				.data = memory_data_OPROM,
				.ops = &default_memory_operation
		},
		/*
		 * INDEX 0:OPROMR
		 */
		{
				.type = GLOBAL_MEMORY,
				.is_malloc = FALSE,
				.permission = MPU_ADDRESS_REGION_PERM_ALL,
				.start = MPU_ADDRESS_REGION_START_INX_OPROMR,
				.size = sizeof(memory_data_OPROMR),
				.mask = MPU_ADDRESS_REGION_MASK_ALL,
				.data = memory_data_OPROMR,
				.ops = &default_memory_operation
		},
		/*
		 * INDEX 0:ROM
		 */
		{
				.type = GLOBAL_MEMORY,
				.is_malloc = FALSE,
				.permission = MPU_ADDRESS_REGION_PERM_ALL,
				.start = MPU_ADDRESS_REGION_START_INX_ROM,
				.size = sizeof(memory_data_ROM),
				.mask = MPU_ADDRESS_REGION_MASK_ALL,
				.data = memory_data_ROM,
				.ops = &default_memory_operation
		},
	}
};
