#ifndef AUTOCELL_H
#define AUTOCELL_H

#include <QtWidgets>
#include <typeinfo>
#include <cstdlib>
#include "Automate1D.h"
#include "Simulateur.h"


class Autocell: public QWidget{
    Q_OBJECT
protected:
    int taille =20;
    unsigned int nbEtat;
    unsigned int speed=100;
    std::vector<std::string> couleur;
    int hauteur =20;        // pour Autocell1D la hauteur représente le nb de simulation
    int largeur = 15;
public:
    Autocell(QWidget* parent = nullptr,unsigned int Etat=2): QWidget(parent),nbEtat(Etat){
        couleur.push_back("white");
        couleur.push_back("black");
        couleur.push_back("blue");
        couleur.push_back("red");
    }
    void setNbEtat(unsigned int e){nbEtat = e;}
    unsigned int getNbEtat() const {return nbEtat;}
    void setTaille(unsigned int t){taille =t;adjustTaille();}
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
    virtual void setContinu(bool a)=0;
    virtual void clear()=0;
    virtual void adjustTaille() =0;
    virtual void init()=0;
    virtual void setCouleur(std::vector<std::string> c){couleur.clear();couleur =c;}
    virtual void setSpeed(unsigned int s)=0;
 public slots:

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
    QColor getColor() const{return *color;}
    void setHauteur(unsigned int nb){hauteur =nb;}
    void setRegle(unsigned int r){regle=r;}
    virtual void runSim();
    virtual void setContinu(bool a){}
    virtual void adjustTaille();
    virtual void clear();
    virtual void init(){}
    void setSpeed(unsigned int s){}
public slots:
    virtual void cellSelected(int a,int b);


};

/*####################################################################################*/

class Autocell2D:public Autocell{
    Q_OBJECT
protected:
    std::vector<std::vector<unsigned short int>> regle;
    QGridLayout* layout;
    QTableWidget* etats = nullptr;
    bool continu = true;
    unsigned int compteur =1;
    void setEtat(int h,int l);
public:
    Autocell2D(QWidget* parent = nullptr);
    void setSpeed(unsigned int s){speed =s;}
    void setLargeur(unsigned int l){largeur=l;adjustTaille();}
    void setHauteur(unsigned int h){hauteur=h;adjustTaille();}
    void setNbSim(unsigned int){}
    void setContinu(bool a){continu=a;}
    bool getContinu(){return continu;}
    virtual void adjustTaille();
    void setRegle(std::vector<std::vector<unsigned short int>> r){regle.clear();regle=r;setNbEtat(regle.size());}
    const std::vector<std::vector<unsigned short int>>& getRegle() const {return regle;}
    virtual void init();

public slots:
    void cellSelected(int a,int b);
    void clear();
    void runSim();

};

class Regle2D: public QWidget{
    Q_OBJECT
private:
    std::vector<std::vector<unsigned short int>> regle;
    QSpinBox* nbEtat;
    QComboBox* regleBase;
    std::vector<QSpinBox*> etatCellulePourAppliquer;
    std::vector<QSpinBox*> celluleACCompter;
    std::vector<QComboBox*> interval;
    std::vector<QSpinBox*> borneInf;
    std::vector<QSpinBox*> borneSup;
    std::vector<QComboBox*> couleur;
    std::vector<std::string> couleurNom;
    QGridLayout* layout;

    void depart();                  //méthode d'initialisation
    virtual void modifDepart(){regleBase->addItem("Feu de Foret");}

public:
    Regle2D(QWidget* parent = nullptr);
public slots:

    void cacher();
    void setRegle();
    void setCouleur();
    void sendRegle();
    void reglePredefini(QString);
    virtual void ajoutReglePredefini(QString);
    void montrer();
    void adjust();

signals:
    void envoiRegle(std::vector<std::vector<unsigned short int>>,std::vector<std::string>);

};

#endif // AUTOCELL_H
