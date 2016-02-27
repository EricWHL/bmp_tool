#include <QFileDialog>

#include "DL_imagelibrary.h"

DL_Imagelibrary::DL_Imagelibrary(QWidget *parent)
    : QWidget(parent)
	, m_curfilepath(new QPushButton(this))
	, m_preview(new QLabel(this))
{
    init();
    connect(m_curfilepath,SIGNAL(clicked(bool)),this,SLOT(loadFile()));
}

DL_Imagelibrary::~DL_Imagelibrary()
{
	
}

void DL_Imagelibrary::init()
{
    m_curfilepath->setText("加载图片文件");
    m_preview->setText("预览");
}

void DL_Imagelibrary::resizeEvent(QResizeEvent *)
{
    m_curfilepath->setGeometry(10,20,150,20);

    m_preview->setGeometry(300,20,1280,720);
}

void DL_Imagelibrary::loadFile()
{
    QString curFile;
        curFile=QFileDialog::getOpenFileName(this,
                                              tr("选择图像"),
                                              "",
                                              tr("Images (*.png *.bmp *.jpg *.tif *.GIF *.*)"));
    if(curFile.isEmpty())
    {
         return;
    }
    else
    {
        showFile(curFile);
    }

}

void DL_Imagelibrary::showFile(QString filename)
{

}


