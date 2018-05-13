
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


class Simulateur{
	const Automate & m_automate;
	std::vector<Etat *> m_etats;
	const Etat * m_depart;
	unsigned int m_nbMaxEtats;
	unsigned int m_rang=0;
	void build(unsigned int c);// elle manipule le tableau etats (allocation de l'espace mémoire)
  Simulateur(const Simulateur&) = delete;
  Simulateur& operator=(const Simulateur&);
public:
	Simulateur (const Automate & a,unsigned int buffer=2);
	Simulateur (const Automate & a, const Etat & dep, unsigned int buffer=2 );
	void setEtatDepart(const Etat & e);
	void run (unsigned int nb);//génère les n prochains états
	void next(); // génère le prochain état
	const Etat & dernier() const;
	unsigned int getRangDernier() const {return m_rang;}
	void reset();//revenir à l'état de départ
	~Simulateur();
    class iterator {
            friend class Simulateur;
            Simulateur* sim;
            int i;
            iterator(Simulateur* s) :sim(s), i(s->m_rang) {}
            iterator(Simulateur* s, int dep) :sim(s), i(dep) {}
        public:
            iterator():sim(nullptr),i(0) {}
            iterator& operator++() {
                i--;
                if (i == -1 && sim->m_rang >= sim->m_nbMaxEtats) i = sim->m_nbMaxEtats - 1;
                return *this;
            }
            Etat& operator*() const {
                return *sim->m_etats[i%sim->m_nbMaxEtats];
            }
            bool operator!=(iterator it) const { return sim != it.sim || i != it.i; }
        };

        iterator begin() {	return iterator(this); }
        iterator end() { if (m_rang < m_nbMaxEtats) return iterator(this, -1); else return iterator(this, m_rang - m_nbMaxEtats);  }

        class const_iterator {
            friend class Simulateur;
            const Simulateur* sim;
            int i;
            const_iterator(const Simulateur* s) :sim(s), i(s->m_rang) {}
            const_iterator(const Simulateur* s, int dep) :sim(s), i(dep) {}
        public:
            const_iterator():sim(nullptr),i(0) {}
            const_iterator& operator++() {
                i--;
                if (i == -1 && sim->m_rang >= sim->m_nbMaxEtats) i = sim->m_nbMaxEtats - 1;
                return *this;
            }
            const Etat& operator*() const {
                return *sim->m_etats[i%sim->m_nbMaxEtats];
            }
            bool operator!=(const_iterator it) const { return sim != it.sim || i != it.i; }
        };

        const_iterator begin() const { return const_iterator(this); }
        const_iterator end() const { if (m_rang < m_nbMaxEtats) return const_iterator(this, -1); else return const_iterator(this, m_rang - m_nbMaxEtats); }
        const_iterator cbegin() const { return const_iterator(this); }
        const_iterator cend() const { if (m_rang < m_nbMaxEtats) return const_iterator(this, -1); else return const_iterator(this, m_rang - m_nbMaxEtats); }
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
