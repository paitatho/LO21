#include "mainwindow.h"
#include "autocell.h"
#include <iostream>
#include <typeinfo>


Autocell1D* MainWindow::auto1D = nullptr;
Autocell2D* MainWindow::auto2D = nullptr;

MainWindow::MainWindow(): QMainWindow(){

    createToolBar();
    createDockOption();
    createMdiArea();
    createOption1D();
    createOption2D();
    setStyleSheet("QMainWindow::separator {background: black;width: 1px;height: 1px;}");
    setWindowTitle("AutoCell");
}


void MainWindow::createToolBar(){
    choixSim = new QComboBox;
    choixSim->addItem("Choix Automate"); choixSim->addItem("1D");choixSim->addItem("2D");

    toolBar = addToolBar("file");
    //icon récup dans /usr/share/icons/oxygen/22x22/actions
    icon.push_back(new QIcon(QCoreApplication::applicationDirPath() + "/media-record.png"));
    icon.push_back(new QIcon(QCoreApplication::applicationDirPath() + "/media-playback-start.png"));
    icon.push_back(new QIcon(QCoreApplication::applicationDirPath() + "/media-playback-pause.png"));
    icon.push_back(new QIcon(QCoreApplication::applicationDirPath() + "/media-playback-stop.png"));
    icon.push_back(new QIcon(QCoreApplication::applicationDirPath() + "/document-save.png"));
    icon.push_back(new QIcon(QCoreApplication::applicationDirPath() + "/document-open-folder.png"));
    icon.push_back(new QIcon(QCoreApplication::applicationDirPath() + "/help-browser.png"));
    action.push_back(new QAction(*icon[0],"&Lance Simulation Ctrl+S",this));
    action.push_back(new QAction(*icon[1],"&StartSim",this));
    action.push_back(new QAction(*icon[2],"&PauseSim",this));
    action.push_back(new QAction(*icon[3],"&StopSim",this));
    action.push_back(new QAction(*icon[4],"&SaveSim",this));
    action.push_back(new QAction(*icon[5],"&OpenSim",this));
    action.push_back(new QAction(*icon[6],"&Help",this));
    action[0]->setShortcut(QKeySequence("Ctrl+S"));
    action[0]->activate(QAction::Trigger);
    toolBar->addAction(action[0]);toolBar->addAction(action[1]);toolBar->addAction(action[2]);toolBar->addAction(action[3]);
    toolBar->addSeparator();
    toolBar->addWidget(choixSim);
    toolBar->addSeparator();
    toolBar->addAction(action[4]);
    toolBar->addAction(action[5]);
    toolBar->addWidget(new WSpacer);
    toolBar->addAction(action[6]);
    toolBar->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    toolBar->setFloatable(false);
    toolBar->setStyleSheet("QToolBar{border: 1px solid black;}");

    connect(action[0],&QAction::triggered,this,&MainWindow::openSim);
    connect(action[1], SIGNAL(triggered()),this,SLOT(play()));
    connect(action[2], SIGNAL(triggered()),this,SLOT(pause()));
    connect(action[3],SIGNAL(triggered()),this,SLOT(clear()));

}

void MainWindow::createDockOption(){

    optionDock = new QDockWidget(this);
    QFont* police = new QFont("",14,QFont::Bold);
    QLabel* titre=new QLabel(tr("Option"));titre->setAlignment(Qt::AlignCenter);titre->setFont(*police);
    optionDock->setTitleBarWidget(titre);
    optionDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //optionDock->setWidget(label[0]);
    optionDock->setMinimumWidth(100);
    optionDock->setFeatures(QDockWidget::NoDockWidgetFeatures);optionDock->setFeatures(/*QDockWidget::DockWidgetClosable | */QDockWidget::DockWidgetMovable);
    setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, optionDock);
    optionDock->hide();
}

