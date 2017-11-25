#include "EC_CodeGenerationTools.h"
#include "EC_CopyRightConfig.h"

EC_CodeGenerationTools::EC_CodeGenerationTools(QWidget *parent)
    : QWidget(parent)
    , m_CopyRight(new QPushButton(this))
    , m_MakeGenCompPro(new QPushButton(this))
{
    init();

    connect(m_CopyRight,SIGNAL(clicked(bool)),this,SLOT(copyRightRecord()));

    connect(m_MakeGenCompPro,SIGNAL(clicked(bool)),this,SLOT(makeGenComPro()));
}

void EC_CodeGenerationTools::init()
{
    m_CopyRight->setText("Code CopyRight");

    m_CopyRight->setGeometry(20,20,200,20);

    m_MakeGenCompPro->setText("Make Generate Code Project config");

    m_MakeGenCompPro->setGeometry(20,430,300,20);
}

void EC_CodeGenerationTools::copyRightRecord()
{
    m_CpRtDtl = new EC_CopyRightConfig;
    m_CpRtDtl->show();
}

void EC_CodeGenerationTools::makeGenComPro()
{

}
