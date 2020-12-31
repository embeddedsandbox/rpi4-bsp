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
#ifndef __FRAME_BUFFER_H__
#define __FRAME_BUFFER_H__

//-----------------------------------------------------------------------------
// The order of these structures is intended to match the order of the 
//  that the VC/GPU expects this information 
//-----------------------------------------------------------------------------
typedef struct 
{
    uint32_t    baseAddress;
    uint32_t    size;
} fbMemory_t;

typedef struct 
{
    uint32_t    width;
    uint32_t    height;    
}fbDisplaySpecs_t;

typedef struct 
{
    uint32_t    x;
    uint32_t    y;
} fbScreenLocation_t;

//-----------------------------------------------------------------------------
//  All the data required for a specific Display
//-----------------------------------------------------------------------------
typedef struct 
{
    fbMemory_t          theFrameBuffer;  // idx 0=framebuffer base address, idx 1= framebuffer size
    fbDisplaySpecs_t    physSpecs;    
    fbDisplaySpecs_t    virtSpecs;    
    uint32_t            colorDepth;
    uint32_t            pitch;
    uint32_t            line;
    uint32_t            lineHeight;
    uint32_t            numLines;
    fbScreenLocation_t  cursorLocation;
} fbDisplayBuffer_t;

status_t frameBufferInit(void* a, uint32_t b);


#endif