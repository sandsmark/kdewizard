#ifndef _TOPLEVEL_H_
#define _TOPLEVEL_H_


#include <kapp.h>
#include <ktopwidget.h>
#include <kwizard.h>


class TopLevel : public KTopLevelWidget
{
  Q_OBJECT
  
public:

  TopLevel();

  void addPage(QString title, QWidget *page);
  
private:

  KWizard    *wizard;
    
};

#endif
