/******************************************************************************/
/*                                                                            */
/* !Layer           : Micro-Controller Abstraction Layer (MCAL)               */
/*                                                                            */
/* !Module          : General Purpose Timer (GPTM)                            */
/* !Description     : GPTM Module implementation                              */
/*                                                                            */
/* !File            : GPTM.c                                                  */
/*                                                                            */
/* !Coding language : C                                                       */
/*                                                                            */
/* !Project         : interfacing Project @EME - CLASS 1                      */
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
/* !Designed by     : Mahmoud Emara                    !Date : AUG 24, 2023   */
/* !Coded by        : Mahmoud Emara                    !Date : AUG 24, 2023   */
/*                                                                            */
/* Ver 1.0    AUG 23, 2023     Initial release                                */
/******************************************************************************/

#include "../Service/std_types.h"
#include "../Service/common_macros.h"
#include "REG.h"
#include "../MCAL/gpio.h"
#include "GPTM.h"

void GPTM_TimerCaptureInit(void)
{
    SET_BIT(SYSCTL_RCGCWTIMER_R,PIN5_ID);  /*Enable clock timer */
    GPIO_Init(PORTD_ID);  /*Enable clock Port D */

    GPIO_PORTD_DIR_R &= ~0x40;
    GPIO_PORTD_DEN_R |= 0x40;
    GPIO_PORTD_AFSEL_R |= 0x40;
    GPIO_PORTD_PCTL_R &= ~0x0F000000;
    GPIO_PORTD_PCTL_R |= 0x07000000;

    WTIMER5_CTL_R &= ~1;
    WTIMER5_CFG_R = 4;


}






