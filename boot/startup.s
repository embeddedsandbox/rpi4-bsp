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

.include "aarch64.i"
.include "config.i"

.EQU    KERNEL_ENTRY,       0x00080000
.EQU    SYSTEM_TIMER_FREQ,  54000000
.EQU    ARM_LOCAL_CONTROL,  0x4c0000000
.EQU    CACHE_TYPE_MASK,    0x00000007


//-----------------------------------------------------------------------------
// Board init 
//-----------------------------------------------------------------------------
.section .startup
.global _start
_start:
    //-------------------------------------------------------------------------
    // Put the CPU into a default execution state.  This will get fixed up
    // right before we move to another exception level
    //-------------------------------------------------------------------------
    MRS     X1, SCTLR_EL3
    LDR     X0, =SCTLR_EL3_DEFAULT
    MSR     SCTLR_EL3, X0

    MRS     X1, SCTLR_EL2
    LDR     X0, =SCTLR_EL2_DEFAULT
    MSR     SCTLR_EL2, X0

    MRS     X1, HCR_EL2                     // this line is for debug purposes 
    LDR     X0, =HCR_EL2_DEFAULT
    MSR     HCR_EL2, X10

    MRS     X1, SCTLR_EL1
    LDR     X0, =SCTLR_EL1_DEFAULT
    MSR     SCTLR_EL1, X0                   // disable the cache and MMU for EL1

    MRS	    X1, SCR_EL3   
    MOV	    X2, SCR_SECURITY_EXECUTION_STATE_MASK
    AND	    X1, X1, X2
    MOV	    X2, SCR_SECURE_STATE_AARCH64 
    ORR	    X1, X1, X2
    MSR	    SCR_EL3, X1

// Set the SMPEN bit in the CPU Extended Control Reg EL1
    MRS     X0, S3_1_c15_c2_1
    MOV     X1, (1<<6)
    ORR     X0, X0, X1
    MSR     S3_1_c15_c2_1, X0

    MRS     X0, CurrentEL

    //-------------------------------------------------------------------------
    // assumption is that we are at EL3 at this point
    // init all the CPU Registers
    //------------------------------------------------------------------------- 
    MOV	    X0,	XZR
    MOV	    X1, XZR
    MOV	    X2, XZR
    MOV	    X3, XZR
    MOV	    X4, XZR
    MOV	    X5, XZR
    MOV	    X6, XZR
    MOV	    X7, XZR
    MOV	    X8, XZR
    MOV	    X9, XZR
    MOV	    X10, XZR
    MOV	    x11, XZR
    MOV	    X12, XZR
    MOV	    X13, XZR
    MOV	    X14, XZR
    MOV	    X15, XZR
    MOV	    X16, XZR
    MOV	    X17, XZR
    MOV	    X18, XZR
    MOV	    X19, XZR
    MOV	    X20, XZR
    MOV	    X21, XZR
    MOV	    X22, XZR
    MOV	    X23, XZR
    MOV	    X24, XZR
    MOV	    X25, XZR
    MOV	    X26, XZR
    MOV	    X27, XZR
    MOV	    X28, XZR
    MOV	    X29, XZR
    MOV	    X30, XZR

    //-------------------------------------------------------------------------
    // zero the Neon Registers
    //-------------------------------------------------------------------------
    MSR	    CPTR_EL3, XZR
    MSR	    CPTR_EL2, XZR

    FMOV    D0, XZR
    FMOV    D1, XZR
    FMOV    D2, XZR
    FMOV    D3, XZR
    FMOV    D4, XZR
    FMOV    D5, XZR
    FMOV    D6, XZR
    FMOV    D7, XZR
    FMOV    D8, XZR
    FMOV    D9, XZR
    FMOV    D10, XZR
    FMOV    D11, XZR
    FMOV    D12, XZR
    FMOV    D13, XZR
    FMOV    D14, XZR
    FMOV    D15, XZR
    FMOV    D16, XZR
    FMOV    D17, XZR
    FMOV    D18, XZR
    FMOV    D19, XZR
    FMOV    D20, XZR
    FMOV    D21, XZR
    FMOV    D22, XZR
    FMOV    D23, XZR
    FMOV    D24, XZR
    FMOV    D25, XZR
    FMOV    D26, XZR
    FMOV    D27, XZR
    FMOV    D28, XZR
    FMOV    D29, XZR
    FMOV    D30, XZR
    FMOV    D31, XZR

    // Setup CPU specific Stack pointer
    MRS	    X0, MPIDR_EL1               // get the CPU 
    AND	    X0, x0, 0xFF                // X0 now has the cpu

    MOV	    X1, 8		                // 1x8bytes entry per EL per cpu
    MUL	    X1, X0, X1                  // mul by 8
    ADR	    X2, El3_stack_pointer_table
    ADD	    X1, X1, X2 
    LDR	    X1, [x1]
    MOV	    SP, X1    

    //-------------------------------------------------------------------------
    // initialize the CPU specific peripherals (gic, local timer, etc.
    //-------------------------------------------------------------------------
    BL      earlyCpuInitEl3

    //-------------------------------------------------------------------------
    // For now let the primary CPU do any system Init stuff and spin all the
    // CPUs
    //-------------------------------------------------------------------------
    MRS	    X0, MPIDR_EL1               // get the CPU 
    AND	    X0, x0, 0xFF                // X0 now has the cpu
    CMP     X0, XZR
    BNE     cpuSpin

    BL      systemInit

    // WE WILL SKIP EL2 Init
    //  We are going straight to a trusted EL1/EL0 (OS)
    // 

    //-------------------------------------------------------------------------
    // Put the CPU into a default execution state.  This will get fixed up
    // right before we move to another exception level
    //-------------------------------------------------------------------------
    MOV	    X1, SPSR_AARCH64_EL1_SP1    // EL1 Execution State
    MSR	    SPSR_EL3, X1

    ADR	    X1, secureOsInit
    MSR	    ELR_EL3, X1

    ERET

