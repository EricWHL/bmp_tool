#include <QFile>
#include <QDebug>


#include "inc\EC_CodeGenerationTools.h"


EC_CodeGenerationTools::EC_CodeGenerationTools(QWidget *parent)
    : QWidget(parent)
    , m_CopyRight(new QPushButton(this))
    , m_SaveCopyRight(new QPushButton(this))
    , m_CopyRightDetail(new QTextEdit(this))
{
    init();
    connect(m_CopyRight,SIGNAL(clicked(bool)),this,SLOT(copyRightRecord()));
    connect(m_CopyRightDetail,SIGNAL(textChanged()),this,SLOT(copyRightRefresh()));
    connect(m_SaveCopyRight,SIGNAL(clicked(bool)),this,SLOT(copyRightSave()));
}

void EC_CodeGenerationTools::init()
{
    m_CopyRight->setText("Code CopyRight");
    m_SaveCopyRight->setText("Save the CopyRight");
    m_CopyRightDetail->setText("please refresh Copyrught!");

    m_CopyRight->setGeometry(20,20,200,20);
    m_SaveCopyRight->setGeometry(20,45,200,20);
    m_CopyRightDetail->setGeometry(230,20,1000,400);

    m_CopyRightDetail->setVisible(false);
    m_SaveCopyRight->setVisible(false);
}

void EC_CodeGenerationTools::copyRightRecord()
{
    m_CopyRightDetail->setVisible(true);
}

void EC_CodeGenerationTools::copyRightRefresh()
{
    m_SaveCopyRight->setVisible(true);
}

void EC_CodeGenerationTools::copyRightSave()
{
    QFile file("../plugin/copyright.cfg");
    if(!file.open( QIODevice::WriteOnly | QIODevice::Text )) {
        qDebug()<<"[EC_CodeGenerationTools][copyRightSave]Can't open the file!"<<endl;
    }

    m_CopyRightDetail->setVisible(false);
    m_SaveCopyRight->setVisible(false);
}
