#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "..\Include\Managers\GlobalManager.h"

class Application
{
public:
	bool Iterate();

	Application();
	~Application();

private:
	void Initialize();
	void Terminate();

private:
	GlobalManager* manager;
};

#endif