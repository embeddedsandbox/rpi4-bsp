//=============================================================================
// Copyright 2020 Daniel Boals & Michael Boals
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
// THE SOFTWARE.
//=============================================================================
#ifndef __GPIO_H__
#define __GPIO_H__

#include "types.h"

typedef struct gpioRegs
{
    volatile uint32_t   gpioSel0;
    volatile uint32_t   gpioSel1;
    volatile uint32_t   gpioSel2;
    volatile uint32_t   gpioSel3;
    volatile uint32_t   gpioSel4;
    volatile uint32_t   gpioSel5;
             uint32_t   reserved0;
    volatile uint32_t   gpioSet0;
    volatile uint32_t   gpioSet1;
             uint32_t   reserved1;
    volatile uint32_t   gpioClear0;
    volatile uint32_t   gpioClear1;
             uint32_t   reserved2;
    volatile uint32_t   gpioLvl0;            
    volatile uint32_t   gpioLvl1;
             uint32_t   reserved3;
    volatile uint32_t   gpioEds0;            
    volatile uint32_t   gpioEds1;             
             uint32_t   reserved4;
    volatile uint32_t   gpioRen0;            
    volatile uint32_t   gpioRen1;
             uint32_t   reserved4;
    volatile uint32_t   gpioFen0;            
    volatile uint32_t   gpioFen1;
             uint32_t   reserved4;
    volatile uint32_t   gpioHen0;            
    volatile uint32_t   gioHenp1;
             uint32_t   reserved4;
    volatile uint32_t   gpioLen0;            
    volatile uint32_t   gpioLen1;
             uint32_t   reserved4;
    volatile uint32_t   gpioAren0;            
    volatile uint32_t   gpioAren1;
             uint32_t   reserved4;
    volatile uint32_t   gpioAfen0;            
    volatile uint32_t   gpioAfen1;    
             uint32_t   reserved4;
    volatile uint32_t   gpioPupPdwnCtrl0;            
    volatile uint32_t   gpioPupPdwnCtrl1;    
    volatile uint32_t   gpioPupPdwnCtrl2;   
    volatile uint32_t   gpioPupPdwnCtrl3;    

} gpioRegs_t;


//-----------------------------------------------------------------------------
//000 = GPIO Pin 19 is an input
//001 = GPIO Pin 19 is an output
//100 = GPIO Pin 19 takes alternate function 0 
//101 = GPIO Pin 19 takes alternate function 1 
//110 = GPIO Pin 19 takes alternate function 2 
//111 = GPIO Pin 19 takes alternate function 3 
//011 = GPIO Pin 19 takes alternate function 4 
//010 = GPIO Pin 19 takes alternate function 5
#define GPIO_FUNC_SELECT_MASK       (0x00000007)
#define GPIO_FUNC_SELECT_INPUT      (0x00000000)
#define GPIO_FUNC_SELECT_OUTPUT     (0x00000001)
#define GPIO_FUNC_SELECT_ALT_0      (0x00000004)
#define GPIO_FUNC_SELECT_ALT_1      (0x00000005)
#define GPIO_FUNC_SELECT_ALT_2      (0x00000006)
#define GPIO_FUNC_SELECT_ALT_3      (0x00000007)
#define GPIO_FUNC_SELECT_ALT_4      (0x00000003)
#define GPIO_FUNC_SELECT_ALT_5      (0x00000002)
#endif 
