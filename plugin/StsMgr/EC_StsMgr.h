#ifndef EC_STSMGR_H
#define EC_STSMGR_H

#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QMenu>
#include <QAction>
#include <QTableWidget>

class EC_StsMgr : public QWidget
{
    Q_OBJECT
public:
    explicit EC_StsMgr(QWidget *parent = 0);

signals:

public slots:

private slots:
    void menu(QPoint);
    void createTable();
    void addAction();
    void addStatus();


private:
    void init();

private:
    QPushButton* m_CrtTbl;

	QMenu*      m_Menu;
    QAction*    m_AddAct;
    QAction*    m_AddSts;

    QTableWidget* m_EditWidget;
	
};

#endif // EC_STSMGR_H