secureOsInit:
    ADR     X4, kernelEntry
    LDR     X4, [X4]
    BR      X4


cpuSpin:
    B       .

//-----------------------------------------------------------------------------
// cache disable & clean
//-----------------------------------------------------------------------------
_cache_disableAndCleanCache:
    // X17  <= CLIDR_EL1
    // X16  <= Max Cache Level
    // W15  <= Current Cache level
    // W14  <= max way register aligned for DC command
    // W13  <= way decrement by value
    // W12  <= max set register aligned for DC command
    // W11  <= set decrement value 
    // w10  <= 1

    // W8   <= current way
    // W7   <= current set

    MRS     X1, SCTLR_EL3	            // get the current sctlr_el3 register
    BIC	    X1, X1, 0x00000004	        // Clear the DCache enable bit
    MSR	    SCTLR_EL3, X1	            // write value back to sctlr_el3

    MRS     X1, CLIDR_EL1
    UBFX    W16, W1, #23, #3 

    CBZ     W0, dcc_done

    MOV     X15, XZR
    MOV     X10, #1

dcc_cacheLevelLoop:
    // figure out if we need to do anything for this cache level
    ADD     W0, W15, W15, LSL #1        // W0 = 3xCache level
    LSR     W1, W17, W0                 // W1 = Cache type for level in W0
    AND     W1, W1, #CACHE_TYPE_MASK    // mas 
    CMP     W1, #2                      
    BLT     dcc_nextCacheLvl            // If this cache level cache type isn't something we need to clear skip it

    // flush this cache level
    LSL     X0, X15, #1                 // put the cache level into the correct git location
    MSR     CSSELR_EL1, X0              // select the next cache level
    ISB                                 // make sure that the cache select has taken affect

    MRS     X0, CCSIDR_EL1              // get the cache size ID register

    // get the Way variables setup
    UBFX    W14, W0, #3, #10            // extract the Max Way value from CCSIDR 
    CLZ     W2, W14                     // Count Leading Zeros (bit position of ways start)

    LSL     W13, W10, W2                // way decrement value
    LSL     W14, w14, W2                // max way register aligned for DC command. 

    // get the Set Variables setup
    AND     W1, W0, #0x00000007         // W1 = log2-4 of the cache line size out of Cache  Size Id reg
    ADD     W1, W1, #4                  // W1 = log2 of cache size   
    UBFX    W12, W0, #13, #14           // extract the Max Set value from CCSIDR
    LSL     W12, W12, W1                // max set aligned for DC command
    LSL     W11, W10, W1                // set decrement value = 1 << log2 of line length aligned for DC Command

    MOV     W8, W14

