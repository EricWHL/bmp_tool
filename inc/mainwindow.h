#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QTabWidget>
#include "EC_iConvLibIF.h"

class DL_ImageDetail;
class DL_ImageBinary;
class EC_Tool;
class EC_StsMgr;
class EC_CodeGenerationTools;


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

    bool nativeEvent(const QByteArray & eventType, void * message, long*result);

private:
    QTabWidget*                m_Main;
    DL_ImageDetail*            m_Image;
    DL_ImageBinary*            m_ImageLibrary;
    EC_Tool*                   m_Tool;
    EC_iConvLibIF*             m_convLib;
    EC_StsMgr*                   m_StsMgr;
    EC_CodeGenerationTools*    m_CodeGenTool;

    char FirstDriveFromMask (unsigned long unitmask);
};

#endif // MAINWINDOW_H
