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

        uint32_t width;
        uint32_t height;
        
        TUI_Symbol *symbols;
        void *colors;
        uint32_t symbols_count;

        TUI_UniSColor draw_color;
        int draw_symbol;

} TUI_Renderer;



TUI_Renderer *TUI_CreateRenderer(FILE *_Stream, uint32_t _Width, uint32_t _Height, TUI_ColorFormat _Format);



bool TUI_RendererPresent(TUI_Renderer *_Renderer);



bool TUI_RendererClear(TUI_Renderer *_Renderer);


bool TUI_ResizeRenderer(TUI_Renderer *_Renderer, uint32_t _Width, uint32_t _Height);



bool TUI_RenderSymbol(TUI_Renderer *_Renderer, uint32_t _X, uint32_t _Y, TUI_Symbol _Symbol, TUI_UniSColor _Color);




#endif // __TUI_Render_h__

