#ifndef TRANSAZIONI_GANDINI_TRANSAZIONE_H
#define TRANSAZIONI_GANDINI_TRANSAZIONE_H

#include <string>
#include <stdexcept>
#include <regex>
#include <iomanip>
#include <sstream>

enum class TipoTransazione { Entrata, Uscita };

class Transazione {
private:
    double importo;
    std::string descrizione;
    std::string data; // formato YYYY-MM-DD
    TipoTransazione tipo;

    bool valida_data(const std::string& data) const {
        const std::regex formato_data("^\\d{4}-\\d{2}-\\d{2}$");
        if (!std::regex_match(data, formato_data)) return false;
        int anno, mese, giorno;
        sscanf(data.c_str(), "%d-%d-%d", &anno, &mese, &giorno);
        if (mese < 1 || mese > 12 || giorno < 1 || giorno > 31) return false;
        if ((mese == 4 || mese == 6 || mese == 9 || mese == 11) && giorno > 30) return false;
        if (mese == 2) {
            bool bisestile = (anno % 4 == 0 && (anno % 100 != 0 || anno % 400 == 0));
            if (giorno > (bisestile ? 29 : 28)) return false;
        }
        return true;
    }

public:
    Transazione(double imp, const std::string& desc, const std::string& d, TipoTransazione t)
            : importo(imp), descrizione(desc), data(d), tipo(t) {
        if (imp < 0) throw std::invalid_argument("Importo negativo non ammesso");
        if (desc.empty()) throw std::invalid_argument("Descrizione non può essere vuota");
        if (!valida_data(d)) throw std::invalid_argument("Data non valida (formato richiesto: YYYY-MM-DD)");
    }

    double get_importo() const { return importo; }
    std::string get_data() const { return data; }
    std::string get_descrizione() const { return descrizione; }
    TipoTransazione get_tipo() const { return tipo; }

    std::string to_string() const{
        std::ostringstream oss;
        oss << (tipo == TipoTransazione::Entrata ? "Entrata" : "Uscita")
            << ";" << std::fixed << std::setprecision(1) << importo
            << ";" << descrizione
            << ";" << data;
        return oss.str();
    }
};

#endif // TRANSAZIONI_GANDINI_TRANSAZIONE_H
