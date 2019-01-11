#ifndef SINGLELANEBRIDGE_H
#define SINGLELANEBRIDGE_H

#include <QThread>
#include <QDebug>
#include <QSemaphore>
#include <map>
#include <queue>
class Car;
class TrafficControl;
class PossionProcess;
class Bridge;

const int kMaxCars2Pass = 3;
const int bridgeTurnPos[6] = {0, 75, 100, 150, 175, 250};
const int bridgeLen = bridgeTurnPos[5];
const int bridgeEntryPos = bridgeTurnPos[1];

class SingleLaneBridge : public QThread
{
    Q_OBJECT

public:
    SingleLaneBridge();
    void run();
    int carWidth;
    Bridge *bridge;

public slots:
    void updatePos(Car *car, int pos);
    void setEnterCar(bool direction);
    void setCarWidth(int width);
    void checkTraffic();
    void changeTraffic(bool direction);
    void init();
    void setCreateFreq(int amountInMin);
    void setCarSpeed(int speed);
    void createCar(bool direction);
    void autoCreateCar();
    void carWaitTime(bool direction, int time);

signals:
    void carChanged(int carID, int pos);
    void deleteCar(int carID);

private:
    // No more car can enter the bridge if true
    bool *trafficLightChange;
    bool *rightPass;
    QSemaphore *trafficLight = new QSemaphore(kMaxCars2Pass);

    int upCarsCount;
    int downCarsCount;
    TrafficControl *trafficControler;
    PossionProcess *possionProcess;
    int createInterval;
    int carSpeed;
    int carAmount;
    std::queue<bool> readyCars;
    int checkTimeDelay;
};

#endif // SINGLELANEBRIDGE_H
