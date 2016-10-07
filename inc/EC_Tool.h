#ifndef DL_TOOL_H
#define DL_TOOL_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

class DL_Tool : public QWidget
{
    Q_OBJECT
public:
    explicit DL_Tool(QWidget *parent = 0);

signals:

public slots:
private:
    QPushButton* m_FilePath;
    QLabel* m_discribtion;
};

#endif // DL_TOOL_H
