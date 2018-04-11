#include "StripeMenuCornerActionsContainer.h"

#include <QDebug>

StripeMenuCornerActionsContainer::StripeMenuCornerActionsContainer ( QWidget *parent ) : QWidget ( parent ) {

  this->setContentsMargins ( 0, 0, 0, 0 );
  //this->setStyleSheet ( "background-color: black");
  //this->setMinimumHeight ( 16 );
  this->setSizePolicy ( QSizePolicy::Maximum, QSizePolicy::Maximum );

  this->showHideStripeMenuBtn = new QToolButton ( this );
  this->showHideStripeMenuBtn->setObjectName ( "showHideRibbonMenuBtn" );
  //this->showHideRibbonMenuBtn->setIcon ( QIcon ( ":/icons/RibbonUp.svg" ) );
  this->showHideStripeMenuBtn->setSizePolicy ( QSizePolicy::Maximum, QSizePolicy::Maximum );
  this->showHideStripeMenuBtn->setStyleSheet ( "QToolButton {border: none;}" );
  this->showHideStripeMenuBtn->setToolButtonStyle ( Qt::ToolButtonIconOnly );
  this->showHideStripeMenuBtn->setArrowType ( Qt::ArrowType::DownArrow );
  this->showHideStripeMenuBtn->setToolTip ( "Collapse" );
  this->showHideStripeMenuBtn->setToolTipDuration ( 5000 );
  this->showHideStripeMenuBtn->setCheckable ( true );
  this->showHideStripeMenuBtn->setChecked ( false );
  this->showHideStripeMenuBtn->setMinimumSize ( 16, 16 );

  this->mainLayout = new QHBoxLayout ( this );
  this->mainLayout->setContentsMargins ( 3, 0, 3, 0 );
  this->mainLayout->addWidget ( this->showHideStripeMenuBtn );
  this->setLayout ( this->mainLayout );
  connect ( this->showHideStripeMenuBtn, SIGNAL ( toggled ( bool ) ), this, SLOT ( toggleShowHideStripeMenuBtn ( bool ) ) );

  // TODO: Estas son las acciones permitidas en el CornerActionsContainer
  // 1-. Ayuda ( Debe contener una lista de opciones de ayuda )
  // 2-. (LISTO)Show/Hide RibbonMenu
  // 3-. Cerrar aplicación
  // 4-. Maximizar ventana
  // 5-. Minimizar ventana
  // 6-. Restaurar marco del gestor de ventanas.

  //TODO: para reordenar los widget en el CornerActionsContainer
  //https://stackoverflow.com/questions/22010835/how-to-programmatically-change-the-order-of-widgets-in-a-layout
  // Para obtener la posición de cada widget dentro de un QGridLayout
  // https://stackoverflow.com/questions/24189202/how-to-get-the-row-column-location-of-a-widget-in-a-qgridlayout
  // https://stackoverflow.com/questions/4160526/qgridlayout-getting-the-list-of-qwidget-added

  // store the previous flags for this window so we can restore them when the window is unmaximized
  //previousWidgetFlags = activeWidget->windowFlags ();
  // https://forum.kde.org/viewtopic.php?f=64&t=95237
  //https://stackoverflow.com/questions/20285294/how-to-remove-a-qt-windowflag
}

void StripeMenuCornerActionsContainer::toggleShowHideStripeMenuBtn ( bool checked ) {

  this->showHideStripeMenuBtn->setArrowType ( checked ? Qt::ArrowType::LeftArrow : Qt::ArrowType::DownArrow );
  this->showHideStripeMenuBtn->setToolTip ( checked ? "Uncollapse" : "Collapse" );

  ( ( StripeMenu * ) this->parent () )->setClosedMenu ( checked ? true : false );
  ( ( StripeMenu * ) this->parent () )->setOpenMenu ( checked ? false : true );

  ( ( StripeMenu * ) this->parent () )->getToggleAnimation ()->setDirection ( checked ? QAbstractAnimation::Forward : QAbstractAnimation::Backward );
  ( ( StripeMenu * ) this->parent () )->getToggleAnimation ()->start ();
  QFlags<Qt::WindowType> flags =  ( ( QMainWindow * ) ( ( StripeMenu * ) this->parent () )->parent () )->windowFlags ();
  // QFlags<Qt::WindowType>(Window|WindowTitleHint|WindowSystemMenuHint|WindowMinMaxButtonsHint|WindowCloseButtonHint|WindowFullscreenButtonHint)
  // http://www.igorexchange.com/node/2827
  if ( flags.testFlag ( Qt::FramelessWindowHint ) ) {

    qDebug () << "No tiene el marco del gestor de ventanas";

  } else {

    qDebug () << "Tiene el marco del gestor de ventanas";
  }
}
