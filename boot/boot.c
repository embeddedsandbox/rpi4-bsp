//=============================================================================
// Copyright 2020 Daniel Boals & Michael Boals
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//
//==============================================================================

#include "types.h"
#include "boot.h"
#include "devices.h"
#include "gic400.h"
#include "gic400_internal.h"

//=============================================================================
// LOCAL VARIABLES
//=============================================================================
volatile system_peripheral_clk_t* sys_peripheral_clk = (system_peripheral_clk_t*) ARM_PERIPHERAL_CLOCK_CONTROL;

//=============================================================================
// LOCAL FUNCTIONS
//=============================================================================

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
uint32_t static inline getCpuId(void)
{
    uint32_t cpuId;

    __asm(
        "   MRS         X0, MPIDR_EL1               // get the CPU\n"
        "   AND         %[result], X0, 0xFF         // X0 now has the cpu\n"
        : [result] "=r" (cpuId)     //outputs
        :                           //inputs
        :                           //clobbers
    );

    return cpuId;
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void static inline bootInitSetSysFreq(uint32_t frequency)
{
    __asm(
        "MSR     CNTFRQ_EL0,  %[freq]        \n"
        :                           //ouputs
        : [freq] "r" (frequency)    //inputs
        :                           //clobbers
    );
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void initGicCpu(void)
{
    gic400CpuMmio_t*    gicCpuMmio  = (gic400CpuMmio_t*)((0x4C0420000));
    
    gicCpuMmio->intPriorityMask     = 0xFF;
    gicCpuMmio->ctrl                = 1;
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void initGicDistributor(void)
{
    uint32_t numInterrupts;
    gic400DistributorMmio_t*    gicDistMmio = (gic400DistributorMmio_t*)((0x4C0410000));


    gicDistMmio->ctrl = 0;              // disable the gic to do the initialization
    numInterrupts = 32*((gicDistMmio->intCtrlrType & 0x1F)+1);


    // disable all interrupts then clear any pending and active interrupts
    // then let the OS re-enable them as it needs to.

    // Disable all interrupts
    gicDistMmio->intClrEnable[0]            = 0x0000FFFF;
    gicDistMmio->intClrActive[0]            = 0x0000FFFF;
    gicDistMmio->intClrPend[0]              = 0x0000FFFF;


    // disable and clear all interrupts
    for (int idx = 1; idx < numInterrupts/32 ; idx++)
    {
        gicDistMmio->intGroup[idx]                  = 0;    // move all interrupts to group 0
        gicDistMmio->nonSecureAccessControl[idx]    = 0;    // make all interrupts secure
        gicDistMmio->intClrEnable[idx]              = 0xFFFFFFFF;
        gicDistMmio->intClrActive[idx]              = 0xFFFFFFFF;
        gicDistMmio->intClrPend[idx]                = 0xFFFFFFFF;

    }

    // set the priority for each interrupt
    // the default will be priority level 127
    // this puts the all in the middle of the map
    // Group 0 interrupts should always be 0x00-0x7F
    // Group 1 interrupts should always be 0x80-0xFF
    for (int idx = 0; idx < numInterrupts/4; idx++)
    {
        gicDistMmio->intPriority[idx]               = 0x7F7F7F7F;   
    }

    // route all interrupts to all CPUs
    // first 8 regsiters are RO because they are
    // CPU Private
    for (int idx = 8; idx < numInterrupts/4; idx++)
    {
        gicDistMmio->intTargets[idx]    = 0x0F0F0F0F;
    }

    // configure all of the interrupts as level
    for (int idx = 2; idx < numInterrupts/2; idx++)
    {
            // for now set them all to level sensitive
        gicDistMmio->intConfig[idx]     = 0xAAAAAAAA;
    }

    initGicCpu();
}

//==============================================================================
// PUBLIC FUNCTIONS
//==============================================================================

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void bootInitSystemPeripheralXlock(void)
{
    bootInitSetSysFreq(ARM_PERIPHERAL_CLOCK_FREQ);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void systemInit(void)
{
    bootInitSystemPeripheralXlock();
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void exceptionTableInitEl3(uint32_t cpu)
{
    __asm(
        "   ADR     X0, El3VectorTable \n"
        "   MSR     VBAR_EL3, X0\n"
        :                           //input
        :                           //output
        : "x0"                      //clobbers
    );
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void gicInitEl3(uint32_t cpu)
{
    initGicDistributor();
    initGicCpu();

}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void mmuInitEl3(uint32_t cpu)
{

}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void earlyCpuInitEl3(void)
{
    uint32_t    cpu = getCpuId();
    exceptionTableInitEl3(cpu);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void lateCpuInitEl3(void)
{
    uint32_t    cpu = getCpuId();
    gicInitEl3(cpu);
    mmuInitEl3(cpu);
}

//=============================================================================
//  interrupt handlers
//=============================================================================

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void El3CurrentElSP0Sync(void)
{
    while(1){}
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void El3CurrentElSP0IRQ(void)
{
    while(1){}
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void El3CurrentElSP0FIQ(void)
 {
    while(1){}
 }

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void El3CurrentElSP0SError(void)
{
    while(1){}
}

///-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void El3CurrentElSPxSync(void)
{
    while(1){}
}
    
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void El3CurrentElSPxIRQ(void)
{
    while(1){}
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void El3CurrentElSPxFIQ(void)
{
    while(1){}
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void El3CurrentElSPxSError(void)
{
    while(1){}
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void El3LowerlAarch64Sync(void)
{
    while(1){}
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void El3LowerElAarch64IRQ(void)
{
    while(1){}
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void El3LowerElAarch64FIQ(void)
{
    while(1){}
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void El3LowerElAarch64SError(void)
{
    while(1){}
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void El3LowerlAarch32Sync(void)
{
    while(1){}
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void El3LowerElAarch32IRQ(void)
{
    while(1){}
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void El3LowerElAarch32FIQ(void)
{
    while(1){}    
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void El3LowerElAarch32SError(void)
{
    while(1){}
}
