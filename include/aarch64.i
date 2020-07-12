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
// SCR REGISTER EQUATES
//------------------------------------------------------------------------------
.EQU	SCR_SECURITY_EXECUTION_STATE_MASK,  (~0x0000000401)     // Need to look at this closer. the bit 10 is supposed to be reserved
.EQU	SCR_NON_SECURE_STATE_AARCH64,       ( 0x0000000401)
.EQU	SCR_SECURE_STATE_AARCH64,           ( 0x0000000400)


//------------------------------------------------------------------------------
//  SPSR REGISTER EQUATES
//------------------------------------------------------------------------------
.EQU	SPSR_AARCH64_EL3_SP0,           ( 0x00000000C)
.EQU	SPSR_AARCH64_EL3_SP3,           ( 0x00000000D)
.EQU	SPSR_AARCH64_EL2_SP0,           ( 0x000000008)
.EQU	SPSR_AARCH64_EL2_SP2,           ( 0x000000009)
.EQU	SPSR_AARCH64_EL1_SP0,           ( 0x000000004)
.EQU	SPSR_AARCH64_EL1_SP1,           ( 0x000000005)
.EQU	SPSR_AARCH64_EL0,               ( 0X000000000)


.EQU	SPSR_AARCH64_FIQ_MASK,          ( 0x000000040)
.EQU	SPSR_AARCH64_IRQ_MASK,          ( 0x000000080)
.EQU	SPSR_AARCH64_SERR_MASK,         ( 0x000000100)
.EQU	SPSR_AARCH64_SERR_MASK,         ( 0x000000100)
.EQU	SPSR_AARCH64_DBG_MASK,          ( 0x000000200)


//------------------------------------------------------------------------------
//  HRC REGISTER EQUATES
//------------------------------------------------------------------------------
.EQU	HRC_EXECUTION_STATE_MASK,       (~0X0080000000)
.EQU	HCR_EXECUTION_STATE_AARCH64,    ( 0X0080000000)
.EQU    HCR_SWIO_STATE_MASK,            (~0X0000000002)
.EQU    HCR_SWIO_STATE,                 ( 0X0000000002)
.EQU    HCR_EL2_DEFAULT,                (HCR_EXECUTION_STATE_AARCH64 | HCR_SWIO_STATE)

//------------------------------------------------------------------------------
//  SCTLR REGISTER EQUATES
//------------------------------------------------------------------------------

//.EQU    SCTLR_DSSBS_BIT,                (1<<44)
//.EQU    SCTLR_ATA_BIT,                  (1<<43)
//.EQU    SCTLR_ATA0_BIT,                 (1<<42)
//.EQU    SCTLR_TCF_DISABLE,              (0x0<<40)
//.EQU    SCTLR_TCF_SYNC_EXCEPT,          (0x1<<40)
//.EQU    SCTLR_TCF_ASYNC_EXCEPT,         (0x2<<40)
//.EQU    SCTLR_ITFSB_BIT,                (1<<37)
//.EQU    SCTLR_BT_BIT,                   (1<<36)
//.EQU    SCTLR_BT0_BIT,                  (1<<35)
//.EQU    SCTLR_EnIA_START_BIT,           (1<<31)
//.EQU    SCTLR_EnIB_START_BIT,           (1<<30)
//.EQU    SCTLR_LSMAOE_BIT,               (1<<29)
//.EQU    SCTLR_nTLSMD_BIT,               (1<<28)
//.EQU    SCTLR_EnDA_START_BIT,           (1<<27)
.EQU    SCTLR_UCI_BIT,                  (1<<26)
.EQU    SCTLR_EE_START_BIT,             (1<<25)
.EQU    SCTLR_EOE_BIT,                  (1<<24)
.EQU    SCTLR_SPAN_BIT,                 (1<<23)
.EQU    SCTLR_EIS_START_BIT,            (1<<22)
.EQU    SCTLR_IESB_START_BIT,           (1<<21)
.EQU    SCTLR_TSCXT_BIT,                (1<<20)
.EQU    SCTLR_WXN_START_BIT,            (1<<19)
.EQU    SCTLR_nTWE_BIT,                 (1<<18)
.EQU    SCTLR_nTWI_BIT,                 (1<<16)
.EQU    SCTLR_UCT_BIT,                  (1<<15)
.EQU    SCTLR_DZE_BIT,                  (1<<14)
.EQU    SCTLR_EnDB_START_BIT,           (1<<13)
.EQU    SCTLR_IC_ENABLE_BIT,            (1<<12)
.EQU    SCTLR_EOS_START_BIT,            (1<<11)
.EQU    SCTLR_EnRCTX_BIT,               (1<<10)
.EQU    SCTLR_UMA_BIT,                  (1<<9)
.EQU    SCTLR_SED_BIT,                  (1<<8)
.EQU    SCTLR_ITD_BIT,                  (1<<7)
.EQU    SCTLR_nAA_START_BIT,            (1<<6)
.EQU    SCTLR_CP15BEN_BIT,              (1<<5)
.EQU    SCTLR_SP_ALIGN_CHECK_EL0_BIT,   (1<<4)
.EQU    SCTLR_SP_ALIGN_CHECK_BIT,       (1<<3)
.EQU    SCTLR_DATA_CACHE_ENABLE_BIT,    (1<<2)
.EQU    SCTLR_ALIGN_CHECK_BIT,          (1<<1)
.EQU    SCTLR_MMU_ENABLE_BIT,           (1<<0)



                            
