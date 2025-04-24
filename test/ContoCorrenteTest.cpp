//
// Created by ettor on 24/04/2025.
//
#include "gtest/gtest.h"
#include "../ContoCorrente.h"

class ContoCorrenteTest : public ::testing::Test {
protected:
    ContoCorrente conto;

    ContoCorrenteTest() : conto("TestAccount") {}

    void SetUp() override {
        conto.aggiungi_transazione(Transazione(1000, "Entrata Test", "2025-04-01", TipoTransazione::Entrata));
        conto.aggiungi_transazione(Transazione(250, "Spesa Test", "2025-04-02", TipoTransazione::Uscita));
    }
};

TEST_F(ContoCorrenteTest, CalcoloSaldoCorretto) {
EXPECT_DOUBLE_EQ(conto.calcola_saldo(), 750);
}

TEST_F(ContoCorrenteTest, RicercaPerDataEsatta) {
auto risultati = conto.cerca_per_data("2025-04-02");
ASSERT_EQ(risultati.size(), 1);
EXPECT_EQ(risultati.front().get_descrizione(), "Spesa Test");
}

TEST_F(ContoCorrenteTest, RicercaPerDescrizioneParziale) {
auto risultati = conto.cerca_per_descrizione("Entrata");
ASSERT_EQ(risultati.size(), 1);
EXPECT_EQ(risultati.front().get_importo(), 1000);
}

TEST_F(ContoCorrenteTest, RimuoviTransazione) {
bool rimosso = conto.rimuovi_transazione("Spesa Test");
EXPECT_TRUE(rimosso);
EXPECT_DOUBLE_EQ(conto.calcola_saldo(), 1000);
}

TEST_F(ContoCorrenteTest, ModificaTransazione) {
Transazione nuova(200, "Spesa Modificata", "2025-04-03", TipoTransazione::Uscita);
conto.modifica_transazione("Spesa Test", nuova);

auto risultati = conto.cerca_per_descrizione("Modificata");
ASSERT_EQ(risultati.size(), 1);
EXPECT_EQ(risultati.front().get_importo(), 200);
}

TEST(TransazioneTest, LanciaEccezioneImportoNegativo) {
EXPECT_THROW({
Transazione t(-50, "Errore", "2025-04-01", TipoTransazione::Entrata);
}, std::invalid_argument);
}

TEST(ContoCorrenteFileTest, SalvaELeggiDaFile) {
std::string nome_file = "test_transazioni.txt";

// Conto di partenza
ContoCorrente conto_orig("Orig");
conto_orig.aggiungi_transazione(Transazione(100, "Paghetta", "2025-04-01", TipoTransazione::Entrata));
conto_orig.aggiungi_transazione(Transazione(50, "Cinema", "2025-04-02", TipoTransazione::Uscita));

// Salva su file
conto_orig.salva_su_file(nome_file);

// Crea un nuovo conto e carica dal file
ContoCorrente conto_letto("Letto");
conto_letto.leggi_da_file(nome_file);

// Controlla che le transazioni siano lette correttamente
auto transazioni = conto_letto.get_transazioni();
ASSERT_EQ(transazioni.size(), 2);

auto it = transazioni.begin();

EXPECT_EQ(it->get_descrizione(), "Paghetta");
EXPECT_EQ(it->get_importo(), 100);

it++;

EXPECT_EQ(it->get_descrizione(), "Cinema");
EXPECT_EQ(it->get_importo(), 50);

// Pulisce il file temporaneo
std::remove(nome_file.c_str());
}


