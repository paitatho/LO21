#include "Automate2D.h"
#include <iostream>

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

bool Automate2D::appliquerTransition(const Etat2D& dep, Etat2D& dest) const{
    if((dep.getLargeur() != dest.getLargeur()) || (dep.getHauteur() != dest.getHauteur()))
      dest=dep;
    int largeur =dep.getLargeur(), hauteur =dep.getHauteur(), nbRegle = m_regle.size(), i =0, nbCel=0;
    bool sol = false;
    bool changement =false;
    for (int iC = 0;iC<hauteur;iC++){
        for (int jC=0;jC<largeur;jC++){
            while(i != nbRegle && sol == false){ // tant qu'il y a des règles et qu'on a pas trouvé de solution
                if(dep.getCellule(iC,jC) == m_regle[i][0]){
                    nbCel = nbCellule(iC,jC,dep,m_regle[i][1]);
                    if(m_regle[i][2] == 1 ){
                        if( m_regle[i][3]<= nbCel && nbCel <= m_regle[i][4] ){
                            dest.setCellule(iC,jC,i);
                            sol = true;
                            if(i != dep.getCellule(iC,jC))changement=true;
                        }
                    }
                    else{
                        if( m_regle[i][4]< nbCel || nbCel < m_regle[i][3] ){
                            dest.setCellule(iC,jC,i);
                            sol = true;
                            if(i != dep.getCellule(iC,jC))changement=true;
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
    return changement;
}


/*#############-AutomateManager2D-###############################*/

bool operator==(const std::vector< std::vector<unsigned short int> >& a,const std::vector< std::vector<unsigned short int> >& b){
    int ligneA = a.size();int ligneB = b.size();
    if (ligneA == ligneB){
            for(int i=0; i<ligneA;i++){
                int colonneA = a[i].size();int colonneB = b[i].size();
                if(colonneA == colonneB){
                    for(int j=0;j<colonneA;j++){
                        if(a[i][j] != b[i][j])return false;
                    }
                }else return false;
            }
    }
    else return false;

    return true;
}


AutomateManager2D* AutomateManager2D::m_AutomateManager2D = nullptr;

AutomateManager2D::AutomateManager2D(){}

AutomateManager2D::~AutomateManager2D(){
  for (int i=0;i<m_tabAutomate.size();i++){
    delete m_tabAutomate[i];
  }
}
AutomateManager2D& AutomateManager2D::getInstance(){
  if(AutomateManager2D::m_AutomateManager2D == nullptr){
    AutomateManager2D::m_AutomateManager2D= new AutomateManager2D();
    return *AutomateManager2D::m_AutomateManager2D;
  }
  else
    return *AutomateManager2D::m_AutomateManager2D;
}
void AutomateManager2D::freeIstance(){
  delete AutomateManager2D::m_AutomateManager2D;
}

const Automate2D& AutomateManager2D::getAutomate(std::vector< std::vector<unsigned short int> > regle, unsigned short int nbEtat){
  for (int i=0; i<m_tabAutomate.size();i++){
    if(m_tabAutomate[i]->getRegle()==regle && m_tabAutomate[i]->getNbEtat() == nbEtat)
      return *m_tabAutomate[i];
  }
  Automate2D* a = new Automate2D(regle,nbEtat);
  m_tabAutomate.push_back(a);
  return *a;
}




