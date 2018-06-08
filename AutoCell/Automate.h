#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <QtWidgets>
#include <QThread>
#include<QTime>
#include<iostream>
#include <string>
#include <vector>

template<class T>class Automate     // classe abstraite
{
private:
    unsigned short int m_nbEtat; // le nombre d'état va de 0 à m_nbEtat -1
public:
    Automate(unsigned short int nbEtat =1) : m_nbEtat(nbEtat){}
    void setNbEtat(unsigned short int e){m_nbEtat = e;}
    unsigned short int getNbEtat() const {return m_nbEtat;}
    virtual void appliquerTransition(const T& , T&) const = 0; // méthode virtuelle pure
};

#endif // AUTOMATE_H
