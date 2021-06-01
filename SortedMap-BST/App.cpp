#include "tests/ExtendedTest.h"
#include "tests/ShortTest.h"

#include "SortedMap.h"


#include <iostream>
using namespace std;

void init_array(int array[]){
    for(int i = 0; i < 3; ++i){
        array[i] = -1;
    }
}

int main() {
	testAll();
	testAllExtended();

	cout << "That's all!" << endl;
	system("pause");
	return 0;
}


