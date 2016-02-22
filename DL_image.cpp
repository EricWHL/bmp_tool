#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include "DL_image.h"

DL_Image::DL_Image(QWidget *parent)
    : QWidget(parent)
    , m_file(new QPushButton(this))
    , m_preview(new QLabel(this))
    , m_FName(new QLabel(this))
    , m_FSize(new QLabel(this))
    , m_FFormat(new QLabel(this))
    , m_FileName(new QLabel(this))
    , m_FileSize(new QLabel(this))
    , m_FileFormat(new QLabel(this))
{
    init();

    resize(maximumWidth(),maximumHeight());

    connect(m_file,SIGNAL(clicked(bool)),this,SLOT(buttonshow()));
}

DL_Image::~DL_Image()
{

}

void DL_Image::init()
{
    m_file->setText("Load Image File");
    m_preview->setText("PreView");

    m_FName->setText("FileName:");
    m_FSize->setText("FileSize:");
    m_FFormat->setText("File Format:");

}

void DL_Image::resizeEvent(QResizeEvent *)
{
    m_file->setGeometry(10,20,150,50);

    m_FName->setGeometry(10,72,150,20);
    m_FSize->setGeometry(10,92,150,20);
    m_FFormat->setGeometry(10,112,150,20);

    m_FileName->setGeometry(162,72,50,20);
    m_FileSize->setGeometry(162,92,50,20);
    m_FileFormat->setGeometry(162,112,50,20);

    m_preview->setGeometry(300,20,1280,720);
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
            QImage* img=new QImage;

            if(! ( img->load(filename) ) ) //加载图像
            {
                QMessageBox::information(this,
                                         tr("打开图像失败"),
                                         tr("打开图像失败!"));
                delete img;
                return;
            }
            m_preview->setPixmap(QPixmap::fromImage(*img));
        }
}
