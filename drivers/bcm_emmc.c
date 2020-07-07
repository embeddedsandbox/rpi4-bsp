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


#include "bcm_emmc.h"
#include "driver.h"

static status_t bcmEmmcDriverInit(uint32_t* mmio, uint32_t interrupt, uint32_t blkSize, uint32_t pagesToPreErase);
static status_t bcmEmmcSetClockSpeed(uint32_t clkInHz);
static status_t bcmEmmcSetVoltage(uint32_t voltIn10ths);
//static status_t bcmEmmcSendCmd(uint32_t cmd, uint32_t args, uint32_t respType, uint32_t ResponseType, uint32_t TransferType, uint32_t blkCount);

emmcController bcmEmmcEriver = 
{
    .init                       = bcmEmmcDriverInit,
    .setClkSpeed                = bcmEmmcSetClockSpeed,
    .setVoltage                 = bcmEmmcSetVoltage,
//    .sendCmd                    = bcmEmmcSendCmd,
    .getResp                    = NULL,
    .setDataBuffer              = NULL, 
    .setBlocksToPreErase        = NULL, 
    .interruptHandler           = NULL, 
} ;

//  once there is a dynamic memory allocation system
static struct 
{
    uint32_t        inerrupt;    
    bcmEmmcMmio_t*  mmio;
    uint32_t        pagesToPreErase;
    uint32_t        blkSize;
    uint32_t        currentBufferAddress; // need to rethink this for queued commands (maybe we queue at the layer above)
} emmcInfo;


//------------------------------------------------------------------------------
// 
//------------------------------------------------------------------------------
static status_t bcmEmmcDriverInit(uint32_t* mmio, uint32_t interrupt, uint32_t blkSize, uint32_t pagesToPreErase)
{
    emmcInfo.mmio               = (bcmEmmcMmio_t *)mmio;
    emmcInfo.inerrupt           = interrupt;
    emmcInfo.blkSize            = blkSize;
    emmcInfo.pagesToPreErase    = pagesToPreErase;

    //_dmb();
    emmcInfo.mmio->control0                     = (1 <<1);  
    emmcInfo.mmio->control1                     = ( 0x7<<24) | (0x0F<<16) | ((625 & 0xFF)<<8) | ((625<<6) & 0x60 ) | (1<<5) | (1<<2) | (1);
    emmcInfo.mmio->control2                     = ( 1<<23) | (1<<22);

    emmcInfo.mmio->interruptFlagEnable          = (1<<24) | (1<<22) | (1<<21) | (1<<17) | (1<<12) | (1<<8) | (1<<5) | (1<<4) | (1<<2) | (1<<1) | (1<<0);
    emmcInfo.mmio->interruptGenerationEnable    = (1<<24) | (1<<22) | (1<<21) | (1<<17) | (1<<12) | (1<<8) | (1<<5) | (1<<4) | (1<<2) | (1<<1) | (1<<0);
    emmcInfo.mmio->cardClockTuningDdr           = 0;
    emmcInfo.mmio->cardClockTuningStd           = 0;
    emmcInfo.mmio->extensionFifoConfig          = 2;
    emmcInfo.mmio->extensionFifoEnable          = 0;  //disable this for the moment
    emmcInfo.mmio->tuneStep                     = 2;
    emmcInfo.mmio->cardClockTuningStd           = 0;
    emmcInfo.mmio->cardClockTuningDdr           = 0;
    emmcInfo.mmio->spiInterruptSpt              = 0;
//    emmcInfo.mmio->slotInterruptStatusVersion   = 0;
    emmcInfo.mmio->blockSizeCount               = (blkSize << 0) | (0<<16);
    
    return STATUS_SUCCESS;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
static status_t bcmEmmcSetClockSpeed(uint32_t clkInHz)
{
    return STATUS_SUCCESS;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
static status_t bcmEmmcSetVoltage(uint32_t voltIn10ths)
{

    return STATUS_SUCCESS;
}

#if 0
//------------------------------------------------------------------------------
//  args are [7:0] arg0, [15:8] arg1, [23:16] arg2, [31:24] arg3
//------------------------------------------------------------------------------
static status_t bcmEmmcSendCmd(uint32_t cmd, uint32_t args, uint32_t respType, uint32_t ResponseType, uint32_t TransferType, uint32_t blkCount)
{
    uint32_t status = emmcInfo.mmio->status;
    uint32_t control1 = emmcInfo.mmio->control1;

    if ((!(status  & 0x0000007)) && ((control1 & (1<<1)))) // make sure nothing is active and the clock is stable
    {
        emmcInfo.mmio->blockSizeCount = (blkCount << 16) | emmcInfo.blkSize;
        emmcInfo.mmio->arg1 = args;

        uint32_t cmdTmValue = ((cmd & 0x3F) << 24);

        switch(respType)
        {
            case EMMC_RESPONSE_NONE:
            {                
                break;
            }
            case EMMC_RESPONSE_48_BITS:
            {
                cmdTmValue   |= (0x2<<16);                
                break;
            }
            case EMMC_RESPONSE_136_BITS:
            {
                cmdTmValue   |= (0x1<<16);
                break;
            }
        }

        if (blkCount > 0)
        {
            switch  (TransferType)
            {
                case EMMC_TRANSFER_NONE:
                {
                    break;
                }
                case EMMC_TRANSFER_READ_DATA:
                {
                    cmdTmValue |= (1<<21) | (1<<4);
                    if (blkCount > 1)
                    {
                        cmdTmValue |= (1<<5);
                    }                
                    break;
                }

                case EMMC_TRANSFER_WRITE_DATA:
                {
                    cmdTmValue |= (1<<21);
                    if (blkCount > 1)
                    {
                        cmdTmValue |= (1<<5);
                    }                

                    break;
                }
            }
        }
        
        emmcInfo.mmio->cmdTm = cmdTmValue;
    }
    return STATUS_SUCCESS;
}
#endif




