#include <QFileInfo>
#include <QApplication>
#include <QDebug>
#include "EC_CodeGenerationTemplates.h"


EC_CodeGenerationTemplates::EC_CodeGenerationTemplates(QWidget *parent)
    : QWidget(parent)
    , m_CodeTempCtgy(new QComboBox(this))
{
    init();
    this->setWindowTitle("Code Generate");
}
EC_CodeGenerationTemplates::~EC_CodeGenerationTemplates()
{

}

void EC_CodeGenerationTemplates::init()
{
    m_CodeTempCtgy->setGeometry(10,10,200,20);
}

void EC_CodeGenerationTemplates::saveTempFiles(QStringList files)
{
    m_CodeTmpFileList = files;

    QStringList::const_iterator constIterator;
    for (constIterator = m_CodeTmpFileList.constBegin(); constIterator != m_CodeTmpFileList.constEnd();
         ++constIterator) {
        QFileInfo* curfileinfo = new QFileInfo ((*constIterator).toLocal8Bit().constData());

        qDebug()<<curfileinfo->fileName();

        delete curfileinfo;

    }
}


