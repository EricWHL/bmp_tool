#ifndef EC_COPYRIGHTCONFIG_H
#define EC_COPYRIGHTCONFIG_H

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>

class EC_CopyRightConfig : public QWidget
{
    Q_OBJECT
public:
    explicit EC_CopyRightConfig(QWidget *parent = 0);

public:
    void init();

signals:

public slots:
    void copyRightSave();
    void copyRightRefresh();

private:
    QPushButton* m_SaveCopyRight;

    QTextEdit*  m_CopyRightDetail;
};

#endif // EC_COPYRIGHTCONFIG_H
