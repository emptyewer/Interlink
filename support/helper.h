#ifndef HELPER_H
#define HELPER_H
#include "support/includes.h"
#endif // HELPER_H

class Helper {
public:
  static QString get_homedirectory();
};

QString Helper::get_homedirectory() { return QDir::homePath(); }
