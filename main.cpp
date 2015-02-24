#include <QApplication>
#include <QTextCodec>
#include "logindlg.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);

   //QTextCodec::setCodecForTr(QTextCodec::codecForLocale()); //设置编码
   //QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

   MainWindow w;
   LoginDlg dlg;

//   if(dlg.exec() == QDialog::Accepted)
//   {
       w.show();
       return a.exec();
//   }
//   else return 0;
}
