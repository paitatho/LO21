 #include "autocell.h"


/*void Autocell::synchronizeNumToNumBit(int i){
    std::string numbit = NumToNumBit(i);
    for (unsigned int i=0;i<numbit.size();i++){
        numeroBit[i]->setText(QString(numbit[i]));
    }
}

void Autocell::synchronizeNumBitToNum(const QString& s){
    if (s=="") return;
    std::string numBit;
    for(unsigned int i=0;i<8;i++){
        numBit += numeroBit[i]->text().toStdString();
    }
    int a = NumBitToNum(numBit);
    //num->setValue(a);
}*/

void Autocell::cellSelected(int a,int b){
    if (depart->item(a,b)->backgroundColor() == "white")
         depart->item(a,b)->setBackgroundColor(*color);
    else
         depart->item(a,b)->setBackgroundColor("white");
}

void Autocell::runSim(){
    AutomateManager& aM = AutomateManager::getInstance();
    Etat1D e(dimension);
    for (int i= 0; i<dimension;i++){
        if (depart->item(0,i)->backgroundColor() == *color){
            e.setCellule(i,true);
        }
    }
    Simulateur<Automate1D,Etat1D> s(aM.getAutomate(regle), e);
    if (etats == nullptr){
        etats = new QTableWidget(nbSim,dimension,this);
        etats->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        etats->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        etats->verticalHeader()->hide();
        etats->horizontalHeader()->hide();
    }
    etats->setFixedSize(dimension * taille,nbSim * taille);
    if(nbSim != etats->rowCount())etats->setRowCount(nbSim);
    if(dimension != etats->columnCount())etats->setColumnCount(dimension);

    for( unsigned int i = 0; i<nbSim; i++){
        s.next();
        for (int j=0;j<dimension;j++){
            if(etats->item(i,j) == nullptr){
                QTableWidgetItem* a = new QTableWidgetItem ("");
                a->setFlags(Qt::NoItemFlags);
                a->setFlags(Qt::ItemIsEnabled);
               // a->setSizeHint(QSize(dimension,dimension));
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

Autocell::Autocell(QWidget* parent) : QWidget(parent){
    this->setWindowTitle("Automate 1D");

    color = new QColor(0,0,0);

    depart = new QTableWidget(1,dimension,this);
    layout = new QGridLayout(this);
    //layout->addLayout(numeroc,1,0,Qt::AlignVCenter);
    depart->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    depart->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    depart->verticalHeader()->hide();
    depart->horizontalHeader()->hide();
    layout->addWidget(depart,2,0);
    depart->setFixedSize(dimension * taille, taille);
    this->setEtatDepartDimension(dimension);
    QWidget::connect(depart, SIGNAL(cellDoubleClicked(int,int)),this,SLOT(cellSelected(int,int)));

    sim = new QHBoxLayout;
    layout->addLayout(sim,3,0);
    setLayout(layout);
    this->runSim();
}

void Autocell::setDimension(int dim){
    setEtatDepartDimension(dim);
    dimension=dim;
    this->runSim();
}

void Autocell::setEtatDepartDimension(int dim){
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

void Autocell::setColor(QColor a){
    delete color;
    color = new QColor(a);
    for(int i=0;i<dimension;i++){
        if(depart->item(0,i)->backgroundColor() != "white")
            depart->item(0,i)->setBackgroundColor(*color);
    }
    this->runSim();
}

