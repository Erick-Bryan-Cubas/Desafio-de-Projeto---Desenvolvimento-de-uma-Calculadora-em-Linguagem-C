#include <stdio.h>
#include <windows.h>
#define makeButton(name, id, x, y, w, h) CreateWindow("BUTTON", name, WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, x, y, w, h, hwnd, (HMENU)(id), GetModuleHandle(NULL), NULL)
#define ID_NUMBER1 1
#define ID_NUMBER2 2
#define ID_RESULT 3
#define ID_ADD 4
#define ID_SUBTRACT 5
#define ID_MULTIPLY 6
#define ID_DIVIDE 7

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static HWND hwndNumber1, hwndNumber2, hwndResult;
    float number1, number2, result;

    switch (message) {
        case WM_CREATE:
            hwndNumber1 = CreateWindowEx(0, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 10, 100, 20, hwnd, (HMENU)ID_NUMBER1, NULL, NULL);
            hwndNumber2 = CreateWindowEx(0, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 40, 100, 20, hwnd, (HMENU)ID_NUMBER2, NULL, NULL);
            hwndResult = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 70, 100, 20, hwnd, (HMENU)ID_RESULT, NULL, NULL);
            CreateWindowEx(0, "BUTTON", "Add", WS_CHILD | WS_VISIBLE, 120, 10, 100, 20, hwnd, (HMENU)ID_ADD, NULL, NULL);
            CreateWindowEx(0, "BUTTON", "Subtract", WS_CHILD | WS_VISIBLE, 120, 40, 100, 20, hwnd, (HMENU)ID_SUBTRACT, NULL, NULL);
            CreateWindowEx(0, "BUTTON", "Multiply", WS_CHILD | WS_VISIBLE, 120, 70, 100, 20, hwnd, (HMENU)ID_MULTIPLY, NULL, NULL);
            CreateWindowEx(0, "BUTTON", "Divide", WS_CHILD | WS_VISIBLE, 120, 100, 100, 20, hwnd, (HMENU)ID_DIVIDE, NULL, NULL);
            break;

        case WM_COMMAND:
            switch (wParam) {
                case ID_ADD:
                case ID_SUBTRACT:
                case ID_MULTIPLY:
                case ID_DIVIDE:
                    char buffer[64];
                    GetWindowText(hwndNumber1, buffer, sizeof(buffer));
                    number1 = atof(buffer);
                    GetWindowText(hwndNumber2, buffer, sizeof(buffer));
                    number2 = atof(buffer);

                    switch (wParam) {
                        case ID_ADD:
                            result = number1 + number2;
                            break;
                        case ID_SUBTRACT:
                            result = number1 - number2;
                            break;
                        case ID_MULTIPLY:
                            result = number1 * number2;
                            break;
                        case ID_DIVIDE:
                            if (number2 == 0) {
                                MessageBox(hwnd, "Divisão por zero.", "Erro", MB_OK | MB_ICONERROR);
                                return 0;
                            }
                            result = number1 / number2;
                            break;
                    }

                    snprintf(buffer, sizeof(buffer), "%.2f", result);
                    SetWindowText(hwndResult, buffer);
                    break;
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WindowProcedure;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "Calculator";
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "Calculator", "Calculadora Simples", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 240, 180, NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
