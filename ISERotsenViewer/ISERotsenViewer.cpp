/*-----------------------------------------------------------------------

PROGRAM: rotsenviewer.cpp

PURPOSE:
    Open Layers data acquisition example, shows: continuos ADC operation.
	ISE rotation sensor viewer
        
FUNCTIONS:

    WinMain()        gets handle to ADC subsystem, configures ADC for
                     continuous operation, opens a dialog box to receive
                     window messages, and performs continuous operation
                     on the ADC.

    GetDriver()      callback to get board name and open board, opens
                     the first available Open Layers board.

    OutputBox()      dialog box to handle information and error window
                     messages from the ADC subsystem.

	CHECKERROR()	 error handling

	CLOSEONERROR()	 error handling

Author: Li Li
E-Mail: lili@eit.uni-kl.de
Date: 01.03.2012

Changelog:
(1) rewrite error handling functions CHECKERROR(), CLOSEONERROR()
(2) use ANSI instead of Unicode functions explicitly:
SetWindowTextA, SetDlgItemTextA, MessageBoxA, DialogBoxA

****************************************************************************/


// ISERotsenViewer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "ISERotsenViewer.h"
using namespace std;

//#define MAX_LOADSTRING 100
//
//// Global Variables:
//HINSTANCE hInst;								// current instance
//TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
//TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
//
//// Forward declarations of functions included in this code module:
//ATOM				MyRegisterClass(HINSTANCE hInstance);
//BOOL				InitInstance(HINSTANCE, int);
//LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
//
//int APIENTRY _tWinMain(HINSTANCE hInstance,
//                     HINSTANCE hPrevInstance,
//                     LPTSTR    lpCmdLine,
//                     int       nCmdShow)
//{
//	UNREFERENCED_PARAMETER(hPrevInstance);
//	UNREFERENCED_PARAMETER(lpCmdLine);
//
// 	// TODO: Place code here.
//	MSG msg;
//	HACCEL hAccelTable;
//
//	// Initialize global strings
//	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
//	LoadString(hInstance, IDC_ROTSENVIEWER, szWindowClass, MAX_LOADSTRING);
//	MyRegisterClass(hInstance);
//
//	// Perform application initialization:
//	if (!InitInstance (hInstance, nCmdShow))
//	{
//		return FALSE;
//	}
//
//	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ROTSENVIEWER));
//
//	// Main message loop:
//	while (GetMessage(&msg, NULL, 0, 0))
//	{
//		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
//		{
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//	}
//
//	return (int) msg.wParam;
//}
//
//
//
////
////  FUNCTION: MyRegisterClass()
////
////  PURPOSE: Registers the window class.
////
////  COMMENTS:
////
////    This function and its usage are only necessary if you want this code
////    to be compatible with Win32 systems prior to the 'RegisterClassEx'
////    function that was added to Windows 95. It is important to call this function
////    so that the application will get 'well formed' small icons associated
////    with it.
////
//ATOM MyRegisterClass(HINSTANCE hInstance)
//{
//	WNDCLASSEX wcex;
//
//	wcex.cbSize = sizeof(WNDCLASSEX);
//
//	wcex.style			= CS_HREDRAW | CS_VREDRAW;
//	wcex.lpfnWndProc	= WndProc;
//	wcex.cbClsExtra		= 0;
//	wcex.cbWndExtra		= 0;
//	wcex.hInstance		= hInstance;
//	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ROTSENVIEWER));
//	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
//	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
//	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_ROTSENVIEWER);
//	wcex.lpszClassName	= szWindowClass;
//	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
//
//	return RegisterClassEx(&wcex);
//}
//
////
////   FUNCTION: InitInstance(HINSTANCE, int)
////
////   PURPOSE: Saves instance handle and creates main window
////
////   COMMENTS:
////
////        In this function, we save the instance handle in a global variable and
////        create and display the main program window.
////
//BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
//{
//   HWND hWnd;
//
//   hInst = hInstance; // Store instance handle in our global variable
//
//   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
//      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
//
//   if (!hWnd)
//   {
//      return FALSE;
//   }
//
//   ShowWindow(hWnd, nCmdShow);
//   UpdateWindow(hWnd);
//
//   return TRUE;
//}
//
////
////  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
////
////  PURPOSE:  Processes messages for the main window.
////
////  WM_COMMAND	- process the application menu
////  WM_PAINT	- Paint the main window
////  WM_DESTROY	- post a quit message and return
////
////
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	int wmId, wmEvent;
//	PAINTSTRUCT ps;
//	HDC hdc;
//
//	switch (message)
//	{
//	case WM_COMMAND:
//		wmId    = LOWORD(wParam);
//		wmEvent = HIWORD(wParam);
//		// Parse the menu selections:
//		switch (wmId)
//		{
//		case IDM_ABOUT:
//			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//			break;
//		case IDM_EXIT:
//			DestroyWindow(hWnd);
//			break;
//		default:
//			return DefWindowProc(hWnd, message, wParam, lParam);
//		}
//		break;
//	case WM_PAINT:
//		hdc = BeginPaint(hWnd, &ps);
//		// TODO: Add any drawing code here...
//		EndPaint(hWnd, &ps);
//		break;
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	default:
//		return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//	return 0;
//}
//
//// Message handler for about box.
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	UNREFERENCED_PARAMETER(lParam);
//	switch (message)
//	{
//	case WM_INITDIALOG:
//		return (INT_PTR)TRUE;
//
//	case WM_COMMAND:
//		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//		{
//			EndDialog(hDlg, LOWORD(wParam));
//			return (INT_PTR)TRUE;
//		}
//		break;
//	}
//	return (INT_PTR)FALSE;
//}



