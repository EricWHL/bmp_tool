#ifndef EC_ZIPC_H
#define EC_ZIPC_H

#include <QWidget>
#include <QTableView>
#include <QPushButton>

class EC_Zipc : public QWidget
{
    Q_OBJECT
public:
    explicit EC_Zipc(QWidget *parent = 0);

signals:

public slots:

private:
    void init();


private:
    QTableView* m_mainView;
};

#endif // EC_ZIPC_H
