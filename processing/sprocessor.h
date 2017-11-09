#ifndef SPROCESSOR_H
#define SPROCESSOR_H
#include "support/includes+structs.h"
#endif // SPROCESSOR_H

class SProcessor {
public:
  SProcessor();
  ~SProcessor();
  void parse_ms2(QString filename);
  FILE *fileIn;

private:
  QVector<QString> split(std::string s);
};
