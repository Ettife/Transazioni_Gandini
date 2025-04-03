#include "./lib/googletest/googletest/include/gtest/gtest.h"
#include "../ContoCorrente.h"

// Test per verificare la creazione di un'entrata
//La macro TEST definisce un test case
TEST(TransazioneTest, CreazioneEntrata) {
Entrata e(100.0, "Stipendio", "2025-03-29");
EXPECT_EQ(e.get_importo(), 100.0);
EXPECT_EQ(e.get_descrizione(), "Stipendio");
EXPECT_EQ(e.get_data(), "2025-03-29");
}

// Test per verificare la creazione di un'uscita
TEST(TransazioneTest, CreazioneUscita) {
Uscita u(50.0, "Spesa", "2025-03-30");
EXPECT_EQ(u.get_importo(), 50.0);
EXPECT_EQ(u.get_descrizione(), "Spesa");
EXPECT_EQ(u.get_data(), "2025-03-30");

}

TEST(TransazioneTest, CreazioneTransazione) {
    // Poiché `Transazione` è una classe astratta, verifichiamo la creazione tramite `Entrata` o `Uscita`
    Entrata e(150.0, "Bonus", "2025-04-01");
    Transazione* t = &e;

    EXPECT_EQ(t->get_importo(), 150.0);
    EXPECT_EQ(t->get_descrizione(), "Bonus");
    EXPECT_EQ(t->get_data(), "2025-04-01");
}

// Test sul metodo `to_string`
TEST(TransazioneTest, ToStringTest) {
    Uscita u(75.0, "Bollette", "2025-04-02");

    std::string expected_output = "Uscita;75.000000;Bollette;2025-04-02";
    EXPECT_EQ(u.to_string(), expected_output);
}

// Test per aggiungere una transazione a un conto corrente
TEST(ContoCorrenteTest, AggiuntaTransazione) {
ContoCorrente conto;
auto e = new Entrata(200.0, "Bonus", "2025-03-31");
conto.aggiungi_transazione(e);

const auto& transazioni = conto.get_transazioni();
EXPECT_EQ(transazioni.size(), 1);
EXPECT_EQ(transazioni[0]->get_importo(), 200.0);
}

// Test per il calcolo del saldo
TEST(ContoCorrenteTest, CalcoloSaldo) {
ContoCorrente conto;
conto.aggiungi_transazione(new Entrata(500.0, "Stipendio", "2025-03-29"));
conto.aggiungi_transazione(new Uscita(100.0, "Cena", "2025-03-30"));

EXPECT_EQ(conto.calcola_saldo(), 400.0);
}

// Test per verificare che le transazioni vengano stampate correttamente
TEST(ContoCorrenteTest, MostraTransazioni) {
ContoCorrente conto;
conto.aggiungi_transazione(new Entrata(300.0, "Regalo", "2025-03-29"));
testing::internal::CaptureStdout(); //funzione di Gtest che cattura l'output sulla console
conto.mostra_transazioni();
std::string output = testing::internal::GetCapturedStdout();

EXPECT_TRUE(output.find("Regalo") != std::string::npos); //se "Regalo" viene trovato allora la funzione find restituisce un indice valido
}


