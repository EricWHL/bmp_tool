#include <QFile>
#include <QDir>
#include <QDebug>


#include "EC_CodeGenerationTools.h"


EC_CodeGenerationTools::EC_CodeGenerationTools(QWidget *parent)
    : QWidget(parent)
    , m_CopyRight(new QPushButton(this))
    , m_SaveCopyRight(new QPushButton(this))
    , m_MakeGenCompPro(new QPushButton(this))
{
    init();

    connect(m_CopyRight,SIGNAL(clicked(bool)),this,SLOT(copyRightRecord()));
    connect(m_SaveCopyRight,SIGNAL(clicked(bool)),this,SLOT(copyRightSave()));

    connect(m_MakeGenCompPro,SIGNAL(clicked(bool)),this,SLOT(makeGenComPro()));
}

void EC_CodeGenerationTools::init()
{
    m_CopyRight->setText("Code CopyRight");
    m_SaveCopyRight->setText("Save the CopyRight");


    m_CopyRight->setGeometry(20,20,200,20);
    m_SaveCopyRight->setGeometry(20,45,200,20);

    m_SaveCopyRight->setVisible(false);

    m_MakeGenCompPro->setText("Make Generate Code Project config");

    m_MakeGenCompPro->setGeometry(20,430,300,20);
}

void EC_CodeGenerationTools::copyRightRecord()
{
    m_CopyRightDetail = new QTextEdit;

    m_CopyRightDetail->setText("please refresh CopyRight!");
    m_CopyRightDetail->setWindowTitle("Copy Right Detail!");
    m_CopyRightDetail->setGeometry(230,20,1000,400);

    connect(m_CopyRightDetail,SIGNAL(textChanged()),this,SLOT(copyRightRefresh()));

    m_CopyRightDetail->setVisible(true);
}

void EC_CodeGenerationTools::copyRightRefresh()
{
    m_SaveCopyRight->setVisible(true);
}

void EC_CodeGenerationTools::copyRightSave()
{
    QDir dir;
    dir.mkdir("config");

    QFile file(dir.currentPath() + "/config/" +"cr.cfg");
    if(!file.open( QIODevice::ReadWrite | QIODevice::Truncate )) {
        qDebug()<<"[EC_CodeGenerationTools][copyRightSave]Can't open the file!"<<endl;
    }
    file.write((char*)m_CopyRightDetail->toPlainText().toStdString().data(),m_CopyRightDetail->toPlainText().size());
    file.close();

    disconnect(m_CopyRightDetail,SIGNAL(textChanged()),this,SLOT(copyRightRefresh()));
    delete m_CopyRightDetail;

    m_SaveCopyRight->setVisible(false);
}

void EC_CodeGenerationTools::makeGenComPro()
{

}
