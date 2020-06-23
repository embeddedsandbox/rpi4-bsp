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
void static inline boot_init_set_sys_freq(uint32_t frequency)
{
    __asm(
        "MSR     CNTFRQ_EL0,  %[freq]        \n"
        :                           //ouputs
        : [freq] "r" (frequency)    //inputs
        :                           //clobbers
    );
}

//==============================================================================
// PUBLIC FUNCTIONS
//==============================================================================

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void boot_init_system_peripheral_clock(void)
{
 //   sys_peripheral_clk->system_clock_control   = ARM_PERIPHERAL_CLOCK_DEFAULT;
 //   sys_peripheral_clk->system_clock_prescaler = 

    boot_init_set_sys_freq(ARM_PERIPHERAL_CLOCK_FREQ);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void systemInit(void)
{
    boot_init_system_peripheral_clock();

}

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

void gicInitEl3(uint32_t cpu)
{
    // set the group of each interrupt in the gic


}

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
