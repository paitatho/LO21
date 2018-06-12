
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
 * \brief hérite de Automate<Etat1D>
 *
 *  La classe permet d'appliquer une transition sur les Etat1D suivant une règle
 */

class Automate1D : public Automate<Etat1D>
{
    friend class AutomateManager;
private:
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
    /*! \brief accesseur en lecture
        \return m_numero : numéro de la règle: int*/
    int getNumero() const;

    /*! \brief accesseur en lecture
        \return m_numeroBit : numéro de la règle: std::string*/
    std::string getNumeroBit() const;

    /*! \brief applique les règles de transition à un état
        \param dep : état de départ: const Etat1D&
        \param dest : etat d'arrivé: Etat1D&*/
    void appliquerTransition(const Etat1D& dep, Etat1D& dest) const;

    /*! \brief afficher un automate*/
    void afficher() const;
};






/*! \class AutomateManager
 * \brief
 *  La classe permet de gèrer les automates
 */
class AutomateManager
{
private:
  static AutomateManager* m_automateManager;    /*!< Singleton*/
  std::vector<Automate1D*> m_tabAutomate;       /*!< Stocke tous les automate1D*/
protected:
  /*! \brief Constructeur Protected*/
    AutomateManager();

    /*! \brief Destructeur Protected*/
    ~AutomateManager();

    /*! \brief Constructeur de recopie supprimé*/
    AutomateManager(const AutomateManager&) = delete;

    /*! \brief Opérateur d'affectation protected*/
    AutomateManager& operator=(const AutomateManager&);
public:
    /*! \brief Méthode statique
        \return m_automateManager : AutomateManager&*/
  static AutomateManager& getInstance();

  /*! \brief Méthode statique
     libère l'automate manager*/
  static void freeIstance();

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
 * \brief
 *      permet d'envoyer des erreurs concernant les automates1D
 */
class AutomateException {
    public:
        AutomateException(const std::string& message):info(message) {}
        std::string getInfo() const { return info; }
    private:
        std::string info;
};


#endif // AUTOMATE1D_H_INCLUDED
