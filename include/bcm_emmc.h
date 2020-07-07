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
#ifndef __BMC_EMMC_H__
#define __BMC_EMMC_H__

#include "types.h"

//-----------------------------------------------------------------------------
// Memory Mapped Registers
//-----------------------------------------------------------------------------
typedef struct bcm_emmc
{
    volatile uint32_t       arg2;
    volatile uint32_t       blockSizeCount;
    volatile uint32_t       arg1;
    volatile uint32_t       cmdTm;
    volatile uint32_t       resp0;
    volatile uint32_t       resp1;
    volatile uint32_t       resp2;
    volatile uint32_t       resp3;
    volatile uint32_t       data;
    volatile uint32_t       status;
    volatile uint32_t       control0;
    volatile uint32_t       control1;
    volatile uint32_t       interrupt;
    volatile uint32_t       interruptFlagEnable;
    volatile uint32_t       interruptGenerationEnable;
    volatile uint32_t       control2;
    volatile uint32_t       forceInterruptEvent;
    volatile uint32_t       bootTimeout;
    volatile uint32_t       debugSelect;
    volatile uint32_t       extensionFifoConfig;
    volatile uint32_t       extensionFifoEnable;
    volatile uint32_t       tuneStep;
    volatile uint32_t       cardClockTuningStd;
    volatile uint32_t       cardClockTuningDdr;
    volatile uint32_t       spiInterruptSpt;
    volatile uint32_t       slotInterruptStatusVersion;
}bcmEmmcMmio_t;


//-----------------------------------------------------------------------------
// CMDs
//-----------------------------------------------------------------------------








#endif
