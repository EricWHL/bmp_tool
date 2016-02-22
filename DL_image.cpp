#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include "DL_image.h"

DL_Image::DL_Image(QWidget *parent)
    : QWidget(parent)
    , m_curfilepath(new QPushButton(this))
    , m_preview(new QLabel(this))
    , m_TName(new QLabel(this))
    , m_TSize(new QLabel(this))
    , m_TFormat(new QLabel(this))
    , m_TDepth(new QLabel(this))
    , m_DName(new QLabel(this))
    , m_DSize(new QLabel(this))
    , m_DFormat(new QLabel(this))
    , m_DDepth(new QLabel(this))
    , m_LoadImage(new QImage)
{
    init();
    connect(m_curfilepath,SIGNAL(clicked(bool)),this,SLOT(buttonshow()));
}

DL_Image::~DL_Image()
{

}

void DL_Image::init()
{
    m_curfilepath->setText("加载图片文件");
    m_preview->setText("预览");

    m_TName->setText("文件名:");
    m_TSize->setText("文件大小:");
    m_TFormat->setText("文件格式:");
    m_TDepth->setText("文件位深度:");

}

void DL_Image::resizeEvent(QResizeEvent *)
{
    m_curfilepath->setGeometry(10,20,80,20);

    m_TName->setGeometry(10,72,80,20);
    m_TSize->setGeometry(10,92,80,20);
    m_TFormat->setGeometry(10,112,80,20);
    m_TDepth->setGeometry(10,132,80,20);

    m_DName->setGeometry(92,72,100,20);
    m_DSize->setGeometry(92,92,100,20);
    m_DFormat->setGeometry(92,112,100,20);
    m_DDepth->setGeometry(92,132,100,20);

    m_preview->setGeometry(300,20,1280,720);
}

void DL_Image::showImageDetail()
{
    m_DSize->setText(QString::number(m_LoadImage->width()) + "*" + QString::number(m_LoadImage->height()));
    m_DDepth->setText(QString::number(m_LoadImage->depth()));
    updateImageFormat(m_LoadImage->format());
}

void DL_Image::updateImageFormat(int format)
{
    switch(format)
    {
    case QImage::Format_Mono:
        break;
    case QImage::Format_RGB32:
        m_DFormat->setText("32-bit RGB");
        break;
    }
}

void DL_Image::buttonshow()
{
    qDebug()<<"ok!!!!!!!!!!!!!!!!!!!!";
    QString filename;
        filename=QFileDialog::getOpenFileName(this,
                                              tr("选择图像"),
                                              "",
                                              tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
        if(filename.isEmpty())
        {
             return;
        }
        else
        {
            if(! ( m_LoadImage->load(filename) ) ) //加载图像
            {
                QMessageBox::information(this,
                                         tr("打开图像失败"),
                                         tr("打开图像失败!"));
                delete m_LoadImage;
                return;
            }
            m_preview->setPixmap(QPixmap::fromImage(*m_LoadImage));
            showImageDetail();
        }
}
