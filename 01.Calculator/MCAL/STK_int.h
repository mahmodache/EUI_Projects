/*
 * STK_int.h
 *
 *  Created on: 18 Aug 2023
 *      Author: dell
 */

#ifndef STK_INT_H_
#define STK_INT_H_

#include "../Service/std_types.h"
/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/
#define STK_CLK_SRC     2

#define STK_COUNT       16

#define STK_ENABLE      0

#define STK_FACTOR      4000UL

/******************************************************************************
 * \Syntax          : void STK_Delyms(u32 Copy_Delayms)
 * \Description     : used for delay of max 4192 ms
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : Copy_Delayms    Delay in ms
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void STK_Delyms(uint32 Copy_Delayms);
void STK_init(uint16 Time_ms, uint8 priority);
void STK_timeReload(uint16 Time_ms);
void STK_SetCallBack(void (*ptr_ext)(void)  );
void STK_dinit(void);
void STK_reInit(void);

void (*STK_isr)(void);

/******************************************** STK Peripheral Definition *********************************************/

#define STK_BASE_ADDRESS                    0xE000E010UL

/******************************************** STK Registers Definition **********************************************/

typedef struct
{
    volatile uint32 CTRL;              /*SysTick Control and Status Register*/
    volatile uint32 LOAD;              /*SysTick Reload Value Register*/
    volatile uint32 CURRENT;           /*SysTick Current Value Register*/
}STK_RegDef_t;

#define STK                       ((STK_RegDef_t*) STK_BASE_ADDRESS)

#endif /* STK_INT_H_ */
