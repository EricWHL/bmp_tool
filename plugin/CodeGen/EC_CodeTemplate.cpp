#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QDesktopWidget>

#include "EC_CodeTemplate.h"

EC_CodeTemplate::EC_CodeTemplate(QWidget *parent)
    : QWidget(parent)
    , m_CtgTl (new QLabel(this))
    , m_CtgDtl (new QLineEdit(this))
    , m_FnCreCk (new QCheckBox(this))
    , m_FnDesCk (new QCheckBox(this))
    , m_FnInsCk (new QCheckBox(this))
{
    init();

    connect(m_CtgDtl,SIGNAL(textChanged(QString)),this, SLOT(ctgChanged()));
}

void EC_CodeTemplate::init()
{
    this->setWindowTitle("代码模板设定");
    m_CtgTl->setText("请输入生成代码模板类型名称:");
    m_CtgDtl->setText("please input detail");

    m_CtgTl->setGeometry(10,10,170,20);
    m_CtgDtl->setGeometry(190,10,200,20);

    m_FnCreCk->setText("Create Funcion?");
    m_FnDesCk->setText("Destory Funcion?");
    m_FnInsCk->setText("Inst Funcion?");

    m_FnCreCk->setGeometry(10,40,120,20);
    m_FnDesCk->setGeometry(140,40,120,20);
    m_FnInsCk->setGeometry(270,40,120,20);

    m_FnCreCk->setEnabled(false);
    m_FnDesCk->setEnabled(false);
    m_FnInsCk->setEnabled(false);

}

void EC_CodeTemplate::resizeEvent(QResizeEvent *)
{
    this->setGeometry(QApplication::desktop()->availableGeometry().width()/4,QApplication::desktop()->availableGeometry().height()/4-10,QApplication::desktop()->availableGeometry().width()/2,QApplication::desktop()->availableGeometry().height()/2 + 200);
}

void EC_CodeTemplate::ctgChanged()
{
    m_FnCreCk->setEnabled(true);
    m_FnDesCk->setEnabled(true);
    m_FnInsCk->setEnabled(true);
}
