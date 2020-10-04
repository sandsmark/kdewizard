#include "intropage.h"

#include <kapp.h>
#include <kurl.h>
#include <qfile.h>
#include <qtextstream.h>


IntroPage::IntroPage(QWidget *parent, const char *name)
  : KHTMLView(parent,name)
{
  getKHTMLWidget()->setDefaultFontBase(3);	//melter: Fixes bad font sizes
  getKHTMLWidget()->setGranularity(10000);
	
  begin(QString("file:")+kapp->kde_datadir()+"/kdewizard/html/");

  parse();

  QFile file(kapp->kde_datadir()+"/kdewizard/html/intro.html");
 
  if (file.open(IO_ReadOnly))
  {
    QTextStream stream(&file);

    while (!stream.eof())
      write(stream.readLine());

    file.close();
  }

  end();
  show();
}
