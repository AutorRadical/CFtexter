#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void textwrite(HWND hwnd, const char *text){ 
  int len = GetWindowTextLength(hwnd); 
  SendMessage(hwnd, EM_SETSEL, len, len); 
  SendMessage(hwnd, EM_REPLACESEL, FALSE, (LPARAM)text); 
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
  switch(msg){
    case WM_DESTROY:
      PostQuitMessage(0); 
      return 0;

    case WM_CREATE:
    
    RECT rc; 
    GetClientRect(hwnd, &rc); 

    int width = rc.right - rc.left;
    int height = rc.bottom - rc.top; 

    HWND hstr = CreateWindowEx(
      WS_EX_CLIENTEDGE, 
      "EDIT", "", 
      WS_CHILD | WS_BORDER | WS_VISIBLE |
      ES_AUTOVSCROLL | ES_MULTILINE | ES_READONLY | 
      WS_VSCROLL, 
      90, 90, 410, 410,
      hwnd, 
      (HMENU)9, 
      GetModuleHandle(NULL), 
      NULL
    ); 
     textwrite(hstr, "Hello, this is a manual that explains how to use the program. The first thing you notice is the OK and Clean buttons. The first OK button is used to confirm the file name you entered and start the analysis, and the second button, Clean, is used to clear the text output lines and found calls. Theres no point in explaining the menu above; this is the entire manual.");

    {
     CreateWindow(
      "BUTTON", "exit", 
      WS_CHILD | WS_VISIBLE, 
      240, 510, 60, 40, 
      hwnd, (HMENU)3, 
      NULL, NULL
     ); 
    }

    break; 

    case WM_PAINT:
    PAINTSTRUCT ps; 
    HDC hdc = BeginPaint(hwnd, &ps); 

    HBRUSH rectBrush = CreateSolidBrush(RGB(0, 200, 255)); 
    SetTextColor(hdc, RGB(255, 255, 255)); 
    SetBkMode(hdc, TRANSPARENT); 
    TextOut(hdc, 500, 500, "v1", lstrlen("v1")); 
    
    SetTextColor(hdc, RGB(255, 255, 255)); 
    SetBkMode(hdc, TRANSPARENT); 
    TextOut(hdc, 250, 70, "tutorial menu", lstrlen("tutorial menu")); 
    EndPaint(hwnd, &ps);   
    break; 
    
    case WM_COMMAND: 
    if(LOWORD(wParam) == 3){
      ExitProcess(0);
    }
    
    {
    if(LOWORD(wParam) == 9){
    }
    
    }
    
    break; 
    
    default: 
      return DefWindowProc(hwnd, msg, wParam, lParam); 
  }
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nCmdShow){ 
  WNDCLASS wc = {0}; 
  wc.lpfnWndProc = WndProc; 
  wc.hInstance = hInst; 
  wc.lpszClassName = "helpwindow"; 
  wc.hbrBackground = CreateSolidBrush(RGB(128, 128, 128)); 
  RegisterClass(&wc); 

  HWND hwnd = CreateWindow(
    "helpwindow", 
    "Help Menu", 
    WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
    400, 400, 600, 600, 
    NULL, NULL, hInst, NULL
  ); 

  ShowWindow(hwnd, nCmdShow); 

  MSG msg; 
  while(GetMessage(&msg, NULL, 0, 0)){
    TranslateMessage(&msg); 
    DispatchMessage(&msg); 
  }
  
  return 0; 
}