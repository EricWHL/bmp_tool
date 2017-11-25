#include "EC_iConvLibIF.h"
#include <QLibrary>
#include <QString>
#include <QMessageBox>

EC_iConvLibIF::EC_iConvLibIF()
{
    init();
}
void EC_iConvLibIF::init()
{
   QLibrary  iconvlib("/lib/iconv.dll");
   if(iconvlib.load()) {

   }
   else {
   }
}

