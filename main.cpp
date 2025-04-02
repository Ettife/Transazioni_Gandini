#include <iostream>
#include "ContoCorrente.h"
#include "GestoreFile.h"

int main() {
    ContoCorrente conto;
    GestoreFile* gestore = GestoreFile::get_istanza();

    // Caricamento transazioni da file (se esiste)
    auto transazioni = gestore->leggi_da_file("../transazioni.txt");
    for (auto t : transazioni) {
        conto.aggiungi_transazione(t);
    }

    // Aggiunta manuale di transazioni
    conto.aggiungi_transazione(new Entrata(1000.0, "Stipendio", "2025-03-20"));
    conto.aggiungi_transazione(new Uscita(150.0, "Spesa", "2025-03-21"));

    // Visualizzazione
    conto.mostra_transazioni();
    std::cout << "Saldo attuale: " << conto.calcola_saldo() << " euro" << std::endl;

    // Salvataggio su file
    gestore->salva_su_file("../transazioni.txt", conto.get_transazioni());

    return 0;
}
