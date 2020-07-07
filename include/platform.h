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
#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#define INT_NUM_ARM_MAILBOX_0       (32)
#define INT_NUM_ARM_MAILBOX_1       (33)
#define INT_NUM_ARM_MAILBOX_2       (34)
#define INT_NUM_ARM_MAILBOX_3       (35)
#define INT_NUM_ARM_MAILBOX_4       (36)
#define INT_NUM_ARM_MAILBOX_5       (37)
#define INT_NUM_ARM_MAILBOX_6       (38)
#define INT_NUM_ARM_MAILBOX_7       (39)
#define INT_NUM_ARM_MAILBOX_8       (40)
#define INT_NUM_ARM_MAILBOX_9       (41)
#define INT_NUM_ARM_MAILBOX_10      (42)
#define INT_NUM_ARM_MAILBOX_11      (43)
#define INT_NUM_ARM_MAILBOX_12      (44)
#define INT_NUM_ARM_MAILBOX_13      (45)
#define INT_NUM_ARM_MAILBOX_14      (46)
#define INT_NUM_ARM_MAILBOX_15      (47)
#define INT_NUM_CORE_0_PMU          (48)
#define INT_NUM_CORE_1_PMU          (49)
#define INT_NUM_CORE_2_PMU          (50)
#define INT_NUM_CORE_3_PMU          (51)
#define INT_NUM_AIXERR              (52)
#define INT_NUM_LOCAL_TIMER         (53)

//-----------------------------------------------------------------------------
// ARMC Interrupts
//-----------------------------------------------------------------------------
#define INT_NUM_ARMC_TIMER          (64 + 0)
#define INT_NUM_ARMC_MAILBOX        (64 + 1)
#define INT_NUM_ARMC_DOORBELL_0     (64 + 2)
#define INT_NUM_ARMC_DOORBELL_1     (64 + 3)
#define INT_NUM_ARMC_VPU0_HALTED    (64 + 4)
#define INT_NUM_ARMC_VPU1_HALTED    (64 + 5)
#define INT_NUM_ARMC_ARM_ADDR_ERR   (64 + 6)
#define INT_NUM_ARMC_ARM_AXI_ERR    (64 + 7)
#define INT_NUM_ARMC_SW_INT_0       (64 + 8)
#define INT_NUM_ARMC_SW_INT_1       (64 + 9)
#define INT_NUM_ARMC_SW_INT_2       (64 + 10)
#define INT_NUM_ARMC_SW_INT_3       (64 + 11)
#define INT_NUM_ARMC_SW_INT_4       (64 + 12)
#define INT_NUM_ARMC_SW_INT_5       (64 + 13)
#define INT_NUM_ARMC_SW_INT_6       (64 + 14)
#define INT_NUM_ARMC_SW_INT_7       (64 + 15)


