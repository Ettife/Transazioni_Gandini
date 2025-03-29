//
// Created by ettor on 29/03/2025.
//
#include "ContoCorrente.h"
#include <iostream>

ContoCorrente::~ContoCorrente() {
    for (auto t : lista_transazioni) {
        delete t;
    }
}

void ContoCorrente::aggiungi_transazione(Transazione* t) {
    lista_transazioni.push_back(t);
}

void ContoCorrente::mostra_transazioni() const {
    for (const auto& t : lista_transazioni) {
        std::cout << t->to_string() << std::endl;
    }
}

double ContoCorrente::calcola_saldo() const {
    double saldo = 0;
    for (const auto& t : lista_transazioni) {
        if (dynamic_cast<const Entrata*>(t)) {
            saldo += t->get_importo();
        } else {
            saldo -= t->get_importo();
        }
    }
    return saldo;
}

const std::vector<Transazione*>& ContoCorrente::get_transazioni() const {
    return lista_transazioni;
}
