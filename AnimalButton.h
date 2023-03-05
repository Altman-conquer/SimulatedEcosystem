#pragma once

#include <QPushButton>
#include "ui_AnimalButton.h"
#include "Animal.h"
#include <memory>


QT_BEGIN_NAMESPACE
namespace Ui { class AnimalButtonClass; };
QT_END_NAMESPACE 

using std::shared_ptr;

class AnimalButton : public QPushButton
{
	Q_OBJECT

public:
	AnimalButton(QWidget *parent = NULL, shared_ptr<Animal> animal = shared_ptr<Animal>(nullptr));
	~AnimalButton();

private:
	Ui::AnimalButtonClass *ui;
};
