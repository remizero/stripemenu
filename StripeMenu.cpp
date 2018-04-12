#include "StripeMenu.h"
#include <QToolButton>
#include <QWidgetAction>
#include <QDebug>

StripeMenu::StripeMenu ( QWidget *parent ) : QTabWidget ( parent ) {

  QString css;
  QFile file ( ":/icons/StripeMenu.qss" );
  if ( file.open ( QIODevice::ReadOnly ) ) {

    css = file.readAll ();
    file.close ();
  }

    //return css
  this->setStyleSheet ( css );

  this->cornerActionsContainer = new StripeMenuCornerActionsContainer ( this );
  this->setCornerWidget ( this->cornerActionsContainer, Qt::TopRightCorner );

  this->setMinimumHeight ( 0 );
  #ifdef Q_OS_WIN
    this->setMaximumHeight ( 110 );
  #endif
  #ifdef Q_OS_LINUX
    this->setMaximumHeight ( 120 );
  #endif
  this->setSizePolicy ( QSizePolicy::Expanding, QSizePolicy::Fixed );
  this->previousIndex = 0;
  this->setCurrentIndex ( 0 );

  // let the entire widget grow and shrink with its content
  this->toggleAnimation = new QParallelAnimationGroup ( this );
  this->toggleAnimation->addAnimation ( new QPropertyAnimation ( this, "minimumHeight" ) );
  this->toggleAnimation->addAnimation ( new QPropertyAnimation ( this, "maximumHeight" ) );
  this->setAnimation ();

  connect ( this, SIGNAL ( tabBarClicked ( int ) ), this, SLOT ( setCurrentIndex ( int ) ) );
  connect ( this, SIGNAL ( tabBarClicked ( int ) ), this, SLOT ( launchAnimation () ) );
}

void StripeMenu::addAction ( QString panelName, QAction *action , int row, int col, int rowSpan, int colSpan ) {

  const int tabsCount = this->count ();
  if ( tabsCount > 0 ) {

    for ( int i = 0; i < tabsCount; i++ ) {

      StripeMenuTab *tab = ( StripeMenuTab * ) this->widget ( i );
      if ( tab->exists ( panelName ) ) {

        StripeMenuPanel *ribbonMenuPanel = tab->getPanel ( panelName );
        ribbonMenuPanel->addAction ( action , row, col, rowSpan, colSpan );
      }
    }
  }
}

void StripeMenu::addPane ( QString tabName, StripeMenuPanel *pane ) {

  if ( this->exists ( tabName ) ) {

    const int tabsCount = this->count ();
    if ( tabsCount > 0 ) {

      for ( int i = 0; i < tabsCount; i++ ) {

        QWidget *tab = this->widget ( i );
        if ( tab->objectName ().compare ( tabName.toLower ().replace ( " ", "" ) ) == 0 ) {

          ( ( StripeMenuTab * ) tab )->addPanel ( pane );
          break;
        }
      }
    }
  }
}

void StripeMenu::addTab ( QString tabName ) {

  if ( !this->exists ( tabName ) ) {

    StripeMenuTab *newTab = new StripeMenuTab ( tabName );
    QTabWidget::addTab ( newTab, newTab->getTitleStripeMenuTab () );
  }
}

void StripeMenu::addTab ( StripeMenuTab *ribbonMenuTab ) {

  if ( this->exists ( ribbonMenuTab ) ) {

    QTabWidget::addTab ( ribbonMenuTab, ribbonMenuTab->getTitleStripeMenuTab () );
  }
}

void StripeMenu::addWidget ( QString panelName, QWidget *widget, int row, int col, int rowSpan, int colSpan ) {

  const int tabsCount = this->count ();
  if ( tabsCount > 0 ) {

    for ( int i = 0; i < tabsCount; i++ ) {

      StripeMenuTab *tab = ( StripeMenuTab * ) this->widget ( i );
      if ( tab->exists ( panelName ) ) {

        StripeMenuPanel *ribbonMenuPanel = tab->getPanel ( panelName );
        ribbonMenuPanel->addWidget ( widget , row, col, rowSpan, colSpan );
      }
    }
  }
}

