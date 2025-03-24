//
// Created by ettor on 24/03/2025.
//

#ifndef TRANSAZIONI_GANDINI_GESTOREFILE_H
#define TRANSAZIONI_GANDINI_GESTOREFILE_H

#include <vector>
#include <string>
#include "Transazione.h"

class GestoreFile {
private:
    static GestoreFile* istanza;
    GestoreFile();

public:
    static GestoreFile* get_istanza();
    void salva_su_file(const std::string& nome_file, const std::vector<Transazione*>& transazioni) const;
    std::vector<Transazione*> leggi_da_file(const std::string& nome_file) const;
};



#endif //TRANSAZIONI_GANDINI_GESTOREFILE_H
