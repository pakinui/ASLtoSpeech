// testing.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "testing.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TESTING, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTING));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTING));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TESTING);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // Calculate the dimensions of the window
        RECT rc;
        GetClientRect(hWnd, &rc);
        int windowWidth = rc.right - rc.left;
        int windowHeight = rc.bottom - rc.top;

        // Draw the green title at the top of the page
        HBRUSH hTitleBrush = CreateSolidBrush(RGB(0, 128, 0)); // RGB value for green
        RECT titleRect = { 0, 0, windowWidth, windowHeight / 4 };
        FillRect(hdc, &titleRect, hTitleBrush);
        DeleteObject(hTitleBrush);

        // Create a font for the title in bold and white color
        HFONT hTitleFont = CreateFont(30, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
        HGDIOBJ hOldFont = SelectObject(hdc, hTitleFont);
        SetTextColor(hdc, RGB(255, 255, 255)); // RGB value for white

        // Draw the title text at the top center of the window
        DrawText(hdc, L"COSC345", -1, &titleRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        // Clean up font
        SelectObject(hdc, hOldFont);
        DeleteObject(hTitleFont);

        // Draw the white container with three clickable buttons
        HBRUSH hButtonBrush = CreateSolidBrush(RGB(255, 255, 255)); // RGB value for white
        RECT buttonRect = { 2 * windowWidth / 3, windowHeight / 4, windowWidth, windowHeight };
        FillRect(hdc, &buttonRect, hButtonBrush);
        DeleteObject(hButtonBrush);

        // Draw the red container with blue text 'camera'
        HBRUSH hRedBrush = CreateSolidBrush(RGB(255, 0, 0)); // RGB value for red
        RECT redRect = { 0, windowHeight / 4, 2 * windowWidth / 3, 3 * windowHeight / 4 };
        FillRect(hdc, &redRect, hRedBrush);
        DeleteObject(hRedBrush);

        // Create a font for the blue text in bold
        HFONT hBlueFont = CreateFont(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
        HGDIOBJ hOldFontBlue = SelectObject(hdc, hBlueFont);
        SetTextColor(hdc, RGB(0, 0, 255)); // RGB value for blue

        // Draw the 'camera' text in the middle of the red container
        DrawText(hdc, L"camera", -1, &redRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        // Clean up font
        SelectObject(hdc, hOldFontBlue);
        DeleteObject(hBlueFont);

        // Draw the green container with white text 'additional area'
        HBRUSH hGreenBrush = CreateSolidBrush(RGB(0, 128, 0)); // RGB value for green
        RECT greenRect = { 0, 3 * windowHeight / 4, 2 * windowWidth / 3, windowHeight };
        FillRect(hdc, &greenRect, hGreenBrush);
        DeleteObject(hGreenBrush);

        // Create a font for the white text in bold
        HFONT hWhiteFont = CreateFont(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
        HGDIOBJ hOldFontWhite = SelectObject(hdc, hWhiteFont);
        SetTextColor(hdc, RGB(255, 255, 255)); // RGB value for white

        // Draw the 'additional area' text in the middle of the green container
        DrawText(hdc, L"additional area", -1, &greenRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        // Clean up font and device context
        SelectObject(hdc, hOldFontWhite);
        DeleteObject(hWhiteFont);
        EndPaint(hWnd, &ps);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
