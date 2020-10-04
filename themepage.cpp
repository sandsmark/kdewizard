#include "themepage.h"
#include "theme.h"

#include <kapp.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <kiconloader.h>
#include <ksimpleconfig.h>
#include <kprocess.h>
#include <qdir.h>
#include <stdlib.h>


ThemePage::ThemePage(QWidget *parent, const char *name)
  : QWidget(parent,name)
{
  KIconLoader *iconLoader = kapp->getIconLoader();

  QGridLayout *grid = new QGridLayout(this, 7,5, 8);    

  QPixmap pixmap(kapp->kde_datadir()+"/kdewizard/html/wizard_small.gif");
  QLabel *l = new QLabel(this);
  l->setPixmap(pixmap);
  l->setFixedSize(pixmap.size());
  grid->addMultiCellWidget(l, 0,1 ,3,4, AlignRight);

  l = new QLabel(i18n("KDE provides a great number of possibilities "
  "to configure the look and feel. You can access these possibilities "
  "using the KDE Control Center. For a start, you may select one of "
  "these predefined themes and refine them later on. NOTE: Changeing "
  "a theme at this point is an action that cannot be undone!"), this);  
  l->setAlignment(WordBreak);
  l->setBackgroundColor(white);
  grid->addMultiCellWidget(l, 0,0, 0,2);
  grid->setRowStretch(0,1);

  QPushButton *button = new QPushButton(this);
  button->setPixmap(iconLoader->loadIcon("kdetheme.xpm"));
  button->setFixedSize(button->sizeHint());
  grid->addWidget(button, 2,0);  
  connect(button, SIGNAL(clicked()), this, SLOT(selectDefault()));

  l = new QLabel(i18n("KDE Default Theme"), this);
  l->setMinimumSize(l->sizeHint());
  l->setAlignment(AlignTop);
  l->setBackgroundColor(white);
  grid->addWidget(l, 2,1);

  button = new QPushButton(this);
  button->setPixmap(iconLoader->loadIcon("wintheme.xpm"));
  button->setFixedSize(button->sizeHint());
  grid->addWidget(button, 2,2);  
  connect(button, SIGNAL(clicked()), this, SLOT(selectWindows()));

  l = new QLabel(i18n("Windows Theme"), this);
  l->setMinimumSize(l->sizeHint());
  l->setAlignment(AlignTop);
  l->setBackgroundColor(white);
  grid->addWidget(l, 2,3);

  button = new QPushButton(this);
  button->setPixmap(iconLoader->loadIcon("mactheme.xpm"));
  button->setFixedSize(button->sizeHint());
  grid->addWidget(button, 4,0);  
  connect(button, SIGNAL(clicked()), this, SLOT(selectMacOS()));

  l = new QLabel(i18n("MacOS Theme"), this);
  l->setMinimumSize(l->sizeHint());
  l->setAlignment(AlignTop);
  l->setBackgroundColor(white);
  grid->addWidget(l, 4,1);

  button = new QPushButton(this);
  button->setPixmap(iconLoader->loadIcon("beostheme.xpm"));
  button->setFixedSize(button->sizeHint());
  grid->addWidget(button, 4,2);  
  connect(button, SIGNAL(clicked()), this, SLOT(selectBeOS()));

  l = new QLabel(i18n("BeOS Theme"), this);
  l->setMinimumSize(l->sizeHint());
  l->setAlignment(AlignTop);
  l->setBackgroundColor(white);
  grid->addWidget(l, 4,3);

  grid->setRowStretch(4,2);
  grid->setRowStretch(5,1);

  button = new QPushButton(this);
  button->setPixmap(iconLoader->loadIcon("kcontrol.xpm"));
  button->setFixedSize(button->sizeHint());
  grid->addWidget(button, 6,0);  
  connect(button, SIGNAL(clicked()), this, SLOT(startKControl()));

  l = new QLabel(i18n("Launch KDE Control Center for further refinement"), this);
  l->setMinimumSize(l->sizeHint());
  l->setBackgroundColor(white);
  grid->addMultiCellWidget(l, 6,6 ,1,3);

  grid->activate();

  Theme::mkdirhier(Theme::workDir());
  Theme::mkdirhier(Theme::themesDir());

  setBackgroundColor(white);
}


