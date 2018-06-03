#include "mainwindow.h"
#include "autocell.h"
#include <iostream>

Autocell* MainWindow::auto1D = nullptr;

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
    icon.push_back(new QIcon(QCoreApplication::applicationDirPath() + "/media-playback-stop.png"));
    icon.push_back(new QIcon(QCoreApplication::applicationDirPath() + "/document-save.png"));
    icon.push_back(new QIcon(QCoreApplication::applicationDirPath() + "/document-open-folder.png"));
    icon.push_back(new QIcon(QCoreApplication::applicationDirPath() + "/help-browser.png"));
    action.push_back(new QAction(*icon[0],"&Lance Simulation Ctrl+S",this));
    action.push_back(new QAction(*icon[1],"&StartSim",this));
    action.push_back(new QAction(*icon[2],"&StopSim",this));
    action.push_back(new QAction(*icon[3],"&SaveSim",this));
    action.push_back(new QAction(*icon[4],"&OpenSim",this));
    action.push_back(new QAction(*icon[5],"&Help",this));
    action[0]->setShortcut(QKeySequence("Ctrl+S"));
    action[0]->activate(QAction::Trigger);
    toolBar->addAction(action[0]);toolBar->addAction(action[1]);toolBar->addAction(action[2]);
    toolBar->addSeparator();
    toolBar->addWidget(choixSim);
    toolBar->addSeparator();
    toolBar->addAction(action[3]);
    toolBar->addAction(action[4]);
    toolBar->addWidget(new WSpacer);
    toolBar->addAction(action[5]);
    toolBar->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    toolBar->setFloatable(false);
    toolBar->setStyleSheet("QToolBar{border: 1px solid black;}");

    connect(action[0],&QAction::triggered,this,&MainWindow::openSim);
    connect(choixSim,&QComboBox::currentTextChanged,this,&MainWindow::setOption);
    connect(action[1], SIGNAL(triggered()),this,SLOT(play()));

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
}

/*##########################SLOT######################################*/

void MainWindow::openSim(){
   if(choixSim->currentText() == "1D" && auto1D == nullptr){
       auto1D = new Autocell;
       auto1D->setDimension(larg1D->value());
       auto1D->setNbSim(nbSim1D->value());
       subWin = central->addSubWindow(auto1D);
       //subWin->setoptionDock(QMdiSubWindow::RubberBandMove);
       subWin->show();
       auto1D->setAttribute(Qt::WA_DeleteOnClose);
       subWin->setAttribute(Qt::WA_DeleteOnClose);
       connect(subWin,&QMdiSubWindow::destroyed,this,&MainWindow::clearAuto1D);
       connect(auto1D,SIGNAL(endSim()),this,SLOT(changeSize()));

       setCentralWidget(central);
       //central->setViewMode(QMdiArea::TabbedView);
   }
   else if(choixSim->currentText() == "Choix Automate"){
       QMessageBox::information(this,"information","Vous devez choisir un automate!");
   }
   else if(choixSim->currentText() == "2D"){
       QMessageBox::information(this,"information","l'automate 2D n'est pas encore implémenté!");
   }
   else{
       QMessageBox::information(this,"information","Vous ne pouvez pas créer 2 automates <strong>identiques</strong> en même temps");
   }
}

void MainWindow::clearAuto1D(){
    auto1D = nullptr;
    subWin = nullptr;
    larg1D->setValue(15);
    nbSim1D->setValue(20);
    regle1D->setValue(0);
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
        auto1D->setDimension(a);
    }
}

void MainWindow::changeNbSim(int a){
    if(auto1D != nullptr){
        auto1D->setNbSim(a);
    }
}
void MainWindow::changeRegle(int a){
    if(auto1D != nullptr){
        auto1D->setRegle(a);
    }
}

void MainWindow::chooseColor(){
    color->show();
}

void MainWindow::changeColor(QColor a){
    if(auto1D != nullptr){
        auto1D->setColor(a);
    }
}

void MainWindow::changeSize(){
    if (subWin != nullptr)
        subWin->adjustSize();
}

void MainWindow::play(){
    QMdiSubWindow* sub =central->currentSubWindow();
    if(sub != nullptr){
        Autocell* a = dynamic_cast<Autocell*>(sub->widget());
        if (a!=nullptr)a->runSim();else std::cout<<"caca";
    }

}
