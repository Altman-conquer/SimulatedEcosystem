#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SimulatedEcosystem.h"

class SimulatedEcosystem : public QMainWindow
{
    Q_OBJECT

public:
    SimulatedEcosystem(QWidget *parent = nullptr);
    ~SimulatedEcosystem();

private:
    Ui::SimulatedEcosystemClass ui;
};
