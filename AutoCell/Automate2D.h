#ifndef AUTOMATE2D_H
#define AUTOMATE2D_H

#include <QtWidgets>
#include "Automate.h"
#include "Etat2D.h"
/*
 *  l'automate 2D de base permettra de gérer des règles du type :
 *      -on passe à un état i si il y a entre X et Y cellules dans l'état j dans l'entourage de notre cellule
 *      -on passe à un état i si il n' y a pas entre X et Y cellules dans l'état j dans l'entourage de notre cellule
 *
 *  m_regle[i] stock la règle qui permet de passer à l'état i
 *  m_regle[i][0] stock l'état que doit avoir la cellule pour qu'on lui applique la règle
 *  m_regle[i][1] stock l'état que doivent avoir les cellules alentours pour être comptées (ex : 3 cellule vivante(etat 1))
 *  m_regle[i][2] vaut 1 si nbCellule doit être dans l'interval pour passer à i, vaut 0 si nbCellule doit être hors de l'interval pour passer à i
 *  m_regle[i][3] et m_regle[i][4] interval des régles ( peut être différent, c'est au programmeur de choisir en faisant une classe fille (redéfinir appliquerTransition dans ce cas)
 *
 *  Si on veut instancier un JDLV il suffit de mettre dans m_regle:
 *      -m_regle[0] = [1,1,0,2,3]   Une cellule vivante ne possédant pas entre 2 et 3 voisines vivantes meurt.
 *      <=> une cellule meurt (etat 0) si elle est vivante( etat 1) et qu'il n'y a pas entre 2 et 3 cellule vivante autour
 *      -m_regle[1] = [0,1,1,3,3]    Une cellule morte possédant 3 voisines vivantes devient vivante
 */

/*!
 * \file Automate2D.h
 * \brief Implémente l'automate 2D ainsi que les Etats 2D
 * \version 1.0
 */


/*! \class  Automate2D
 * \brief hérite de Automate<Etat2D>.
            La classe permet d'appliquer une transition sur les Etat2D en suivant des règles
 */
class Automate2D : public Automate<Etat2D>
{

private:
    std::vector< std::vector<unsigned short int> > m_regle; /*!< représente les règles de transitions*/

public:
    /*! \brief Constructeur Privée
     *  \param regle : std::vector< std::vector<unsigned short int> >
        \param nbEtat : nombre d'état : unsigned short int*/
    Automate2D(std::vector< std::vector<unsigned short int> > regle = std::vector< std::vector<unsigned short int> >(), unsigned short int nbEtat = 2): Automate(nbEtat), m_regle(regle){}

    /*! \brief Destructeur virtuel*/
    virtual ~Automate2D(){}

    /*! \brief accesseur lecture
     *  \return m_regle : std::vector< std::vector<unsigned short int> >*/
    std::vector< std::vector<unsigned short int> > getRegle() const {return this->m_regle;}

    /*! \brief modifie la règle
     *  \param newRegle : std::vector< std::vector<unsigned short int> > const&*/
    void setRegle(std::vector< std::vector<unsigned short int> > const& newRegle){m_regle = newRegle;}

    /*! \brief applique la transition entre 2 Etats en fonction de la règle
     *  \param dep : const Etat2D&
        \param dest : Etat2D&*/
    virtual void appliquerTransition(const Etat2D& dep, Etat2D& dest) const;

    /*! \brief compte le nombre de cellules alentours dans l'état etatCel
     *  \param i : unsigned int
     *  \param j : unsigned int
     *  \param etat : const Etat2D&
        \param etatCel : unsigned short int*/
    int nbCellule(unsigned int i,unsigned int j, Etat2D const& etat, unsigned short int etatCel) const; // etatCel nous indique quel est l'état des cellules qu'on devra compter

};




#endif // AUTOMATE2D_H
