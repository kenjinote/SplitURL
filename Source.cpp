#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib,"wininet")

#include <windows.h>
#include <wininet.h> 

TCHAR szClassName[] = TEXT("Window");

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit1;
	static HWND hEdit2;
	static HWND hButton;
	switch (msg)
	{
	case WM_CREATE:
		hEdit1 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("http://user:pass@hack.jp:8080/test/index.html"), WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL, 0, 0, 0, 0, hWnd, 0, ((LPCREATESTRUCT)(lParam))->hInstance, 0);
		hEdit2 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), 0, WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_READONLY | ES_AUTOVSCROLL | ES_AUTOHSCROLL, 0, 0, 0, 0, hWnd, 0, ((LPCREATESTRUCT)(lParam))->hInstance, 0);
		hButton = CreateWindow(TEXT("BUTTON"), TEXT("URLの分解"), WS_CHILD | WS_VISIBLE | WS_TABSTOP, 0, 0, 0, 0, hWnd, (HMENU)IDOK, ((LPCREATESTRUCT)(lParam))->hInstance, 0);
		break;
	case WM_SIZE:
		MoveWindow(hEdit1, 10, 10, LOWORD(lParam) - 20, 32, 1);
		MoveWindow(hButton, 10, 50, 256, 32, 1);
		MoveWindow(hEdit2, 10, 90, LOWORD(lParam) - 20, HIWORD(lParam) - 100, 1);
		break;
	case WM_SETFOCUS:
		SetFocus(hEdit1);
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			DWORD dwSize = GetWindowTextLength(hEdit1);
			if (dwSize)
			{
				SetWindowText(hEdit2, 0);

				LPTSTR lpURL = (LPTSTR)GlobalAlloc(0, sizeof(TCHAR)*(dwSize + 1));
				GetWindowText(hEdit1, lpURL, dwSize + 1);

				URL_COMPONENTS uc;
				TCHAR Scheme[1000];
				TCHAR HostName[1000];
				TCHAR UserName[1000];
				TCHAR Password[1000];
				TCHAR UrlPath[1000];
				TCHAR ExtraInfo[1000];

				uc.dwStructSize = sizeof(uc);
				uc.lpszScheme = Scheme;
				uc.lpszHostName = HostName;
				uc.lpszUserName = UserName;
				uc.lpszPassword = Password;
				uc.lpszUrlPath = UrlPath;
				uc.lpszExtraInfo = ExtraInfo;

				uc.dwSchemeLength = 1000;
				uc.dwHostNameLength = 1000;
				uc.dwUserNameLength = 1000;
				uc.dwPasswordLength = 1000;
				uc.dwUrlPathLength = 1000;
				uc.dwExtraInfoLength = 1000;

				InternetCrackUrl(lpURL, 0, 0, &uc);

				SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("scheme: "));
				SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)uc.lpszScheme);
				SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));

				SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("host name: "));
				SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)uc.lpszHostName);
				SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));

				SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("port: "));
				{
					TCHAR szPort[32];
					wsprintf(szPort, TEXT("%d"), uc.nPort);
					SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)szPort);
				}
				SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));

				SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("user name: "));
				SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)uc.lpszUserName);
				SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));

				SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("password: "));
				SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)uc.lpszPassword);
				SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));

				SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("url path: "));
				SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)uc.lpszUrlPath);
				SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));

				SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("extra info: "));
				SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)uc.lpszExtraInfo);
				SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));

				SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("scheme type: "));
				switch (uc.nScheme)
				{
				case INTERNET_SCHEME_PARTIAL:SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("partial\r\n")); break;
				case INTERNET_SCHEME_UNKNOWN: SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("unknown\r\n")); break;
				case INTERNET_SCHEME_DEFAULT: SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("default\r\n")); break;
				case INTERNET_SCHEME_FTP: SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("FTP\r\n")); break;
				case INTERNET_SCHEME_GOPHER: SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("GOPHER\r\n")); break;
				case INTERNET_SCHEME_HTTP: SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("HTTP\r\n")); break;
				case INTERNET_SCHEME_HTTPS: SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("HTTPS\r\n")); break;
				case INTERNET_SCHEME_FILE: SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("FILE\r\n")); break;
				case INTERNET_SCHEME_NEWS: SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("NEWS\r\n")); break;
				case INTERNET_SCHEME_MAILTO: SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("MAILTO\r\n")); break;
				default: SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("不明\r\n"));
				}
				GlobalFree(lpURL);
			}
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR pCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASS wndclass = {
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		0,
		LoadCursor(0,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		0,
		szClassName
	};
	RegisterClass(&wndclass);
	HWND hWnd = CreateWindow(
		szClassName,
		TEXT("URLの分解"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		0,
		0,
		hInstance,
		0
	);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
