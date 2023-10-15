/******************************************************************************/
/*                                                                            */
/* !Layer           : MACL                                                    */
/*                                                                            */
/* !Module          : DIO                                                     */
/* !Description     : DIO module header file                                  */
/*                                                                            */
/* !File            : DIO.h                                                   */
/*                                                                            */
/* !Coding language : C                                                       */
/*                                                                            */
/* !Project         : AutoSAR Static Code Project @EME - EUI                  */
/*                                                                            */
/* !Target          : TIVA-C TM4C123GH6PM                                     */
/*                                                                            */
/* !Compiler        : Code Composer Studio 12.4.0                             */
/*                                                                            */
/*                                                                            */
/******************************************************************************/
/* MODIFICATION LOG :                                                         */
/******************************************************************************/
/*                                                                            */
/* !Designed by     : Mahmoud EMARA                    !Date : OCT 15, 2023   */
/* !Coded by        : Mahmoud EMARA                    !Date : OCT 15, 2023   */
/*                                                                            */
/* Ver 1.0    OCT 15, 2023     Initial release                                */
/******************************************************************************/
#include "std_types.h"
#ifndef DIO_H_
#define DIO_H_

#define STD_LOW             0x00U
#define STD_HIGH            0x01U

#define PORTA               0x00U
#define PORTB               0x01U
#define PORTC               0x02U
#define PORTD               0x03U
#define PORTE               0x04U
#define PORTF               0x05U


typedef uint8_t Dio_ChannelType   ;
typedef uint8_t Dio_PortType      ;
typedef uint8_t Dio_LevelType     ;
typedef uint8_t Dio_PortLevelType ;

Dio_LevelType Dio_ReadChannel( Dio_ChannelType ChannelId );
Dio_PortLevelType Dio_ReadPort( Dio_PortType PortId );
void Dio_WriteChannel( Dio_ChannelType ChannelId, Dio_LevelType Level );
void Dio_WritePort( Dio_PortType PortId , Dio_PortLevelType Level );






#endif /* DIO_H_ */
