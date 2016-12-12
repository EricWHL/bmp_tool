#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QDesktopWidget>
#include "inc/mainwindow.h"
#include "inc/EC_ImageDetail.h"
#include "inc/EC_ImageBinary.h"
#include "inc/EC_Tool.h"
#include "inc/EC_Zipc.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_Main(new QTabWidget(this))
    , m_Image(new DL_ImageDetail(this))
    , m_ImageLibrary(new DL_ImageBinary(this))
    , m_Tool(new EC_Tool(this))
    , m_convLib (new EC_iConvLibIF)
    , m_Zipc (new EC_Zipc)
{
    m_Main->addTab(m_ImageLibrary,"加载图片数据文件");
    m_Main->addTab(m_Image,"图片详细信息");
    m_Main->addTab(m_Tool,"工具");
    m_Main->addTab(m_Zipc,"Zipc");

    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect deskRect = desktopWidget->availableGeometry();

    resize(deskRect.width() - 20,deskRect.height() - 40);

}

MainWindow::~MainWindow()
{

}

void MainWindow::resizeEvent(QResizeEvent *)
{
    m_Main->setGeometry(2,30,width()-4,height()-30-4);
}
