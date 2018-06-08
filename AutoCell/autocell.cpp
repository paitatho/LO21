 #include "autocell.h"
 #include "Automate2D.h"
 #include "Etat2D.h"


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
    depart->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    depart->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    depart->verticalHeader()->hide();
    depart->horizontalHeader()->hide();
    layout->addWidget(depart,2,0);
    depart->setFixedSize(largeur * taille, taille);
    this->setEtatDepart(largeur);
    QWidget::connect(depart, SIGNAL(cellClicked(int,int)),this,SLOT(cellSelected(int,int)));

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

void Autocell1D::adjustTaille(){

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

Autocell2D::Autocell2D(QWidget* parent) : Autocell(parent),regle(std::vector<std::vector<unsigned short int>>()){
    largeur=30;
    hauteur=30;
    this->setWindowTitle("Automate 2D");
    layout = new QGridLayout;
    etats = new QTableWidget(largeur,hauteur,this);

    etats->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    etats->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    etats->verticalHeader()->hide();
    etats->horizontalHeader()->hide();
    etats->setFixedSize(largeur * taille, hauteur* taille);

    QWidget::connect(etats, SIGNAL(cellClicked(int,int)),this,SLOT(cellSelected(int,int)));

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
}

void Autocell2D::runSim(){
    unsigned int c=0;
    bool sol=false;
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
    Automate2D a(regle,nbEtat);
    Simulateur<Automate2D,Etat2D> s(a,e);
    do {
        s.next();
        for (unsigned int i=0;i<hauteur;i++){
            for(unsigned int j =0 ; j<largeur;j++){
                if(etats->item(i,j) == nullptr){
                    QTableWidgetItem* a = new QTableWidgetItem ("");
                    a->setFlags(Qt::NoItemFlags);
                    a->setFlags(Qt::ItemIsEnabled);
                    etats ->setItem(i, j, a);
                }
                if(s.avantDernier() == s.dernier()) continu=false;
                else{
                    etats->item(i,j)->setBackgroundColor(couleur[s.dernier().getCellule(i,j)].c_str());
                    etats->setColumnWidth(j,taille);
                    etats->setRowHeight(i,taille);
                }
            }
        }
        if(continu){delay(speed);}
    }while(continu);
    emit endSim();
}

void Autocell2D::clear(){
    setContinu(false);
    for (int i= 0; i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            etats->item(i,j)->setBackgroundColor(couleur[0].c_str());
        }
    }
}

void Autocell2D::adjustTaille(){
    if(hauteur != etats->rowCount())etats->setRowCount(hauteur);
    if(largeur != etats->columnCount())etats->setColumnCount(largeur);
    for (unsigned int i=0;i<hauteur;i++){
        for(unsigned int j =0 ; j<largeur;j++){
            if(etats->item(i,j) == nullptr){
                QTableWidgetItem* a = new QTableWidgetItem ("");
                a->setFlags(Qt::NoItemFlags);
                a->setFlags(Qt::ItemIsEnabled);
                etats ->setItem(i, j, a);
                etats->item(i,j)->setBackgroundColor(couleur[0].c_str());
            }
            etats->setColumnWidth(j,taille);
            etats->setRowHeight(i,taille);
        }
    }
    etats->setFixedSize(largeur * taille,hauteur * taille);;
}

void Autocell2D::init(){
    for (unsigned int i=0;i<hauteur;i++){
        for(unsigned int j =0 ; j<largeur;j++){
            etats->item(i,j)->setBackgroundColor(couleur[rand()%2].c_str()); //met soit la couleur de l'état 0, soit celle de l'état 1
        }
    }
}
/*#####################################################---REGLE 2D----#######################################"*/

Regle2D::Regle2D(QWidget* parent) : QWidget(parent),regle (std::vector<std::vector<unsigned short int>>()){
   nbEtat = new QSpinBox;
   nbEtat->setRange(2,8);
   nbEtat->setValue(2);
   regleBase = new QComboBox;regleBase->addItems((QStringList()<<"régles prédéfinies" << "JDLV"));
   connect(regleBase,SIGNAL(currentTextChanged(QString)),this,SLOT(reglePredefini(QString)));
   connect(nbEtat,SIGNAL(valueChanged(int)),this,SLOT(adjust()));
   layout= new QGridLayout;
   layout->addWidget(regleBase);
   layout->addWidget(new QLabel("nombre d'état"),0,1);
   layout->addWidget(nbEtat,0,2);
   etatCellulePourAppliquer= std::vector<QSpinBox*>();
   celluleACCompter= std::vector<QSpinBox*>();
   interval= std::vector<QComboBox*>();
   borneInf= std::vector<QSpinBox*>();
   borneSup= std::vector<QSpinBox*>();
   couleur = std::vector<QComboBox*>();
   setWindowTitle("regle2D");
   this->depart();
   setLayout(layout);
   this->cacher();
}

