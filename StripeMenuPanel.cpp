#include "StripeMenuPanel.h"

#include <QDebug>

StripeMenuPanel::StripeMenuPanel ( QString title, bool panelSettings, QWidget *parent ) : QWidget ( parent ) {

  // TODO : Para ajustar el stylesheet de los paneles
  // https://stackoverflow.com/questions/12116413/how-do-i-style-a-qt-widget-not-its-children-with-stylesheets
  // http://doc.qt.io/qt-5/stylesheet-reference.html
  // http://doc.qt.io/qt-5/stylesheet-customizing.html
  // http://doc.qt.io/qt-5/stylesheet-examples.html
  // http://doc.qt.io/qt-5/stylesheet.html
  // http://developers-club.com/posts/48963/

  this->panelSettings = panelSettings;
  this->setObjectName ( title.toLower ().replace ( " ", "" ) );
  this->setStyleSheet ( "StripeMenuPanel { border-right: 1px solid red; border-left: 1px solid red; }" );
  #ifdef Q_OS_WIN
    this->setMaximumHeight ( 83 );
    this->setMinimumHeight ( 83 );
  #endif
  #ifdef Q_OS_LINUX
    this->setMaximumHeight ( 83 );
    this->setMinimumHeight ( 83 );
  #endif

  this->mainLayout = new QVBoxLayout ( this );
  this->mainLayout->setContentsMargins ( 0, 0, 0, 0 );
  this->setLayout ( this->mainLayout );

  this->createContentPanel ();
  this->mainLayout->addWidget ( this->contentPanel, 0, Qt::AlignTop );

  this->createTitlePanel ( title );
  this->mainLayout->addWidget ( this->titlePanel, 0, Qt::AlignBottom );

  this->adjustMenuPanel ();
}

void StripeMenuPanel::addAction ( QAction *action , int row, int col, int rowSpan, int colSpan ) {

  QToolButton *newActionBtn = new QToolButton ( this );
  action->setParent ( newActionBtn );
  newActionBtn->setDefaultAction ( action );
  newActionBtn->setToolTipDuration ( 3000 );
  newActionBtn->setMaximumSize ( 16, 16 );
  this->contentPanelLayout->addWidget ( newActionBtn, row, col, rowSpan, colSpan, Qt::AlignLeft | Qt::AlignTop );
}

void StripeMenuPanel::addWidget ( QWidget *widget, int row, int col, int rowSpan, int colSpan ) {

  widget->setParent ( this );
  int fixedHeight = ( this->heightFactor * ( colSpan > 3 ? 3 : colSpan ) ) + ( this->spaceFactor * ( ( colSpan > 3 ? 3 : colSpan ) - 1 ) );
  int fixedWidth = ( this->widthFactor * rowSpan ) + ( this->spaceFactor * ( rowSpan - 1 ) );
  widget->setMaximumSize ( fixedWidth, fixedHeight );
  widget->setMinimumSize ( fixedWidth, fixedHeight );
  this->contentPanelLayout->addWidget ( widget, row, col, rowSpan, colSpan, Qt::AlignLeft | Qt::AlignTop );
}

void StripeMenuPanel::adjustMenuPanel () {

  int contentPanelWidth = this->getContentPanelWidth ();
  int titlePanelWidth = this->getTitlePanelWidth ();
  int menuPanelWidth = 0;
  if ( titlePanelWidth > contentPanelWidth ) {

    menuPanelWidth = titlePanelWidth;

  } else {

    menuPanelWidth = contentPanelWidth;
  }
  this->setFixedSize ( menuPanelWidth, this->minimumHeight () );
}

void StripeMenuPanel::adjustTitlePanelHeight () {

  this->titlePanel->setMinimumHeight ( this->titlePanel->height () );
  this->titlePanel->setMaximumHeight ( this->titlePanel->height () );
}

void StripeMenuPanel::adjustTitlePanelWidth () {

  int titlePanelWidth = this->getTitlePanelWidth ();
  this->titlePanel->setMinimumWidth ( titlePanelWidth );
  this->titlePanel->setMaximumWidth ( titlePanelWidth );
}

void StripeMenuPanel::createContentPanel () {

  this->contentPanel = new QWidget ( this );
  #ifdef Q_OS_WIN
    this->contentPanel->setMaximumHeight ( 68 );
    this->contentPanel->setMinimumHeight ( 68 );
  #endif
  #ifdef Q_OS_LINUX
    this->contentPanel->setMaximumHeight ( 68 );
    this->contentPanel->setMinimumHeight ( 68 );
  #endif

  this->contentPanelLayout = new QGridLayout ( this->contentPanel );
  this->contentPanelLayout->setSpacing ( 5 );
  this->contentPanelLayout->setAlignment ( Qt::AlignLeft );
  this->contentPanel->setLayout ( this->contentPanelLayout );
}

