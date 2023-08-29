/******************************************************************************/
/*                                                                            */
/* !Layer           : Application                                             */
/*                                                                            */
/* !Module          : Calculator                                              */
/* !Description     : Calculator Module Header file                           */
/*                                                                            */
/* !File            : calculator.h                                            */
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

#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#define MaxOperations 10

#define CALC_INTERRUPT   0
#define CALC_PULLING     1
#define MaxOperations   10
#define CALC_KEYPAD_TYPE     CALC_INTERRUPT



void CALC_init(void);
void CALC_start(void);
void handleSyntaxError(void);

#endif /* CALCULATOR_H_ */
