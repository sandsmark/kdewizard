#ifndef _PRINTERPAGE_H_
#define _PRINTERPAGE_H_


#include <qwidget.h>


class PrinterPage : public QWidget
{
  Q_OBJECT
  
public:

  PrinterPage(QWidget *parent=0, const char *name=0);

public slots:

  void togglePrinter();

};


#endif(
