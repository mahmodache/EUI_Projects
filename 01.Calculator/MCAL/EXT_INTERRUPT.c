/******************************************************************************/
/*                                                                            */
/* !Layer           : Micro-Controller Abstraction Layer (MCAL)               */
/*                                                                            */
/* !Module          : External Interrupt                                      */
/* !Description     : External Interrupt implementation                       */
/*                                                                            */
/* !File            : EXT_INTERRUPT.c                                         */
/*                                                                            */
/* !Coding language : C                                                       */
/*                                                                            */
/* !Project         : interfacing Project @EME - CLASS 1                      */
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

#include "EXT_INTERRUPT.h"
#include "REG.h"
#include "gpio.h"

#define TEST 1


#if TEST == 2
extern void (*GPIOA_isr)(void);
extern void (*GPIOB_isr)(void);
extern void (*GPIOC_isr)(void);
extern void (*GPIOD_isr)(void);
extern void (*GPIOE_isr)(void);
extern void (*GPIOF_isr)(void);
#endif


void EXT_Handler_Config(uint8 PORTx, uint8 pinx, uint8 priority )
{
    switch (PORTx) {
            case PORTA_ID :

                            CLEAR_BIT(GPIO_PORTA_IS_R,pinx);
                            CLEAR_BIT(GPIO_PORTA_IBE_R,pinx);
                            CLEAR_BIT(GPIO_PORTA_IEV_R,pinx);
                            SET_BIT(GPIO_PORTA_ICR_R,pinx);
                            NVIC_PRI0_R |= priority<5;
                            SET_BIT(GPIO_PORTA_IM_R,pinx);
                            SET_BIT(NVIC_EN0_R,0);

                            break;

            case PORTB_ID :
                            CLEAR_BIT(GPIO_PORTB_IS_R,pinx);
                            CLEAR_BIT(GPIO_PORTB_IBE_R,pinx);
                            CLEAR_BIT(GPIO_PORTB_IEV_R,pinx);
                            SET_BIT(GPIO_PORTB_ICR_R,pinx);
                            NVIC_PRI0_R |= priority<13;
                            SET_BIT(GPIO_PORTB_IM_R,pinx);
                            SET_BIT(NVIC_EN0_R,1);

                            break;

            case PORTC_ID :
                            CLEAR_BIT(GPIO_PORTC_IS_R,pinx);
                            CLEAR_BIT(GPIO_PORTC_IBE_R,pinx);
                            CLEAR_BIT(GPIO_PORTC_IEV_R,pinx);
                            SET_BIT(GPIO_PORTC_ICR_R,pinx);
                            NVIC_PRI0_R |= priority < 21;
                            SET_BIT(GPIO_PORTC_IM_R,pinx);
                            SET_BIT(NVIC_EN0_R,2);

                            break;
            case PORTD_ID :
                            CLEAR_BIT(GPIO_PORTD_IS_R,pinx);
                            CLEAR_BIT(GPIO_PORTD_IBE_R,pinx);
                            CLEAR_BIT(GPIO_PORTD_IEV_R,pinx);
                            SET_BIT(GPIO_PORTD_ICR_R,pinx);
                            NVIC_PRI0_R |= priority < 29;
                            SET_BIT(GPIO_PORTD_IM_R,pinx);
                            SET_BIT(NVIC_EN0_R,3);
                            break;

            case PORTE_ID :

                            CLEAR_BIT(GPIO_PORTE_IS_R,pinx);
                            CLEAR_BIT(GPIO_PORTE_IBE_R,pinx);
                            CLEAR_BIT(GPIO_PORTE_IEV_R,pinx);
                            SET_BIT(GPIO_PORTE_ICR_R,pinx);
                            NVIC_PRI1_R |= priority < 5;
                            SET_BIT(GPIO_PORTE_IM_R,pinx);
                            SET_BIT(NVIC_EN0_R,4);

                            break;

            case PORTF_ID :

                            CLEAR_BIT(GPIO_PORTF_IS_R,pinx);
                            CLEAR_BIT(GPIO_PORTF_IBE_R,pinx);
                            CLEAR_BIT(GPIO_PORTF_IEV_R,pinx);
                            SET_BIT(GPIO_PORTF_ICR_R,pinx);
                            NVIC_PRI7_R |= priority < 21;
                            SET_BIT(GPIO_PORTF_IM_R,pinx);
                            SET_BIT(NVIC_EN0_R,30);

                            break;

            default:
                break;
        }


}


void EXT_ClearBitHandler( uint8 Portx, uint8 pinx)
{
    switch (Portx) {
        case PORTA_ID:

                    SET_BIT(GPIO_PORTA_ICR_R,pinx);
                    break;

        case PORTB_ID:

                    SET_BIT(GPIO_PORTB_ICR_R,pinx);
                    break;

        case PORTC_ID:

                    SET_BIT(GPIO_PORTC_ICR_R,pinx);
                    break;

        case PORTD_ID:

                    SET_BIT(GPIO_PORTD_ICR_R,pinx);
                    break;

        case PORTE_ID:

                    SET_BIT(GPIO_PORTE_ICR_R,pinx);
                    break;

        case PORTF_ID:

                    SET_BIT(GPIO_PORTF_ICR_R,pinx);
                    break;

        default:
            break;
    }
}

uint8 EXT_BitHandler( uint8 Portx, uint8 pinx)
{
    uint8 data=0;
    switch (Portx) {
            case PORTA_ID:

                        data = GET_BIT(GPIO_PORTA_MIS_R,pinx);
                        break;

            case PORTB_ID:

                        data = GET_BIT(GPIO_PORTB_MIS_R,pinx);
                        break;

            case PORTC_ID:

                        data = GET_BIT(GPIO_PORTC_MIS_R,pinx);
                        break;

            case PORTD_ID:

                        data = GET_BIT(GPIO_PORTD_MIS_R,pinx);
                        break;

            case PORTE_ID:

                        data = GET_BIT(GPIO_PORTE_MIS_R,pinx);
                        break;

            case PORTF_ID:

                        data = GET_BIT(GPIO_PORTF_MIS_R,pinx);
                        break;

            default:
                break;
        }

    return data;
}

#if TEST == 2
void GPIOA_Handler(void){  GPIOA_isr();  }

void GPIOB_Handler(void){  GPIOB_isr();  }

void GPIOC_Handler(void){  GPIOC_isr();  }

void GPIOD_Handler(void){  GPIOD_isr();  }

void GPIOE_Handler(void){  GPIOE_isr();  }

void GPIOF_Handler(void){  GPIOF_isr();  }
#endif




