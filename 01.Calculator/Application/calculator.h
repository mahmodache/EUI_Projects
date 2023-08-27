/*
 * calculator.h
 *
 *  Created on: 23 Aug 2023
 *      Author: dell
 */

#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#define MaxOperations 10

#define CALC_INTERRUPT   0
#define CALC_PULLING     1
#define MaxOperations   10
#define CALC_KEYPAD_TYPE     CALC_INTERRUPT


void handleSyntaxError(void);
void CALC_init(void);
void CALC_start(void);
void handleSyntaxError(void);

#endif /* CALCULATOR_H_ */
