#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QTabWidget>

class DL_ImageDetail;
class DL_ImageBinary;
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
    DL_ImageDetail    *m_Image;
    DL_ImageBinary *m_ImageLibrary;
};

#endif // MAINWINDOW_H
