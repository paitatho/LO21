#include "Etat2D.h"
#include <iostream>

void Etat2D::adjustEtat(){
    m_valeur.clear();
    for(unsigned int i = 0; i<m_hauteur ; i++){
        m_valeur.push_back(std::vector<unsigned short int>(m_largeur,0));
    }
}

void Etat2D::afficher() const{
    std::cout<<std::endl;
    for(unsigned int i=0;i<m_largeur;i++){
        for (unsigned int j=0;j<m_hauteur;j++){
            std::cout<<m_valeur[i][j];
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}
