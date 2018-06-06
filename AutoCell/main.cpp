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
    window->show();
    window->showMaximized();
/*
    vector<vector<unsigned short int>> v;
    v.push_back(vector<unsigned short int>());
    v.push_back(vector<unsigned short int>());//[1,1,0,2,3] [0,1,1,3,3]
    v[0].push_back(1);v[0].push_back(1);v[0].push_back(0);v[0].push_back(2);v[0].push_back(3);
    v[1].push_back(0);v[1].push_back(1);v[1].push_back(1);v[1].push_back(3);v[1].push_back(3);


    Etat2D e(15,15,2);
    e.setCellule(7,7,1);e.setCellule(7,6,1);e.setCellule(7,8,1);e.setCellule(6,7,1);e.setCellule(8,7,1);
    for( int i=0;i<2;i++){
        for(int j=0;j<5;j++){
            cout<<v[i][j];
        }
        cout<<endl;
    }
    Automate2D a(v);
    Simulateur<Automate2D,Etat2D> s(a,e);
    for(int i=0;i<12;i++){
    s.next(); s.dernier().afficher();}*/

    return app.exec();
}
