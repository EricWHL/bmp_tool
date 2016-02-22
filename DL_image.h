#ifndef DL_IMAGE_H
#define DL_IMAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class DL_Image : public QWidget
{
    Q_OBJECT
public:
    explicit DL_Image(QWidget *parent = 0);
    ~DL_Image();

signals:

public slots:
    void buttonshow();

protected:
    void resizeEvent(QResizeEvent *);

private:
    void init();

private:
    /*Main Window Function*/
    QPushButton *m_file;
    QLabel      *m_preview;

    /*Main Window Image Information Title*/
    QLabel      *m_FName;
    QLabel      *m_FSize;
    QLabel      *m_FFormat;

    /*Main Window Image Information Detail*/
    QLabel      *m_FileName;
    QLabel      *m_FileSize;
    QLabel      *m_FileFormat;

};

#endif // DL_IMAGE_H
