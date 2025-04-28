#include "gtest/gtest.h"
#include "../ContoCorrente.h"
#include <fstream>
#include <cstdio>

// Fixture base per testare ContoCorrente
class ContoCorrenteTest : public ::testing::Test {
protected:
    ContoCorrente conto;

    ContoCorrenteTest() : conto("TestAccount") {}

    void SetUp() override {
        conto.aggiungi_transazione(Transazione(1000, "Stipendio", "2025-04-01", TipoTransazione::Entrata));
        conto.aggiungi_transazione(Transazione(300, "Affitto", "2025-04-02", TipoTransazione::Uscita));
        conto.aggiungi_transazione(Transazione(150, "Cena", "2025-04-03", TipoTransazione::Uscita));
    }

    void TearDown() override {
        // Niente da fare
    }
};

// Fixture base per testare Transazione
class TransazioneTest : public ::testing::Test {};

TEST_F(ContoCorrenteTest, CalcoloSaldoCorretto) {
    EXPECT_DOUBLE_EQ(conto.calcola_saldo(), 550);
}

TEST_F(ContoCorrenteTest, RicercaPerDataEsatta) {
    auto risultati = conto.cerca_per_data("2025-04-02");
    ASSERT_EQ(risultati.size(), 1);
    EXPECT_EQ(risultati.front().get_descrizione(), "Affitto");
}

TEST_F(ContoCorrenteTest, RicercaPerDescrizioneParziale) {
    auto risultati = conto.cerca_per_descrizione("Cena");
    ASSERT_EQ(risultati.size(), 1);
    EXPECT_EQ(risultati.front().get_importo(), 150);
}

TEST_F(ContoCorrenteTest, RimuoviTransazione) {
    EXPECT_TRUE(conto.rimuovi_transazione("Affitto"));
    EXPECT_DOUBLE_EQ(conto.calcola_saldo(), 850);
}

TEST_F(ContoCorrenteTest, ModificaTransazione) {
    Transazione nuova(400, "Affitto Modificato", "2025-04-04", TipoTransazione::Uscita);
    conto.modifica_transazione("Affitto", nuova);
    auto risultati = conto.cerca_per_descrizione("Modificato");
    ASSERT_EQ(risultati.size(), 1);
    EXPECT_EQ(risultati.front().get_importo(), 400);
}

TEST_F(ContoCorrenteTest, RicercaDescrizioneNessunRisultato) {
    auto risultati = conto.cerca_per_descrizione("Palestra");
    EXPECT_TRUE(risultati.empty());
}

TEST_F(ContoCorrenteTest, OrdinaPerImporto) {
    conto.ordina_per_importo();
    auto transazioni = conto.get_transazioni();
    auto it = transazioni.begin();
    EXPECT_EQ(it++->get_importo(), 150);
    EXPECT_EQ(it++->get_importo(), 300);
    EXPECT_EQ(it++->get_importo(), 1000);
}

TEST_F(ContoCorrenteTest, OrdinaPerData) {
    conto.ordina_per_data();
    auto transazioni = conto.get_transazioni();
    auto it = transazioni.begin();
    EXPECT_EQ(it++->get_data(), "2025-04-01");
    EXPECT_EQ(it++->get_data(), "2025-04-02");
    EXPECT_EQ(it++->get_data(), "2025-04-03");
}

TEST_F(ContoCorrenteTest, SalvataggioELetturaFile) {
    std::string filename = "testfile.txt";
    conto.salva_su_file(filename);

    ContoCorrente conto_lettura("Vuoto");
    conto_lettura.leggi_da_file(filename);

    EXPECT_EQ(conto_lettura.get_transazioni().size(), 3);
    EXPECT_EQ(conto_lettura.calcola_saldo(), 550);

    std::remove(filename.c_str());
}

TEST_F(ContoCorrenteTest, CaricamentoFileNonEsistente) {
    ContoCorrente conto_errore("Errore");
    EXPECT_THROW({
                     conto_errore.leggi_da_file("file_inesistente.txt");
                 }, std::runtime_error);
}

TEST_F(ContoCorrenteTest, ContoCorrenteCopyConstructor) {
    ContoCorrente copia = conto;
    EXPECT_EQ(copia.get_transazioni().size(), conto.get_transazioni().size());
}

TEST_F(ContoCorrenteTest, ContoCorrenteAssignmentOperator) {
    ContoCorrente nuovo("Altro");
    nuovo = conto;
    EXPECT_EQ(nuovo.get_transazioni().size(), conto.get_transazioni().size());
}

TEST_F(TransazioneTest, CreaTransazioneValida) {
    Transazione t(500, "Vendita", "2025-04-10", TipoTransazione::Entrata);
    EXPECT_EQ(t.get_importo(), 500);
    EXPECT_EQ(t.get_descrizione(), "Vendita");
    EXPECT_EQ(t.get_data(), "2025-04-10");
    EXPECT_EQ(t.get_tipo(), TipoTransazione::Entrata);
}

TEST_F(TransazioneTest, CreazioneImportoNegativo) {
    EXPECT_THROW({
                     Transazione t(-20, "Errore", "2025-04-11", TipoTransazione::Uscita);
                 }, std::invalid_argument);
}

TEST_F(TransazioneTest, ToStringCorretto) {
    Transazione t(300, "Bonus", "2025-04-12", TipoTransazione::Entrata);
    EXPECT_EQ(t.to_string(), "Entrata;300.0;Bonus;2025-04-12");
}

TEST_F(ContoCorrenteTest, OperazioniSuContoVuoto) {
    ContoCorrente vuoto("Vuoto");
    EXPECT_TRUE(vuoto.get_transazioni().empty());
    EXPECT_DOUBLE_EQ(vuoto.calcola_saldo(), 0.0);
    EXPECT_TRUE(vuoto.cerca_per_descrizione("Nessuno").empty());
}
