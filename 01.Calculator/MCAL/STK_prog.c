/******************************************************************************/
/*                                                                            */
/* !Layer           : Micro-Controller Abstraction Layer (MCAL)               */
/*                                                                            */
/* !Module          : Systick                                                 */
/* !Description     : Systick Module Implementation                           */
/*                                                                            */
/* !File            : STK_prog.c                                              */
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
#include "Reg.h"
#include "STK_int.h"
#include "../Service/std_types.h"
#include "../Service/common_macros.h"

extern void (*STK_isr)(void);

void STK_Delyms(uint32 Copy_Delayms)
{
    /*Max count 4192 ms*/
    /*Program the value of Load*/
    /*To convert the time to ms we must multiply by 4000*/
    STK->LOAD=Copy_Delayms*STK_FACTOR;
    /*Clear current*/
    STK->CURRENT=0;
    /*Set the clock source*/
    CLEAR_BIT(STK->CTRL,STK_CLK_SRC);
    /*Enable the STK*/
    SET_BIT(STK->CTRL,STK_ENABLE);
    /*Busy waiting until it counts to zero*/
    while(GET_BIT(STK->CTRL,STK_COUNT)==0);

}
void STK_init(uint16 Time_ms, uint8 priority)
{
    uint32 Reload = (Time_ms* 1000 * 16) - 1;
    NVIC_ST_RELOAD_R = Reload ;
    NVIC_SYS_PRI3_R |= priority < 29;
    SET_BIT(NVIC_ST_CTRL_R,2);
    SET_BIT(NVIC_ST_CTRL_R,1);
    NVIC_ST_CURRENT_R= 0x00;
    SET_BIT(NVIC_ST_CTRL_R,0);

}

void STK_timeReload(uint16 Time_ms)
{
    uint32 Reload = (Time_ms* 1000 * 16) - 1;
    NVIC_ST_RELOAD_R = Reload ;
}
void STK_SetCallBack(void (*ptr_ext)(void)  )
{
    if (ptr_ext != NULL_PTR)
        STK_isr= ptr_ext;
    NVIC_ST_CURRENT_R = 0 ;
}
void SysTick_Handler(void)
{
    STK_isr();
}
void STK_dinit(void)
{
    CLEAR_BIT(NVIC_ST_CTRL_R,0);
}
void STK_reInit(void)
{
    SET_BIT(NVIC_ST_CTRL_R,0);
}

