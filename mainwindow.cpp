#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QDesktopWidget>
#include "mainwindow.h"
#include "DL_ImageDetail.h"
#include "DL_ImageBinary.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_Main(new QTabWidget(this))
    , m_Image(new DL_ImageDetail(this))
    , m_ImageLibrary(new DL_ImageBinary(this))
{
    m_Main->addTab(m_ImageLibrary,"加载图片数据文件");
    m_Main->addTab(m_Image,"图片详细信息");

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
