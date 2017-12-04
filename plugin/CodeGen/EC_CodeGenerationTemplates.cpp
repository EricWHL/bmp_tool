#include <QMessageBox>
#include <QDebug>

#include "EC_CodeGenerationTemplates.h"

EC_CodeGenerationTemplates::EC_CodeGenerationTemplates(QWidget *parent)
    : QWidget(parent)
    , m_TempCtgyTl (new QLabel(this))
    , m_TempObjTl (new QLabel(this))
    , m_CodeTempCtgy (new QComboBox(this))
    , m_CodeObjNm (new QLineEdit(this))
    , m_CodeGen (new QPushButton(this))
{
    init();
    this->setWindowTitle("Code Generate");
    connect(m_CodeObjNm, SIGNAL(textChanged(QString)), this, SLOT(objChanged()));
    connect(m_CodeGen, SIGNAL(clicked(bool)), this, SLOT(genCode()));
}
EC_CodeGenerationTemplates::~EC_CodeGenerationTemplates()
{

}

void EC_CodeGenerationTemplates::init()
{
    m_TempCtgyTl->setText("Template Category:");
    m_TempObjTl->setText("Object Name:");

    m_TempCtgyTl->setGeometry(10,10,105,20);
    m_CodeTempCtgy->setGeometry(120,10,200,20);

    m_TempObjTl->setGeometry(10,35,105,20);
    m_CodeObjNm->setGeometry(120,35,200,20);

    m_CodeGen->setText("Code Generate");
    m_CodeGen->setGeometry(330,10,200,50);
    m_CodeGen->setEnabled(false);

}

void EC_CodeGenerationTemplates::objChanged()
{
    m_CodeGen->setEnabled(true);
}

void EC_CodeGenerationTemplates::genCode()
{

    for (int i = 0; i < m_FileListAna.size(); ++i) {
        if(0 == QString::localeAwareCompare(m_CodeTempCtgy->currentText(),m_FileListAna.at(i).baseName())) {
            QFile* tempfile = new QFile(m_FileListAna.at(i).absoluteFilePath());
            if(!tempfile->open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug()<<"[EC_CodeGenerationTemplates][genCode]Can't open the file!"<<endl;
            }
            if(0 == QString::localeAwareCompare("tmph",m_FileListAna.at(i).completeSuffix())) {
                QByteArray* containHFile = new QByteArray(tempfile->readAll());
                containHFile->replace("###",m_CodeObjNm->text().toStdString().c_str());
                containHFile->replace("@@@",m_CodeObjNm->text().toUpper().toStdString().c_str());
                QByteArray* genFileName = new QByteArray(m_FileListAna.at(i).baseName().toStdString().c_str());
                genFileName->replace("###",m_CodeObjNm->text().toStdString().c_str());
                QString temFileName = genFileName->data();
                QFile* genHfile = new QFile( temFileName + ".h");
                if(!genHfile->open(QIODevice::ReadWrite | QIODevice::Text)) {
                    qDebug()<<"[EC_CodeGenerationTemplates][genCode]Can't open the file!"<<endl;
                }
                genHfile->write(containHFile->data(),containHFile->size());
                genHfile->close();

                delete genHfile;
                delete containHFile;
            }
            if(0 == QString::localeAwareCompare("tmpc",m_FileListAna.at(i).completeSuffix())) {
                QByteArray* containCFile = new QByteArray(tempfile->readAll());
                containCFile->replace("###",m_CodeObjNm->text().toStdString().c_str());
                containCFile->replace("@@@",m_CodeObjNm->text().toUpper().toStdString().c_str());
                QByteArray* genFileName = new QByteArray(m_FileListAna.at(i).baseName().toStdString().c_str());
                genFileName->replace("###",m_CodeObjNm->text().toStdString().c_str());
                QString temFileName = genFileName->data();
                QFile* genCfile = new QFile( temFileName + ".c");
                if(!genCfile->open(QIODevice::ReadWrite | QIODevice::Text)) {
                    qDebug()<<"[EC_CodeGenerationTemplates][genCode]Can't open the file!"<<endl;
                }
                genCfile->write(containCFile->data(),containCFile->size());
                genCfile->close();

                delete genCfile;
                delete containCFile;
            }
            tempfile->close();
            delete tempfile;
        }
    }
    QMessageBox::information(NULL, NULL, "文件生成完了!");
    this->close();
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


