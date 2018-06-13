#ifndef AUTOCELL_H
#define AUTOCELL_H

#include <QtWidgets>
#include <typeinfo>
#include <cstdlib>
#include "Automate1D.h"
#include "Simulateur.h"
class Regle2D;

/*!
 * \file autocell.h
 * \brief Gestion graphique des Automates cellulaires 1D et 2D
 * \version 1.0
 */


/*! \class Autocell
 * \brief Classe abstraite.
          La classe généralise un Autocell et définie les méthodes virtuelles qui devront être présente et définie dans chaque Autocell.
          La fenetre principale va alors mettre en action le polymorphisme, permettant alors de lancer, arrêter... n'importe quel Autocell
 */

class Autocell: public QWidget{
    Q_OBJECT
protected:
    int taille =17;         /*!< Taille d'une cellule*/
    unsigned int nbEtat;    /*!< Nombre d'état pour une cellule*/
    unsigned int speed=100; /*!< delai entre chaque simulation*/
    std::vector<std::string> couleur;   /*!< liste des couleurs pour chaque état i*/
    int hauteur =20;        /*!< hauteur de la grille(pour Autocell1D la hauteur  représente le nombre de simulation)*/
    int largeur = 15;       /*!< Largeur de la grille*/
    bool continu = true;    /*!< Mode de lecture*/
public:
    /*! \brief Constructeur de la classe Autocell
     *  \param etat nombre d'états que peut prendre chaque cellule (2 par défaut): unsigned int*/
    Autocell(QWidget* parent = nullptr,unsigned int etat=2): QWidget(parent),nbEtat(etat){
        couleur.push_back("white"); couleur.push_back("white");
    }
    /*! \brief change le nombre d'état que peut prendre une cellule
        \param e : nouveau nombre d'état: unsigned int*/
    void setNbEtat(unsigned int e){nbEtat = e;}

    /*! \brief change la taille des cellules
        \param t :nouvelle taille: unsigned int*/
    void setTaille(unsigned int t){taille =t;adjustTaille();adjustSize();}

    /*! \brief change la liste de couleur
        \param c : nouvelle liste de couleur: std::vector<std::string>*/
    void setCouleur(std::vector<std::string> c){couleur.clear();couleur =c;}

    /*! \brief change le delai
        \param s : nouveau délai: unsigned int*/
    void setSpeed(unsigned int s){speed =s;}

    /*! \brief change le mode de lecture de l'autocell
        \param a : mode de lecture: bool*/
    void setContinu(bool a){continu = a;}

    /*! \brief accesseur Lecture
        \return retourne le nombre d'états*/
    unsigned int getNbEtat() const {return nbEtat;}

    /*! \brief accesseur Lecture
        \return retourne la taille*/
    unsigned int getTaille() const {return taille;}

    /*! \brief accesseur Lecture
        \return retourne la largeur*/
    unsigned int getLargeur() const{return largeur;}

    /*! \brief accesseur Lecture
        \return retourne la hauteur*/
    unsigned int getHauteur() const{return hauteur;}

    /*! \brief accesseur en écriture
     *         change la hauteur et ajuste la taille de la fenetre grâce à la méthode virtuelle pure adjustTaille()
     *  \param h : nouvelle hauteur: unsigned int*/
    void setHauteur(unsigned int h){hauteur =h;adjustTaille();adjustSize();}

    /*! \brief accesseur en écriture
     *         change la largeur et ajuste la taille de la fenetre grâce à la méthode virtuelle pure adjustTaille()
     *  \param l : nouvelle largeur:unsigned int */
    virtual void setLargeur(unsigned int l){largeur =l;adjustTaille();adjustSize();}

    /*! \brief Lance la simulation
                méthode virtuelle pure qui va permettre de lancer une simulation en fonction de l'automate*/
    virtual void runSim() =0;

    /*! \brief nettoie l'autocell
                méthode virtuelle pure qui va permettre de réinitialiser l'autocell*/
    virtual void clear()=0;

