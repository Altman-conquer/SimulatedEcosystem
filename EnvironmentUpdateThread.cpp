#include "EnvironmentUpdateThread.h"

EnvironmentUpdateThread::EnvironmentUpdateThread(shared_ptr<Environment>& _environment, QObject* parent /*= nullptr*/):
	environment(_environment)
{

}

void EnvironmentUpdateThread::Update()
{
	run();
}

void EnvironmentUpdateThread::run()
{
	environment->Update();
	
	emit UpdateFinish();
}
