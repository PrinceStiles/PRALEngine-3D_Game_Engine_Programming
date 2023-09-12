//File: main.h

//Note: Authors admit that this code is meant to be a quick and dirty demo to show the renderer working, and could be vastly improved
//with OO techniques like smart class encapsulation, etc.

#pragma once

#include <Windows.h>

LRESULT WINAPI MsgProc(HWND, UINT, WPARAM, LPARAM);
HRESULT ProgramStartup(wchar_t *chAPI);
HRESULT ProgramCleanup();
HRESULT ProgramTick();
HRESULT	BuildAndSetShader();
