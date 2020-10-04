#ifndef _DRIVEPAGE_H_
#define _DRIVEPAGE_H_


#include <qwidget.h>
#include <qlined.h>


class DrivePage : public QWidget
{
  Q_OBJECT
  
public:

  DrivePage(QWidget *parent=0, const char *name=0);

public slots:

  void floppy1();
  void floppy2();
  void cdrom();

private:

  QLineEdit *edit1, *edit2, *edit3;

  void toggleDrive(QString file, QString name, QString mount, QString icon);
  
};


#endif(