void MainWindow::createMdiArea(){
    central = new QMdiArea;
    central->setStyleSheet("QMdiArea::separator {background: black;width: 1px;height: 1px;}");
    setCentralWidget(central);
    connect(central,SIGNAL(subWindowActivated(QMdiSubWindow*)),this,SLOT(current(QMdiSubWindow*)));
}



void MainWindow::createOption1D(){
    option1D = new QWidget;
    layout1D = new QGridLayout;

    QFrame* sep = new QFrame();sep->setFrameShape(QFrame::HLine);sep ->setFrameShadow(QFrame::Sunken);sep->setMaximumHeight(10);

    boxDim = new QGroupBox(tr("Dimension"));
    layoutBoxDim = new QGridLayout;
    boxCel = new QGroupBox(tr("Cellule"));
    layoutBoxCel =new QGridLayout;

    QComboBox* bb=new QComboBox;bb->addItems((QStringList() << "white"<< "black"<<"green" << "red"<<"blue"<<"yellow"<<"pink"<<"brown"<<"grey"));

    nbSim1D = new QSpinBox;nbSim1D->setRange(5,40);nbSim1D->setValue(20);
    regle1D = new QSpinBox;regle1D->setRange(0,255);regle1D->setValue(150);
    larg1D = new QSpinBox;larg1D->setRange(5,80);larg1D->setValue(15);
    QSpinBox* taille = new QSpinBox();taille->setValue(17);taille->setRange(6,40);

    connect(bb,SIGNAL(currentTextChanged(QString)),this,SLOT(changeColor(QString)));
    connect(larg1D, SIGNAL(valueChanged(int)),this,SLOT(changeLargeur(int)));
    connect(nbSim1D, SIGNAL(valueChanged(int)),this,SLOT(changeHauteur(int)));
    connect(regle1D, SIGNAL(valueChanged(int)),this,SLOT(changeRegle1D(int)));
    connect(taille, SIGNAL(valueChanged(int)),this,SLOT(changeTaille(int)));


    layoutBoxDim->addWidget(new QLabel("Largeur"),0,0);layoutBoxDim->addWidget(larg1D,0,1);
    layoutBoxDim->addWidget(new QLabel("Nombre Simu"),1,0);layoutBoxDim->addWidget(nbSim1D,1,1);
    layoutBoxDim->addWidget(new QLabel("Taille"), 2,0);layoutBoxDim->addWidget(taille, 2,1);

    layoutBoxCel->addWidget(bb, 0,0,1,2);
    layoutBoxCel->addWidget(new QLabel("Règle"), 1,0);
    layoutBoxCel->addWidget(regle1D, 1,1);
    layoutBoxCel->addWidget(new QLabel("Régle"), 1,0);layoutBoxCel->addWidget(regle1D, 1,1);

    QPushButton* initialisation=new QPushButton("Etat initial aléatoire");
    layoutBoxCel->addWidget(initialisation, 2,0,1,2);
    connect(initialisation,SIGNAL(clicked()),this,SLOT(initialiseur()));
    QPushButton* initialisationSym=new QPushButton("Etat initial symétrique");
    layoutBoxCel->addWidget(initialisationSym, 3,0,1,2);
    connect(initialisationSym,SIGNAL(clicked()),this,SLOT(initialiseurSym()));

    boxDim->setLayout(layoutBoxDim);boxDim->setMaximumHeight(150);
    boxCel->setLayout(layoutBoxCel);boxCel->setMaximumHeight(200);

    label.push_back(new QLabel("Dimension"));label[0]->setStyleSheet("QLabel{font:bold;}");

    layout1D->addWidget(sep,0,0);layout1D->addWidget(boxDim,1,0);layout1D->addWidget(boxCel,2,0);layout1D->addWidget(new QWidget,3,0);
    option1D->setLayout(layout1D);
}

