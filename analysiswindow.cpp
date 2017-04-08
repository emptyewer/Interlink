#include "analysiswindow.h"
#include "ui_analysiswindow.h"

AnalysisWindow::AnalysisWindow(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::AnalysisWindow)
{
  ui->setupUi(this);
}

AnalysisWindow::~AnalysisWindow()
{
  delete ui;
}
