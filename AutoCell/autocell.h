#ifndef AUTOCELL_H
#define AUTOCELL_H

#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QIntValidator>
#include <QString>
#include <QSpinBox>
#include <QLayout>
#include <QTableWidget>
#include <QTableView>
#include <QHeaderView>
#include <QColor>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QMainWindow>
#include <QToolBar>
#include "Automate1D.h"
#include "Simulateur.h"

class Autocell : public QWidget {
    Q_OBJECT
    //QSpinBox* num; // numéro
    QIntValidator* zeroOneValidator;
    QGridLayout* layout;
    QTableWidget* depart;
    QTableWidget* etats = nullptr;
    QHBoxLayout* sim;
    QColor* color;

    unsigned int regle=0;
    int nbSim =20;
    int dimension = 15;
    int taille =20;

    void setEtatDepartDimension(int dim);

public:
    explicit Autocell(QWidget* parent = nullptr);
    void setDimension(int dim);
    void setColor(QColor a);
    int getDimension() const{
        return dimension;
    }
    QColor getColor() const{
        return *color;
    }
    void setNbSim(unsigned int nb){nbSim =nb;}
    void setRegle(unsigned int r){regle=r;}

private slots:
    /*void synchronizeNumToNumBit(int i);
    void synchronizeNumBitToNum(const QString& s);*/
    void cellSelected(int a,int b);

public slots:
    void runSim();

signals:
    void endSim();
};

#endif // AUTOCELL_H
