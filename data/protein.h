#ifndef PROTEIN_H
#define PROTEIN_H
#include "processing/pprocessor.h"
#include "support/includes+structs.h"

class Protein {

public:
  Protein(QString);
  ~Protein();
  QString filename;
  QString get_sequence();
  void set_sequence(QString);
  QString get_name();
  QVector<Peptide *> get_peptides();
  void digest(int, QList<int>);
  void fragment_ions(QList<int>, QList<FragmentType>, QList<FragmentType>);

private:
  QVector<Peptide *> peptides;
  QString sequence;
  QString name;
  PProcessor *protein_processor;

signals:

public slots:
};

#endif // PROTEIN_H
