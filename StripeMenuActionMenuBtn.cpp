#include "StripeMenuActionMenuBtn.h"

StripeMenuActionMenuBtn::StripeMenuActionMenuBtn ( QWidget *parent ) : QToolButton ( parent ) {

  this->setPopupMode ( QToolButton::MenuButtonPopup );
  connect ( this, SIGNAL ( triggered ( QAction * ) ), this, SLOT ( setDefaultAction ( QAction * ) ) );
}
