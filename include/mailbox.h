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
#ifndef __MAILBOX_H__
#define __MAILBOX_H__

#include "types.h"

//=============================================================================
// DEFINES
//=============================================================================
#define MBX_STATUS_FULL     (0x80000001)


//=============================================================================
// TYPES
//=============================================================================
typedef struct 
{
	volatile uint32_t data;	  // 0x00         Read data from VC to ARM
	volatile uint32_t reserved1[3];       // 0x04-0x0F
	volatile uint32_t peek0;	       // 0x10
	volatile uint32_t sender;      // 0x14
  	volatile uint32_t status;	// 0x18         Status of VC to ARM
	volatile uint32_t config;	// 0x1C        
} mbxRegisters_t;

typedef enum
{
    MBX_CHAN_POWER              = 0,
    MBX_CHAN_FRAMEBUFFER        = 1,
    MBX_CHAN_VIRT_UART          = 2,
    MBX_CHAN_VCHIQ              = 3,
    MBX_CHAN_LEDS               = 4,
    MBX_CHAN_BTNS               = 5,
    MBX_CHAN_TOUCH              = 6,
    MBX_CHAN_COUNT              = 7,
    MBX_CHAN_PROPERTIES         = 8,
} mbxChannel_t;

typedef enum
{
    MBX_TAG_LAST                = 0x00000000,
    MBX_VC_GET_FW_VER           = 0x00000001,
    MBX_VC_GET_HW_MDL           = 0x00010001,
    MBX_VC_GET_BRD_VER          = 0x00010002,
    MBX_VC_GET_BRD_MAC          = 0x00010003,
    MBX_VC_GET_BRD_SN           = 0x00010004,
    MBX_VC_GET_ARM_MEM          = 0x00010005,
    MBX_VC_GET_VC_MEM           = 0x00010006,
    MBX_VC_GET_CLKS             = 0x00010007,   // Note this requires a LargeRequest (so only 1 per message buffer to send.

    MBX_CFG_GET_CMD_LINE        = 0x00050001, // Note this requires a LargeRequest (so only 1 per message buffer to send.

    //SHARED RECOURCES
    MBX_SR_GET_DMA_CHNS         = 0x00060001,
    
    // POWER
    MBX_PWR_GET_PWR_ST          = 0x00020001,
    MBX_PWR_GET_TIMING          = 0x00020002,
    MBX_PWR_SET_PWR_ST          = 0x00028001,

    // Clocks

    // Voltage

    // VC Memory

    // Frame Buffer
    MBX_FB_ALLOC_BUFF           = 0x00040001,
    MBX_FB_RELEASE_BUFF         = 0x00048001,
    MBX_FB_BLANK_SCRN           = 0x00040002,
    MBX_FB_GET_DISP_SPECS       = 0x00040003,
    MBX_FB_TEST_DISP_SPECS      = 0x00044003,
    MBX_FB_SET_DISP_SPECS       = 0x00048003,
    MBX_FB_GET_VIRT_DISP_SPECS  = 0x00040004,
    MBX_FB_SET_VIRT_DISP_SPECS  = 0x00048004,
    MBX_FB_GET_COLOR_DEPTH      = 0x00040005,
    MBX_FB_SET_COLOR_DEPTH      = 0x00048005,
    MBX_FB_GET_PIXEL_ORDER      = 0x00040006,
    MBX_FB_TEST_PIXEL_ORDER     = 0x00044006,
    MBX_FB_SET_PIXEL_ORDER      = 0x00048006,
    MBX_FB_GET_ALPHA_MODE       = 0x00040007,
    MBX_FB_TEST_ALPHA_MODE      = 0x00044007,
    MBX_FB_SET_ALPHA_MODE       = 0x00048007,
    MBX_FB_GET_PITCH            = 0x00040008,
    MBX_FB_GET_VIRT_OFFSET      = 0x00040009,
    MBX_FB_TEST_VIRT_OFFSET     = 0x00044009,
    MBX_FB_SET_VIRT_OFFSET      = 0x00048009,
    MBX_FB_GET_OVERSCAN         = 0x0004000A,
    MBX_FB_TEST_OVERSCAN        = 0x0004400A,
    MBX_FB_SET_OVERSCAN         = 0x0004800A,
    MBX_FB_GET_PALETTE          = 0x0004000B,   // Currently there is a limit to the number of entries that can be modified or retured 
    MBX_FB_TEST_PALETTE         = 0x0004400B,
    MBX_FB_SET_PALETTE          = 0x0004800B,   // Currently there is a limit to the number of entries that can be modified or retured 
    MBX_FB_SET_CURSOR_INFO      = 0x00008010,
    MBX_FB_SET_CURSPR_STATE     = 0x00008011,

} MbxReqPropertyTags_t;

