#ifndef _LINKPAGE_H_
#define _LINKPAGE_H_


#include <qwidget.h>


class LinkPage : public QWidget
{
  Q_OBJECT
  
public:

  LinkPage(QWidget *parent=0, const char *name=0);

  void toggleLink(QString link, QString destination);

public slots:

  void linkKDE();
  void linkFTP();
  void linkDevel();

};


#endif(
