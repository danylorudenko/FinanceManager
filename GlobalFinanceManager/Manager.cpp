#include "Manager.h"

Manager* Manager::instance = nullptr;

Manager::Manager()
{

}

Manager::~Manager()
{

}

Manager& Manager::Instance()
{
	if (instance != nullptr)
	{
		return *instance;
	}
	else
	{
		instance = new Manager();
		return *instance;
	}
}
