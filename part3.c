#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <commctrl.h>

#pragma comment(lib, "comctl32.lib")

void textwrite(HWND hwnd, const char *text){ 
     int len = GetWindowTextLength(hwnd); 
     SendMessage(hwnd, EM_SETSEL, len, len); 
     SendMessage(hwnd, EM_REPLACESEL, FALSE, (LPARAM)text); 
}

HWND output; 
HWND hscanf; 
HINSTANCE hInst; 
HWND bar;
HWND houtshell; 

int pointer = 0;

typedef struct{ 
    int pointerN1; 
    int pointerN2; 
    int pointerN3; 
} flag; 

flag flags; 

char type[7128]; 
char *mamssiveC[4056] = {"<stdio.h>", "printf", "scanf", "fgets", "strcmp", "<stdlib.h>", "<string.h>", "fopen", "strtok", "strcat", "struct", "typedef", "memset", "malloc", "free", "strlen", "fread", "fwrite", "fprintf", "fclose"};  
char line[7128];
char buffer[100000000]; 
char out[8032];
char *token; 
char bfr[8056]; 
char bft[8092];

STARTUPINFOA si; 
PROCESS_INFORMATION pi; 

void srv(char *a[], char b[]){ 

   token = strtok(b, " ,.\t<>();{}");

   while(token != NULL){ 
    int found = 0; 

    for(int i = 0; i < 20; i++){
    if(strcmp(token, a[i]) == 0){
    textwrite(houtshell, token); 
    textwrite(houtshell, "\r\n"); 
    found++; 
      break;
    }
}

   token = strtok(NULL, " ,.\t<>();{}");
   }
}

void fileopen(const char *filename){
    FILE *file = fopen(filename, "r"); 
    line[0] = '\0';
    while(fgets(type, sizeof(type), file)){ 
      strncat(line, type, sizeof(line) - strlen(line) - 1);
    }    
    
    char *dest = out; 
    for(char *src = line; *src; ++src){
        if(*src == '\n'){
            *dest++ = '\r'; 
            *dest++ = '\n'; 
        } else { 
            *dest++ = *src; 
        }
    }
    *dest = '\0'; 
    strcpy(line, out);
}

