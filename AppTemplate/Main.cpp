#include "Application.h"

#ifdef _DEBUG
	
#else
	#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main()
{
	Application app;
	app.run(800, 600);
	return 0;
}