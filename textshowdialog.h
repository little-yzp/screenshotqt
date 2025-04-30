#pragma once

#include <QDialog>
#include "ui_textshowdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
	class TextShowDialog;
}
QT_END_NAMESPACE

class TextShowDialog :public QDialog
{
	Q_OBJECT
public:
	TextShowDialog(QWidget* parent);
	~TextShowDialog();
	int ExecAndRet(char*);
private:
	Ui::TextShowDialog* ui;

};