    /*! \brief ajuste l'autocell
                méthode virtuelle pure qui va permettre de d'ajuster l'autocelle en fonction de la largeur, hauteur et taille*/
    virtual void adjustTaille() =0;

    /*! \brief Génère une grille de départ
                méthode virtuelle pure qui va générer aléatoirement un état initiale pour l'autocell*/
    virtual void init()=0;

    /*! \brief Génère une grille de départ symétrique
                méthode virtuelle pure qui va générer aléatoirement un état initiale symétrique par rapport à l'axe Y pour l'autocell*/
    virtual void initSym()=0;

 public slots:
    /*! \brief Change la couleur de la cellule selectionnée
                SLOT virtuel pur qui va réaliser une action à la selection (un click) d'une cellule*/
    virtual void cellSelected(int a,int b)=0;

signals:
    /*! \brief Signal de fin de simulation
                Signal envoyé à la fin de la simulation*/
    void endSim();

};

/*! \class Autocell1D
 * \brief Hérite de Autocell.
          La classe Autocell1D permet de lancer des automates cellulaires à 1Dimensions (classe Automate1D et Etat1D)
 */

class Autocell1D: public Autocell {
    Q_OBJECT
protected:
    QGridLayout* layout;    /*!< layout principal*/
    QTableWidget* depart;   /*!< grille de départ à 1D*/
    QTableWidget* etats = nullptr;  /*!< grille de simulation*/

    unsigned int regle=0;   /*!< numéro de la règle à appliquer*/

    /*! \brief initialise grille de départ
                méthode privée qui est utilisée dans le constructeur*/
    void setEtatDepart(int dim);

public:
    /*! \brief constructeur*/
    explicit Autocell1D(QWidget* parent = nullptr);
    /*! \brief change la règle
     *  \param r :nouvelle règle : unsigned int*/
    void setRegle(unsigned int r){regle=r;}

    /*! \brief change la couleur
     *  \param a : nouvelle couleur: QString*/
    void setColor(QString a);

    /*! \brief retourne le départ
     *  \return const QTableWidget* */
    const QTableWidget* get_depart() const {return depart;}

    /*! \brief change la case i de l'état de départ dans l'attribut membre depart
     *  \param i : indice: unsigned int
     *  \param color : couleur de la case: QString */
    void setDepart(unsigned int i, QString color){
        depart->item(0,i)->setBackgroundColor(QColor(color));
    }
    /*! \brief Simule un automate1D
     *      construit un automate1D et un etat1D */
    virtual void runSim();

    /*! \brief ajuste la fenêtre
     *     ajuste la fenêtre en fonction de la largeur, hauteur et la taille */
    virtual void adjustTaille();

    /*! \brief nettoie l'autocell*/
    virtual void clear();

    /*! \brief initialise un état de départ pour l'attribut membre depart aléatoirement*/
    virtual void init();

    /*! \brief initialise un état de départ pour l'attribut membre depart symétriquement*/
    virtual void initSym();

public slots:
    /*! \brief SLOT qui change la couleur d'une cellule (a,b)
    *   \param ligne:int
    *   \param colonne: int*/
    virtual void cellSelected(int a,int b);


};

/*####################################################################################*/



/*! \class Autocell2D
 * \brief  Hérite de Autocell.
            La classe Autocell2D permet de lancer des automates cellulaires à 2Dimensions (classe Automate2D et Etat2D)
 *
 */
class Autocell2D:public Autocell{
    Q_OBJECT
protected:
    std::vector<std::vector<unsigned short int>> regle; /*!< enregistre la règle qui sera donnée à l'automate2D*/
    QGridLayout* layout;            /*!< layout principal*/
    QTableWidget* etats = nullptr;  /*!< représente les cellules de l'automates*/
    Regle2D* fenetreRegle2D;        /*!< IHM pour rentrer les règles*/
    unsigned int compteur =0;       /*!< compte de nombre de simulation*/
    QLabel* nbSimu;

