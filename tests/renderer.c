#include "TUI_Render.h"

#include <time.h>
#include <synchapi.h>




int main() {
        TUI_Renderer *renderer = TUI_RendererCreate(stdout, 100, 50, ColorFormat_RGB);
        if ( renderer == NULL ) {
                printf("NULL\n");
                return -1;
        }

        renderer->draw_symbol = '|';
        renderer->draw_color.cfRGB.fg = (TUI_ColorRGB){
                0, 0, 0
        };

        TUI_RendererClear(renderer);


        TUI_UniSColor now;
        now.cfRGB = ((TUI_SColorRGB){((TUI_ColorRGB){0, 0, 0}), ((TUI_ColorRGB){0, 0, 0})});

        for ( int y = 0 ; y <= 50 ; y++ ) {
                for ( int x = 0 ; x < 100 ; x++ ) {
                        now.cfRGB.bg = (TUI_ColorRGB){
                                255 - y - y / 2, x + x, 0
                        };

                        TUI_RenderSymbol(renderer, x, y, ' ', now);
                }
        }

        TUI_RendererPresent(renderer);

        printf("\x1b[0m");
        return 1;
}