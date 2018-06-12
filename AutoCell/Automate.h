#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <QtWidgets>
#include <QThread>
#include<QTime>
#include<iostream>
#include <string>
#include <vector>

/*!
 * \file Automate.h
 * \brief Structure de Base d'un Automate
 * \version 1.0
 */


/*! \class Automate
 * \brief Classe Template abstraite
 *
 *  La classe généralise un Automate et définie la méthodes virtuelle qui devra être présente et définie dans chaque Automate. (runSim())
 */

template<class T>class Automate     // classe abstraite
{
private:
    unsigned short int m_nbEtat; /*!< Nombre d'état*/
public:
    /*! \brief Constructeur
     *  \param nbEtat nombre d'états que peut prendre chaque cellule (2 par défaut): unsigned short int*/
    Automate(unsigned short int nbEtat =2) : m_nbEtat(nbEtat){}

    /*! \brief change le nombre d'état
     *  \param e : nouveau nombre d'état :unsigned short int*/
    void setNbEtat(unsigned short int e){m_nbEtat = e;}

    /*! \brief retourne le nombre d'état
     *  \return m_nbEtat : unsigned short int*/
    unsigned short int getNbEtat() const {return m_nbEtat;}

    /*! \brief applique la transition entre deux quelconques donnés en paramètre
     *          Méthode virtuelle pure
     *  \param depart : const T&
        \param destination : T&*/
    virtual void appliquerTransition(const T& , T&) const = 0; // méthode virtuelle pure
};

#endif // AUTOMATE_H