    /*! \brief initialise l'attribut membre etats
    *   \param h : hauteur: int
    *   \param l : largeur: int */
    void setEtat(int h,int l);
public:
    /*! \brief Constructeur*/
    Autocell2D(QWidget* parent = nullptr);
    /*! \brief change le mode de lecture
    *   \param mode de lecture: bool */
    void setContinu(bool a){continu=a;}

    /*! \brief retourne le mode de lecture
    *   \return mode de lecture: bool */
    bool getContinu(){return continu;}

    /*! \brief ajuste la taille de la fenêtre en fonction de la largeur, la hauteur et la taille
            méthode virtuelle*/
    virtual void adjustTaille();

    /*! \brief change la règle
        \param r: nouvelle règle: std::vector<std::vector<unsigned short int>>*/
    void setRegle(std::vector<std::vector<unsigned short int>> r){regle.clear();regle=r;setNbEtat(regle.size());}

    /*! \brief retourne la règle
        \return règle: const std::vector<std::vector<unsigned short int>>& */
    const std::vector<std::vector<unsigned short int>>& getRegle() const {return regle;}

    /*! \brief initialise un état de départ pour l'attribut membre etats aléatoirement*/
    virtual void init();


    /*! \brief initialise un état de départ pour l'attribut membre etats symétriquement*/
    virtual void initSym();

    /*! \brief retourne l'attribut membre etats
        \return etats: const QTableWidget* */
    const QTableWidget* get_etats() const {return etats;}

    /*! \brief retourne l'attribut membre regle
        \return etats: Regle2D* */
    Regle2D* get_regle2D(){return fenetreRegle2D;}

    /*! \brief modifie la cellule (i,j) de la grille etats
        \param i : ligne: int
        \param j : colonne: int
        \param color : couleur de la cellule : QString */
    void setEtats(unsigned int i, unsigned int j, QString color){
        etats->item(i,j)->setBackgroundColor(QColor(color));
    }

public slots:
    /*! \brief SLOT qui modifie la
        \param a ligne: int
        \param b colonne: int */
    void cellSelected(int a,int b);

    /*! \brief SLOT qui nettoie l'attribut membre etats*/
    void clear();

    /*! \brief SLOT qui simule un automate à 2 dimensions à l'aide des classes Automate2D et Etat2D*/
    void runSim();

     /*! \brief SLOT change les attributs membres regle et couleur
         \param r :nouvelle règle: std::vector<std::vector<unsigned short int> >
         \param c :nouvelles couleurs: std::vector<std::string> */
    void changeRegle(std::vector<std::vector<unsigned short int> > r,std::vector<std::string> c);

};


/*! \class Regle2D
 * \brief  Hérite de QWidget.
           La classe Regle2D permet d'entrer une règle pour un autocell2D (classe Automate2D et Etat2D)
 *
 */

class Regle2D: public QWidget{
    Q_OBJECT
protected:
    std::vector<std::vector<unsigned short int>> regle; /*!< enregistre la règle sous le même format que dans autocell2D*/
    std::vector<std::string> couleurNom;                /*!< enregistre les couleurs sous le même format que dans autocell2D*/
    QSpinBox* nbEtat;                                   /*!< permet d'entrer le nombre d'état des cellules*/
    QComboBox* regleBase;                               /*!< permet de sélectionner des règles prédéfinies*/
    std::vector<QSpinBox*> etatCellulePourAppliquer;    /*!< permet de rentre l'état que la cellule doit avoir pour qu'on lui applique la règle*/
    std::vector<QSpinBox*> celluleACCompter;            /*!< permet de rentre l'état que la cellule doit avoir qu'on la considère dans l'entourage*/
    std::vector<QComboBox*> interval;                   /*!< permet de savoir si on doit être dedans ou hors de l'interval*/
    std::vector<QSpinBox*> borneInf;                    /*!< permet de rentrer la borne inférieur de l'interval*/
    std::vector<QSpinBox*> borneSup;                    /*!< permet de rentrer la borne supérieur de l'interval*/
    std::vector<QComboBox*> couleur;                    /*!< permet de rentrer la couleur de la cellule*/
    QGridLayout* layout;                                /*!< layout principal*/


