#include "drivepage.h"

#include <kapp.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qdir.h>
#include <qpushbutton.h>
#include <kiconloader.h>
#include <kfm.h>
#include <qtextstream.h>


DrivePage::DrivePage(QWidget *parent, const char *name)
  : QWidget(parent,name)
{
  KIconLoader *iconLoader = kapp->getIconLoader();

  QGridLayout *grid = new QGridLayout(this, 8,4, 8);    

  QPixmap pixmap(kapp->kde_datadir()+"/kdewizard/html/wizard_small.gif");
  QLabel *l = new QLabel(this);
  l->setPixmap(pixmap);
  l->setFixedSize(pixmap.size());
  grid->addMultiCellWidget(l, 0,1 ,2,3, AlignRight);

  l = new QLabel(i18n("Ok, now we should add some nice icons for "
		      "your disc and cdrom drives to the desktop. "
		      "You just have to click the drive icon to "
		      "create/delete the icon. In rare cases, it "
		      "will be necessary to correct the drive info."), this);  
  l->setAlignment(WordBreak);
  l->setBackgroundColor(white);
  grid->addMultiCellWidget(l, 0,0, 0,2);
  grid->setRowStretch(0,1);

  l = new QLabel(i18n("1st Floppy Disc drive"), this);
  l->setMinimumSize(l->sizeHint());
  l->setAlignment(AlignTop);
  l->setBackgroundColor(white);
  grid->addWidget(l, 3,1);
  
  QButton *button = new QPushButton(this);
  button->setPixmap(iconLoader->loadIcon("3floppy_unmount.xpm"));
  button->setFixedSize(button->sizeHint());
  grid->addWidget(button, 3,0);  
  connect(button, SIGNAL(clicked()), this, SLOT(floppy1()));

  edit1 = new QLineEdit(this);
  edit1->setText("/dev/fd0");
  grid->addWidget(edit1,3,2);

  l = new QLabel(i18n("2nd Floppy Disc drive"), this);
  l->setMinimumSize(l->sizeHint());
  l->setAlignment(AlignTop);
  l->setBackgroundColor(white);
  grid->addWidget(l, 4,1);
  
  button = new QPushButton(this);
  button->setPixmap(iconLoader->loadIcon("5floppy_unmount.xpm"));
  button->setFixedSize(button->sizeHint());
  grid->addWidget(button, 4,0);  
  connect(button, SIGNAL(clicked()), this, SLOT(floppy2()));

  edit2 = new QLineEdit(this);
  edit2->setText("/dev/fd1");
  grid->addWidget(edit2,4,2);

  l = new QLabel(i18n("CD-ROM drive"), this);
  l->setMinimumSize(l->sizeHint());
  l->setAlignment(AlignTop);
  l->setBackgroundColor(white);
  grid->addWidget(l, 5,1);
  
  button = new QPushButton(this);
  button->setPixmap(iconLoader->loadIcon("cdrom_unmount.xpm"));
  button->setFixedSize(button->sizeHint());
  grid->addWidget(button, 5,0);  
  connect(button, SIGNAL(clicked()), this, SLOT(cdrom()));

  edit3 = new QLineEdit(this);
  edit3->setText("/dev/cdrom");
  grid->addWidget(edit3,5,2);

  grid->setRowStretch(6,1);

  setBackgroundColor(white);
}


void DrivePage::floppy1()
{
  toggleDrive("Floppy.kdelnk", i18n("Floppy disc"), edit1->text(), "3floppy");
}


void DrivePage::floppy2()
{
  toggleDrive("Floppy_2.kdelnk", i18n("Floppy disc"), edit2->text(), "5floppy");
}


void DrivePage::cdrom()
{
  toggleDrive("CD-ROM.kdelnk", i18n("CD-ROM"), edit3->text(), "cdrom");
}


void DrivePage::toggleDrive(QString file, QString name, QString mount, QString icon)
{
  QFile kdelnk(QDir::homeDirPath()+"/Desktop/"+file);

  if (kdelnk.exists())
    kdelnk.remove();
  else {
    if (kdelnk.open(IO_WriteOnly)) {
      QTextStream text(&kdelnk);

      text << "# KDE Config File\n";
      text << "[KDE Desktop Entry]\n";
      text << "Name=" << name << "\n";
      text << "Icon=" << icon << "_mount.xpm\n";
      text << "UnmountIcon=" << icon << "_unmount.xpm\n";
      text << "ReadOnly=0\n";
      text << "FSType=Default\n";
      text << "Type=FSDevice\n";
      text << "Dev=" << mount << "\n";

      kdelnk.close();
    }
  }
  
  KFM kfm;
  kfm.refreshDesktop();
}

#include "drivepage.moc"
