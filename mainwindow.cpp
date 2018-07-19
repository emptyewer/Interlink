#include "mainwindow.h"
#include "processing/sprocessor.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  aw = new AnalysisWindow();
  aw->show();
  // REMOVE NEXT LINES
  //  protein = new Protein(
  //      "/Users/Venky/Work/Softwares/Interlink/test_files/HDH_wt++.fasta");
  //  update_protein_changes();
  //  SProcessor *s = new SProcessor();
  //  //  s->parse_ms2("/Users/Venky/Work/Softwares/Interlink/test_files/"
  //  //               "CM_151128_Elite_32_N94HDH_gel_band_UV_CID.ms2");
  //  aw->add_one_cell();
}

MainWindow::~MainWindow() {
  delete aw;
  delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
  if (aw->isVisible()) {
    aw->close();
  }
  QApplication::closeAllWindows();
}

void MainWindow::on_actionProtein_triggered() {
  protein = new Protein(QFileDialog::getOpenFileName(
      this, tr("Protein Sequence"), get_homedirectory(),
      tr("FASTA (*.fasta *.fa)")));
  update_protein_changes();
}

void MainWindow::on_actionUV_ms2_file_triggered() {}

void MainWindow::on_actionUV_ms2_file_2_triggered() {}

void MainWindow::on_protease_currentIndexChanged(const QString &arg1) {}

void MainWindow::on_missed_cleavages_valueChanged(int arg1) {
  update_protein_changes();
}

void MainWindow::on_a_released() { update_protein_changes(); }
void MainWindow::on_b_released() { update_protein_changes(); }
void MainWindow::on_c_released() { update_protein_changes(); }
void MainWindow::on_x_released() { update_protein_changes(); }
void MainWindow::on_y_released() { update_protein_changes(); }
void MainWindow::on_z_released() { update_protein_changes(); }
void MainWindow::on_p1_clicked() { update_protein_changes(); }
void MainWindow::on_p12_clicked() { update_protein_changes(); }
void MainWindow::on_p123_clicked() { update_protein_changes(); }

// void MainWindow::on_protein_sequence_textChanged() {
//  protein->set_sequence(ui->protein_sequence->toPlainText());
//  update_protein_changes();
//}

void MainWindow::update_protein_changes() {
  read_values();
  protein->digest(ui->missed_cleavages->value(), charges);
  update_protein_data();
  update_peptides_list_table();
  protein->fragment_ions(charges, fragment_types_n, fragment_types_c);
  update_fragments_list_table();
}

void MainWindow::update_fragments_list_table() {
  QVector<Peptide *> peptides = protein->get_peptides();
  aw->reset_fragments_list_table();
  int len = peptides.length();
  for (int i = 0; i < len; i++) {
    Peptide *p = peptides.at(i);
    if (p->crosslinker) {
      aw->update_fragments_list_table(p->fragments);
    }
  }
}

void MainWindow::update_peptides_list_table() {
  QVector<Peptide *> peptides = protein->get_peptides();
  QTableWidgetItem *item1;
  QTableWidgetItem *item2;

  reset_peptides_list_table();
  int len = peptides.length();
  int count = 0;
  for (int i = 0; i < len; i++) {
    Peptide *p = peptides.at(i);
    ui->peptides_list_table->insertRow(count);
    item1 = new QTableWidgetItem(p->sequence);
    item2 = new QTableWidgetItem(QString::number(p->mass, 'f', 6));
    if (p->crosslinker) {
      item1->setForeground(Qt::red);
      item2->setForeground(Qt::red);
    }
    ui->peptides_list_table->setItem(count, 0, item1);
    ui->peptides_list_table->setItem(count, 1, item2);
    count += 1;
  }
  set_peptides_list_table_column_names();
}

void MainWindow::set_peptides_list_table_column_names() {
  QStringList labels;
  labels << "Sequence"
         << "Mass";
  ui->peptides_list_table->setHorizontalHeaderLabels(labels);
  ui->peptides_list_table->resizeRowsToContents();
  ui->peptides_list_table->resizeColumnsToContents();
}

void MainWindow::reset_peptides_list_table() {
  // Clear contents of the table and set the row count to zero
  ui->peptides_list_table->clear();
  ui->peptides_list_table->setRowCount(0);
}

void MainWindow::update_protein_data() {
  QFontMetrics metrics(ui->sequence_name->font());
  QString elidedText =
      metrics.elidedText("Name: " + protein->get_name(), Qt::ElideRight, 300);
  QString html_text = protein->get_sequence().replace(
      QRegExp("X"), "<strong><font color=\"red\">X</font></strong>");
  html_text = html_text.replace(
      QRegExp("B"), "<strong><font color=\"red\">B</font></strong>");
  QString sequence_text = "<html><body>" + html_text + "</body></html>";
  //  ui->protein_sequence->setText(protein->get_sequence());
  //  qDebug() << sequence_text;
  ui->protein_sequence->setHtml(sequence_text);
  ui->sequence_name->setText(elidedText);
}

void MainWindow::read_values() {
  charges.clear();
  fragment_types_n.clear();
  fragment_types_c.clear();
  charges.append(1);
  if (ui->p12->isChecked()) {
    charges.append(2);
  }
  if (ui->p123->isChecked()) {
    charges.append(3);
  }
  if (ui->a->isChecked()) {
    if (fragment_types_n.contains(A) == false) {
      fragment_types_n.append(A);
    }
    //    if (fragment_types_n.contains(A_HYDRATED) == false) {
    //      fragment_types_n.append(A_HYDRATED);
    //    }
    //    if (fragment_types_n.contains(A_AMIDATED) == false) {
    //      fragment_types_n.append(A_AMIDATED);
    //    }
  }
  if (ui->b->isChecked()) {
    if (fragment_types_n.contains(B) == false) {
      fragment_types_n.append(B);
    }
    //    if (fragment_types_n.contains(B_HYDRATED) == false) {
    //      fragment_types_n.append(B_HYDRATED);
    //    }
    //    if (fragment_types_n.contains(B_AMIDATED) == false) {
    //      fragment_types_n.append(B_AMIDATED);
    //    }
  }
  if (ui->c->isChecked()) {
    if (fragment_types_n.contains(C) == false) {
      fragment_types_n.append(C);
    }
  }
  if (ui->x->isChecked()) {
    if (fragment_types_c.contains(X) == false) {
      fragment_types_c.append(X);
    }
  }
  if (ui->y->isChecked()) {
    if (fragment_types_c.contains(Y) == false) {
      fragment_types_c.append(Y);
    }
    //    if (fragment_types_c.contains(Y_HYDRATED) == false) {
    //      fragment_types_c.append(Y_HYDRATED);
    //    }
    //    if (fragment_types_c.contains(Y_AMIDATED) == false) {
    //      fragment_types_c.append(Y_AMIDATED);
    //    }
  }
  if (ui->z->isChecked()) {
    if (fragment_types_c.contains(Z) == false) {
      fragment_types_c.append(Z);
    }
  }
  qDebug() << fragment_types_n << fragment_types_c;
}

QString MainWindow::get_homedirectory() { return QDir::homePath(); }

void MainWindow::on_find_x_ms2_peaks_clicked() {}

void MainWindow::on_find_binding_peptides_clicked() {}