/**************************************************/
/*           modified C sample code               */
/**************************************************/
//
//
//// Global Variables:
//HINSTANCE hInst;								// current instance
//TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
//TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name


#define NUM_BUFFERS 4
#define STRLEN 80        /* string size for general text manipulation   */
char str[STRLEN];        /* global string for general text manipulation */


/* Error handling macros */
//#define SHOW_ERROR(ecode) MessageBox(HWND_DESKTOP,olDaGetErrorString(ecode,\
//                  str,STRLEN),"Error", MB_ICONEXCLAMATION | MB_OK);
//
//#define CHECKERROR(ecode) if ((board.status = (ecode)) != OLNOERROR)\
//                  {\
//                  SHOW_ERROR(board.status);\
//                  olDaReleaseDASS(board.hdass);\
//                  olDaTerminate(board.hdrvr);\
//                  return ((UINT)NULL);}
//
//#define CLOSEONERROR(ecode) if ((board.status = (ecode)) != OLNOERROR)\
//                  {\
//                  SHOW_ERROR(board.status);\
//                  olDaReleaseDASS(board.hdass);\
//                  olDaTerminate(board.hdrvr);\
//                  EndDialog(hDlg, TRUE);\
//                  return (TRUE);}


/* simple structure used with board */
typedef struct tag_board {
   HDEV  hdrvr;        /* device handle            */
   HDASS hdass;        /* sub system handle        */
   ECODE status;       /* board error status       */
   char name[MAX_BOARD_NAME_LENGTH];  /* string for board name    */
   char entry[MAX_BOARD_NAME_LENGTH]; /* string for board name    */
} BOARD;

typedef BOARD* LPBOARD;

static BOARD board;
static ULNG count = 0;

// File for data storage
fstream file;

/* Error handling functions */
void SHOW_ERROR(ECODE eCode) 
{	
	MessageBox(HWND_DESKTOP,(LPCWSTR)olDaGetErrorString(eCode, (PTSTR)str, STRLEN), (LPCWSTR)"Error", MB_ICONEXCLAMATION | MB_OK);
}

UINT CHECKERROR(ECODE eCode) 
{	
	if ((board.status = (eCode)) != OLNOERROR)
    {
		SHOW_ERROR(board.status);
		olDaReleaseDASS(board.hdass);
		olDaTerminate(board.hdrvr);
		return ((UINT)NULL);
	}
}

