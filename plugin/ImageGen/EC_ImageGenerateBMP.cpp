#include<QFile>
#include<QFileInfo>
#include<QMessageBox>


#include"EC_ImageGenerateBMP.h"

ImageGenerateBMP::ImageGenerateBMP(QWidget *parent)
    :QWidget(parent)
{
    init();
}

ImageGenerateBMP::~ImageGenerateBMP()
{

}

void ImageGenerateBMP::init()
{
    memset(&m_Header,0,sizeof(BITMAPFILEHEADER));
    memset(&m_HeaderInfo,0,sizeof(BITMAPINFOHEADER));
    memset(&m_ImageRGB,0,sizeof(RGBQUAD));
}

void ImageGenerateBMP::generateBMP(QString filename,int width,int height)
{
	QFile file(filename);
    QFileInfo Finfo(filename);
    if(file.open(QIODevice::ReadOnly))
    {
        int flen = file.size();

        // 1 分配缓冲空间
        char *pdata = new char [flen + 54];
        if ( NULL == pdata )
        {
            QMessageBox::information(NULL, NULL, "malloc buffer failed...");
        }
        memset(pdata, 0, flen+ 54);


        // 2 把数据读到缓冲
        QDataStream mystream(&file);
        if ( -1 == mystream.readRawData(&pdata[54], flen))
        {
            QMessageBox::information(NULL, NULL, "readRawData failed...");
            if( NULL != pdata )// 释放缓冲空间
            {
                delete[] pdata;
                pdata = NULL;
            }
        }
        m_Header.bfType = 0x4D42;
        m_Header.bfSize = flen + 54;
        m_Header.bfOffBits = 54;

        m_HeaderInfo.biWidth = width;
        m_HeaderInfo.biHeight = height;
        m_HeaderInfo.biSize = 40;
        m_HeaderInfo.biPlanes = 1;
        m_HeaderInfo.biBitCount = 32;
        m_HeaderInfo.biCompression = 0;
        m_HeaderInfo.biSizeImage = flen;
        m_HeaderInfo.biXPelsPerMeter = 3780;
        m_HeaderInfo.biYPelsPerMeter = 3780;
    
        memcpy(pdata,&m_Header,sizeof(BITMAPFILEHEADER));
        memcpy(&pdata[14],&m_HeaderInfo,sizeof(BITMAPINFOHEADER));
        QFile fd(Finfo.filePath() + "Generate1111111.bmp");
        fd.open(QIODevice::WriteOnly);
        fd.close();
        fd.open(QIODevice::ReadWrite);
        if ( fd.isOpen() )
        {
            //read or write the file "filename"
            QDataStream newFile(&fd);
            imgDataExchange(&pdata[54],width,height);
            newFile.writeRawData(pdata,flen + 54);
            QMessageBox::information(NULL, NULL, "文件生成成功!");

        }

        if( NULL != pdata )// 释放缓冲空间
        {
            delete[] pdata;
            pdata = NULL;
        }
    }
    else {
        QMessageBox::information(NULL, NULL, "文件打开失败!");
    }
}

BITMAPFILEHEADER ImageGenerateBMP::getBMPHeader(QString filename)
{
    QFile file(filename);
    BITMAPFILEHEADER header;

    memset(&header,0,sizeof(BITMAPFILEHEADER));

    if(file.open(QIODevice::ReadOnly)) {
        int flen = file.size();

        // 1 分配缓冲空间
        char *pdata = new char [flen];
        if ( NULL == pdata )
        {
            QMessageBox::information(NULL, NULL, "malloc buffer failed...");
        }
        memset(pdata, 0, flen);
        QDataStream filestream(&file);
        if ( -1 == filestream.readRawData(pdata, flen))
        {
            QMessageBox::information(NULL, NULL, "readRawData failed...");
            if( NULL != pdata )// 释放缓冲空间
            {
                delete[] pdata;
                pdata = NULL;
            }
        }
        memcpy(&header,pdata,sizeof(BITMAPFILEHEADER));
    }
    else {
        QMessageBox::information(NULL, NULL, "文件打开失败!");
    }
    return header;
}

BITMAPINFOHEADER ImageGenerateBMP::getBMPHeaderInfo(QString filename)
{
    QFile file(filename);
    BITMAPINFOHEADER headerInfo;

    memset(&headerInfo,0,sizeof(BITMAPINFOHEADER));

    if(file.open(QIODevice::ReadOnly)) {
        int flen = file.size();

        // 1 分配缓冲空间
        char *pdata = new char [flen];
        if ( NULL == pdata )
        {
            QMessageBox::information(NULL, NULL, "malloc buffer failed...");
        }
        memset(pdata, 0, flen);
        QDataStream filestream(&file);
        if ( -1 == filestream.readRawData(pdata, flen))
        {
            QMessageBox::information(NULL, NULL, "readRawData failed...");
            if( NULL != pdata )// 释放缓冲空间
            {
                delete[] pdata;
                pdata = NULL;
            }
        }
        memcpy(&headerInfo,&pdata[14],sizeof(BITMAPINFOHEADER));

    }
    else {
        QMessageBox::information(NULL, NULL, "文件打开失败!");
    }
    return headerInfo;
}
void ImageGenerateBMP::imgDataExchange(char* data,int width,int height)
{
    char *tmp = new char[width*height*4];

    for (int i=height-1,j = 0; i>=0; i--,j ++) {
        memcpy(&tmp[j*width*4],&data[i*width*4],width*4);
    }
    memcpy(data,tmp,width*4*height);
    delete [] tmp;
}


