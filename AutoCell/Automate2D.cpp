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
    int largeur =dep.getLargeur(), hauteur =dep.getHargeur(), nbRegle = m_regle.size(), i =0, nbCel=0;
    bool sol = false;

    for (int iC = 0;iC<hauteur;iC++){
        for (int jC=0;jC<largeur;jC++){
            while(i != nbRegle && sol == false){ // tant qu'il y a des règles et qu'on a pas trouvé de solution
                if(dep.getCellule(iC,jC) == m_regle[i][0]){
                    nbCel = nbCellule(iC,jC,dep,m_regle[i][1]);

                    if(m_regle[i][2] == 0 ){
                        if( m_regle[i][3]<= nbCel && nbCel <= m_regle[i][4] ){
                            dep.setCellule(iC,jC,i);
                            sol = true;
                        }
                    }
                    else{
                        if( m_regle[i][4]<= nbCel && nbCel <= m_regle[i][3] ){
                            dep.setCellule(iC,jC,i);
                            sol = true;
                        }
                    }
                }
                i++;
            }
            if(sol == false){
                dest.setCellule(iC,jC,dep.getCellule(iC,jC));
            }
            else{
                sol=false;
            }
            i=0;
        }
    }

}

