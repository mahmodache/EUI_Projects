/******************************************************************************/
/*                                                                            */
/* !Layer           : Micro-Controller Abstraction Layer (MCAL)               */
/*                                                                            */
/* !Module          : External Interrupt                                      */
/* !Description     : External Interrupt Header file                          */
/*                                                                            */
/* !File            : EXT_INTERRUPT.h                                         */
/*                                                                            */
/* !Coding language : C                                                       */
/*                                                                            */
/* !Project         : interfacing Progect @EME - CLASS 1                      */
/*                                                                            */
/* !Target          : TIVA-C TM4C123GH6PM                                     */
/*                                                                            */
/* !Compiler        : Code Composer Studio 8.3.1                              */
/*                                                                            */
/*                                                                            */
/******************************************************************************/
/* MODIFICATION LOG :                                                         */
/******************************************************************************/
/*                                                                            */
/* !Designed by     : Mahmoud Emara                    !Date : AUG 15, 2023   */
/* !Coded by        : Mahmoud Emara                    !Date : AUG 15, 2023   */
/*                                                                            */
/* Ver 1.0    AUG 23, 2023     Initial release                                */
/******************************************************************************/

#ifndef EXT_INTERRUPT_H_
#define EXT_INTERRUPT_H_

#include "../Service/common_macros.h"
#include "../Service/STD_TYPES.h"




typedef enum
{
    IDLE =0,
    RED_LED_ON,
    GREEN_LED_ON,
    BLUE_LED_ON
}GPIO_enuLedState;

void EXT_Handler_Config(uint8 PORTx, uint8 PINx, uint8 priority );
uint8 EXT_BitHandler( uint8 Portx, uint8 pinx);
void EXT_ClearBitHandler( uint8 Portx, uint8 pinx);

#endif /* EXT_INTERRUPT_H_ */
