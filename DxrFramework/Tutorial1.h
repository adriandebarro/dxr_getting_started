#pragma once

#include "DXRApp.h"

class Sample1 : public DXR::SimpleDXRApp
{
public:
	Sample1()
	{}

	virtual void OnLoad(HWND winHandle, ui32t wiWidth, ui32t winHeight)
	{

	}
	
	virtual void OnFrameRender()
	{

	}

	virtual void OnShutDown()
	{

	}
};

class Sample2 : public DXR::DXRApp
{
public:
	Sample2()
	{

	}

	// Inherited via DXRApp
	virtual void OnLoad(HWND winHandle, ui32t wiWidth, ui32t winHeight) override 
	{

	}

	virtual void OnFrameRender() override
	{

	}

	virtual void OnShutDown() override
	{

	}
};

