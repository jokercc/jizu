
#include"mainwindow.h"
//update to qt5
#include<QtWidgets>

int main(int argc,char* argv[]){
    QApplication app(argc,argv);

    QSplashScreen splash;
    QTimer splash_timer;
    splash.setPixmap(QPixmap(":/images/splash.png"));
    splash.show();
    splash_timer.start(3000);

    MainWindow mainwindow;

    QObject::connect(&splash_timer,SIGNAL(timeout()),&mainwindow,SLOT(show()));
    QObject::connect(&splash_timer,SIGNAL(timeout()),&splash,SLOT(close()));

    return app.exec();
}

