//
// Created by ettor on 29/03/2025.
//
#include "ContoCorrente.h"
#include <iostream>

ContoCorrente::ContoCorrente() : num_transazioni(0), saldo(0) {
    for (int i = 0; i < MAX_TRANSAZIONI; ++i) {
        transazioni[i] = nullptr;
    }
}

ContoCorrente::~ContoCorrente() {
    for (int i = 0; i < num_transazioni; ++i) {
        delete transazioni[i];
    }
}

void ContoCorrente::aggiungi_transazione(Transazione* t) {
    if (num_transazioni < MAX_TRANSAZIONI) {
        transazioni[num_transazioni++] = t;
        saldo += t->get_importo();  // Aggiorna il saldo direttamente
    } else {
        std::cerr << "Errore: Numero massimo di transazioni raggiunto." << std::endl;
    }
}

double ContoCorrente::get_saldo() const {
    return saldo;
}

void ContoCorrente::mostra_transazioni() const {
    for (int i = 0; i < num_transazioni; ++i) {
        if (transazioni[i] != nullptr) {
            std::cout << transazioni[i]->to_string() << std::endl;
        }
    }
}
