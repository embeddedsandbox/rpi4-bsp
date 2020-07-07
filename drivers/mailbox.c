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
#include "mailbox.h"


//==============================================================================
// LOCAL VARIABLES
//==============================================================================
static volatile mbxRegisters_t * mbxVC2ARM = ((volatile mbxRegisters_t *)(0x47E00B880));
static volatile mbxRegisters_t * mbxARM2VC = ((volatile mbxRegisters_t *)(0x47E00B8A0));

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void MbxInitMsgBuffer(mbxMessage_t* msg)
{
    msg->bufferSize = 8;
    msg->req        = MBX_MSG_PROCESS_REQ;

    for (int idx = 0; idx < (sizeof(msg->tagBuffer)/sizeof(msg->tagBuffer[0])); idx++)  /*TODO clean this up*/
    {
        msg->tagBuffer[idx]= 0;
    }

    msg->nextTagIndex = 0;
    msg->numTags = 0;
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
status_t MbxAddMsgTag(mbxMessage_t* msg, uint32_t tag, uint32_t values[])
{
    status_t status = STATUS_SUCCESS;

    switch(tag)
    {
        
        case    MBX_TAG_LAST:
        {
            if (msg->nextTagIndex < ((sizeof(msg->tagBuffer))/(sizeof(msg->tagBuffer[0]))))
            { 
                msg->bufferSize += 4;                
                msg->tagBuffer[msg->nextTagIndex] = tag;
            }
            break;
        }

        // zero byte value buffer
        case    MBX_FB_RELEASE_BUFF:
            break;

        // 4 byte value buffer
        case    MBX_VC_GET_FW_VER:
        case    MBX_VC_GET_HW_MDL:
        case    MBX_VC_GET_BRD_VER:
        case    MBX_SR_GET_DMA_CHNS:
        case    MBX_FB_BLANK_SCRN:     
        case    MBX_FB_GET_COLOR_DEPTH:
        case    MBX_FB_SET_COLOR_DEPTH:
        case    MBX_FB_GET_PIXEL_ORDER:
        case    MBX_FB_TEST_PIXEL_ORDER:
        case    MBX_FB_SET_PIXEL_ORDER:
        case    MBX_FB_GET_ALPHA_MODE:
        case    MBX_FB_TEST_ALPHA_MODE:
        case    MBX_FB_SET_ALPHA_MODE:
        case    MBX_FB_GET_PITCH:
        {
            if (((sizeof(msg->tagBuffer)/4)- msg->nextTagIndex) > sizeof(mbx4ByteRespReq_t))
            {
                msg->bufferSize             += sizeof(mbx4ByteRespReq_t);
                mbx4ByteRespReq_t* tag4Req  = (mbx4ByteRespReq_t*)&msg->tagBuffer[msg->nextTagIndex];
                tag4Req->header.tag         = tag;
                tag4Req->header.valSize     = 4;
                tag4Req->header.req         = 0;
                if(values != NULL)
                {
                    tag4Req->value              = values[0];
                }
                msg->nextTagIndex           += sizeof(mbx4ByteRespReq_t)/4;
                msg->numTags++;
            }
            break;
        }

        // 8 byte value buffer
        case    MBX_VC_GET_BRD_MAC:
        case    MBX_VC_GET_BRD_SN:
        case    MBX_VC_GET_ARM_MEM:
        case    MBX_VC_GET_VC_MEM:
        case    MBX_PWR_GET_PWR_ST:
        case    MBX_PWR_GET_TIMING:
        case    MBX_PWR_SET_PWR_ST:
        case    MBX_FB_ALLOC_BUFF:
        case    MBX_FB_GET_DISP_SPECS:
        case    MBX_FB_TEST_DISP_SPECS:
        case    MBX_FB_SET_DISP_SPECS:
        case    MBX_FB_GET_VIRT_DISP_SPECS:
        case    MBX_FB_SET_VIRT_DISP_SPECS:
        case    MBX_FB_GET_VIRT_OFFSET:
        case    MBX_FB_TEST_VIRT_OFFSET:
        case    MBX_FB_SET_VIRT_OFFSET:
        {
            if (((sizeof(msg->tagBuffer)/4)- msg->nextTagIndex) > sizeof(mbx8ByteRespReq_t))
            {
                msg->bufferSize += sizeof(mbx8ByteRespReq_t);
                mbx8ByteRespReq_t* tag8Req = (mbx8ByteRespReq_t*)&msg->tagBuffer[msg->nextTagIndex];
                tag8Req->header.tag         = tag;
                tag8Req->header.valSize     = 8;
                tag8Req->header.req         = 0;
                if (values != NULL)
                {
                    tag8Req->value[0]           = values[0];
                    tag8Req->value[1]           = values[1];
                }
                msg->nextTagIndex           += sizeof(mbx8ByteRespReq_t)/4;
                msg->numTags++;
            }
            break;
        }
        
/*
        // 12 byte value buffer
        case

        // 16 byte value buffer
        case
            MBX_FB_GET_OVERSCAN         = 0x0004000A,
            MBX_FB_TEST_OVERSCAN        = 0x0004400A,
            MBX_FB_SET_OVERSCAN         = 0x0004800A,
            MBX_FB_SET_CURSPR_STATE     = 0x00008011,   

        // 24 byte value buffer
        case 
            MBX_FB_SET_CURSOR_INFO      = 0x00008010,

        //Variable sized value buffer
        case:
                MBX_VC_GET_CLKS:
                MBX_CFG_GET_CMD_LINE:
                MBX_FB_GET_PALETTE          = 0x0004000B,   // Currently there is a limit to the number of entries that can be modified or retured 
                MBX_FB_TEST_PALETTE         = 0x0004400B,
                MBX_FB_SET_PALETTE          = 0x0004800B,   // Currently there is a limit to the number of entries that can be modified or retured 
*/
    }

    return status;
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
status_t MbxSendMsg(mbxMessage_t* msg)
{
    status_t    status;
    uint32_t    msgAddr = ((uint64_t)(msg) & (0xFFFFFFFF));
    uint32_t    resp;

    do
    {
        resp = mbxARM2VC->status;
    }
    while ((resp & MBX_STATUS_FULL) != 0);
    
    mbxARM2VC->data     =   (msgAddr | MBX_CHAN_PROPERTIES);

    // TODO this is a hack. Poll for the response.  This is only until we get 
    //  interrupts sorted out and
    //  events working

    do
    {
        resp = mbxVC2ARM->data;
    } while (resp != (msgAddr | MBX_CHAN_PROPERTIES));
    msg->nextTagIndex = 0;

    if (msg->resp == 0x80000000)
    {
        status = STATUS_SUCCESS;
    }
    else
    {
        status = STATUS_HW_NOT_PRESENT;
    }
    


    return status;
}

//-----------------------------------------------------------------------------
// Note this return value should be changed to a "Status" code and should not
//  be a bool
//-----------------------------------------------------------------------------
status_t MbxUnpackNextTagResp(mbxMessage_t* msg, uint32_t *resp, uint32_t *respData)
{
    status_t    status = STATUS_SUCCESS;
    
    if (msg->numTags > 0)
    {
        msg->numTags--;

        mbxTagCommonHeader_t* tagRespHeader = ((mbxTagCommonHeader_t*) &msg->tagBuffer[msg->nextTagIndex]);
        
        switch (tagRespHeader->tag)
        {        
            case    MBX_TAG_LAST:
            {
                break;
            }

            // zero byte value buffer
            case    MBX_FB_RELEASE_BUFF:
                break;

            // 4 byte value buffer
            case    MBX_VC_GET_FW_VER:
            case    MBX_VC_GET_HW_MDL:
            case    MBX_VC_GET_BRD_VER:
            case    MBX_SR_GET_DMA_CHNS:
            case    MBX_FB_BLANK_SCRN:     
            case    MBX_FB_GET_COLOR_DEPTH:
            case    MBX_FB_SET_COLOR_DEPTH:
            case    MBX_FB_GET_PIXEL_ORDER:
            case    MBX_FB_TEST_PIXEL_ORDER:
            case    MBX_FB_SET_PIXEL_ORDER:
            case    MBX_FB_GET_ALPHA_MODE:
            case    MBX_FB_TEST_ALPHA_MODE:
            case    MBX_FB_SET_ALPHA_MODE:
            case    MBX_FB_GET_PITCH:
            {
                mbx4ByteRespReq_t * tagResp = (mbx4ByteRespReq_t *)tagRespHeader;

                if (resp != NULL)
                {
                    *resp = tagResp->header.resp;                
                }

                if (respData != NULL)
                {
                    respData[0] = tagResp->value;
                    msg->nextTagIndex += sizeof(mbx4ByteRespReq_t)/4;
                }

                break;
            }

            // 8 byte value buffer
            case    MBX_VC_GET_BRD_MAC:
            case    MBX_VC_GET_BRD_SN:
            case    MBX_VC_GET_ARM_MEM:
            case    MBX_VC_GET_VC_MEM:
            case    MBX_PWR_GET_PWR_ST:
            case    MBX_PWR_GET_TIMING:
            case    MBX_PWR_SET_PWR_ST:
            case    MBX_FB_ALLOC_BUFF:
            case    MBX_FB_GET_DISP_SPECS:
            case    MBX_FB_TEST_DISP_SPECS:
            case    MBX_FB_SET_DISP_SPECS:
            case    MBX_FB_GET_VIRT_DISP_SPECS:
            case    MBX_FB_SET_VIRT_DISP_SPECS:
            case    MBX_FB_GET_VIRT_OFFSET:
            case    MBX_FB_TEST_VIRT_OFFSET:
            case    MBX_FB_SET_VIRT_OFFSET:
            {
                mbx8ByteRespReq_t * tagResp = (mbx8ByteRespReq_t *)tagRespHeader;

                if (resp != NULL)
                {
                    *resp = tagResp->header.resp;
                }

                if (respData != NULL)
                {
                    respData[0] = tagResp->value[0];
                    respData[1] = tagResp->value[1];
                    msg->nextTagIndex += sizeof(mbx8ByteRespReq_t)/4;
                }

                break;
            }
            
    /*
            // 12 byte value buffer
            case

            // 16 byte value buffer
            case
                MBX_FB_GET_OVERSCAN         = 0x0004000A,
                MBX_FB_TEST_OVERSCAN        = 0x0004400A,
                MBX_FB_SET_OVERSCAN         = 0x0004800A,
                MBX_FB_SET_CURSPR_STATE     = 0x00008011,   

            // 24 byte value buffer
            case 
                MBX_FB_SET_CURSOR_INFO      = 0x00008010,

            //Variable sized value buffer
            case:
                    MBX_VC_GET_CLKS:
                    MBX_CFG_GET_CMD_LINE:
                    MBX_FB_GET_PALETTE          = 0x0004000B,   // Currently there is a limit to the number of entries that can be modified or retured 
                    MBX_FB_TEST_PALETTE         = 0x0004400B,
                    MBX_FB_SET_PALETTE          = 0x0004800B,   // Currently there is a limit to the number of entries that can be modified or retured 
    */
        }
    }

    return status;
}
