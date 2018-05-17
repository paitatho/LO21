#ifndef AUTOMATE2D_H
#define AUTOMATE2D_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "Etat2D.h"

class Automate2D
{

private:
    std::vector<unsigned int> m_regle;

public:
    Automate2D(std::vector<unsigned int> regle = std::vector<unsigned int>()): m_regle(regle){}
    std::vector<unsigned int> getRegle(){return this->m_regle;}
    void setRegle(std::vector<unsigned int>& newRegle){m_regle = newRegle;}
    //virtual void appliquerTransition(const Etat2D& dep, Etat2D& dest) const;
    int nbCelluleEnVie(unsigned int i,unsigned int j, Etat2D const& etat, unsigned int etatCel) const; // etatCel nous indique quel est l'état des cellules qu'on devra compter
};

class JDLV : public Automate2D
{

};

#endif // AUTOMATE2D_H
