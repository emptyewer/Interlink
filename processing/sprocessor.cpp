#include "sprocessor.h"
#include "boost/algorithm/string.hpp"
#include <fstream>

SProcessor::SProcessor() {}

SProcessor::~SProcessor() {}

QVector<QString> SProcessor::split(std::string s) {
  std::vector<std::string> v;
  boost::algorithm::split(v, s, boost::algorithm::is_space());
  QVector<QString> qstrings;
  for (unsigned long i = 0; i < v.size(); i++) {
    qstrings.append(QString::fromStdString(v.at(i)));
  }
  return qstrings;
}

void SProcessor::parse_ms2(QString filename) {
  QVector<Scan *> scans;
  std::ifstream input(filename.toLatin1().data());
  if (!input.good()) {
    std::cerr << "Error opening '" << filename.toStdString()
              << "'. Bailing out." << std::endl;
  }
  std::string line;
  Scan *s = new Scan;
  while (std::getline(input, line).good()) {
    if (!line.empty()) {
      if (line[0] == 'H') {
      } else if (line[0] == 'S') {
        if (s->scan_number != 0) {
          scans.push_back(s);
          s = new Scan;
        }
        QVector<QString> i = split(line);
        s->scan_number = i.at(1).toInt();
        s->observed_mass = i.at(3).toDouble();
      } else if (line[0] == 'I') {
        QVector<QString> i = split(line);
        if (i.at(1) == "RTime") {
          s->retention_time = i.at(2).toDouble();
        } else {
          s->intensity = i.at(2).toDouble();
        }
      } else if (line[0] == 'Z') {
        s->parent_mass = split(line).at(1).toDouble();
      } else if (line[0] == '0' || line[0] == '1' || line[0] == '2' ||
                 line[0] == '3' || line[0] == '4' || line[0] == '5' ||
                 line[0] == '6' || line[0] == '7' || line[0] == '8' ||
                 line[0] == '9') {
        QVector<QString> i = split(line);
        Peak *p = new Peak;
        p->mass = i.at(0).toDouble();
        p->intensity = i.at(1).toDouble();
        s->peaks.push_back(p);
      }
    }
  }
}
