#include "ContoCorrente.h"
#include <iostream>
#include <fstream>
#include <sstream>

ContoCorrente::ContoCorrente(const std::string& nome_conto) : nome(nome_conto) {}

void ContoCorrente::aggiungi_transazione(const Transazione& t) {
    lista_transazioni.push_back(t);
}

bool ContoCorrente::rimuovi_transazione(const std::string& descrizione) {
    for (auto it = lista_transazioni.begin(); it != lista_transazioni.end(); ++it) {
        if (it->get_descrizione() == descrizione) {
            lista_transazioni.erase(it);
            return true;
        }
    }
    return false;
}

void ContoCorrente::modifica_transazione(const std::string& vecchia_descrizione, const Transazione& nuova) {
    for (auto& t : lista_transazioni) {
        if (t.get_descrizione() == vecchia_descrizione) {
            t = nuova;
            return;
        }
    }
}

void ContoCorrente::mostra_transazioni() const {
    for (const auto& t : lista_transazioni) {
        std::cout << t.to_string() << std::endl;
    }
}

double ContoCorrente::calcola_saldo() const {
    double saldo = 0;
    for (const auto& t : lista_transazioni) {
        saldo += (t.get_tipo() == TipoTransazione::Entrata) ? t.get_importo() : -t.get_importo();
    }
    return saldo;
}

std::list<Transazione> ContoCorrente::get_transazioni() const {
    return lista_transazioni;
}

std::list<Transazione> ContoCorrente::cerca_per_data(const std::string& data) const {
    std::list<Transazione> risultati;
    for (const auto& t : lista_transazioni) {
        if (t.get_data() == data) {
            risultati.push_back(t);
        }
    }
    return risultati;
}

std::list<Transazione> ContoCorrente::cerca_per_descrizione(const std::string& keyword) const {
    std::list<Transazione> risultati;
    for (const auto& t : lista_transazioni) {
        if (t.get_descrizione().find(keyword) != std::string::npos) {
            risultati.push_back(t);
        }
    }
    return risultati;
}

void ContoCorrente::salva_su_file(const std::string& nome_file) const {
    std::ofstream file(nome_file);
    for (const auto& t : lista_transazioni) {
        file << t.to_string() << std::endl;
    }
}

void ContoCorrente::leggi_da_file(const std::string& nome_file) {
    std::ifstream file(nome_file);
    std::string riga;
    while (std::getline(file, riga)) {
        std::stringstream ss(riga);
        std::string tipo_str, imp_str, desc, data;
        std::getline(ss, tipo_str, ';');
        std::getline(ss, imp_str, ';');
        std::getline(ss, desc, ';');
        std::getline(ss, data, ';');

        double imp = std::stod(imp_str);
        TipoTransazione tipo = (tipo_str == "Entrata") ? TipoTransazione::Entrata : TipoTransazione::Uscita;
        Transazione t(imp, desc, data, tipo);
        lista_transazioni.push_back(t);
    }
}
