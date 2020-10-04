#include "printerpage.h"

#include <kapp.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qdir.h>
#include <qpushbutton.h>
#include <kiconloader.h>
#include <kfm.h>


PrinterPage::PrinterPage(QWidget *parent, const char *name)
  : QWidget(parent,name)
{
  KIconLoader *iconLoader = kapp->getIconLoader();

  QGridLayout *grid = new QGridLayout(this, 4,3, 8);    

  QPixmap pixmap(kapp->kde_datadir()+"/kdewizard/html/wizard_small.gif");
  QLabel *l = new QLabel(this);
  l->setPixmap(pixmap);
  l->setFixedSize(pixmap.size());
  grid->addMultiCellWidget(l, 0,1 ,1,2, AlignRight);

  l = new QLabel(i18n("You will propably have a printer, don't you? "
  	"Then why not create a little icon for the printer that "
	"allows you to drag & drop files to the printer, and to "
	"invoke the printer queue utility!"), this);  
  l->setAlignment(WordBreak);
  l->setBackgroundColor(white);
  grid->addMultiCellWidget(l, 0,0, 0,1);
  grid->setRowStretch(0,1);

  l = new QLabel(i18n("Printer icon"), this);
  l->setMinimumSize(l->sizeHint());
  l->setAlignment(AlignTop);
  l->setBackgroundColor(white);
  grid->addWidget(l, 2,1);
  
  QButton *button = new QPushButton(this);
  button->setPixmap(iconLoader->loadIcon("printer.xpm"));
  button->setFixedSize(button->sizeHint());
  grid->addWidget(button, 2,0);  
  connect(button, SIGNAL(clicked()), this, SLOT(togglePrinter()));

  grid->setRowStretch(3,1);

  setBackgroundColor(white);
}


void PrinterPage::togglePrinter()
{
  QString destname = QDir::homeDirPath()+"/Desktop/Printer.kdelnk";
  QFile dest(destname);

  if (dest.exists())
    dest.remove();
  else {
    QString srcname = kapp->kde_datadir()+"/kdewizard/printer.kdelnk";
    QString command = "cp "+srcname+" "+destname;
    system(command.data());
  }
    
 KFM kfm;
 kfm.refreshDesktop();
}
