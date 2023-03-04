#include "SimulatedEcosystem.h"

SimulatedEcosystem::SimulatedEcosystem(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    temp->setParent(this);
    temp->show();
    move_of_window = 0;
    connect(ui.unfold, &QPushButton::clicked, this, &SimulatedEcosystem::dealUnfold);
}

SimulatedEcosystem::~SimulatedEcosystem()
{


}

void SimulatedEcosystem::resizeEvent(QResizeEvent* event) {
    int w = width();
    int h = height();

    ui.stackedWidget->setGeometry(w - 20 -  move_of_window, 0, 200, 500);
}

void SimulatedEcosystem::dealUnfold() {
    if (move_of_window == 0) {
        move_of_window = 200;
        ui.stackedWidget->setGeometry(width() - 20 - move_of_window, 0, 200, 500);
        ui.unfold->setText(">");
    }
    else {
        move_of_window = 0;
        ui.stackedWidget->setGeometry(width() - 20 - move_of_window, 0, 200, 500);
        ui.unfold->setText("<");
    }
}