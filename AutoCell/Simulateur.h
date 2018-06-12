#ifndef SIMULATEUR_H
#define SIMULATEUR_H

#include <QtWidgets>
#include <iostream>
#include <string>
#include <vector>

/*!
 * \file Simulateur.h
 * \brief
 * \version 1.0
 */


/*! \class  Simulateur
 * \brief Classe template.
          Permet de gérer la simulation de n'importe quel automate héritant de la Classe Automate
 */


template<class T>class Automate;
template<class T1, class T2> class Simulateur;
class AutomateException;

template<class T1, class T2> class Simulateur{
    const T1 & m_automate;          /*!< référence vers un automate*/
    std::vector<T2 *> m_etats;      /*!< tableau d'états que l'automate peut gérer*/
    const T2 * m_depart;            /*!< états de départ*/
    unsigned int m_nbMaxEtats;      /*!< nombre maximum d'état stocké dans le tableau*/
    unsigned int m_rang=0;          /*!< rang du dernier état dans le tableau*/


    //void build(unsigned int c);

    /*! \brief  suppression constructeur de recopie*/
    Simulateur(const Simulateur&) = delete;

    /*! \brief  operateur d'affectation en privée*/
    Simulateur& operator=(const Simulateur&);
public:
    /*! \brief Constructeur
        \param a : automate : const T1&
        \param buffer : taille attribut m_etats : unsigned int*/
    Simulateur (const T1 & a,unsigned int buffer=2);

    /*! \brief Constructeur
        \param a : automate : const T1&
        \param dep : état départ :const T2 &
        \param buffer : taille attribut m_etats : unsigned int*/
    Simulateur (const T1 & a, const T2 & dep, unsigned int buffer=2 );

    /*! \brief destructeur*/
    ~Simulateur();

    /*! \brief  modifie état de départ
        \param e : const T2 &*/
    void setEtatDepart(const T2 & e);

    /*! \brief génère les n prochains états
        \param nb : unsigned int*/
    void run (unsigned int nb);

    /*! \brief génère le  prochain état*/
    void next(); // génère le prochain état

    /*! \brief accesseur lecture
        \return etat : dernier etat: const T2 &*/
    const T2 & dernier() const;

    /*! \brief accesseur lecture
        \return etat : avant dernier etat: const T2 &*/
    const T2 & avantDernier() const;

    /*! \brief accesseur lecture
        \return m_rang : unsigned int */
    unsigned int getRangDernier() const {return m_rang;}

    /*! \brief revient à l'état de départ*/
    void reset();


    /*! \class  iterator
     * \brief permet le parcourt des états
     */
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
