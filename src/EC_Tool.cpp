#include <QDebug>
#include <QMessageBox>
#include <windows.h>
#include <assert.h>
#include <stdio.h>
#include "EC_Tool.h"
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
    connect(m_UsbGrtBtn,SIGNAL(clicked(bool)),this,SLOT(genFiles()));
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

void EC_Tool::genFiles()
{

}
QFileInfoList EC_Tool::GetFileList(QString path)
{
    QDir dir(path);
    QFileInfoList file_list = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList folder_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for(int i = 0; i != folder_list.size(); i++)
    {
        QString name = folder_list.at(i).absoluteFilePath();
        QFileInfoList child_file_list = GetFileList(name);
        qDebug()<<name;
        file_list.append(child_file_list);
    }

    return file_list;
}
void EC_Tool::addUsbDev(QString dev)
{
    QMessageBox::information(NULL, NULL,"U盘:" + dev + "插入");
    m_UsbRdLst->addItem(dev);
    QString path = dev + ":\\";
    this->readBuffer();
    this->GetFileList(path);
}


void EC_Tool::delUsbDev(QString dev)
{
    QMessageBox::information(NULL, NULL,"U盘:" + dev + "拔出");
    m_UsbRdLst->removeItem(m_UsbRdLst->findText(dev));
}

void EC_Tool::readBuffer()
{
    HANDLE hFile;
    hFile = CreateFile("\\\\.\\H:",
                       GENERIC_READ,
                       FILE_SHARE_READ,
                       NULL,
                       OPEN_EXISTING,
                       0,
                       NULL);
    assert(hFile && "CreateFile failed!");
    FILE * fp;
    fp = fopen("boot.txt", "wb");
    assert(fp && "Open file failed!");
    for(int i = 0; i < 100000;i++) {
        PBYTE pBuffer = (PBYTE)malloc(512);
        assert(pBuffer && "Allocate memory failed!");
        DWORD dwLen;
        ReadFile(hFile, pBuffer, 512, &dwLen, NULL);
        qDebug()<<"load"<<i/2<< "K Data!"<<endl;
        fwrite(pBuffer, 512, 1, fp);
        free(pBuffer);
    }

    fclose(fp);
    CloseHandle(hFile);
}
