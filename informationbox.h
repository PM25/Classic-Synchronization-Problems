#ifndef INFORMATIONBOX_H
#define INFORMATIONBOX_H

#include <QWidget>
class QHBoxLayout;
class QLabel;

class InformationBox : public QWidget
{
    Q_OBJECT
public:
    explicit InformationBox(QWidget *parent = nullptr);

signals:

public slots:
    void setLabel1(bool direction, int time);
    void setLabel2(int status);

private:
    QHBoxLayout *layout;
    QLabel *label1;
    QLabel *label2;
};

#endif // INFORMATIONBOX_H