void ThemePage::installTheme(ThemeType theme)
{
  // delete all window manager pictures
  system("rm $HOME/.kde/share/apps/kwm/pics/*");
  system("rm $HOME/.kde/share/icons/*");
  system("rm $HOME/.kde/share/icons/minit/*");
	
  // switch widget style
  // Note: at the moment, all themes should use Windows style
  QString widgetStyle = "Windows 95";

  // switch Mac-Like Toolbar
  QString macStyle="off";
  if (theme == MacOS)
    macStyle="on";

  // switch toolbar placement
  QString panelPosition = "bottom";
  QString taskbarPosition = "top";
  QString panelStyle = "normal";
  QString panelHidden = "00000000";

  switch (theme)
  {
    case Windows:
      taskbarPosition = "bottom";
      panelStyle = "tiny";
      panelHidden = "11000000";
      break;
    case BeOS:
      taskbarPosition = "top_left";
      panelHidden = "11000000";
      panelPosition = "top";
      break;
    case MacOS:
      taskbarPosition = "bottom";
      break;
  }  	

  // write out the config files
  QString home(QDir::home().path());
  home.append("/.kderc");
  KSimpleConfig *kderc = new KSimpleConfig(home);
  kderc->setGroup("KDE");
  kderc->writeEntry("widgetStyle", widgetStyle);
  kderc->writeEntry("macStyle", macStyle);
  kderc->sync();
  delete kderc;

  KSimpleConfig *kpanelrc = new KSimpleConfig(kapp->localconfigdir()+"/kpanelrc");
  kpanelrc->setGroup("kpanel");
  kpanelrc->writeEntry("Position", panelPosition);
  kpanelrc->writeEntry("TaskbarPosition", taskbarPosition);
  kpanelrc->writeEntry("Style", panelStyle);
  kpanelrc->writeEntry("PanelHidden", panelHidden);

  QString size;
  size = (panelStyle == "normal") ? "45" : "24";
  kpanelrc->writeEntry("BoxHeight", size);
  kpanelrc->writeEntry("BoxWidth", size);

  kpanelrc->sync();
  delete kpanelrc;
 
  // Install theme files ---------------------------------------------

  QString themeFile;

  switch(theme)
  {
    case Windows:
      themeFile = "Windows.tar.gz"; 
      break;
    case MacOS:
      themeFile = "MacOS.tar.gz";
      break;
    case BeOS:
      themeFile = "BeOS.tar.gz";
      break;
    default:
      themeFile = "Default.tar.gz";
  }

  Theme themeConfig;

  themeConfig.instPanel = true;
  themeConfig.instSounds = true;
  themeConfig.instWindowBorder = true;
  themeConfig.instWindowTitlebar = true;
  themeConfig.instWindowButtonLayout = true;
  themeConfig.instWindowGimmick = true;
  themeConfig.instWallpapers = true;
  themeConfig.instColors = true;
  themeConfig.instIcons = true;

  QString name = kapp->kde_datadir()+"/kdewizard/Themes/"+themeFile;

  if (themeConfig.load(name))
  {
    themeConfig.install();
  }  
  else
    printf("could not load!\n");

}


void ThemePage::selectDefault()
{
  installTheme(Default);
}


void ThemePage::selectMacOS()
{
  installTheme(MacOS);
}


void ThemePage::selectWindows()
{
  installTheme(Windows);
}


void ThemePage::selectBeOS()
{
  installTheme(BeOS);
}

void ThemePage::startKControl()
{
  KProcess proc;	
  proc << "kcontrol";
  proc.start(KProcess::DontCare);
}

#include "themepage.moc"
