#ifndef MYTHREADS_H
#define MYTHREADS_H

#include <QThread>
#include <QDebug>
#include <QSemaphore>
#include "singlelanebridge.h"

class Car : public SingleLaneBridge
{
    Q_OBJECT

public:
    Car(SingleLaneBridge *bridge, bool direction=0, int timeInterval=-1);
    void run();
    unsigned int getID() const;
    int getPos() const;
    bool getDirection() const;
    void setBackCar(Car *car);
    Car* getBackCar() const;
    QSemaphore *trafficLight;

signals:
    void posChanged(int, int);
    void backCarMaxDistance(Car*, int);
    void finished(int);
    void enterBridge(bool);

public slots:
    void setTrafficLight(QSemaphore *tLight);
    void setCarPass(bool *lightChange, bool *rPass);
    void setMaxDistance(int distance);

private:
    unsigned int id;
    int tickInterval;
    int pos;
    static unsigned int lastID;
    bool _direction; // {false} for left to right, {true} for right to left
    bool *disablePass;
    bool *rightPass;
    int *maxDistance;
    Car *back;
    SingleLaneBridge *world;
};

#endif // MYTHREADS_H
