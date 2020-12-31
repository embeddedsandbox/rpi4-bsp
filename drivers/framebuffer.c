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
#include "driver.h"
#include "framebuffer.h"
#include "mailbox.h"



fbDisplayBuffer_t   displays[2]; // TODO get rid of magic number 

status_t frameBufferInit(void* a, uint32_t b)
{
    static mbxMessage_t     fbMbxMsg;
    displays[0].physSpecs.width     = 1280;
    displays[0].physSpecs.height    = 1024;    
    displays[0].virtSpecs.width     = 1280;
    displays[0].virtSpecs.height    = 1024;  
    displays[0].colorDepth          = 32;

    MbxInitMsgBuffer(&fbMbxMsg);
    MbxAddMsgTag(&fbMbxMsg, MBX_FB_ALLOC_BUFF, (uint32_t*)&displays[0].theFrameBuffer);
    MbxAddMsgTag(&fbMbxMsg, MBX_FB_SET_DISP_SPECS, (uint32_t*)&displays[0].physSpecs);
    MbxAddMsgTag(&fbMbxMsg, MBX_FB_SET_VIRT_DISP_SPECS, (uint32_t*)&displays[0].virtSpecs);
    MbxAddMsgTag(&fbMbxMsg, MBX_FB_SET_COLOR_DEPTH, &displays[0].colorDepth);

    MbxAddMsgTag(&fbMbxMsg, MBX_FB_GET_PITCH, &displays[0].pitch);
    MbxAddMsgTag(&fbMbxMsg, MBX_FB_GET_DISP_SPECS, (uint32_t*)&displays[0].physSpecs);
    MbxAddMsgTag(&fbMbxMsg, MBX_FB_GET_COLOR_DEPTH, &displays[0].colorDepth);
    MbxAddMsgTag(&fbMbxMsg, MBX_TAG_LAST, NULL);

    // if we get a bad response.  It is likely that no display is attached
    if (MbxSendMsg(&fbMbxMsg) == STATUS_SUCCESS)
    {
        MbxUnpackNextTagResp(&fbMbxMsg, NULL, (uint32_t*)&displays[0].theFrameBuffer);
        MbxUnpackNextTagResp(&fbMbxMsg, NULL, NULL);
        MbxUnpackNextTagResp(&fbMbxMsg, NULL, NULL);
        MbxUnpackNextTagResp(&fbMbxMsg, NULL, NULL);
        MbxUnpackNextTagResp(&fbMbxMsg, NULL, &displays[0].pitch);
        MbxUnpackNextTagResp(&fbMbxMsg, NULL, (uint32_t*)&displays[0].physSpecs);
        MbxUnpackNextTagResp(&fbMbxMsg, NULL, &displays[0].colorDepth);
    }

    return STATUS_SUCCESS;
}