#include "protein.h"

/* When any Protein instance is initialized with a filename, the sequence is
 * automatically digested with the default enzyme (Trypsin). Alternately, diget
 * can also be called as a public method if a different enzyme is chosen.*/

Protein::Protein(QString filename) {
  this->filename = filename;
  // All protein sequence processing is perfomed using PProcessor
  protein_processor = new PProcessor();
  // Parse and obtain protein sequence and name from fasta files
  NameSequence ns = protein_processor->parse_fasta(filename);
  name = ns.name;
  sequence = ns.sequence;
}

// Only digests Trypsin. #### Future To Do: Need to implement other preteases
void Protein::digest(int missed, QList<int> charges) {
  peptides = protein_processor->digest(sequence, missed, charges);
}

void Protein::fragment_ions(QList<int> charges, QList<FragmentType> n_types,
                            QList<FragmentType> c_types) {
  protein_processor->fragment(&peptides, charges, n_types, c_types);
}

QString Protein::get_sequence() { return sequence; }
void Protein::set_sequence(QString seq) { sequence = seq; }

QVector<Peptide *> Protein::get_peptides() { return peptides; }

QString Protein::get_name() { return name; }
