#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

double randomdouble(double left, double right){
    double normalised_rand = double(rand()) / RAND_MAX;
    return left + normalised_rand * (right - left);
}


int main(){
    srand(time(0));
    int* temp = new int;
    *temp = rand();
    delete temp;
    double centre_factor = 1;
    double z_factor = 1;
    double radius_factor = 1.5;

    int numberofspheres = 3;
    cout << numberofspheres << endl;

    for (int i = 0; i < numberofspheres; i++){
        cout << centre_factor * randomdouble(-1, 1) << " " << centre_factor * randomdouble(-1, 1) << " " << -z_factor * randomdouble(1, 10) << endl;
        cout << radius_factor * randomdouble(0, 1) << endl;
    }
}