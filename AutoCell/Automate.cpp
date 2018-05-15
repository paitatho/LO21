#include "Automate.h"
#include <iostream>
using namespace std;

short unsigned int NumBitToNum(const std::string& num) {
  if (num.size() != 8) throw AutomateException("Numero d’automate indefini");
  int puissance = 1;short unsigned int numero = 0;
  for (int i = 7; i >= 0; i--) {
    if (num[i] == '1') numero += puissance;
    else if (num[i] != '0') throw AutomateException("Numero d’automate indefini");
    puissance *= 2;
  }
  return numero;
  }

std::string NumToNumBit(short unsigned int num) {
  std::string numeroBit;
  if (num > 256) throw AutomateException("Numero d’automate indefini");
  unsigned short int p = 128;
  int i = 7;
  while (i >= 0) {
    if (num >= p) { numeroBit.push_back('1'); num -= p; }
    else { numeroBit.push_back('0'); }
    i--;
    p = p / 2;
  }
return numeroBit;
}

/*#############-Etat-###############################*/



Etat::Etat(unsigned int taille) : m_nbCellule(taille){
  for (int i=0;i<m_nbCellule;i++)
    m_tab.push_back(false);
}
Etat::Etat(Etat const& etat) : m_nbCellule(etat.m_nbCellule){
  for (int i=0;i<m_nbCellule;i++)
    m_tab.push_back(etat.m_tab[i]);
}

Etat::~Etat(){}

unsigned int Etat::getDimension() const{
  return m_nbCellule;
}
bool Etat::getCellule(unsigned int i)const{
  if (i>=0 && i< m_nbCellule)
    return m_tab[i];
  else
    throw "truc";
}
void  Etat::setCellule(unsigned int i, bool val){
  if (i>=0 && i< m_nbCellule)
    m_tab[i] = val;
  else
    throw "truc";
}

ostream &operator<<(ostream& flux, const Etat& etat){
  int taille = etat.getDimension();
  for (int i = 0; i<taille;++i){
    if (etat.getCellule(i) == true) flux<< "X";
    else flux << " ";
  }
  return flux;
}

Etat& Etat::operator=(const Etat& etat){
  if (m_nbCellule == etat.m_nbCellule){
    for (int i = 0; i<m_nbCellule;i++)
      m_tab[i]=etat.m_tab[i];
  }
  else {
    m_tab.clear();
    m_nbCellule =  etat.m_nbCellule;
    for (int i = 0; i<m_nbCellule;i++)
      m_tab.push_back(etat.m_tab[i]);
  }
}

/*#############-Automate-###############################*/

Automate::Automate(short unsigned int num): m_numero(num), m_numeroBit(NumToNumBit(num)){}

Automate::Automate(const std::string& numBit): m_numeroBit(numBit), m_numero(NumBitToNum(numBit)){}

int Automate::getNumero() const{
  return m_numero;
}
std::string Automate::getNumeroBit() const{
  return m_numeroBit;
}
void Automate::appliquerTransition(const Etat& dep, Etat& dest) const{
  if(dep.getDimension()!=dest.getDimension())
    dest=dep;
  for(unsigned int i=0;i<dep.getDimension();i++)
  {
    unsigned int conf=0;
    if(i>0) conf+= dep.getCellule(i-1)*4;
    conf+=dep.getCellule(i)*2;
    if(i<dep.getDimension()-1)
      conf+=dep.getCellule(i+1);
    dest.setCellule(i,m_numeroBit[7-conf]-'0');
  }

}

ostream &operator<<(ostream& flux, const Automate& automate){
  flux << "Automate: " << automate.getNumero() << " " << automate.getNumeroBit();
  return flux;
}

/*#############-AutomateManager-###############################*/

AutomateManager* AutomateManager::m_automateManager = nullptr;

AutomateManager::AutomateManager(){}

AutomateManager::~AutomateManager(){
  for (int i=0;i<m_tabAutomate.size();i++){
    delete m_tabAutomate[i];
  }
}
AutomateManager& AutomateManager::getInstance(){
  if(AutomateManager::m_automateManager == nullptr){
    AutomateManager::m_automateManager= new AutomateManager();
    return *AutomateManager::m_automateManager;
  }
  else
    return *AutomateManager::m_automateManager;
}
void AutomateManager::freeIstance(){
  delete AutomateManager::m_automateManager;
}

const Automate& AutomateManager::getAutomate(short unsigned int num){
  for (int i=0; i<m_tabAutomate.size();i++){
    if(m_tabAutomate[i]->getNumero()==num)
      return *m_tabAutomate[i];
  }
  Automate* a = new Automate(num);
  m_tabAutomate.push_back(a);
  return *a;
}
const Automate& AutomateManager::getAutomate(const std::string& numbit){
  for (int i=0; i<m_tabAutomate.size();i++){
    if(m_tabAutomate[i]->getNumeroBit()==numbit)
      return *m_tabAutomate[i];
  }
  Automate* a = new Automate(numbit);
  m_tabAutomate.push_back(a);
  return *a;
}

/*#############-Simulateur-###############################*/

