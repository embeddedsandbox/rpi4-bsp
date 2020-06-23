//==============================================================================
// Copyright 2020 Daniel Boals & Michael Boals
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
// THE SOFTWARE.
//==============================================================================


#include "types.h"

typedef struct 
{
    volatile uint32_t    system_clock_control;
    volatile uint32_t    system_clock_subtract_depricated;
    volatile uint32_t    system_clock_prescaler;
} system_peripheral_clk_t;

#define ARM_PERIPHERAL_CLOCK_DEFAULT    0x800000000
#define ARM_PERIPHERAL_CLOCK_CONTROL    0x4c00000000


// Need to add a way to auto detect the flavor of Raspberry Pi the code is 
// running on
// 54000000  <- RPI 4
// 19000000  <- RPI 3B

#define ARM_PERIPHERAL_CLOCK_FREQ       (54000000)
