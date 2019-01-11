#include "sidemenu.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>

SideMenu::SideMenu(QWidget *parent) : QWidget(parent)
{
    // Layout configuration
    layout = new QVBoxLayout();
    setLayout(layout);

    layout -> addWidget(createControlWidgets());
}

QWidget*
SideMenu::createControlWidgets()
{
    // Layout
    QGridLayout *carLayout = new QGridLayout();

    // Widgets
    QLabel *carLabel = new QLabel(tr("Control"));
    carLabel -> setAlignment(Qt::AlignCenter);
    QPushButton *startBtn = new QPushButton(tr("Start"));
    QPushButton *addUpCarBtn = new QPushButton(tr("Add (Left)"));
    QPushButton *addDownCarBtn = new QPushButton(tr("Add (Right)"));
    QPushButton *autoCreateCarBtn = new QPushButton(tr("Auto"));
    QPushButton *starvation = new QPushButton(tr("Starvation"));
    QPushButton *deadLock = new QPushButton(tr("DeadLock"));
    QCheckBox *timeLimit = new QCheckBox(tr("Set time limit (5sec)"));
    QWidget *carFreq = carControlWidget(0, "(cars/min)");
    QWidget *carSpeed = carControlWidget(1, "(1/speed)");

    // Layout
    carLayout -> addWidget(carLabel, 0, 0, 1, 5);
    carLayout -> addWidget(startBtn, 1, 0);
    carLayout -> addWidget(addUpCarBtn, 1, 1);
    carLayout -> addWidget(autoCreateCarBtn, 1, 2);
    carLayout -> addWidget(addDownCarBtn, 1, 3);
    carLayout -> addWidget(starvation, 1, 4);
    carLayout -> addWidget(carFreq, 2, 0, 1, 4);
    carLayout -> addWidget(deadLock, 2, 4);
    carLayout -> addWidget(carSpeed, 3, 0, 1, 4);
    carLayout -> addWidget(timeLimit, 3, 4);

    // Behavior
    connect(startBtn, SIGNAL(clicked()), this, SIGNAL(run()));
    connect(addUpCarBtn, SIGNAL(clicked()), this, SLOT(createUpCarSignal()));
    connect(addDownCarBtn, SIGNAL(clicked()), this, SLOT(createDownCarSignal()));
    connect(autoCreateCarBtn, SIGNAL(clicked()), this, SIGNAL(autoCreateCar()));
    connect(starvation, SIGNAL(clicked()), this, SIGNAL(makeStarvation()));
    connect(deadLock, SIGNAL(clicked()), this, SIGNAL(makeDeadLock()));
    connect(timeLimit, SIGNAL(clicked(bool)), this, SIGNAL(setTimeLimit(bool)));

    // Pack as a widget
    QWidget *carMenu = new QWidget;
    carMenu -> setLayout(carLayout);

    return carMenu;
}

QWidget*
SideMenu::carControlWidget(int mode, QString text)
{
    // Widgets
    QLabel *labelTitle = new QLabel();
    switch(mode){
    case 0: labelTitle -> setText(tr("Frequence: ")); break;
    case 1: labelTitle -> setText(tr("Speed: ")); break;
    }
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider -> setRange(10, 300);
    slider -> setValue(100);
    QLabel *labelValue = new QLabel();
    labelValue -> setText(QString::number(slider -> value()));

    // Behavior
    connect(slider, SIGNAL(valueChanged(int)), labelValue, SLOT(setNum(int)));
    switch(mode){
    case 0: connect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(freqChange(int))); break;
    case 1: connect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(speedChange(int))); break;
    }

    // Layout
    QHBoxLayout *carFreqLayout = new QHBoxLayout();
    carFreqLayout -> addWidget(labelTitle);
    carFreqLayout -> addWidget(slider);
    carFreqLayout -> addWidget(labelValue);
    carFreqLayout -> addWidget(new QLabel(text));

    // Pack as a widget
    QWidget *carFreqWidget = new QWidget;
    carFreqWidget -> setLayout(carFreqLayout);

    return carFreqWidget;
}

void
SideMenu::createUpCarSignal()
{
    emit createCar(false);
}

void
SideMenu::createDownCarSignal()
{
    emit createCar(true);
}
