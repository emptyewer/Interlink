#include "analysiswindow.h"
#include "ui_analysiswindow.h"

static const char *EnumStrings[] = {"a",     "a (H)", "a (A)", "b",
                                    "b (H)", "b (A)", "c",     "x",
                                    "y",     "y (H)", "y (A)", "z"};

AnalysisWindow::AnalysisWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::AnalysisWindow) {
  ui->setupUi(this);
}

AnalysisWindow::~AnalysisWindow() { delete ui; }

void AnalysisWindow::reset_fragments_list_table() {
  // Clear contents of the table and set the row count to zero
  ui->fragments_list_table->clear();
  ui->fragments_list_table->setRowCount(0);
}

void AnalysisWindow::update_fragments_list_table(
    QVector<Fragment *> fragments) {
  QTableWidgetItem *item1;
  QTableWidgetItem *item2;
  QTableWidgetItem *item3;
  QTableWidgetItem *item4;
  int count = 0;
  int len = fragments.length();
  for (int i = 0; i < len; i++) {
    Fragment *f = fragments.at(i);
    ui->fragments_list_table->insertRow(count);
    item1 = new QTableWidgetItem(f->sequence);
    item2 = new QTableWidgetItem(EnumStrings[f->type]);
    item3 = new QTableWidgetItem("+" + QString::number(f->charge));
    item4 = new QTableWidgetItem(QString::number(f->mz_ratio, 'f', 6));
    ui->fragments_list_table->setItem(count, 0, item1);
    ui->fragments_list_table->setItem(count, 1, item2);
    ui->fragments_list_table->setItem(count, 2, item3);
    ui->fragments_list_table->setItem(count, 3, item4);
    count += 1;
  }
  format_fragments_list_table();
}

void AnalysisWindow::format_fragments_list_table() {
  QStringList labels;
  labels << "Sequence"
         << "Type"
         << "Charge"
         << "m/z";
  ui->fragments_list_table->setHorizontalHeaderLabels(labels);
  ui->fragments_list_table->resizeRowsToContents();
  ui->fragments_list_table->resizeColumnsToContents();
}
