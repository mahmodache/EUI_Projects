/*
 * SW_Timer.c
 *
 *  Created on: Aug 18, 2023
 *      Author:
 */
#include "SW_Timer.h"
#include "../Service/std_types.h"

void SWT_delay(uint32 ms)
{
    uint64 t;
    t = 1500U * (uint64)ms;
    while(t)
    {
        t--;
    }
}

