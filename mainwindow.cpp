#include "mainwindow.h"
#include "autocell.h"


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
    icon.push_back(new QIcon(QCoreApplication::applicationDirPath() + "/s.jpg"));
    icon.push_back(new QIcon(QCoreApplication::applicationDirPath() + "/play.jpeg"));
    icon.push_back(new QIcon(QCoreApplication::applicationDirPath() + "/stop.png"));
    icon.push_back(new QIcon(QCoreApplication::applicationDirPath() + "/help.jpeg"));
    action.push_back(new QAction(*icon[0],"&Simulation Ctrl+S",this));
    action.push_back(new QAction(*icon[1],"&Play",this));
    action.push_back(new QAction(*icon[2],"&Stop",this));
    action.push_back(new QAction(*icon[3],"&Help",this));
    action[0]->setShortcut(QKeySequence("Ctrl+S"));
    action[0]->activate(QAction::Trigger);
    toolBar->addAction(action[0]);toolBar->addAction(action[1]);toolBar->addAction(action[2]);
    toolBar->addSeparator();
    toolBar->addWidget(choixSim);
    toolBar->addAction(action[3]);
    toolBar->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    toolBar->setFloatable(false);
    toolBar->setStyleSheet("QToolBar{border: 1px solid black;}");

    connect(action[0],&QAction::triggered,this,&MainWindow::runSim);
    connect(choixSim,&QComboBox::currentTextChanged,this,&MainWindow::setOption);

}

void MainWindow::createDockOption(){

    optionDock = new QDockWidget("Option",this);
    optionDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //optionDock->setWidget(label[0]);
    optionDock->setMinimumWidth(100);
    optionDock->setFeatures(QDockWidget::NoDockWidgetFeatures);optionDock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
    setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, optionDock);
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
    QLabel* a = new QLabel("Cell Number");
    b = new QSpinBox;
    b->setRange(5,80);
    b->setValue(15);

    QLabel* aa = new QLabel("Cell Color");
    QPushButton* bb=new QPushButton;


    color = new QColorDialog;
    connect(bb,SIGNAL(clicked(bool)),this,SLOT(chooseColor()));
    connect(color,SIGNAL(currentColorChanged(QColor)),this,SLOT(changeColor(QColor)));
    connect(b, SIGNAL(valueChanged(int)),this,SLOT(changeNbCell(int)));

    layoutBoxDim->addWidget(a,0,0);
    layoutBoxDim->addWidget(b,0,1);
    layoutBoxDim->addWidget(aa,1,0);
    layoutBoxDim->addWidget(bb,1,1);
    boxDim->setLayout(layoutBoxDim);
    boxDim->setMaximumHeight(100);
    label.push_back(new QLabel("Dimension"));
    label[0]->setStyleSheet("QLabel{font:bold;}");

    QWidget* w = new QWidget;

    layout1D->addWidget(separator,0,0);
    layout1D->addWidget(boxDim,1,0);
    layout1D->addWidget(w,2,0);
    option1D->setLayout(layout1D);
}

void MainWindow::createOption2D(){
    option2D = new QWidget;
}

/*##########################SLOT######################################*/

void MainWindow::runSim(){
   if(choixSim->currentText() == "1D" && auto1D == nullptr){
       auto1D = new Autocell;
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
    b->setValue(15);
}

void MainWindow::setOption(const QString& automate){
    if (automate == "1D"){
        optionDock->setWidget(option1D);
    }
    else if (automate == "2D"){
        optionDock->setWidget(option2D);
    }
}

void MainWindow::changeNbCell(int a){
    if(auto1D != nullptr){
        auto1D->setDimension(a);
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
