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
#include "Automate.h"
#include "Simulateur.h"

class Autocell : public QWidget {
    Q_OBJECT
    QSpinBox* num; // numéro
    QLineEdit* numeroBit[8]; // un QLineEdit par bit
    QLabel* numl;
    QLabel* numeroBitl[8];
    QVBoxLayout* numc;
    QVBoxLayout* bitc[8];
    QHBoxLayout* numeroc;
    QIntValidator* zeroOneValidator;
    QGridLayout* layout;
    QTableWidget* depart;
    QPushButton* simulation;
    QTableWidget* etats = nullptr;
    QSpinBox* nbSim;
    QHBoxLayout* sim;
    //QToolBar* option;
    QColor* color;

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

private slots:
    void synchronizeNumToNumBit(int i);
    void synchronizeNumBitToNum(const QString& s);
    void cellSelected(int a,int b);
    void runSim(bool);

signals:
    void endSim();
};

#endif // AUTOCELL_H
