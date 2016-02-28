#include <QFileDialog>
#include <QMessageBox>
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
    m_curfilepath->setGeometry(10,20,150,25);

    m_preview->setGeometry(300,20,1280,720);
}

void DL_Imagelibrary::loadFile()
{
    QString curFile;
        curFile=QFileDialog::getOpenFileName(this,
                                              tr("选择图像"),
                                              "",
                                              tr("Images library(*.bin *.*)"));
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
    QFile File(filename);
    if(File.open(QIODevice::ReadOnly)) {
        int flen = File.size();
        char *p_data = new char [flen];
        if ( NULL == p_data )
        {
            QMessageBox::information(NULL, NULL, "malloc buffer failed...");

        }
        memset(p_data, 0, flen);
        QDataStream fstream(&File);
        if ( -1 == fstream.readRawData(p_data, flen))
        {
            QMessageBox::information(NULL, NULL, "readRawData failed...");
            if( NULL != p_data )// 释放缓冲空间
            {
                delete[] p_data;
                p_data = NULL;
            }

        }
        QImage a((uchar*)p_data,1280,720,QImage::Format_ARGB32);
        m_preview->setPixmap(QPixmap::fromImage(a));
    }
}


