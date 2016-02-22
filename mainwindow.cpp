#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

#include "mainwindow.h"
#include "DL_image.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_Main(new QTabWidget(this))
    , m_Image(new DL_Image(this))
{

    m_Main->addTab(m_Image,"Image");

    resize(maximumWidth(),maximumHeight());

}

MainWindow::~MainWindow()
{

}

void MainWindow::resizeEvent(QResizeEvent *)
{
    m_Main->setGeometry(0,30,maximumWidth() - 4,maximumHeight() -30 -2);
}
