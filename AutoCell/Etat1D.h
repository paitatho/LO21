#ifndef ETAT1D_H
#define ETAT1D_H

#include <iostream>
#include <string>
#include <vector>
#include "Automate.h"
#include "Etat.h"


/*!
 * \file Etat1D.h
 * \brief Classe pour représenter un état à 1 dimensions
 * \version 1.0
 */


/*! \class Etat1D
 * \brief   hérite de Etat.
 *         Permet de créer de état à 1Dimension
 */
class Etat1D : public Etat
{
    friend class Automate1D;
    protected:
        std::vector<bool> m_tab;    /*!< Etat de la cellule*/

    public:
        /*! \brief Constructeur
            \param taille : nombre de cellule : unsigned int
            \param nbEtat : unsigned int*/
        Etat1D(unsigned int taille = 0,unsigned int nbEtat = 2);

        /*! \brief Constructeur par recopie*/
        Etat1D(Etat1D const& etat);

        /*! \brief Destructeur*/
        virtual ~Etat1D(){}

        /*! \brief accesseur lecture
            \return taille : unsigned int*/
        unsigned int getDimension() const;

        /*! \brief accesseur lecture
         *  \param i : indice :unsigned int
            \return valeur : bool*/
        bool getCellule(unsigned int i)const;


        /*! \brief accesseur écriture
         *  \param i : indice :unsigned int
         *  \param val : valeur : bool*/
        void setCellule(unsigned int i, bool val);

        /*! \brief affiche un Etat1D*/
        void afficher() const{}

        /*! \brief operateur de copie
         *  \param etat : const Etat1D&l
            \return Etat1D&*/
        Etat1D& operator=(const Etat1D& etat);

        /*! \brief méthode virtuelle
         *  \param etat : const Etat1D&l
            \return Etat1D&*/
        virtual unsigned int getHauteur() const{return 1;}

        /*! \brief méthode virtuelle
         *  modifie la taille de l'état*/
        virtual void adjustEtat(){
            int taille=m_tab.size();
            if (taille < m_largeur){
                for(int i =taille;i<m_largeur;i++)
                    m_tab.push_back(false);
            }
            else{
                for(int i =taille;i>=m_largeur; i--)
                    m_tab.pop_back();
            }
        }
};

#endif // ETAT1D_H
