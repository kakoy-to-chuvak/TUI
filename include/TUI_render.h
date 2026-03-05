#ifndef __TUI_Render_h__
#define __TUI_Render_h__
#pragma once



#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>



#include "TUI_Symbols.h"
#include "TUI_Error.h"



typedef struct TUI_Renderer {
        
        FILE *stream;
        TUI_ColorFormat color_format;
        int color_size; // size of color of one symbol

        int width;
        int height;
        
        TUI_Symbol *symbols;
        void *colors;

        TUI_UniSColor draw_color;
        int draw_symbol;

} TUI_Renderer;



TUI_Renderer *TUI_CreateRenderer(int _Width, int _Height, TUI_ColorFormat _Format);



bool TUI_ResizeRenderer(TUI_Renderer *_Renderer, int _Width, int _Height);



bool TUI_RenderSymbol(TUI_Renderer *_Renderer, TUI_Symbol _Symbol, TUI_UniColor _Color);




#endif // __TUI_Render_h__

