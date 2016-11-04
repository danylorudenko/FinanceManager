#ifndef __MANAGER__
#define __MANAGER__

class Manager
{
public:
	static Manager& Instance();

private:
	static Manager* instance;
	Manager();
	~Manager();
};

#endif