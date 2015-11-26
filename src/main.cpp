#include "Window.h"

int main(int argc, char * arg[])
{
	bool run = true;

	createWindow();

	while (run)
	{
		if (!windowLoop())
		{
			run = false;
		}
	}

	destroyWindow();

    return 0;
}
vector <IkeyboardListener*> keyboardListeners;