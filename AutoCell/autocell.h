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
#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include "Automate1D.h"
#include "Simulateur.h"


class Autocell: public QWidget{
    Q_OBJECT
protected:
    int taille =20;
    unsigned int nbEtat;
    std::vector<std::string> couleur;
    int hauteur =20;
    int largeur = 15;
public:
    Autocell(QWidget* parent = nullptr,unsigned int Etat=2): QWidget(parent),nbEtat(Etat){
        couleur.push_back("green");
        couleur.push_back("black");
        couleur.push_back("red");
        couleur.push_back("white");
    }
    void setNbEtat(unsigned int e){nbEtat = e;}
    unsigned int getNbEtat() const {return nbEtat;}
    void setTaille(unsigned int t){taille =t;}
    unsigned int getTaille() const {return taille;}
    virtual int getLargeur() const{
        return largeur;
    }
    virtual int getHauteur() const{
        return hauteur;
    }
    virtual void runSim() =0;
    virtual void setHauteur(unsigned int)=0;
    virtual void setLargeur(unsigned int)=0;
    virtual void setColor(QColor)=0;
    virtual void setContinu(bool a)=0;
    virtual void clear()=0;
 public slots:
    //virtual ~Autocell()=default;

    virtual void cellSelected(int a,int b)=0;

signals:
    void endSim();

};


class Autocell1D: public Autocell {
    Q_OBJECT
protected:
    QGridLayout* layout;
    QTableWidget* depart;
    QTableWidget* etats = nullptr;
    QHBoxLayout* sim;
    QColor* color;

    unsigned int regle=0;

    void setEtatDepart(int dim);

public:
    explicit Autocell1D(QWidget* parent = nullptr);
    void setLargeur(unsigned int dim);
    void setColor(QColor a);

    QColor getColor() const{
        return *color;
    }
    void setHauteur(unsigned int nb){hauteur =nb;}
    void setRegle(unsigned int r){regle=r;}

    virtual void runSim();
    virtual void setContinu(bool a){}
    virtual void clear();
public slots:
    virtual void cellSelected(int a,int b);


private slots:
    /*void synchronizeNumToNumBit(int i);
    void synchronizeNumBitToNum(const QString& s);*/




};

/*####################################################################################*/

class Autocell2D:public Autocell{
    Q_OBJECT
protected:
    std::vector<std::vector<unsigned short int>> regle;
    unsigned int speed=100;
    QGridLayout* layout;
    QTableWidget* etats = nullptr;
    QColor* color;
    bool continu = true;
    unsigned int compteur =1;
    void setEtat(int h,int l);
public:
    Autocell2D(QWidget* parent = nullptr);
    void setSpeed(unsigned int s){speed =100;}
    void setColor(QColor a){}
    void setLargeur(unsigned int l){largeur=l;}
    void setHauteur(unsigned int l){hauteur=l;}
    void setNbSim(unsigned int){}
    QColor getColor() const{
        return *color;
    }
    void setContinu(bool a){continu=a;}
    bool getContinu(){return continu;}


public slots:
    void cellSelected(int a,int b);
    void clear();
    void runSim();

};

class Regle2D: public QWidget{
    Q_OBJECT
private:
    QSpinBox* nbEtat;
    QComboBox* regleBase;
    std::vector<QSpinBox*> celluleACCompter;
    std::vector<QComboBox*> interval;
    std::vector<QSpinBox*> borneInf;
    std::vector<QSpinBox*> borneSup;
    std::vector<QComboBox*> couleur;
    QGridLayout* layout;

public:
    Regle2D(QWidget* parent = nullptr);
public slots:
    void depart();
    void cacher();
signals:
    void emitRegle(std::vector<std::vector<int>> v);

};

#endif // AUTOCELL_H