    /*! \brief initialise tous les attributs
    *       méthode protected */
    void depart();


public:
    /*! \brief Constructeur*/
    Regle2D(QWidget* parent = nullptr);

    /*! \brief accesseur lecture
    *   \return nbEtat : const QSpinBox* */
    const QSpinBox* get_nbEtat() const {return nbEtat;}

    /*! \brief accesseur lecture
    *   \return regleBase : const QComboBox*  */
    const QComboBox* get_regleBase() const{return regleBase;}

    /*! \brief accesseur lecture
    *   \return etatCellulePourAppliquer : const std::vector<QSpinBox*>&  */
    const std::vector<QSpinBox*>& get_etatCellulePourAppliquer() const {return etatCellulePourAppliquer;}

    /*! \brief accesseur lecture
    *   \return celluleACCompter : const std::vector<QSpinBox*>&  */
    const std::vector<QSpinBox*>& get_celluleACCompter() const {return celluleACCompter;}

    /*! \brief accesseur lecture
    *   \return interval : const std::vector<QComboBox*>&  */
    const std::vector<QComboBox*>& get_interval() const {return interval;}

    /*! \brief accesseur lecture
    *   \return borneInf : const std::vector<QSpinBox*>&  */
    const std::vector<QSpinBox*>& get_borneInf() const {return borneInf;}

    /*! \brief accesseur lecture
    *   \return borneSup : const std::vector<QSpinBox*>&  */
    const std::vector<QSpinBox*>& get_borneSup() const {return borneSup;}

    /*! \brief accesseur lecture
    *   \return couleur : const std::vector<QComboBox*>&  */
    const std::vector<QComboBox*>& get_couleur() const {return couleur;}

    /*! \brief accesseur lecture
    *   \return couleurNom : const std::vector<std::string>& */
    const std::vector<std::string>& get_couleurNom() const {return couleurNom;}

    /*! \brief accesseur lecture
    *   \return regle : const std::vector<std::vector<unsigned short int>>&  */
    const std::vector<std::vector<unsigned short int>>& get_regle() const {return regle;}

    /*! \brief change la règle prédéfinie
    *   \param s : nouveau nom de règle prédéfinie: QString */
    void setRegleBase(const QString& s){regleBase->setCurrentText(s);}

    /*! \brief change le nombre d'état
    *   \param n : nouveau nombre d'état: unsigned int */
    void setNbEtat(unsigned int n){nbEtat->setValue(n);}

    /*! \brief change l'objet à l'indice i
    *   \param i : indice : unsigned int
    *   \param n : nouvelle valeur : unsigned int */
    void setEtatCellulePourAppliquer(unsigned int i, unsigned int n){ etatCellulePourAppliquer[i]->setValue(n);}

    /*! \brief change l'objet à l'indice i
    *   \param i : indice : unsigned int
    *   \param n : nouvelle valeur : unsigned int */
    void setCelluleACompter(unsigned int i, unsigned int n){celluleACCompter[i]->setValue(n);}

    /*! \brief change l'objet à l'indice i
    *   \param i : indice : unsigned int
    *   \param s : nouvelle valeur : const QString& */
    void setInterval(unsigned int i, const QString& s){interval[i]->setCurrentText(s);}

    /*! \brief change l'objet à l'indice i
    *   \param i : indice : unsigned int
    *   \param n : nouvelle valeur : unsigned int */
    void setBorneInf(unsigned int i, unsigned int n){borneInf[i]->setValue(n);}

    /*! \brief change l'objet à l'indice i
    *   \param i : indice : unsigned int
    *   \param n : nouvelle valeur : unsigned int */
    void setBorneSup(unsigned int i, unsigned int n){borneSup[i]->setValue(n);}

    /*! \brief change l'objet à l'indice i
    *   \param i : indice : unsigned int
    *   \param s : nouvelle valeur : const QString& */
    void setCouleur(unsigned int i, const QString& s){couleur[i]->setCurrentText(s);}
public slots:
    /*! \brief SLOT qui cache les lignes inutiles en fonction du nombre d'états entré*/
    void cacher();

