#ifndef AUTOCELL_H
#define AUTOCELL_H

#include <QtWidgets>
#include <typeinfo>
#include <cstdlib>
#include "Automate1D.h"
#include "Simulateur.h"

class Regle2D;

class Autocell: public QWidget{
    Q_OBJECT
protected:
    int taille =17;
    unsigned int nbEtat;
    unsigned int speed=100;
    std::vector<std::string> couleur;
    int hauteur =20;        // pour Autocell1D la hauteur représente le nb de simulation
    int largeur = 15;
public:
    Autocell(QWidget* parent = nullptr,unsigned int Etat=2): QWidget(parent),nbEtat(Etat){
        couleur.push_back("white"); couleur.push_back("white");
    }
    void setNbEtat(unsigned int e){nbEtat = e;}
    void setTaille(unsigned int t){taille =t;adjustTaille();adjustSize();}
    unsigned int getNbEtat() const {return nbEtat;}
    unsigned int getTaille() const {return taille;}
    unsigned int getLargeur() const{return largeur;}
    unsigned int getHauteur() const{return hauteur;}
    virtual void runSim() =0;
    virtual void setHauteur(unsigned int)=0;
    virtual void setLargeur(unsigned int)=0;
    virtual void setContinu(bool a)=0;
    virtual void clear()=0;
    virtual void adjustTaille() =0;
    virtual void init()=0;
    virtual void initSym()=0;
    void setCouleur(std::vector<std::string> c){couleur.clear();couleur =c;}
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

    unsigned int regle=0;

    void setEtatDepart(int dim);

public:
    explicit Autocell1D(QWidget* parent = nullptr);
    void setLargeur(unsigned int dim);
    void setHauteur(unsigned int nb){hauteur =nb;}
    void setRegle(unsigned int r){regle=r;}
    void setColor(QString a);
    virtual void runSim();
    virtual void setContinu(bool a){}
    virtual void adjustTaille();
    virtual void clear();
    virtual void init();
    virtual void initSym();
    void setSpeed(unsigned int s){}
    const QTableWidget* get_depart() const {return depart;}

    void setDepart(unsigned int i, QString color){
        depart->item(0,i)->setBackgroundColor(QColor(color));
    }
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
    Regle2D* fenetreRegle2D;
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
    virtual void initSym();
    const QTableWidget* get_etats() const {return etats;}
    Regle2D* get_regle2D(){return fenetreRegle2D;}
    void setEtats(unsigned int i, unsigned int j, QString color){
        etats->item(i,j)->setBackgroundColor(QColor(color));
    }

public slots:
    void cellSelected(int a,int b);
    void clear();
    void runSim();
    void changeRegle(std::vector<std::vector<unsigned short int> >,std::vector<std::string>);

};

class Regle2D: public QWidget{
    Q_OBJECT
protected:
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


public:
    Regle2D(QWidget* parent = nullptr);
    const QSpinBox* get_nbEtat() const {return nbEtat;}
    const QComboBox* get_regleBase() const{return regleBase;}
    const std::vector<QSpinBox*>& get_etatCellulePourAppliquer() const {return etatCellulePourAppliquer;}
    const std::vector<QSpinBox*>& get_celluleACCompter() const {return celluleACCompter;}
    const std::vector<QComboBox*>& get_interval() const {return interval;}
    const std::vector<QSpinBox*>& get_borneInf() const {return borneInf;}
    const std::vector<QSpinBox*>& get_borneSup() const {return borneSup;}
    const std::vector<QComboBox*>& get_couleur() const {return couleur;}
    const std::vector<std::string>& get_couleurNom() const {return couleurNom;}
    const std::vector<std::vector<unsigned short int>>& get_regle() const {return regle;}

    void setRegleBase(const QString& s){regleBase->setCurrentText(s);}
    void setNbEtat(unsigned int n){nbEtat->setValue(n);}
    void setEtatCellulePourAppliquer(unsigned int i, unsigned int n){ etatCellulePourAppliquer[i]->setValue(n);}
    void setCelluleACompter(unsigned int i, unsigned int n){celluleACCompter[i]->setValue(n);}
    void setInterval(unsigned int i, const QString& s){interval[i]->setCurrentText(s);}
    void setBorneInf(unsigned int i, unsigned int n){borneInf[i]->setValue(n);}
    void setBorneSup(unsigned int i, unsigned int n){borneSup[i]->setValue(n);}
    void setCouleur(unsigned int i, const QString& s){couleur[i]->setCurrentText(s);}
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

class Regle2DBis : public Regle2D{
public:
    Regle2DBis(QWidget* parent = nullptr):Regle2D(parent){regleBase->addItem("Feu de Foret");}
    virtual void ajoutReglePredefini(QString nom){
        if (nom == "Feu de Foret"){
            nbEtat->setValue(4);
            etatCellulePourAppliquer[0]->setValue(0);
            celluleACCompter[0]->setValue(2); interval[0]->setCurrentIndex(1);
            borneInf[0]->setValue(1);borneSup[0]->setValue(8);couleur[0]->setCurrentIndex(2);

            etatCellulePourAppliquer[1]->setValue(1);
            celluleACCompter[1]->setValue(0); interval[1]->setCurrentIndex(0);
            borneInf[1]->setValue(0);borneSup[1]->setValue(8);couleur[1]->setCurrentIndex(0);

            etatCellulePourAppliquer[2]->setValue(0);
            celluleACCompter[2]->setValue(2); interval[2]->setCurrentIndex(0);
            borneInf[2]->setValue(1);borneSup[2]->setValue(8);couleur[2]->setCurrentIndex(3);

            etatCellulePourAppliquer[3]->setValue(2);
            celluleACCompter[3]->setValue(0); interval[3]->setCurrentIndex(0);
            borneInf[3]->setValue(0);borneSup[3]->setValue(8);couleur[3]->setCurrentIndex(1);
        }
    }
};

class Autocell2DBis: public Autocell2D{
public:
    Autocell2DBis(QWidget* parent = nullptr):Autocell2D(parent){
        delete fenetreRegle2D;
        fenetreRegle2D = new Regle2DBis;
        connect(fenetreRegle2D,SIGNAL(envoiRegle(std::vector<std::vector<unsigned short int> >,std::vector<std::string>)),this,SLOT(changeRegle(std::vector<std::vector<unsigned short int> >,std::vector<std::string>)));
    }

};

#endif // AUTOCELL_H
