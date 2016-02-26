#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include "DL_image.h"


static int g_bitdepth = 0;//save the bmp bit-depth value

DL_Image::DL_Image(QWidget *parent)
    : QWidget(parent)
    , m_curfilepath(new QPushButton(this))
    , m_preview(new QLabel(this))
    , m_curFileInfo(NULL)
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

    memset(&m_Header,0,sizeof(BITMAPFILEHEADER));
    memset(&m_HeaderInfo,0,sizeof(BITMAPINFOHEADER));
    memset(&m_ImageRGB,0,sizeof(RGBQUAD));

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
    m_DName->setText(m_curFileInfo->fileName());
    /* -- 2016-02-25 change begin zhaolong -- */
    m_DDepth->setText(QString::number(m_HeaderInfo.biBitCount));
    /* -- 2016-02-25 change end zhaolong -- */
    updateImageFormat();
    if(NULL != m_curFileInfo) {
        delete m_curFileInfo;
        m_curFileInfo = NULL;
    }
}

void DL_Image::updateImageFormat()
{
    /* -- 2016-02-25 change begin zhaolong -- */
    if( 0 == m_HeaderInfo.biBitCount )
    {
        m_DFormat->setText("not bmp ... ");
    }
    else
    {
        m_DFormat->setText(QString::number(m_HeaderInfo.biBitCount) +QString("-bit RGB"));
    }
    /* -- 2016-02-25 change end zhaolong -- */
}


void DL_Image::buttonshow()
{
    qDebug()<<"ok!!!!!!!!!!!!!!!!!!!!";

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
        /* -- 2016-02-25 add begin zhaolong --*/
        m_curFileInfo = new QFileInfo(curFile);
        g_bitdepth = getFileBitDepth(curFile,m_curFileInfo);
        /* -- 2016-02-25 add end zhaolong --*/

        if(! ( m_LoadImage->load(curFile) ) ) //加载图像
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


/*****************************************************************
*
* Description
*   open the bmp file in bytes and return the bmp bit depth
*
* Inputs
*   filename: the bmp file name
*
* Outputs
*   None.
*
* Return Codes
*   0:   wrong in something...
*   1/4/8/16/24/32: the bit-depth of the bmp file
*
* Author
*   zhaolong (2016.02.25)
*
*****************************************************************/
int DL_Image::getFileBitDepth(QString filename,QFileInfo *Finfo)
{
    int bitdepth = 0;
    QFile file(filename);

    // 0 打开文件获取文件长度
    if(file.open(QIODevice::ReadWrite))
    {
        int flen = file.size();

        // 1 分配缓冲空间
        char *pdata = new char [flen + 56];
        if ( NULL == pdata )
        {
            QMessageBox::information(NULL, NULL, "malloc buffer failed...");
            return 0;
        }
        memset(pdata, 0, flen);


        // 2 把数据读到缓冲
        QDataStream mystream(&file);
        if ( -1 == mystream.readRawData(pdata + 56, flen))
        {
            QMessageBox::information(NULL, NULL, "readRawData failed...");
            if( NULL != pdata )// 释放缓冲空间
            {
                delete[] pdata;
                pdata = NULL;
            }
            return 0;
        }
        m_Header.bfType = 0x4D42;
        m_Header.bfSize = flen + 54 + 2;
        m_Header.bfOffBits = 54;

        m_HeaderInfo.biWidth = 1280;
        m_HeaderInfo.biHeight = 720;
        m_HeaderInfo.biSize = 40;
        m_HeaderInfo.biPlanes = 1;
        m_HeaderInfo.biBitCount = 32;
        m_HeaderInfo.biCompression = 0;
        m_HeaderInfo.biSizeImage = flen + 2;
        m_HeaderInfo.biXPelsPerMeter = 2834;
        m_HeaderInfo.biYPelsPerMeter = 2834;

        memcpy(pdata,&m_Header,sizeof(BITMAPFILEHEADER));
        memcpy(&pdata[14],&m_HeaderInfo,sizeof(BITMAPINFOHEADER));
        QFile fd(Finfo->filePath() + "change.bmp");
        fd.open(QIODevice::WriteOnly);
        fd.close();
        fd.open(QIODevice::ReadWrite);
        if ( fd.isOpen() )
        {
            //read or write the file "filename"
            QDataStream newFile(&fd);
            newFile.writeRawData(pdata,flen + 56);

        }

        if( NULL != pdata )// 释放缓冲空间
        {
            delete[] pdata;
            pdata = NULL;
        }


        // 3 查验是否是bmp图片文件
        if( m_Header.bfType != 0x424D )
        {
            //QMessageBox::information(NULL, NULL, "it's not bmp file...");
            return 0;
        }

        // 4 检验图片位深度是否正确
        if( bitdepth!=1  && bitdepth!=4  &&
            bitdepth!=8  && bitdepth!=16 &&
            bitdepth!=24 && bitdepth!=32)
        {
            QMessageBox::information(NULL, NULL, "wrong bit-depth in bmp file...");
            return 0;
        }

        // 5 关闭文件
        file.close();
        return bitdepth;
    }
    else
    {
        QMessageBox::information(NULL, NULL, "open file failed...");
        return 0;
    }
}








