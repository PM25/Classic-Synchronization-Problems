#ifndef SIDEMENU_H
#define SIDEMENU_H

#include <QWidget>
class QVBoxLayout;

class SideMenu : public QWidget
{
    Q_OBJECT
public:
    explicit SideMenu(QWidget *parent = nullptr);

private:
    QWidget* createControlWidgets();
    QWidget* carControlWidget(int mode=0, QString text="");
    QVBoxLayout *layout;

public slots:
    void createUpCarSignal();
    void createDownCarSignal();

signals:
    void run();
    void freqChange(int);
    void speedChange(int);
    void createCar(bool);
    void autoCreateCar();
    void makeStarvation();
    void setTimeLimit(bool);

public slots:
};

#endif // SIDEMENU_H
