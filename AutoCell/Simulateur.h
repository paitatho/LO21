#ifndef SIMULATEUR_H
#define SIMULATEUR_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <iostream>
#include <string>
#include <vector>

class Etat;
template<class T>class Automate;
template<class T1, class T2> class Simulateur;
class AutomateException;

template<class T1, class T2> class Simulateur{
    const T1 & m_automate;
    std::vector<T2 *> m_etats;
    const T2 * m_depart;
    unsigned int m_nbMaxEtats;
    unsigned int m_rang=0;
    void build(unsigned int c);// elle manipule le tableau etats (allocation de l'espace mémoire)
    Simulateur(const Simulateur&) = delete;
    Simulateur& operator=(const Simulateur&);
public:
    Simulateur (const T1 & a,unsigned int buffer=2);
    Simulateur (const T1 & a, const T2 & dep, unsigned int buffer=2 );
    void setEtatDepart(const T2 & e);
    void run (unsigned int nb);//génère les n prochains états
    void next(); // génère le prochain état
    const T2 & dernier() const;
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
            T2& operator*() const {
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
            const T2& operator*() const {
                return *sim->m_etats[i%sim->m_nbMaxEtats];
            }
            bool operator!=(const_iterator it) const { return sim != it.sim || i != it.i; }
        };

        const_iterator begin() const { return const_iterator(this); }
        const_iterator end() const { if (m_rang < m_nbMaxEtats) return const_iterator(this, -1); else return const_iterator(this, m_rang - m_nbMaxEtats); }
        const_iterator cbegin() const { return const_iterator(this); }
        const_iterator cend() const { if (m_rang < m_nbMaxEtats) return const_iterator(this, -1); else return const_iterator(this, m_rang - m_nbMaxEtats); }
};

#endif // SIMULATEUR_H
