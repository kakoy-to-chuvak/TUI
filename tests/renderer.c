#include "TUI_Render.h"

#include <time.h>
#include <synchapi.h>




int main() {
        TUI_Renderer *renderer = TUI_CreateRenderer(stdout, 100, 70, ColorFormat_RGB);
        if ( renderer == NULL ) {
                printf("NULL\n");
                return -1;
        }

        renderer->draw_symbol = 'a';
        renderer->draw_color.cfRGB.fg = (TUI_ColorRGB){
                0, 255, 0
        };

        TUI_RendererClear(renderer);

        TUI_RendererPresent(renderer);
        Sleep(2000);

        TUI_ResizeRenderer(renderer, 5, 3);
        renderer->draw_symbol = '0';
        TUI_RendererClear(renderer);
        TUI_RendererPresent(renderer);

        fflush(stdout);
        

        return 1;
}