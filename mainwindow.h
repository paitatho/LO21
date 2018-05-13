#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include <QMenu>
#include "autocell.h"



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
    QWidget* option1D;
    QGridLayout* layout1D;
    QSpinBox* b;
    QWidget* option2D;
    QGridLayout* layout2D;
    QColorDialog* color;

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


public slots:
    void changeNbCell(int a);
    virtual void runSim();
    void clearAuto1D();
    void setOption(const QString& automate);
    void chooseColor();
    void changeColor(QColor);
    void changeSize();
};


#endif // MAINWINDOW_H
