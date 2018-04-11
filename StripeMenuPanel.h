#ifndef STRIPEMENUPANEL_H
#define STRIPEMENUPANEL_H

#include "StripeMenuItemLayout.h"

#include <QAction>
#include <QFont>
#include <QFontMetrics>
#include <QFrame>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QLayoutItem>
#include <QMargins>
#include <QPainter>
#include <QPaintEvent>
#include <QPalette>
#include <QString>
#include <QStyle>
#include <QStyleOption>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

class StripeMenuPanel : public QWidget {

    Q_OBJECT

  public:
    const int heightFactor = 16;
    const int widthFactor = 16;
    const int spaceFactor = 5;

    explicit StripeMenuPanel ( QString title, bool panelSettings = false, QWidget *parent = 0 );

    void addAction ( QAction *action, int row, int col, int rowSpan, int colSpan );
    void addWidget ( QWidget *widget, int row, int col, int rowSpan, int colSpan );
    void adjustMenuPanel ();
    void adjustTitlePanelHeight ();
    void adjustTitlePanelWidth ();
    QString getTitle () const;
    bool hasPanelSettings () const;
    void paintEvent ( QPaintEvent *event ) Q_DECL_OVERRIDE;
    void setPanelSettings ( bool value );

  signals:

  public slots:

  private:
        QWidget *contentPanel;
    QGridLayout *contentPanelLayout;
    QVBoxLayout *mainLayout;
           bool  panelSettings;
    QToolButton *panelSettingsAct;
         QLabel *titleLbl;
        QWidget *titlePanel;
    QHBoxLayout *titlePanelLayout;

    void createContentPanel ();
    void createTitlePanel ( QString title );
    int getContentPanelWidth ();
    int getTitlePanelWidth ();
};

#endif // STRIPEMENUPANEL_H