bool StripeMenu::exists ( QString tabName ) {

  bool found = false;
  const int tabsCount = this->count ();
  if ( tabsCount > 0 ) {

    for ( int i = 0; i < tabsCount; i++ ) {

      QWidget *tab = this->widget ( i );
      if ( tab->objectName ().compare ( tabName.toLower ().replace ( " ", "" ) ) == 0 ) {

        found = true;
        break;
      }
    }
  }
  return found;
}

bool StripeMenu::exists ( StripeMenuTab *ribbonMenuTab ) {

  bool found = false;
  const int tabsCount = this->count ();
  if ( tabsCount > 0 ) {

    for ( int i = 0; i < tabsCount; i++ ) {

      QWidget *tab = this->widget ( i );
      if ( ribbonMenuTab->objectName ().compare ( tab->objectName () ) == 0 ) {

        found = true;
        break;
      }
    }
  }
  return found;
}

bool StripeMenu::getLockedMenu () const {

  return this->lockedMenu;
}

bool StripeMenu::getOpenMenu () const {

  return this->openMenu;
}

QParallelAnimationGroup *StripeMenu::getToggleAnimation () const {

  return this->toggleAnimation;
}

void StripeMenu::leaveEvent ( QEvent *event ) {

  if ( event->type () == QEvent::Leave ) {

    if ( this->openMenu ) {

      this->launchAnimation ();
    }
  }
  QWidget::leaveEvent ( event );
}

void StripeMenu::launchAnimation () {

  if ( this->lockedMenu ) {

    if ( this->currentIndex () != this->previousIndex ) {

      this->previousIndex = this->currentIndex ();
      if ( !this->openMenu ) {

        this->getToggleAnimation ()->setDirection ( this->openMenu ? QAbstractAnimation::Forward : QAbstractAnimation::Backward );
        this->setOpenMenu ( !this->openMenu );
        this->getToggleAnimation ()->start ();
      }
    } else {

      this->getToggleAnimation ()->setDirection ( this->openMenu ? QAbstractAnimation::Forward : QAbstractAnimation::Backward );
      this->setOpenMenu ( !this->openMenu );
      this->getToggleAnimation ()->start ();
    }
  } else {

    if ( this->currentIndex () != this->previousIndex ) {

      this->previousIndex = this->currentIndex ();
    }
  }
}

void StripeMenu::setAnimation () {

  for ( int i = 0; i < toggleAnimation->animationCount () - 1; ++i ) {

    QPropertyAnimation* SectionAnimation = static_cast<QPropertyAnimation *> ( toggleAnimation->animationAt ( i ) );
    SectionAnimation->setDuration ( 300 );
    #ifdef Q_OS_WIN
      SectionAnimation->setStartValue ( 110 );
    #endif
    #ifdef Q_OS_LINUX
      SectionAnimation->setStartValue ( 120 );
    #endif
    SectionAnimation->setEndValue ( 0 );
  }
  QPropertyAnimation* contentAnimation = static_cast<QPropertyAnimation *> ( toggleAnimation->animationAt ( toggleAnimation->animationCount () - 1 ) );
  contentAnimation->setDuration ( 300 );
  contentAnimation->setStartValue ( 0 );
  #ifdef Q_OS_WIN
    contentAnimation->setEndValue ( this->tabBar ()->height () - 7 );
  #endif
  #ifdef Q_OS_LINUX
    contentAnimation->setEndValue ( this->tabBar ()->height () );
  #endif
}

void StripeMenu::setClosedMenu ( bool value ) {

  this->lockedMenu = value;
}

void StripeMenu::setOpenMenu ( bool value ) {

  this->openMenu = value;
}