void Regle2D::depart(){
    for (int i=0;i<nbEtat->maximum();i++){
            std::string label("Pour passer à l'état " + std::to_string(i) +", ");
            QString labelBis= label.c_str();
            layout->addWidget(new QLabel(labelBis),i+1,0);

            layout->addWidget(new QLabel("il faut être dans l'état"),i+1,1);
            etatCellulePourAppliquer.push_back(new QSpinBox(this));etatCellulePourAppliquer[i]->setRange(0,nbEtat->value()-1);
            layout->addWidget(etatCellulePourAppliquer[i],i+1,2);

            layout->addWidget(new QLabel("compter les cellules alentours dans l'état"),i+1,3);
            celluleACCompter.push_back(new QSpinBox(this));celluleACCompter[i]->setRange(0,nbEtat->value()-1);
            layout->addWidget(celluleACCompter[i],i+1,4);

            interval.push_back(new QComboBox(this));interval[i]->addItem("Dans interval");interval[i]->addItem("hors interval");
            layout->addWidget(interval[i],i+1,5);


            borneInf.push_back(new QSpinBox(this));borneInf[i]->setRange(0,8);
            layout->addWidget(borneInf[i],i+1,6);


            borneSup.push_back(new QSpinBox);borneSup[i]->setRange(0,8);
            layout->addWidget(borneSup[i],i+1,7);


            couleur.push_back(new QComboBox(this)); couleur[i]->addItems((QStringList() << "white"<< "black"<<"green" << "red"<<"blue"<<"yellow"));
            layout->addWidget(couleur[i],i+1,8);
    }
    QPushButton* bouton = new QPushButton("OK");
    connect(bouton,SIGNAL(clicked()),this,SLOT(sendRegle()));
    layout->addWidget(bouton,nbEtat->maximum()+1,8);
    modifDepart();
}

void Regle2D::cacher(){
    for (int i=nbEtat->value()+1;i<=nbEtat->maximum();i++){
        for(int j=0;j<9;j++){
            layout->itemAtPosition(i,j)->widget()->hide();
        }
    }
}

void Regle2D::montrer(){
    int c =0;
    for (int i=1;i<=nbEtat->value();i++){
        for(int j=0;j<9;j++){
            layout->itemAtPosition(i,j)->widget()->show();
            if (c < 2){ //On modifie que les deux premiers QSpinBox qui ne doivent pas dépasser le nombre max d'état
                QSpinBox* s =dynamic_cast<QSpinBox*>(layout->itemAtPosition(i,j)->widget());
                if(s != nullptr) {s->setRange(0,nbEtat->value()-1); ++c;}
            }

        }
        c=0;
    }
}
void Regle2D::adjust(){
    montrer();
    cacher();
}

void Regle2D::setRegle(){
    regle.clear();
    for(int i=0;i<nbEtat->value();++i){
        regle.push_back(std::vector<unsigned short int>(5));
        regle[i][0] = etatCellulePourAppliquer[i]->value();
        regle[i][1] = celluleACCompter[i]->value();
        if(interval[i]->currentText() == "Dans interval")regle[i][2] = 1;else regle[i][2]=0;
        regle[i][3] = borneInf[i]->value();
        regle[i][4] = borneSup[i]->value();
    }
}


void Regle2D::setCouleur(){
    couleurNom.clear();
    for(int i=0;i<nbEtat->value();++i){
        couleurNom.push_back(couleur[i]->currentText().toStdString());
    }
}

void Regle2D::sendRegle(){
    setRegle();
    setCouleur();
    emit envoiRegle(regle,couleurNom);
    this->hide();
}

void Regle2D::reglePredefini(QString nom){
    if (nom == "JDLV"){
        nbEtat->setValue(2);
        etatCellulePourAppliquer[0]->setValue(1);
        celluleACCompter[0]->setValue(1); interval[0]->setCurrentIndex(1);
        borneInf[0]->setValue(2);borneSup[0]->setValue(3);couleur[0]->setCurrentIndex(0);

        etatCellulePourAppliquer[1]->setValue(0);
        celluleACCompter[1]->setValue(1); interval[1]->setCurrentIndex(0);
        borneInf[1]->setValue(3);borneSup[1]->setValue(3);couleur[1]->setCurrentIndex(1);
    }
    else
        ajoutReglePredefini(nom);


}

void Regle2D::ajoutReglePredefini(QString nom){
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