void StripeMenuPanel::createTitlePanel ( QString title ) {

  this->titlePanel = new QWidget ( this );
  this->titlePanel->setObjectName ( title.toLower ().replace ( " ", "" ) + "Pnl" );
  this->titlePanel->setMaximumHeight ( 16 );
  this->titlePanel->setStyleSheet ( "QWidget#" + this->titlePanel->objectName () + " { border-top: 1px solid red; border-bottom: 1px solid red; }" );
  this->titlePanelLayout = new QHBoxLayout ( this->titlePanel );
  this->titlePanelLayout->setContentsMargins ( 0, 0, 0, 0 );
  this->titlePanelLayout->setSpacing ( 0 );
  this->titleLbl = new QLabel ( this->titlePanel );
  this->titleLbl->setText ( title );
  this->titleLbl->setAlignment ( Qt::AlignCenter );
  this->titleLbl->setMaximumHeight ( 16 );
  this->titleLbl->setSizePolicy ( QSizePolicy::Expanding, QSizePolicy::Fixed );
  this->titleLbl->setStyleSheet ( "font-size: 10px; padding-top: 2px; padding-bottom: 2px; padding-left: 10px; padding-right: 10px;" );
  this->titlePanelLayout->addWidget ( this->titleLbl );
  if ( this->panelSettings ) {

    this->panelSettingsAct = new QToolButton ( this->titlePanel );
    this->panelSettingsAct->setIcon ( QIcon ( ":/icons/MoreOptions.svg" ) );
    this->panelSettingsAct->setToolTip ( "More actions" );
    this->panelSettingsAct->setToolTipDuration ( 3000 );
    this->panelSettingsAct->setMaximumSize ( 16, 16 );
    this->titlePanelLayout->addWidget ( this->panelSettingsAct, 0, Qt::AlignRight );
  }
  this->titlePanel->setLayout ( this->titlePanelLayout );
  this->adjustTitlePanelHeight ();
  this->adjustTitlePanelWidth ();
}

int StripeMenuPanel::getContentPanelWidth () {

  int maxWidth = 0;
  const int contentPanelLayoutCount = this->contentPanelLayout->count ();
  if ( contentPanelLayoutCount > 0 ) {

    StripeMenuItemLayout *itemLayout = new StripeMenuItemLayout ();
    this->contentPanelLayout->getItemPosition ( 0, &itemLayout->row, &itemLayout->col, &itemLayout->row, &itemLayout->colSpan );
    itemLayout->item = ( QToolButton * ) this->contentPanelLayout->itemAtPosition ( itemLayout->row, itemLayout->col )->widget ();
    maxWidth = itemLayout->item->width () + ( this->contentPanelLayout->spacing () * 2 );

    for ( int i = 1; i < contentPanelLayoutCount; i++ ) {

      StripeMenuItemLayout *itemLayoutAux = new StripeMenuItemLayout ();
      this->contentPanelLayout->getItemPosition ( i, &itemLayoutAux->row, &itemLayoutAux->col, &itemLayoutAux->row, &itemLayoutAux->colSpan );
      itemLayoutAux->item = ( QToolButton * ) this->contentPanelLayout->itemAtPosition ( itemLayoutAux->row, itemLayoutAux->col )->widget ();

      if ( itemLayout->col == itemLayoutAux->col ) {

        if ( itemLayout->colSpan < itemLayoutAux->colSpan ) {

          itemLayout = itemLayoutAux;
          maxWidth = maxWidth + itemLayout->item->width () + this->contentPanelLayout->spacing ();
        }
      } else if ( itemLayout->col < itemLayoutAux->col ) {

        if ( ( itemLayout->col + itemLayout->colSpan ) < (itemLayoutAux->col + itemLayoutAux->colSpan ) ) {

          itemLayout = itemLayoutAux;
          maxWidth = maxWidth + itemLayout->item->width () + this->contentPanelLayout->spacing ();
        }
      }
    }
  }
  return maxWidth;
}

int StripeMenuPanel::getTitlePanelWidth () {

  QLabel *itemTitle = new QLabel ();
  itemTitle = ( QLabel * ) this->titlePanelLayout->itemAt ( 0 )->widget ();
  int titlePanelWidth = itemTitle->width ();

  if ( this->panelSettings ) {

    QToolButton *itemTitleBtn = new QToolButton ();
    itemTitleBtn = ( QToolButton * ) this->titlePanelLayout->itemAt ( 1 )->widget ();
    titlePanelWidth = titlePanelWidth + itemTitleBtn->width ();
  }
  return titlePanelWidth;
}

QString StripeMenuPanel::getTitle () const {

  return this->titleLbl->text ();
}

bool StripeMenuPanel::hasPanelSettings () const {

  return this->panelSettings;
}

void StripeMenuPanel::paintEvent ( QPaintEvent *event ) {

  Q_UNUSED ( event )
  QStyleOption o;
  o.initFrom ( this );
  QPainter p ( this );
  this->style ()->drawPrimitive ( QStyle::PE_Widget, &o, &p, this );
}

void StripeMenuPanel::setPanelSettings ( bool value ) {

  this->panelSettings = value;
}
