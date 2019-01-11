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

    layout -> addWidget(label1);
    layout -> addWidget(label2);
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

