#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QTabWidget>

class DL_Image;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:

public slots:

protected:
    void resizeEvent(QResizeEvent *);
private:
    QTabWidget  *m_Main;
    DL_Image    *m_Image;
};

#endif // MAINWINDOW_H
