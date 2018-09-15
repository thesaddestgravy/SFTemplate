#include "Application.h"

#ifdef _DEBUG
	
#else
	#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main()
{
	Application app;
	app.run(1700, 900);
	return 0;
}