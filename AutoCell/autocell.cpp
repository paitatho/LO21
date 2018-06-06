 #include "autocell.h"
 #include "Automate2D.h"
 #include "Etat2D.h"
    #include <QThread>
#include<QTime>
#include<iostream>

/*void Autocell1D::synchronizeNumToNumBit(int i){
    std::string numbit = NumToNumBit(i);
    for (unsigned int i=0;i<numbit.size();i++){
        numeroBit[i]->setText(QString(numbit[i]));
    }
}

void Autocell1D::synchronizeNumBitToNum(const QString& s){
    if (s=="") return;
    std::string numBit;
    for(unsigned int i=0;i<8;i++){
        numBit += numeroBit[i]->text().toStdString();
    }
    int a = NumBitToNum(numBit);
    //num->setValue(a);
}*/

void delay(int n)
{
    QTime dieTime= QTime::currentTime().addMSecs(n);
    while (QTime::currentTime() < dieTime)
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void Autocell1D::cellSelected(int a,int b){
    if (depart->item(a,b)->backgroundColor() == "white")
         depart->item(a,b)->setBackgroundColor(*color);
    else
         depart->item(a,b)->setBackgroundColor("white");
}

void Autocell1D::runSim(){
    AutomateManager& aM = AutomateManager::getInstance();
    Etat1D e(largeur);
    for (int i= 0; i<largeur;i++){
        if (depart->item(0,i)->backgroundColor() == *color){
            e.setCellule(i,true);
        }
    }
    Simulateur<Automate1D,Etat1D> s(aM.getAutomate(regle), e);
    if (etats == nullptr){
        etats = new QTableWidget(hauteur,largeur,this);
        etats->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        etats->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        etats->verticalHeader()->hide();
        etats->horizontalHeader()->hide();
    }
    etats->setFixedSize(largeur * taille,hauteur * taille);
    if(hauteur != etats->rowCount())etats->setRowCount(hauteur);
    if(largeur != etats->columnCount())etats->setColumnCount(largeur);

    for( unsigned int i = 0; i<hauteur; i++){
        s.next();
        for (int j=0;j<largeur;j++){
            if(etats->item(i,j) == nullptr){
                QTableWidgetItem* a = new QTableWidgetItem ("");
                a->setFlags(Qt::NoItemFlags);
                a->setFlags(Qt::ItemIsEnabled);
               // a->setSizeHint(QSize(largeur,largeur));
                etats ->setItem(i, j, a);
            }
            if (s.dernier().getCellule(j) == true){
                etats->item(i,j)->setBackgroundColor(*color);
             }
            else  etats->item(i,j)->setBackgroundColor("white");
            etats->setColumnWidth(j,taille);
        }
        etats->setRowHeight(i,taille);
    layout->addWidget(etats,4,0);
    }
    emit endSim();
}

Autocell1D::Autocell1D(QWidget* parent) : Autocell(parent){
    this->setWindowTitle("Automate 1D");

    color = new QColor(0,0,0);

    depart = new QTableWidget(1,largeur,this);
    layout = new QGridLayout(this);
    //layout->addLayout(numeroc,1,0,Qt::AlignVCenter);
    depart->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    depart->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    depart->verticalHeader()->hide();
    depart->horizontalHeader()->hide();
    layout->addWidget(depart,2,0);
    depart->setFixedSize(largeur * taille, taille);
    this->setEtatDepart(largeur);
    QWidget::connect(depart, SIGNAL(cellDoubleClicked(int,int)),this,SLOT(cellSelected(int,int)));

    sim = new QHBoxLayout;
    layout->addLayout(sim,3,0);
    setLayout(layout);
    this->runSim();
}

void Autocell1D::setLargeur(unsigned int l){
    setEtatDepart(l);
    largeur=l;
    this->runSim();
}


void Autocell1D::setEtatDepart(int dim){
    if(depart == nullptr) throw "depart must be defined before";
    else
    {
        depart->setFixedSize(dim * taille, taille);
        depart->setColumnCount(dim);
        for(int i=0;i<dim;i++){
            if(depart->item(0,i) == nullptr){
                QTableWidgetItem* a = new QTableWidgetItem ("");
                a->setFlags(Qt::NoItemFlags);
                a->setFlags(Qt::ItemIsEnabled);
                depart->setItem(0, i, a);
                depart->setColumnWidth(i,taille);
                depart->setRowHeight(i,taille);
                depart->item(0,i)->setBackgroundColor("white");
            }
        }
    }
}

void Autocell1D::setColor(QColor a){
    delete color;
    color = new QColor(a);
    for(int i=0;i<largeur;i++){
        if(depart->item(0,i)->backgroundColor() != "white")
            depart->item(0,i)->setBackgroundColor(*color);
    }
    this->runSim();
}

void Autocell1D::clear(){
    for (int i= 0; i<largeur;i++)
        depart->item(0,i)->setBackgroundColor("white");
    runSim();
}

/*##########################################################################################"*/

void Autocell2D::setEtat(int h,int l){
    if(etats != nullptr){
        etats->setColumnCount(l);
        etats->setRowCount(h);
        for(int i=0;i<hauteur;i++){
            for(int j=0;j<largeur;j++){
                if(etats->item(i,j) == nullptr){
                    QTableWidgetItem* a = new QTableWidgetItem ("");
                    a->setFlags(Qt::NoItemFlags);
                    a->setFlags(Qt::ItemIsEnabled);
                    etats->setItem(i,j, a);
                    etats->setColumnWidth(j,taille);
                    etats->setRowHeight(i,taille);
                    etats->item(i,j)->setBackgroundColor(couleur[0].c_str());
                }
            }
        }
    }
}

Autocell2D::Autocell2D(QWidget* parent) : Autocell(parent){
    largeur=30;
    hauteur=30;
    this->setWindowTitle("Automate 2D");
    layout = new QGridLayout;
    color = new QColor(0,0,0);

    etats = new QTableWidget(largeur,hauteur,this);

    etats->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    etats->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    etats->verticalHeader()->hide();
    etats->horizontalHeader()->hide();
    etats->setFixedSize(largeur * taille, hauteur* taille);

    QWidget::connect(etats, SIGNAL(cellDoubleClicked(int,int)),this,SLOT(cellSelected(int,int)));

    this->setEtat(largeur,hauteur);
    layout->addWidget(etats);

    this->setLayout(layout);
    //this->runSim();
}

void Autocell2D::cellSelected(int a,int b){
    unsigned int i=0;
    bool sol=false;
    while(i<nbEtat && sol==false )
    {
        if(etats->item(a,b)->backgroundColor()== couleur[i].c_str()){
            etats->item(a,b)->setBackgroundColor(couleur[(i+1)%nbEtat].c_str());
            sol=true;
        }
        i++;
    }
    /*if (etats->item(a,b)->backgroundColor() == "white")
         etats->item(a,b)->setBackgroundColor(couleur[1].c_str());
    else
         etats->item(a,b)->setBackgroundColor("white");*/
}

void Autocell2D::runSim(){
    unsigned int c=0;
    bool sol=false;

    do {
        Etat2D e(largeur,hauteur);
        for (unsigned int i= 0; i<hauteur;i++){
            for(unsigned int j =0; j<largeur;j++){
                while(sol==false && c<nbEtat){
                    if (etats->item(i,j)->backgroundColor() == couleur[c].c_str()){
                        e.setCellule(i,j,c);
                        sol=true;
                    }
                    c++;
                }
                sol=false;
                c=0;
            }
        }
        std::vector<std::vector<unsigned short int>> v;
        v.push_back(std::vector<unsigned short int>());
        v.push_back(std::vector<unsigned short int>());//[1,1,0,2,3] [0,1,1,3,3]
        v.push_back(std::vector<unsigned short int>());
        v[0].push_back(0);v[0].push_back(2);v[0].push_back(0);v[0].push_back(1);v[0].push_back(8);
        v[1].push_back(2);v[1].push_back(0);v[1].push_back(1);v[1].push_back(0);v[1].push_back(9);
        v[2].push_back(0);v[2].push_back(2);v[2].push_back(1);v[2].push_back(1);v[2].push_back(8);
        v[3].push_back(3);v[3].push_back(0);v[3].push_back(1);v[3].push_back(0);v[3].push_back(9);
        Automate2D a(v,3);
        Simulateur<Automate2D,Etat2D> s(a,e);
        s.next();
        if (etats == nullptr){
            etats = new QTableWidget(hauteur,largeur,this);
            etats->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            etats->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            etats->verticalHeader()->hide();
            etats->horizontalHeader()->hide();
        }
        etats->setFixedSize(largeur * taille,hauteur * taille);
        if(hauteur != etats->rowCount())etats->setRowCount(hauteur);
        if(largeur != etats->columnCount())etats->setColumnCount(largeur);

        for (unsigned int i=0;i<hauteur;i++){
            for(unsigned int j =0 ; j<largeur;j++){
                if(etats->item(i,j) == nullptr){
                    QTableWidgetItem* a = new QTableWidgetItem ("");
                    a->setFlags(Qt::NoItemFlags);
                    a->setFlags(Qt::ItemIsEnabled);
                    etats ->setItem(i, j, a);
                }
                if(e == s.dernier()) continu=false;
                else{
                    etats->item(i,j)->setBackgroundColor(couleur[s.dernier().getCellule(i,j)].c_str());
                    etats->setColumnWidth(j,taille);
                    etats->setRowHeight(i,taille);
                }
            }
        }
        if(continu){delay(300);}
        //if(!continu) compteur--;
    }while(continu);

    //compteur++;
    emit endSim();
}

void Autocell2D::clear(){
    setContinu(false);
    for (int i= 0; i<hauteur;i++)
        for(int j=0;j<largeur;j++){
            etats->item(i,j)->setBackgroundColor(couleur[0].c_str());
        }
    runSim();
}

