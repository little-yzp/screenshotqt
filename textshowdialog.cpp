#include "textshowdialog.h"

TextShowDialog::TextShowDialog(QWidget*parent):
	QDialog(parent),
	ui(new Ui::TextShowDialog())
{
	ui->setupUi(this);
}

TextShowDialog::~TextShowDialog()
{
}

int TextShowDialog::ExecAndRet(char*text)
{
	QString htmlStr(text);
	htmlStr.replace("\n", "<br>");
	htmlStr.replace("\r", "<br>");
	QString result = "<body>" + htmlStr + "</body>";
	QFont font("ËÎÌו", 12);
	font.setStyleStrategy(QFont::StyleStrategy::PreferAntialias);
	ui->textBrowser->setHtml(result);
	ui->textBrowser->setFont(font);
	return this->exec();
}
