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
    void DealUnfold();
    
    void InitChart();
    void UpdateSurface();


    void DeleteAnimal(int id);
    void AddNewAnimal(shared_ptr<Animal> animal);
    void MoveAnimal(shared_ptr<Animal> animal);

    void ReGame();
    void CurveFigure();
    void StartButton();
	void StopButton();

    void AddButton_1();
	void AddButton_2();
	void AddButton_3();
	void AddButton_4();
	void AddButton_5();


private:
    Ui::SimulatedEcosystemClass ui;
    

	MyChart* chart;

    AnimalButton* temp = new AnimalButton(this);
	QVector<QList<QPointF>> pointlist;
    shared_ptr<vector<shared_ptr<Animal>>> animals;

    QTimer* timer = new QTimer(this);

	map<int, AnimalButton*> my_animals;
    AVLTree<Species, int> test_species;
    shared_ptr<Environment> environment;
    
    long long time = 0;
	int FPS = 1;
    int move_of_sidebar = 0;
    bool is_updating = false;
};
