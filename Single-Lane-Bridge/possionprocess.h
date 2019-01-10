#ifndef POSSIONPROCESS_H
#define POSSIONPROCESS_H


class PossionProcess
{
public:
    PossionProcess(int n);
    void setAvg(int avg);
    double nextTime();

private:
    double lambda;
};

#endif // POSSIONPROCESS_H
