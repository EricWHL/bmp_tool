
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
    this->tempFileListAnalysis();
}

void EC_CodeGenerationTemplates::tempFileListAnalysis()
{
    QStringList::const_iterator constIterator;
    for (constIterator = m_CodeTmpFileList.constBegin(); constIterator != m_CodeTmpFileList.constEnd();
         ++constIterator) {
        QFileInfo* curfileinfo = new QFileInfo ((*constIterator).toLocal8Bit().constData());
        m_FileListAna.append(*curfileinfo);
        delete curfileinfo;
    }
    QFileInfo tgrtmp;
    for (int i = 0; i < m_FileListAna.size(); ++i) {
        tgrtmp = m_FileListAna.at(i);
        for (int j = 1; j < m_FileListAna.size(); ++j) {
            if(0 == QString::localeAwareCompare(tgrtmp.baseName(),m_FileListAna.at(j).baseName())) {
                if(0!= QString::localeAwareCompare(tgrtmp.completeSuffix(),m_FileListAna.at(j).completeSuffix())) {
                    if(-1 == m_CodeTempCtgy->findText(tgrtmp.baseName())) {
                        m_CodeTempCtgy->addItem(tgrtmp.baseName());
                    }
                }
            }
        }
    }
}


