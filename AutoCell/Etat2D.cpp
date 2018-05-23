#include "Etat2D.h"

unsigned int Etat2D::adjustEtat(){
    m_valeur.clear();
    for(int i = 0; i<m_hauteur ; i++){
        m_valeur.push_back(std::vector<unsigned short int>(m_nbCellule,0));
    }
}

