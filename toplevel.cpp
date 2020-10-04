#include "toplevel.h"

#include "themepage.h"
#include "intropage.h"
#include "linkpage.h"
#include "drivepage.h"
#include "printerpage.h"
#include "kwm.h"


TopLevel::TopLevel()
  : KTopLevelWidget()
{
  setCaption(i18n("The KDE Setup Wizard"));

  wizard = new KWizard(this);
  wizard->setOkButton();

  connect(wizard, SIGNAL(okclicked()), kapp, SLOT(quit()));

  addPage(i18n("Introduction"), new IntroPage(wizard));
  addPage(i18n("Theme selection"), new ThemePage(wizard));
  addPage(i18n("Drive configuration"), new DrivePage(wizard));
  addPage(i18n("Printer integration"), new PrinterPage(wizard));
  addPage(i18n("Link creation"), new LinkPage(wizard));

  resize(690,530);
  move((kapp->desktop()->width()-width()) / 2,
       (kapp->desktop()->height()-height()) /2);

  setView(wizard);
}


void TopLevel::addPage(QString title, QWidget *page)
{
  KWizardPage *wizpage = new KWizardPage();
  wizpage->w = page;
  wizpage->title = title;
  wizpage->enabled = TRUE;
  wizard->addPage(wizpage);
}
