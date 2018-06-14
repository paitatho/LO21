#ifndef ETAT2D_H
#define ETAT2D_H

#include "Etat.h"
#include <vector>

/*!
 * \file Etat2D.h
 * \brief Classe pour représenter un état à 2 dimensions
 * \version 1.0
 */


/*! \class  Etat2D
 * \brief hérite de Etat.
          Permet de créer des états à 2 dimensions
 */
class Etat2D : public Etat
{
protected:
    std::vector<std::vector<unsigned short int>> m_valeur;/*!< représente la grille de cellule*/

public:
    /*! \brief Constructeur
     *  \param l : largeur : unsigned int
        \param h : hauteur: unsigned int
        \param nbEtat : nombre d'état :unsigned int */
    Etat2D(unsigned int l =0, unsigned int h =0, unsigned int nbEtat=2): Etat(l,h,nbEtat){
        for(int i = 0; i<h ; i++){
            m_valeur.push_back(std::vector<unsigned short int>(m_largeur,0));
        }
    }

    /*! \brief Destructeur */
    virtual ~Etat2D(){}

    /*! \brief affiche l'état*/
    void afficher() const;

    /*! \brief modifie la valeur d'une cellule
        \param i : ligne : unsigned int
        \param j : colonne : unsigned int
        \param val : nouvelle valeur : unsigned int*/
    void setCellule(unsigned int i, unsigned int j, unsigned short int val){
        m_valeur[i][j] = val;
    }

    /*! \brief Accesseur en lecture
     *  \param i : ligne : unsigned int
        \param j : colonne : unsigned int
     *  \return m_valeur[i][j] : unsigned short int*/
    unsigned short int getCellule(unsigned int i, unsigned int j) const {return m_valeur[i][j]; }

    /*! \brief ajuste la taille de l'etat*/
    virtual void adjustEtat();

    /*! \brief opérateur d'affectation
        \param e : état à copier :const Etat2D& */
    bool operator==(const Etat2D& e) const{
        bool sol=true;
        for(int i=0;i<m_hauteur;i++){
            for(int j=0;j<m_largeur;j++){
                if(m_valeur[i][j] != e.m_valeur[i][j]) sol =false;
            }
        }
        return sol;
    }

};

#endif // ETAT2D_H
