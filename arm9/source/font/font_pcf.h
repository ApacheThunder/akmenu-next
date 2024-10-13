/*
    font_pcf.h
    Copyright (C) 2008-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    SPDX-License-Identifier: GPL-3.0-or-later
*/

/*
  very base pcf font implementation
  supported only fonts with ...
*/

#pragma once

#include "font.h"

//#define SMALL 1

class cFontPcf : public cFont {
  private:
#ifdef SMALL
    struct PACKED SGlyph {
        unsigned iOffset : 19;
        unsigned iWidth : 5;
        signed iLeft : 6;
        signed iRight : 6;
        signed iAscent : 6;
        signed iDescent : 6;
        unsigned iCode : 16;
    };
#else
    struct SGlyph {
        u32 iOffset;
        u16 iCode;
        u8 iWidth;
        u8 iReserved;
        s8 iLeft;
        s8 iRight;
        s8 iAscent;
        s8 iDescent;
    };
#endif
  private:
    SGlyph* iGlyphs;
    u8* iData;
    u32 iCount;
    u32 iDataSize;
    u32 iHeight;
    u32 iAscent;
    u32 iDescent;

  private:
    bool ParseAccels(int aFont, u32 aSize, u32 aOffset);
    bool ParseBitmaps(int aFont, u32 aSize, u32 aOffset);
    bool ParseMetrics(int aFont, u32 aSize, u32 aOffset);
    bool ParseEncodings(int aFont, u32 aSize, u32 aOffset);
    s32 SearchInternal(u16 aCode);
    s32 Search(u16 aCode);
    static u32 utf8toucs2(const u8* aSource, u32* aLength);
    void DrawInternal(u16* mem, s16 x, s16 y, const u8* data, u16 color, u32 width, u32 height);
    static int Compare(const void* a, const void* b);

  public:
    cFontPcf();
    ~cFontPcf();
    bool Load(const char* aFileName);
    void Draw(u16* mem, s16 x, s16 y, const u8* aText, u16 color);
    void Info(const char* aString, u32* aWidth, u32* aSymbolCount);
    u32 FontRAM(void);
};
