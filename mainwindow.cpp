#include "mainwindow.h"
#include "sidemenu.h"
#include "informationbox.h"
#include "canvas.h"
#include "Single-Lane-Bridge/singlelanebridge.h"
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGuiApplication>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create a QWidget as a central widget.
    QWidget* win = new QWidget;
    setCentralWidget(win);

    // Initialize window
    QRect desktop =  QGuiApplication::primaryScreen() -> geometry();
    int win_height = desktop.height() / 2;
    int win_width = desktop.width() / 2;
    setGeometry(desktop.width()/4, desktop.height()/4, win_width, win_height);
    setWindowTitle(tr("Single Lane Bridge Problem"));
    setMinimumSize(win_width/2, win_height/2);
    setFont(QFont("Helvetica [Cronyx]", 14));
    setPalette(QColor(180, 180, 180));
    setAutoFillBackground(true);

    // Widgets
    SideMenu *sidemenu = new SideMenu();
    InformationBox *informationbox = new InformationBox();
    Canvas *canvas = new Canvas();

    // Problem
    SingleLaneBridge *problem = new SingleLaneBridge;
    connect(canvas, SIGNAL(carWidthChange(int)), problem, SLOT(setCarWidth(int)));
    connect(sidemenu, SIGNAL(run()), problem, SLOT(init()));
    connect(sidemenu, SIGNAL(createCar(bool)), problem, SLOT(createCar(bool)));
    connect(sidemenu, SIGNAL(autoCreateCar()), problem, SLOT(autoCreateCar()));
    connect(sidemenu, SIGNAL(freqChange(int)), problem, SLOT(setCreateFreq(int)));
    connect(sidemenu, SIGNAL(speedChange(int)), problem, SLOT(setCarSpeed(int)));
    connect(sidemenu, SIGNAL(makeStarvation()), problem, SLOT(makeStarvation()));
    connect(sidemenu, SIGNAL(setTimeLimit(bool)), problem, SLOT(setTimeLimit(bool)));
    connect(problem, SIGNAL(carChanged(int,int)), canvas, SLOT(setObjects(int,int)));
    connect(problem, SIGNAL(deleteCar(int)), canvas, SLOT(deleteObject(int)));
    connect(problem, SIGNAL(waitTime(bool,int)), informationbox, SLOT(setLabel1(bool,int)));
    connect(problem, SIGNAL(trafficStatus(int)), informationbox, SLOT(setLabel2(int)));

    // Layout
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout -> addWidget(canvas, 0, 0);
    mainLayout -> setRowStretch(0, 5);
    mainLayout -> addWidget(informationbox, 1, 0);
    mainLayout -> setRowStretch(1, 1);
    mainLayout -> addWidget(sidemenu, 2, 0);
    mainLayout -> setRowStretch(2, 1);

    //Set layout
    win -> setLayout(mainLayout);
}

MainWindow::~MainWindow()
{

}
