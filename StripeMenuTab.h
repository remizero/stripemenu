#ifndef STRIPEMENUTAB_H
#define STRIPEMENUTAB_H

#include "StripeMenuPanel.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QSizePolicy>

class StripeMenuTab : public QWidget {

    Q_OBJECT

  public:
    explicit StripeMenuTab ( QString tabTitle, QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags () );

    void addPanel ( StripeMenuPanel *pane );
    bool exists ( QString panelName );
    StripeMenuPanel *getPanel ( QString panelName );
    QString getTitleStripeMenuTab () const;
    void setTitleStripeMenuTab ( const QString &value );

  private:
    QSpacerItem *spacer;
    QHBoxLayout *mainLayout;
    QString titleStripeMenuTab;
};

#endif // STRIPEMENUTAB_H
