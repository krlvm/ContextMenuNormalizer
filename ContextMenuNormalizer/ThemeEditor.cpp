#include "ThemeEditor.h"

#include <stdint.h>
#include <stdlib.h>

#include <Windows.h>
#include <Uxtheme.h>
#include <vsstyle.h>
#include <vssym32.h>
#include <sysinfoapi.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "uxtheme.lib")
#pragma warning(disable : 4996)

#if _DEBUG
#include <iostream>
#endif

#pragma region Pixel Color

static inline int PixClr(int val)
{
    return val & 0xFFFFFF;
}

static inline int PixR(BYTE* pPixel)
{
    return PixClr(pPixel[2]);
}
static inline int PixG(BYTE* pPixel)
{
    return PixClr(pPixel[1]);
}
static inline int PixB(BYTE* pPixel)
{
    return PixClr(pPixel[0]);
}
static inline int PixA(BYTE* pPixel)
{
    return PixClr(pPixel[3]);
}

#pragma endregion

typedef struct {
    PixelModifier pmPixelModifier;
    BitmapHandler pmSimpleReplacer;
} CallContext_t;

static void prvSimpleWrapper(const RBContext_t* pxContext, Pixel_t* pPixel, void* pParam) {
    CallContext_t* pCallContext = (CallContext_t*)pParam;
    int r = pPixel->bits.r;
    int g = pPixel->bits.g;
    int b = pPixel->bits.b;
    int a = pPixel->bits.a;
    pCallContext->pmSimpleReplacer(&r, &g, &b, &a);
    pPixel->bits.r = r;
    pPixel->bits.g = g;
    pPixel->bits.b = b;
    pPixel->bits.a = a;
}

static int prvRecolorizeBitmap(int iWidth, int iHeight, Pixel_t *pPixels, void* pParam)
{
    RBContext_t xRBContext;
    xRBContext.width = iWidth;
    xRBContext.height = iHeight;

    for (xRBContext.y = 0; xRBContext.y < iHeight; xRBContext.y++) {
        Pixel_t* pPixel = pPixels + (iWidth * xRBContext.y);

        for (xRBContext.x = 0; xRBContext.x < iWidth; xRBContext.x++) {
#if _DEBUG
            _RPT1(0, "(%d, %d, %d / %d) \n", pPixel->bits.r, pPixel->bits.g, pPixel->bits.b, pPixel->bits.a);
#endif
            CallContext_t* pCallContext = (CallContext_t*) pParam;
            pCallContext->pmPixelModifier(&xRBContext, pPixel, pParam);

            pPixel ++;
        }
    }

    return TRUE;
}

int ModifyContextMenuBitmap(LPCWSTR pszClassList, int iPartId, BitmapModifier pmModifier, void* pParam)
{
    HBITMAP hBitmap;

    HTHEME hTheme = OpenThemeData(GetForegroundWindow(), pszClassList);
    GetThemeBitmap(hTheme, iPartId, 0, TMT_DIBDATA, GBF_DIRECT, &hBitmap);
    CloseThemeData(hTheme);

    BITMAP xBitMap;
    GetObject(hBitmap, sizeof(xBitMap), &xBitMap);

    if (!hBitmap || xBitMap.bmBitsPixel != 32) {
        // Format is not ARGB
        return FALSE;
    }

    int result = FALSE;
    LONG xPixelCount = xBitMap.bmWidth * xBitMap.bmHeight;
    LONG xBitCount = xPixelCount * sizeof(Pixel_t);
    Pixel_t* pPixels = (Pixel_t*)malloc(xBitCount);
    if (!pPixels) {
        return result;
    }

    if (!GetBitmapBits(hBitmap, xBitCount, pPixels)) {
        goto free_bits;
    }

    result = pmModifier(xBitMap.bmWidth, xBitMap.bmHeight, pPixels, pParam);

    if (!SetBitmapBits(hBitmap, xBitCount, pPixels)) {
        goto free_bits;
    }

free_bits:
    if (pPixels) {
        free(pPixels);
    }

    return result;
}

int NormalizeContextMenu(LPCWSTR pszClassList, int iPartId, BitmapHandler pmHandler) {
    CallContext_t xContext;
    xContext.pmPixelModifier = prvSimpleWrapper;
    xContext.pmSimpleReplacer = pmHandler;
    return ModifyContextMenuBitmap(pszClassList, iPartId, prvRecolorizeBitmap, &xContext);
}

int NormalizeContextMenuEx(LPCWSTR pszClassList, int iPartId, PixelModifier pmHandler) {
    CallContext_t xContext;
    xContext.pmPixelModifier = pmHandler;
    return ModifyContextMenuBitmap(pszClassList, iPartId, prvRecolorizeBitmap, &xContext);
}