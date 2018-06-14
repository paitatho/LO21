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
    bool changement=false;          /*!< booléen qui indique si il y a eu des changements lors de la dernière simulation*/

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

    /*! \brief  indique si après une similation il y a bien au des modifications entre etat de départ et d'arrivé
        \return changement : bool*/
    bool getChangement() const{return changement;}

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

        /*! \class  const_iterator
         * \brief permet le parcourt des états dans simulateur const*/
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


#endif // SIMULATEUR_H
