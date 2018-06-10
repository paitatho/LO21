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
    unsigned int getNbEtat() const {return nbEtat;}
    void setTaille(unsigned int t){taille =t;adjustTaille();adjustSize();}
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
    virtual void initSym()=0;
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
    virtual void initSym();
    const QTableWidget* get_etats() const {return etats;}
    void setEtats(unsigned int i, unsigned int j, QString color){
        etats->item(i,j)->setBackgroundColor(QColor(color));
    }

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
    const QSpinBox* get_nbEtat() const {return nbEtat;}
    const QComboBox* get_regleBase() const{return regleBase;}
    const std::vector<QSpinBox*>& get_etatCellulePourAppliquer() const {return etatCellulePourAppliquer;}
    const std::vector<QSpinBox*>& get_celluleACCompter() const {return celluleACCompter;}
    const std::vector<QComboBox*>& get_interval() const {return interval;}
    const std::vector<QSpinBox*>& get_borneInf() const {return borneInf;}
    const std::vector<QSpinBox*>& get_borneSup() const {return borneSup;}
    const std::vector<QComboBox*>& get_couleur() const {return couleur;}
    const std::vector<std::string>& get_couleurNom() const {return couleurNom;}
    void setRegleBase(const QString& s){regleBase->setCurrentText(s);}
    void setNbEtat(unsigned int n){nbEtat->setValue(n);}
    void setEtatCellulePourAppliquer(unsigned int i, unsigned int n){
        etatCellulePourAppliquer[i]->setValue(n);
    }
    void setCelluleACompter(unsigned int i, unsigned int n){
        celluleACCompter[i]->setValue(n);
    }
    void setInterval(unsigned int i, const QString& s){
        interval[i]->setCurrentText(s);
    }
    void setBorneInf(unsigned int i, unsigned int n){
        borneInf[i]->setValue(n);
    }
    void setBorneSup(unsigned int i, unsigned int n){
        borneSup[i]->setValue(n);
    }
    void setCouleur(unsigned int i, const QString& s){
        couleur[i]->setCurrentText(s);
    }
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
