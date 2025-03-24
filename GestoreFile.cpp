//
// Created by ettor on 24/03/2025.
//

#include "GestoreFile.h"
#include <fstream>
#include <sstream>

GestoreFile* GestoreFile::istanza = nullptr;

GestoreFile* GestoreFile::get_istanza() {
    if (istanza == nullptr) {
        istanza = new GestoreFile();
    }
    return istanza;
}

void GestoreFile::salva_su_file(const std::string& nome_file, const std::vector<Transazione*>& transazioni) const {
    std::ofstream file(nome_file);
    for (const auto& t : transazioni) {
        file << t->to_string() << std::endl;
    }
    file.close();
}

std::vector<Transazione*> GestoreFile::leggi_da_file(const std::string& nome_file) const {
    std::vector<Transazione*> transazioni;
    std::ifstream file(nome_file);
    std::string riga;
    while (std::getline(file, riga)) { //getline(file, riga) legge una riga intera dal file e la memorizza in "riga"
        std::stringstream ss(riga);
        std::string tipo, importo_str, descrizione, data;
        std::getline(ss, tipo, ';');	//legge dallo stringstream "ss" fino all'occorrenza del primo ';'
        std::getline(ss, importo_str, ';');
        std::getline(ss, descrizione, ';');
        std::getline(ss, data, ';');

        double imp = std::stod(importo_str);	//string to double

        if (tipo == "Entrata") {
            transazioni.push_back(new Entrata(imp, descrizione, data));
        } else if (tipo == "Uscita") {
            transazioni.push_back(new Uscita(imp, descrizione, data));
        }
    }
    file.close();
    return transazioni;
}
