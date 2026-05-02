#include "mainwindow.h"
#include "System.h"
#include "Provider.h"
#include <QApplication>
#include <QtSql>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    System system;
    // Removed: hardcoded provider1/provider2/provider3 inserts.
    // They added duplicate DB rows on every launch.
    // Register providers through the UI instead.
    MainWindow w(&system);
    w.show();
    return a.exec();
}
