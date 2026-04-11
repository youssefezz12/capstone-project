#include "mainwindow.h"
#include "System.h"
#include "Provider.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    System system;
    Provider provider1 ("Name", "pass", "Cooking", 50);
    Provider provider2 ("Name", "pass", "Cooking", 100);
    Provider provider3 ("Name", "pass", "Cooking", 200);

    system.addProvider(provider1);
    system.addProvider(provider2);
    system.addProvider(provider3);

    MainWindow w(&system);

    w.show();
    return a.exec();
}
