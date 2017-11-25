#ifndef DL_IMAGELIBRARY_H
#define DL_IMAGELIBRARY_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QFileInfo>
#include <QComboBox>

class DL_ImageBinary : public QWidget
{
    Q_OBJECT
public:
    explicit DL_ImageBinary(QWidget *parent = 0);
    ~DL_ImageBinary();

protected:
	void resizeEvent(QResizeEvent *);
	
public slots:
    void loadFile();
    void generateBMP();

private:
	void init();
    void showFile(QString filename);

private:
    /*Function*/
    QPushButton *m_curfilepath;
    QLabel      *m_preview;

    QString     m_curFile;

    QLabel      *m_FName;
    QLabel      *m_FSize;
    QComboBox   *m_FRect;

    QLabel      *m_DName;
    QLabel      *m_DSize;

    QPushButton *m_GenerateBMP;


};

#endif // DL_IMAGELIBRARY_H
