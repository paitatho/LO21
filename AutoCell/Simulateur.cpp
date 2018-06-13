#include "Simulateur.h"
#include "Automate1D.h"
#include "Automate2D.h"
#include "Etat2D.h"
#include <iostream>
using namespace std;

template<class T1, class T2> Simulateur<T1,T2>::Simulateur (const T1 & a,unsigned int buffer) : m_nbMaxEtats(buffer), m_automate(a){
  for (int i=0; i<m_nbMaxEtats;i++)
    m_etats.push_back(nullptr);
}
template<class T1, class T2> Simulateur<T1,T2>::Simulateur (const T1& a, const T2 & dep, unsigned int buffer) : m_nbMaxEtats(buffer), m_automate(a),m_depart(&dep){
  for (int i=0; i<m_nbMaxEtats;i++)
    m_etats.push_back(nullptr);

  m_etats[0] = new T2(dep);
}
template<class T1, class T2> void Simulateur<T1,T2>::setEtatDepart(const T2 & e){
  if (m_automate.getNbEtat() == e.getNbEtat()){
      m_depart = &e;
      m_etats[0] = new T2(e);
      reset();
  }
}

template<class T1, class T2> void Simulateur<T1,T2>::run (unsigned int nb){  //génère les n prochains états
  for( int i=0;i<nb;i++){
    next();
  }
}

template<class T1, class T2> void Simulateur<T1,T2>::next(){// génère le prochain état
  T2* e = new T2();
  if (m_automate.appliquerTransition(*m_etats[m_rang%m_nbMaxEtats], *e) == false)changement=false;
  else changement =true;
  ++m_rang;
  m_etats[m_rang%m_nbMaxEtats]= e;
}

template<class T1, class T2> const T2 & Simulateur<T1,T2>::dernier() const{
  return *m_etats[m_rang%m_nbMaxEtats];
}

template<class T1, class T2> const T2 & Simulateur<T1,T2>::avantDernier() const{
  return *m_etats[(m_rang-1)%m_nbMaxEtats];
}

template<class T1, class T2> void Simulateur<T1,T2>::reset(){//revenir à l'état de départ
  m_rang=0;
  *(m_etats[0])= *m_depart;
}

template<class T1, class T2> Simulateur<T1,T2>::~Simulateur(){
  for (int i=0;i<m_nbMaxEtats;i++)
    delete m_etats[i];
}

template class Simulateur<Automate1D,Etat1D>;
template class Simulateur<Automate2D,Etat2D>;
