#include "Simulateur.h"
#include "Automate.h"
#include <iostream>
using namespace std;

Simulateur::Simulateur (const Automate & a,unsigned int buffer) : m_nbMaxEtats(buffer), m_automate(a){
  for (int i=0; i<m_nbMaxEtats;i++)
    m_etats.push_back(nullptr);
}
Simulateur::Simulateur (const Automate & a, const Etat & dep, unsigned int buffer) : m_nbMaxEtats(buffer), m_automate(a), m_depart(&dep){
  for (int i=0; i<m_nbMaxEtats;i++)
    m_etats.push_back(nullptr);
  m_etats[0] = new Etat(dep);
}
void Simulateur::setEtatDepart(const Etat & e){
  m_depart = &e;
  m_etats[0] = new Etat(e);
  reset();
}
void Simulateur::run (unsigned int nb){  //génère les n prochains états
  for( int i=0;i<nb;i++){
    next();
  }
}
void Simulateur::next(){// génère le prochain état
  Etat* e = new Etat();
  m_automate.appliquerTransition(*m_etats[m_rang%m_nbMaxEtats], *e);
  ++m_rang;
  m_etats[m_rang%m_nbMaxEtats]= e;
}
const Etat & Simulateur::dernier() const{
  return *m_etats[m_rang%m_nbMaxEtats];
}
void Simulateur::reset(){//revenir à l'état de départ
  m_rang=0;
  *(m_etats[0])= *m_depart;
}
Simulateur::~Simulateur(){
  for (int i=0;i<m_nbMaxEtats;i++)
    delete m_etats[i];
}
