#include <QApplication>
#include "autocell.h"
#include "mainwindow.h"
#include "Etat2D.h"
#include "Automate2D.h"
#include "Simulateur.h"
using namespace std;

int main(int argc, char * argv[]) {
    QApplication app(argc, argv);

    MainWindow* window = new MainWindow();
    window->restoreAppState();
    window->showMaximized();

    return app.exec();
}
