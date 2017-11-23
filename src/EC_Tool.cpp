#include "inc/EC_Tool.h"
class PrivateUsbTools {

};

EC_Tool::EC_Tool(QWidget *parent)
    : QWidget(parent)
    ,m_UsbTlGp(new QGroupBox(this))
    ,m_UsbRdLst(new QComboBox(this))
    ,m_UsbGrtBtn(new QPushButton(this))
    ,m_UsbRdPt(new QLabel(this))
    ,m_UsbFlPt(new QLabel(this))
{
    init();
}

void EC_Tool::init()
{
    usbToolsInit();
}

void EC_Tool::usbToolsInit()
{
    m_UsbTlGp->setTitle("USB Tools:");
    m_UsbRdPt->setText("请选择生成文件路径名:");
    m_UsbFlPt->setText("请选择生成路径文件名:");
    m_UsbGrtBtn->setText("生成文件");


    m_UsbTlGp->setGeometry(20,20,500,150);
    m_UsbRdPt->setGeometry(30,30,180,32);
    m_UsbFlPt->setGeometry(30,72,180,32);
    m_UsbRdLst->setGeometry(215,30,200,32);
    m_UsbGrtBtn->setGeometry(418,118,100,50);

}
