#include "analysiswindow.h"
#include "ui_analysiswindow.h"

static const char *EnumStrings[] = {"a",     "a (H)", "a (A)", "b",
                                    "b (H)", "b (A)", "c",     "x",
                                    "y",     "y (H)", "y (A)", "z"};

AnalysisWindow::AnalysisWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::AnalysisWindow) {
  ui->setupUi(this);
  colors.append(QColor(255, 252, 128, 255));
  colors.append(QColor(121, 121, 121, 255));
  colors.append(QColor(30, 248, 38, 255));
  colors.append(QColor(253, 56, 147, 255));
  colors.append(QColor(19, 150, 252, 255));
  colors.append(QColor(33, 252, 253, 255));
}

AnalysisWindow::~AnalysisWindow() { delete ui; }

void AnalysisWindow::closeEvent(QCloseEvent *event) {

  QApplication::closeAllWindows();
}

void AnalysisWindow::reset_fragments_list_table() {
  // Clear contents of the table and set the row count to zero
  ui->fragments_list_table->clear();
  ui->fragments_list_table->setRowCount(0);
}

void AnalysisWindow::add_one_cell() {
  ui->ms_peak_matches_table->setColumnCount(2);
  ui->ms_peak_matches_table->setRowCount(colors.length());
  QTableWidgetItem *item1;
  for (int i = 0; i < colors.length(); i++) {
    item1 = new QTableWidgetItem();
    item1->setBackgroundColor(colors.at(i));
    ui->ms_peak_matches_table->setItem(i, 0, item1);
    item1 = new QTableWidgetItem("Hello");
    ui->ms_peak_matches_table->setItem(i, 1, item1);
  }
  ui->ms_peak_matches_table->resizeColumnsToContents();
  ui->ms_peak_matches_table->resizeRowsToContents();
  qDebug("Set Cell");
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
