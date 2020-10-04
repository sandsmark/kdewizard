#include "linkpage.h"

#include <kapp.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qdir.h>
#include <qpushbutton.h>
#include <kiconloader.h>
#include <kfm.h>


LinkPage::LinkPage(QWidget *parent, const char *name)
  : QWidget(parent,name)
{
  KIconLoader *iconLoader = kapp->getIconLoader();

  QGridLayout *grid = new QGridLayout(this, 6,3, 8);    

  QPixmap pixmap(kapp->kde_datadir()+"/kdewizard/html/wizard_small.gif");
  QLabel *l = new QLabel(this);
  l->setPixmap(pixmap);
  l->setFixedSize(pixmap.size());
  grid->addMultiCellWidget(l, 0,1 ,1,2, AlignRight);

  l = new QLabel(i18n("Finally, I would advise you to create some links "
  "to important ressources on the net for you. All information about "
  "KDE will be only one mouseclick away. Just click the icon to "
  "create the link."), this);  
  l->setAlignment(WordBreak);
  l->setBackgroundColor(white);
  grid->addMultiCellWidget(l, 0,0, 0,1);
  grid->setRowStretch(0,1);

  l = new QLabel(i18n("The KDE homepage"), this);
  l->setMinimumSize(l->sizeHint());
  l->setAlignment(AlignTop);
  l->setBackgroundColor(white);
  grid->addWidget(l, 2,1);
  
  QButton *button = new QPushButton(this);
  button->setPixmap(iconLoader->loadIcon("kdehome.xpm"));
  button->setFixedSize(button->sizeHint());
  grid->addWidget(button, 2,0);  
  connect(button, SIGNAL(clicked()), this, SLOT(linkKDE()));

  l = new QLabel(i18n("The KDE FTP server"), this);
  l->setMinimumSize(l->sizeHint());
  l->setAlignment(AlignTop);
  l->setBackgroundColor(white);
  grid->addWidget(l, 3,1);
  
  button = new QPushButton(this);
  button->setPixmap(iconLoader->loadIcon("kdeftp.xpm"));
  button->setFixedSize(button->sizeHint());
  grid->addWidget(button, 3,0);  
  connect(button, SIGNAL(clicked()), this, SLOT(linkFTP()));

  l = new QLabel(i18n("KDE Developers site"), this);
  l->setMinimumSize(l->sizeHint());
  l->setAlignment(AlignTop);
  l->setBackgroundColor(white);
  grid->addWidget(l, 4,1);
  
  button = new QPushButton(this);
  button->setPixmap(iconLoader->loadIcon("kdedevel.xpm"));
  button->setFixedSize(button->sizeHint());
  grid->addWidget(button, 4,0);  
  connect(button, SIGNAL(clicked()), this, SLOT(linkDevel()));

  grid->setRowStretch(5,1);

  setBackgroundColor(white);
}


void LinkPage::linkKDE()
{
  toggleLink("kdewww.kdelnk", "www.kde.org.kdelnk");
}


void LinkPage::linkFTP()
{
  toggleLink("kdeftp.kdelnk", "ftp.kde.org.kdelnk");
}


void LinkPage::linkDevel()
{
  toggleLink("kdedevel.kdelnk", "devel@kde");
}


void LinkPage::toggleLink(QString link, QString destination)
{
  QString destname = QDir::homeDirPath()+"/Desktop/"+destination;
  QFile dest(destname);

  if (dest.exists())
    dest.remove();
  else {
    QString srcname = kapp->kde_datadir()+"/kdewizard/"+link;
    QString command = "cp "+srcname+" "+destname;
    system(command.data());
  }
    
 KFM kfm;
 kfm.refreshDesktop();
}

#include "linkpage.moc"
