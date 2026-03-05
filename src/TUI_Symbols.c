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