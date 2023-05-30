#include "talk/base/openssladapter.h"
#include "widgetstreamer.h"
#include <QApplication>
#include <QTextEdit>
#include <QTimer>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	QTextEdit w1;
	TestWidget w2;

	if (!talk_base::InitializeSSL(NULL) || !talk_base::InitializeSSLThread()) 
	{
		cerr << "Unable to initialize SSL" << endl;
		return -1;
	} 

	WidgetStreamer conn(&w1, &w2);

	w1.show();
	w2.show();

	return app.exec();
}


