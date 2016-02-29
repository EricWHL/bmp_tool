#include"DL_ImageGenerateBMP.h"

ImageGenerateBMP::ImageGenerateBMP(QWidget *parent = 0)
    :QWidget(parent)
{
    init();
}

ImageGenerateBMP::~ImageGenerateBMP()
{

}

ImageGenerateBMP::init()
{
    memset(&m_Header,0,sizeof(BITMAPFILEHEADER));
    memset(&m_HeaderInfo,0,sizeof(BITMAPINFOHEADER));
    memset(&m_ImageRGB,0,sizeof(RGBQUAD));
}

ImageGenerateBMP::generateBMP(QString filename)
{
	QFile file(filename);
	if(file.open(QIODevice::ReadOnly))
    {
        int flen = file.size();

        // 1 分配缓冲空间
        char *pdata = new char [flen + 54];
        if ( NULL == pdata )
        {
            QMessageBox::information(NULL, NULL, "malloc buffer failed...");
            return 0;
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
            return 0;
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
        QFile fd(Finfo->filePath() + ".bmp");
        fd.open(QIODevice::WriteOnly);
        fd.close();
        fd.open(QIODevice::ReadWrite);
        if ( fd.isOpen() )
        {
            //read or write the file "filename"
            QDataStream newFile(&fd);
            newFile.writeRawData(pdata,flen + 54);

        }

        if( NULL != pdata )// 释放缓冲空间
        {
            delete[] pdata;
            pdata = NULL;
        }


	
}
