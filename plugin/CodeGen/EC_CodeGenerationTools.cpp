#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include "EC_CodeGenerationTools.h"
#include "EC_CopyRightConfig.h"
#include "EC_CodeTemplate.h"
#include "EC_CodeGenerationTemplates.h"

EC_CodeGenerationTools::EC_CodeGenerationTools(QWidget *parent)
    : QWidget(parent)
    , m_CopyRight(new QPushButton(this))
    , m_MakeGenCompPro(new QPushButton(this))
    , m_LoadGenCompPro(new QPushButton(this))
{
    init();

    connect(m_CopyRight,SIGNAL(clicked(bool)),this,SLOT(copyRightRecord()));
    connect(m_LoadGenCompPro,SIGNAL(clicked(bool)),this,SLOT(loadGenTmp()));
    connect(m_MakeGenCompPro,SIGNAL(clicked(bool)),this,SLOT(makeGenComPro()));

}

EC_CodeGenerationTools::~EC_CodeGenerationTools()
{
}

void EC_CodeGenerationTools::init()
{
    m_CopyRight->setText("Code CopyRight");
    m_LoadGenCompPro->setText("Load Exist Generate Code Project config");
    m_MakeGenCompPro->setText("Make Generate Code Project config");

    m_CopyRight->setGeometry(20,20,200,50);
    m_LoadGenCompPro->setGeometry(20,80,300,50);
    m_MakeGenCompPro->setGeometry(20,140,300,50);

}

void EC_CodeGenerationTools::copyRightRecord()
{
    m_CpRtDtl = new EC_CopyRightConfig;
    m_CpRtDtl->show();
}

void EC_CodeGenerationTools::makeGenComPro()
{
    m_CodeTemplate = new EC_CodeTemplate;
    m_CodeTemplate->show();
    m_CodeTemplate->resize(0,0);
}

void EC_CodeGenerationTools::loadGenTmp()
{
    QStringList fileList;
    fileList = QFileDialog::getOpenFileNames(this,
                                              tr("选择配置文件"),
                                              "",
                                              tr("tmp* (*.tmph *.tmpc)"));

    m_CodeGenTem = new EC_CodeGenerationTemplates;
    m_CodeGenTem->saveTempFiles(fileList);
    m_CodeGenTem->setGeometry(this->window()->geometry());
    m_CodeGenTem->show();

}


