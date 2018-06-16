#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "autocell.h"
#include<iostream>
#include<QtXml>
#include<QFileDialog>

/*!
 * \file MainWindow.h
 * \brief Fenêtre principale
 * \version 1.0
 */


/*! \class  MainWindow
 * \brief hérite de QMainWindow
 *        Représente la fenêtre principal de l'application
 */

class MainWindow : public QMainWindow
{Q_OBJECT
private:
    QToolBar* toolBar;              /*!< barre d'outil*/
    std::vector<QIcon *> icon;      /*!< icone de la barre d'outil*/
    std::vector<QAction *> action;  /*!< action de la barre d'outil*/
    std::vector<QLabel *> label;    /*!< text de la barre d'outil*/
    QComboBox *choixSim;            /*!< Permet le choix de l'automate qu'on veut lancer*/

    QGroupBox* boxDim;              /*!< sous option dimension*/
    QGridLayout* layoutBoxDim;      /*!< layout des sous option dimension*/
    QGroupBox* boxCel;              /*!< sous option cellule*/
    QGridLayout* layoutBoxCel;      /*!< layout des sous option cellule*/
    QWidget* option1D;              /*!< représente les options de l'automate1D*/
    QGridLayout* layout1D;          /*!< layout principal des options 1D*/
    QSpinBox* larg1D;               /*!< sous option dimension*/
    QSpinBox* nbSim1D;              /*!< Nombre de simulation*/
    QSpinBox* regle1D;              /*!< Numéro de la règle de transition*/
    QComboBox* couleur;             /*!< Couleur des cellules 1D*/


    QWidget* option2D;              /*!< représente les options de l'automate2D*/
    QGridLayout* layout2D;          /*!< layout principal des options 1D*/
    QGridLayout* layoutBoxDim2D;    /*!< layout des sous option dimension 2D*/
    QGroupBox* boxCel2D;            /*!< sous option Cellule*/
    QGroupBox* boxDim2D;            /*!< sous option dimension*/
    QGridLayout* layoutBoxCel2D;    /*!< layout des sous option cellule 2D*/
    QGroupBox* boxParam2D;          /*!< sous option paramètre*/
    QComboBox* mode2D;              /*!< mode de lecture 2D*/
    QGridLayout* layoutBoxParam2D;  /*!< layout des sous option paramètre 2D*/
    QMdiArea * central;             /*!< représente la zone centrale de l'application ou seront chargé les automates*/
    QMdiSubWindow* subWin;          /*!< représente la la subWindow de l'automate 1D*/
    QMdiSubWindow* subWin2D;        /*!< représente la la subWindow de l'automate 2D*/
    QSpinBox* larg2D;               /*!< Largeur*/
    QSpinBox* haut2D;               /*!< Hauteur*/
    QSpinBox* speed2D;              /*!< Delai entre chaque simulation*/
    QSpinBox* taille;               /*!< taille des cellules*/

    QDockWidget* optionDock;        /*!< option*/
    static Autocell1D* auto1D;      /*!< attribut static pour l'automate 1D (on peut en construire qu'un)*/
    static Autocell2D* auto2D;      /*!< attribut static pour l'automate 2D (on peut en construire qu'un)*/

    /*! \brief construit la barre d'outil
                méthode virtuelle privée utilisée dans le constructeur*/
    virtual void createToolBar();

    /*! \brief construit les options
                méthode virtuelle privée utilisée dans le constructeur*/
    virtual void createDockOption();

    /*! \brief construit la zone centrale
                méthode virtuelle privée utilisée dans le constructeur*/
    virtual void createMdiArea();

    /*! \brief construit les options pour l'automate1D
                méthode virtuelle privée utilisée dans le constructeur*/
    virtual void createOption1D();

    /*! \brief construit les options pour l'automate2D
                méthode virtuelle privée utilisée dans le constructeur*/
    virtual void createOption2D();

public:
    /*! \brief Constructeur*/
    MainWindow(QWidget* parent = nullptr);

    /*! \brief méthode permettant de contrôler le comportement de l'application lors de la fermeture
                méthode vituelle*/
    virtual void closeEvent(QCloseEvent *event);

    /*! \brief méthode permettant la sauvegarde des informations nécessaires à la réouverture en l'état de l'application
                méthode vituelle*/
    virtual void saveAppState();

    /*! \brief méthode qui permet d'ajouter des options à sauvegarder dans saveAppState() [Hook]
                méthode vituelle*/
    virtual void extensionSaveAppState(){}

