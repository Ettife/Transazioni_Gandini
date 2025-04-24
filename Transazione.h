#ifndef TRANSAZIONI_GANDINI_TRANSAZIONE_H
#define TRANSAZIONI_GANDINI_TRANSAZIONE_H

#include <string>
#include <stdexcept>

enum class TipoTransazione { Entrata, Uscita };

class Transazione {
private:
    double importo;
    std::string descrizione;
    std::string data;
    TipoTransazione tipo;

public:
    Transazione(double imp, const std::string& desc, const std::string& d, TipoTransazione t)
            : importo(imp), descrizione(desc), data(d), tipo(t) {
        if (imp < 0) throw std::invalid_argument("Importo negativo non ammesso");
    }

    double get_importo() const { return importo; }
    std::string get_data() const { return data; }
    std::string get_descrizione() const { return descrizione; }
    TipoTransazione get_tipo() const { return tipo; }

    std::string to_string() const {
        return (tipo == TipoTransazione::Entrata ? "Entrata" : "Uscita") +
               (";" + std::to_string(importo) + ";" + descrizione + ";" + data);
    }
};

#endif //TRANSAZIONI_GANDINI_TRANSAZIONE_H