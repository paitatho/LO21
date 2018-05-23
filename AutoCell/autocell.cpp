 #include "autocell.h"


void Autocell::synchronizeNumToNumBit(int i){
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
    num->setValue(a);
}

void Autocell::cellSelected(int a,int b){
    if (depart->item(a,b)->backgroundColor() == "white")
         depart->item(a,b)->setBackgroundColor(*color);
    else
         depart->item(a,b)->setBackgroundColor("white");
}

void Autocell::runSim(bool){
    unsigned int nb = nbSim->value();
    AutomateManager& aM = AutomateManager::getInstance();
    Etat1D e(dimension);
    for (int i= 0; i<dimension;i++){
        if (depart->item(0,i)->backgroundColor() == *color){
            e.setCellule(i,true);
        }
    }
    Simulateur<Automate1D,Etat1D> s(aM.getAutomate(num->value()), e);
    if (etats == nullptr){
        etats = new QTableWidget(nb,dimension,this);
        etats->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        etats->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        etats->verticalHeader()->hide();
        etats->horizontalHeader()->hide();
    }
    etats->setFixedSize(dimension * taille,nb * taille);
    if(nb != etats->rowCount())etats->setRowCount(nb);
    if(dimension != etats->columnCount())etats->setColumnCount(dimension);

    for( unsigned int i = 0; i<nb; i++){
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
    num = new QSpinBox(this);
    num->setRange(0,255);
    num->setValue(0);
    num->setAlignment(Qt::AlignCenter);
    //num->setFixedWidth(50);
    numl = new QLabel("Numéro",this);
    numl->setAlignment(Qt::AlignCenter);
    numc = new QVBoxLayout;
    numc->addWidget(numl,Qt::AlignAbsolute);
    numc->addWidget(num,Qt::AlignAbsolute);
    //numc->setSizeConstraint(QLayout::SetFixedSize);
    numeroc = new QHBoxLayout;
    numeroc->addLayout(numc);

    zeroOneValidator = new QIntValidator(this);
    zeroOneValidator->setRange(0,1);

    color = new QColor(0,0,0);

    for (int i = 0; i<8;i++){
        numeroBit[i] = new QLineEdit(this);
        numeroBit[i]->setFixedWidth(20);
        numeroBit[i]->setMaxLength(1);
        numeroBit[i]->setText("0");
        numeroBit[i]->setValidator(zeroOneValidator);
        numeroBitl[i]=new QLabel(this);

        bitc[i] = new QVBoxLayout;
        bitc[i]->addWidget(numeroBitl[i]);
        bitc[i]->addWidget(numeroBit[i]);
        numeroc->addLayout(bitc[i]);
    }


    numeroBitl[0]->setText("111");
    numeroBitl[1]->setText("110");
    numeroBitl[2]->setText("101");
    numeroBitl[3]->setText("100");
    numeroBitl[4]->setText("011");
    numeroBitl[5]->setText("010");
    numeroBitl[6]->setText("001");
    numeroBitl[7]->setText("000");

    depart = new QTableWidget(1,dimension,this);
    layout = new QGridLayout(this);
    layout->addLayout(numeroc,1,0,Qt::AlignVCenter);
    depart->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    depart->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    depart->verticalHeader()->hide();
    depart->horizontalHeader()->hide();
    layout->addWidget(depart,2,0);
    depart->setFixedSize(dimension * taille, taille);
    this->setEtatDepartDimension(dimension);
    QWidget::connect(depart, SIGNAL(cellDoubleClicked(int,int)),this,SLOT(cellSelected(int,int)));

    simulation = new QPushButton("Simulation",this);
    nbSim = new QSpinBox(this);
    nbSim->setRange(0,255);
    nbSim->setValue(20);
    sim = new QHBoxLayout;
    sim->addWidget(simulation,Qt::AlignVCenter);
    sim->addWidget(nbSim);
    layout->addLayout(sim,3,0);
    setLayout(layout);
    this->runSim(true);

    QWidget::connect(simulation, SIGNAL(clicked(bool)),this,SLOT(runSim(bool)));


    QWidget::connect(num, SIGNAL(valueChanged(int)),this,SLOT(synchronizeNumToNumBit(int)));

    for (unsigned int i=0; i<8;i++){
        QWidget::connect(numeroBit[i],SIGNAL(textChanged(QString)),this,SLOT(synchronizeNumBitToNum(QString)));
    }

    QWidget::connect(num, SIGNAL(valueChanged(int)),this,SLOT(synchronizeNumToNumBit(int)));

}

void Autocell::setDimension(int dim){
    setEtatDepartDimension(dim);
    dimension=dim;
    this->runSim(true);
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
    this->runSim(true);
}

