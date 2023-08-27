/******************************************************************************/
/*                                                                            */
/* !Layer           : Application                                             */
/*                                                                            */
/* !Module          : Stop Watch                                              */
/* !Description     : Stop Watch Module implementation                        */
/*                                                                            */
/* !File            : StopWatch.c                                             */
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

/*! Include the module header file                                            */
#include "StopWatch.h"

/*! Include compiler types header                                             */
#include "../MCAL/EXT_INTERRUPT.h"
#include "../MCAL/STK_int.h"
#include "../MCAL/gpio.h"
#include "../HAL/lcd.h"

/******************************************************************************/
/*********************** Global Variables Declaration *************************/
/******************************************************************************/
extern uint8 secondsCount;
extern uint8 Sw1Flag;
extern uint8 Sw2Flag;

/******************************************************************************/
/*! \Description : Initialise the GPIO pin used in this application           */
/*                 and the LCD screen intro setup                             */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void StopWatch_init(void)
{
    /*  Initialise the MCAL layer  */
    GPIO_Init(PORTB_ID);
    GPIO_Init(PORTF_ID);

    /*  Set configration for the Push Bottons   */
    GPIO_setupPinDirection(PORTF_ID, PIN0_ID, PIN_INPUT);
    GPIO_setupPinDirection(PORTF_ID, PIN4_ID, PIN_INPUT);
    EXT_Handler_Config(PORTF_ID, PIN0_ID, 1);
    EXT_Handler_Config(PORTF_ID, PIN4_ID, 3);

    /*  Set the callBack func for the interrupt   */
    STK_SetCallBack(&StopWatch_ISR);
    GPIOF_SetCallBack(&PushButton_ISR);


    /*  Set up the LCD screen intro   */
    LCD_displayStringRowColumn(0,3,"**Welcome**");
    LCD_displayStringRowColumn(1,3,"Stop Watch");
    STK_Delyms(2000);
    LCD_clearScreen();
    LCD_displayString("S1=Stop | S2=Lap");
    LCD_displayStringRowColumn(1, 0, "T.00:00");

    /*  Initialise the Systick timer to count and interrupt each 1000 ms  */
    STK_init(1000, 1);


}

/******************************************************************************/
/*! \Description : The Super loop of the application handling the system      */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void StopWatch_Call(void)
{
    /*  Declare Local variables     */
    uint8 stopflag = 0;
    uint8 minutesCount=0;

    while(1)    /*  System Super Loop   */
    {
        if(Sw1Flag) /*  Check if SW1 is pushed  */
        {
            /*  stopflag to check on the stopwatch state  */
            if(stopflag == 0) /*  stopflag is not set , stop watch state is ON , SW1 func is pause  */
            {
                stopflag=1;  /*  Set the stopflag        */
                Sw1Flag=0;   /*  Clear SW1 global flag   */
                STK_dinit(); /*  Stop the Systick timer  */
            }
            else /*  stopflag is set , stop watch state is OFF , SW1 func is resume  */
            {
                stopflag=0;    /*  Clear the stopflag        */
                Sw1Flag=0;     /*  Clear SW1 global flag     */
                STK_reInit();  /*  start the Systick timer   */
            }
        }
        if(Sw2Flag) /*  Check if SW2 is pushed  */
        {
            /*  stopflag to check on the stopwatch state  */
            if(stopflag) /*  stopflag is set , stop watch state is OFF , SW2 func is reset  */
            {
                Sw2Flag=0;       /*  Clear SW2 global flag           */
                stopflag=0;      /*  Clear the stopflag              */

                /*  Reset all the stop watch variabls and the screen */
                secondsCount=0;
                minutesCount=0;
                LCD_displayStringRowColumn(1, 0, "T.00:00");
                LCD_displayStringRowColumn(1, 9,"L.00:00");
                STK_reInit();    /*  start the Systick timer   */
            }
            else  /*  stopflag is not set , stop watch state is ON , SW2 func is take Laps  */
            {
                Sw2Flag=0;    /*  Clear SW2 global flag     */

                /*  set up the screen to print the lap time */
                LCD_moveCursor(1, 9);
                LCD_displayString("L.00:00");
                if(secondsCount > 9)
                {
                    LCD_moveCursor(1, 14);
                    LCD_intgerToString(secondsCount);

                }
                else
                {
                    LCD_moveCursor(1, 15);
                    LCD_intgerToString(secondsCount);
                }
                if(minutesCount > 9)
                {
                    LCD_moveCursor(1, 11);
                    LCD_intgerToString(minutesCount);
                }
                else
                {
                    LCD_moveCursor(1, 12);
                    LCD_intgerToString(minutesCount);
                }

            }
        }
        /*  if the Seconds Counter var is < 60     *
         * print the seconds on the LCD            */
        if(secondsCount < 60 )
        {
            if(secondsCount<=9)
            {
                LCD_moveCursor(1, 6);
                LCD_intgerToString(secondsCount);
            }
            else
            {
                LCD_displayStringRowColumn(1, 7, " ");
                LCD_moveCursor(1, 5);
                LCD_intgerToString(secondsCount);
            }
        }
        /*  if the Seconds Counter var is > 60       *
         * and the Minutes Counter var is < 60       *
         * Reset the Seconds Counter var             *
         * Increment Minutes Counter var             *
         * print the Minutes on the  LCD             */
        else if(minutesCount < 60 )
        {
            secondsCount=0; /* Reset the Seconds Counter var */
            minutesCount++; /* Increment Minutes Counter var */
            /*  print the Minutes on the  LCD     */
            LCD_displayStringRowColumn(1, 5,"00");
            if(minutesCount<=9)
            {
                LCD_moveCursor(1, 3);
                LCD_intgerToString(minutesCount);
            }
            else
            {
                LCD_moveCursor(1, 2);
                LCD_intgerToString(minutesCount);
            }
        }
        else /*  the stop watch reached its limit , Reset the Stop Watch   */
        {
            Sw2Flag=0;       /*  Clear SW2 global flag           */
            Sw1Flag=0;       /*  Clear SW1 global flag           */
            stopflag=0;      /*  Clear the stopflag              */

            /*  Reset all the stop watch variabls and the screen */
            secondsCount=0;
            minutesCount=0;
            LCD_displayStringRowColumn(1, 0, "T.00:00");
            STK_reInit();    /*  start the Systick timer   */
        }

    }
}

/******************************************************************************/
/*! \Description : ISR function handled by the systick ISR                    */
/*                 to increment the seconds Counter global var                */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void StopWatch_ISR(void)
{
    /* Increment Seconds Counter global variable */
    secondsCount++;
}

/******************************************************************************/
/*! \Description : ISR function handled by the GPIO ISR                       */
/*                 to check which button is pressed                           */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void PushButton_ISR(void)
{
    if(EXT_BitHandler(PORTF_ID,PIN0_ID)) /* check which Pin fired the interrupt */
    {
        Sw1Flag=1; /* assign the value of switch  */
        EXT_ClearBitHandler(PORTF_ID,PIN0_ID); /* clear the flag */
    }
    else if(EXT_BitHandler(PORTF_ID,PIN4_ID))
    {

        Sw2Flag=1;
        EXT_ClearBitHandler(PORTF_ID,PIN4_ID);
    }
    else
    {
        /*  DO Nothing , For MISRA-C  */
    }
}

