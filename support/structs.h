#ifndef STRUCTS_H
#define STRUCTS_H
#include "support/includes.h"

struct NameSequence {
  QString name;
  QString sequence;
};

enum FragmentType {
  A,
  A_HYDRATED,
  A_AMIDATED,
  B,
  B_HYDRATED,
  B_AMIDATED,
  C,
  X,
  Y,
  Y_HYDRATED,
  Y_AMIDATED,
  Z
};

struct Fragment {
  QString sequence = "";
  FragmentType type;
  int charge = 0;
  double mz_ratio = 0.0;
};

struct Peptide {
  int cleavage_begin = 0;
  int cleavage_end = 0;
  QString sequence = "";
  double mass = 0.0;
  bool crosslinker = false;
  QVector<Fragment *> fragments;
};

#endif // STRUCTS_H
