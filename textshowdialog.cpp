#include "textshowdialog.h"

TextShowDialog::TextShowDialog(QWidget*parent):
	QDialog(parent),
	ui(new Ui::TextShowDialog())
{

}

TextShowDialog::~TextShowDialog()
{
}

int TextShowDialog::ExecAndRet(char*)
{
	ui->textBrowser
}
