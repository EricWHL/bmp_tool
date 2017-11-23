#ifndef EC_CODEGENERATIONTOOLS_H
#define EC_CODEGENERATIONTOOLS_H

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>

class EC_CodeGenerationTools : public QWidget
{
    Q_OBJECT
public:
    explicit EC_CodeGenerationTools(QWidget *parent = 0);

public:
    void init();

signals:

public slots:
    void copyRightRecord();
    void copyRightRefresh();
    void copyRightSave();

private:
    QPushButton* m_CopyRight;
    QPushButton* m_SaveCopyRight;

    QTextEdit*  m_CopyRightDetail;
};

#endif // EC_CODEGENERATIONTOOLS_H
