#include "informationbox.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>

InformationBox::InformationBox(QWidget *parent) : QWidget(parent)
{
    // Layout configuration
    layout = new QHBoxLayout();
    setLayout(layout);

    label1 = new QLabel("Right wait: ");
    label2 = new QLabel(">");

    QVBoxLayout *carCounts = new QVBoxLayout();
    label3 = new QLabel("Up cars: 0");
    label4 = new QLabel("Down cars: 0");
    carCounts -> addWidget(label3);
    carCounts -> addWidget(label4);

    layout -> addWidget(label1);
    layout -> addWidget(label2);
    layout -> addLayout(carCounts);
}

void
InformationBox::setLabel1(bool direction, int time)
{
    if(direction) label1 -> setText("Right wait: " + QString::number(time) + "ms");
    else label1 -> setText("Left wait: " + QString::number(time) + "ms");
}

void
InformationBox::setLabel2(int status)
{
    switch (status) {
    case 1: label2 -> setText("<"); break;
    case 2: label2 -> setText(">"); break;
    case 3: label2 -> setText("X"); break;
    default: break;
    }
}

void
InformationBox::setLabel3And4(int upCount, int downCount)
{
    label3 -> setText("Up cars: " + QString::number(upCount));
    label4 -> setText("Down cars: " + QString::number(downCount));
}

