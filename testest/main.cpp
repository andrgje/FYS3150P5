//#include <mpi.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <random>
#include <armadillo>
#include <string>
#include <sstream>
using namespace  std;
using namespace arma;
// output file
ofstream ofile;

using namespace std;
int main()
{
    mat b(500, 500, fill::zeros);
    b[200,201]=1;
    cout <<b[200,201];
}
