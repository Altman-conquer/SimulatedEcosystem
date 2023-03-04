#include "AnimalButton.h"

AnimalButton::AnimalButton(QWidget *parent, shared_ptr<Animal>animal)
	: QPushButton(parent)
	, ui(new Ui::AnimalButtonClass())
{
	ui->setupUi(this);
	



}

AnimalButton::~AnimalButton()
{
	delete ui;
}
