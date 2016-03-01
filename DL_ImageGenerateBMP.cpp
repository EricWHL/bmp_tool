#include<QFile>
#include<QFileInfo>
#include<QMessageBox>


#include"DL_ImageGenerateBMP.h"

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

void ImageGenerateBMP::generateBMP(QString filename)
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
        memset(pdata, 0, flen);


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

        m_HeaderInfo.biWidth = 1280;
        m_HeaderInfo.biHeight = 720;
        m_HeaderInfo.biSize = 40;
        m_HeaderInfo.biPlanes = 1;
        m_HeaderInfo.biBitCount = 32;
        m_HeaderInfo.biCompression = 0;
        m_HeaderInfo.biSizeImage = flen;
        m_HeaderInfo.biXPelsPerMeter = 3780;
        m_HeaderInfo.biYPelsPerMeter = 3780;
    
        memcpy(pdata,&m_Header,sizeof(BITMAPFILEHEADER));
        memcpy(&pdata[14],&m_HeaderInfo,sizeof(BITMAPINFOHEADER));
        QFile fd(Finfo.filePath() + "Generate.bmp");
        fd.open(QIODevice::WriteOnly);
        fd.close();
        fd.open(QIODevice::ReadWrite);
        if ( fd.isOpen() )
        {
            //read or write the file "filename"
            QDataStream newFile(&fd);
            imgDataExchange(&pdata[54]);
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
void ImageGenerateBMP::imgDataExchange(char* data)
{
    char tmp[1280*4];
    int j = 0;
    for (int i=720-1; i>720/2; i--) {
        memcpy(tmp,&data[j],1280*4);
        memcpy(&data[j],&data[i*1280*4],1280*4);
        memcpy(&data[i*1280*4],tmp,1280*4);
        j +=1280*4;
    }
}


