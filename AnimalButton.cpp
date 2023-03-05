#include "AnimalButton.h"
#include "Animal.h"

AnimalButton::AnimalButton(QWidget *parent, shared_ptr<Animal>animal)
	: QPushButton(parent)
	, ui(new Ui::AnimalButtonClass())
{
	ui->setupUi(this);


	int animalSize = 0;
	if (animal->GetAge() == Age::Child) {
		animalSize = CHILD_SIZE;
	}
	else if (animal->GetAge() == Age::Adult) {
		animalSize = ADULT_SIZE;
	}



	//setGeometry(animal->GetPosition().GetX(), animal->GetPosition().GetY(), , 500);
	//setStyleSheet("QPushButton{background-image:" + animal->GetPicturePath() + ";}");
	
	if (animal != NULL)
		setStyleSheet("QWidget{image:url(" + animal->GetPicturePath() +  ");border:dashed; }");

}

AnimalButton::~AnimalButton()
{
	delete ui;
}
