#ifndef DL_IMAGELIBRARY_H
#define DL_IMAGELIBRARY_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
class DL_Imagelibrary : public QWidget
{
    Q_OBJECT
public:
    explicit DL_Imagelibrary(QWidget *parent = 0);
    ~DL_Imagelibrary();

signals:

protected:
	void resizeEvent(QResizeEvent *);
	
public slots:
    void loadFile();

private:
	void init();
    void showFile(QString filename);

private:
    /*Function*/
    QPushButton *m_curfilepath;
    QLabel      *m_preview;

};

#endif // DL_IMAGELIBRARY_H
