#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main(){
    srand(time(0));
    for (int i = 0; i < 2; i++){
        cout << 20 * (2 * float(rand()) / RAND_MAX  - 1) << " " << 20 * (2 * float(rand()) / RAND_MAX  - 1) << " " << 20 * (2 * float(rand()) / RAND_MAX  - 1) << endl;
    }
}