#include "Automate1D.h"
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



/*#############-Automate-###############################*/

Automate1D::Automate1D(short unsigned int num,unsigned short int nbEtat): Automate(nbEtat),m_numero(num), m_numeroBit(NumToNumBit(num)){}

Automate1D::Automate1D(const std::string& numBit,unsigned short int nbEtat): Automate(nbEtat),m_numeroBit(numBit), m_numero(NumBitToNum(numBit)){}

int Automate1D::getNumero() const{
  return m_numero;
}
std::string Automate1D::getNumeroBit() const{
  return m_numeroBit;
}
bool Automate1D::appliquerTransition(const Etat1D& dep, Etat1D& dest) const{
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
  return true;

}

ostream &operator<<(ostream& flux, const Automate1D& automate){
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

const Automate1D& AutomateManager::getAutomate(short unsigned int num){
  for (int i=0; i<m_tabAutomate.size();i++){
    if(m_tabAutomate[i]->getNumero()==num)
      return *m_tabAutomate[i];
  }
  Automate1D* a = new Automate1D(num);
  m_tabAutomate.push_back(a);
  return *a;
}
const Automate1D& AutomateManager::getAutomate(const std::string& numbit){
  for (int i=0; i<m_tabAutomate.size();i++){
    if(m_tabAutomate[i]->getNumeroBit()==numbit)
      return *m_tabAutomate[i];
  }
  Automate1D* a = new Automate1D(numbit);
  m_tabAutomate.push_back(a);
  return *a;
}


