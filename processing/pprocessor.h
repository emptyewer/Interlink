#ifndef PPROCESSOR_H
#define PPROCESSOR_H
#include "support/includes+structs.h"

class PProcessor {
public:
  PProcessor();
  ~PProcessor();
  NameSequence parse_fasta(QString);
  QVector<Peptide *> digest(QString, int, QList<int>);
  void fragment(QVector<Peptide *> *, QList<int>, QList<FragmentType>,
                QList<FragmentType>);
  double get_fragment_mass(QString, int, FragmentType);
  double get_parent_mass(QString);

private:
  QMap<QString, double> aminoacids;
  void define_masses();
};

#endif // PPROCESSOR_H
