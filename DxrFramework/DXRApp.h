#pragma once
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <string>
#include <d3d12.h>
#include <comdef.h>
#include <dxgi1_4.h>
#include <dxgiformat.h>
#include <dxcapi.h>

#include "Constants.h"

namespace DXR
{
	// TODO: check why exactly we need to make use of the SMART_COM_PTR
	#define MAKE_SMART_COM_PTR(_a) _COM_SMARTPTR_TYPEDEF(_a, __uuidof(_a))
	MAKE_SMART_COM_PTR(ID3D12Device5);
	MAKE_SMART_COM_PTR(ID3D12GraphicsCommandList4);
	MAKE_SMART_COM_PTR(ID3D12CommandQueue);
	MAKE_SMART_COM_PTR(IDXGISwapChain3);
	MAKE_SMART_COM_PTR(IDXGIFactory4);
	MAKE_SMART_COM_PTR(IDXGIAdapter1);
	MAKE_SMART_COM_PTR(ID3D12Fence);
	MAKE_SMART_COM_PTR(ID3D12CommandAllocator);
	MAKE_SMART_COM_PTR(ID3D12Resource);
	MAKE_SMART_COM_PTR(ID3D12DescriptorHeap);
	MAKE_SMART_COM_PTR(ID3D12Debug);
	MAKE_SMART_COM_PTR(ID3D12StateObject);
	MAKE_SMART_COM_PTR(ID3D12RootSignature);
	MAKE_SMART_COM_PTR(ID3DBlob);
	MAKE_SMART_COM_PTR(IDxcBlobEncoding);

	static const uint32_t kDefaultSwapChainBuffers = 3;

	// simple call result status check
	#define d3d_call(a) {HRESULT hr = a; if(FAILED(hr)){ d3dTraceHR(#a, hr); }}
	// array size check
	#define arraysize(a) (sizeof(a)/sizeof(a[0]))
	// alignment setup definition	
	#define align_to(_alignement, _val) (((_val + _alignment - 1) / _alignement) * _alignment)

	class SimpleDXRApp
	{
	public:
		virtual ~SimpleDXRApp() {}
		virtual void OnLoad(HWND winHandle, ui32t wiWidth, ui32t winHeight) = 0;
		virtual void OnFrameRender() = 0;
		virtual void OnShutDown() = 0;
	};

	HWND CreateDXRWindow(const std::string& winTitle, ui32t& width, ui32t& height);
	std::string wstring_2_string(const std::wstring& ws);
	std::wstring string_2_wstring(const std::string& s);
	void MessagePump(DXR::SimpleDXRApp& application);
	static LRESULT CALLBACK msgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void ShowMessageBox(const std::string& msg);

	class Framework
	{
	public:
		static void Run(SimpleDXRApp& applicaton, const std::string& winTitle, ui32t width = 1920, ui32t height = 1200);
	};

	/*
		this code will follow the following code structure
		https://docs.microsoft.com/en-us/windows/win32/direct3d12/creating-a-basic-direct3d-12-component
	*/
	class DXRApp : public SimpleDXRApp 
	{
	public:
		DXRApp()
		{}

	private:

		void InitDXR(HWND winHandle, ui32t winWidth, ui32t winHeight);
		ui32t BeginFrame();
		void EndFrame(ui32t rtvIndex);

	private:

		HWND mHwnd = nullptr;
		ID3D12Device5Ptr mpDevice;
		ID3D12CommandQueuePtr mpCmdQueue;
		IDXGISwapChain3Ptr mpSwapChain;
		// swapChainSize
		ID3D12GraphicsCommandList4Ptr mpCommandList;
		ID3D12FencePtr mpFence;
		HANDLE mFenceEvent;
		uint64_t mFenceValue = 0;
		
		struct
		{
			ID3D12CommandAllocatorPtr pCmdAllocator;
			ID3D12ResourcePtr pSwapChainBuffer;
			D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
		} mFrameObjects[kDefaultSwapChainBuffers];

		struct HeapData
		{
			ID3D12DescriptorHeapPtr pHeap;
			ui32t usedEntires = 0;
		};

		HeapData mRtvHEap;
		static const ui32t kRtvHeapSize = 3;
	};


}

