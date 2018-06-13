#include "Etat1D.h"

using namespace std;

Etat1D::Etat1D(unsigned int taille,unsigned int nbEtat) : Etat(taille,0,nbEtat){
  for (int i=0;i<m_largeur;i++)
    m_tab.push_back(false);
}
Etat1D::Etat1D(Etat1D const& etat) : Etat(etat.getLargeur(),etat.getNbEtat()){
  for (int i=0;i<m_largeur;i++)
    m_tab.push_back(etat.m_tab[i]);
}

unsigned int Etat1D::getDimension() const{
  return m_largeur;
}
bool Etat1D::getCellule(unsigned int i)const{
  if (i>=0 && i< m_largeur)
    return m_tab[i];
  else
    throw "truc";
}
void  Etat1D::setCellule(unsigned int i, bool val){
  if (i>=0 && i< m_largeur)
    m_tab[i] = val;
  else
    throw "truc";
}

ostream &operator<<(ostream& flux, const Etat1D& etat){
  int taille = etat.getDimension();
  for (int i = 0; i<taille;++i){
    if (etat.getCellule(i) == true) flux<< "X";
    else flux << " ";
  }
  return flux;
}

Etat1D& Etat1D::operator=(const Etat1D& etat){
  if (m_largeur == etat.m_largeur){
    for (int i = 0; i<m_largeur;i++)
      m_tab[i]=etat.m_tab[i];
  }
  else {
    m_tab.clear();
    m_largeur =  etat.m_largeur;
    for (int i = 0; i<m_largeur;i++)
      m_tab.push_back(etat.m_tab[i]);
  }
  return *this;
}