BOOL CLOSEONERROR(ECODE eCode, HWND hDlg)
{	
	if ((board.status = (eCode)) != OLNOERROR)
    {
		SHOW_ERROR(board.status);
		olDaReleaseDASS(board.hdass);
		olDaTerminate(board.hdrvr);
		EndDialog(hDlg, TRUE);
		return (TRUE);
	}
}


BOOL CALLBACK
GetDriver( LPSTR lpszName, LPSTR lpszEntry, LPARAM lParam )   
/*
this is a callback function of olDaEnumBoards, it gets the 
strings of the Open Layers board and attempts to initialize
the board.  If successful, enumeration is halted.
*/
{
   LPBOARD lpboard = (LPBOARD)(LPVOID)lParam;
   
   /* fill in board strings */

   lstrcpyn((LPWSTR)lpboard->name,(LPCWSTR)lpszName,MAX_BOARD_NAME_LENGTH-1);
   lstrcpyn((LPWSTR)lpboard->entry,(LPWSTR)lpszEntry,MAX_BOARD_NAME_LENGTH-1);

   /* try to open board */

   lpboard->status = olDaInitialize((PTSTR)lpszName,&lpboard->hdrvr);
   if   (lpboard->hdrvr != NULL)
      return FALSE;          /* false to stop enumerating */
   else                      
      return TRUE;           /* true to continue          */
}


BOOL CALLBACK
InputBox( HWND hDlg, 
          UINT message,

          WPARAM wParam, 
          LPARAM lParam )
