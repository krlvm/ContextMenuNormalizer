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

inline int PixClr(int val)
{
    return val & 0xFFFFFF;
}

inline int PixR(BYTE* pPixel)
{
    return PixClr(pPixel[2]);
}
inline int PixG(BYTE* pPixel)
{
    return PixClr(pPixel[1]);
}
inline int PixB(BYTE* pPixel)
{
    return PixClr(pPixel[0]);
}
inline int PixA(BYTE* pPixel)
{
    return PixClr(pPixel[3]);
}

#pragma endregion

typedef void (*BitmapHandler)(int* r, int* g, int* b, int* a);

#pragma region Recolorizators

#define CONTEXT_MENU_BACKGROUND_LIGHT 238

void Recolorize_Menu_PopupItem(int* r, int* g, int* b, int* a) {
    if (*a == 13)
    {
        *a = 0;
    }
    else if (*r == 0 && *g == 56 && *b == 102)
    {
        *r = 0;
        *g = 0;
        *b = 0;
        *a = 23;
    }
}
void Recolorize_Menu_PopupGutter(int* r, int* g, int* b, int* a) {
    *r = CONTEXT_MENU_BACKGROUND_LIGHT;
    *g = CONTEXT_MENU_BACKGROUND_LIGHT;
    *b = CONTEXT_MENU_BACKGROUND_LIGHT;
    *a = 255;
}
void Recolorize_Menu_CheckBackground(int* r, int* g, int* b, int* a) {
    *r = 0;
    *g = 0;
    *b = 0;
    *a = 0;
}
void Recolorize_Menu_BarItem(int* r, int* g, int* b, int* a) {
    if (*r == 0 && *g == 56 && *b == 102)
    {
        *r = 0;
        *g = 0;
        *b = 0;
        *a = 28;
    }
    else if (*r == 0 && *g == 28 && *b == 51)
    {
        *r = 0;
        *g = 0;
        *b = 0;
        *a = 20;
    }
    else if (*r == 0 && *g == 14 && *b == 26)
    {
        *r = 0;
        *g = 0;
        *b = 0;
        *a = 12;
    }
}

void Recolorize_ImmersiveMenu_PopupSeparator(int* r, int* g, int* b, int* a) {
    *r = 215;
    *g = 215;
    *b = 215;
}
void Recolorize_ImmersiveMenu_PopupItem(int* r, int* g, int* b, int* a) {
    if (*r == 255 && *g == 255 && *b == 255)
    {
        *r = 217;
        *g = 217;
        *b = 217;
    }
}
void Recolorize_ImmersiveMenu_PopupBackground(int* r, int* g, int* b, int* a) {
    *r = CONTEXT_MENU_BACKGROUND_LIGHT;
    *g = CONTEXT_MENU_BACKGROUND_LIGHT;
    *b = CONTEXT_MENU_BACKGROUND_LIGHT;
}

void Recolorize_ImmersiveMenuDark_PopupSeparator(int* r, int* g, int* b, int* a) {
    if (*r == 128 && *g == 128 && *b == 128)
    {
        *r = 64;
        *g = 64;
        *b = 64;
    }
}
void Recolorize_ImmersiveMenuDark_CheckBackground(int* r, int* g, int* b, int* a) {
    //*r = 43;
    //*g = 43;
    //*b = 43;
    //*a = 0;
}
void Recolorize_ImmersiveMenuDark_PopupBorders(int* r, int* g, int* b, int* a) {
    if (*r == 128 && *g == 128 && *b == 128)
    {
        *r = 86;
        *g = 86;
        *b = 86;
    }
}


void Recolorize_Menu_PopupItem11(int* r, int* g, int* b, int* a) {
    if (*a == 13)
    {
        *a = 0;
    }
    else if (*r == 0 && *g == 56 && *b == 102)
    {
        *r = 0;
        *g = 0;
        *b = 0;
        *a = 16;
    }
}
void Recolorize_Menu_PopupSeparator11(int* r, int* g, int* b, int* a) {
    if (*r == 215 && *g == 215 && *b == 215)
    {
        *r = 229;
        *g = 229;
        *b = 229;
    }
}
#pragma endregion

