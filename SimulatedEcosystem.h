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

    void resizeEvent(QResizeEvent* event);//处理窗口大小更改
    void dealUnfold();//处理侧边栏


private:
    Ui::SimulatedEcosystemClass ui;
    AnimalButton* temp = new AnimalButton(this);
    int move_of_window = 0;//侧边栏
};
