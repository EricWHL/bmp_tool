#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QDesktopWidget>

#include "mainwindow.h"

#include "EC_ImageDetail.h"
#include "EC_ImageBinary.h"
#include "EC_Tool.h"
#include "EC_Zipc.h"
#include "EC_CodeGenerationTools.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_Main(new QTabWidget(this))
    , m_Image(new DL_ImageDetail(this))
    , m_ImageLibrary(new DL_ImageBinary(this))
    , m_Tool(new EC_Tool(this))
    , m_convLib (new EC_iConvLibIF)
    , m_Zipc (new EC_Zipc)
    , m_CodeGenTool(new EC_CodeGenerationTools)
{
    m_Main->addTab(m_ImageLibrary,"加载图片数据文件");
    m_Main->addTab(m_Image,"图片详细信息");
    m_Main->addTab(m_CodeGenTool,"代码生成工具");
    m_Main->addTab(m_Tool,"工具");
    m_Main->addTab(m_Zipc,"Zipc");

    this->setWindowTitle("Tools Box");

    resize(QApplication::desktop()->availableGeometry().width(),QApplication::desktop()->availableGeometry().height());
}

MainWindow::~MainWindow()
{
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    this->setGeometry(QApplication::desktop()->availableGeometry().width()/4,QApplication::desktop()->availableGeometry().height()/4-10,QApplication::desktop()->availableGeometry().width()/2,QApplication::desktop()->availableGeometry().height()/2 + 200);
    m_Main->setGeometry(0,0,this->geometry().width(),this->geometry().height());
}
