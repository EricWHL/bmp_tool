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
    ,m_pBar(new QProgressBar(this))
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
    this->m_UsbTlGp->setTitle("USB Tools:");
    this->m_UsbRdPt->setText("请选择生成文件路径名:");
    this->m_UsbFlPt->setText("请选择生成路径文件名:");
    this->m_UsbGrtBtn->setText("生成文件");


    this->m_UsbTlGp->setGeometry(20,20,500,150);
    this->m_UsbRdPt->setGeometry(30,30,180,32);
    this->m_UsbFlPt->setGeometry(30,72,180,32);
    this->m_UsbRdLst->setGeometry(215,30,200,32);
    this->m_UsbGrtBtn->setGeometry(418,118,100,50);

    this->m_pBar->setGeometry(30,170,200,30);
    this->m_pBar->setMaximum(100);
    this->m_pBar->setMinimum(0);
    this->m_pBar->setVisible(FALSE);
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
    QString path = "\\\\.\\" + dev + ":";
    QString disc_dev = dev + ":";
    quint64 freesize = this->getDiskFreeSpace("D:");
    QMessageBox::information(NULL, NULL,"U盘:" + freesize );
    this->m_pBar->setVisible(TRUE);
    this->readBuffer(path);
    this->GetFileList(path);
}


void EC_Tool::delUsbDev(QString dev)
{
    //QMessageBox::information(NULL, NULL,"U盘:" + dev + "拔出");
    m_UsbRdLst->removeItem(m_UsbRdLst->findText(dev));
}

quint64 EC_Tool::getDiskFreeSpace(QString driver)
{
    LPCWSTR lpcwstrDriver=(LPCWSTR)driver.utf16();

       ULARGE_INTEGER  liFreeBytesAvailable, liTotalBytes, liTotalFreeBytes;

       if( !GetDiskFreeSpaceExW( lpcwstrDriver, &liFreeBytesAvailable, &liTotalBytes, &liTotalFreeBytes) )
       {
           qDebug() << "ERROR: Call to GetDiskFreeSpaceEx() failed.";
           return 0;
       }
       qDebug()<<"Total Size = " <<(quint64) liTotalBytes.QuadPart/1024/1024/1024 << " GB";
       return (quint64) liTotalBytes.QuadPart/1024/1024/1024;
}

void EC_Tool::readBuffer(QString path)
{
    HANDLE hFile;
    LPTSTR dest=(LPTSTR)path.utf16();
    hFile = CreateFile(dest,
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
    for(int i = 0; i < 100;i++) {
        PBYTE pBuffer = (PBYTE)malloc(512);
        assert(pBuffer && "Allocate memory failed!");
        DWORD dwLen;
        ReadFile(hFile, pBuffer, 512, &dwLen, NULL);

        fwrite(pBuffer, 512, 1, fp);
        free(pBuffer);
        this->m_pBar->setValue(i+1);
    }

    fclose(fp);
    CloseHandle(hFile);
    QMessageBox::information(NULL, NULL,"U盘扫描完成");
    this->m_pBar->setVisible(FALSE);
}