    /*! \brief SLOT qui affecte l'attribut membre regle pour mettre la règle dans le même format que Autocell2D*/
    void setRegle();

    /*! \brief SLOT qui affecte l'attribut membre couleurNom pour mettre le mettre dans le même format que Autocell2D*/
    void setCouleur();

    /*! \brief SLOT qui envoie le signal envoieRegle*/
    void sendRegle();

    /*! \brief SLOT qui gère les règles prédéfinies*/
    void reglePredefini(QString);

    /*! \brief SLOT Hook qui permet de rajouter des règles prédéfinies*/
    virtual void ajoutReglePredefini(QString);

    /*! \brief SLOT qui montre les lignes nécessaires en fonction du nombre d'états entré*/
    void montrer();

    /*! \brief SLOT qui utilise montrer() et cacher() pour modifier la fenêtre en fonction du nombre d'état*/
    void adjust();

signals:
    /*! \brief SIGNAL qui envoie la règle et la couleur des cellules
        \param  regle : std::vector<std::vector<unsigned short int>>
        \param  couleur : std::vector<std::string>*/
    void envoiRegle(std::vector<std::vector<unsigned short int>>,std::vector<std::string>);

};

/*! \class Regle2DBis
 * \brief  Hérite de Regle2D
            La classe Regle2DBis montre comment intégrer de nouvelles règles à un autocell2D
 *
 */
class Regle2DBis : public Regle2D{
public:
     /*! \brief Constructeur
                ajout d'une nouvelle règle Feu de Forêt*/
    Regle2DBis(QWidget* parent = nullptr):Regle2D(parent){regleBase->addItem("Feu de Foret");}

    /*! \brief Hook permettant d'ajouter la nouvelle règle
        \param nom : nom de la règle prédéfinie : QString*/
    virtual void ajoutReglePredefini(QString nom){
        if (nom == "Feu de Foret"){
            nbEtat->setValue(4);
            etatCellulePourAppliquer[0]->setValue(0);
            celluleACCompter[0]->setValue(2); interval[0]->setCurrentIndex(1);
            borneInf[0]->setValue(1);borneSup[0]->setValue(8);couleur[0]->setCurrentIndex(2);

            etatCellulePourAppliquer[1]->setValue(1);
            celluleACCompter[1]->setValue(0); interval[1]->setCurrentIndex(0);
            borneInf[1]->setValue(0);borneSup[1]->setValue(8);couleur[1]->setCurrentIndex(0);

            etatCellulePourAppliquer[2]->setValue(0);
            celluleACCompter[2]->setValue(2); interval[2]->setCurrentIndex(0);
            borneInf[2]->setValue(1);borneSup[2]->setValue(8);couleur[2]->setCurrentIndex(3);

            etatCellulePourAppliquer[3]->setValue(2);
            celluleACCompter[3]->setValue(0); interval[3]->setCurrentIndex(0);
            borneInf[3]->setValue(0);borneSup[3]->setValue(8);couleur[3]->setCurrentIndex(1);
        }
    }
};

/*! \class Autocell2DBis
 * \brief  Hérite de Autocell2D.
            La classe Autocell2DBis montre comment intégrer de nouvelles règles à un autocell2D
 *
 */
class Autocell2DBis: public Autocell2D{
public:
    /*! \brief Constructeur
               modification de la fenetreRegle2D et la remplaçant par un Regle2DBis*/
    Autocell2DBis(QWidget* parent = nullptr):Autocell2D(parent){
        delete fenetreRegle2D;
        fenetreRegle2D = new Regle2DBis;
        connect(fenetreRegle2D,SIGNAL(envoiRegle(std::vector<std::vector<unsigned short int> >,std::vector<std::string>)),this,SLOT(changeRegle(std::vector<std::vector<unsigned short int> >,std::vector<std::string>)));
    }

};

#endif // AUTOCELL_H
