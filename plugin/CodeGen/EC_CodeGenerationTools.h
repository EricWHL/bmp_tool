#ifndef EC_CODEGENERATIONTOOLS_H
#define EC_CODEGENERATIONTOOLS_H

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>

class EC_CopyRightConfig;

class EC_CodeGenerationTools : public QWidget
{
    Q_OBJECT
public:
    explicit EC_CodeGenerationTools(QWidget *parent = 0);
    ~EC_CodeGenerationTools();
public:
    void init();

signals:

public slots:
    void copyRightRecord();


    void makeGenComPro();

private:
    /* copyright config */
    QPushButton* m_CopyRight;
    EC_CopyRightConfig* m_CpRtDtl;
    /* copyright config */

    /* generate complete config */
    QPushButton* m_MakeGenCompPro;
    /* generate complete config */
};

#endif // EC_CODEGENERATIONTOOLS_H