/*
This function processes messages for "Input" dialog box
*/
{
   DBL min=0,max=0;
   DBL volts;
   ULNG value;
   ULNG samples;
   UINT encoding=0,resolution=0;
   HBUF  hBuffer = NULL;
   PDWORD  pBuffer32 = NULL;
   PWORD  pBuffer = NULL;
   char WindowTitle[128];
   char temp[128];    
   DASSINFO ssinfo;


   switch (message) {
      case WM_INITDIALOG:   /* message: initialize dialog box  */
         
         /* set the title to the board name */ 
         
         olDaGetDASSInfo(board.hdass,&ssinfo);
         itoa(ssinfo.uiElement,temp,10);
         strncpy(WindowTitle,board.name,128);
         strncat(WindowTitle," Element # ",128);
         strncat(WindowTitle,temp,128);

         //SetWindowText(hDlg,(LPCWSTR)WindowTitle);
         SetWindowTextA(hDlg,(LPCSTR)WindowTitle);

         /* set window handle and configure sub system */
         
         CLOSEONERROR (olDaSetWndHandle(board.hdass, hDlg,(UINT)NULL), hDlg);
		 //olDaSetWndHandle(board.hdass, hDlg,(UINT)NULL);

         CLOSEONERROR (olDaConfig(board.hdass), hDlg);
		 //olDaConfig(board.hdass);

         /* start sub system */

         CLOSEONERROR (olDaStart(board.hdass), hDlg);
		 //olDaStart(board.hdass);
         
		 return (TRUE);   /* Did process a message */

      case OLDA_WM_BUFFER_REUSED:   /* message: buffer reused  */
         break;

      case OLDA_WM_BUFFER_DONE:     /* message: buffer done  */

         /* get buffer off done list */

         CHECKERROR (olDaGetBuffer(board.hdass, &hBuffer));
		 //olDaGetBuffer(board.hdass, &hBuffer);
         
		 /* if there is a buffer */

         if( hBuffer )
         {

             /* get sub system information for code/volts conversion */

             CLOSEONERROR (olDaGetRange(board.hdass,&max,&min), hDlg);
			 //olDaGetRange(board.hdass,&max,&min);
             CLOSEONERROR (olDaGetEncoding(board.hdass,&encoding), hDlg);
			 //olDaGetEncoding(board.hdass,&encoding);
             CLOSEONERROR (olDaGetResolution(board.hdass,&resolution), hDlg);
			 //olDaGetResolution(board.hdass,&resolution);

            /* get max samples in input buffer */

            CLOSEONERROR (olDmGetValidSamples(hBuffer, &samples), hDlg);
			//olDmGetValidSamples(hBuffer,&samples);

            /* get pointer to the buffer */
            if (resolution > 16)
            {
            CLOSEONERROR (olDmGetBufferPtr( hBuffer,(LPVOID*)&pBuffer32), hDlg);
			//olDmGetBufferPtr(hBuffer,(LPVOID*)&pBuffer32);

            /* get last sample in buffer */
            value = pBuffer32[samples-1];
            }
            else
            {
            CLOSEONERROR (olDmGetBufferPtr( hBuffer,(LPVOID*)&pBuffer), hDlg);
            //olDmGetBufferPtr( hBuffer,(LPVOID*)&pBuffer);
			
			/* get last sample in buffer */
            value = pBuffer[samples-1];
            }
            /* put buffer back to ready list */

            CHECKERROR (olDaPutBuffer(board.hdass, hBuffer));
			//olDaPutBuffer(board.hdass, hBuffer);

            /*  convert value to volts */

            if (encoding != OL_ENC_BINARY) 
            {
               /* convert to offset binary by inverting the sign bit */
      
               value ^= 1L << (resolution-1);
               value &= (1L << resolution) - 1;     /* zero upper bits */
            }
   
            volts = ((float)max-(float)min)/(1L<<resolution)*value + (float)min;

            /* display value */
   
            sprintf(str,"%.3f Volts",volts);
            SetDlgItemTextA (hDlg, IDD_ROTSENVIEWER_DIALOG, (LPCSTR)str);

			/* write value into file */

			file << volts << endl;

         }
         return (TRUE);   /* Did process a message */
         
      case OLDA_WM_QUEUE_DONE:
      case OLDA_WM_QUEUE_STOPPED:
         /* using wrap multiple - if these message are received */
         /* acquisition has stopped.                            */
   
         EndDialog(hDlg, TRUE);
         return (TRUE);   /* Did process a message */
    
      case OLDA_WM_TRIGGER_ERROR:
         /* Process trigger error message */

         MessageBoxA(hDlg,(LPCSTR)"Trigger error: acquisition stopped",
                  (LPCSTR)"Error", MB_ICONEXCLAMATION | MB_OK);
         EndDialog(hDlg, TRUE);
         return (TRUE);   /* Did process a message */
        
      case OLDA_WM_OVERRUN_ERROR:
         /* Process underrun error message */
        
         MessageBoxA(hDlg,(LPCSTR)"Input overrun error: acquisition stopped",
                  (LPCSTR)"Error", MB_ICONEXCLAMATION | MB_OK);
         EndDialog(hDlg, TRUE);   /* Did process a message */
         return (TRUE);   /* Did process a message */
 
      case WM_COMMAND:      /* message: received a command */

         switch ( LOWORD(wParam) )  {
            case IDOK:
            case IDCANCEL:
               CLOSEONERROR (olDaAbort(board.hdass), hDlg);
               EndDialog(hDlg, TRUE);
               return (TRUE);   /* Did process a message */
         }
         break;   
    }                               
    return (FALSE);               /* Didn't process a message */
}
   

/* MAIN PROGRAMM - ENTRY POINT */
int WINAPI 
WinMain( HINSTANCE hInstance, 
         HINSTANCE hPrevInstance, 
         LPSTR lpCmdLine, 
         int nCmdShow )
