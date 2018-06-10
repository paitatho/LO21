#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "autocell.h"
#include<iostream>
#include<QtXml>


class MainWindow : public QMainWindow
{Q_OBJECT
private:
    QToolBar* toolBar;
    std::vector<QIcon *> icon;
    std::vector<QAction *> action;
    std::vector<QLabel *> label;
    QComboBox *choixSim;

    QGroupBox* boxDim;
    QGridLayout* layoutBoxDim;
    QGroupBox* boxCel;
    QGridLayout* layoutBoxCel;
    QWidget* option1D;
    QGridLayout* layout1D;
    QSpinBox* larg1D;
    QSpinBox* nbSim1D;
    QSpinBox* regle1D;
    QComboBox* bb;

    QColorDialog* color;

    QWidget* option2D;
    QGridLayout* layout2D;
    QGridLayout* layoutBoxDim2D;
    QGroupBox* boxCel2D;
    QGroupBox* boxDim2D;
    QGridLayout* layoutBoxCel2D;
    QGroupBox* boxParam2D;
    QComboBox* mode2D;
    QGridLayout* layoutBoxParam2D;
    QMdiArea * central;
    QMdiSubWindow* subWin;
    QMdiSubWindow* subWin2D;
    QSpinBox* larg2D;
    QSpinBox* haut2D;
    QSpinBox* speed2D;
    QSpinBox* taille;

    QDockWidget* optionDock;
    static Autocell1D* auto1D;
    static Autocell2D* auto2D;

    void createToolBar();
    virtual void createDockOption();
    virtual void createMdiArea();
    void createOption1D();
    void createOption2D();

    virtual void extensionOption1D(){}
    virtual void extensionOption2D(){}
    virtual void extensionToolBar(){}

public:
    MainWindow();
    virtual void closeEvent(QCloseEvent *event);
    virtual void saveAppState();
    virtual void restoreAppState();
public slots:
    virtual void openSim();
    virtual void clearAuto1D(){ auto1D = nullptr;subWin = nullptr;larg1D->setValue(15);nbSim1D->setValue(20);regle1D->setValue(150);}
    virtual void clearAuto2D(){auto2D = nullptr; subWin2D = nullptr;}

    void changeColor(QString);
    void changeSize();
    void changeHauteur(int a);
    void changeLargeur(int a);
    virtual void changeRegle1D(int a);
    //virtual void changeRegle2D(std::vector<std::vector<unsigned short int>> r,std::vector<std::string> c);
    void changeSpeed(int s);
    void changeTaille(int);

    virtual void play();
    void pause();
    void clear();
    virtual void current(QMdiSubWindow *w);
    virtual void allow(){action[3]->setEnabled(true);}
    virtual void afficherRegle2D(){ auto2D->get_regle2D()->show();}

    void initialiseur();
    void initialiseurSym();
};


class WSpacer : public QWidget
{
Q_OBJECT
public :
    WSpacer()
    {
    setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    }
};

#endif // MAINWINDOW_H
