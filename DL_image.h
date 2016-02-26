#ifndef DL_IMAGE_H
#define DL_IMAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QFileInfo>

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long LONG;

#pragma pack (1)        /* 设置数据1字节对齐 */
typedef struct tagBITMAPFILEHEADER {
 WORD bfType;//固定为0x4d42
 DWORD bfSize; //文件大小
 WORD bfReserved1; //保留字，不考虑
 WORD bfReserved2; //保留字，同上
 DWORD bfOffBits; //实际位图数据的偏移字节数，即前三个部分长度之和
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER{
 //public:
 DWORD biSize; //指定此结构体的长度，为40
 LONG biWidth; //位图宽
 LONG biHeight; //位图高
 WORD biPlanes; //平面数，为1
 WORD biBitCount; //采用颜色位数，可以是1，2，4，8，16，24，新的可以是32
 DWORD biCompression; //压缩方式，可以是0，1，2，其中0表示不压缩
 DWORD biSizeImage; //实际位图数据占用的字节数
 LONG biXPelsPerMeter; //X方向分辨率
 LONG biYPelsPerMeter; //Y方向分辨率
 DWORD biClrUsed; //使用的颜色数，如果为0，则表示默认值(2^颜色位数)
 DWORD biClrImportant; //重要颜色数，如果为0，则表示所有颜色都是重要的
} BITMAPINFOHEADER;

//调色板Palette，当然，这里是对那些需要调色板的位图文件而言的。24位和32位是不需要调色板的。
//（似乎是调色板结构体个数等于使用的颜色数。）
typedef struct tagRGBQUAD {
 //public:
 BYTE rgbBlue; //该颜色的蓝色分量
 BYTE rgbGreen; //该颜色的绿色分量
 BYTE rgbRed; //该颜色的红色分量
 BYTE rgbReserved; //保留值
} RGBQUAD;
#pragma pack () /* 取消数据1字节对齐 */

class DL_Image : public QWidget
{
    Q_OBJECT
public:
    explicit DL_Image(QWidget *parent = 0);
    ~DL_Image();

    enum StackIamgeFormat{
        Image_BMP,
        Image_JPG,
        Image_PNG,
        Image_Invalid,
    };

signals:

public slots:
    void buttonshow();

protected:
    void resizeEvent(QResizeEvent *);

private:
    void init();
    void showImageDetail();
    void updateImageFormat();
    int getFileBitDepth(QString filename,QFileInfo *Finfo);

private:
    /*Function*/
    QPushButton *m_curfilepath;
    QLabel      *m_preview;
    QFileInfo   *m_curFileInfo;

    /*BMP Information*/
    BITMAPFILEHEADER m_Header;
    BITMAPINFOHEADER m_HeaderInfo;
    RGBQUAD          m_ImageRGB;

    /*Image Information Title*/
    QLabel      *m_TName;
    QLabel      *m_TSize;
    QLabel      *m_TFormat;
    QLabel      *m_TDepth;

    /*Image Information Detail*/
    QLabel      *m_DName;
    QLabel      *m_DSize;
    QLabel      *m_DFormat;
    QLabel      *m_DDepth;

    /*Image*/
    QImage      *m_LoadImage;

};

#endif // DL_IMAGE_H