void MainWindow::createOption2D(){
    option2D = new QWidget;
    layout2D = new QGridLayout;

    QFrame* sep = new QFrame();
    sep ->setFrameShape(QFrame::HLine);
    sep ->setFrameShadow(QFrame::Sunken);
    sep->setMaximumHeight(10);

    QPushButton* boutonRegle=new QPushButton("Regle");

    boxDim2D = new QGroupBox(tr("Dimension"));
    layoutBoxDim2D = new QGridLayout;
    boxCel2D = new QGroupBox(tr("Cellule"));
    layoutBoxCel2D =new QGridLayout;
    boxParam2D = new QGroupBox(tr("Param"));
    layoutBoxParam2D =new QGridLayout;

    larg2D = new QSpinBox;larg2D->setRange(5,60);larg2D->setValue(35);
    haut2D = new QSpinBox;haut2D->setRange(5,60);haut2D->setValue(35);
    speed2D = new QSpinBox;speed2D->setRange(1,1000);speed2D->setValue(50);
    mode2D = new QComboBox;
    mode2D->addItem("Continu");mode2D->addItem("pas à pas");
    taille = new QSpinBox();taille->setValue(17);taille->setRange(6,40);
    layoutBoxDim2D->addWidget(new QLabel("Largeur"),0,0);layoutBoxDim2D->addWidget(larg2D,0,1);
    layoutBoxDim2D->addWidget(new QLabel("Hauteur"),1,0);layoutBoxDim2D->addWidget(haut2D,1,1);
    layoutBoxDim2D->addWidget(new QLabel("Taille"), 2,0);layoutBoxDim2D->addWidget(taille, 2,1);

    connect(larg2D, SIGNAL(valueChanged(int)),this,SLOT(changeLargeur(int)));
    connect(haut2D, SIGNAL(valueChanged(int)),this,SLOT(changeHauteur(int)));

    layoutBoxCel2D->addWidget(boutonRegle, 0,0,1,2);

    connect(taille,SIGNAL(valueChanged(int)),this,SLOT(changeTaille(int)));

    fenetreRegle2D = new Regle2D;
    fenetreRegle2D->hide();
    connect(boutonRegle,SIGNAL(clicked()),this,SLOT(afficherRegle2D()));
    connect(fenetreRegle2D,SIGNAL(envoiRegle(std::vector<std::vector<unsigned short int> >,std::vector<std::string>)),this,SLOT(changeRegle2D(std::vector<std::vector<unsigned short int> >,std::vector<std::string>)));

    layoutBoxParam2D->addWidget(new QLabel("Delai(ms)"), 0,0);
    layoutBoxParam2D->addWidget(speed2D, 0,1);
    connect(speed2D,SIGNAL(valueChanged(int)),this, SLOT(changeSpeed(int)));
    layoutBoxParam2D->addWidget(new QLabel("mode"), 1,0);
    layoutBoxParam2D->addWidget(mode2D, 1,1);
    QPushButton* initialisation=new QPushButton("Etat initial aléatoire");
    layoutBoxParam2D->addWidget(initialisation, 2,0,1,2);
    connect(initialisation,SIGNAL(clicked()),this,SLOT(initialiseur()));
    QPushButton* initialisationSym=new QPushButton("Etat initial symétrique");
    layoutBoxParam2D->addWidget(initialisationSym, 3,0,1,2);
    connect(initialisationSym,SIGNAL(clicked()),this,SLOT(initialiseurSym()));

    boxDim2D->setLayout(layoutBoxDim2D);boxDim2D->setMaximumHeight(150);
    boxCel2D->setLayout(layoutBoxCel2D);boxCel2D->setMaximumHeight(75);
    boxParam2D->setLayout(layoutBoxParam2D);boxParam2D->setMaximumHeight(200);

    layout2D->addWidget(sep,0,0);
    layout2D->addWidget(boxDim2D,1,0);
    layout2D->addWidget(boxCel2D,2,0);
    layout2D->addWidget(boxParam2D,3,0);
    layout2D->addWidget(new QWidget,4,0);
    option2D->setLayout(layout2D);


}

/*##########################SLOT######################################*/

