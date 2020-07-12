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

//------------------------------------------------------------------------------
// SCTLR_EL3_DEFAULT
//------------------------------------------------------------------------------
.EQU    SCLTR_EL3_RESERVED,         (0b11<<28 | 0b11<<22 | 1<<18 | 1<<16 | 0b11<<4 )
.EQU    SCLTR_EL3_DEFAULT_BITS,     ((SCTLR_SP_ALIGN_CHECK_BIT))
.EQU    SCTLR_EL3_DEFAULT,          (SCLTR_EL3_RESERVED | SCLTR_EL3_DEFAULT_BITS) 

//------------------------------------------------------------------------------
// SCTLR_EL2_DEFAULT
//------------------------------------------------------------------------------
.EQU    SCLTR_EL2_RESERVED,         (0b11<<28 | 0b11<<22 | 1<<18 | 1<<16 | 0b11<<4) // TODO
.EQU    SCLTR_EL2_DEFAULT_BITS,     ((SCTLR_UCI_BIT) | (SCTLR_nTWE_BIT) | (SCTLR_nTWI_BIT) | (SCTLR_SP_ALIGN_CHECK_EL0_BIT) | (SCTLR_SP_ALIGN_CHECK_BIT)) // TODO
.EQU    SCTLR_EL2_DEFAULT,          (SCLTR_EL2_RESERVED | SCLTR_EL2_DEFAULT_BITS)

//------------------------------------------------------------------------------
// SCTLR_EL1_DEFAULT
//------------------------------------------------------------------------------
.EQU    SCLTR_EL1_RESERVED,         (0b11<<28 | 0b11<<22 | 1<<20 | 1<<11)
.EQU    SCLTR_EL1_DEFAULT_BITS,     ((SCTLR_nTWE_BIT) | (SCTLR_nTWI_BIT) | SCTLR_CP15BEN_BIT | (SCTLR_SP_ALIGN_CHECK_EL0_BIT) | (SCTLR_SP_ALIGN_CHECK_BIT))
.EQU    SCTLR_EL1_DEFAULT,          (SCLTR_EL1_RESERVED | SCLTR_EL1_DEFAULT_BITS)

//------------------------------------------------------------------------------
// SCTLR_EL1_DEFAULT
//------------------------------------------------------------------------------

.EQU    SCR_EL3_DEFAULT,            (1<<8)     // TODO
