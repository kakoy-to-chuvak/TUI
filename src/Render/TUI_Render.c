#include "TUI_Render.h"
#include "TUI_Symbols.h"

#define __MIN(a, b) ( a > b ? b : a )
#define __RGB_BLACK ((TUI_ColorRGB){0, 0, 0})
#define __RGB_S_BLACK ((TUI_SColorRGB){__RGB_BLACK, __RGB_BLACK})


void __memset32(void *_Buffer, int32_t _Value, size_t _Count) {
    uint32_t *buf = _Buffer;

    while(_Count--) *buf++ = _Value;
}

void __memsetXX(void *_Buffer, void *_Value, size_t _Value_size, size_t _Count) {
    char *buf = _Buffer;

    while(_Count--)
    {
        memcpy(buf, _Value, _Value_size);
        buf += _Value_size;
    }
}




TUI_Renderer *TUI_CreateRenderer(FILE *_Stream, uint32_t _Width, uint32_t _Height, TUI_ColorFormat _Format) {
        if ( _Stream == NULL || _Format == ColorFormat_Undefined ) {
                return NULL;
        }

        TUI_Renderer *renderer = malloc(sizeof(TUI_Renderer));
        if ( renderer == NULL ) {
                TUI_SetError(TUI_ErrType_AllocationError, "couldn`t allocate memory");
                return NULL;
        }
        
        uint32_t symbols_count = _Width * _Height;

        renderer->symbols = malloc( symbols_count * sizeof(TUI_Symbol) );
        if ( renderer->symbols == NULL ) {
                TUI_SetError(TUI_ErrType_AllocationError, "couldn`t allocate memory");
                
                free(renderer);
                return NULL;
        }

        renderer->color_size = TUI_GetSColorSize(_Format);

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
        renderer->symbols_count = symbols_count;
        renderer->draw_symbol = 0;
        
        renderer->draw_color.cfRGB = __RGB_S_BLACK;

        return renderer;
}




bool TUI_RendererPresent(TUI_Renderer *_Renderer) {
        if ( _Renderer == NULL || _Renderer->symbols == NULL || _Renderer->colors == NULL ) {
                return 0;
        }

        uint32_t count = _Renderer->symbols_count; 
        TUI_Symbol *now_symbol = _Renderer->symbols;
        void *now_color = _Renderer->colors;
        int color_size = _Renderer->color_size;

        uint32_t now_width = _Renderer->width;

        fputs("\x1b[2J\x1b[H", _Renderer->stream);

        while ( count ) {
                TUI_PrintSColor(now_color, _Renderer->color_format, _Renderer->stream);
                fputc(*now_symbol, _Renderer->stream);

                now_width--;
                if ( now_width == 0 ) {
                        now_width = _Renderer->width;
                        fputc('\n', _Renderer->stream);

                }

                now_symbol++;
                now_color = (char*)now_color + color_size;
                count--;
        }
        // доделать

        return 1;
}



bool TUI_RendererClear(TUI_Renderer *_Renderer){
        if ( _Renderer == NULL || _Renderer->symbols == NULL || _Renderer->colors == NULL ) {
                return 0;
        }
        
        memset(_Renderer->symbols, _Renderer->draw_symbol, _Renderer->symbols_count);

        if ( _Renderer->color_size ) {
                __memsetXX(_Renderer->colors, &_Renderer->draw_color, _Renderer->color_size, _Renderer->symbols_count);
        }

        return 1;
}





bool TUI_ResizeRenderer(TUI_Renderer *_Renderer, uint32_t _Width, uint32_t _Height) {
        if ( _Renderer == NULL || _Renderer->symbols == NULL || _Renderer->colors == NULL) {
                return 0;
        }

        uint32_t new_count = _Width * _Height;

        TUI_Symbol *new_symbols = realloc( _Renderer->symbols, new_count * sizeof(TUI_Symbol) );
        if ( new_symbols == NULL ) {
                TUI_SetError(TUI_ErrType_AllocationError, "couldn`t allocate memory");
                return 0;  
        }

        _Renderer->symbols = new_symbols;

        void *new_colors;
        if ( _Renderer->color_size ) {
                 new_colors = realloc( _Renderer->colors, new_count * _Renderer->color_size );
        } else {
                new_colors = _Renderer->colors;
        }

        if ( new_colors == NULL ) {
                TUI_SetError(TUI_ErrType_AllocationError, "couldn`t allocate memory");
                return 0;  
        }

        _Renderer->colors = new_colors;

        _Renderer->width = _Width;
        _Renderer->height = _Height;
        _Renderer->symbols_count = new_count;

        return 1;
}



bool TUI_RenderSymbol(TUI_Renderer *_Renderer, uint32_t _X, uint32_t _Y, TUI_Symbol _Symbol, TUI_UniSColor _Color) {
        if ( _Renderer == NULL || _Renderer->symbols == NULL || _Renderer->colors == NULL ||
             _X >= _Renderer->width || _Y >= _Renderer->height )
        {
                return 0;
        }

        uint32_t position = _Y * _Renderer->width  + _X;

        _Renderer->symbols[position] = _Symbol;

        switch ( _Renderer->color_format ) {
                case ColorFormat_RGB:
                        ((TUI_SColorRGB*)_Renderer->colors)[position] = _Color.cfRGB;
                        return 1;
                        
                case ColorFormat_256:
                        ((TUI_SColor256*)_Renderer->colors)[position] = _Color.cf256;
                        return 1;
                case ColorFormat_16:
                        ((TUI_SColor16*)_Renderer->colors)[position] = _Color.cf16;
                        return 1;
                
                default:
                        return 1;
        }
        
        return 1;
}