void MainWindow::openSim(){
   if(choixSim->currentText() == "1D" && auto1D == nullptr){
       auto1D = new Autocell1D;
       auto1D->setLargeur(larg1D->value());
       auto1D->setHauteur(nbSim1D->value());
       auto1D->setRegle(150);
       subWin = central->addSubWindow(auto1D);
       subWin->show();
       auto1D->setAttribute(Qt::WA_DeleteOnClose);
       subWin->setAttribute(Qt::WA_DeleteOnClose);
       connect(subWin,&QMdiSubWindow::destroyed,this,&MainWindow::clearAuto1D);
       connect(auto1D,SIGNAL(endSim()),this,SLOT(changeSize()));
       connect(auto1D,SIGNAL(endSim()),this,SLOT(allow()));
       setCentralWidget(central);
       //central->setViewMode(QMdiArea::TabbedView);
   }
   else if(choixSim->currentText() == "Choix Automate"){
       QMessageBox::information(this,"information","Vous devez choisir un automate!");
   }
   else if(choixSim->currentText() == "2D" && auto2D == nullptr){
       auto2D =new Autocell2D;
       subWin2D = central->addSubWindow(auto2D);
       auto2D->setAttribute(Qt::WA_DeleteOnClose);
       subWin2D->setAttribute(Qt::WA_DeleteOnClose);
       subWin2D->show();
       connect(subWin2D,&QMdiSubWindow::destroyed,this,&MainWindow::clearAuto2D);
       connect(auto2D,SIGNAL(endSim()),this,SLOT(allow()));
   }
   else{
       QMessageBox::information(this,"information","Vous ne pouvez pas créer 2 automates <strong>identiques</strong> en même temps");
   }
}

void MainWindow::changeLargeur(int a){
    QMdiSubWindow* sub =central->currentSubWindow();
    if(sub != nullptr){
        Autocell* au = dynamic_cast<Autocell*>(sub->widget());
        if (au!=nullptr)au->setLargeur(a);
        sub->adjustSize();
    }
}

void MainWindow::changeHauteur(int a){
    QMdiSubWindow* sub =central->currentSubWindow();
    if(sub != nullptr){
        Autocell* au = dynamic_cast<Autocell*>(sub->widget());
        if (au != nullptr)au->setHauteur(a);
        sub->adjustSize();
    }
}
void MainWindow::changeRegle1D(int a){
    if(auto1D != nullptr)auto1D->setRegle(a);
}


void MainWindow::changeColor(QString a){
    if(auto1D != nullptr)auto1D->setColor(a);
}

void MainWindow::changeSize(){
    if (subWin != nullptr) subWin->adjustSize();
}

void MainWindow::changeSpeed(int s){
    QMdiSubWindow* sub =central->currentSubWindow();
    if(sub != nullptr){
        Autocell* a = dynamic_cast<Autocell*> (sub->widget());
        if (a!=nullptr) a->setSpeed(s);
    }
}

void MainWindow::play(){
    QMdiSubWindow* sub =central->currentSubWindow();
    if(sub != nullptr){
        Autocell* a = dynamic_cast<Autocell*> (sub->widget());
        if (a!=nullptr){
            if(a==auto2D && mode2D->currentText()=="Continu")a->setContinu(true);
            else a->setContinu(false);
            action[3]->setEnabled(false);
            a->runSim();
        }
        else throw "erreur slot play()";
    }
}

void MainWindow::pause(){
    QMdiSubWindow* sub =central->currentSubWindow();
    if(sub != nullptr){
        Autocell* a = dynamic_cast<Autocell*>(sub->widget());
        if (a!=nullptr)a->setContinu(false);
    }
}

void MainWindow::clear(){
    QMdiSubWindow* sub =central->currentSubWindow();
    if(sub != nullptr){
        Autocell* a = dynamic_cast<Autocell*>(sub->widget());
        if (a!=nullptr){ a->setContinu(false), a->clear();}
    }
}

