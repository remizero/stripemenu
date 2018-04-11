#ifndef STRIPEMENU_H
#define STRIPEMENU_H

#include "StripeMenuCornerActionsContainer.h"
#include "StripeMenuTab.h"
#include "StripeMenuPanel.h"

#include <QFlags>
#include <QFocusEvent>
#include <QHBoxLayout>
#include <QParallelAnimationGroup>
#include <QSizePolicy>
#include <QString>
#include <QTabBar>
#include <QTabWidget>
#include <QWidget>

/**
 * http://www.qtcentre.org/threads/11922-Styling-a-QTabWidget
 * http://blog.qt.io/blog/2007/06/22/styling-the-tab-widget/
 * https://stackoverflow.com/questions/45042508/how-to-set-qwidget-in-qtabwidget-header
 * https://stackoverflow.com/questions/44436328/qt-tabwidget-corner-widget-size
 * https://stackoverflow.com/questions/37649177/add-widgets-into-a-qtabwidget/37650578
 * http://developers-club.com/posts/48963/
 *
 * PARA LA ANIMACIÓN DEL COLLAPSE/UNCOLLAPSE DEL MENU
 * https://stackoverflow.com/questions/24106177/how-to-animate-hiding-showing-of-a-qvboxlayout-widget
 * http://doc.qt.io/qt-5/animation-overview.html
 *
 */

class StripeMenuCornerActionsContainer;

class StripeMenu : public QTabWidget {

    Q_OBJECT

  public:
    explicit StripeMenu ( QWidget *parent = Q_NULLPTR );

    void addAction ( QString panelName, QAction *action, int row, int col, int rowSpan, int colSpan );
    void addPane ( QString tabName, StripeMenuPanel *pane );
    void addTab ( QString tabName );
    void addTab ( StripeMenuTab *ribbonMenuTab );
    void addWidget ( QString panelName, QWidget *widget, int row, int col, int rowSpan, int colSpan );
    bool exists ( QString tabName );
    bool exists ( StripeMenuTab *ribbonMenuTab );
    bool getLockedMenu () const;
    bool getOpenMenu () const;
    QParallelAnimationGroup *getToggleAnimation () const;
    void leaveEvent ( QEvent *event ) Q_DECL_OVERRIDE;
    void setAnimation ();
    void setClosedMenu ( bool value );
    void setOpenMenu ( bool value );

  public slots:
    void launchAnimation ();

  private:
    StripeMenuCornerActionsContainer *cornerActionsContainer;
    QParallelAnimationGroup *toggleAnimation;
    bool lockedMenu = false;
    bool openMenu = true;
    int previousIndex;
};

#endif // STRIPEMENU_H
