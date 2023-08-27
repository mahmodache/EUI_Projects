/******************************************************************************/
/*                                                                            */
/* !Layer           : Micro-Controller Abstraction Layer (MCAL)               */
/*                                                                            */
/* !Module          : GPIO                                                    */
/* !Description     : GPIO Module Header file                                 */
/*                                                                            */
/* !File            : gpio.h                                                  */
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

#ifndef GPIO_H_
#define GPIO_H_

#include "../Service/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define NUM_OF_PORTS           6
#define NUM_OF_PINS_PER_PORT   8

#define PORTA_ID               0
#define PORTB_ID               1
#define PORTC_ID               2
#define PORTD_ID               3
#define PORTE_ID               4
#define PORTF_ID               5

#define PIN0_ID                0
#define PIN1_ID                1
#define PIN2_ID                2
#define PIN3_ID                3
#define PIN4_ID                4
#define PIN5_ID                5
#define PIN6_ID                6
#define PIN7_ID                7

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
    PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirectionType;

typedef enum
{
    PORT_INPUT,PORT_OUTPUT=0xFF
}GPIO_PortDirectionType;

void (*GPIOF_isr)(void);
void (*GPIOB_isr)(void);

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void GPIO_Init(uint8 port);

/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction);

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);

/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortDirection(uint8 port_num, uint8 direction);

/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8 port_num, uint8 value);

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(uint8 port_num);

void GPIOF_SetCallBack(void (*ptr_ext)(void));
void GPIOB_SetCallBack(void (*ptr_ext)(void));

#endif /* GPIO_H_ */
