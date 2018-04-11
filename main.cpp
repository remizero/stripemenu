#include <QApplication>

#include "MainWindow.h"

#include <QString>

int main ( int argc, char *argv [] ) {

    QApplication app ( argc, argv );
    app.setOrganizationName ( "QtProject" );
    app.setApplicationName ( "Application Example" );

    MainWindow mainWindow;
    //mainWindow.setWindowFlags ( Qt::FramelessWindowHint );
    mainWindow.show ();

    return app.exec ();
}
