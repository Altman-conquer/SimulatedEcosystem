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
	AnimalButton(QWidget *parent, shared_ptr<Animal> animal);
	~AnimalButton();

private:
	Ui::AnimalButtonClass *ui;
};