dcc_wayLoop:
    MOV     W7, W14                     // start over from the max Set

dcc_setLoop:
    ORR     W0, W8, W15, LSL #1         // combine the cache level and the  
    ORR     W0, W0, W7                  //
    DC      CISW, X0                    // Clean and Invalidate Cache line

    SUBS    W7, W7, W11                 // decrement set loop control
    BGE     dcc_setLoop                 // bottom of set loop

    SUBS    X8, X8, X13                 // decrement way loop control
    BGE     dcc_wayLoop                 

dcc_nextCacheLvl:
    DSB     SY
    ADD     W15, W15, #1                // increment to the next cache level
    CMP     W16, W15                    // check if still cache levels to handle 
    BGT     dcc_cacheLevelLoop          // bottom of cache level set loop

dcc_done:

    ret

.section .data
//-----------------------------------------------------------------------------
// Stack pointer Table.  The labels and space associated with them are 
// generated by the linker script
//-----------------------------------------------------------------------------
El3_stack_pointer_table:
    .dword      _el3StackCpu0
    .dword      _el3StackCpu1
    .dword      _el3StackCpu2
    .dword      _el3StackCpu3

//-----------------------------------------------------------------------------
// Interrupt vector Table
//-----------------------------------------------------------------------------

.align (10)
.global El3VectorTable
El3VectorTable:
//--------------------------------------------------------
// Current EL to EL 3 using SP0 (won't use these)
//--------------------------------------------------------
.balign (0x80)
_El3CurrentElSP0Sync:
    BL      El3CurrentElSP0Sync
    ERET

.balign (0x80)
_El3CurrentElSP0IRQ:
    BL       El3CurrentElSP0IRQ
    ERET

.balign (0x80)
_El3CurrentElSP0FIQ:
    BL       El3CurrentElSP0FIQ
    ERET

.balign (0x80)
El3CurrentElSP0SError:
    BL       El3CurrentElSP0SError
    ERET

//--------------------------------------------------------
// Current EL to EL3 using EL3 SP 
//--------------------------------------------------------
.balign (0x80)
_El3CurrentElSPxSync:
    BL       El3CurrentElSPxSync
    ERET

.balign (0x80)
_El3CurrentElSPxIRQ:
    B       El3CurrentElSPxIRQ
    ERET

.balign (0x80)
_El3CurrentElSPxFIQ:
    BL      El3CurrentElSPxFIQ
    ERET

.balign (0x80)
_El3CurrentElSPxSError:
    BL       El3CurrentElSPxSError
    ERET

//--------------------------------------------------------
// Lower aarch64 EL to EL3 using EL3 SP 
//--------------------------------------------------------
.balign (0x80)
_El3LowerlAarch64Sync:
    BL       El3LowerlAarch64Sync
    ERET

.balign (0x80)
_El3LowerElAarch64IRQ:
    BL       El3LowerElAarch64IRQ
    ERET

.balign (0x80)
_El3LowerElAarch64FIQ:
    BL       El3LowerElAarch64FIQ

.balign (0x80)
_El3LowerElAarch64SError:
    BL       El3LowerElAarch64SError
    ERET
//--------------------------------------------------------
// Lower aarch32 EL to EL3 using EL3 SP (won't use these)
//--------------------------------------------------------

.balign (0x80)
_El3LowerlAarch32Sync:
    BL      El3LowerlAarch32Sync
    ERET

.balign (0x80)
_El3LowerElAarch32IRQ:
    BL      El3LowerElAarch32IRQ
    ERET

.balign (0x80)
_El3LowerElAarch32FIQ:
    BL      El3LowerElAarch32FIQ
    ERET

.balign (0x80)
El3LowerElAarch32SError:
    BL      El3LowerElAarch32SError
    ERET
.balign (0x80)

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
.balign (0x100)
crystalSpeed:
    .dword   54000000

deviceTree:
    .dword   0x00000000

kernelEntry:
    .dword   KERNEL_ENTRY

//=============================================================================
//
//=============================================================================
.section .bss
.balign 16;

.space 2048
_el3StackCpu0:

.space 2048;
_el3StackCpu1:

.space 2048;
_el3StackCpu2:

.space 2048;
_el3StackCpu3:


.end
