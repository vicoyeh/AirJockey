#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

     connect(ui->start, SIGNAL(released()),this, SLOT(clickStart()));
     connect(ui->stop, SIGNAL(released()),this, SLOT(clickStop()));
     connect(ui->leftCD, SIGNAL(released()),this, SLOT(loadSoundTrack1()));
     connect(ui->rightCD, SIGNAL(released()),this, SLOT(loadSoundTrack2()));


     //disc images
     //QPixmap *pixmap = new QPixmap("/Users/kuan-hsuanyeh/build-mixer-Desktop_Qt_5_3_clang_64bit-Debug/disc.png");
     //ui->leftCD->setPixmap(*pixmap);
     //ui->rightCD->setPixmap(*pixmap);



}

void MainWindow::loadSoundTrack1(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"", tr("Files (*.wav)"));
    std::string fname = fileName.toStdString();
    std::string printMe = "Loading..."+fname;
    qDebug(printMe.c_str());
}

void MainWindow::loadSoundTrack2(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"", tr("Files (*.*)"));
    std::string fname = fileName.toStdString();
    std::string printMe = "Loading..."+fname;
    qDebug(printMe.c_str());
}

void MainWindow::clickStart() {
    qDebug ("Start");
}

void MainWindow::clickStop() {
    qDebug ("Stop");
}

void mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton){
        qDebug("right button is pressed");
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
