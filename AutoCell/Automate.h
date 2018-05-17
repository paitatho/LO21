#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

template<class T>class Automate
{
private:
    unsigned short int m_nbEtat; // le nombre d'état va de 0 à m_nbEtat
public:
    Automate(unsigned short int nbEtat) : m_nbEtat(nbEtat){}
    virtual void appliquerTransition(const T& , T&) const;
};

#endif // AUTOMATE_H
