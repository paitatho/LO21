#ifndef ETAT_H
#define ETAT_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class Etat
{
protected:
    unsigned int m_nbCellule;
    unsigned int m_nbEtat;
public:
    Etat(unsigned int nbCel, unsigned int nbEtat =1): m_nbCellule(nbCel),m_nbEtat(nbEtat){}
    virtual ~Etat(){}
    unsigned int getLargeur()const {return m_nbCellule;}
    void setLargeur(unsigned int l){m_nbCellule = l;}
    unsigned int getNbEtat() const {return m_nbEtat;}
    virtual unsigned int getHauteur() const = 0;
    virtual unsigned int adjustEtat() =0;
};

#endif // ETAT_H
