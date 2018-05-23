
#ifndef AUTOMATE1D_H_INCLUDED
#define AUTOMATE1D_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Automate.h"
#include "Etat.h"
class Etat1D;
class Automate1D;
template<class T>class Automate;
template<class T1, class T2> class Simulateur;
class AutomateException;

short unsigned int NumBitToNum(const std::string& num);
std::string NumToNumBit(short unsigned int num);
std::ostream &operator<<(std::ostream& flux, const Etat1D& etat);
std::ostream &operator<<(std::ostream& flux, const Automate1D& automate);

class Automate1D : public Automate<Etat1D>
{
    friend class AutomateManager;
private:
    short unsigned int m_numero;
    std::string m_numeroBit;
    Automate1D(short unsigned int num,unsigned short int nbEtat=2);
    Automate1D(const std::string& numBit,unsigned short int nbEtat=2);

public:
    int getNumero() const;
    std::string getNumeroBit() const;
    void appliquerTransition(const Etat1D& dep, Etat1D& dest) const;
    void afficher() const;
};

class AutomateManager
{
private:
  static AutomateManager* m_automateManager;
  std::vector<Automate1D*> m_tabAutomate;
protected:
    AutomateManager();
    ~AutomateManager();
    AutomateManager(const AutomateManager&) = delete;
    AutomateManager& operator=(const AutomateManager&);
public:
  static AutomateManager& getInstance();
  static void freeIstance();
  const Automate1D& getAutomate(short unsigned int num);
  const Automate1D& getAutomate(const std::string& numbit);
};

class AutomateException {
    public:
        AutomateException(const std::string& message):info(message) {}
        std::string getInfo() const { return info; }
    private:
        std::string info;
};


class Etat1D : public Etat
{
    friend class Automate1D;
     protected:
        std::vector<bool> m_tab;

    public:
        Etat1D(unsigned int taille = 0,unsigned int nbEtat = 2);
        Etat1D(Etat1D const& etat);
        virtual ~Etat1D(){}
        unsigned int getDimension() const;
        bool getCellule(unsigned int i)const;
        void setCellule(unsigned int i, bool val);
        void afficher() const;
        Etat1D& operator=(const Etat1D& etat);
        virtual unsigned int getHauteur() const{return 1;}
        virtual void adjustEtat(){
            int taille=m_tab.size();
            if (taille < m_largeur){
                for(int i =taille;i<m_largeur;i++)
                    m_tab.push_back(false);
            }
            else{
                for(int i =taille;i>=m_largeur; i--)
                    m_tab.pop_back();
            }
        }
};


#endif // AUTOMATE1D_H_INCLUDED
