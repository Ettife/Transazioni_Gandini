#ifndef TRANSAZIONI_GANDINI_CONTOCORRENTE_H
#define TRANSAZIONI_GANDINI_CONTOCORRENTE_H

#include "Transazione.h"
#include <list>
#include <string>

class ContoCorrente {
private:
    std::string nome;
    std::list<Transazione> lista_transazioni;

public:
    ContoCorrente(const std::string& nome_conto);

    void aggiungi_transazione(const Transazione& t);
    bool rimuovi_transazione(const std::string& descrizione);
    void modifica_transazione(const std::string& vecchia_descrizione, const Transazione& nuova);
    void mostra_transazioni() const;
    double calcola_saldo() const;
    double calcola_saldo_fino_a(const std::string& data_limite) const;

    std::list<Transazione> get_transazioni() const;
    std::list<Transazione> cerca_per_data(const std::string& data) const;
    std::list<Transazione> cerca_per_descrizione(const std::string& keyword) const;
    std::list<Transazione> filtra_per_mese_anno(int mese, int anno) const;
    void ordina_per_data();
    void ordina_per_importo();

    void salva_su_file(const std::string& nome_file) const;
    void leggi_da_file(const std::string& nome_file);
};

#endif // TRANSAZIONI_GANDINI_CONTOCORRENTE_H