    /*! \brief méthode qui permet d'ajouter des options à sauvegarder dans saveAppState() [Hook]
                méthode vituelle*/
    virtual void extensionRestoreAppState(){}

    /*! \brief méthode appelée avant la méthode show() de la mainwindow afin de restaurer la dernière session
                méthode vituelle*/
    virtual void restoreAppState();

    /*! \brief méthode qui permet d'ajouter des automates dans le SLOT openSim() [Hook]
                méthode vituelle*/
   virtual void extensionOpenSim(){}

    /*! \brief méthode qui permet d'ajouter des actions lors du nettoyage des attributs dans le SLOT clearAuto1D() [Hook]
                méthode vituelle*/
   virtual void extensionclearAuto1D(){larg1D->setValue(15);nbSim1D->setValue(20);regle1D->setValue(150);}

    /*! \brief méthode qui permet d'ajouter des actions lors du nettoyage des attributs dans le SLOT clearAuto2D()  [Hook]
                méthode vituelle*/
   virtual void extensionclearAuto2D(){larg2D->setValue(35);haut2D->setValue(35);taille->setValue(17);}

public slots:
    /*! \brief SLOT qui ouvre un automate choisit dans l'attribut membre choixSim*/
     void openSim();

    /*! \brief SLOT qui nettoie le attribut et les options à la destruction de l'automate 1D
                méthode vituelle*/
    void clearAuto1D(){ auto1D = nullptr;subWin = nullptr;this->extensionclearAuto1D();}


    /*! \brief SLOT qui nettoie le attribut à la destruction de l'automate 1D
                méthode vituelle*/
    void clearAuto2D(){auto2D = nullptr; subWin2D = nullptr; this->extensionclearAuto2D();}


    /*! \brief SLOT qui gère le changement de couleur de l'automate courant*/
    void changeColor(QString);

    /*! \brief SLOT qui gère le changement de taille de l'automate courant*/
    void changeSize();

    /*! \brief SLOT qui gère le changement de hauteur de l'automate courant
        \param a : nouvelle hauteur : int*/
    void changeHauteur(int a);

    /*! \brief SLOT qui gère le changement de hauteur de l'automate courant
        \param a : nouvelle largeur : int*/
    void changeLargeur(int a);

    /*! \brief SLOT qui gère le changement de règle de l'automate1D
        \param a : nouvelle règle : int*/
    virtual void changeRegle1D(int a);

    /*! \brief SLOT qui gère le changement de délai de l'automate courant
        \param a : nouveau délai : int*/
    void changeSpeed(int s);

    /*! \brief SLOT qui gère le changement de taille de l'automate courant
        \param taille : nouvelle taille : int*/
    void changeTaille(int);

    /*! \brief SLOT qui gère la lecture de l'automate courant*/
    virtual void play();

    /*! \brief SLOT qui gère l'arrêt de l'automate courant*/
    void pause();

    /*! \brief SLOT qui gère le nettoyage de l'automate courant*/
    void clear();

    /*! \brief SLOT qui gère l'affichage des options en fonction de l'automate courant
        \param w : automateCourant : QMdiSubWindow * */
    virtual void current(QMdiSubWindow *w);

    /*! \brief SLOT qui permet d'activer le bouton pour nettoyer l'automate (quand on est en lecture on ne peut pas clear)*/
    virtual void allow(){action[3]->setEnabled(true);}

    /*! \brief SLOT qui permet d'afficherla fenêtre de saisie des règles pour l'automate2D*/
    void afficherRegle2D(){ auto2D->get_regle2D()->show();} // avec le polymorphisme quelque soit la classe fille on aura les bonnes régles

    /*! \brief SLOT qui gère la génération d'un état initial aléatoire en fonction de l'automate courant*/
    void initialiseur();

    /*! \brief SLOT qui gère la génération d'un état initial symétrique en fonction de l'automate courant*/
    void initialiseurSym();

    /*! \brief SLOT permettant la sauvegarde d'un Automate 1D ou 2D*/
    void saveAutomate();

    /*! \brief SLOT permettant le chargement d'un Automate 1D ou 2D*/
    void loadAutomate();
};


/*! \class  WSpacer
 * \brief hérite de QWidget
 *        met un espace dans la QToolBar
 */
class WSpacer : public QWidget
{
Q_OBJECT
public :
    WSpacer()
    {
    setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    }
};

#endif // MAINWINDOW_H
