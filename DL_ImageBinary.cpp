#include <QFileDialog>
#include <QMessageBox>
#include "DL_ImageBinary.h"

DL_ImageBinary::DL_ImageBinary(QWidget *parent)
    : QWidget(parent)
	, m_curfilepath(new QPushButton(this))
	, m_preview(new QLabel(this))
    , m_curFileInfo(NULL)
    , m_FName(new QLabel(this))
    , m_FSize(new QLabel(this))
    , m_DName(new QLabel(this))
    , m_DSize(new QLabel(this))
    , m_GenerateBMP(new QPushButton(this))
{
    init();
    connect(m_curfilepath,SIGNAL(clicked(bool)),this,SLOT(loadFile()));
    connect(m_GenerateBMP,SIGNAL(clicked(bool)),this,SLOT(generateBMP()));
}

DL_ImageBinary::~DL_ImageBinary()
{
	
}

void DL_ImageBinary::init()
{
    m_curfilepath->setText("加载图片数据文件");
    m_preview->setText("预览");

    m_FName->setText("文件名:");
    m_FSize->setText("文件大小:");
    m_GenerateBMP->setText("生成BMP图片");

}

void DL_ImageBinary::resizeEvent(QResizeEvent *)
{
    m_curfilepath->setGeometry(10,20,150,25);
    m_preview->setGeometry(300,20,1280,720);

    m_FName->setGeometry(10,60,120,25);
    m_FSize->setGeometry(10,90,120,25);

    m_DName->setGeometry(165,60,150,25);
    m_DSize->setGeometry(165,90,150,25);

    m_GenerateBMP->setGeometry(10,500,150,25);

}

void DL_ImageBinary::loadFile()
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
        m_curFileInfo = new QFileInfo(curFile);
        m_DName->setText(m_curFileInfo->fileName());

        showFile(curFile);
    }
    if(NULL != m_curFileInfo) {
        delete m_curFileInfo;
        m_curFileInfo = NULL;
    }
}

void DL_ImageBinary::generateBMP()
{

}

void DL_ImageBinary::showFile(QString filename)
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
        QImage img((uchar*)p_data,1280,720,QImage::Format_ARGB32);
        m_preview->setPixmap(QPixmap::fromImage(img));
        m_DSize->setText(QString::number(flen) + " 字节");
    }
}


