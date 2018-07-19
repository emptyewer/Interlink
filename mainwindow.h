#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "analysiswindow.h"
#include "data/protein.h"
#include "data/spectra.h"
#include "graphwindow.h"
#include "support/includes+structs.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

protected:
  void closeEvent(QCloseEvent *event) override;

private slots:
  void on_actionProtein_triggered();
  void on_actionUV_ms2_file_triggered();
  void on_actionUV_ms2_file_2_triggered();
  void on_protease_currentIndexChanged(const QString &arg1);
  void on_missed_cleavages_valueChanged(int arg1);
  void on_a_released();
  void on_b_released();
  void on_c_released();
  void on_x_released();
  void on_y_released();
  void on_z_released();
  void on_p1_clicked();
  void on_p12_clicked();
  void on_p123_clicked();

  void on_find_x_ms2_peaks_clicked();

  void on_find_binding_peptides_clicked();

private:
  Ui::MainWindow *ui;
  AnalysisWindow *aw;
  Protein *protein;
  void update_peptides_list_table();
  void reset_peptides_list_table();
  void set_peptides_list_table_column_names();
  void update_protein_data();
  QList<int> charges;
  QList<FragmentType> fragment_types_n;
  QList<FragmentType> fragment_types_c;
  void read_values();
  void update_protein_changes();
  void update_fragments_list_table();
  void reset_fragments_list_table();
  QString get_homedirectory();
};

#endif // MAINWINDOW_H
