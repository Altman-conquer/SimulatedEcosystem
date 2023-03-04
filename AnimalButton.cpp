#include "AnimalButton.h"

AnimalButton::AnimalButton(QWidget *parent)
	: QPushButton(parent)
	, ui(new Ui::AnimalButtonClass())
{
	ui->setupUi(this);
}

AnimalButton::~AnimalButton()
{
	delete ui;
}
