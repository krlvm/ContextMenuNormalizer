#ifndef __INCLUDE_THEME_EDITOR_H_
#define __INCLUDE_THEME_EDITOR_H_

#include <stdint.h>

#include <Windows.h>

// MSB --- ARGB --> LSB
typedef union {
    uint32_t all;
    struct {
        uint8_t b, g, r, a;
    } bits;
} Pixel_t;

typedef struct {
    int x, y;
    int width, height;
} RBContext_t;

static inline void vSetPixel(Pixel_t* pPixels, int iX, int iY, int iWidth, Pixel_t xPixel) {
    pPixels[iWidth * iY + iX] = xPixel;
}

typedef void (*BitmapHandler)(int* r, int* g, int* b, int* a);
typedef void (*PixelModifier)(const RBContext_t* pxContext, Pixel_t* pPixels, void* pParam);
typedef int (*BitmapModifier)(int iWidth, int iHeight, Pixel_t* pPixels, void* pParam);

Pixel_t xGetPixel(uint32_t uiRawPixel);

int ModifyContextMenuBitmap(LPCWSTR pszClassList, int iPartId, BitmapModifier pmModifier, void* pParam);
int NormalizeContextMenu(LPCWSTR pszClassList, int iPartId, BitmapHandler pmHandler);

#endif // !__INCLUDE_THEME_EDITOR_H_
