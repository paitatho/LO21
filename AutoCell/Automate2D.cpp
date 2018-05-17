#include "Automate2D.h"

int Automate2D::nbCellule(unsigned int i,unsigned int j, Etat2D const& etat, unsigned short int etatCel) const{

    int nb=0;
    int x=etat.getLargeur();
    int y=etat.getHauteur();
    for (int h=-1;h<=1;h++){
        for (int k=-1;k<=1;k++){
            if (etat.getCellule((i+h+y)%y,(j+k+x)%x) == etatCel) ++nb;
        }
    }
    if (etat.getCellule(i,j) == etatCel) --nb;

    return nb;
}

void Automate2D::appliquerTransition(const Etat2D& dep, Etat2D& dest) const{



}

