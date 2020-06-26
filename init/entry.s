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



.include "aarch64.i"

//-----------------------------------------------------------------------------
// reinitialize the CPU registers
//-----------------------------------------------------------------------------
.section .entry
.global _entry
_entry:

    MRS     X30, CurrentEL  // assume we are in EL1
    B       .

//-----------------------------------------------------------------------------
// Setup the SP for each EL1
//-----------------------------------------------------------------------------
    MRS	    X0, MPIDR_EL1               // get the CPU 
    AND	    X0, x0, 0xFF                // x0 now has the cpu

    MOV	    X1, 16                      // 1x4bytes entry per EL per cpu
    MUL	    X1, X0, X1                  // mul by 4
    ADR	    X2, El1_stack_pointer_table
    ADD	    X1, X1, X2 
    LDR	    X1, [x1]
    MOV	    SP, X1

//-----------------------------------------------------------------------------
// init MPU & VA
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Enable and MMU Cache
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//  allow the OS to initialize itself
//-----------------------------------------------------------------------------
    
    // one way ticket to the Os
    B	    OsInit 

#
# We will sit in EL1 in secondary loop
#
secondaryCpuLoop:
    WFE
    B	secondaryCpuLoop

.section .data
.balign(16)
El1_stack_pointer_table:
    .quad   _el1StackCpu0
    .quad   _el1StackCpu1
    .quad   _el1StackCpu2
    .quad   _el1StackCpu3

//-----------------------------------------------------------------------------
// Security Monitor Vector Table
//-----------------------------------------------------------------------------

.align (9)

//-----------------------------------------------------------------------------
// Secure Os Vector Table
//-----------------------------------------------------------------------------
.align (8)
SecureOsVectorTable:
//-------------------------
// current EL with SP0
//-------------------------
sos_synchronous_cur_el_sp0:
    B	.

.align(8)
sos_irq_cur_el_sp0:
    B	.

.align(8)
sos_fiq_cur_el_sp0:
    B	.

.align(8)
sos_serr_cur_el_sp0:
    B	.

//-------------------------
// current EL with SPX
//-------------------------
.align(8)
sos_synchronous_cur_el_spx:
    B	.

.align(8)
sos_irq_cur_el_spx:
    B	.

.align(8)
sos_fiq_cur_el_spx:
    B	.

.align(8)
sos_serr_cur_el_spx:
    B	.

//-------------------------
// Lower EL using aarch64
//-------------------------
.align(8)
sosSyncLwrEl_aarch64:
    B	.

.align(8)
sosIrqLwrEl_aarch64:
    B	.

.align(8)
sosFiqLwrEl_aarch64:
    B	.

.align(8)
sosSerrLwrEl_aarch64:
    B	.


//-------------------------
// Lower EL using aarch32
//-------------------------
.align(8)
sosSyncLwrEl_aarch32:
    B	.

.align(8)
sosIrqLwrEl_aarch32:
    B	.

.align(8)
sosFiqLwrEl_aarch32:
    B	.

.align(8)
sosSerrLwrEl_arch32:
    B	.


    .end
