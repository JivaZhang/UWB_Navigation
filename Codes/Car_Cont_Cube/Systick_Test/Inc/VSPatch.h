/**
******************************************************************************
* Patch for VS2015 Editor
* @Copyright Han ZHANG(haldak) | All rights reserved.
******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __VSPATCH_H
#define __VSPATCH_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported macro ------------------------------------------------------------*/
#define __INT64 __int64

/* Exported types ------------------------------------------------------------*/
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __INT64 int64_t;

/* exact-width unsigned integer types */
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __INT64 uint64_t;

/* Exported constants --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __VSPATCH_H */
