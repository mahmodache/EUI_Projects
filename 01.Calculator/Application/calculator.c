/******************************************************************************/
/*                                                                            */
/* !Layer           : Application                                             */
/*                                                                            */
/* !Module          : Calculator                                              */
/* !Description     : Calculator Module implementation                        */
/*                                                                            */
/* !File            : calculator.c                                            */
/*                                                                            */
/* !Coding language : C                                                       */
/*                                                                            */
/* !Project         : Calculator Project @EME - CLASS 1                       */
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
#include "calculator.h"

/*! Include compiler types header                                             */
#include "../MCAL/EXT_INTERRUPT.h"
#include "../MCAL/STK_int.h"
#include "../HAL/keypad.h"
#include "../MCAL/gpio.h"
#include "../HAL/lcd.h"

/******************************************************************************/
/*********************** Global Variables Declaration *************************/
/******************************************************************************/
extern uint8 currRow;

/******************************************************************************/
/*! \Description Initialise the GPIO pin used in this application             */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void CALC_init(void)
{
    /* Set the Pins used in the KeyPad */
    GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID,   PIN_INPUT);
    GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+(uint8)1, PIN_INPUT);
    GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+(uint8)2, PIN_INPUT);
    GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+(uint8)3, PIN_INPUT);

    /* Set the Pins used in the KeyPad if using interrupt */
#if CALC_KEYPAD_TYPE==CALC_INTERRUPT
    EXT_Handler_Config(PORTB_ID, PIN4_ID, (uint8)2);
    EXT_Handler_Config(PORTB_ID, PIN5_ID, (uint8)2);
    EXT_Handler_Config(PORTB_ID, PIN6_ID, (uint8)2);
    EXT_Handler_Config(PORTB_ID, PIN7_ID, (uint8)2);
#endif

    /* Initialise the KeyPad */
    KEYPAD_init();
}

