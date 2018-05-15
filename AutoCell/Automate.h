
#ifndef AUTOMATE_H_INCLUDED
#define AUTOMATE_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

class Etat;
class Automate;
class Simulateur;
class AutomateException;

short unsigned int NumBitToNum(const std::string& num);
std::string NumToNumBit(short unsigned int num);
std::ostream &operator<<(std::ostream& flux, const Etat& etat);
std::ostream &operator<<(std::ostream& flux, const Automate& automate);

class Automate
{
    friend class AutomateManager;
private:
    short unsigned int m_numero;
    std::string m_numeroBit;
    Automate(short unsigned int num);
    Automate(const std::string& numBit);

public:
    int getNumero() const;
    std::string getNumeroBit() const;
    void appliquerTransition(const Etat& dep, Etat& dest) const;
    void afficher() const;

};

class AutomateManager
{
private:
  static AutomateManager* m_automateManager;
  std::vector<Automate*> m_tabAutomate;
protected:
    AutomateManager();
    ~AutomateManager();
    AutomateManager(const AutomateManager&) = delete;
    AutomateManager& operator=(const AutomateManager&);
public:
  static AutomateManager& getInstance();
  static void freeIstance();
  const Automate& getAutomate(short unsigned int num);
  const Automate& getAutomate(const std::string& numbit);
};

class AutomateException {
    public:
        AutomateException(const std::string& message):info(message) {}
        std::string getInfo() const { return info; }
    private:
        std::string info;
};


class Etat
{
    friend class Automate;
     protected:
        unsigned int m_nbCellule;
        std::vector<bool> m_tab;

    public:
        Etat(unsigned int taille = 0);
        Etat(Etat const& etat);
        virtual ~Etat();
        unsigned int getDimension() const;
        bool getCellule(unsigned int i)const;
        void setCellule(unsigned int i, bool val);
        void afficher() const;
        Etat& operator=(const Etat& etat);
    private:
};


#endif // AUTOMATE_H_INCLUDED
