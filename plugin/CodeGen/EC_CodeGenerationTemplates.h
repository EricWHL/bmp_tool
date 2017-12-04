#ifndef EC_CODEGENERATIONTEMPLATES_H
#define EC_CODEGENERATIONTEMPLATES_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QList>
#include <QStringList>
#include <QFileInfo>
#include <QApplication>
#include <QString>
#include <QLabel>
#include <QFile>
#include <QLineEdit>

class EC_CodeGenerationTemplates : public QWidget
{
    Q_OBJECT
public:
    explicit EC_CodeGenerationTemplates(QWidget *parent = 0);
    ~EC_CodeGenerationTemplates();
public:
    void saveTempFiles(QStringList files);
    void init();

signals:

public slots:
    void objChanged();
    void genCode();

private:
    /* widget */
    QLabel* m_TempCtgyTl;
    QLabel* m_TempObjTl;

    QLineEdit* m_CodeObjNm;
    QComboBox* m_CodeTempCtgy;
    QStringList m_CodeTmpFileList;

    QPushButton* m_CodeGen;
    /* widget */

    /* Data  Analysis */
    QList<QFileInfo> m_FileListAna;
    /* Data  Analysis */

private:
    void tempFileListAnalysis();
};
#endif // EC_CODEGENERATIONTEMPLATES_H
