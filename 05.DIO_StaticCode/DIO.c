/******************************************************************************/
/*                                                                            */
/* !Layer           : MACL                                                    */
/*                                                                            */
/* !Module          : DIO                                                     */
/* !Description     : DIO module Implementation                               */
/*                                                                            */
/* !File            : DIO.C                                                   */
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
#include "DIO.h"
#include "hw_gpio.h"

Dio_LevelType Dio_ReadChannel( Dio_ChannelType ChannelId )
{
    Dio_LevelType Local_u8Value = 0 ;
    uint8_t Local_u8Port = ChannelId / 8U;
    uint8_t local_u8Pin  = ChannelId % 8U;
    switch (Local_u8Port)
    {
    case PORTA:
        Local_u8Value = (( GPIO_PORTA_DATA_R >> local_u8Pin ) & 1U ) ;
    case PORTB:
        Local_u8Value = (( GPIO_PORTB_DATA_R >> local_u8Pin ) & 1U ) ;
    case PORTC:
        Local_u8Value = (( GPIO_PORTC_DATA_R >> local_u8Pin ) & 1U ) ;
    case PORTD:
        Local_u8Value = (( GPIO_PORTD_DATA_R >> local_u8Pin ) & 1U ) ;
    case PORTE:
        Local_u8Value = (( GPIO_PORTE_DATA_R >> local_u8Pin ) & 1U ) ;
    case PORTF:
        Local_u8Value = (( GPIO_PORTF_DATA_R >> local_u8Pin ) & 1U ) ;
    default
    break;
    }
    return Local_u8Value;
}
void Dio_WriteChannel( Dio_ChannelType ChannelId, Dio_LevelType Level )
{
    uint8_t Local_u8Port = ChannelId / 8U;
    uint8_t local_u8Pin  = ChannelId % 8U;
    switch (Local_u8Port)
    {
    case PORTA:
        GPIO_PORTA_DATA_R |= Level << local_u8Pin ;
    case PORTB:
        GPIO_PORTB_DATA_R |= Level << local_u8Pin ;
    case PORTC:
        GPIO_PORTC_DATA_R |= Level << local_u8Pin ;
    case PORTD:
        GPIO_PORTD_DATA_R |= Level << local_u8Pin ;
    case PORTE:
        GPIO_PORTE_DATA_R |= Level << local_u8Pin ;
    case PORTF:
        GPIO_PORTF_DATA_R |= Level << local_u8Pin ;
    default
    break;
    }
}
Dio_PortLevelType Dio_ReadPort( Dio_PortType PortId )
{
    Dio_PortLevelType Local_u8PortValue =0;

    switch (PortId) {
    case PORTA:
        Local_u8PortValue=GPIO_PORTA_DATA_R;
        break;
    case PORTB:
        Local_u8PortValue=GPIO_PORTB_DATA_R;
        break;
    case PORTC:
        Local_u8PortValue=GPIO_PORTC_DATA_R;
        break;
    case PORTD:
        Local_u8PortValue=GPIO_PORTD_DATA_R;
        break;

    case PORTE:
        Local_u8PortValue=GPIO_PORTE_DATA_R;
        break;
    case PORTF:
        Local_u8PortValue=GPIO_PORTF_DATA_R;
        break;
    default:
        break;
    }

    return Local_u8PortValue;
}
void Dio_WritePort( Dio_PortType PortId , Dio_PortLevelType Level )
{
    switch (PortId) {
    case PORTA:
        GPIO_PORTA_DATA_R = Level ;
        break;
    case PORTB:
        GPIO_PORTB_DATA_R = Level ;
        break;
    case PORTC:
        GPIO_PORTC_DATA_R = Level ;
        break;
    case PORTD:
        GPIO_PORTD_DATA_R = Level ;
        break;

    case PORTE:
        GPIO_PORTE_DATA_R = Level ;
        break;
    case PORTF:
        GPIO_PORTF_DATA_R = Level ;
        break;
    default:
        break;
    }
}
