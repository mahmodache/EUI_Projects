/******************************************************************************/
/*                                                                            */
/* !Layer           : Application                                             */
/*                                                                            */
/* !Module          : main                                                    */
/* !Description     : Main Module implementation                              */
/*                                                                            */
/* !File            : main.c                                                  */
/*                                                                            */
/* !Coding language : C                                                       */
/*                                                                            */
/* !Project         : Stop watch | EME - CLASS 1                              */
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
/* !Designed by     : Mahmoud Emara                    !Date : AUG 23, 2023   */
/* !Coded by        : Mahmoud Emara                    !Date : AUG 23, 2023   */
/*                                                                            */
/* Ver 1.0    AUG 23, 2023     Initial release                                */
/******************************************************************************/

/*! Include compiler types header                                             */
#include "Application/StopWatch.h"
#include "MCAL/EXT_INTERRUPT.h"
#include "MCAL/STK_int.h"
#include "HAL/keypad.h"
#include "MCAL/gpio.h"
#include "HAL/lcd.h"

/******************************************************************************/
/*********************** Global Variables Externs *****************************/
/******************************************************************************/
extern uint8 currRow=KEYPAD_BUTTON_PRESSED;
extern uint8 secondsCount=0;
extern uint8 Sw1Flag=0;
extern uint8 Sw2Flag=0;



void main(void)
{
    LCD_init();       /* Initialise the LCD    */
    StopWatch_init(); /* Initialise Stop watch */
    StopWatch_Call(); /* Start the Stop watch  */

}

