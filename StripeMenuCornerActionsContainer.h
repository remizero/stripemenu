#ifndef STRIPEMENUCORNERACTIONSCONTAINER_H
#define STRIPEMENUCORNERACTIONSCONTAINER_H

#include "StripeMenu.h"

#include <QAbstractAnimation>
#include <QAction>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QPropertyAnimation>
#include <QToolButton>
#include <QWidget>

class StripeMenuCornerActionsContainer : public QWidget {

    Q_OBJECT

  public:
    explicit StripeMenuCornerActionsContainer ( QWidget *parent = 0 );

  public slots:
    void toggleShowHideStripeMenuBtn ( bool checked );

  private:
    QToolButton *showHideStripeMenuBtn;
    QHBoxLayout *mainLayout;
};

#endif // STRIPEMENUCORNERACTIONSCONTAINER_H
