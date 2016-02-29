#ifndef DL_IMAGE_H
#define DL_IMAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QFileInfo>



class DL_ImageDetail : public QWidget
{
    Q_OBJECT
public:
    explicit DL_ImageDetail(QWidget *parent = 0);
    ~DL_ImageDetail();

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
