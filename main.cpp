#include <iostream>
#include "ContoCorrente.h"

int main() {
    ContoCorrente conto("Conto di Ettore");

    // Aggiunta manuale di transazioni
    conto.aggiungi_transazione(Transazione(1500, "Stipendio", "2025-04-01", TipoTransazione::Entrata));
    conto.aggiungi_transazione(Transazione(200, "Spesa supermercato", "2025-04-05", TipoTransazione::Uscita));
    conto.aggiungi_transazione(Transazione(60, "Cena fuori", "2025-04-07", TipoTransazione::Uscita));

    // Visualizzazione transazioni
    std::cout << "Transazioni:\n";
    conto.mostra_transazioni();

    // Calcolo del saldo
    std::cout << "\nSaldo attuale: " << conto.calcola_saldo() << "\n";

    // Ricerca per descrizione
    std::cout << "\nRicerca per 'Cena':\n";
    auto risultati = conto.cerca_per_descrizione("Cena");
    for (const auto& t : risultati) {
        std::cout << t.to_string() << "\n";
    }

    // Salvataggio su file
    std::string nome_file = "transazioni.txt";
    conto.salva_su_file(nome_file);
    std::cout << "\nTransazioni salvate su file: " << nome_file << "\n";

    // Caricamento da file in un nuovo conto
    ContoCorrente nuovo_conto("Conto Letto Da File");
    nuovo_conto.leggi_da_file(nome_file); //nome_file = transazioni.txt
    std::cout << "\nTransazioni lette da file:\n";
    nuovo_conto.mostra_transazioni();

    return 0;
}
