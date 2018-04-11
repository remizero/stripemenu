#ifndef STRIPEMENUITEMLAYOUT_H
#define STRIPEMENUITEMLAYOUT_H

#include <QToolButton>

class StripeMenuItemLayout {

  public:
    StripeMenuItemLayout ();

    int index;
    QToolButton *item;
    int col;
    int colSpan;
    int row;
    int rowSpan;
};

#endif // STRIPEMENUITEMLAYOUT_H
