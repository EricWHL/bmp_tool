#ifndef DL_TOOL_H
#define DL_TOOL_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QFileDevice>
#include <QFileSystemWatcher>
#include <QFile>
#include <QFileInfoList>
#include <QDir>

class PrivateUsbTools;

class EC_Tool : public QWidget
{
    Q_OBJECT
public:
    explicit EC_Tool(QWidget *parent = 0);

    void addUsbDev(QString dev);
    void delUsbDev(QString dev);
    QFileInfoList GetFileList(QString path);
    void readBuffer();

signals:

public slots:
    void genFiles();

private:
    void init();
    void usbToolsInit();



private:
    QGroupBox* m_UsbTlGp;
    QComboBox* m_UsbRdLst;
    QPushButton* m_UsbGrtBtn;
    QLabel* m_UsbRdPt;
    QLabel* m_UsbFlPt;
};

#endif // DL_TOOL_H
