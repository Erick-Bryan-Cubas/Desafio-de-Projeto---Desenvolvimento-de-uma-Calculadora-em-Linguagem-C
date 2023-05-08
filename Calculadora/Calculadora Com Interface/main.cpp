#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <stdlib.h>
#include "resource.h"

HINSTANCE hInst;
/// Controles para as caixas de texto
HWND caixa_x, caixa_y, caixa_result;

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    ///----------------------------------------
    case WM_INITDIALOG:
    {
        /// Quando iniciar o aplicativo
        /// Pegamos os controles para cada caixa de texto
        caixa_x      = GetDlgItem(hwndDlg,CAIXA_X);
        caixa_y      = GetDlgItem(hwndDlg,CAIXA_Y);
        caixa_result = GetDlgItem(hwndDlg,CAIXA_RESULT);
    }
    return TRUE;

    case WM_CLOSE:
    {
        EndDialog(hwndDlg, 0);
    }
    return TRUE;

    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {
            /// Caso algum botão seja apertado... Ou outro comando
    case SOMAR:
        char x_str[10], y_str[10];
        /// Obtendo o texto da caixa de texto do X
        GetWindowText(caixa_x, x_str, 10);
        /// Obtendo o texto da caixa de texto do Y
        GetWindowText(caixa_y, y_str, 10);

        float x, y, result;
        /// Função para transformar string em número (double/float)
        /// É da biblioteca stdlib.h
        x = atof(x_str);
        y = atof(y_str);
        result = x + y;

        char result_str[15];
        /// Transformando número em string com a função sprintf() (biblioteca stdio.h)
        sprintf(result_str, "%.2f", result);
        /// Atribuindo a string "result_str" para caixa de texto do resultado
        SetWindowText(caixa_result, result_str);
        break;
        }
    }
    return TRUE;
    }
    ///---------------------------------------
    return FALSE;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst=hInstance;
    InitCommonControls();
    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}
