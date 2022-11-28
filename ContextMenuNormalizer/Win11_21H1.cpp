#include "PopupMenus.h"
#include "ThemeEditor.h"

Pixel_t apxCorner[4][4] = {
    {0xFFF9F9F9, 0xFFCAE1F2, 0xFF449BDE, 0xFF057BD5},
    {0xFFCAE1F2, 0xFF097DD6, 0xFF0078D4, 0xFF0078D4},
    {0xFF449BDE, 0xFF0078D4, 0xFF0078D4, 0xFF0078D4},
    {0xFF057BD5, 0xFF0078D4, 0xFF0078D4, 0xFF0078D4}
};

static void prvPaint(int iXPos, int iYPos, int iSize, Pixel_t* pPixels) {
    // Top-Left
    for (int iX = 0; iX < 4; iX++) {
        for (int iY = 0; iY < 4; iY++) {
            vSetPixel(pPixels, iXPos + iX, iYPos + iY, iSize, apxCorner[iX][iY]);
        }
    }

    // Top-Right
    for (int iX = 0; iX < 4; iX++) {
        for (int iY = 0; iY < 4; iY++) {
            vSetPixel(pPixels, iXPos + iSize - iX - 1, iYPos + iY, iSize, apxCorner[iX][iY]);
        }
    }

    // Bottom-Left
    for (int iX = 0; iX < 4; iX++) {
        for (int iY = 0; iY < 4; iY++) {
            vSetPixel(pPixels, iXPos + iX, iYPos + iSize - iY - 1, iSize, apxCorner[iX][iY]);
        }
    }

    // Bottom-Right
    for (int iX = 0; iX < 4; iX++) {
        for (int iY = 0; iY < 4; iY++) {
            vSetPixel(pPixels, iXPos + iSize - iX - 1, iYPos + iSize - iY - 1, iSize, apxCorner[iX][iY]);
        }
    }
}

static void prvFill(int iXPos, int iYPos, int iSize, Pixel_t xFill, Pixel_t* pPixels) {
    for (int iX = iXPos; iX < iXPos + iSize; iX++) {
        for (int iY = iYPos; iY < iYPos + iSize; iY++) {
            vSetPixel(pPixels, iX, iY, iSize, xFill);
        }
    }
}

int iWin11_21H1_PopupMenu(int iWidth, int iHeight, Pixel_t* pPixels, void* pParam) {
    Pixel_t xFill;

    xFill.bits.r = 249;
    xFill.bits.g = 249;
    xFill.bits.b = 249;
    xFill.bits.a = 255;

    prvFill(0, iWidth * 0, iWidth, xFill, pPixels);
    prvFill(0, iWidth * 2, iWidth, xFill, pPixels);
    prvFill(0, iWidth * 3, iWidth, xFill, pPixels);

    xFill.bits.r = 0;
    xFill.bits.g = 120;
    xFill.bits.b = 212;
    xFill.bits.a = 255;

    prvFill(0, iWidth * 1, iWidth, xFill, pPixels);
    prvPaint(0, iWidth * 1, iWidth, pPixels);

    return 1;
}