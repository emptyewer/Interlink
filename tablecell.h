#ifndef TABLECELL_H
#define TABLECELL_H

#include <QWidget>

namespace Ui {
  class tablecell;
}

class tablecell : public QWidget
{
  Q_OBJECT

public:
  explicit tablecell(QWidget *parent = 0);
  ~tablecell();

private:
  Ui::tablecell *ui;
};

#endif // TABLECELL_H
