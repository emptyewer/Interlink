
#ifndef STRUCTS_H
#define STRUCTS_H
#include <QDebug>
#include <QDir>
#include <QMap>
#include <QObject>
#include <QStandardPaths>
#include <QVector>
#include <iostream>

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

struct Peak {
  double mass = 0.0;
  double intensity = 0.0;
};

struct Scan {
  int scan_number = 0;
  double retention_time = 0.0;
  double observed_mass = 0.0;
  double intensity = 0.0;
  int charge_state = 0;
  double parent_mass = 0.0;
  QVector<Peak *> peaks;
};

struct XPeak {
  Scan *scan;
  QVector<Peak *> matching_peaks;
};

extern QMap<QString, double> aminoacids;

#endif // STRUCTS_H
