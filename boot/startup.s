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

    BL _cache_CleanCache

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
_cache_CleanCache:
    // X17  <= CLIDR_EL1
    // X16  <= Max Cache Level
    // W15  <= Current Cache level
    // W14  <= max way register 
    // X13  <= max set register
    // X12  <= log2 line size
    // X11  <= current CCSIDR_EL1
    // X8   <= current way
    // X7   <= current set

    MRS     X1, SCTLR_EL3	            // get the current sctlr_el3 register
    BIC	    X1, X1, 0x00000004	        // Clear the DCache enable bit
    MSR	    SCTLR_EL3, X1	            // write value back to sctlr_el3

    MRS     X17, CLIDR_EL1
    UBFX    W16, W17, #24, #3 

    CBZ     X16, cc_done

    MOV     X15, XZR
    MOV     X10, #1

cc_cacheLevelLoop:
    // figure out if we need to do anything for this cache level
    ADD     X0, X15, X15, LSL #1        // W0 = 3xCache level
    LSR     X1, X17, X0                 // W1 = Cache type for level in W0
    AND     X1, X1, #CACHE_TYPE_MASK    // mas 
    CMP     X1, #2                      
    BLT     cc_nextCacheLvl            // If this cache level cache type isn't something we need to clear skip it

    // flush this cache level
    LSL     X0, X15, #1                 // put the cache level into the correct bit location
    MSR     CSSELR_EL1, X0              // select the next cache level
    ISB                                 // make sure that the cache select has taken affect

    MRS     X11, CCSIDR_EL1             // get the cache size ID register   
    
    AND     X12, X11, #0x7              // X1 = log2-4 of the cache line size out of Cache  Size Id reg
    ADD     X12, X12, #4                // X1 = log2 of cache size   

    // get the max set value - 1
    UBFX    X13, X11, #13, #15          // extract the Max Set value from CCSIDR

    // get the Way variables setup
    UBFX    X14, X11, #3, #10           // extract the Max Way value from CCSIDR 
    CLZ     W2, W14                     // Count Leading Zeros (bit position of ways start)

    MOV     X8, 0                       // start with way 0

cc_wayLoop:
    MOV     X7, 0                       // start with set 0

cc_setLoop:
    LSL     X0, X8,  X2
    ORR     X0, X15, X0
    LSL     X3, X7,  X12
    ORR     X0, X0,  X3

    DC      CISW, X0                    // Clean and Invalidate Cache line

    ADD     X7, X7, #1                   // increment current set value
    CMP     X7, X13
    BLE     cc_setLoop                 

    ADD     X8, X8, #1                   // increment way value
    CMP     X8, X14
    BLE     cc_wayLoop                 

cc_nextCacheLvl:
    DSB     SY                          // wait for all everything to complete for that loop
    ADD     X15, X15, #1                // increment to the next cache level
    CMP     X15, X16                    // check if still cache levels to handle 
    BLE     cc_cacheLevelLoop           // bottom of cache level set loop

cc_done:

    IC IALLU                            // invalidate all of the instruction cache
    DMB     SY

    // RE-ENABLE THE CACHE here
    MRS     X1, SCTLR_EL3	            // get the current sctlr_el3 register
    MOV     X0, #(1<<2) | (1<<12)
    ORR	    X1, X1, X0                  // Set the Cache enable bits
    MSR	    SCTLR_EL3, X1	            // write value back to sctlr_el3

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
