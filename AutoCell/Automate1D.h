
#ifndef AUTOMATE1D_H_INCLUDED
#define AUTOMATE1D_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Automate.h"
#include "Etat.h"
#include "Etat1D.h"

class Automate1D;
template<class T>class Automate;
template<class T1, class T2> class Simulateur;
class AutomateException;

short unsigned int NumBitToNum(const std::string& num);
std::string NumToNumBit(short unsigned int num);
std::ostream &operator<<(std::ostream& flux, const Etat1D& etat);
std::ostream &operator<<(std::ostream& flux, const Automate1D& automate);

/*!
 * \file Automate1D.h
 * \brief Implémente l'automate 1D ainsi que les Etats 1D
 * \version 1.0
 */


/*! \class Automate1D
 * \brief hérite de Automate<Etat1D>.
          La classe permet d'appliquer une transition sur les Etat1D suivant une règle
 */

class Automate1D : public Automate<Etat1D>
{
    friend class AutomateManager1D;
protected:
    short unsigned int m_numero;    /*!< Numéro de la règle*/
    std::string m_numeroBit;        /*!< Numéro de la règle sous un autre format*/

    /*! \brief Constructeur Privée
     *  \param num : numéro de la régle: unsigned short int
        \param nbEtat : nombre d'état : unsigned short int*/
    Automate1D(short unsigned int num,unsigned short int nbEtat=2);

    /*! \brief Constructeur Privée
     *  \param numBit : numéro de la régle: const std::string&
        \param nbEtat : nombre d'état : unsigned short int*/
    Automate1D(const std::string& numBit,unsigned short int nbEtat=2);

public:

    /*! \brief Destructeur virtuel*/
    virtual ~Automate1D(){}

    /*! \brief accesseur en lecture
        \return m_numero : numéro de la règle: int*/
    int getNumero() const;

    /*! \brief accesseur en lecture
        \return m_numeroBit : numéro de la règle: std::string*/
    std::string getNumeroBit() const;

    /*! \brief applique les règles de transition à un état
        \param dep : état de départ: const Etat1D&
        \param dest : etat d'arrivé: Etat1D&
        \return bool : permet de savoir si il y a eu des modifications entre l'état de départ et celui d'arrivé*/
    bool appliquerTransition(const Etat1D& dep, Etat1D& dest) const;

    /*! \brief afficher un automate*/
    void afficher() const;
};






/*! \class AutomateManager1D
 * \brief Singleton. La classe permet de gèrer la création d'automates à 1 dimension
 */
class AutomateManager1D
{
private:
  static AutomateManager1D* m_AutomateManager1D;    /*!< Singleton*/
  std::vector<Automate1D*> m_tabAutomate;       /*!< Stocke tous les automate1D*/
protected:
  /*! \brief Constructeur Protected*/
    AutomateManager1D();

    /*! \brief Destructeur Protected*/
    ~AutomateManager1D();

    /*! \brief Constructeur de recopie supprimé*/
    AutomateManager1D(const AutomateManager1D&) = delete;

    /*! \brief Opérateur d'affectation protected*/
    AutomateManager1D& operator=(const AutomateManager1D&);
public:
    /*! \brief Méthode statique
        \return m_AutomateManager1D : AutomateManager1D&*/
  static AutomateManager1D& getInstance();

  /*! \brief Méthode statique
     libère l'automate manager*/
  static void freeInstance();

  /*! \brief retourne un automate1D
   * \param num : numéro de la règle : short unsigned int
   * \return const Automate1D&*/
  const Automate1D& getAutomate(short unsigned int num);

  /*! \brief retourne un automate1D
   * \param numbit : numéro de la règle : const std::string&
   * \return const Automate1D&*/
  const Automate1D& getAutomate(const std::string& numbit);
};



/*! \class AutomateException
 * \brief permet d'envoyer des erreurs concernant les automates1D
 */
class AutomateException {
    public:
        AutomateException(const std::string& message):info(message) {}
        std::string getInfo() const { return info; }
    private:
        std::string info;
};


#endif // AUTOMATE1D_H_INCLUDED
