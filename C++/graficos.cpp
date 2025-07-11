/**
 * @file graficos.cpp
 * @author Jose Luis Cruz (j0z3ph@gmail.com)
 * @brief Traduccion a C de MiniWin. Un mini-conjunto de funciones para abrir una ventana, pintar en
 *    ella y detectar la presión de algunas teclas. Básicamente para hacer
 *    juegos sencillos.
 *    Basado en el trabajo de Pau Fernández.
 * @version 0.2
 * @date 2023-12-09
 *
 *  MiniWin: Un mini-conjunto de funciones para abrir una ventana, pintar en
 *    ella y detectar la presión de algunas teclas. Básicamente para hacer
 *    juegos sencillos.
 *
 *  (c) Pau Fernández, licencia MIT: http://es.wikipedia.org/wiki/MIT_License
 *
 *
 * Git original: https://github.com/pauek/MiniWin
 * Git: https://github.com/j0z3ph/Miniwin
 */

#if defined(_WIN32)

// Windows ////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <sstream>
#include <queue>
#include <cmath>
#include <process.h>
#include <windows.h>
#include <windowsx.h>

#define _GRAFICOS_SOURCE_
#define CLASS_NAME "GraficosXD"
#include "graficos.hpp"

class Variables
{
public:
    HWND hWnd;                 // ventana principal
    HBITMAP hBitmap;           // bitmap para pintar off-screen
    int iWidth;                // ancho de la ventana
    int iHeight;               // alto de la ventana
    HDC hDCMem;                // Device Context en memoria
    bool _raton_dentro;        // el raton esta dentro del 'client area'
    int _xraton, _yraton;      // posicion del raton
    bool _bot_izq, _bot_der;   // botones izquierdo y derecho
    WINDOWPLACEMENT g_wpPrev;  // respaldo de la posicion de la ventana antes de ir a fullscreen
    int iWidthPrev;            // respaldo del ancho de la ventana antes de ir a fullscreen
    int iHeightPrev;           // respaldo del alto de la ventana antes de ir a fullscreen
    bool _fullscreen;          // modo fullscreen
    std::queue<int> _teclas;   // cola de teclas
    std::queue<int> _teclasUp; // cola de teclas 2
    COLORREF _color;           // Color de la brocha (blanco por defecto)
    COLORREF _back_color;      // Color del fondo de la ventana (blanco por defecto)
    COLORREF _colores[8];

    Variables()
    {
        iWidth = 400;
        iHeight = 300;
        hDCMem = NULL;
        _raton_dentro = false;
        _xraton = 0;
        _yraton = 0;
        _bot_izq = false;
        _bot_der = false;
        iWidthPrev = 0;
        iHeightPrev = 0;
        _fullscreen = false;
        _color = RGB(255, 255, 255);
        _back_color = RGB(255, 255, 255);
        _colores[0] = RGB(0, 0, 0);       // NEGRO
        _colores[1] = RGB(255, 0, 0);     // ROJO
        _colores[2] = RGB(0, 255, 0);     // VERDE
        _colores[3] = RGB(0, 0, 255);     // AZUL
        _colores[4] = RGB(255, 255, 0);   // AMARILLO
        _colores[5] = RGB(255, 0, 255);   // MAGENTA
        _colores[6] = RGB(0, 255, 255);   // CYAN
        _colores[7] = RGB(255, 255, 255); // BLANCO
    }
};

// Variables globales
Variables variables;

// Declaraciones de funciones

static LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
static VOID Thread(PVOID pvoid);
static void maybe_call_main();
static void frame_real(int w, int h, int &rw, int &rh);
static void newMemDC(int w, int h);
static bool validKey(const WPARAM &wParam);

