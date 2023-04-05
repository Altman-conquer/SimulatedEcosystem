#pragma once
#include "QThread"
#include "Environment.h"

class EnvironmentUpdateThread : public QThread
{
	Q_OBJECT

public:
	//************************************
	// Parameter: shared_ptr<Environment> & _environment - The current environment pointer.
	// Parameter: QObject * parent - Parent object to be attached to, default to be nullptr
	//************************************
	explicit EnvironmentUpdateThread(shared_ptr<Environment>& _environment, QObject* parent = nullptr);

	// Update the environment by 1 tick.
	// Don't modify the environment until signal UpdateFinish is sent.
	void Update();
	
signals:
	
	void UpdateFinish();
	
protected:
	void run() override;

private:
	shared_ptr<Environment> environment;
};