typedef enum
{
    MBX_DEV_SD                  = 0x00000000,
    MBX_DEV_UART0               = 0x00000001,
    MBX_DEV_UART1               = 0x00000002,
    MBX_DEV_USB_HDC             = 0x00000003,
    MBX_DEV_12C0                = 0x00000004,    
    MBX_DEV_I2C1                = 0x00000005,
    MBX_DEV_12C2                = 0x00000006,
    MBX_DEV_SPI                 = 0x00000007,
    MBX_DEV_CCP2TX              = 0x00000008,
    MBX_DEV_UNKNOWN0            = 0x00000009,
    MBX_DEV_UNKNOWN1            = 0x00000010,
} MbxDevId_t;

typedef enum
{
    // There are a few of these that I don't think this can be used on Pi4
    MBX_CLK_EMMC                = 0x00000001,
    MBX_CLK_UART                = 0x00000002,
    MBX_CLK_ARM                 = 0x00000003,
    MBX_CLK_CORE                = 0x00000004,
    MBX_CLK_V3D                 = 0x00000005,
    MBX_CLK_H254                = 0x00000006, 
    MBX_CLK_ISP                 = 0x00000007,
    MBX_CLK_SDRAM               = 0x00000008,
    MBX_CLK_PIXEL               = 0x00000009,
    MBX_CLK_PWM                 = 0x0000000A,
    MBX_CLK_HEVC                = 0x0000000B,
    MBX_CLK_EMMC2               = 0x0000000C,
    MBX_CLK_M2MC                = 0x0000000D,
    MBX_CLK_PIXEL_BVD           = 0x0000000E,
} MbxClkId_t;


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
typedef struct 
{
    uint32_t    tag;
    uint32_t    valSize;
    union   
    {
        uint32_t    req;
        uint32_t    resp;
    };    
} mbxTagCommonHeader_t;


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
typedef struct 
{
    mbxTagCommonHeader_t    header;
    uint32_t                value;
} mbx4ByteRespReq_t;

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
typedef struct 
{
    mbxTagCommonHeader_t    header;
    uint32_t                value[2];
} mbx8ByteRespReq_t;

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
typedef struct 
{
    mbxTagCommonHeader_t    header;
    uint32_t                value[4];
} mbx16ByteRespReq_t;

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
typedef struct 
{
    mbxTagCommonHeader_t    header;
    uint32_t                value[32];
} mbxLargeReq_t;

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
typedef struct 
{
    uint32_t    bufferSize;
    union 
    {
        uint32_t    req;
        uint32_t    resp;
    };
    uint32_t    tagBuffer[64];
    uint32_t    nextTagIndex;
    uint32_t    numTags;
} mbxMessage_t __attribute__((aligned (16)));


#define MBX_MSG_PROCESS_REQ     (0x00000000)

//=============================================================================
// FUNC PROTOTYPES
//=============================================================================

void MbxInitMsgBuffer(mbxMessage_t* msg);
status_t MbxAddMsgTag(mbxMessage_t* msg, uint32_t tag, uint32_t values[]);
status_t MbxSendMsg(mbxMessage_t* msg);
status_t MbxUnpackNextTagResp(mbxMessage_t* msg, uint32_t *resp, uint32_t respData[]);

#endif
