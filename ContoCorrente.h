//
// Created by ettor on 29/03/2025.
//

#ifndef TRANSAZIONI_GANDINI_CONTOCORRENTE_H
#define TRANSAZIONI_GANDINI_CONTOCORRENTE_H

#include "Transazione.h"
#include <vector>

class ContoCorrente {
private:
    std::vector<Transazione*> lista_transazioni;

public:
    ContoCorrente() = default;
    ~ContoCorrente();

    void aggiungi_transazione(Transazione* t);
    void mostra_transazioni() const;
    double calcola_saldo() const;
    const std::vector<Transazione*>& get_transazioni() const;
};

#endif //TRANSAZIONI_GANDINI_CONTOCORRENTE_H
