#include "SimulatedEcosystem.h"
#include <QtWidgets/QApplication>
#include "Log.h"
#include "Vector2D.h"
#include <iostream>

/*
在构造函数里面，参数名使用一个下划线开头，例如_n，这样可以避免出现n=n的错误
一律使用shared_ptf,禁止使用C++原生指针，避免内存错误
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimulatedEcosystem w;
    w.show();
    
    //std::cout << "hello";

	/*Log::LogMessage("HelloWorld", LogLevel::Info);
	Log::LogMessage("HelloWorld", LogLevel::Warning);
	Log::LogMessage("HelloWorld", LogLevel::Error);
    Vector2D::GetDirectionVector(Direction(5));*/

    return a.exec();
}
