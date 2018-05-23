#ifndef ETAT_H
#define ETAT_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class Etat
{
protected:
    unsigned int m_largeur;
    unsigned int m_nbEtat;
public:
    Etat(unsigned int nbCel, unsigned int nbEtat =2): m_largeur(nbCel),m_nbEtat(nbEtat){}
    virtual ~Etat(){}
    unsigned int getLargeur()const {return m_largeur;}
    void setLargeur(unsigned int l){m_largeur = l;}
    unsigned int getNbEtat() const {return m_nbEtat;}
    virtual unsigned int getHauteur() const = 0;
    virtual void adjustEtat() =0;
};

#endif // ETAT_H
