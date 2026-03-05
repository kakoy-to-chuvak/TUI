#include "TUI_Render.h"

#define __MIN(a, b) ( a > b ? b : a )


TUI_Renderer *TUI_CreateRenderer(FILE *_Stream, int _Width, int _Height, TUI_ColorFormat _Format) {
        if ( _Stream == NULL || _Format == ColorFormat_Undefined ) {
                return NULL;
        }

        TUI_Renderer *renderer = malloc(sizeof(TUI_Renderer));
        if ( renderer == NULL ) {
                TUI_SetError(TUI_ErrType_AllocationError, "couldn`t allocate memory");
                return NULL;
        }
        
        int symbols_count = _Width * _Height;

        renderer->symbols = malloc( symbols_count * sizeof(TUI_Symbol) );
        if ( renderer->symbols == NULL ) {
                TUI_SetError(TUI_ErrType_AllocationError, "couldn`t allocate memory");
                
                free(renderer);
                return NULL;
        }

        renderer->colors = malloc(symbols_count * renderer->color_size);
        if ( renderer->colors == NULL ) {
                TUI_SetError(TUI_ErrType_AllocationError, "couldn`t allocate memory");
                
                free(renderer->symbols);
                free(renderer);
                return NULL;
        }

        renderer->stream = _Stream;
        renderer->color_format = _Format;
        renderer->width = _Width;
        renderer->height = _Height;
        renderer->draw_symbol = 0;
        renderer->color_size = TUI_GetSColorSize(_Format);
        
        renderer->draw_color.bg.cfRGB = (TUI_ColorRGB){
                0, 0, 0
        };

        renderer->draw_color.fg.cfRGB = (TUI_ColorRGB){
                0, 0, 0
        };

        return renderer;
}



bool TUI_ResizeRenderer(TUI_Renderer *_Renderer, int _Width, int _Height) {
        if ( _Renderer == NULL ) {
                return 0;
        }

        int new_count = _Width * _Height;

        TUI_Symbol *new_symbols = malloc( new_count * sizeof(TUI_Symbol) );
        if ( new_symbols == NULL ) {
                TUI_SetError(TUI_ErrType_AllocationError, "couldn`t allocate memory");
                return 0;  
        }

        TUI_Symbol *new_colors = malloc( new_count * _Renderer->color_size );
        if ( new_symbols == NULL ) {
                TUI_SetError(TUI_ErrType_AllocationError, "couldn`t allocate memory");

                free(new_symbols);
                return 0;  
        }


        void *now_dst = new_symbols;
        void *now_src = _Renderer->symbols;

        int copy_size = __MIN(_Renderer->width, _Width);
        int rows = __MIN(_Renderer->height, _Height);

        while ( rows ) {
                memcpy( now_dst, now_src, copy_size * sizeof(TUI_Symbol) );

                (TUI_Symbol*)now_dst += _Width;
                (TUI_Symbol*)now_src += _Renderer->width;
                rows--;
        }

        now_dst = new_colors;
        now_src = _Renderer->colors;

        rows = __MIN(_Renderer->height, _Height);
        int color_size = _Renderer->color_size;

        while ( rows ) {
                memcpy( now_dst, now_src, copy_size * color_size );

                (char*)now_dst += _Width * color_size;
                (char*)now_src += _Renderer->width * color_size;
                rows--;
        }

        return 1;
}



bool TUI_RenderSymbol(TUI_Renderer *_Renderer, int _X, int _Y, int _Symbol, TUI_UniColor _Color);