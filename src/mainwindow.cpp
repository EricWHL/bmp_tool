#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QDesktopWidget>
#include <windows.h>
#include <dbt.h>
#include "mainwindow.h"

#include "EC_ImageDetail.h"
#include "EC_ImageBinary.h"
#include "EC_Tool.h"
#include "EC_StsMgr.h"
#include "EC_CodeGenerationTools.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_Main(new QTabWidget(this))
    , m_Image(new DL_ImageDetail(this))
    , m_ImageLibrary(new DL_ImageBinary(this))
    , m_Tool(new EC_Tool(this))
    , m_convLib (new EC_iConvLibIF)
    , m_StsMgr (new EC_StsMgr)
    , m_CodeGenTool(new EC_CodeGenerationTools)
{
    m_Main->addTab(m_ImageLibrary,"加载图片数据文件");
    m_Main->addTab(m_Image,"图片详细信息");
    m_Main->addTab(m_CodeGenTool,"代码生成工具");
    m_Main->addTab(m_Tool,"工具库");
    m_Main->addTab(m_StsMgr,"状态管理");

    this->setWindowTitle("Tools Box");

    resize(QApplication::desktop()->availableGeometry().width(),QApplication::desktop()->availableGeometry().height());
}

MainWindow::~MainWindow()
{
}

char MainWindow::FirstDriveFromMask(unsigned long unitmask)
{
    char i;
    for (i = 0; i < 26; ++i)
    {
        if (unitmask & 0x1)
            break;
        unitmask = unitmask >> 1;
    }
    return (i + 'A');
}


bool MainWindow::nativeEvent(const QByteArray & eventType, void * message, long*result)
{
    MSG* msg = reinterpret_cast<MSG*>(message);
    int msgType = msg->message;
    if(msgType==WM_DEVICECHANGE)
    {
        PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)msg->lParam;
        switch (msg->wParam) {
        case DBT_DEVICEARRIVAL:

            if(lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)
            {
                PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
                if(lpdbv->dbcv_flags ==0)
                {
                    QString USBDisk = QString(this->FirstDriveFromMask(lpdbv ->dbcv_unitmask));
                    qDebug() << "USB_Arrived and The USBDisk is: "<<USBDisk ;
                    this->m_Tool->addUsbDev(USBDisk);
                }
            }
            break;
        case DBT_DEVICEREMOVECOMPLETE:
            if(lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)
            {
                PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
                if(lpdbv->dbcv_flags == 0)
                {
                    QString USBDisk = QString(this->FirstDriveFromMask(lpdbv ->dbcv_unitmask));
                    qDebug() << "USB_Removed";
                    this->m_Tool->delUsbDev(USBDisk);
                }
            }
            break;
        }
    }
    return false;
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    this->setGeometry(QApplication::desktop()->availableGeometry().width()/4,QApplication::desktop()->availableGeometry().height()/4-10,QApplication::desktop()->availableGeometry().width()/2,QApplication::desktop()->availableGeometry().height()/2 + 200);
    m_Main->setGeometry(0,0,this->geometry().width(),this->geometry().height());
}
