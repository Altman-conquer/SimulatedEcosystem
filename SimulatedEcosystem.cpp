#include "SimulatedEcosystem.h"
#include "Animal.h"

SimulatedEcosystem::SimulatedEcosystem(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    temp->setParent(this);
    temp->show();
    move_of_sidebar = 0;
    ui.scrollAreaWidgetContents->setFixedHeight(800);
    ui.scrollAreaWidgetContents->setFixedWidth(600);

        
    connect(timer, &QTimer::timeout, this, &SimulatedEcosystem::update_Surface);


    map<Species, int> test_species;
    test_species[Species::Grass] = 1000;
	test_species[Species::Cow] = 100;
    environment = std::make_shared<Environment>(test_species);
    
    shared_ptr<vector<shared_ptr<Animal>>> animals = environment->GetEnvironment();


    for (shared_ptr<Animal>& animal : *animals) {
        AnimalButton* temp = new AnimalButton(ui.scrollAreaWidgetContents, animal);
        my_animals[animal->GetID()] = temp;
    }

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
    ui.scrollArea->setGeometry(0, 0, w - 200, h-100);

    //chart->setGeometry(0, 0, 800, 600);
}

void SimulatedEcosystem::dealUnfold() {
    if (move_of_sidebar == 0) {
        move_of_sidebar = 200 - 20;
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
    chart->setAxis(QString::fromLocal8Bit("X axis"), 0, 100, 11, QString::fromLocal8Bit("Y axis"), 0, 20, 11);

    QList<QPointF> pointlist_temp = { QPointF(0,1), QPointF(10,2), QPointF(20,4), QPointF(30,8), QPointF(40,16),
                                QPointF(50,16), QPointF(60,8), QPointF(70,4), QPointF(80,2), QPointF(90,1), };
    pointlist.append(pointlist_temp);

    chart->buildChart(pointlist);
}

void SimulatedEcosystem::update_Surface() {
    environment->Update();
	shared_ptr<vector<shared_ptr<Animal>>> animals = environment->GetEnvironment();
	vector<int>deadID = environment->GetDeadAnimals();
    for (int id : deadID) {
        AnimalButton* temp = my_animals[id];
        temp->setParent(NULL);
        delete temp;
    }
	for (shared_ptr<Animal>& animal : *animals) {
		AnimalButton* temp = my_animals[animal->GetID()];
	}
}