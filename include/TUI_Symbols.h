#ifndef __TUI_Symbols_h__
#define __TUI_Symbols_h__
#pragma once



#include <stdint.h>



typedef int TUI_Symbol;


typedef enum TUI_ColorFormat : int8_t {
        
        ColorFormat_Undefined = -1,

        ColorFormat_None = 0,
        
        ColorFormat_16 = 1,
        
        ColorFormat_256 = 2,

        ColorFormat_RGB = 3,

} TUI_ColorFormat;




typedef enum TUI_Color16 : int8_t {
        
        Color_BLack   = 0,
        Color_Red     = 1,
        Color_Green   = 2,
        Color_Yellow  = 3,
        Color_Blue    = 4,
        Color_Magenta = 5,
        Color_Cyan    = 6,
        Color_White   = 7,

        Color_BrightBLack   = 8,
        Color_BrightRed     = 9,
        Color_BrightGreen   = 10,
        Color_BrightYellow  = 11,
        Color_BrightBlue    = 12,
        Color_BrightMagenta = 13,
        Color_BrightCyan    = 14,
        Color_BrightWhite   = 15,
        
} TUI_Color16;




typedef struct TUI_SColor16 {
        TUI_Color16 fg: 4;
        TUI_Color16 bg: 4;
} TUI_SColor16;




typedef uint8_t TUI_Color256;




typedef struct TUI_SColor256 {
        TUI_Color256 fg;
        TUI_Color256 bg;
} TUI_SColor256;




typedef struct TUI_ColorRGB {
        uint8_t r;
        uint8_t g;
        uint8_t b;
} TUI_ColorRGB;




typedef struct TUI_SColorRGB {
        TUI_ColorRGB fg;
        TUI_ColorRGB bg;
} TUI_SColorRGB;



typedef union TUI_UniColor {
        TUI_ColorRGB cfRGB;
        TUI_Color256 cf256;
        TUI_Color16  cf16;
} TUI_UniColor;




typedef struct TUI_UniSColor {
        TUI_UniColor fg;
        TUI_UniColor bg;
} TUI_UniSColor;




int TUI_GetColorSize(TUI_ColorFormat _Format);

int TUI_GetSColorSize(TUI_ColorFormat _Format);


// TUI_Color256 TUI_TransformColor16_256(TUI_Color16 _Color);
// TUI_ColorRGB TUI_TransformColor16_RGB(TUI_Color16 _Color);


// TUI_Color16 TUI_TransformColor256_16(TUI_Color256 _Color);
// TUI_ColorRGB TUI_TransformColor256_RGB(TUI_Color256 _Color);


// TUI_Color16 TUI_TransformColorRGB_16(TUI_ColorRGB _Color);
// TUI_Color256 TUI_TransformColorRGB_256(TUI_ColorRGB _Color);


#endif // __TUI_Symbols_h__