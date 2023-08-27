/******************************************************************************/
/*                                                                            */
/* !Layer           : Application                                             */
/*                                                                            */
/* !Module          : Stop Watch                                              */
/* !Description     : Stop Watch Module Header File                           */
/*                                                                            */
/* !File            : StopWatch.h                                             */
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

#ifndef STOPWATCH_H_
#define STOPWATCH_H_


/******************************************************************************/
/*************************** Functions Declaration ****************************/
/******************************************************************************/

/******************************************************************************/
/*! \Description : Initialise the GPIO pin used in this application           */
/*                 and the LCD screen intro setup                             */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void StopWatch_init(void);

/******************************************************************************/
/*! \Description : The Super loop of the application handling the system      */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void StopWatch_Call(void);

/******************************************************************************/
/*! \Description : ISR function handled by the systick ISR                    */
/*                 to increment the seconds Counter global var                */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void StopWatch_ISR(void);

/******************************************************************************/
/*! \Description : ISR function handled by the GPIO ISR                       */
/*                 to check which button is pressed                           */
/*! \return      None                                                         */
/*! \arguments   None                                                         */
/******************************************************************************/
void PushButton_ISR(void);


#endif /* STOPWATCH_H_ */
