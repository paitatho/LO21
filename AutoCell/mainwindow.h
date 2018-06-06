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
    QWidget* option2D;
    QGridLayout* layout2D;
    QColorDialog* color;
    QSpinBox* nbSim1D;
    QSpinBox* regle1D;

    QMdiArea * central;
    QMdiSubWindow* subWin;

    QDockWidget* optionDock;
    QFrame* separator;
    static Autocell* auto1D;

    virtual void createToolBar();
    virtual void createDockOption();
    virtual void createMdiArea();
    virtual void createOption1D();
    virtual void createOption2D();
public:
    MainWindow();
    void closeEvent(QCloseEvent *event);
    void saveAppState();
    void restoreAppState();
public slots:
    void changeNbCell(int a);
    virtual void openSim();
    void clearAuto1D();
    void setOption(const QString& automate);
    void chooseColor();
    void changeColor(QColor);
    void changeSize();
    void changeNbSim(int a);
    void changeRegle(int a);
    void play();
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
