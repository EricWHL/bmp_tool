
#include <QMessageBox>

#include "EC_StsMgr.h"

EC_StsMgr::EC_StsMgr(QWidget *parent)
    : QWidget(parent)
    , m_CrtTbl(new QPushButton("创建",this))
	, m_Menu (new QMenu(this))
    , m_AddAct (new QAction("添加动作",this))
    , m_AddSts (new QAction("添加状态",this))
{
    init();
    connect(m_CrtTbl,SIGNAL(clicked(bool)),this,SLOT(createTable()));

}

void EC_StsMgr::init()
{

    m_Menu->addAction(m_AddAct);
    m_Menu->addAction(m_AddSts);

    connect(m_AddAct,SIGNAL(triggered(bool)),this,SLOT(addAction()));
    connect(m_AddSts,SIGNAL(triggered(bool)),this,SLOT(addStatus()));
}


void EC_StsMgr::createTable()
{
    m_CrtTbl->setVisible(false);

    m_EditWidget = new QTableWidget(2,1,this);

    m_EditWidget->setGeometry(this->geometry().x() + 10,this->geometry().y() + 10,this->geometry().width()-20,this->geometry().height()-20);
    m_EditWidget->setVisible(true);
    m_EditWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    QStringList headerLine;
    headerLine.append("S_INIT");
    QStringList rowLine;
    rowLine.append("E_A_INIT");
    rowLine.append("E_S_INIT");

    m_EditWidget->setHorizontalHeaderLabels(headerLine);
    m_EditWidget->setVerticalHeaderLabels(rowLine);

    connect(m_EditWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(menu(QPoint)));
}

void EC_StsMgr::addAction()
{
    if(!m_EditWidget) {
        return;
    }
    QMessageBox::information(NULL, NULL, "addAction");
}

void EC_StsMgr::addStatus()
{
    if(!m_EditWidget) {
        return;
    }
    QMessageBox::information(NULL, NULL, "addStatus");
}


void EC_StsMgr::menu(QPoint)
{
    m_Menu->exec(QCursor::pos());
}