void MainWindow::current(QMdiSubWindow *w){
    if (w != nullptr){
        QMdiSubWindow* sub =central->currentSubWindow();
        Autocell* a = dynamic_cast<Autocell*>(sub->widget());
        if(a!=nullptr){
            if(a == auto1D){
                optionDock->show();
                optionDock->setWidget(option1D);
            }
            else if (a==auto2D){
                optionDock->show();
                optionDock->setWidget(option2D);
            }
        }
    }
    else optionDock->hide();
}


void MainWindow::saveAppState(){
    QSettings settings("Reyhan&Thomas", "AutoCell");
    settings.clear();
    settings.setValue("typeAutomate", choixSim->currentText());
    if(choixSim->currentText()=="1D"){
        settings.setValue("larg1D", larg1D->value());
        settings.setValue("nbSim1D", nbSim1D->value());
        settings.setValue("regle1D", regle1D->value());

    }
    if(choixSim->currentText()=="2D"){
        settings.setValue("larg2D", larg2D->value());
        settings.setValue("haut2D", haut2D->value());
        settings.setValue("speed2D", speed2D->value());
        settings.setValue("mode2D", mode2D->currentText());
        settings.setValue("regle2DJeu", fenetreRegle2D->get_regleBase()->currentText());
        settings.setValue("nbEtat", fenetreRegle2D->get_nbEtat()->value());
        settings.setValue("tailleCellule", taille->value());
        for(unsigned int i=0; i<(fenetreRegle2D->get_nbEtat()->value()); ++i){
            settings.setValue("reglePassageEtatDepart"+QString::fromStdString(std::to_string(i)), fenetreRegle2D->get_etatCellulePourAppliquer()[i]->value());
            settings.setValue("reglePassageEtatAcompter"+QString::fromStdString(std::to_string(i)), fenetreRegle2D->get_celluleACCompter()[i]->value());
            settings.setValue("reglePassageTypeInterval"+QString::fromStdString(std::to_string(i)), fenetreRegle2D->get_interval()[i]->currentText());
            settings.setValue("reglePassageBorneInf"+QString::fromStdString(std::to_string(i)), fenetreRegle2D->get_borneInf()[i]->value());
            settings.setValue("reglePassageBorneSup"+QString::fromStdString(std::to_string(i)), fenetreRegle2D->get_borneSup()[i]->value());
            settings.setValue("reglePassageCouleurEtat"+QString::fromStdString(std::to_string(i)), fenetreRegle2D->get_couleur()[i]->currentText());
        }
        QString fileXmlName = QCoreApplication::applicationDirPath()+QString::fromStdString("/lastEtat.xml");
        QFile fileXml(fileXmlName);

        // Ouverture du fichier en écriture et en texte. (sort de la fonction si le fichier ne s'ouvre pas)
        if(!fileXml.open(QFile::WriteOnly | QFile::Text))
            return;
        QXmlStreamWriter writer(&fileXml);

        // Active l'indentation automatique du fichier XML pour une meilleur visibilité
        writer.setAutoFormatting(true);

        // Insert la norme de codification du fichier XML :
        writer.writeStartDocument();

        // Élément racine du fichier XML
        writer.writeStartElement("dernierEtat");
        for(unsigned int i=0; i<auto2D->get_etats()->rowCount() ;++i){
            for(unsigned int j=0; j<auto2D->get_etats()->columnCount(); ++j){
                writer.writeStartElement("valCellule");
                writer.writeAttribute("row", QString::fromStdString(std::to_string(i)));
                writer.writeAttribute("col", QString::fromStdString(std::to_string(j)));
                writer.writeEmptyElement("val");
                writer.writeAttribute("value", (auto2D->get_etats()->item(i,j)->backgroundColor()).name());
                writer.writeEndElement();
            }

        }
        writer.writeEndElement();
        writer.writeEndDocument();
    }
}

void MainWindow::closeEvent(QCloseEvent* event){
    saveAppState();
    event->accept();
}

