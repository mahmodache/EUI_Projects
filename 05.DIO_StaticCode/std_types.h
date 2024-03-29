/******************************************************************************/
/*                                                                            */
/* !Layer           : General Functions (Service Folder)                      */
/*                                                                            */
/* !Module          : std_types                                               */
/* !Description     : Type defines for common data types                      */
/*                                                                            */
/* !File            : std_types.h                                             */
/*                                                                            */
/* !Coding language : C                                                       */
/*                                                                            */
/* !Project         : Robot Car Project @EME - EUI                            */
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
/* !Designed by     : Mahmoud EMARA                    !Date : SEP 09, 2023   */
/* !Coded by        : Mahmoud EMARA                    !Date : SEP 09, 2023   */
/*                                                                            */
/* Ver 1.0    SEP 13, 2023     Initial release                                */
/******************************************************************************/

#ifndef GENERALFUNCTIONS_STD_TYPES_H_
#define GENERALFUNCTIONS_STD_TYPES_H_

/******************************************************************************/
/******************************** Data Types **********************************/
/******************************************************************************/

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned long int uint32_t;

typedef signed char sint8_t;
typedef signed short int sint16_t;
typedef signed long int sint32_t;
typedef signed long long int sint64_t;

typedef float f32;
typedef double f64;

#define NULL_PTR    ((void*)0)

#endif /* GENERALFUNCTIONS_STD_TYPES_H_ */
