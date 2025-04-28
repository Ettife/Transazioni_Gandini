#include <iostream>
#include "ContoCorrente.h"

void stampa_menu() {
    std::cout << "\n--- MENU ---\n"
              << "1. Aggiungi transazione\n"
              << "2. Rimuovi transazione\n"
              << "3. Modifica transazione\n"
              << "4. Mostra tutte le transazioni\n"
              << "5. Calcola saldo\n"
              << "6. Cerca transazioni per descrizione\n"
              << "7. Cerca transazioni per data\n"
              << "8. Ordina transazioni per data\n"
              << "9. Ordina transazioni per importo\n"
              << "10. Salva su file\n"
              << "11. Carica da file\n"
              << "0. Esci\n";
}

int main() {
    try {
        ContoCorrente conto("Conto di Ettore");
        int scelta = -1;

        while (scelta != 0) {
            stampa_menu();
            std::cout << "Seleziona un'opzione: ";
            std::cin >> scelta;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cerr << "Input non valido.\n";
                continue;
            }

            switch (scelta) {
                case 1: {
                    double importo;
                    std::string descrizione, data;
                    int tipo_int;

                    std::cout << "Importo: ";
                    std::cin >> importo;
                    std::cin.ignore();
                    std::cout << "Descrizione: ";
                    std::getline(std::cin, descrizione);
                    std::cout << "Data (YYYY-MM-DD): ";
                    std::getline(std::cin, data);
                    std::cout << "Tipo (0=Entrata, 1=Uscita): ";
                    std::cin >> tipo_int;

                    if (tipo_int != 0 && tipo_int != 1) {
                        std::cerr << "Tipo transazione non valido.\n";
                        break;
                    }

                    TipoTransazione tipo = (tipo_int == 0) ? TipoTransazione::Entrata : TipoTransazione::Uscita;
                    conto.aggiungi_transazione(Transazione(importo, descrizione, data, tipo));
                    break;
                }

                case 2: {
                    std::cin.ignore();
                    std::string descrizione;
                    std::cout << "Inserisci descrizione della transazione da rimuovere: ";
                    std::getline(std::cin, descrizione);
                    if (conto.rimuovi_transazione(descrizione))
                        std::cout << "Transazione rimossa con successo.\n";
                    else
                        std::cout << "Transazione non trovata.\n";
                    break;
                }

                case 3: {
                    std::cin.ignore();
                    std::string vecchia_descrizione;
                    std::cout << "Descrizione della transazione da modificare: ";
                    std::getline(std::cin, vecchia_descrizione);

                    double nuovo_importo;
                    std::string nuova_descrizione, nuova_data;
                    int nuovo_tipo_int;

                    std::cout << "Nuovo importo: ";
                    std::cin >> nuovo_importo;
                    std::cin.ignore();
                    std::cout << "Nuova descrizione: ";
                    std::getline(std::cin, nuova_descrizione);
                    std::cout << "Nuova data (YYYY-MM-DD): ";
                    std::getline(std::cin, nuova_data);
                    std::cout << "Nuovo tipo (0=Entrata, 1=Uscita): ";
                    std::cin >> nuovo_tipo_int;

                    TipoTransazione nuovo_tipo = (nuovo_tipo_int == 0) ? TipoTransazione::Entrata : TipoTransazione::Uscita;
                    conto.modifica_transazione(vecchia_descrizione, Transazione(nuovo_importo, nuova_descrizione, nuova_data, nuovo_tipo));
                    break;
                }

                case 4:
                    conto.mostra_transazioni();
                    break;

                case 5:
                    std::cout << "Saldo attuale: " << conto.calcola_saldo() << "\n";
                    break;

                case 6: {
                    std::cin.ignore();
                    std::string keyword;
                    std::cout << "Inserisci parola chiave per la ricerca: ";
                    std::getline(std::cin, keyword);
                    auto risultati = conto.cerca_per_descrizione(keyword);
                    if (risultati.empty()) {
                        std::cout << "Nessuna transazione trovata.\n";
                    } else {
                        for (const auto& t : risultati) {
                            std::cout << t.to_string() << "\n";
                        }
                    }
                    break;
                }

                case 7: {
                    std::cin.ignore();
                    std::string data;
                    std::cout << "Inserisci data (YYYY-MM-DD): ";
                    std::getline(std::cin, data);
                    auto risultati = conto.cerca_per_data(data);
                    if (risultati.empty()) {
                        std::cout << "Nessuna transazione trovata.\n";
                    } else {
                        for (const auto& t : risultati) {
                            std::cout << t.to_string() << "\n";
                        }
                    }
                    break;
                }

                case 8:
                    conto.ordina_per_data();
                    std::cout << "Transazioni ordinate per data.\n";
                    break;

                case 9:
                    conto.ordina_per_importo();
                    std::cout << "Transazioni ordinate per importo.\n";
                    break;

                case 10: {
                    std::cin.ignore();
                    std::string nome_file;
                    std::cout << "Inserisci nome file per salvare: ";
                    std::getline(std::cin, nome_file);
                    conto.salva_su_file(nome_file);
                    std::cout << "Transazioni salvate.\n";
                    break;
                }

                case 11: {
                    std::cin.ignore();
                    std::string nome_file;
                    std::cout << "Inserisci nome file da cui caricare: ";
                    std::getline(std::cin, nome_file);
                    conto.leggi_da_file(nome_file);
                    std::cout << "Transazioni caricate.\n";
                    break;
                }

                case 0:
                    std::cout << "Uscita dal programma.\n";
                    break;

                default:
                    std::cout << "Scelta non valida.\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Errore: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
