#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include <QMenu>
#include <QSettings>
#include <QEvent>
#include <QCloseEvent>
#include "autocell.h"
#include<iostream>


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

    QColorDialog* color;

    QWidget* option2D;
    QGridLayout* layout2D;
    QGridLayout* layoutBoxDim2D;
    QGroupBox* boxCel2D;
    QGroupBox* boxDim2D;
    QGridLayout* layoutBoxCel2D;
    QSpinBox* larg2D;
    QSpinBox* haut2D;
    QGroupBox* boxParam2D;
    QComboBox* mode2D;
    QGridLayout* layoutBoxParam2D;
    QSpinBox* speed2D;
    QMdiArea * central;
    QMdiSubWindow* subWin;
    QMdiSubWindow* subWin2D;

    QDockWidget* optionDock;
    QFrame* separator;
    static Autocell1D* auto1D;
    static Autocell2D* auto2D;

    virtual void createToolBar();
    virtual void createDockOption();
    virtual void createMdiArea();
    virtual void createOption1D();
    virtual void createOption2D();

    virtual void extensionOption1D(){}
    virtual void extensionOption2D(){}
    virtual void extensionToolBar(){}

public:
    MainWindow();
    void closeEvent(QCloseEvent *event);
    void saveAppState();
    void restoreAppState();
public slots:
    void changeNbCell(int a);
    virtual void openSim();
    void clearAuto1D(){ auto1D = nullptr;subWin = nullptr;larg1D->setValue(15);nbSim1D->setValue(20);regle1D->setValue(0);}
    void clearAuto2D(){auto2D = nullptr; subWin2D = nullptr;larg2D->setValue(30);haut2D->setValue(30);}
    void setOption(const QString& automate);
    void chooseColor() const;
    void changeColor(QColor);
    void changeSize();
    void changeNbSim(int a);
    void changeRegle(int a);
    void play();
    void pause();
    void clear();
    void current(QMdiSubWindow *w);
    void allow(){action[3]->setEnabled(true);}
    void regle2D(std::vector<std::vector<unsigned short int>>){}
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
