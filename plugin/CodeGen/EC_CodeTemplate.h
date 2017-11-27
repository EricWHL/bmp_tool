#ifndef EC_CODETEMPLATE_H
#define EC_CODETEMPLATE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>

class EC_CodeTemplate : public QWidget
{
    Q_OBJECT
public:
    explicit EC_CodeTemplate(QWidget *parent = 0);

signals:

public slots:
    void ctgChanged();

public:
    void init();

protected:
    void resizeEvent(QResizeEvent *);

private:
    /* Category define */
    QLabel*         m_CtgTl;
    QLineEdit*      m_CtgDtl;
    /* Category define */

    /* function define */
    QCheckBox*      m_FnCreCk;
    QCheckBox*      m_FnDesCk;
    QCheckBox*      m_FnInsCk;
    /* function define */


};

#endif // EC_CODETEMPLATE_H
