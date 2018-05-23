#ifndef ETAT2D_H
#define ETAT2D_H

#include "Etat.h"
#include <vector>
class Etat2D : public Etat
{
protected:
    std::vector<std::vector<unsigned short int>> m_valeur;
    unsigned int m_hauteur;
public:
    Etat2D(unsigned int l =0, unsigned int h =0, unsigned int nbEtat=2): Etat(l,nbEtat),m_hauteur(h){
        for(int i = 0; i<h ; i++){
            m_valeur.push_back(std::vector<unsigned short int>(m_largeur,0));
        }
    }
    ~Etat2D(){}
    unsigned int getHauteur() const {return m_hauteur;}
    void setHauteur(unsigned int h) {m_hauteur =h; this->adjustEtat();}
    unsigned short int getCellule(unsigned int i,unsigned j) const {return m_valeur[i][j];}
    void afficher() const;
    void setCellule(unsigned int i, unsigned int j, unsigned short int val){
        m_valeur[i][j] = val;
    }
    virtual void adjustEtat();
};

#endif // ETAT2D_H
