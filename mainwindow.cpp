#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

#include "mainwindow.h"
#include "DL_image.h"
#include "dl_imagelibrary.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_Main(new QTabWidget(this))
    , m_Image(new DL_Image(this))
    , m_ImageLibrary(new DL_Imagelibrary(this))
{
    m_Main->addTab(m_Image,"图片详细信息");
    m_Main->addTab(m_ImageLibrary,"加载图片数据文件");
    resize(maximumWidth(),maximumHeight());

}

MainWindow::~MainWindow()
{

}

void MainWindow::resizeEvent(QResizeEvent *)
{
    m_Main->setGeometry(2,30,width()-4,height()-30-4);
}
