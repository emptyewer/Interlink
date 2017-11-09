#ifndef ANALYSISWINDOW_H
#define ANALYSISWINDOW_H

#include "support/includes+structs.h"
#include <QWidget>

namespace Ui {
class AnalysisWindow;
}

class AnalysisWindow : public QWidget {
  Q_OBJECT

public:
  explicit AnalysisWindow(QWidget *parent = 0);
  ~AnalysisWindow();

  void reset_fragments_list_table();

  void update_fragments_list_table(QVector<Fragment *> fragments);

private:
  Ui::AnalysisWindow *ui;
  void format_fragments_list_table();
};

#endif // ANALYSISWINDOW_H
