//
// Created by ettor on 24/03/2025.
//
#include "Transazione.h"

Transazione::Transazione(double imp, const std::string& desc, const std::string& d)
        : importo(imp), descrizione(desc), data(d) {}

double Transazione::get_importo() const {
    return importo;
}

std::string Transazione::get_data() const {
    return data;
}

std::string Transazione::get_descrizione() const {
    return descrizione;
}

Entrata::Entrata(double imp, const std::string& desc, const std::string& d)
        : Transazione(imp, desc, d) {}

std::string Entrata::to_string() const {
    return "Entrata;" + std::to_string(importo) + ";" + descrizione + ";" + data;
}

Uscita::Uscita(double imp, const std::string& desc, const std::string& d)
        : Transazione(imp, desc, d) {}

std::string Uscita::to_string() const {
    return "Uscita;" + std::to_string(importo) + ";" + descrizione + ";" + data;
}
