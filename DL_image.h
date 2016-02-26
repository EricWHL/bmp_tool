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

#pragma pack (1)        /* ��������1�ֽڶ��� */
typedef struct tagBITMAPFILEHEADER {
 WORD bfType;//�̶�Ϊ0x4d42
 DWORD bfSize; //�ļ���С
 WORD bfReserved1; //�����֣�������
 WORD bfReserved2; //�����֣�ͬ��
 DWORD bfOffBits; //ʵ��λͼ���ݵ�ƫ���ֽ�������ǰ�������ֳ���֮��
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER{
 //public:
 DWORD biSize; //ָ���˽ṹ��ĳ��ȣ�Ϊ40
 LONG biWidth; //λͼ��
 LONG biHeight; //λͼ��
 WORD biPlanes; //ƽ������Ϊ1
 WORD biBitCount; //������ɫλ����������1��2��4��8��16��24���µĿ�����32
 DWORD biCompression; //ѹ����ʽ��������0��1��2������0��ʾ��ѹ��
 DWORD biSizeImage; //ʵ��λͼ����ռ�õ��ֽ���
 LONG biXPelsPerMeter; //X����ֱ���
 LONG biYPelsPerMeter; //Y����ֱ���
 DWORD biClrUsed; //ʹ�õ���ɫ�������Ϊ0�����ʾĬ��ֵ(2^��ɫλ��)
 DWORD biClrImportant; //��Ҫ��ɫ�������Ϊ0�����ʾ������ɫ������Ҫ��
} BITMAPINFOHEADER;

//��ɫ��Palette����Ȼ�������Ƕ���Щ��Ҫ��ɫ���λͼ�ļ����Եġ�24λ��32λ�ǲ���Ҫ��ɫ��ġ�
//���ƺ��ǵ�ɫ��ṹ���������ʹ�õ���ɫ������
typedef struct tagRGBQUAD {
 //public:
 BYTE rgbBlue; //����ɫ����ɫ����
 BYTE rgbGreen; //����ɫ����ɫ����
 BYTE rgbRed; //����ɫ�ĺ�ɫ����
 BYTE rgbReserved; //����ֵ
} RGBQUAD;
#pragma pack () /* ȡ������1�ֽڶ��� */

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
