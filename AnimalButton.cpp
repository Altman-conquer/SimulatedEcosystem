#include "AnimalButton.h"

AnimalButton::AnimalButton(QWidget *parent, shared_ptr<Animal>animal)
	: QPushButton(parent)
	, ui(new Ui::AnimalButtonClass())
{
	ui->setupUi(this);
	setGeometry(0.1, 0.1, 500, 500);
	//setStyleSheet("QPushButton{background-image:" + animal->GetPicturePath() + ";}");
	this->setStyleSheet("QWidget{image:url(:/sourcePicture/wolf.png);border:dashed;}");
}

AnimalButton::~AnimalButton()
{
	delete ui;
}
