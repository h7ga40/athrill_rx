#ifndef _MPU_CONFIG_H_
#define _MPU_CONFIG_H_

#include "std_types.h"
#include "loader/elf.h"

#define MPU_CONFIG_REGION_NUM		UINT_C(11)

#define MPU_ADDRESS_REGION_INX_RAM		(0U)
#define MPU_ADDRESS_REGION_INX_PH0      (1U)
#define MPU_ADDRESS_REGION_INX_SBRAM    (2U)
#define MPU_ADDRESS_REGION_INX_PH1      (3U)
#define MPU_ADDRESS_REGION_INX_DTROM    (4U)
#define MPU_ADDRESS_REGION_INX_FACI     (5U)
#define MPU_ADDRESS_REGION_INX_PH2      (6U)
#define MPU_ADDRESS_REGION_INX_EXRAM    (7U)
#define MPU_ADDRESS_REGION_INX_OPROM    (8U)
#define MPU_ADDRESS_REGION_INX_OPROMR   (9U)
#define MPU_ADDRESS_REGION_INX_ROM      (10U)

#define ELF_MACHINE_TYPE	EM_RX


#endif /* _MPU_CONFIG_H_ */
