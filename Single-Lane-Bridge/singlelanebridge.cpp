#include "singlelanebridge.h"
#include "car.h"
#include "trafficcontrol.h"
#include <QSemaphore>

SingleLaneBridge::SingleLaneBridge()
{
    if(eastTrafficLight -> available() > 0) east2west = true;
    else if(westTrafficLight -> available() > 0) east2west = false;

    upCarsCount = 0;
    downCarsCount = 0;

    trafficLightChange = new bool(false);
}

void
SingleLaneBridge::run()
{
    for(int iter(0); iter < 50; ++iter){
        Car *tmpCar;
        if(iter %2) {
            tmpCar = new Car(true);
            ++upCarsCount;
        }
        else {
            tmpCar = new Car(false);
            ++downCarsCount;
        }

        tmpCar -> setTrafficLight(westTrafficLight, eastTrafficLight);
        tmpCar -> setCarPass(trafficLightChange);
        cars.insert(std::pair<int, Car*>(tmpCar->getID(), tmpCar));
    }

    trafficControler = new TrafficControl;
    trafficControler -> setCarPass(trafficLightChange);
    trafficControler -> setTrafficLight(westTrafficLight, eastTrafficLight);

    std::map<int, Car*>::iterator iter;
    for(iter = cars.begin(); iter != cars.end(); ++iter){
        Car *currCar = (iter -> second);

        currCar -> start();
        connect(currCar, SIGNAL(posChanged(int,int)), this, SIGNAL(carChanged(int,int)));
        connect(currCar, SIGNAL(finished()), currCar, SLOT(deleteLater()));
        connect(currCar, SIGNAL(finished(int)), this, SIGNAL(deleteCar(int)));
        connect(currCar, SIGNAL(leaveBridge(bool)), this, SLOT(setFinishCar(bool)));

        QThread::currentThread() -> msleep(500);
    }
}

void
SingleLaneBridge::updatePos(int carID, int pos)
{
    qDebug() << "Car:" << carID << ", Pos:" << pos;
}

void
SingleLaneBridge::setFinishCar(bool direction)
{
    if(direction) {
        --downCarsCount;
        if(upCarsCount > downCarsCount && !(*trafficLightChange)) {
            trafficControler -> start();
            qDebug() << "Up Change";
        }
    }
    else {
        --upCarsCount;
        if(downCarsCount > upCarsCount && !(*trafficLightChange)) {
            trafficControler -> start();
            qDebug() << "Down Change";
        }
    }
}
