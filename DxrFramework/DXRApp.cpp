#include <string>
#include <locale>
#include <codecvt>
#include "DXRApp.h"


HWND gWinHandle = nullptr;

void ShowMessageBox(const std::string &msg)
{
	MessageBoxA(gWinHandle, msg.c_str(), "Error", MB_OK);
}

static LRESULT CALLBACK msgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		if(wParam == VK_ESCAPE)
			PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

void MessagePump(DXR::SimpleDXRApp &application)
{
	MSG msg;
	while(1)
	{
		if(PeekMessage(&msg, nullptr, 0,0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);	
		}
		else
		{
			application.OnFrameRender();
		}
	}
}

std::wstring string_2_wstring(const std::string& s)
{
    std::wstring_convert<std::codecvt_utf8<WCHAR>> cvt;
    std::wstring ws = cvt.from_bytes(s);
    return ws;
}

std::string wstring_2_string(const std::wstring& ws)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> cvt;
    std::string s = cvt.to_bytes(ws);
    return s;
}

HWND CreateDXRWindow(const std::string &winTitle, ui32t &width, ui32t &height)
{
	const WCHAR* className = L"DxrWindowClass";
	DWORD winStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

	WNDCLASS wc = {};
	wc.lpfnWndProc = msgProc;
	wc.hInstance = GetModuleHandle(nullptr);
	wc.lpszClassName  = className;

	if(RegisterClass(&wc) == 0)
	{
		ShowMessageBox("Registration of window class failed!");
		return nullptr;
	}

	RECT r {0, 0, (LONG) width, (LONG) height};
	AdjustWindowRect(&r, winStyle, false);
	int windowWidth = r.right - r.left;
	int windowHeight = r.bottom - r.top;


	std::wstring wTitle = string_2_wstring(winTitle);
	HWND hWnd = CreateWindowEx(0, className, wTitle.c_str(), winStyle, CW_USEDEFAULT, CW_USEDEFAULT, windowWidth, windowHeight, nullptr, nullptr, wc.hInstance, nullptr);

	if(hWnd == nullptr)
	{
		ShowMessageBox("Failed to create window!");
		return nullptr;
	}

	return hWnd;
}


/*
	The swapchain taked care of switching the buffer pointers to update the image on the screen. 
	This is done when the VSYNC signal is sent from the monitor. If the swapping takes place while the screen is not fully loaded\
	it may result in tearing as the buffer was updated while the buffer was still being utilised.

	What to do? use double buffer or triple buffering techniques which can be used in DirectX using the //swap chain//
*/

DXR::IDXGISwapChain3Ptr CreateDxgiSwapChain(DXR::IDXGIFactory4Ptr pFactory, HWND hwnd, ui32t width, ui32t height, DXGI_FORMAT format, DXR::ID3D12CommandQueuePtr pCommandQueue)
{
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	swapChainDesc.BufferCount = DXR::kDefaultSwapChainBuffers;
	swapChainDesc.Width = width;
	swapChainDesc.Height = height;
	swapChainDesc.Format = format;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.SampleDesc.Count = 1;

	// TODO check why the smart com ptr statment
	MAKE_SMART_COM_PTR(IDXGISwapChain1);

}




void DXR::Framework::Run(DXR::SimpleDXRApp& application, const std::string& winTitle, ui32t width , ui32t height)
{
	gWinHandle = CreateDXRWindow(winTitle, width, height);
	RECT r;

	GetClientRect(gWinHandle, &r);
	int actual_width = r.right - r.left;
	int actual_height = r.bottom - r.top;
	
	application.OnLoad(gWinHandle, width, height);

	ShowWindow(gWinHandle, SW_SHOWNORMAL);

	MessagePump(application);

	application.OnShutDown();
	DestroyWindow(gWinHandle);
}

void DXR::DXRApp::InitDXR(HWND winHandle, ui32t winWidth, ui32t winHeight)
{
	// TODO Add implementation
}


ui32t DXR::DXRApp::BeginFrame()
{
	// TODO Add implementation
}

void DXR::DXRApp::EndFrame(ui32t rtvIndex)
{
	// TODO Add implementation
}

