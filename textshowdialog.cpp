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
	QStringList strlist = htmlStr.split("\n");
	int maxLength = INT_MIN;
	for (QString str : strlist)
	{
		int tmpLen = str.length();
		if (tmpLen > maxLength)
		{
			maxLength = tmpLen;
		}
	}
	htmlStr.replace("\n", "<br>");
	htmlStr.replace("\r", "<br>");
	QString result = "<body>" + htmlStr + "</body>";
	QFont tmpfont("ËÎÌו", 12);
	tmpfont.setStyleStrategy(QFont::StyleStrategy::PreferAntialias);
	ui->textBrowser->setHtml(result);
	ui->textBrowser->setFont(tmpfont);
	this->setMinimumWidth(maxLength * QFontMetrics(tmpfont).capHeight());
	return this->exec();
}
