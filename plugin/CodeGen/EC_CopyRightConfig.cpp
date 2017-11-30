#include <QFile>
#include <QDir>
#include <QDebug>
#include "EC_CopyRightConfig.h"

EC_CopyRightConfig::EC_CopyRightConfig(QWidget *parent)
    : QWidget(parent)
    , m_SaveCopyRight(new QPushButton(this))
    , m_CopyRightDetail(new QTextEdit(this))
{
    init();
    connect(m_SaveCopyRight,SIGNAL(clicked(bool)),this,SLOT(copyRightSave()));
    connect(m_CopyRightDetail,SIGNAL(textChanged()),this,SLOT(copyRightRefresh()));
}

void EC_CopyRightConfig::init()
{
    this->setWindowTitle("Copy Right Detail!");

    m_SaveCopyRight->setText("Save the CopyRight");
    m_CopyRightDetail->setText("please refresh CopyRight!");

    m_SaveCopyRight->setEnabled(false);
    m_SaveCopyRight->setGeometry(0,2,this->geometry().width(),20);

    m_CopyRightDetail->setGeometry(0,24,this->geometry().width(),this->geometry().height()-24);
}

void EC_CopyRightConfig::copyRightSave()
{
    QDir dir;
    dir.mkdir("config/cr");
    QFile file(dir.currentPath() + "/config/" +"cr.cfg");

    if(!file.open( QIODevice::ReadWrite | QIODevice::Truncate )) {
        qDebug()<<"[EC_CopyRightConfig][copyRightSave]Can't open the file!"<<endl;
    }

    file.write((char*)m_CopyRightDetail->toPlainText().toStdString().data(),m_CopyRightDetail->toPlainText().size());
    file.close();

    m_SaveCopyRight->setEnabled(false);
    this->close();
}

void EC_CopyRightConfig::copyRightRefresh()
{
    m_SaveCopyRight->setEnabled(true);
}