//-----------------------------------------------------------------------------
// Interrupts generated via the Video Congroller
//-----------------------------------------------------------------------------
#define INT_NUM_VC_TIMER_0          (96 + 0)
#define INT_NUM_VC_TIMER_1          (96 + 1)
#define INT_NUM_VC_TIMER_2          (96 + 2)
#define INT_NUM_VC_TIMER_3          (96 + 3)
#define INT_NUM_VC_H264_0           (96 + 4)
#define INT_NUM_VC_H264_1           (96 + 5)
#define INT_NUM_VC_H264_2           (96 + 6)
#define INT_NUM_JPEG                (96 + 7)
#define INT_NUM_ISP                 (96 + 8)
#define INT_NUM_USB                 (96 + 9)
#define INT_NUM_V3D                 (96 + 10)
#define INT_NUM_TRANSPOSER          (96 + 11)
#define INT_NUM_MULTI_CORE_SYNC_0   (96 + 12)
#define INT_NUM_MULTI_CORE_SYNC_1   (96 + 13)
#define INT_NUM_MULTI_CORE_SYNC_2   (96 + 14)
#define INT_NUM_MULTI_CORE_SYNC_3   (96 + 15)
#define INT_NUM_DMA_0               (96 + 16)
#define INT_NUM_DMA_1               (96 + 17)
#define INT_NUM_DMA_2               (96 + 18)
#define INT_NUM_DMA_3               (96 + 19)
#define INT_NUM_DMA_4               (96 + 20)
#define INT_NUM_DMA_5               (96 + 21)
#define INT_NUM_DMA_6               (96 + 22)
#define INT_NUM_DMA_7_8             (96 + 23)
#define INT_NUM_DMA_9_10            (96 + 24)
#define INT_NUM_DMA_11              (96 + 25)
#define INT_NUM_DMA_12              (96 + 26)
#define INT_NUM_DMA_13              (96 + 27)
#define INT_NUM_DMA_14              (96 + 28)
#define INT_NUM_AUX                 (96 + 29)
#define INT_NUM_ARM                 (96 + 30)
#define INT_NUM_DMA_15              (96 + 31)
#define INT_NUM_HDMI_ECE            (96 + 32)
#define INT_NUM_HVS                 (96 + 33)
#define INT_NUM_RPIVID              (96 + 34)
#define INT_NUM_SDC                 (96 + 35)
#define INT_NUM_DSI_0               (96 + 36)
#define INT_NUM_PIXEL_VALVE_2       (96 + 37)
#define INT_NUM_CAMERA_0            (96 + 38)
#define INT_NUM_CAMERA_1            (96 + 39)
#define INT_NUM_HDMI_0              (96 + 40)
#define INT_NUM_HDMO_1              (96 + 41)
#define INT_NUM_PIXEL_VALVE_3       (96 + 42)
#define INT_NUM_SPI_BSC_SLAVE       (96 + 43)
#define INT_NUM_DSI_1               (96 + 44)
#define INT_NUM_PIXEL_VALVE_0       (96 + 45)
#define INT_NUM_PIXEL_VALVE_1_4     (96 + 46)
#define INT_NUM_CPR                 (96 + 47)
#define INT_NUM_SMI                 (96 + 48)
#define INT_NUM_GPIO_0              (96 + 49)
#define INT_NUM_GPIO_1              (96 + 50)
#define INT_NUM_GPIO_2              (96 + 51)
#define INT_NUM_GPIO_3              (96 + 52)
#define INT_NUM_I2C_ALL             (96 + 53)
#define INT_NUM_SPI_ALL             (96 + 54)
#define INT_NUM_PCM_I2S             (96 + 55)
#define INT_NUM_SD_HOST             (96 + 56)
#define INT_NUM_PL011_ALL           (96 + 57)
#define INT_NUM_ETH_PCIE_ALL        (96 + 58)
#define INT_NUM_VEC                 (96 + 59)
#define INT_NUM_CPG                 (96 + 60)
#define INT_NUM_RNG                 (96 + 61)
#define INT_NUM_EMMC_EMMC2          (96 + 62)
#define INT_NUM_ETH_PCIE_SECURE     (96 + 63) 

#define INT_NUM_AVS                 (160 + 9)
#define INT_NUM_PCIE_0_INTA         (160 + 15)
#define INT_NUM_PCIE_0_INTB         (160 + 16)
#define INT_NUM_PCIE_0_INTC         (160 + 17)
#define INT_NUM_PCIE_0_INTD         (160 + 18)
#define INT_NUM_PCIE_0_MSI          (160 + 20)
#define INT_NUM_GENET_0_A           (160 + 29)
#define INT_NUM_GENET_0_B           (160 + 30)
#define INT_NUM_USB0_XHCI_0         (160 + 48)


extern uint32_t     gVideoMemory[2];  // [0] start [1] size  note this is below the 1Gb boundary 
extern uint64_t     gvideoMemoryEnd;
extern uint32_t     gLowMemory[2];
extern uint64_t     gTopOfMemory;
extern uint64_t     gBoardSerialNumber;
extern uint64_t     gMacAddress;
extern uint32_t     gFwVersion;
extern uint32_t     gHwModel;
extern uint32_t     gBoardVersion;

#endif 