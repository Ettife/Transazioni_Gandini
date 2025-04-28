#include "ContoCorrente.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

ContoCorrente::ContoCorrente(const std::string& nome_conto) : nome(nome_conto) {
    if (nome_conto.empty()) {
        throw std::invalid_argument("Il nome del conto non può essere vuoto.");
    }
}

void ContoCorrente::aggiungi_transazione(const Transazione& t) {
    lista_transazioni.push_back(t);
}

bool ContoCorrente::rimuovi_transazione(const std::string& descrizione) {
    auto it = std::find_if(lista_transazioni.begin(), lista_transazioni.end(),
                           [&descrizione](const Transazione& t) {
                               return t.get_descrizione() == descrizione;
                           });
    if (it != lista_transazioni.end()) {
        lista_transazioni.erase(it);
        return true;
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
    throw std::runtime_error("Transazione da modificare non trovata.");
}

void ContoCorrente::mostra_transazioni() const {
    if (lista_transazioni.empty()) {
        std::cout << "Nessuna transazione presente.\n";
        return;
    }
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

double ContoCorrente::calcola_saldo_fino_a(const std::string& data_limite) const {
    double saldo = 0;
    for (const auto& t : lista_transazioni) {
        if (t.get_data() <= data_limite) {
            saldo += (t.get_tipo() == TipoTransazione::Entrata) ? t.get_importo() : -t.get_importo();
        }
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

std::list<Transazione> ContoCorrente::filtra_per_mese_anno(int mese, int anno) const {
    std::list<Transazione> risultati;
    for (const auto& t : lista_transazioni) {
        int anno_t, mese_t, giorno_t;
        sscanf(t.get_data().c_str(), "%d-%d-%d", &anno_t, &mese_t, &giorno_t);
        if (anno_t == anno && mese_t == mese) {
            risultati.push_back(t);
        }
    }
    return risultati;
}

void ContoCorrente::ordina_per_data() {
    lista_transazioni.sort([](const Transazione& a, const Transazione& b) {
        return a.get_data() < b.get_data();
    });
}

void ContoCorrente::ordina_per_importo() {
    lista_transazioni.sort([](const Transazione& a, const Transazione& b) {
        return a.get_importo() < b.get_importo();
    });
}

void ContoCorrente::salva_su_file(const std::string& nome_file) const {
    std::ofstream file(nome_file);
    if (!file) {
        throw std::runtime_error("Impossibile aprire il file per la scrittura.");
    }
    for (const auto& t : lista_transazioni) {
        file << t.to_string() << std::endl;
    }
}

void ContoCorrente::leggi_da_file(const std::string& nome_file) {
    std::ifstream file(nome_file);
    if (!file) {
        throw std::runtime_error("Impossibile aprire il file per la lettura.");
    }

    std::string riga;
    while (std::getline(file, riga)) {
        std::stringstream ss(riga);
        std::string tipo_str, imp_str, desc, data;

        if (!std::getline(ss, tipo_str, ';') ||
            !std::getline(ss, imp_str, ';') ||
            !std::getline(ss, desc, ';') ||
            !std::getline(ss, data, ';')) {
            continue; // Salta righe malformate
        }

        try {
            double imp = std::stod(imp_str);
            TipoTransazione tipo = (tipo_str == "Entrata") ? TipoTransazione::Entrata : TipoTransazione::Uscita;
            Transazione t(imp, desc, data, tipo);
            lista_transazioni.push_back(t);
        } catch (const std::exception& e) {
            std::cerr << "Errore nella lettura di una transazione: " << e.what() << std::endl;
            continue;
        }
    }
}
