#include "SimulatedEcosystem.h"

SimulatedEcosystem::SimulatedEcosystem(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    temp->setParent(this);
    temp->show();
    move_of_sidebar = 0;

    /*map<Species, int> test_species;
    test_species[Species::Grass] = 100;
    Environment environment(test_species);*/

    
    




    connect(ui.unfold, &QPushButton::clicked, this, &SimulatedEcosystem::dealUnfold);
    pointlist.clear();
    chart = new MyChart(nullptr, QString::fromLocal8Bit("动物数量"));
    chart->show();
    initChart();
    
}

SimulatedEcosystem::~SimulatedEcosystem()
{


}

void SimulatedEcosystem::resizeEvent(QResizeEvent* event) {
    int w = width();
    int h = height();

    ui.stackedWidget->setGeometry(w - 20 - move_of_sidebar, 0, 200, 500);
    //chart->setGeometry(0, 0, 800, 600);
}

void SimulatedEcosystem::dealUnfold() {
    if (move_of_sidebar == 0) {
        move_of_sidebar = 200;
        ui.stackedWidget->setGeometry(width() - 20 - move_of_sidebar, 0, 200, 500);
        ui.unfold->setText(">");
    }
    else {
        move_of_sidebar = 0;
        ui.stackedWidget->setGeometry(width() - 20 - move_of_sidebar, 0, 200, 500);
        ui.unfold->setText("<");
    }
}

void SimulatedEcosystem::initChart()
{
    chart->setAxis(QString::fromLocal8Bit("X轴"), 0, 100, 11, QString::fromLocal8Bit("Y轴"), 0, 20, 11);

    QList<QPointF> pointlist_temp = { QPointF(0,1), QPointF(10,2), QPointF(20,4), QPointF(30,8), QPointF(40,16),
                                QPointF(50,16), QPointF(60,8), QPointF(70,4), QPointF(80,2), QPointF(90,1), };
    pointlist.append(pointlist_temp);
    //绘制
    chart->buildChart(pointlist);
    //为MainWindow的centralWidget添加一个布局
    /*QHBoxLayout* pHLayout = new QHBoxLayout(ui.centralWidget);
    //将chart添加到布局中
    pHLayout->addWidget(chart);*/
}
