#ifndef _THEMEPAGE_H_
#define _THEMEPAGE_H_


#include <qwidget.h>


class ThemePage : public QWidget
{
  Q_OBJECT
  
public:

  ThemePage(QWidget *parent=0, const char *name=0);

private:

  enum ThemeType { Default=0, Windows, MacOS, BeOS };
  
  void installTheme(ThemeType theme);
  
private slots:

  void selectDefault();
  void selectMacOS();
  void selectWindows();
  void selectBeOS();
  void startKControl();  
};


#endif
