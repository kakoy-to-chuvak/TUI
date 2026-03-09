#include "TUI_Symbols.h"

#define __MAX3(a, b, c) ( (a) > (b) ? (a) > (c) ? (a) : (c) : (b) > (c) ? (b) : (c) )


TUI_ColorRGB __STD_COLORS16[16] = {
    { 0,   0,   0   },  //  0 black
    { 128, 0,   0   },  //  1 red
    { 0,   128, 0   },  //  2 green
    { 128, 128, 0   },  //  3 yellow
    { 0,   0,   128 },  //  4 blue
    { 128, 0,   128 },  //  5 magenta
    { 0,   128, 128 },  //  6 cyan
    { 192, 192, 192 },  //  7 white (light grey)
    { 128, 128, 128 },  //  8 grey
    { 255, 0,   0   },  //  9 bright red
    { 255, 255, 0   },  // 10 bright green
    { 0,   255, 0   },  // 11 bright yellow
    { 0,   0,   255 },  // 12 bright blue
    { 255, 0,   255 },  // 13 bright magenta
    { 0,   255, 255 },  // 14 bright cyan
    { 255, 255, 255 },  // 15 bright white
};


int TUI_GetColorSize(TUI_ColorFormat _Format) {
        switch ( _Format ) {
                case ColorFormat_RGB:
                        return sizeof(TUI_ColorRGB);
                case ColorFormat_256:
                        return sizeof(TUI_Color256);
                case ColorFormat_16:
                        return sizeof(TUI_Color16);

                default:
                        return 0;
        }
}

int TUI_GetSColorSize(TUI_ColorFormat _Format) {
        return TUI_GetColorSize(_Format) * 2;
}



int TUI_PrintFgColor(void *_Color, TUI_ColorFormat _Format, FILE *_Stream) {
        if ( _Color == NULL ) {
                return 0;
        }

        switch ( _Format ) {
                case ColorFormat_RGB: {
                        TUI_ColorRGB color = *(TUI_ColorRGB*)_Color;
                        return fprintf(_Stream, "\x1b[38;2;%i;%i;%im", color.r, color.g, color.b);
                        break;
                }

                case ColorFormat_256: {
                        TUI_Color256 color = *(TUI_Color256*)_Color;
                        return fprintf(_Stream, "\x1b[38;5;%im", color);
                        break;
                }

                case ColorFormat_16: {
                        TUI_Color16 color = *(TUI_Color16*)_Color;
                        return fprintf(_Stream, "\x1b[%im", color);
                        break;
                }

                default:
                        return 0;
        }
}

int TUI_PrintBgColor(void *_Color, TUI_ColorFormat _Format, FILE *_Stream) {
        if ( _Color == NULL ) {
                return 0;
        }

        switch ( _Format ) {
                case ColorFormat_RGB: {
                        TUI_ColorRGB color = *(TUI_ColorRGB*)_Color;
                        return fprintf(_Stream, "\x1b[48;2;%i;%i;%im", color.r, color.g, color.b);
                        break;
                }

                case ColorFormat_256: {
                        TUI_Color256 color = *(TUI_Color256*)_Color;
                        return fprintf(_Stream, "\x1b[48;5;%im", color);
                        break;
                }

                case ColorFormat_16: {
                        TUI_Color16 color = *(TUI_Color16*)_Color;
                        return fprintf(_Stream, "\x1b[%im", (int)color + 10);
                        break;
                }

                default:
                        return 0;
        }
}



int TUI_PrintSColor(void *_Color, TUI_ColorFormat _Format, FILE *_Stream) {
        if ( _Color == NULL ) {
                return 0;
        }

        switch ( _Format ) {
                case ColorFormat_RGB: {
                        TUI_SColorRGB color = *(TUI_SColorRGB*)_Color;
                        return fprintf(_Stream, "\x1b[38;2;%i;%i;%im\x1b[48;2;%i;%i;%im", color.fg.r, color.fg.g, color.fg.b, color.bg.r, color.bg.g, color.bg.b);
                        break;
                }

                case ColorFormat_256: {
                        TUI_SColor256 color = *(TUI_SColor256*)_Color;
                        return fprintf(_Stream, "\x1b[38;5;%im\x1b[48;5;%im", color.fg, color.bg);
                        break;
                }

                case ColorFormat_16: {
                        TUI_SColor16 color = *(TUI_SColor16*)_Color;
                        return fprintf(_Stream, "\x1b[%im\x1b[%im", color.fg, (int)color.bg + 10);
                        break;
                }

                default:
                        return 0;
        }
}






TUI_Color256 TUI_TransformColor16_256(TUI_Color16 _Color) {
        if ( _Color < 40 ) {
                return _Color - 30;
        } else {
                return _Color - 82;
        }
}

TUI_ColorRGB TUI_TransformColor16_RGB(TUI_Color16 _Color) {
        return __STD_COLORS16[TUI_TransformColor16_256(_Color)];
}
        


TUI_Color16 TUI_TransformColor256_16(TUI_Color256 _Color) {
        if ( _Color < 8 ) {
                return _Color + 30;
        }

        if ( _Color < 16 ) {
                return _Color + 82;
        }

        float r;
        float g;
        float b;

        if ( _Color < 232 ) {
                _Color -= 16;
                r = ( _Color / 36 ) / 5.0;
                g = ( ( _Color % 36 ) / 6 ) / 5.0;
                b = ( _Color % 6 ) / 5.0;
        } else {
                r = ( ( ( _Color - 232) * 10) + 8 ) / 255.0;
		g = r;
		b = r;
        }

        float value = __MAX3(r, g, b) * 2;

        if ( value == 0 ) {
                return 30;
        }

        int result = 30 + ( ( (int)round(b) << 2 ) | ( (int)round(g) << 1 ) | (int)round(r) );

        if ( value == 2 ) {
                result += 60;
        }

        return result;
}

TUI_ColorRGB TUI_TransformColor256_RGB(TUI_Color256 _Color) {        
        if ( _Color < 16 ) {
                return __STD_COLORS16[_Color];
        } 
        
        if ( _Color < 232 ) {
                _Color -= 16;
                TUI_ColorRGB rgb_color = {
                        0, 0, 0
                };

                int i = _Color / 36;
                if ( i ) {
                        rgb_color.r = ( 14135 + 10280 * i ) / 256;
                }

                i = ( _Color / 6 ) % 6;
                if ( i ) {
                        rgb_color.g = ( 14135 + 10280 * i ) / 256;
                }

                i = _Color % 6;
                if ( i ) {
                        rgb_color.b = ( 14135 + 10280 * i ) / 256;
                }

                return rgb_color;
        } 
        
        TUI_ColorRGB rgb_color;
        rgb_color.r = ( 2056 + 2570 * (_Color - 232) ) / 256;
        rgb_color.g = rgb_color.r;
        rgb_color.b = rgb_color.r;
        return rgb_color;
}



TUI_Color16 TUI_TransformColorRGB_16(TUI_ColorRGB _Color) {
        return TUI_TransformColor256_16(TUI_TransformColorRGB_256(_Color));
}

TUI_Color256 TUI_TransformColorRGB_256(TUI_ColorRGB _Color) {
        if ( _Color.r == _Color.g && _Color.g == _Color.b ) {
                if ( _Color.r < 8) {
                    return 16;
                }

                if ( _Color.r > 248 ) {
                    return 231;
                }

                return round( ( _Color.r - 8 ) * 0.0971659919 ) + 232;
        }

        return 16 + _Color.r / 51 * 36 + _Color.g / 51 * 6 + _Color.b / 51;
}

