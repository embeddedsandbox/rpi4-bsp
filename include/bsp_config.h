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
#ifndef __BSP_CONFIG_H__
#define __BSP_CONFIG_H__


// NOTE: NOT ALL OF THESE DEVICES CAN BE USED AT THE SAME TIME
// SOME OF THESE DEVICES SHARE THE SAME PINS
enum
{
    DEV_ID_BSP_FIRST_DEV        = 10,
    DEV_ID_FRAMEBUFFER_0_CHAR   = DEV_ID_BSP_FIRST_DEV,
    DEV_ID_FRAMEBUFFER_1_CHAR,
    DEV_ID_HDMI_0,
    DEV_ID_HDMI_1,
    DEV_ID_EMMC,
    DEV_ID_GPIO,
    DEV_ID_DMA,
    DEV_ID_PCM,     / AUDIO
    DEV_ID_PWM,     / PWM
    DEV_ID_TIMER,

    DEV_ID_I2C_0,
    DEV_ID_I2C_1,

#ifdef PC_ENABLE_EXTRA_I2C
    DEV_ID_I2C_2,
    DEV_ID_I2C_3,
    DEV_ID_I2C_4,
    DEV_ID_I2C_5,
 #endif

    DEV_ID_UART_0,

 #ifdef PC_ENABLE_EXTRA_UART
    DEV_ID_UART_1,
    DEV_ID_UART_2,
    DEV_ID_UART_3, 
    DEV_ID_UART_4, 
    DEV_ID_UART_5,
#endif 

    DEV_ID_SPI_0,

#ifdef PC_ENABLE_EXTRA_SPI
    DEV_ID_SPI_1,
    DEV_ID_SPI_2,
    DEV_ID_SPI_3,
    DEV_ID_SPI_4,
#endif 
    
    DEV_ID_USB_ROOT_HUB0,
    DEV_ID_ETH0,
    DEV_ID_LAST_DEV             = DEV_ID_ETH0,
    NUM_BSP_DEVICES             = DEV_ID_LAST_DEV - DEV_ID_BSP_FIRST_DEV,
} bsp_devices_t


#endif


