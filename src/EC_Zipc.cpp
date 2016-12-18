#include "inc/EC_Zipc.h"
#include <QStandardItemModel>

EC_Zipc::EC_Zipc(QWidget *parent)
    : QWidget(parent)
    , m_mainView (new QTableView(this))
	, m_Menu (new QMenu(this))
    , m_AddAct (new QAction("添加动作",this))
    , m_AddSts (new QAction("添加状态",this))
{
    init();
    connect(m_mainView,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(menu(QPoint)));
}

void EC_Zipc::init()
{
    QStandardItemModel *student_model = new QStandardItemModel();
    student_model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("Name")));
    student_model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("NO.")));
    student_model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("Sex")));
    student_model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("Age")));
    student_model->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("College")));
    student_model->setItem(0, 0, new QStandardItem("张三"));
    student_model->setItem(0, 1, new QStandardItem("20120202"));
    student_model->setItem(0, 2, new QStandardItem("男"));
    student_model->setItem(0, 3, new QStandardItem("18"));
    student_model->setItem(0, 4, new QStandardItem("土木学院"));
    m_mainView->setModel(student_model);
    m_mainView->setContextMenuPolicy(Qt::CustomContextMenu);
    m_Menu->addAction(m_AddAct);
    m_Menu->addAction(m_AddSts);
    m_mainView->setGeometry(200,200,600,400);
}

void EC_Zipc::menu(QPoint)
{
    m_Menu->exec(QCursor::pos());
}
