#include "tablecell.h"
#include "ui_tablecell.h"

tablecell::tablecell(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::tablecell)
{
  ui->setupUi(this);
}

tablecell::~tablecell()
{
  delete ui;
}
