#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SimulatedEcosystem.h"
#include "AnimalButton.h"
#include <memory>

using std::shared_ptr;

class SimulatedEcosystem : public QMainWindow
{
    Q_OBJECT

public:
    SimulatedEcosystem(QWidget *parent = nullptr);
    ~SimulatedEcosystem();

    void resizeEvent(QResizeEvent* event);//deal the size of window
    void dealUnfold();//deal sidebar unfold


private:
    Ui::SimulatedEcosystemClass ui;
    AnimalButton* temp = new AnimalButton(this);
    int move_of_sidebar = 0;
};
