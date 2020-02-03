#pragma once
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <string>

#include "Constants.h"


namespace DXR
{
	class DXRApp
	{
	public:
		virtual ~DXRApp() {}
		virtual void OnLoad(HWND winHandle, uint32t wiWidth, uint32t winHeight) = 0;
		virtual void OnFrameRender() = 0;
		virtual void OnShutDown() = 0;
	};

	class Framework
	{
	public:
		static void Run(DXRApp& applicaton, const std::string& winTitle, uint32t width = 1920, uint32t height = 1200);
	};


}

