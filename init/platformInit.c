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

#include "types.h"
#include "../../rtos/include/process.h"
#include "memory.h"
#include "mailbox.h"
#include "framebuffer.h"
#include "platform.h"
#include "mmu.h"

status_t mmuBuildTable(void);


//-----------------------------------------------------------------------------
// platform Init.   Platform Specific Initialization
//-----------------------------------------------------------------------------
void platformInit(void)
{
    mbxMessage_t    mbxMsg;
    uint32_t        resp;

    MbxInitMsgBuffer(&mbxMsg);
    MbxAddMsgTag(&mbxMsg, MBX_VC_GET_FW_VER, NULL);
    MbxAddMsgTag(&mbxMsg, MBX_VC_GET_HW_MDL, NULL);
    MbxAddMsgTag(&mbxMsg, MBX_VC_GET_BRD_VER, NULL);
    MbxAddMsgTag(&mbxMsg, MBX_VC_GET_BRD_MAC, NULL);
    MbxAddMsgTag(&mbxMsg, MBX_VC_GET_BRD_SN, NULL);
    MbxAddMsgTag(&mbxMsg, MBX_VC_GET_ARM_MEM, NULL);
    MbxAddMsgTag(&mbxMsg, MBX_VC_GET_VC_MEM, NULL);
    MbxAddMsgTag(&mbxMsg, MBX_TAG_LAST, NULL);    
    if (MbxSendMsg(&mbxMsg) == STATUS_SUCCESS)
    {        
        MbxUnpackNextTagResp(&mbxMsg, &resp, (uint32_t*)&gFwVersion);
        MbxUnpackNextTagResp(&mbxMsg, &resp, (uint32_t*)&gHwModel);
        MbxUnpackNextTagResp(&mbxMsg, &resp, (uint32_t*)&gBoardVersion);
        MbxUnpackNextTagResp(&mbxMsg, &resp, (uint32_t*)&gMacAddress);
        MbxUnpackNextTagResp(&mbxMsg, &resp, (uint32_t*)&gBoardSerialNumber);
        MbxUnpackNextTagResp(&mbxMsg, &resp, (uint32_t*)gLowMemory);
        MbxUnpackNextTagResp(&mbxMsg, &resp, gVideoMemory);

        switch (gBoardVersion)
        {
            case 0xa03111:
            {
                gTopOfMemory    = (uint64_t)(1LL*1024LL*1024LL*1024LL) - 1;
                break;
            }

            case 0xb03111:
            case 0xb03112:
            {
                gTopOfMemory    = (uint64_t)(2LL*1024LL*1024LL*1024LL) - 1;
                break;
            }

            case 0xc03111:
            case 0xc03112:
            {
                gTopOfMemory    = (uint64_t)(4LL*1024LL*1024LL*1024LL) - 1;
                break;
            }            
        }
    }

    _brk();  
    uintptr_t mmuTranslationTableStart = gTopOfMemory - (100 * 1024 * 1024) + 1;
    uintptr_t mmuTranslationTableSize = (100 * 1024 * 1024);
    MmuInit(mmuTranslationTableStart, mmuTranslationTableSize);

    FbInit(); 
}


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
status_t mmuBuildTable()
{
    // map the Kernel Memory 
    uint64_t memoryRegionStart = 0;
    uint64_t memoryRegionSize = 0xFFFFF; // 1st 1 Meg of RAM is for the kernel (for now)
    MmuMapRange(memoryRegionStart, memoryRegionStart, memoryRegionSize, 0, 0); // Normal Memory Cache enabled privileged 

    // map the memory range from 0 to the start of Video RAM
    memoryRegionStart = 0x100000;
    memoryRegionSize = gLowMemory[1];
    MmuMapRange(memoryRegionStart, memoryRegionStart, memoryRegionSize, 0, 0); // Normal Memory Cache enabled not privileged

    // map the memory range for Video RAM
    memoryRegionStart = gVideoMemory[0];
    memoryRegionSize = gVideoMemory[1];
    MmuMapRange(memoryRegionStart, memoryRegionStart, memoryRegionSize, 0, 0);  // Cache disabled privileged 

    // Map the reset of Memory below the TTs
    memoryRegionStart = ((1024) * (1024) * (1024));
    memoryRegionSize = (gTopOfMemory - memoryRegionStart - (100 * 1024 * 1024) + 1);
    MmuMapRange(memoryRegionStart, memoryRegionStart, memoryRegionSize, 0, 0);  // Normal Memory Cache enabled not Privileged 

    // Map TTs
    memoryRegionStart = gTopOfMemory - ((1024) * (1024) * (1024)) + 1;
    memoryRegionSize = (100 * 1024 * 1024);
    MmuMapRange(memoryRegionStart, memoryRegionStart, memoryRegionSize, 0, 0);  // Normal Memory Cache enabled Privileged  

#if 0
    // Map The Gic Distributor MMIO
    memoryRegionStart = GIC_START_ADDRESS;
    memoryRegionSize = ;
    MmuMapRange(memoryRegionStart, memoryRegionStart, memoryRegionSize, 0, 0);  // Device Memory Disabled Cache privileged 

    // Map The Gic CPU MMIO
    memoryRegionStart = GIC_START_ADDRESS;
    memoryRegionSize = ;
    MmuMapRange(memoryRegionStart, memoryRegionStart, memoryRegionSize, 0, 0);  // Device Memory Disabled Cache privileged 

    // Map EMMC MMIO
    memoryRegionStart = GIC_START_ADDRESS;
    memoryRegionSize = ;
    MmuMapRange(memoryRegionStart, memoryRegionStart, memoryRegionSize, 0, 0);  // Device Memory Disabled Cache privileged 
#endif 
    return STATUS_SUCCESS;
}
