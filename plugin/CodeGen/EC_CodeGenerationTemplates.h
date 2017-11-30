#ifndef EC_CODEGENERATIONTEMPLATES_H
#define EC_CODEGENERATIONTEMPLATES_H

#include <QWidget>
#include <QComboBox>
#include <QStringList>

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

private:
    QComboBox* m_CodeTempCtgy;
    QStringList m_CodeTmpFileList;
};
#endif // EC_CODEGENERATIONTEMPLATES_H
