#include "singlelanebridge.h"
#include "car.h"
#include "trafficcontrol.h"
#include "possionprocess.h"
#include "bridge.h"
#include <QSemaphore>
#include <QTimer>

SingleLaneBridge::SingleLaneBridge()
{
    upCarsCount = 0;
    downCarsCount = 0;
    trafficLightChange = new bool(false);
    rightPass = new bool(false);
    carWidth = 60;
    createInterval = 500;
    possionProcess = new PossionProcess(createInterval);
    carSpeed = 8;
    carAmount = 0;
    checkTimeDelay = 0;
    bridge = new Bridge(bridgeLen - bridgeEntryPos * 2);
}

void
SingleLaneBridge::run()
{
    trafficControler = new TrafficControl;
    trafficControler -> setCarPass(trafficLightChange, rightPass);
    trafficControler -> setTrafficLight(trafficLight);

    Car *lastUpCar(NULL), *lastDownCar(NULL), *currCar;
    for(int iter(0); iter < INT_MAX; ++iter) {
        // Increase {carAmount} to make more cars
        while(iter >= carAmount) {
            if(carAmount == -1) carAmount = iter;
            QThread::currentThread() -> msleep(100);
        }
        if(carAmount == INT_MAX) {
            if(rand() % 2) readyCars.push(true);
            else readyCars.push(false);
        }

        if(readyCars.front()) {
            currCar = new Car(this, true, carSpeed);
            ++downCarsCount;
        } else {
            currCar = new Car(this, false, carSpeed);
            ++upCarsCount;
        } readyCars.pop();
        currCar -> setTrafficLight(trafficLight);
        currCar -> setCarPass(trafficLightChange, rightPass);

        if(currCar -> getDirection()) {
            if(lastDownCar == NULL || lastDownCar->getPos() == bridgeLen) {
                currCar -> setMaxDistance(bridgeLen);
            } else {
                lastDownCar -> setBackCar(currCar);
                currCar -> setMaxDistance(lastDownCar->getPos() - carWidth);  
            } lastDownCar = currCar;
        } else {
            if(lastUpCar == NULL || lastUpCar->getPos() == bridgeLen) {
                currCar -> setMaxDistance(bridgeLen);
            } else {
                lastUpCar -> setBackCar(currCar);
                currCar -> setMaxDistance(lastUpCar->getPos() - carWidth);
            } lastUpCar = currCar;
        }
        connect(currCar, SIGNAL(backCarMaxDistance(Car*,int)), this, SLOT(updatePos(Car*,int)));

        currCar -> start();
        connect(currCar, SIGNAL(posChanged(int,int)), this, SIGNAL(carChanged(int,int)));
        connect(currCar, SIGNAL(finished()), currCar, SLOT(deleteLater()));
        connect(currCar, SIGNAL(finished(int)), this, SIGNAL(deleteCar(int)));
        connect(currCar, SIGNAL(enterBridge(bool)), this, SLOT(setEnterCar(bool)));

        QThread::currentThread() -> msleep(possionProcess->nextTime());
    }
}

void
SingleLaneBridge::updatePos(Car *car, int pos)
{
    if((car -> getBackCar()) != NULL) {
        Car *backCar = (car -> getBackCar());
        if(pos == bridgeLen) backCar -> setMaxDistance(bridgeLen);
        else backCar -> setMaxDistance(pos - carWidth);
    }
}

void
SingleLaneBridge::setEnterCar(bool direction)
{
    if(direction) --downCarsCount;
    else --upCarsCount;
}

void
SingleLaneBridge::init()
{
    this -> start();
}

void
SingleLaneBridge::setCarWidth(int width)
{
    carWidth = width;
}

void
SingleLaneBridge::setCreateFreq(int amountInMin)
{
    createInterval = (1.0 / amountInMin) * 60000;
    possionProcess -> setAvg(createInterval);
}

void
SingleLaneBridge::createCar(bool direction)
{
    ++carAmount;
    readyCars.push(direction);
}

void
SingleLaneBridge::checkTraffic()
{
    if(checkTimeDelay == 0) {
        if(downCarsCount > upCarsCount && !(*trafficLightChange)) {
            trafficControler -> setLanePass(true);
        } else if(upCarsCount > downCarsCount && !(*trafficLightChange)) {
            trafficControler -> setLanePass(false);
        }
    } else {
        --checkTimeDelay;
    }
}

void
SingleLaneBridge::changeTraffic(bool direction)
{
    checkTimeDelay = 20;
    trafficControler -> setLanePass(direction);
}

void
SingleLaneBridge::autoCreateCar()
{
    if(carAmount == INT_MAX) carAmount = -1;
    else carAmount = INT_MAX;
}

void
SingleLaneBridge::setCarSpeed(int speed)
{
    carSpeed = speed / 30;
}

void
SingleLaneBridge::carWaitTime(bool direction, int time)
{
    if(time >= 5000) changeTraffic(direction);
    else checkTraffic();
}
