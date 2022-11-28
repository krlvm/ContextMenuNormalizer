#include "PopupMenus.h"
#include "ThemeEditor.h"

static void prvReplace(int iXPos, int iYPos, int iSize, Pixel_t xBoarder, Pixel_t xFill, Pixel_t* pPixels) {
    for (int iX = iXPos; iX < iXPos + iSize; iX++) {
        for (int iY = iYPos; iY < iYPos + iSize; iY++) {
            if (iX == iXPos || iY == iYPos || iX == iXPos + iSize - 1 || iY == iYPos + iSize - 1) {
                vSetPixel(pPixels, iX, iY, iSize, xBoarder);
            }
            else {
                vSetPixel(pPixels, iX, iY, iSize, xFill);
            }
        }
    }
}

int iWin8_RP_PopupMenu(int iWidth, int iHeight, Pixel_t* pPixels, void* pParam) {
    Pixel_t xBoarder;
    Pixel_t xFill;

    xBoarder.bits.r = 249;
    xBoarder.bits.g = 249;
    xBoarder.bits.b = 249;
    xBoarder.bits.a = 255;

    xFill.bits.r = 249;
    xFill.bits.g = 249;
    xFill.bits.b = 249;
    xFill.bits.a = 255;

    prvReplace(0, iWidth * 0, iWidth, xBoarder, xFill, pPixels);
    prvReplace(0, iWidth * 2, iWidth, xBoarder, xFill, pPixels);

    xBoarder.bits.r = 127;
    xBoarder.bits.g = 181;
    xBoarder.bits.b = 236;
    xBoarder.bits.a = 255;

    xFill.bits.r = 222;
    xFill.bits.g = 239;
    xFill.bits.b = 255;
    xFill.bits.a = 255;

    prvReplace(0, iWidth * 1, iWidth, xBoarder, xFill, pPixels);

    xBoarder.bits.r = 219;
    xBoarder.bits.g = 219;
    xBoarder.bits.b = 219;
    xBoarder.bits.a = 255;

    xFill.bits.r = 249;
    xFill.bits.g = 249;
    xFill.bits.b = 249;
    xFill.bits.a = 255;
    prvReplace(0, iWidth * 3, iWidth, xBoarder, xFill, pPixels);

    return 1;
}