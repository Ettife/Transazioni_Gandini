//
// Created by ettor on 24/03/2025.
//

#ifndef TRANSAZIONI_GANDINI_GESTOREFILE_H
#define TRANSAZIONI_GANDINI_GESTOREFILE_H

#include <vector>
#include <string>
#include "transazione.h"

class GestoreFile {
private:
    static GestoreFile* istanza;
    GestoreFile();

public:
    static GestoreFile* get_istanza();
    void salva_su_file(std::string nome_file, std::vector<Transazione*> transazioni);
    std::vector<Transazione*> leggi_da_file(std::string nome_file);
};



#endif //TRANSAZIONI_GANDINI_GESTOREFILE_H
