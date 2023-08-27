/*
 * STK_prog.c
 *
 *  Created on: 18 Aug 2023
 *      Author: dell
 */
#include "Reg.h"
#include "STK_int.h"
#include "../Service/std_types.h"
#include "../Service/common_macros.h"

extern void (*STK_isr)(void);

void STK_Delyms(uint32 Copy_Delayms)
{
//    /*Max count 4192 ms*/
//    /*Program the value of Load*/
//    /*To convert the time to ms we must multiply by 4000*/
//    STK->LOAD=Copy_Delayms*STK_FACTOR;
//    /*Clear current*/
//    STK->CURRENT=0;
//    /*Set the clock source*/
//    CLEAR_BIT(STK->CTRL,STK_CLK_SRC);
//    /*Enable the STK*/
//    SET_BIT(STK->CTRL,STK_ENABLE);
//    /*Busy waiting until it counts to zero*/
//    while(GET_BIT(STK->CTRL,STK_COUNT)==0);

    unsigned long long t;
    t = 1500 * Copy_Delayms;
    while(t)
    {
        t--;
    }
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

