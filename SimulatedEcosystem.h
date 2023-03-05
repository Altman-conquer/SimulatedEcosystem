#pragma once
#include <QtCharts>
#include <qchar.h>
#include <QtWidgets/QMainWindow>
#include "ui_SimulatedEcosystem.h"
#include "AnimalButton.h"
#include <memory>
#include <qchartview.h>
#include"MyChart.h"
#include <QTimer>

using std::map;
using std::shared_ptr;

class SimulatedEcosystem : public QMainWindow
{
    Q_OBJECT
public:
    SimulatedEcosystem(QWidget *parent = nullptr);
    ~SimulatedEcosystem();
    //deal the size of window
    void resizeEvent(QResizeEvent* event);

    //deal sidebar unfold
    void dealUnfold();
    
    void initChart();
    void update_Surface();
private:
    Ui::SimulatedEcosystemClass ui;
    AnimalButton* temp = new AnimalButton(this);
    int move_of_sidebar = 0;
    MyChart* chart;
    QVector<QList<QPointF>> pointlist;
    QTimer* timer = new QTimer(this);
	map<Species, int> test_species;

    shared_ptr<Environment> environment;
};
