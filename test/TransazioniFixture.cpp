//
// Created by ettor on 03/04/2025.
//
#include <gtest/gtest.h>
#include "../Transazione.h"
#include "../GestoreFile.h"
#include "../ContoCorrente.h"
#include <fstream>

class TestGestoreFile : public ::testing::Test {
protected:
    void SetUp() override {
        GestoreFile::get_istanza()->salva_su_file("test_file.txt", transazioni);
    }

    void TearDown() override {
        std::remove("test_file.txt");
    }

    std::vector<Transazione*> transazioni = {
            new Entrata(100.0, "Salary", "2025-03-25"),
            new Uscita(50.0, "Groceries", "2025-03-26"),
            new Entrata(200.0, "Freelance", "2025-03-27")
    };
};

// Testa la funzione di salvataggio su file di GestoreFile
TEST_F(TestGestoreFile, TestSalvaSuFile) {
    GestoreFile* gestore = GestoreFile::get_istanza();
    std::vector<Transazione*> transazioni_iniziali = {
            new Entrata(100.0, "Salary", "2025-03-25"),
            new Uscita(50.0, "Groceries", "2025-03-26")
    };

    gestore->salva_su_file("test_file.txt", transazioni_iniziali);

    std::ifstream file("test_file.txt");
    ASSERT_TRUE(file.is_open());

    std::string line;
    getline(file, line);
    EXPECT_EQ(line, "Entrata;100.000000;Salary;2025-03-25");

    getline(file, line);
    EXPECT_EQ(line, "Uscita;50.000000;Groceries;2025-03-26");

    file.close();
}

// Testa la funzione di lettura del gestore file
TEST_F(TestGestoreFile, TestLeggiDaFile) {
    GestoreFile* gestore = GestoreFile::get_istanza();
    std::vector<Transazione*> transazioni_lettura = gestore->leggi_da_file("test_file.txt");

    ASSERT_EQ(transazioni_lettura.size(), 3); //3 sono le transazioni salvate dal test

    EXPECT_EQ(transazioni_lettura[0]->to_string(), "Entrata;100.000000;Salary;2025-03-25");
    EXPECT_EQ(transazioni_lettura[1]->to_string(), "Uscita;50.000000;Groceries;2025-03-26");
    EXPECT_EQ(transazioni_lettura[2]->to_string(), "Entrata;200.000000;Freelance;2025-03-27");

    // per evitare memory leak
    for (auto t : transazioni_lettura) {
        delete t;
    }
}




