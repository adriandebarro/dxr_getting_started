#include "DXRApp.h"

#include "Tutorial1.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	Sample2 sample_app;
	DXR::Framework::Run(sample_app, "This is a test application");
}


