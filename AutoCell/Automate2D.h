#ifndef AUTOMATE2D_H
#define AUTOMATE2D_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "Automate.h"
#include "Etat2D.h"
/*
 *  On se base sur les règles du jeu de la vie pour construire l'automate 2D de base.
 *  Une cellule vivante ne possédant pas entre X et Y voisines vivantes meurt.
 *  Une cellule morte possédant entre A et B voisines vivantes devient vivante (elle naît).
 *  pour le cas précis du jeu de la vie on a A = B = 3 et X = 2 Y = 3
 *  X Y sont les règles pour passer à l'état mort = 0
 *  A B sont les règles pour passer à l'état mort = 1
 *  on stock donc dans m_regle[0] les règles X Y pour passer à l'état 0
 *  et dans m_regle[1] les règles A B pour passer à l'état 1
 *  Conclusion:
 *  m_regle[i] stock la règle qui permet de passer à l'état i
 *  m_regle[i][0] stock l'état que doit avoir la cellule pour qu'on lui applique la règle
 *  m_regle[i][1] stock l'état que doivent avoir les cellules pour être comptées (ex : 3 cellule vivant(etat 1))
 *  m_regle[i][2] vaut 0 si nbCellule doit être dans l'interval pour passer à i, vaut 1 si nbCellule doit être hors de l'interval pour passer à i
 *  m_regle[i][3] et m_regle[i][4] interval des régles ( peut être différent, c'est au programmeur de choisir en faisant une classe fille (redéfinir appliquerTransition dans ce cas)
 *
 */
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


#endif // AUTOMATE2D_H
