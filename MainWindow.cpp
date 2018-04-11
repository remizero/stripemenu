#include "MainWindow.h"

#include <QPlainTextEdit>
#include <QComboBox>

MainWindow::MainWindow ( QWidget *parent ) : QMainWindow ( parent ) {

  StripeMenu *ribbon = new StripeMenu ();
  //# add a couple of tabs
  ribbon->addTab ( "Home" );
  ribbon->addTab ( "Insert" );
  ribbon->addPane ( "Home", new StripeMenuPanel ( "Edit", true, ribbon ) );
  ribbon->addPane ( "Home", new StripeMenuPanel ( "Panel 3", true, ribbon ) );
  ribbon->addPane ( "Insert", new StripeMenuPanel ( "Panel 1", true, ribbon ) );
  ribbon->addPane ( "Insert", new StripeMenuPanel ( "Panel 2", true, ribbon ) );

  QAction *action = new QAction ( this );
  action->setIcon ( QIcon ( ":/icons/RibbonUp.svg" ) );
  action->setToolTip ( "Acción 1" );
  ribbon->addAction ( "Edit", action, 0, 0, 1, 1 );

  QAction *action1 = new QAction ( this );
  action1->setIcon ( QIcon ( ":/icons/RibbonUp.svg" ) );
  action1->setToolTip ( "Acción 2" );
  ribbon->addAction ( "Edit", action1, 0, 1, 1, 1 );

  QAction *action2 = new QAction ( this );
  action2->setIcon ( QIcon ( ":/icons/RibbonUp.svg" ) );
  action2->setToolTip ( "Acción 3" );
  ribbon->addAction ( "Edit", action2, 0, 2, 1, 1 );

  QAction *action3 = new QAction ( this );
  action3->setIcon ( QIcon ( ":/icons/RibbonUp.svg" ) );
  action3->setToolTip ( "Acción 4" );
  ribbon->addAction ( "Edit", action3, 1, 0, 1, 1 );

  QAction *action4 = new QAction ( this );
  action4->setIcon ( QIcon ( ":/icons/RibbonUp.svg" ) );
  action4->setToolTip ( "Acción 5" );
  ribbon->addAction ( "Edit", action4, 1, 1, 1, 1 );

  QAction *action5 = new QAction ( this );
  action5->setIcon ( QIcon ( ":/icons/RibbonUp.svg" ) );
  action5->setToolTip ( "Acción 6" );
  ribbon->addAction ( "Edit", action5, 1, 2, 1, 1 );

  QAction *action6 = new QAction ( this );
  action6->setIcon ( QIcon ( ":/icons/RibbonUp.svg" ) );
  action6->setToolTip ( "Acción 7" );
  ribbon->addAction ( "Edit", action6, 2, 0, 1, 1 );

  QAction *action7 = new QAction ( this );
  action7->setIcon ( QIcon ( ":/icons/RibbonUp.svg" ) );
  action7->setToolTip ( "Acción 8" );
  ribbon->addAction ( "Edit", action7, 2, 1, 1, 1 );

  QAction *action8 = new QAction ( this );
  action8->setIcon ( QIcon ( ":/icons/RibbonUp.svg" ) );
  action8->setToolTip ( "Acción 9" );
  ribbon->addAction ( "Edit", action8, 2, 2, 1, 1 );

  QComboBox *comboBox = new QComboBox ( this );
  for ( int i = 0; i < 10; i++ ) {

    comboBox->addItem ( "item " + QString::number ( i ) );
  }
  ribbon->addWidget ( "Panel 3", comboBox, 0, 0, 5, 1 );


  this->setMenuWidget ( ribbon );
  this->setCentralWidget ( new QPlainTextEdit ( this ) );
  //this->setCentralWidget ( new RibbonMenuPanel ( "Titulo del panel", true, this ) );
}