// Funcion Principal

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil)
{
    static WNDCLASSEX wincl;
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = CLASS_NAME;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof(WNDCLASSEX);

    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

    if (!RegisterClassEx(&wincl))
        return 0;

    int w, h, xPos, yPos;
    frame_real(variables.iWidth, variables.iHeight, w, h);

    // Centra la ventana
    xPos = (GetSystemMetrics(SM_CXSCREEN) - w) / 2;
    yPos = (GetSystemMetrics(SM_CYSCREEN) - h) / 2;

    variables.hWnd = CreateWindowEx(
        0,                                     /* Extended possibilites for variation */
        CLASS_NAME,                            /* Classname */
        _GRAFICOS_VERSION_,                    /* Title Text */
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, /* no resizable window */
        xPos,                                  /* The window position  */
        yPos,                                  /* in x and y coordinates */
        w,                                     /* The programs width */
        h,                                     /* and height in pixels */
        HWND_DESKTOP,                          /* The window is a child-window to desktop */
        NULL,                                  /* No menu */
        hThisInstance,                         /* Program Instance handler */
        NULL                                   /* No Window Creation data */
    );

    variables.hBitmap = NULL;

    ShowWindow(variables.hWnd, nFunsterStil);

    MSG messages;
    while (GetMessage(&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}

// Definicion de funciones

static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_SIZE:
    {
        RECT R;
        GetClientRect(hWnd, &R);
        int w = R.right - R.left;
        int h = R.bottom - R.top;
        if (w == 0 && h == 0)
            break; // Al minimizar envia WM_SIZE(0,0)

        if (variables.hDCMem == NULL || w != variables.iWidth || h != variables.iHeight)
        {
            newMemDC(w, h);
            maybe_call_main();
        }
        break;
    }
    case WM_SIZING:
    {
        RECT *pRECT = (RECT *)lParam;
        int w, h;
        frame_real(variables.iWidth, variables.iHeight, w, h);
        switch (wParam)
        {
        case WMSZ_BOTTOM:
            pRECT->bottom = pRECT->top + h;
            break;
        case WMSZ_TOP:
            pRECT->top = pRECT->bottom - h;
            break;
        case WMSZ_RIGHT:
            pRECT->right = pRECT->left + w;
            break;
        case WMSZ_LEFT:
            pRECT->left = pRECT->right - w;
            break;
        case WMSZ_TOPLEFT:
            pRECT->top = pRECT->bottom - h;
            pRECT->left = pRECT->right - w;
            break;
        case WMSZ_TOPRIGHT:
            pRECT->top = pRECT->bottom - h;
            pRECT->right = pRECT->left + w;
            break;
        case WMSZ_BOTTOMLEFT:
            pRECT->bottom = pRECT->top + h;
            pRECT->left = pRECT->right - w;
            break;
        case WMSZ_BOTTOMRIGHT:
            pRECT->bottom = pRECT->top + h;
            pRECT->right = pRECT->left + w;
            break;
        }

        return TRUE;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        SelectObject(variables.hDCMem, variables.hBitmap);
        if (variables.hBitmap != NULL)
        {
            BitBlt(hdc, 0, 0, variables.iWidth, variables.iHeight, variables.hDCMem, 0, 0, SRCCOPY);
        }
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_MOUSEMOVE:
    {
        variables._raton_dentro = true;
        variables._xraton = GET_X_LPARAM(lParam);
        variables._yraton = GET_Y_LPARAM(lParam);
        variables._bot_izq = wParam & MK_LBUTTON;
        variables._bot_der = wParam & MK_RBUTTON;
        break;
    }
    case WM_MOUSELEAVE:
    {
        variables._raton_dentro = false;
        break;
    }
    case WM_LBUTTONDOWN:
    {
        variables._bot_izq = true;
        break;
    }
    case WM_LBUTTONUP:
    {
        variables._bot_izq = false;
        break;
    }
    case WM_RBUTTONDOWN:
    {
        variables._bot_der = true;
        break;
    }
    case WM_RBUTTONUP:
    {
        variables._bot_der = false;
        break;
    }
    case WM_KEYDOWN:
    {
        if (validKey(wParam))
            variables._teclas.push(wParam);

        break;
    }
    case WM_KEYUP:
    {
        if (validKey(wParam))
            variables._teclasUp.push(wParam);

        break;
    }

    case WM_DESTROY:
    {
        DeleteObject(variables.hBitmap);
        DeleteDC(variables.hDCMem);
        PostQuitMessage(0);
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

static bool validKey(const WPARAM &wParam)
{
    bool push_it = false;

    // Escape
    push_it |= (wParam == VK_ESCAPE);

    // Flechas
    push_it |= (wParam == VK_LEFT ||
                wParam == VK_RIGHT ||
                wParam == VK_UP ||
                wParam == VK_DOWN);

    // Barra espaciadora
    push_it |= (wParam == VK_SPACE);

    // Enter
    push_it |= (wParam == VK_RETURN);

    // Numeros 0-9
    push_it |= (wParam >= 48 && wParam <= 57);

    // Letras A-Z
    push_it |= (wParam >= 65 && wParam <= 90);

    // Teclas de funcion
    for (int i = 0; i < 10; i++)
        push_it |= (wParam == (VK_F1 + i));

    return push_it;
}

static VOID Thread(PVOID pvoid)
{
    Sleep(50); // FIXME
    _main_();
}

static void maybe_call_main()
{
    static bool started = false;
    if (!started)
    {
        _beginthread(Thread, 0, NULL); // Llama a 'main' (realmente  '_main_')
        started = true;
    }
}

static void frame_real(int w, int h, int &rw, int &rh)
{
    RECT frame = {0, 0, w, h};
    AdjustWindowRect(&frame, WS_OVERLAPPEDWINDOW, FALSE);
    rw = frame.right - frame.left;
    rh = frame.bottom - frame.top;
}

static void newMemDC(int w, int h)
{
    if (variables.hDCMem != NULL)
    {
        DeleteObject(variables.hBitmap);
        DeleteDC(variables.hDCMem);
    }
    HDC hDC = GetDC(variables.hWnd);
    variables.hDCMem = CreateCompatibleDC(hDC);
    variables.hBitmap = CreateCompatibleBitmap(hDC, w, h);
    SelectObject(variables.hDCMem, variables.hBitmap);
    SetBkMode(variables.hDCMem, TRANSPARENT);
    ReleaseDC(variables.hWnd, hDC);
}

static void _rect(int x1, int y1, int x2, int y2, bool fill)
{
    RECT rect = {x1, y1, x2, y2};
    HBRUSH brush = CreateSolidBrush(variables._color);
    if (fill)
        FillRect(variables.hDCMem, &rect, brush);
    else
        FrameRect(variables.hDCMem, &rect, brush);
    DeleteObject(brush);
}

static void _circ(int x, int y, int radio, bool fill)
{
    HPEN hPen = CreatePen(PS_SOLID, 1, variables._color);
    HGDIOBJ orig = SelectObject(variables.hDCMem, hPen);

    if (fill)
    {
        HBRUSH brush = CreateSolidBrush(variables._color);
        SelectObject(variables.hDCMem, brush);
        Ellipse(variables.hDCMem, x, y, x + radio + radio, y + radio + radio);
        DeleteObject(brush);
    }
    else
    {
        SelectObject(variables.hDCMem, GetStockObject(NULL_BRUSH));
        Ellipse(variables.hDCMem, x, y, x + radio + radio, y + radio + radio);
    }
    SelectObject(variables.hDCMem, orig);
    DeleteObject(hPen);
}

////////////////////////////////////////////////////////////////////////////////
//
//   Funciones del API
//
////////////////////////////////////////////////////////////////////////////////

namespace graficos
{
    GraficosAPI ventana;

    const struct graficos::Teclas TECLAS = {
        VK_ESCAPE,
        VK_LEFT,
        VK_RIGHT,
        VK_UP,
        VK_DOWN,
        VK_F1,
        VK_F2,
        VK_F3,
        VK_F4,
        VK_F5,
        VK_F6,
        VK_F7,
        VK_F8,
        VK_F9,
        VK_F10,
        VK_SPACE,
        VK_RETURN,
        48,
        49,
        50,
        51,
        52,
        53,
        54,
        55,
        56,
        57,
        65,
        66,
        67,
        68,
        69,
        70,
        71,
        72,
        73,
        74,
        75,
        76,
        77,
        78,
        79,
        80,
        81,
        82,
        83,
        84,
        85,
        86,
        87,
        88,
        89,
        90,
        0};

    const struct graficos::Colores COLORES = {0, 1, 2, 3, 4, 5, 6, 7};

#pragma region Imagen class

    Imagen::Imagen(std::string ruta) : Imagen(ruta, ruta)
    {
    }

    Imagen::Imagen(std::string ruta, std::string ruta_mask)
    {
        BITMAP bitmap;

        this->_hBitmap = (HBITMAP)LoadImageA(NULL, ruta.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        if (this->_hBitmap == NULL)
        {
            throw GraficosException("No fue posible cargar la imagen '" + ruta + "'.");
        }
        GetObject(this->_hBitmap, sizeof(bitmap), &bitmap);
        this->_alto = bitmap.bmHeight;
        this->_ancho = bitmap.bmWidth;

        // mask
        this->_hBitmapMask = (HBITMAP)LoadImageA(NULL, ruta_mask.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        if (this->_hBitmapMask == NULL)
        {
            throw GraficosException("No fue posible cargar la mascara '" + ruta_mask + "'.");
        }

        this->_hdcimg = CreateCompatibleDC(NULL);
        SelectObject(this->_hdcimg, this->_hBitmap);

        this->_hdcimg_mask = CreateCompatibleDC(NULL);
        SelectObject(this->_hdcimg_mask, this->_hBitmapMask);
    }

    Imagen::~Imagen()
    {
        DeleteObject(this->_hBitmap);
        DeleteObject(this->_hBitmapMask);
        DeleteDC(this->_hdcimg);
        DeleteDC(this->_hdcimg_mask);
    }

    int Imagen::ancho()
    {
        return this->_ancho;
    }
    int Imagen::alto()
    {
        return this->_alto;
    }

    void _renderImage(int x, int y, int w, int h, graficos::Imagen &imagen)
    {
        if (imagen._hBitmapMask != NULL)
        {
            SetStretchBltMode(variables.hDCMem, COLORONCOLOR);

            if (imagen._hBitmapMask != NULL)
            {
                if (imagen._alto == h && imagen._ancho == w)
                {
                    BitBlt(variables.hDCMem, x, y, w, h,
                           imagen._hdcimg_mask, 0, 0, SRCAND);
                }
                else
                {
                    StretchBlt(variables.hDCMem, x, y, w, h,
                               imagen._hdcimg_mask, 0, 0, imagen._ancho, imagen._alto, SRCAND);
                }
                if (imagen._hBitmap != NULL)
                {
                    if (imagen._alto == h && imagen._ancho == w)
                    {
                        BitBlt(variables.hDCMem, x, y, w, h,
                               imagen._hdcimg, 0, 0, SRCPAINT);
                    }
                    else
                    {
                        StretchBlt(variables.hDCMem, x, y, w, h,
                                   imagen._hdcimg, 0, 0, imagen._ancho, imagen._alto, SRCPAINT);
                    }
                }
            }
        }
    }

#pragma endregion

#pragma region GraficosAPI class
        int GraficosAPI::teclaPresionada()
        {
            if (variables._teclas.empty())
                return TECLAS.NINGUNA;
            int ret = variables._teclas.front();
            variables._teclas.pop();
            return ret;
        }

        int GraficosAPI::teclaSoltada()
        {
            while (!variables._teclas.empty())
                variables._teclas.pop();

            if (variables._teclasUp.empty())
                return TECLAS.NINGUNA;

            int ret = variables._teclasUp.front();
            variables._teclasUp.pop();

            return ret;
        }

        bool GraficosAPI::raton(int &x, int &y)
        {
            if (!variables._raton_dentro)
                return false;

            x = variables._xraton;
            y = variables._yraton;
            return true;
        }

        bool GraficosAPI::ratonEnVentana()
        {
            return variables._raton_dentro;
        }

        int GraficosAPI::ratonX()
        {
            return variables._xraton;
        }

        int GraficosAPI::ratonY()
        {
            return variables._yraton;
        }

        void GraficosAPI::ratonBotones(bool &izq, bool &der)
        {
            izq = variables._bot_izq;
            der = variables._bot_der;
        }

        bool GraficosAPI::ratonBotonIzquierdo()
        {
            return variables._bot_izq;
        }

        bool GraficosAPI::ratonBotonDerecho()
        {
            return variables._bot_der;
        }

        void GraficosAPI::espera(int miliseg)
        {
            Sleep(miliseg);
        }

        void GraficosAPI::muestraMensaje(const std::string &msj)
        {
            MessageBox(variables.hWnd, msj.c_str(), "Mensaje...", MB_OK);
        }

        void GraficosAPI::muestraMensaje(const std::string &msj, const std::string &titulo)
        {
            MessageBox(variables.hWnd, msj.c_str(), titulo.c_str(), MB_OK);
        }

        bool GraficosAPI::muestraPregunta(const std::string &msj)
        {
            return MessageBox(variables.hWnd, msj.c_str(), "Pregunta...", MB_OKCANCEL) == IDOK;
        }

        bool GraficosAPI::muestraPregunta(const std::string &msj, const std::string &titulo)
        {
            return MessageBox(variables.hWnd, msj.c_str(), titulo.c_str(), MB_OKCANCEL) == IDOK;
        }

        void GraficosAPI::limpiaVentana()
        {
            RECT R;
            SetRect(&R, 0, 0, variables.iWidth, variables.iHeight);
            HBRUSH hBrush = CreateSolidBrush(variables._back_color);
            FillRect(variables.hDCMem, &R, hBrush);
            DeleteObject(hBrush);
        }

        void GraficosAPI::actualizaVentana()
        {
            RedrawWindow(variables.hWnd, NULL, NULL, RDW_INVALIDATE | RDW_INTERNALPAINT);
        }

        void GraficosAPI::punto(int x, int y)
        {
            SetPixel(variables.hDCMem, x, y, variables._color);
        }

        void GraficosAPI::linea(int x1, int y1, int x2, int y2)
        {
            BeginPath(variables.hDCMem);
            MoveToEx(variables.hDCMem, x1, y1, NULL);
            LineTo(variables.hDCMem, x2, y2);
            EndPath(variables.hDCMem);
            HPEN hPen = CreatePen(PS_SOLID, 1, variables._color);
            SelectObject(variables.hDCMem, hPen);
            StrokePath(variables.hDCMem);
            DeleteObject(hPen);
        }

        void GraficosAPI::rectangulo(int x1, int y1, int x2, int y2)
        {
            _rect(x1, y1, x2, y2, false);
        }

        void GraficosAPI::rectanguloRelleno(int x1, int y1, int x2, int y2)
        {
            _rect(x1, y1, x2, y2, true);
        }

        void GraficosAPI::circulo(int x, int y, int radio)
        {
            _circ(x, y, radio, false);
        }

        void GraficosAPI::circuloRelleno(int x, int y, int radio)
        {
            _circ(x, y, radio, true);
        }

        void GraficosAPI::texto(int x, int y, const std::string &texto)
        {
            SetTextColor(variables.hDCMem, variables._color);
            TextOut(variables.hDCMem, x, y, texto.c_str(), texto.size());
        }

        void GraficosAPI::texto(int x, int y, const std::string &texto, int tamanioFuente, const std::string &fuente,
                                bool italica, bool negrita, bool subrayada)
        {
            HFONT hf, hforiginal;
            hf = CreateFont(tamanioFuente, 0, 0, 0, (negrita ? FW_BOLD : FW_NORMAL), italica, subrayada, 0, 0, 0, 0, 0, 0, fuente.c_str());
            hforiginal = (HFONT)SelectObject(variables.hDCMem, hf);
            SetTextColor(variables.hDCMem, variables._color);
            TextOut(variables.hDCMem, x, y, texto.c_str(), texto.size());
            SelectObject(variables.hDCMem, hforiginal);
            DeleteObject(hf);
        }

        void GraficosAPI::muestraImagen(int x, int y, Imagen &imagen)
        {
            _renderImage(x, y, imagen.ancho(), imagen.alto(), imagen);
        }

        void GraficosAPI::muestraImagen(int x, int y, Imagen *imagen)
        {
            _renderImage(x, y, imagen->ancho(), imagen->alto(), *imagen);
        }

        void GraficosAPI::muestraImagen(int x, int y, int ancho, int alto, Imagen &imagen)
        {
            _renderImage(x, y, ancho, alto, imagen);
        }

        void GraficosAPI::muestraImagen(int x, int y, int ancho, int alto, Imagen *imagen)
        {
            _renderImage(x, y, ancho, alto, *imagen);
        }

        void GraficosAPI::color(int c)
        {
            if (c >= 0 && c <= 7)
                variables._color = variables._colores[c];
            else
                variables._color = variables._colores[0];
        }

        void GraficosAPI::color(UINT8 r, UINT8 g, UINT8 b)
        {
            variables._color = RGB(r, g, b);
        }

        void GraficosAPI::colorFondo(int c)
        {
            if (c >= 0 && c <= 7)
                variables._back_color = variables._colores[c];
            else
                variables._back_color = variables._colores[0];
        }

        void GraficosAPI::colorFondo(UINT8 r, UINT8 g, UINT8 b)
        {
            variables._back_color = RGB(r, g, b);
        }

        int GraficosAPI::ancho()
        {
            return variables.iWidth;
        }

        int GraficosAPI::alto()
        {
            return variables.iHeight;
        }

        void GraficosAPI::tamanio(int ancho, int alto)
        {
            variables.iWidth = ancho;
            variables.iHeight = alto;
            int w, h;
            int xPos;
            int yPos;

            frame_real(variables.iWidth, variables.iHeight, w, h);

            // Centra la ventana
            xPos = (GetSystemMetrics(SM_CXSCREEN) - w) / 2;
            yPos = (GetSystemMetrics(SM_CYSCREEN) - h) / 2;

            SetWindowPos(variables.hWnd, HWND_TOP, xPos, yPos, w, h, SWP_FRAMECHANGED);
            newMemDC(w, h);
        }

        void GraficosAPI::pantallaCompleta(bool fullscreenOn)
        {
            DWORD dwStyle = GetWindowLong(variables.hWnd, GWL_STYLE);
            if (fullscreenOn && !variables._fullscreen)
            {
                MONITORINFO mi = {sizeof(mi)};
                if (GetWindowPlacement(variables.hWnd, &variables.g_wpPrev) &&
                    GetMonitorInfo(MonitorFromWindow(variables.hWnd, MONITOR_DEFAULTTOPRIMARY), &mi))
                {
                    SetWindowLong(variables.hWnd, GWL_STYLE,
                                  dwStyle & ~WS_OVERLAPPEDWINDOW);
                    SetWindowPos(variables.hWnd, HWND_TOP,
                                 mi.rcMonitor.left, mi.rcMonitor.top,
                                 mi.rcMonitor.right - mi.rcMonitor.left,
                                 mi.rcMonitor.bottom - mi.rcMonitor.top,
                                 SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
                    variables.iWidthPrev = variables.iWidth;
                    variables.iHeightPrev = variables.iHeight;
                    variables.iWidth = mi.rcMonitor.right - mi.rcMonitor.left;
                    variables.iHeight = mi.rcMonitor.bottom - mi.rcMonitor.top;
                    variables._fullscreen = true;
                    limpiaVentana();
                    actualizaVentana();
                }
            }
            else if (!fullscreenOn && variables._fullscreen)
            {
                SetWindowLong(variables.hWnd, GWL_STYLE,
                              dwStyle | WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX);
                SetWindowPlacement(variables.hWnd, &variables.g_wpPrev);
                variables.iWidth = variables.iWidthPrev;
                variables.iHeight = variables.iHeightPrev;
                variables._fullscreen = false;
                tamanio(variables.iWidth, variables.iHeight);
                limpiaVentana();
                actualizaVentana();
            }
        }

        void GraficosAPI::cierra()
        {
            PostMessage(variables.hWnd, WM_CLOSE, 0, 0);
        }

        void GraficosAPI::titulo(const std::string &titulo)
        {
            SetWindowTextA(variables.hWnd, titulo.c_str());
        }

        void GraficosAPI::imprimeEnConsola(const std::string &message)
        {
            HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
            if (stdOut == NULL || stdOut == INVALID_HANDLE_VALUE)
            {
                AllocConsole();
                stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
            }
            if (stdOut != NULL && stdOut != INVALID_HANDLE_VALUE)
            {
                DWORD written = 0;
                WriteConsoleA(stdOut, message.c_str(), message.size(), &written, NULL);
            }
        }
#pragma endregion

#pragma region GraficosException class

        GraficosException::GraficosException(const std::string &msg) : mensaje(msg) {}

        const char *GraficosException::what() const throw()
        {
            return mensaje.c_str();
        }

#pragma endregion
    }

    ///////////////////////////////////////////////////////////////////////////////////////

#else

#error "Graficos no funciona en esta plataforma"

#endif
