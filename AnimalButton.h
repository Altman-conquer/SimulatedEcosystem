#pragma once

#include <QPushButton>
#include "ui_AnimalButton.h"
#include "Animal.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AnimalButtonClass; };
QT_END_NAMESPACE

class AnimalButton : public QPushButton
{
	Q_OBJECT

public:
	AnimalButton(QWidget *parent = nullptr, Animal animal = Animal);
	~AnimalButton();

private:
	Ui::AnimalButtonClass *ui;
};
