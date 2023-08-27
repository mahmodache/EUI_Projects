/******************************************************************************/
/*                                                                            */
/* !Layer           : Hardware Abstraction Layer (HAL)                        */
/*                                                                            */
/* !Module          : Keypad                                                  */
/* !Description     : Keypad Module implementation                            */
/*                                                                            */
/* !File            : Keypad.c                                                */
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
/* !Designed by     : Mahmoud Emara                    !Date : AUG 20, 2023   */
/* !Coded by        : Mahmoud Emara                    !Date : AUG 20, 2023   */
/*                                                                            */
/* Ver 1.0    AUG 23, 2023     Initial release                                */
/******************************************************************************/


#include "../HAL/keypad.h"
#include "../MCAL/gpio.h"
#include "../MCAL/EXT_INTERRUPT.h"

/*******************************************************************************
 *                      Global var                                             *
 *******************************************************************************/
uint8 col=0;
uint8 Columnflag = 1U;
extern uint8 currRow;

#ifndef STANDARD_KEYPAD

#if (KEYPAD_NUM_COLS == 3)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x3 keypad
 */
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number);
#elif (KEYPAD_NUM_COLS == 4)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x4 keypad
 */
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number);
#endif

#endif /* STANDARD_KEYPAD */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void KEYPAD_init(void)
{
    GPIOB_SetCallBack(&KEYPAD_ISR);
}
uint8 KEYPAD_getPressedKey(void)
{
    uint8 col,row;
    GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID, PIN_INPUT);
    GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+1, PIN_INPUT);
    GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+2, PIN_INPUT);
    GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+3, PIN_INPUT);

    GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID, PIN_INPUT);
    GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+1, PIN_INPUT);
    GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+2, PIN_INPUT);
#if(KEYPAD_NUM_COLS == 4)
    GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+3, PIN_INPUT);
#endif

    while(1)
    {
        for(row=0 ; row<KEYPAD_NUM_ROWS ; row++) /* loop for rows */
        {
            /*
             * Each time setup the direction for all keypad port as input pins,
             * except this row will be output pin
             */
            GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,PIN_OUTPUT);

            /* Set/Clear the row output pin */
            GPIO_writePin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+row, KEYPAD_BUTTON_PRESSED);

            for(col=0 ; col<KEYPAD_NUM_COLS ; col++) /* loop for columns */
            {
                /* Check if the switch is pressed in this column */
                if(GPIO_readPin(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID+col) == KEYPAD_BUTTON_PRESSED)
                {
#if (KEYPAD_NUM_COLS == 3)
#ifdef STANDARD_KEYPAD
                    return ((row*KEYPAD_NUM_COLS)+col+1);
#else
                    return KEYPAD_4x3_adjustKeyNumber((row*KEYPAD_NUM_COLS)+col+1);
#endif
#elif (KEYPAD_NUM_COLS == 4)
#ifdef STANDARD_KEYPAD
                    return ((row*KEYPAD_NUM_COLS)+col+1);
#else
                    return KEYPAD_4x4_adjustKeyNumber((row*KEYPAD_NUM_COLS)+col+1);
#endif
#endif
                }
            }
            GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,PIN_INPUT);
        }
    }
}

uint8 KEYPAD_getPressedKeyInteruppt(void)
{
    uint8 row ;
    GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID,   PIN_INPUT);
    GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+1, PIN_INPUT);
    GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+2, PIN_INPUT);
    GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+3, PIN_INPUT);

    GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID,   PIN_INPUT);
    GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+1, PIN_INPUT);
    GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+2, PIN_INPUT);
    GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+3, PIN_INPUT);


    while(1)
    {
        for(row=0 ; row<KEYPAD_NUM_ROWS ; row++) /* loop for rows */
        {
            /*
             * Each time setup the direction for all keypad port as input pins,
             * except this row will be output pin
             */
            GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,PIN_OUTPUT);

            /* Set/Clear the row output pin */
            GPIO_writePin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+row, KEYPAD_BUTTON_PRESSED);
            currRow = GPIO_readPin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+row);

                /* Check if the switch is pressed in this column */
                if(Columnflag == KEYPAD_BUTTON_PRESSED && currRow == KEYPAD_BUTTON_PRESSED )
                {
                    Columnflag =1U;
                    currRow = KEYPAD_BUTTON_RELEASED;
                    GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,PIN_INPUT);
                    return KEYPAD_4x4_adjustKeyNumber((row*KEYPAD_NUM_COLS)+col);


                }

            GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,PIN_INPUT);
            currRow = KEYPAD_BUTTON_RELEASED;

        }
    }
}

#ifndef STANDARD_KEYPAD

#if (KEYPAD_NUM_COLS == 3)
/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x3 shape
 */
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number)
{
    uint8 keypad_button = 0;
    switch(button_number)
    {
    case 10: keypad_button = '*'; // ASCII Code of *
    break;
    case 11: keypad_button = 0;
    break;
    case 12: keypad_button = '#'; // ASCII Code of #
    break;
    default: keypad_button = button_number;
    break;
    }
    return keypad_button;
} 


#elif (KEYPAD_NUM_COLS == 4)

/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x4 shape
 */
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number)
{
    uint8 keypad_button = 0;
    switch(button_number)
    {
    case 1: keypad_button = 1;
    break;
    case 2: keypad_button = 2;
    break;
    case 3: keypad_button = 3;
    break;
    case 4: keypad_button = '+'; // ASCII Code of %
    break;
    case 5: keypad_button = 4;
    break;
    case 6: keypad_button = 5;
    break;
    case 7: keypad_button = 6;
    break;
    case 8: keypad_button = '*'; /* ASCII Code of '*' */
    break;
    case 9: keypad_button = 7;
    break;
    case 10: keypad_button = 8;
    break;
    case 11: keypad_button = 9;
    break;
    case 12: keypad_button = '-'; /* ASCII Code of '-' */
    break;
    case 13: keypad_button = 'C';  /* ASCII of Enter */
    break;
    case 14: keypad_button = 0;
    break;
    case 15: keypad_button = '='; /* ASCII Code of '=' */
    break;
    case 16: keypad_button = '%'; /* ASCII Code of '+' */
    break;
    default: keypad_button = button_number;
    break;
    }
    return keypad_button;
} 

#endif


void KEYPAD_ISR(void)
{
    if(EXT_BitHandler(PORTB_ID,PIN4_ID)) /* check which Pin fired the interrupt */
     {
         col=1; /* assign the value of the column Number  */
         EXT_ClearBitHandler(PORTB_ID,PIN4_ID); /* clear the flag */
     }
     else if(EXT_BitHandler(PORTB_ID,PIN5_ID))
     {
         col=2;
         EXT_ClearBitHandler(PORTB_ID,PIN5_ID);
     }
     else if(EXT_BitHandler(PORTB_ID,PIN6_ID))
     {
         col=3;
         EXT_ClearBitHandler(PORTB_ID,PIN6_ID);
     }
     else if(EXT_BitHandler(PORTB_ID,PIN7_ID))
     {
         col=4;
         EXT_ClearBitHandler(PORTB_ID,PIN7_ID);
     }
     Columnflag = LOGIC_LOW;
}

#endif /* STANDARD_KEYPAD */
