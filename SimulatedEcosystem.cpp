#include "SimulatedEcosystem.h"

SimulatedEcosystem::SimulatedEcosystem(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    temp->setParent(this);
    temp->show();


}

SimulatedEcosystem::~SimulatedEcosystem()
{


}
