/*
	X File Animation Demo

	This demo shows how to load .x files keeping their hierarchy and handling animation and skinning
	See the site notes for more details

	main.cpp - this file. Contains Window's code etc.
	CGraphics (Graphics.cpp/h) - class that wraps all the graphics functionality.
	CXFileEntity (Graphics.cpp/h) - class that represents one .x file model 
	CMeshHierarchy (MeshHierarchy.cpp/h) - class required by the D3DXLoadMeshHierarchyFromX function to
	handle the allocation and deallocation of frames and mesh
	CCamera (Camera.cpp./h) - class that implements a first person camera
	CUtility (Utility.cpp/h) - a set of useful functions

	Keith Ditchburn, January 2008
*/

#include <windows.h>
#include "Graphics.h"
#include "Camera.h"
#include "Utility.h"

// The global graphics instance
CGraphics *gGraphics=0;

// Function prototypes
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
bool SetupDirect3D(HWND hWnd);
void LoadFile(HWND hWnd);

// Constants
const int kViewPortWidth=800;
const int kViewPortHeight=600;

const float kCameraMovementSpeed=0.05f;
const float kCameraRotationSpeed=0.01f;

/*	Main entry point of the program
	Create a window, setup the graphics and enter the message loop
*/ 
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Create and register a window class (type) for our main window
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style= 0;//CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc= (WNDPROC)WndProc;
	wcex.cbClsExtra= 0;
	wcex.cbWndExtra= 0;
	wcex.hInstance= hInstance;
	wcex.hIcon= 0;
	wcex.hCursor= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName= 0;
	wcex.lpszClassName= "MainWindowClass";
	wcex.hIconSm= 0;
		
	RegisterClassEx(&wcex);

    // adjust the window size so the actual client area is the requested viewport size
	// i.e. so the size does not include the borders and other adornments
	RECT rc;
	SetRect( &rc, 0, 0, kViewPortWidth,kViewPortHeight );  
	AdjustWindowRectEx( &rc, WS_OVERLAPPEDWINDOW,false,0);  

	// Create the main window
	HWND hWnd = CreateWindow("MainWindowClass", "X File Animation Demo, Keith Ditchburn 2008", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right-rc.left, rc.bottom-rc.top, NULL, NULL, hInstance, NULL);
	if (hWnd==0)
		return 0;

	// Create an instance of our graphics class
	gGraphics=new CGraphics();
	if (!gGraphics->Initialise(hWnd))
	{
		delete gGraphics;
		return 0;
	}

	// Load a default .x file to start with
	gGraphics->LoadXFile(CUtility::GetTheCurrentDirectory()+"/data/bones_all.x",1);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// The message loop. Whenever there is no message to be processed we update our graphics
	MSG msg;
	ZeroMemory( &msg, sizeof(msg) );
	while( msg.message!=WM_QUIT )
	{
	   if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
	   {
		  TranslateMessage( &msg );
		  DispatchMessage( &msg );
	   }
	   else
	   {
		   gGraphics->Update();
	   }  
	}

	// Clean up and exit
	delete gGraphics;
	return (int)msg.wParam;
}

/*
	Window callback function
	Receives messages sent to the main window
	Here I trap key presses to control camera and entity movement
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
	case WM_KEYDOWN:
		switch(wParam)
		{			
			// Camera Translations
			case 'W':
			case VK_UP:
				gGraphics->GetCamera()->MoveForward(kCameraMovementSpeed);
			break;
			case 'S':
			case VK_DOWN:
				gGraphics->GetCamera()->MoveForward(-kCameraMovementSpeed);
			break;
			case 'D':
			case VK_RIGHT:
				gGraphics->GetCamera()->MoveRight(kCameraMovementSpeed);
			break;
			case 'A':
			case VK_LEFT:
				gGraphics->GetCamera()->MoveRight(-kCameraMovementSpeed);
			break;
			case VK_HOME:
				gGraphics->GetCamera()->MoveUp(kCameraMovementSpeed);
			break;
			case VK_END:
				gGraphics->GetCamera()->MoveUp(-kCameraMovementSpeed);
			break;

			// Entity Translations / Rotations
			case VK_NUMPAD4: 
				gGraphics->YawEntity(-kCameraRotationSpeed);
			break;
			case VK_NUMPAD6:				
				gGraphics->YawEntity(kCameraRotationSpeed);
			break;
			case VK_NUMPAD8:
				gGraphics->PitchEntity(-kCameraRotationSpeed);
			break;
			case VK_NUMPAD2:
				gGraphics->PitchEntity(kCameraRotationSpeed);
			break;
			case VK_NUMPAD7:
				gGraphics->RollEntity(-kCameraRotationSpeed);
			break;
			case VK_NUMPAD9:
				gGraphics->RollEntity(kCameraRotationSpeed);
			break;

			// Animation Controls			
			case VK_SPACE:
				gGraphics->NextAnimation();
			break;
			case VK_ADD:
				gGraphics->AnimateFaster();
			break;
			case VK_SUBTRACT:
				gGraphics->AnimateSlower();
			break;

			// Other keys
			case 'L':
				LoadFile(hWnd);
			break;
			case VK_F1:
				gGraphics->ToggleControlsDisplay();
			break;

			default:
				break;
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

/*
	Puts up a Window's open dialog box for the user to choose a file to load
	Then calls the graphics to load the file
*/
void LoadFile(HWND hWnd)
{
	// Return buffer
    static char filename[4096];

    OPENFILENAME ofn;
    memset( &ofn, 0, sizeof(ofn) );

    ofn.lStructSize       = sizeof(ofn);
    ofn.hwndOwner         = hWnd;
    ofn.hInstance         = 0;
	ofn.lpstrFilter		  = "X Files (*.x)\0*.x\0All Files (*.*)\0*.*\0\0";
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter    = 0L;
    ofn.nFilterIndex      = 0L;
    ofn.lpstrFile         = filename;
    ofn.nMaxFile          = sizeof(filename);
    ofn.lpstrFileTitle    = 0;
    ofn.nMaxFileTitle     = 0;
	ofn.lpstrInitialDir   = 0;
    ofn.nFileOffset       = 0;
    ofn.nFileExtension    = 0;
    ofn.lpstrDefExt       = "*.x";
    ofn.lCustData         = 0;
	ofn.lpstrTitle		  = "Select a .X file to open";
    ofn.Flags			  = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR | OFN_OVERWRITEPROMPT;

	if (GetOpenFileName(&ofn))
		gGraphics->LoadXFile(filename);
}