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
#include "AVLTree.h"


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


    void delete_Animal(int id);
    void add_NewAnimal(shared_ptr<Animal> animal);
    void move_Animal(shared_ptr<Animal> animal);

    void reGame();
    void curveFigure();
private:
    Ui::SimulatedEcosystemClass ui;
    AnimalButton* temp = new AnimalButton(this);
    int move_of_sidebar = 0;
    MyChart* chart;
    QVector<QList<QPointF>> pointlist;
    QTimer* timer = new QTimer(this);
	AVLTree<int, AnimalButton*> my_animals;
    AVLTree<Species, int> test_species;
    shared_ptr<Environment> environment;
    int time = 0;
};
