#include <QFileDialog>
#include <QFile>
#include <QMessageBox>

#include "inc/EC_ImageBinary.h"
#include "inc/EC_ImageGenerateBMP.h"

typedef enum _DL_IMG_BNY_RECT {
    DL_IMG_BNY_RECT_800_400 = 0,
    DL_IMG_BNY_RECT_800_480,
    DL_IMG_BNY_RECT_1024_600,
    DL_IMG_BNY_RECT_1024_720,
    DL_IMG_BNY_RECT_MAX,
}DL_IMG_BNY_RECT;

static QString curFilename;

DL_ImageBinary::DL_ImageBinary(QWidget *parent)
    : QWidget(parent)
	, m_curfilepath(new QPushButton(this))
	, m_preview(new QLabel(this))
    , m_FName(new QLabel(this))
    , m_FSize(new QLabel(this))
    , m_DName(new QLabel(this))
    , m_DSize(new QLabel(this))
    , m_GenerateBMP(new QPushButton(this))
    , m_FRect(new QComboBox(this))
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
    m_FRect->addItem("800*400");
    m_FRect->addItem("800*480");
    m_FRect->addItem("1024*600");
    m_FRect->addItem("1024*720");

}

void DL_ImageBinary::resizeEvent(QResizeEvent *)
{
    m_curfilepath->setGeometry(10,20,150,25);
    m_preview->setGeometry(300,20,1280,720);

    m_FName->setGeometry(10,60,120,25);
    m_FSize->setGeometry(10,90,120,25);
    m_FRect->setGeometry(10,120,150,25);

    m_DName->setGeometry(165,60,150,25);
    m_DSize->setGeometry(165,90,150,25);


    m_GenerateBMP->setGeometry(10,500,150,25);

}

void DL_ImageBinary::loadFile()
{
    QString m_curFile;
        m_curFile=QFileDialog::getOpenFileName(this,
                                              tr("选择图像"),
                                              "",
                                              tr("Images library(*.bin *.*)"));
    if(m_curFile.isEmpty())
    {
         return;
    }
    else
    {
        curFilename = m_curFile;
        QFileInfo curFileInfo(m_curFile);
        m_DName->setText(curFileInfo.fileName());

        showFile(m_curFile);
    }
}

void DL_ImageBinary::generateBMP()
{
    ImageGenerateBMP bmpFile;
    int imageWidth = 0;
    int imageHeight = 0;

    switch (m_FRect->currentIndex()) {
    case DL_IMG_BNY_RECT_800_400:
        imageWidth = 800;
        imageHeight = 400;
        break;
    case DL_IMG_BNY_RECT_800_480:
        imageWidth = 800;
        imageHeight = 480;
        break;
    case DL_IMG_BNY_RECT_1024_600:
        imageWidth = 1024;
        imageHeight = 600;
        break;
    case DL_IMG_BNY_RECT_1024_720:
        imageWidth = 1024;
        imageHeight = 720;
        break;
    default:
        break;
    }

    bmpFile.generateBMP(curFilename,imageWidth,imageHeight);
}

void DL_ImageBinary::showFile(QString filename)
{
    QFile File(filename);
    int imageWidth = 0;
    int imageHeight = 0;

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
        switch (m_FRect->currentIndex()) {
        case DL_IMG_BNY_RECT_800_400:
            imageWidth = 800;
            imageHeight = 400;
            break;
        case DL_IMG_BNY_RECT_800_480:
            imageWidth = 800;
            imageHeight = 480;
            break;
        case DL_IMG_BNY_RECT_1024_600:
            imageWidth = 1024;
            imageHeight = 600;
            break;
        case DL_IMG_BNY_RECT_1024_720:
            imageWidth = 1024;
            imageHeight = 720;
            break;
        default:
            break;
        }
        QImage img((uchar*)p_data,imageWidth,imageHeight,QImage::Format_ARGB32);
        m_preview->setPixmap(QPixmap::fromImage(img));
        m_DSize->setText(QString::number(flen) + " 字节");
        File.close();
    }
    else {
        QMessageBox::information(NULL, NULL, "文件打开失败");
    }
}



