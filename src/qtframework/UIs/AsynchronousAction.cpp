#include "AsynchronousAction.h"


AsynchronousAction::AsynchronousAction():_pParam(NULL)
{
}

AsynchronousAction::AsynchronousAction(void* pParam):_pParam(pParam)
{
	
}


AsynchronousAction::~AsynchronousAction()
{
}

void AsynchronousAction::run()
{
	int i = *((int*)_pParam);
	sleep(i);
}