void fileop(const char *filename){
    FILE *file = fopen(filename, "r"); 
    line[0] = '\0';
    while(fgets(type, sizeof(type), file)){ 
    char *dest = out; 
    for(char *src = type; *src; ++src){
        if(*src == '\n'){
            *dest++ = '\r'; 
            *dest++ = '\n'; 
            Sleep(10);
            textwrite(output, type); 
        } else { 
            *dest++ = *src; 
        }
    }    
    *dest = '\0'; 
    strcpy(line, out);
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    switch(uMsg){
        case WM_DESTROY:
           PostQuitMessage(0); 
           return 0;
      
        case WM_CREATE: 
            
           hscanf = CreateWindow(
               "EDIT", "",
               WS_CHILD | WS_VISIBLE | WS_BORDER, 
               20, 20, 200, 25, 
               hwnd, (HMENU)5, 
               NULL, NULL
           ); 
               
            textwrite(hscanf, "created by AutorRadical");

            {
            
            HMENU hMenu = CreateMenu(); 
            HMENU hFileMenu = CreatePopupMenu(); 

            AppendMenuA(hFileMenu, MF_STRING, 450, "about the program"); 
            AppendMenuA(hFileMenu, MF_STRING, 451, "tutorials the use"); 
            AppendMenuA(hFileMenu, MF_STRING, 452, "exit"); 
            AppendMenuA(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "more");

            SetMenu(hwnd, hMenu);
            DrawMenuBar(hwnd);
            
            }
            
            { 
             
              RECT rcc; 
              GetClientRect(hwnd, &rcc); 

              int width = rcc.right - rcc.left; 
              int height = rcc.bottom - rcc.top; 
              
               output = CreateWindowEx(
               WS_EX_CLIENTEDGE, 
               "EDIT", "", 
               WS_CHILD | WS_BORDER | ES_MULTILINE |
               ES_AUTOVSCROLL | ES_READONLY | 
               WS_VSCROLL | WS_VISIBLE, 
               width / 2, 
               0, 
               width / 2, 
               height, 
               hwnd,
               (HMENU)7,
               GetModuleHandle(NULL), 
               NULL
            ); 
            
            } 

            { 
                           
               houtshell = CreateWindowEx(
               WS_EX_CLIENTEDGE, 
               "EDIT", "", 
               WS_CHILD | WS_BORDER | ES_MULTILINE |
               ES_AUTOVSCROLL | ES_READONLY | 
               WS_VSCROLL | WS_VISIBLE, 
               1, 350, 390, 200, 
               hwnd,
               (HMENU)2,
               GetModuleHandle(NULL), 
               NULL
            ); 
            
            } 

            {
            CreateWindow(
                "BUTTON", "ok", 
                WS_CHILD | WS_VISIBLE, 
                20, 60, 80, 30, 
                hwnd, (HMENU)3, 
                NULL, NULL
            ); 
            } 

            {
            CreateWindow(
                "BUTTON", "clean", 
                WS_CHILD | WS_VISIBLE, 
                20, 90, 80, 30, 
                hwnd, (HMENU)6, 
                NULL, NULL
            ); 
            }
               
               {
                INITCOMMONCONTROLSEX icex; 
                icex.dwSize = sizeof(INITCOMMONCONTROLSEX); 
                icex.dwICC = ICC_PROGRESS_CLASS; 
                InitCommonControlsEx(&icex); 

                bar = CreateWindowEx(0, PROGRESS_CLASS, NULL,
                WS_CHILD | WS_VISIBLE, 
                100, 300, 200, 25, 
                hwnd, NULL, hInst, NULL  
                ); 
            
            SendMessageA(bar, PBM_SETRANGE, 0, MAKELPARAM(0, 100)); 
            SendMessageA(bar, PBM_SETSTEP, (WPARAM)1, 0);
            }
    
            break; 
       
        case WM_COMMAND:        
        
        if(LOWORD(wParam) == 9){
           HMENU hpopup = CreatePopupMenu(); 
            AppendMenu(hpopup, MF_STRING, 1001, "C file"); 
            AppendMenu(hpopup, MF_STRING, 1002, "ASM file"); 
            
            RECT rc; 
            GetWindowRect(hwnd, &rc); 

            TrackPopupMenu( 
                hpopup, 
                TPM_LEFTALIGN | TPM_TOPALIGN, 
                rc.left, 
                rc.bottom, 
                0, 
                hwnd, 
                NULL
            ); 
        }

        if(LOWORD(wParam) == 1001){
           flags.pointerN1++; 
        } else if(LOWORD(wParam) == 1002){ 
           flags.pointerN2++; 
        }
    
            switch(LOWORD(wParam)){
                case 450:

                ZeroMemory(&si, sizeof(si)); 
                ZeroMemory(&pi, sizeof(pi)); 

                CreateProcess(
                    "C:\\part5.exe", //your path 
                    NULL, 
                    NULL, 
                    NULL, 
                    FALSE, 
                    0, 
                    NULL, 
                    NULL, 
                    &si, 
                    &pi 
                ); 

                WaitForSingleObject(pi.hProcess, INFINITE); 
                CloseHandle(pi.hProcess); 
                CloseHandle(pi.hThread); 

                break; 

                case 451: 
                
                 ZeroMemory(&si, sizeof(si)); 
                 ZeroMemory(&pi, sizeof(pi)); 

                 CreateProcess(
                "C:\\part4.exe",  //your path 
                    NULL,
                    NULL,  
                    NULL,
                    FALSE, 
                    0, 
                    NULL, 
                    NULL, 
                    &si, 
                    &pi 
                 ); 
                   
                   WaitForSingleObject(pi.hProcess, INFINITE); 
                   CloseHandle(pi.hProcess); 
                   CloseHandle(pi.hThread);
                   break; 
                
                case 452:
                ExitProcess(0);
                break;
            }

       
            if(LOWORD(wParam) == 3){
              if(GetWindowTextA(hscanf, buffer, sizeof(buffer)) == 0){
                MessageBox(
                NULL, 
                "enter name a line input higher",
                "Error!", 
                MB_OK | MB_ICONERROR
                );
             } else { 
              SetTimer(hwnd, 1, 10, NULL);              
               fileop(buffer); 
             }
            
         }
    
            if(LOWORD(wParam) == 6){
               SendMessage(output, WM_SETTEXT, 0, (LPARAM)"");
               SendMessage(houtshell, WM_SETTEXT, 0, (LPARAM)"");
               SendMessage(bar, PBM_SETPOS, 0, 0); 


               InvalidateRect(output, NULL, TRUE); 
               UpdateWindow(output);
            }
             break; 

        case WM_MOUSEMOVE: 
        if(LOWORD(lParam) >= 50 && LOWORD(lParam) <= 200 &&
           HIWORD(lParam) >= 50 && HIWORD(lParam) <= 125){ 
            SetCursor(LoadCursor(NULL, IDC_HELP)); 
           } else {
           SetCursor(LoadCursor(NULL, IDC_ARROW)); 
           } 
           break; 
        
        case WM_TIMER:

        if(wParam == 1){
        int pos = SendMessage(bar, PBM_GETPOS, 0, 0); 
        if(pos < 100){
            SendMessage(bar, PBM_STEPIT, 0, 0); 
             } else { 
            KillTimer(hwnd, 1); 
 
            FILE *file = fopen(buffer, "r"); 
            bfr[0] = '\0';
 
            while(fgets(bfr, sizeof(bfr), file)){ 
            srv(mamssiveC, bfr);
    }
         
        MessageBox(
                NULL, 
                "Searcing End, results in the bottom left line of the output",
                "Searcing true", 
                MB_OK | MB_ICONINFORMATION
        );

        }
    }
        break; 

    case WM_PAINT:
    PAINTSTRUCT ps; 
    HDC hdc = BeginPaint(hwnd, &ps); 

    HBRUSH rectBrush = CreateSolidBrush(RGB(0, 200, 255)); 
    SetTextColor(hdc, RGB(255, 255, 255)); 
    SetBkMode(hdc, TRANSPARENT); 
    TextOut(hdc, 180, 280, "progress bar", lstrlen("progress bar"));
    TextOut(hdc, 345, 335, "v1", lstrlen("v1"));
    TextOut(hdc, 60, 1, "Input Name your file", lstrlen("Input Name your file"));
    EndPaint(hwnd, &ps);
    break; 

        default: 
           return DefWindowProc(hwnd, uMsg, wParam, lParam); 
    }
} 

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nCmdShow){
    WNDCLASS wc = {0}; 
    wc.lpfnWndProc = WndProc; 
    wc.hInstance = hInst; 
    wc.lpszClassName = "part2"; 
    wc.hbrBackground = CreateSolidBrush(RGB(128, 128, 128));
    RegisterClass(&wc); 

    HWND hwnd = CreateWindow("part2", 
                            "CFtexter",
                            WS_OVERLAPPED | WS_VISIBLE |
                             WS_CAPTION | WS_SYSMENU |
                             WS_MINIMIZEBOX, 
                            800, 400, 800, 600,
                            NULL, NULL, hInst, NULL); 

    ShowWindow(hwnd, nCmdShow); 
    
    MSG msg; 
    while(GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg); 
        DispatchMessage(&msg);
    }
 
 return 0;
}