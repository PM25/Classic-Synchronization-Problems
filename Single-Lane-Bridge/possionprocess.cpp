#include "possionprocess.h"
#include <cstdlib>
#include <cmath>

PossionProcess::PossionProcess(int n)
{
    lambda = 1.0 / n;
}

void
PossionProcess::setAvg(int avg)
{
    lambda = 1.0 / avg;
}

double
PossionProcess::nextTime()
{
    double u = (double) rand() / (RAND_MAX + 1.0);
    return (-1) * log(u) / lambda;
}
