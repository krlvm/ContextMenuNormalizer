#include <Windows.h>
#include <Uxtheme.h>
#include <vsstyle.h>
#include <vssym32.h>
#include <sysinfoapi.h>

#include "ThemeEditor.h"
#include "PopupMenus.h"

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "uxtheme.lib")
#pragma warning(disable : 4996)

#if _DEBUG
#include <iostream>
#endif

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
    if (*r == 145 && *g == 145 && *b == 145)
    {
        *r = 215;
        *g = 215;
        *b = 215;
    }
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
        // Windows 10
        NormalizeContextMenu(L"Menu", MENU_POPUPITEM, Recolorize_Menu_PopupItem);
        NormalizeContextMenu(L"Menu", MENU_POPUPGUTTER, Recolorize_Menu_PopupGutter);
        NormalizeContextMenu(L"Menu", MENU_POPUPCHECKBACKGROUND, Recolorize_Menu_CheckBackground);
        NormalizeContextMenu(L"Menu", MENU_BARITEM, Recolorize_Menu_BarItem);

        NormalizeContextMenu(L"ImmersiveStart::Menu", MENU_POPUPSEPARATOR, Recolorize_ImmersiveMenu_PopupSeparator);
        NormalizeContextMenu(L"ImmersiveStart::Menu", MENU_POPUPITEM, Recolorize_ImmersiveMenu_PopupItem);
        NormalizeContextMenu(L"ImmersiveStart::Menu", MENU_POPUPBACKGROUND, Recolorize_ImmersiveMenu_PopupBackground);

        NormalizeContextMenu(L"ImmersiveStartDark::Menu", MENU_POPUPSEPARATOR, Recolorize_ImmersiveMenuDark_PopupSeparator);
        NormalizeContextMenu(L"DarkMode_ImmersiveStart::Menu", MENU_POPUPSEPARATOR, Recolorize_ImmersiveMenuDark_PopupSeparator);
        NormalizeContextMenu(L"DarkMode::Menu", MENU_POPUPSEPARATOR, Recolorize_ImmersiveMenuDark_PopupSeparator);
        NormalizeContextMenu(L"DarkMode::Menu", MENU_POPUPCHECKBACKGROUND, Recolorize_ImmersiveMenuDark_CheckBackground);
        NormalizeContextMenu(L"DarkMode::Menu", MENU_POPUPBORDERS, Recolorize_ImmersiveMenuDark_PopupBorders);
    }
    else if (info.dwBuildNumber < 22621)
    {
        // before Win11 22H2
        NormalizeContextMenu(L"Menu", MENU_POPUPITEM, Recolorize_Menu_PopupItem11);
        NormalizeContextMenu(L"Menu", MENU_POPUPSEPARATOR, Recolorize_Menu_PopupSeparator11);
    }
    else {
        // Win11 22H2 and after
        ModifyContextMenuBitmap(L"Menu", 27, iWin11_21H1_PopupMenu, NULL);  // The new "MENU_POPUPITEM" in use
        ModifyContextMenuBitmap(L"Menu", MENU_POPUPITEM, iWin11_21H1_PopupMenu, NULL);
        ModifyContextMenuBitmap(L"ImmersiveStart::Menu", MENU_POPUPITEM, iWin11_21H1_PopupMenu, NULL);
    }

    return 0;
}