int RecolorizeBitmap(HBITMAP hbm, BitmapHandler handler)
{
    BITMAP bm;
    GetObject(hbm, sizeof(bm), &bm);

    if (!hbm || bm.bmBitsPixel != 32) {
        return FALSE;
    }

    BYTE* pBits = new BYTE[bm.bmWidth * bm.bmHeight * 4];
    GetBitmapBits(hbm, bm.bmWidth * bm.bmHeight * 4, pBits);

    for (int y = 0; y < bm.bmHeight; y++) {
        BYTE* pPixel = (BYTE*)pBits + bm.bmWidth * 4 * y;

        for (int x = 0; x < bm.bmWidth; x++) {

            int r = PixR(pPixel); // [2]
            int g = PixG(pPixel); // [1]
            int b = PixB(pPixel); // [0]
            int a = PixA(pPixel); // [3]

#if _DEBUG
            _RPT1(0, "(%d, %d, %d / %d) \n", r, g, b, a);
#endif

            handler(&r, &g, &b, &a);

            pPixel[2] = r;
            pPixel[1] = g;
            pPixel[0] = b;
            pPixel[3] = a;

            pPixel += 4;
        }
    }


    SetBitmapBits(hbm, bm.bmWidth * bm.bmHeight * 4, pBits);

    delete[] pBits;
    return TRUE;
}

int NormalizeContextMenu(LPCWSTR pszClassList, int iPartId, BitmapHandler handler)
{
    HBITMAP hBitmap;

    HTHEME hTheme = OpenThemeData(GetForegroundWindow(), pszClassList);
    GetThemeBitmap(hTheme, iPartId, 0, TMT_DIBDATA, GBF_DIRECT, &hBitmap);
    CloseThemeData(hTheme);

    return RecolorizeBitmap(hBitmap, handler);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{

    OSVERSIONINFOEX info;
    info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    GetVersionEx((LPOSVERSIONINFO)&info);

    if (info.dwBuildNumber < 22000)
    {
        NormalizeContextMenu(L"Menu", 14, Recolorize_Menu_PopupItem);
        NormalizeContextMenu(L"Menu", 13, Recolorize_Menu_PopupGutter);
        NormalizeContextMenu(L"Menu", 12, Recolorize_Menu_CheckBackground);
        NormalizeContextMenu(L"Menu", 8, Recolorize_Menu_BarItem);

        NormalizeContextMenu(L"ImmersiveStart::Menu", 15, Recolorize_ImmersiveMenu_PopupSeparator);
        NormalizeContextMenu(L"ImmersiveStart::Menu", 14, Recolorize_ImmersiveMenu_PopupItem);
        NormalizeContextMenu(L"ImmersiveStart::Menu", 9, Recolorize_ImmersiveMenu_PopupBackground);

        NormalizeContextMenu(L"ImmersiveStartDark::Menu", 15, Recolorize_ImmersiveMenuDark_PopupSeparator);
        NormalizeContextMenu(L"DarkMode_ImmersiveStart::Menu", 15, Recolorize_ImmersiveMenuDark_PopupSeparator);
        NormalizeContextMenu(L"DarkMode::Menu", 15, Recolorize_ImmersiveMenuDark_PopupSeparator);
        NormalizeContextMenu(L"DarkMode::Menu", 12, Recolorize_ImmersiveMenuDark_CheckBackground);
        NormalizeContextMenu(L"DarkMode::Menu", 10, Recolorize_ImmersiveMenuDark_PopupBorders);
    }
    else
    {
        NormalizeContextMenu(L"Menu", 14, Recolorize_Menu_PopupItem11);
        NormalizeContextMenu(L"Menu", 15, Recolorize_Menu_PopupSeparator11);
    }

    return 0;
}