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
    connect(choixSim,&QComboBox::currentTextChanged,this,&MainWindow::setOption);
    connect(action[1], SIGNAL(triggered()),this,SLOT(play()));
    connect(action[2], SIGNAL(triggered()),this,SLOT(pause()));
    connect(action[3],SIGNAL(triggered()),this,SLOT(clear()));

}

void MainWindow::createDockOption(){

    optionDock = new QDockWidget("Option",this);
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

    separator = new QFrame();
    separator ->setFrameShape(QFrame::HLine);
    separator ->setFrameShadow(QFrame::Sunken);
    separator->setMaximumHeight(10);

    boxDim = new QGroupBox(tr("Dimension"));
    layoutBoxDim = new QGridLayout;
    boxCel = new QGroupBox(tr("Cellule"));
    layoutBoxCel =new QGridLayout;

    larg1D = new QSpinBox;
    larg1D->setRange(5,80);
    larg1D->setValue(15);

    QPushButton* bb=new QPushButton;

    nbSim1D = new QSpinBox;
    nbSim1D->setRange(5,40);
    nbSim1D->setValue(20);

    regle1D = new QSpinBox;
    regle1D->setRange(0,255);
    regle1D->setValue(0);

    color = new QColorDialog;
    connect(bb,SIGNAL(clicked(bool)),this,SLOT(chooseColor()));
    connect(color,SIGNAL(currentColorChanged(QColor)),this,SLOT(changeColor(QColor)));
    connect(larg1D, SIGNAL(valueChanged(int)),this,SLOT(changeNbCell(int)));
    connect(nbSim1D, SIGNAL(valueChanged(int)),this,SLOT(changeNbSim(int)));
    connect(regle1D, SIGNAL(valueChanged(int)),this,SLOT(changeRegle(int)));


    layoutBoxDim->addWidget(new QLabel("Largeur"),0,0);
    layoutBoxDim->addWidget(larg1D,0,1);
    layoutBoxDim->addWidget(new QLabel("Nombre Simu"),1,0);
    layoutBoxDim->addWidget(nbSim1D,1,1);

    layoutBoxCel->addWidget(new QLabel("Couleur"), 0,0);
    layoutBoxCel->addWidget(bb, 0,1);
    layoutBoxCel->addWidget(new QLabel("Régle"), 1,0);
    layoutBoxCel->addWidget(regle1D, 1,1);

    boxDim->setLayout(layoutBoxDim);
    boxDim->setMaximumHeight(100);
    boxCel->setLayout(layoutBoxCel);
    boxCel->setMaximumHeight(100);

    label.push_back(new QLabel("Dimension"));
    label[0]->setStyleSheet("QLabel{font:bold;}");

    QWidget* w = new QWidget;

    layout1D->addWidget(separator,0,0);
    layout1D->addWidget(boxDim,1,0);
    layout1D->addWidget(boxCel,2,0);
    layout1D->addWidget(w,3,0);
    option1D->setLayout(layout1D);
}

