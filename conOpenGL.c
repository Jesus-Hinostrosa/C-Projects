/**************************
 * Includes
 *
 **************************/

#include <windows.h>
#include <gl/gl.h>


/**************************
 * Function Declarations
 *
 **************************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);

/**************
 *Declaraciones
 **************/

#include "logo.h"
#include "koch.h"
#include "rama.h"
#include "dragon.h"
#include "Ccurve.h"
#include "gosper.h"
#include "mandelbrot.h"
#include "nested.h"
#include "hooksnow.h"
#include "hil.h"
#include "sierpinski.h"
#include "weave.h"
#include "corner.h"

#define escX 0.125
#define escY 0.125
#define MX 0.0
#define MY 0.0

void segmento(double, double, double, double);




/**************************
 * WinMain
 *
 **************************/

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;        
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "graficos";
    RegisterClass (&wc);

    char fractales=0, funciones=0;
    misFractales miFractal;
    int nRecursion = 5;
    LOGO miTortuga;
    char *miParametro="koch";

    if (iCmdShow>1) miParametro = lpCmdLine;
    if (strlen(lpCmdLine)==0) miParametro="Ccurve";

    if((strncmp(miParametro, "koch", 4)==0)
	     || (strncmp(miParametro, "dragon", 6)==0) || (strncmp(miParametro, "hil", 3)==0) 
		 || (strncmp(miParametro, "sierpinski", 10)==0)  || (strncmp(miParametro, "Ccurve",6)==0)
		 || (strncmp(miParametro, "gosper", 6)==0) || (strncmp(miParametro, "mandelbrot", 10)==0)
		 || (strncmp(miParametro, "corner", 6)==0) || (strncmp(miParametro, "weave", 5)==0)
		 || (strncmp(miParametro, "nested", 6)==0) || (strncmp(miParametro, "hooksnow", 8)==0)){
      fractales=1;
      asignaModoDibujarSegmento(segmento, &miTortuga);
      if(strncmp(miParametro, "dragon", 6)==0){
    	iniciaDragon(13, 0.09, 3.0, 1.0, &miTortuga);
        miFractal = dibujaDragon;
	  } else if(strncmp(miParametro, "nested", 6)==0){
    	iniciaNested(6, 10, -5.0, 4.0, &miTortuga);
        miFractal = dibujaNested;
	  } else if(strncmp(miParametro, "corner", 6)==0){
    	iniciaCorner(4, 144, 0.05, -2.0, 2.0, &miTortuga);
        miFractal = dibujaCorner;
	  } else if(strncmp(miParametro, "weave", 5)==0){
    	iniciaWeave(2, 10, -1.0, 0, -6.0, 0.0, &miTortuga);
        miFractal = dibujaWeave;
	  } else if(strncmp(miParametro, "Ccurve", 6)==0){
    	iniciaC(10, 0.15, -1.0, 2.0, &miTortuga);
        miFractal = dibujaC;
	  } else if(strncmp(miParametro, "hooksnow", 8)==0){
    	iniciaHooksnow(3, 9, -5.0, -2.0, &miTortuga);
        miFractal = dibujaHooksnow;
	  } else if(strncmp(miParametro, "mandelbrot", 10)==0){
    	iniciaMandelbrot(2, 6, -3.0, 3.0, &miTortuga);
        miFractal = dibujaMandelbrot;
	  } else if(strncmp(miParametro, "gosper", 6)==0){
    	iniciaGosper(3, 6, -4.0, 2.0, &miTortuga);
        miFractal = dibujaGosper;
	  } else if(strncmp(miParametro, "sierpinski", 10)==0){
    	iniciaSierpinski(4, 0.29, -5.0, 5.0, &miTortuga);
        miFractal = dibujaSierpinski;
	  } else if(strncmp(miParametro, "hil", 3)==0){
    	iniciaHil(5, 0.29, 1, -5.0, -3.0, &miTortuga);
        miFractal = dibujaHil;
	  } else if (strncmp(miParametro, "kochII", 6)==0){
        iniciaKoch(3, 10.0, -5.0, -2.5, &miTortuga);
        miFractal = dibujaKochII;
      } else if (strncmp(miParametro, "kochI", 5)==0){
        iniciaKoch(3, 10.0, -5.0, 2.5, &miTortuga);
        miFractal = dibujaKochI;
      } else {
        iniciaKoch(3, 10.0, -5.0, 0.0, &miTortuga);
        miFractal = dibujaKoch;
      }
    } 

    /* create main window */
    hWnd = CreateWindow (
      "graficos", 
      "Ejemplo de gr'aficos (fractales y gr'aficas de funciones) con OpenGL", 
      WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
      0, 0, 2*256, 2*256,
      NULL, NULL, hInstance, NULL);

    /* enable OpenGL for the window */
    EnableOpenGL (hWnd, &hDC, &hRC);

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */

            glClearColor (1.0f, 1.0f, 1.0f, 0.5f);
            glClear (GL_COLOR_BUFFER_BIT);

            glPushMatrix ();
            glRotatef (theta, 0.0f, 0.0f, 1.0f);
            glColor3d(0.0, 0.0, 0.0);

            if(fractales==1){
              miFractal();
            } else if (funciones == 1){
              segmento(5.0, 0.0, 0.0, 0.0);
              segmento(0.0, 5.0, 0.0, 0.0);
            }
            glPopMatrix ();

            SwapBuffers (hDC);

            //theta += 1.0f;
            Sleep (1);
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL (hWnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow (hWnd);

    return msg.wParam;
}


/********************
 * Window Procedure
 *
 ********************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        PostQuitMessage (0);
        return 0;

    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            return 0;
        }
        return 0;

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}


/*******************
 * Enable OpenGL
 *
 *******************/

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );

}


/******************
 * Disable OpenGL
 *
 ******************/

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}

void segmento(double x1, double y1, double x2, double y2)
{
  glBegin (GL_LINES);
    glVertex2d (MX+escX*x1, MY+escY*y1);
    glVertex2d (MX+escX*x2, MY+escY*y2);
  glEnd ();
}

