//
// Created by ettor on 29/03/2025.
//

#ifndef TRANSAZIONI_GANDINI_CONTOCORRENTE_H
#define TRANSAZIONI_GANDINI_CONTOCORRENTE_H

#include "Transazione.h"

class ContoCorrente {
private:
    static const int MAX_TRANSAZIONI = 100;
    Transazione* transazioni[MAX_TRANSAZIONI];
    int num_transazioni;
    double saldo;

public:
    ContoCorrente();
    ~ContoCorrente();

    void aggiungi_transazione(Transazione* t);
    double get_saldo() const;
    void mostra_transazioni() const;
};

#endif //TRANSAZIONI_GANDINI_CONTOCORRENTE_H
