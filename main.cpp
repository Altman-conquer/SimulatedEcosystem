#include "SimulatedEcosystem.h"
#include <QtWidgets/QApplication>
#include "Log.h"
#include "Vector2D.h"
#include <iostream>
#include <string>
#include "Environment.h"
#include "Grass.h"
#include <memory>
#include <thread>
#include <chrono>
#include <QuadTree.h>
#include "Animal.h"
/*
* 
在构造函数里面，参数名使用一个下划线开头，例如_n，这样可以避免出现n=n的错误
一律使用shared_ptf,禁止使用C++原生指针，避免内存错误
调试的代码写在DEBUG里面，正式的代码写在else里面，看main函数里面的宏定义
禁止使用std::cout，一律使用LogMessage来输出，并且要标注好输出的等级
函数名使用大写开头，例如GetNumber();
变量名使用小写开头，下划线连接，例如number_hello;
*/

#define DEBUG

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimulatedEcosystem w;
    w.show();


 
#ifdef DEBUG
    /*
    Log::LogMessage("HelloWorld", LogLevel::Info);
	Log::LogMessage("HelloWorld", LogLevel::Warning);
	Log::LogMessage("HelloWorld", LogLevel::Error);
    std::shared_ptr<Grass> it = std::dynamic_pointer_cast<Grass>(*environment.GetEnvironment()->begin());*/
    
	AVLTree<Species, int> test_species;
	test_species[Species::Grass] = 100;

    //test_species[Species::Cow] = 100;
    Environment environment(test_species);


    QuadTree<shared_ptr<Animal>> q(environment.GetEnvironment());

    for (auto& animal : *environment.GetEnvironment())
    {
        vector<shared_ptr<Animal>> coll = q.GetCollision(animal);
    }

    
    /*PRINT_FUNCTION_NAME(LogLevel::Error)
    Log::LogMessage(GET_FUNCTION_NAME, LogLevel::Warning);*/
    
    for (int i = 0; i < 5; i++)
    {
        environment.Update();
    }

#else

#endif


    return a.exec();
}
