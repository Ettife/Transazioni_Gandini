//
// Created by ettor on 23/03/2025.
//
#ifndef TRANSAZIONI_GANDINI_TRANSAZIONE_H
#define TRANSAZIONI_GANDINI_TRANSAZIONE_H

#include <string>
#include <iostream>

class Transazione {
protected:
    double importo;
    std::string descrizione;
    std::string data; // formato: YYYY-MM-DD

public:
    Transazione(double imp, const std::string& desc, const std::string& d);
    virtual ~Transazione() = default;

    virtual std::string to_string() const = 0;
    double get_importo() const;
    std::string get_data() const;
    std::string get_descrizione() const;
};

class Entrata : public Transazione {
public:
    Entrata(double imp, const std::string& desc, const std::string& d);
    std::string to_string() const override;
};

class Uscita : public Transazione {
public:
    Uscita(double imp, const std::string& desc, const std::string& d);
    std::string to_string() const override;
};

#endif //TRANSAZIONI_GANDINI_TRANSAZIONE_H
