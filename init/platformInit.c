//==============================================================================
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
//==============================================================================

#include "../../rtos/include/process.h"


void OsInit(void)
{

}


void _uKswitchToTask(ProcessState_t * taskState)
{
#if 0
    __asm(
    "   // Setup the stack pointer for the application layer                    \n"
    "   ADR	    X2, app_stack_pointer_table                                     \n"
    "   ADD	    X1, X1, X2                                                      \n"
    "   LDR	    X1, [x1]                                                        \n"
    "   MSR	    SP_EL0, X1                                                      \n"
    "   // Setup the Execution state of EL0                                     \n"
    "   MOV	    X1, SPSR_AARCH64_EL0        // EL1 Execution State              \n"
    "   MSR	    SPSR_EL1, X1                                                    \n"
    "   ADR	    X0, taskStart                                                   \n"
    "   MSR	    ELR_EL1, X0                                                     \n"
    "   ERET                                                                    \n"
    :
    :
    :
    );
#endif
}