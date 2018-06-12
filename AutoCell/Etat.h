#ifndef ETAT_H
#define ETAT_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

/*!
 * \file Etat.h
 * \brief Permet de généraliser un Etat
 * \version 1.0
 */


/*! \class  Etat
 * \brief Classe abstraite.
          La classe permet de généraliser un Etat
 */

class Etat
{
protected:
    unsigned int m_largeur; /*!< largeur de l'état*/
    unsigned int m_nbEtat;  /*!< nombre d'état d'une cellule*/
public:
    /*! \brief Constructeur
        \param nbCel : largeur: unsigned int
        \param nbEtat : nombre d'état :unsigned int */
    Etat(unsigned int nbCel, unsigned int nbEtat =2): m_largeur(nbCel),m_nbEtat(nbEtat){}

    /*! \brief Destructeur */
    virtual ~Etat(){}

    /*! \brief Accesseur en lecture
        \return m_largeur : unsigned int */
    unsigned int getLargeur()const {return m_largeur;}

    /*! \brief change la largeur
        \param l : nouvelle largeur :unsigned int */
    void setLargeur(unsigned int l){m_largeur = l;}

    /*! \brief Accesseur en lecture
        \return m_nbEtat : unsigned int */
    unsigned int getNbEtat() const {return m_nbEtat;}

    /*! \brief Accesseur en lecture
     *          méthode virtuelle pure*/
    virtual unsigned int getHauteur() const = 0;

    /*! \brief Ajuste la taille de l'état
     *          méthode virtuelle pure*/
    virtual void adjustEtat() =0;

    /*! \brief affiche un état dans la sortier standard
     *          méthode virtuelle pure*/
    virtual void afficher() const =0;
};

#endif // ETAT_H