/******************************************************************************/
/*! \Description : The Super loop of the application handling the system      */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void CALC_start(void)
{
    /* Declare local variables used in the function */
    uint8 key;      /* var to hold the key pressed from the keypad        */
    uint8 prevkey;  /* var to hold the previous key state from the keypad */

    uint8  operand[MaxOperations]={0};  /* array to hold the operand      */
    sint16 numbers[MaxOperations]={0};  /* array to hold the numbers      */

    sint16 NUMcounter = 0;  /* counter of numbers entered in the numbers[]*/
    sint16 OPcounter = 0;   /* counter of operand entered in the operand[]*/
    sint16 enterCounter=0;  /* counter of all entered characters          */

    sint16 syntaxError = 0; /* syntax error flag  , indicate that a syntax error is occurred */
    sint16 resDone =0;      /* equal pressed flag , indicate that '=' is pressed             */
    sint16 secondRowRes=0;  /* second row flag , indicate that entered characters need the second row   */
    sint16 startByOp=0;     /* start by Operand flag , indicate that first character is operand         */
    sint16 negativeKey=0;   /* negative Key flag , indicate that entered character is a negative number */

    /* set the screen to the intro */
    LCD_displayStringRowColumn((uint8)0,(uint8)3,"**Welcome**");
    LCD_displayStringRowColumn((uint8)1,(uint8)2,"OUR CALCUATOR");
    STK_Delyms((uint32)2000);
    LCD_clearScreen();

    while(1)
    {

        prevkey = key ; /* set the prevkey with the previos key entered */

        /* Get the pressed key number,
         * if any switch pressed for more than 500 ms it will considered more than one press */
        key = KEYPAD_getPressedKeyInteruppt();
        currRow = KEYPAD_BUTTON_RELEASED;     /* update the global var (currRow) */
        enterCounter++;

        /*  check if the screen needs to be reset by entering any key */
        if(resDone)
        {
            resDone=0;
            LCD_clearScreen();
            LCD_moveCursor((uint8)0, (uint8)0);
        }else{/* DO NOTHING , For MISRA-C  */};

        /*  check if the first character is operand */
        if(enterCounter == 1 && key > 9 && key != 45 && key != 67 && key != 61)
        {
            startByOp=1;
        }else{/* DO NOTHING , For MISRA-C*/};

        /*  check if the entered characters need the second row */
        if(enterCounter > 16)
        {
            enterCounter =0;
            LCD_moveCursor((uint8)1, (uint8)0); /*  Move the cursor to the second row      */
            secondRowRes =1; /*  set the flag to indicate second row is used */
        }else{/* DO NOTHING , For MISRA-C*/};

        /*  check if the entered key is the clear key */
        if(key == (uint8)'C')
        {
            /* Reset the screen              */
            LCD_clearScreen();
            LCD_moveCursor((uint8)0, (uint8)0);

            /* Reset all the counters        */
            NUMcounter =0;
            OPcounter =0;
            enterCounter=0;
            secondRowRes=0;

            /* Clear numbers[] and operand[] */
            sint16 d=0;
            for(d=0;d<MaxOperations;d++)
            {
                numbers[d]=0;
                operand[d]=(uint8)0;
            }

            continue; /* Start the super loop again */
        }else{/* DO NOTHING , For MISRA-C*/};

        /*  check if the entered key is negative sign */
        if(key == (uint8)'-')
        {
            negativeKey = 1;

            /* if the previous key is number               *
             * then save '+' instead of '-' and,           *
             * then save the number multiplied by "-1"     */
            if(prevkey <= (uint8)9)
            {
                /*  save the '+' operand and this increment the counters  */
                operand[OPcounter]='+';
                OPcounter++;
                NUMcounter++;
            }else{/* DO NOTHING , For MISRA-C*/};

            LCD_displayCharacter(key);

            /* if negative sign is entered this loop is set to wait and take the next character */
            while(negativeKey == (uint8)1)
            {
                STK_Delyms(500);
                key = KEYPAD_getPressedKeyInteruppt();
                if(key <= (uint8)9) /* if the next character is a number save it in numbers[] */
                {
                    LCD_intgerToString(key);   /* display the pressed keypad switch */
                    numbers[NUMcounter] = numbers[NUMcounter]*10+key;
                }
                else if(key =='=')  /* if the character is '=' */
                {
                    numbers[NUMcounter] *= -1; /*save the number multiplied by "-1" in numbers[]   */
                    negativeKey=0; /* clear the negativeKey flag */
                    prevkey=0;
                    break;
                }
                else if(key > 9) /* if the character is an operand  */
                {
                    numbers[NUMcounter] *= -1; /*save the number multiplied by "-1" in numbers[]   */
                    negativeKey=0; /* clear the negativeKey flag */
                    continue;
                }else{/* DO NOTHING , For MISRA-C*/};
            }

        }else{/* DO NOTHING , For MISRA-C*/};

        /* if the entered character is a number save it in numbers[]        */
        if(key <= 9)
        {
            LCD_intgerToString(key);   /* display the pressed keypad switch */

            numbers[NUMcounter] = numbers[NUMcounter]*10+key; /* equation to take an multiple digit number */

        }
        /* the entered character is not a number  */
        else
        {
            LCD_displayCharacter(key); /* display the pressed keypad switch */
            if(key == '=')
            {
                if(prevkey > 9 && prevkey != '=' && prevkey != 'C') /* End with operand */
                {
                    handleSyntaxError(); /* function to handle if any syntax error happened */
                    LCD_moveCursor(1, 0);
                    LCD_displayString("EndByOperand"); /* show the type of error on the LCD */

                    /*  zero the counters and clear the flags */
                    NUMcounter =0;
                    OPcounter =0;
                    syntaxError = 0;
                    enterCounter=0;
                    startByOp=0;
                    resDone=1; /* set the flag of entering the result mode */
                    sint16 d=0;
                    for(d=0;d<MaxOperations;d++)
                    {
                        numbers[d]=0;
                        operand[d]=0;
                    }
                    continue;
                }else{/* DO NOTHING , For MISRA-C*/};

                if(startByOp) /* start with operand */
                {
                    handleSyntaxError(); /* function to handle if any syntax error happened */
                    LCD_moveCursor(1, 0);
                    LCD_displayString("StartByOperand"); /* show the type of error on the LCD */
                    resDone =1 ; /* set the flag of entering the result mode */

                    /*  zero the counters and clear the flags */
                    NUMcounter =0;
                    OPcounter =0;
                    enterCounter=0;
                    secondRowRes=0;
                    startByOp=0;
                    prevkey = 0;
                    sint16 d=0;
                    for(d=0;d<MaxOperations;d++)
                    {
                        numbers[d]=0;
                        operand[d]=0;
                    }

                    continue;
                }else{/* DO NOTHING , For MISRA-C*/};

                resDone = 1; /* set the flag of entering the result mode */

                /****  start the calculation from here  ****/
                /* declaring var for looping*/
                sint16 i=0 , j=0 ;

                /* declaring var counters for shifting the zeros */
                sint16 opZeroCount=0 , numZeroCount=0;

                /* loop on the elements of operand[]    */
                for(i=0 ; i<OPcounter ; i++  )
                {
                    /* if '*' multiply the element inside the numbers[] with next element
                       and save the result in the higher index element                      */
                    if(operand[i]=='*')
                    {
                        operand[i]=0; /* zero the operand that has been handled  */
                        numbers[i+1] = numbers[i]*numbers[i+1];
                        numbers[i]=0; /* zero the lower index element */

                    }
                    /* if '%' divide the element inside the numbers[] with next element
                       and save the result in the higher index element                      */
                    else if(operand[i]=='%')
                    {
                        operand[i]=0;

                        /* if the second element dividing on is zero */
                        if(numbers[i+1] == 0)
                        {
                            handleSyntaxError(); /* function to handle if any syntax error happened */
                            LCD_moveCursor(1, 0);
                            LCD_displayString("DividByZero`"); /* show the type of error on the LCD */
                            syntaxError = 1; /* set the syntax error flag */
                            enterCounter=0;
                            secondRowRes=0;
                            break;
                        }else{/* DO NOTHING , For MISRA-C*/};
                        numbers[i+1] = numbers[i]/numbers[i+1];
                        numbers[i]=0;
                    }else{/* DO NOTHING , For MISRA-C*/};

                }

                /* if the syntax error flag is set */
                if(syntaxError)
                {
                    NUMcounter =0;
                    OPcounter =0;
                    syntaxError = 0;
                    resDone=1;
                    int d=0;
                    for(d=0;d<MaxOperations;d++)
                    {
                        numbers[d]=0;
                        operand[d]=0;
                    }
                    continue;
                }else{/* DO NOTHING , For MISRA-C*/};

                /*  The next 2 loops are shifting the zeros at the end of the array */
                for(j=0 ; j <= NUMcounter ; j++)
                {
                    if(numbers[j] != 0)
                    {
                        numbers[numZeroCount++] = numbers[j];
                    }else{/* DO NOTHING , For MISRA-C*/};
                    if(operand[j] != 0)
                    {
                        operand[opZeroCount++] = operand[j];
                    }else{/* DO NOTHING , For MISRA-C*/};
                }
                while(numZeroCount < MaxOperations )
                {
                    numbers[numZeroCount++] = 0;
                }
                while(opZeroCount < MaxOperations )
                {
                    operand[opZeroCount++] = 0;
                }

                /* zero the variable used in looping and counting to be used again */
                i=0 , j=0 , opZeroCount=0 , numZeroCount=0;

                /* if '+' add the element inside the numbers[] with next element
                   and save the result in the higher index element                      */
                for(i=0 ; i<OPcounter ; i++  )
                {
                    if(operand[i]=='+')
                    {
                        operand[i]=0;
                        numbers[i+1] = numbers[i]+numbers[i+1];
                        numbers[i]=0;
                    }else{/* DO NOTHING , For MISRA-C*/};

                }

                /*  The next 2 loops are shifting the zeros at the end of the array */
                for(j=0 ; j <= NUMcounter ; j++)
                {
                    if(numbers[j] != 0)
                    {
                        numbers[numZeroCount++] = numbers[j];
                    }
                    if(operand[j] != 0)
                    {
                        operand[opZeroCount++] = operand[j];
                    }
                }
                while(numZeroCount < MaxOperations )
                {
                    numbers[numZeroCount++] = 0;
                }
                while(opZeroCount < MaxOperations )
                {
                    operand[opZeroCount++] = 0;

                }

                /* if the entered characters exceeded 16 character move to 2nd row */
                if(secondRowRes)
                {
                    /* Print the result at the end of the characters entered */
                    LCD_moveCursor(1, ++enterCounter);
                    LCD_intgerToString(numbers[0]);
                    secondRowRes=0;
                }
                else /* if not exceeded 16 */
                {
                    /* move to the 2nd row and print the result */
                    LCD_moveCursor(1, 0);
                    LCD_intgerToString(numbers[0]);
                }

                /* reset for the next calculation */
                sint16 d=0;
                for(d=0;d<= NUMcounter;d++)
                {
                    numbers[d]=0;
                    operand[d]=0;
                }
                NUMcounter =0;
                OPcounter =0;
                enterCounter=0;

            }
            /* if the entered operand is not '=' then save the operand in operand[] */
            else
            {
                NUMcounter ++;
                operand[OPcounter]=key;
                OPcounter++;
            }
        }
        STK_Delyms(500);/* Press time */
    }

}
/******************************************************************************/
/*! \Description :  function to handle if any syntax error happened           */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void handleSyntaxError(void)
{
    LCD_clearScreen();
    LCD_moveCursor(0,0);
    LCD_displayString("Syntax Error..");
    STK_Delyms(500);
}
