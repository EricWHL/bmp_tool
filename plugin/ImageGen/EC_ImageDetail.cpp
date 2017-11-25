#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

#include "EC_ImageDetail.h"
#include "EC_ImageGenerateBMP.h"


DL_ImageDetail::DL_ImageDetail(QWidget *parent)
    : QWidget(parent)
    , m_curfilepath(new QPushButton(this))
    , m_preview(new QLabel(this))
    , m_curFileInfo(NULL)
    , m_TName(new QLabel(this))
    , m_TSize(new QLabel(this))
    , m_TDepth(new QLabel(this))
    , m_DName(new QLabel(this))
    , m_DSize(new QLabel(this))
    , m_DDepth(new QLabel(this))
    , m_LoadImage(new QImage)

{
    init();
    connect(m_curfilepath,SIGNAL(clicked(bool)),this,SLOT(buttonshow()));
}

DL_ImageDetail::~DL_ImageDetail()
{

}

void DL_ImageDetail::init()
{
    m_curfilepath->setText("加载图片文件");
    m_preview->setText("预览");

    m_TName->setText("文件名:");
    m_TSize->setText("图片大小:");
    m_TDepth->setText("文件位深度:");



}

void DL_ImageDetail::resizeEvent(QResizeEvent *)
{
    m_curfilepath->setGeometry(10,20,150,25);

    m_TName->setGeometry(10,72,80,20);
    m_TSize->setGeometry(10,92,80,20);
    m_TDepth->setGeometry(10,132,80,20);

    m_DName->setGeometry(92,72,100,20);
    m_DSize->setGeometry(92,92,100,20);
    m_DDepth->setGeometry(92,132,100,20);

    m_preview->setGeometry(300,20,1280,720);
}

void DL_ImageDetail::showImageDetail(QString filename)
{
    BITMAPFILEHEADER header;
    BITMAPINFOHEADER headerInfo;
    ImageGenerateBMP bmpInfo;
    header = bmpInfo.getBMPHeader(filename);
    headerInfo = bmpInfo.getBMPHeaderInfo(filename);

    m_DSize->setText(QString::number(headerInfo.biWidth) + "*" + QString::number(headerInfo.biHeight));
    m_DName->setText(m_curFileInfo->fileName());
    m_DDepth->setText(QString::number(headerInfo.biBitCount));
    if(NULL != m_curFileInfo) {
        delete m_curFileInfo;
        m_curFileInfo = NULL;
    }
}

void DL_ImageDetail::buttonshow()
{
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

        showImageDetail(curFile);
    }
}









