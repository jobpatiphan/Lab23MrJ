#include <windows.h>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

HWND textfield ,button1,button2,button3,button4;
HWND TextBox, TextBox2;
char textSave1[100];
char textSave2[100];
double a,b,sum;
char *textSave3[100];


/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		case WM_CREATE: {
			textfield = CreateWindow("STATIC", "Please INPUT TWO Numbes", WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER, 20, 20, 200, 20, hwnd, NULL, NULL, NULL);
			TextBox = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER |SS_CENTER, 20, 50, 200, 20, hwnd, NULL, NULL, NULL);
			TextBox2 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER |SS_CENTER, 20, 80, 200, 20, hwnd, NULL, NULL, NULL);
			button1 = CreateWindow("BUTTON","+",WS_VISIBLE | WS_CHILD | WS_BORDER |SS_CENTER,20,110,30,20,hwnd,(HMENU)1,NULL,NULL);
			button2 = CreateWindow("BUTTON","-",WS_VISIBLE | WS_CHILD | WS_BORDER |SS_CENTER,73,110,30,20,hwnd,(HMENU)2,NULL,NULL);
			button3 = CreateWindow("BUTTON","*",WS_VISIBLE | WS_CHILD | WS_BORDER |SS_CENTER,130,110,30,20,hwnd,(HMENU)3,NULL,NULL);
			button4 = CreateWindow("BUTTON","/",WS_VISIBLE | WS_CHILD | WS_BORDER |SS_CENTER,190,110,30,20,hwnd,(HMENU)4,NULL,NULL);


			break;
		}

		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		case WM_COMMAND: {
			switch(LOWORD(wParam)) {
				case 1: {
					GetWindowText(TextBox, textSave1, 100);
					GetWindowText(TextBox2, textSave2, 100);
					a = atof(textSave1);
					b = atof(textSave2);
					sum = a + b;
					char t[100];
					sprintf(t, "%f", sum);
					MessageBeep(MB_ICONERROR);
					MessageBox(hwnd, t,"Result", MB_OK | MB_ICONINFORMATION);
					break;
				}
				case 2: {
					GetWindowText(TextBox, textSave1, 100);
					GetWindowText(TextBox2, textSave2, 100);
					a = atof(textSave1);
					b = atof(textSave2);
					sum = a - b;
					char t[100];
					sprintf(t, "%f", sum);
					MessageBeep(MB_ICONERROR);
					MessageBox(hwnd, t,"Result", MB_OK | MB_ICONINFORMATION);
					break;
				}
				case 3: {
					GetWindowText(TextBox, textSave1, 100);
					GetWindowText(TextBox2, textSave2, 100);
					a = atof(textSave1);
					b = atof(textSave2);
					sum = a * b;
					char t[100];
					sprintf(t, "%f", sum);
					MessageBeep(MB_ICONERROR);
					MessageBox(hwnd, t,"Result", MB_OK | MB_ICONINFORMATION);
					break;
				}
				case 4: {
					GetWindowText(TextBox, textSave1, 100);
					GetWindowText(TextBox2, textSave2, 100);
					a = atof(textSave1);
					b = atof(textSave2);
					sum = a / b;
					char t[100];
					sprintf(t, "%f", sum);
					MessageBeep(MB_ICONERROR);
					MessageBox(hwnd, t,"Result", MB_OK | MB_ICONINFORMATION);
					break;
				}
			}
			break;
		}
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}


/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = CreateSolidBrush(RGB(65, 211, 216));
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
