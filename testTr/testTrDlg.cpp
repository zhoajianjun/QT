#include <QMessageBox>
#include "testTrDlg.h"
#include <QApplication>

testTrDlg::testTrDlg(QWidget * parent):QDialog(parent)
{
	setupUi(this);
	
	connect(engBtn,  SIGNAL(clicked()), this, SLOT(english()));
	connect(chsBtn,  SIGNAL(clicked()), this, SLOT(chinese()));
	connect(loveBtn, SIGNAL(clicked()), this, SLOT(ILoveMyFamily()));
	connect(testBtn, SIGNAL(clicked()), this, SLOT(testTr()));

	translator = new QTranslator(this);
	translator->load("Language_Chn");
	qApp->installTranslator(translator);

	retranslateUi(this);
}

testTrDlg::~testTrDlg()
{

}

void testTrDlg::english()
{
	translator->load("Language_Eng");
	retranslateUi(this);
}

void testTrDlg::chinese()
{
	translator->load("Language_Chn");
	retranslateUi(this);
}

void testTrDlg::ILoveMyFamily()
{
	QMessageBox::information(this, loveBtn->text(), loveBtn->text());
}

void testTrDlg::testTr()
{
	QMessageBox::information(this, testBtn->text(), testBtn->text());
}
