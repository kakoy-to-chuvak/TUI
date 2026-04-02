#include "TUI_Render.h"

#include <time.h>



void TestColor256(TUI_Color256 color256) {
        TUI_Color16 color16 = TUI_TransformColor256_16(color256);
        TUI_ColorRGB colorRGB = TUI_TransformColor256_RGB(color256);

        TUI_PrintBgColor(&color256, ColorFormat_256, stdout);
        printf("    ");
        TUI_PrintBgColor(&colorRGB, ColorFormat_RGB, stdout);
        printf("    ");
        TUI_PrintBgColor(&color16, ColorFormat_16, stdout);
        printf("    \x1b[49m");
}

void TestColor16(TUI_Color16 color16) {
        TUI_Color256 color256 = TUI_TransformColor16_256(color16);
        TUI_ColorRGB colorRGB = TUI_TransformColor16_RGB(color16);

        TUI_PrintBgColor(&color16, ColorFormat_16, stdout);
        printf("    ");
        TUI_PrintBgColor(&color256, ColorFormat_256, stdout);
        printf("    ");
        TUI_PrintBgColor(&colorRGB, ColorFormat_RGB, stdout);
        printf("    \x1b[49m");
}


void TestColorRGB(TUI_ColorRGB colorRGB) {
        TUI_Color256 color256 = TUI_TransformColorRGB_256(colorRGB);
        TUI_Color16 color16 = TUI_TransformColorRGB_16(colorRGB);

        TUI_PrintBgColor(&colorRGB, ColorFormat_RGB, stdout);
        printf("    ");
        TUI_PrintBgColor(&color256, ColorFormat_256, stdout);
        printf("    ");
        TUI_PrintBgColor(&color16, ColorFormat_16, stdout);
        printf("    \x1b[49m|");

        colorRGB = TUI_TransformColor256_RGB(color256);
        printf(" %.3i %.3i %.3i ", colorRGB.r, colorRGB.g, colorRGB.b);
}


int main() {
        srand(time(NULL));

        printf("--- |     256    |     16     |             |    RGB     |   result    |\n");
        printf("--- |256 RGB 16  |16  256 RGB | r   g   b   |RGB 256 16  | r   g   b   |\n");
        for ( int i = 0 ; i < 256 ; i++ ) {
                printf("%.3i |", i);
                TestColor256(i);
                printf("|");
                if ( ( i >= 30 && i < 38 ) || ( i >= 90 && i < 98 ) ) {
                        TestColor16(i);
                        printf("|");
                } else {
                        printf("            |");
                }

                TUI_ColorRGB colorRGB;
                colorRGB.r = rand();
                colorRGB.g = rand();
                colorRGB.b = rand();
                printf(" %.3i %.3i %.3i |", colorRGB.r, colorRGB.g, colorRGB.b);
                TestColorRGB(colorRGB);
                printf("|");

                printf("\n");

        }

        
        return 1;
}
