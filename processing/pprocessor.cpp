#include "pprocessor.h"
#include <fstream>

PProcessor::PProcessor() { define_masses(); }

PProcessor::~PProcessor() {}

NameSequence PProcessor::parse_fasta(QString filename) {
  qDebug() << filename;
  std::ifstream input(filename.toLatin1().data());
  if (!input.good()) {
    std::cerr << "Error opening '" << filename.toStdString()
              << "'. Bailing out." << std::endl;
  }
  std::string line, name, content;
  while (std::getline(input, line).good()) {
    if (line.empty() || line[0] == '>') { // Identifier marker
      if (!name.empty()) { // Print out what we read from the last entry
        std::cout << name << " : " << content << std::endl;
        name.clear();
      }
      if (!line.empty()) {
        name = line.substr(1);
      }
      content.clear();
    } else if (!name.empty()) {
      if (line.find(' ') !=
          std::string::npos) { // Invalid sequence--no spaces allowed
        name.clear();
        content.clear();
      } else {
        content += line;
      }
    }
  }
  NameSequence ns;
  if (!name.empty()) { // Print out what we read from the last entry
    ns.name = QString::fromStdString(name);
    ns.sequence = QString::fromStdString(content);
  }
  return ns;
}

QVector<Peptide *> PProcessor::digest(QString sequence, int missed_cleavages,
                                      QList<int> charges) {
  int quit = 0;
  int start = 0;
  QList<int> indicies;
  indicies << 0;
  QRegExp rx("[K|R]");
  QVector<Peptide *> peps;
  while (quit != -1) {
    quit = sequence.indexOf(rx, start);
    if (quit != -1) {
      start = quit + 1;
      if (sequence.at(quit + 1) != 'P') {
        //        qDebug() << sequence.at(quit) << quit + 1;
        indicies << quit + 1;
      }
    }
  }
  int len = indicies.length();
  qDebug() << indicies;
  for (int j = 1; j <= 1 + missed_cleavages; j++) {
    for (int i = 0; i < len - j; i++) {
      Peptide *p = new Peptide;
      p->cleavage_begin = indicies.at(i);
      p->cleavage_end = indicies.at(i + j);
      p->sequence =
          sequence.mid(indicies.at(i), indicies.at(i + j) - indicies.at(i));
      p->mass = get_parent_mass(p->sequence);
      if (p->sequence.indexOf('X') != -1 or p->sequence.indexOf('B') != -1) {
        p->crosslinker = true;
        qDebug() << "###" << p->sequence;
      }
      peps.append(p);
    }
  }
  return peps;
}

void PProcessor::fragment(QVector<Peptide *> *peptides, QList<int> charges,
                          QList<FragmentType> n_types,
                          QList<FragmentType> c_types) {
  int number_of_peptides = peptides->length();
  Fragment *f = new Fragment;
  // Iterate through all the peptides in the list
  for (int i = 0; i < number_of_peptides; i++) {
    QString seq = peptides->at(i)->sequence;
    int seq_length = seq.length();
    //    qDebug() << "######" << seq << "######";
    // For each selected charge state iterate through
    foreach (int charge, charges) {
      // Sequentially fragment peptides into N-ter fragment and C-ter fragement
      for (int mid = 1; mid < seq_length; mid++) {
        QString n_seq = seq.left(mid);
        QString c_seq = seq.right(seq_length - mid);
        // For each fragment type calculate mass N-ter
        foreach (FragmentType n_type, n_types) {
          f->sequence = n_seq;
          f->type = n_type;
          f->mz_ratio = get_fragment_mass(n_seq, charge, n_type);
          f->charge = charge;
          peptides->at(i)->fragments.append(f);
          //          qDebug() << "Seq: " << f->sequence << "m/z: " <<
          //          f->mz_ratio
          //                   << "Type: " << n_type << "Charge: " << f->charge;
        }
        // For each fragment type calculate mass C-ter
        foreach (FragmentType c_type, c_types) {
          f->sequence = c_seq;
          f->type = c_type;
          f->mz_ratio = get_fragment_mass(c_seq, charge, c_type);
          f->charge = charge;
          peptides->at(i)->fragments.append(f);
          //          qDebug() << "Seq: " << f->sequence << "m/z: " <<
          //          f->mz_ratio
          //                   << "Type: " << c_type << "Charge: " << f->charge;
        }
      }
    }
  }
}

void PProcessor::define_masses() {
  // Defining the monoisotopic masses of aminoacids
  aminoacids["A"] = 71.037117;
  aminoacids["R"] = 156.1011047;
  aminoacids["N"] = 114.0429306;
  aminoacids["D"] = 115.0269394;
  aminoacids["J"] = 114.534935;
  aminoacids["C"] = 103.0091858;
  aminoacids["E"] = 129.0425873;
  aminoacids["G"] = 57.0214653;
  aminoacids["H"] = 137.0589142;
  aminoacids["I"] = 113.0840607;
  aminoacids["L"] = 113.0840607;
  aminoacids["K"] = 128.0949554;
  aminoacids["M"] = 131.0404816;
  aminoacids["F"] = 147.0684204;
  aminoacids["P"] = 97.05276489;
  aminoacids["S"] = 87.0320282;
  aminoacids["T"] = 101.0476761;
  aminoacids["U"] = 150.95364;
  aminoacids["W"] = 186.0793152;
  aminoacids["Y"] = 163.063324;
  aminoacids["V"] = 99.06841278;
  aminoacids["B"] = 251.0946;
  aminoacids["X"] = 453.18009;
  aminoacids["Q"] = 128.0585785;
  aminoacids["Z"] = 128.5505829;
}

double PProcessor::get_fragment_mass(QString sequence, int charge,
                                     FragmentType type) {
  QList<QString> sequence_chars;
  sequence_chars.push_back(sequence);
  double mass = 1.0078 * charge; // Initialize with charge state of the fragment
  foreach (QString s, sequence_chars[0]) { mass = mass + aminoacids[s]; }
  if (type == A) {
    mass = mass - 27.9949;
  }
  if (type == A_HYDRATED || type == B_HYDRATED || type == Y_HYDRATED) {
    mass = mass - 18.0106;
  }
  if (type == A_AMIDATED || type == B_AMIDATED || type == Y_AMIDATED) {
    mass = mass - 17.0266;
  }
  if (type == C) {
    mass = mass + 1.0078 + 29.02134;
  }
  if (type == X) {
    mass = mass + 17.0027 + 27.9949 - 1.0078;
  }
  if (type == Y) {
    mass = mass + 17.0027 + 1.0078;
  }
  if (type == Z) {
    mass = mass + 17.0027 - 15.01464;
  }
  return mass / charge;
}

double PProcessor::get_parent_mass(QString sequence) {
  QList<QString> sequence_chars;
  sequence_chars.push_back(sequence);
  double mass = 0.0;
  foreach (QString s, sequence_chars[0]) { mass = mass + aminoacids[s]; }
  return mass;
}
