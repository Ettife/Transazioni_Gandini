//
// Created by ettor on 03/04/2025.
//
#include <gtest/gtest.h>
#include "../Transazione.h"

class TransazioneTest : public ::testing::Test {
protected:
    Entrata* entrata;
    Uscita* uscita;

    void SetUp() override {
        entrata = new Entrata(150.0, "Bonus", "2025-04-01");
        uscita = new Uscita(75.0, "Bollette", "2025-04-02");
    }

    void TearDown() override {
        delete entrata;
        delete uscita;
    }
};


