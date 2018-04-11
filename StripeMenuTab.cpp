#include "StripeMenuTab.h"
#include <QLabel>
#include <QDebug>

StripeMenuTab::StripeMenuTab ( QString tabTitle, QWidget *parent, Qt::WindowFlags f ) : QWidget ( parent, f ) {

//# create the spacer and the layout and set it as a widget main layout
  //tabTitle.toLower ().replace ( " ", "" );
  this->setObjectName ( tabTitle.toLower ().replace ( " ", "" ) );
  this->setTitleStripeMenuTab ( tabTitle );
  this->spacer = new QSpacerItem ( 10, 10, QSizePolicy::Expanding );
  this->mainLayout = new QHBoxLayout ( this );
  this->mainLayout->setContentsMargins ( 0, 0, 0, 0 );
  //this->tabMainLayout->setSpacing ( 2 );
  //this->tabMainLayout->addSpacerItem ( this->spacer );
  this->mainLayout->setSpacing ( 2 );
  this->mainLayout->addStretch ( 1 );
  this->setLayout ( this->mainLayout );
}

void StripeMenuTab::addPanel ( StripeMenuPanel *pane ) {

  //pane->setParent ( ( QWidget * ) this->parent () );
  //this->tabMainLayout->insertWidget ( this->tabMainLayout->count () - 1, new QLabel ( "Prueba" ), Qt::AlignLeft );
  this->mainLayout->insertWidget ( this->mainLayout->count () - 1, pane, 0, Qt::AlignLeft );
  //this->tabMainLayout->insertWidget ( this->tabMainLayout->count () - 1, new QLabel ( "Prueba" ), Qt::AlignLeft );
  //this->mainLayout->addWidget ( pane, 0, Qt::AlignLeft );
}

bool StripeMenuTab::exists ( QString panelName ) {

  bool found = false;
  const int panelsCount = this->mainLayout->count ();
  if ( panelsCount > 0 ) {

    for ( int i = 0; i < panelsCount - 1; i++ ) {

      QWidget *tab = this->mainLayout->itemAt ( i )->widget ();

      if ( tab->inherits ( "StripeMenuPanel" ) ) {

        if ( tab->objectName ().compare ( panelName.toLower ().replace ( " ", "" ) ) == 0 ) {

          found = true;
          break;
        }
      }
    }
  }
  return found;
}

StripeMenuPanel *StripeMenuTab::getPanel ( QString panelName ) {

  StripeMenuPanel *ribbonMenuPanelReturned = nullptr;
  if ( this->exists ( panelName ) ) {

    const int panelsCount = this->mainLayout->count ();
    if ( panelsCount > 0 ) {

      for ( int i = 0; i < panelsCount - 1; i++ ) {

        QWidget *tab = this->mainLayout->itemAt ( i )->widget ();

        if ( tab->inherits ( "StripeMenuPanel" ) ) {

          if ( tab->objectName ().compare ( panelName.toLower ().replace ( " ", "" ) ) == 0 ) {

            ribbonMenuPanelReturned = ( StripeMenuPanel * ) tab;
            break;
          }
        }
      }
    }
  }
  return ribbonMenuPanelReturned;
}

QString StripeMenuTab::getTitleStripeMenuTab () const {

  return this->titleStripeMenuTab;
}

void StripeMenuTab::setTitleStripeMenuTab ( const QString &value ) {

  this->titleStripeMenuTab = value;
}
