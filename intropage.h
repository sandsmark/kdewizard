#ifndef _INTROPAGE_H_
#define _INTROPAGE_H_


#include <html.h>


class IntroPage : public KHTMLView
{
  Q_OBJECT
  
public:

  IntroPage(QWidget *parent=0, const char *name=0);

};


#endif