void MainWindow::restoreAppState(){
    QSettings settings("Reyhan&Thomas", "AutoCell");
    if(settings.value("typeAutomate") == "1D"){
        choixSim->setCurrentText(settings.value("typeAutomate").toString());
        larg1D->setValue(settings.value("larg1D").toInt());
        nbSim1D->setValue(settings.value("nbSim1D").toInt());
        regle1D->setValue(settings.value("regle1D").toInt());
        openSim();
        play();
    }
    if(settings.value("typeAutomate") == "2D"){
        choixSim->setCurrentText(settings.value("typeAutomate").toString());
        larg2D->setValue(settings.value("larg2D").toInt());
        haut2D->setValue(settings.value("haut2D").toInt());
        speed2D->setValue(settings.value("speed2D").toInt());
        mode2D->setCurrentText(settings.value("mode2D").toString());
        fenetreRegle2D->setRegleBase(settings.value("regle2DJeu").toString());
        fenetreRegle2D->setNbEtat(settings.value("nbEtat").toInt());
        taille->setValue(settings.value("tailleCellule").toInt());
        for(unsigned int i=0; i<(fenetreRegle2D->get_nbEtat()->value()); ++i){
            fenetreRegle2D->setEtatCellulePourAppliquer(i, settings.value("reglePassageEtatDepart"+QString::fromStdString(std::to_string(i))).toInt());
            fenetreRegle2D->setCelluleACompter(i, settings.value("reglePassageEtatAcompter"+QString::fromStdString(std::to_string(i))).toInt());
            fenetreRegle2D->setInterval(i, settings.value("reglePassageTypeInterval"+QString::fromStdString(std::to_string(i))).toString());
            fenetreRegle2D->setBorneInf(i, settings.value("reglePassageBorneInf"+QString::fromStdString(std::to_string(i))).toInt());
            fenetreRegle2D->setBorneSup(i, settings.value("reglePassageBorneSup"+QString::fromStdString(std::to_string(i))).toInt());
            fenetreRegle2D->setCouleur(i, settings.value("reglePassageCouleurEtat"+QString::fromStdString(std::to_string(i))).toString());
        }
        openSim();
        fenetreRegle2D->sendRegle();

        QString fileXmlName = QCoreApplication::applicationDirPath()+QString::fromStdString("/lastEtat.xml");
        QFile file(fileXmlName);
        QXmlStreamReader xml(&file);

        if(!file.open(QFile::ReadOnly)) { qDebug() << "Cannot read file" << file.errorString(); }
        while(!xml.atEnd())
        {
            if(xml.isStartElement())
            {
                if(xml.name() == "valCellule")
                {
                    unsigned int i = xml.attributes().at(0).value().toInt();
                    unsigned int j = xml.attributes().at(1).value().toInt();
                    xml.readNextStartElement();
                    const QString color = (xml.attributes().at(0).value().toString());
                    auto2D->setEtats(i, j, color);
                }
            }
            xml.readNextStartElement();
        }
    }
}

void MainWindow::changeRegle2D(std::vector<std::vector<unsigned short int>> r,std::vector<std::string> c){
    if(auto2D != nullptr){
        auto2D->setRegle(r);
        auto2D->setCouleur(c);
        auto2D->setNbEtat(r.size());
        auto2D->clear();
    }
}

void MainWindow::changeTaille(int t){
    QMdiSubWindow* sub =central->currentSubWindow();
    if(sub != nullptr){
        Autocell* a = dynamic_cast<Autocell*> (sub->widget());
        if(a!= nullptr){
            a->setTaille(t);
            sub->adjustSize();
        }
    }
}

void MainWindow::initialiseur(){
    QMdiSubWindow* sub =central->currentSubWindow();
    if(sub != nullptr){
        Autocell* a = dynamic_cast<Autocell*> (sub->widget());
        if (a!=nullptr) a->init();
    }
}

void MainWindow::initialiseurSym(){
    QMdiSubWindow* sub =central->currentSubWindow();
    if(sub != nullptr){
        Autocell* a = dynamic_cast<Autocell*> (sub->widget());
        if (a!=nullptr) a->initSym();
    }
}


