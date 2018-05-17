#ifndef AUTOMATE2D_H
#define AUTOMATE2D_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "Automate.h"
#include "Etat2D.h"

class Automate2D : public Automate<Etat2D>
{

private:
    std::vector< std::vector<unsigned short int> > m_regle;

public:
    Automate2D(std::vector< std::vector<unsigned short int> > regle = std::vector< std::vector<unsigned short int> >(), unsigned short int nbEtat = 1): Automate(nbEtat), m_regle(regle){}
    virtual ~Automate2D(){}
    std::vector< std::vector<unsigned short int> > getRegle() const {return this->m_regle;}
    void setRegle(std::vector< std::vector<unsigned short int> > const& newRegle){m_regle = newRegle;}
    virtual void appliquerTransition(const Etat2D& dep, Etat2D& dest) const;
    int nbCellule(unsigned int i,unsigned int j, Etat2D const& etat, unsigned short int etatCel) const; // etatCel nous indique quel est l'état des cellules qu'on devra compter

};

class JDLV : public Automate2D
{

};

#endif // AUTOMATE2D_H