/*++
This is our apps entry point.  It calls the open layers functions
to execute the required operation.
--*/
{
   DBL  freq;
   UINT size,dma,gainsup,samplesize;
   int i;

   UINT channel = 0;
   UINT numberADs = 0;
   UINT currentAD = 0;
   DBL gain = 1.0;
   HBUF  hBuffer = NULL;
   ECODE ec=OLNOERROR;

   board.hdrvr = NULL;

   const char* cFilename = "SensorData.txt";
   // Open file for writing
   file.open(cFilename, ios_base::out);

   // Get cmdline board
   if (lpCmdLine[0]!=0)
   {
		CHECKERROR( olDaInitialize((PTSTR)lpCmdLine,&board.hdrvr) );
		strcpy(board.name,lpCmdLine);
   }
   else
   {
		/* Get first available Open Layers board */
		CHECKERROR (olDaEnumBoards((DABRDPROC)GetDriver,(LPARAM)(LPBOARD)&board));
   }
   /* check for error within callback function */

   CHECKERROR (board.status);

   /* check for NULL driver handle - means no boards */

   if (board.hdrvr == NULL)
   {
      MessageBoxA(HWND_DESKTOP, (LPCSTR)" No Open Layer boards!!!", (LPCSTR)"Error",
            MB_ICONEXCLAMATION | MB_OK);
      return ((UINT)NULL);
   }

   /* get handle to first available ADC sub system */
   CHECKERROR(olDaGetDevCaps(board.hdrvr,OLDC_ADELEMENTS,&numberADs));

    while(1)    // Enumerate through all the A/D subsystems and try and select the first available one...
   {
        ec=olDaGetDASS(board.hdrvr,OLSS_AD,currentAD,&board.hdass);
        if (ec!=OLNOERROR)
        {
        // busy subsys etc...
        currentAD++;
        if (currentAD>numberADs)
        {
            MessageBoxA(HWND_DESKTOP,(LPCSTR)"No Available A/D Subsystems!",(LPCSTR)"Error",MB_ICONEXCLAMATION|MB_OK);
              return ((UINT)NULL);
        }

        }
        else
        break;

   }

   /*
      Set up the ADC - multiple wrap so we can get buffer reused
      window messages.
   */
   CHECKERROR (olDaGetSSCapsEx(board.hdass,OLSSCE_MAXTHROUGHPUT,&freq));

   CHECKERROR (olDaGetSSCaps(board.hdass,OLSSC_NUMDMACHANS,&dma));
   CHECKERROR (olDaGetSSCaps(board.hdass,OLSSC_SUP_PROGRAMGAIN,&gainsup));
   
   dma  = min (1, dma);            /* try for one dma channel   */ 
   freq = min (1000.0, freq);      /* try for 1000hz throughput */

   CHECKERROR (olDaSetDataFlow(board.hdass,OL_DF_CONTINUOUS));
   CHECKERROR (olDaSetWrapMode(board.hdass,OL_WRP_MULTIPLE));
   CHECKERROR (olDaSetClockFrequency(board.hdass,freq));
   CHECKERROR (olDaSetDmaUsage(board.hdass,dma));
   CHECKERROR (olDaSetChannelListEntry(board.hdass,0,channel));

   /* only set the gain if the board supports it!!! */

   if (gainsup)
      CHECKERROR (olDaSetGainListEntry(board.hdass,0,gain));

   CHECKERROR (olDaSetChannelListSize(board.hdass,1));
   CHECKERROR (olDaConfig(board.hdass));

   size = (UINT)freq/1;     /* 1 second buffer */
   
   /* allocate the input buffers */
   /* Put the buffer to the ADC  */
    
   CHECKERROR(olDaGetResolution(board.hdass,&samplesize));
   if (samplesize > 16)
   {
	   samplesize=4; //4 bytes...// e.g. 24 bits = 4 btyes
   }
   else
   {
	   samplesize=2; // e.g. 16 or 12 bits = 2 bytes
   }

   for (i=0;i<NUM_BUFFERS;i++)
   {
      CHECKERROR (olDmCallocBuffer(0,0,(ULNG) size,samplesize,&hBuffer));
      CHECKERROR (olDaPutBuffer(board.hdass, hBuffer));
   }

   /*
      use a dialog box to collect information and error
      messages from the subsystem
   */

   DialogBoxA(hInstance, (LPCSTR)INPUTBOX, HWND_DESKTOP, InputBox);

   /*
      get the input buffers from the ADC subsystem and
      free the input buffers
   */

   CHECKERROR (olDaFlushBuffers(board.hdass));
   
   for (i=0;i<NUM_BUFFERS;i++)
   {
      CHECKERROR (olDaGetBuffer(board.hdass, &hBuffer));
      CHECKERROR (olDmFreeBuffer(hBuffer));
   }
   
   /* release the subsystem and the board */

   CHECKERROR (olDaReleaseDASS(board.hdass));
   CHECKERROR (olDaTerminate(board.hdrvr));

   /* Close file */
   
   file.close();

   /* all done - return */

   return ((UINT)NULL);
}