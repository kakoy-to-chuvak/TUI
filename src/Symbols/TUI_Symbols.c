#include "TUI_Symbols.h"



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
                        return fprintf(_Stream, "\x1b[%im\x1b[%im", color.fg, color.bg + 10);
                        break;
                }

                default:
                        return 0;
        }
}
