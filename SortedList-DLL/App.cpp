#include <iostream>

#include "tests/ShortTest.h"
#include "tests/ExtendedTest.h"

int main(){
    std::cout << "Hello\n";
    testAll();
    std::cout << "Short tests done\n";
    testAllExtended();
    std::cout<<"Finished IL Tests!"<<std::endl;
	system("pause");
}