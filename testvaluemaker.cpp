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
    double centre_factor = 1.3;
    double z_factor = 1;
    double radius_factor = 0.8;
    std::cout << centre_factor * randomdouble(-1, 1) << " " << centre_factor * randomdouble(-1, 1) << " " << -z_factor * randomdouble(5, 10) << endl;
    std::cout << radius_factor * randomdouble(0, 1) << endl;
}