void MainWindow::createOption2D(){
    option2D = new QWidget;
    layout2D = new QGridLayout;

    QPushButton* boutonRegle=new QPushButton("Regle");

    boxDim2D = new QGroupBox(tr("Dimension"));
    layoutBoxDim2D = new QGridLayout;
    boxCel2D = new QGroupBox(tr("Cellule"));
    layoutBoxCel2D =new QGridLayout;
    boxParam2D = new QGroupBox(tr("Param"));
    layoutBoxParam2D =new QGridLayout;

    larg2D = new QSpinBox;
    larg2D->setRange(5,80);
    larg2D->setValue(30);
    haut2D = new QSpinBox;
    haut2D->setRange(5,80);
    haut2D->setValue(30);
    speed2D = new QSpinBox;
    speed2D->setRange(1,1000);
    speed2D->setValue(100);
    mode2D = new QComboBox;
    mode2D->addItem("Continu");mode2D->addItem("pas à pas");
    layoutBoxDim2D->addWidget(new QLabel("Largeur"),0,0);
    layoutBoxDim2D->addWidget(larg2D,0,1);
    layoutBoxDim2D->addWidget(new QLabel("Hauteur"),1,0);
    layoutBoxDim2D->addWidget(haut2D,1,1);

    layoutBoxCel2D->addWidget(boutonRegle, 0,0,1,2);

    fenetreRegle2D = new Regle2D;
    fenetreRegle2D->hide();
    connect(boutonRegle,SIGNAL(clicked()),this,SLOT(afficherRegle2D()));
    connect(fenetreRegle2D,SIGNAL(envoiRegle(std::vector<std::vector<unsigned short int> >,std::vector<std::string>)),this,SLOT(regle2D(std::vector<std::vector<unsigned short int> >,std::vector<std::string>)));

    layoutBoxParam2D->addWidget(new QLabel("Speed(ms)"), 0,0);
    layoutBoxParam2D->addWidget(speed2D, 0,1);
    layoutBoxParam2D->addWidget(new QLabel("mode"), 1,0);
    layoutBoxParam2D->addWidget(mode2D, 1,1);

    boxDim->setLayout(layoutBoxDim);
    boxDim->setMaximumHeight(100);
    boxCel->setLayout(layoutBoxCel);
    boxCel->setMaximumHeight(100);
    boxParam2D->setLayout(layoutBoxParam2D);
    boxParam2D->setMaximumHeight(100);

    QWidget* w = new QWidget;
    boxDim2D->setLayout(layoutBoxDim2D);
    boxDim2D->setMaximumHeight(100);
    boxCel2D->setLayout(layoutBoxCel2D);
    boxCel2D->setMaximumHeight(100);
    layout2D->addWidget(separator,0,0);
    layout2D->addWidget(boxDim2D,1,0);
    layout2D->addWidget(boxCel2D,2,0);
    layout2D->addWidget(boxParam2D,3,0);
    layout2D->addWidget(w,4,0);
    option2D->setLayout(layout2D);


}

/*##########################SLOT######################################*/

void MainWindow::openSim(){
   if(choixSim->currentText() == "1D" && auto1D == nullptr){
       auto1D = new Autocell1D;
       auto1D->setLargeur(larg1D->value());
       auto1D->setHauteur(nbSim1D->value());
       subWin = central->addSubWindow(auto1D);
       //subWin->setoptionDock(QMdiSubWindow::RubberBandMove);
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


void MainWindow::setOption(const QString& automate){
    if (automate == "1D"){
        optionDock->show();
        optionDock->setWidget(option1D);
    }
    else if (automate == "2D"){
        optionDock->show();
        optionDock->setWidget(option2D);
    }
    else if (automate == "Choix Automate"){
        optionDock->hide();
    }
}

void MainWindow::changeNbCell(int a){
    if(auto1D != nullptr){
        auto1D->setLargeur(a);
    }
}

void MainWindow::changeNbSim(int a){
    if(auto1D != nullptr){
        auto1D->setHauteur(a);
    }
}
void MainWindow::changeRegle(int a){
    if(auto1D != nullptr)auto1D->setRegle(a);
}

void MainWindow::chooseColor() const{
    if(color!=nullptr)color->show();
}

void MainWindow::changeColor(QColor a){
    if(auto1D != nullptr)auto1D->setColor(a);
}

void MainWindow::changeSize(){
    if (subWin != nullptr) subWin->adjustSize();
}

void MainWindow::play(){
    QMdiSubWindow* sub =central->currentSubWindow();
    if(sub != nullptr){
        Autocell* a = dynamic_cast<Autocell*> (sub->widget());
        if (a!=nullptr){
            if(a==auto2D && mode2D->currentText()=="Continu")a->setContinu(true);
            else a->setContinu(false);
            action[3]->setEnabled(false);
            //action[1]->setEnabled(false);
            a->runSim();
        }
        else throw "erreur slot play()";
    }
}

void MainWindow::pause(){
    QMdiSubWindow* sub =central->currentSubWindow();
    if(sub != nullptr){
        Autocell* a = dynamic_cast<Autocell*>(sub->widget());
        if (a!=nullptr/* && a==auto2D*/)a->setContinu(false);
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
    /*if (w != nullptr){
        Autocell* a = dynamic_cast<Autocell*>(w);
        if(a == auto1D){
            optionDock->show();
            optionDock->setWidget(option1D);
        }
        else if (a==auto2D){
            optionDock->show();
            optionDock->setWidget(option2D);
        }
    }*/
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
}

void MainWindow::regle2D(std::vector<std::vector<unsigned short int>> r,std::vector<std::string> c){
    if(auto2D != nullptr){
        auto2D->setRegle(r);
        auto2D->setCouleur(c);
        auto2D->clear();
    }
}
