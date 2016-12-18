#ifndef EC_ZIPC_H
#define EC_ZIPC_H

#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QMenu>
#include <QAction>

class EC_Zipc : public QWidget
{
    Q_OBJECT
public:
    explicit EC_Zipc(QWidget *parent = 0);

signals:

public slots:
        void menu(QPoint);
private:
    void init();


private:
    QTableView* m_mainView;
	QMenu*      m_Menu;
    QAction*    m_AddAct;
    QAction*    m_AddSts;
	
};

#endif // EC_ZIPC_H
