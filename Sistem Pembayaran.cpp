#include <iostream>
#include <string>
using namespace std;

class Pembayaran {
protected:
    string idPembayaran;
    double jumlah;
    string tanggal;
    string status;

public:
    Pembayaran(string id, double jml, string tgl, string stat) : idPembayaran(id), jumlah(jml), tanggal(tgl), status(stat) {}
    virtual ~Pembayaran() {}

    virtual bool validasiPembayaran() = 0;
    virtual string prosesPembayaran() = 0;
    virtual string refundPembayaran() = 0;
};

class KartuKredit : public Pembayaran {
private:
    string nomorKartu;
    string tanggalKadaluwarsa;
    string cvv;

public:
    KartuKredit(string id, double jml, string tgl, string stat, string noKartu, string expDate, string cvvKode)
        : Pembayaran(id, jml, tgl, stat), nomorKartu(noKartu), tanggalKadaluwarsa(expDate), cvv(cvvKode) {}

    bool validasiPembayaran() override {
        return (nomorKartu.length() == 15 || nomorKartu.length() == 16) && cvv.length() == 3;
    }

    string prosesPembayaran() override {
        if (validasiPembayaran()) {
            status = "Diproses";
            return "Pembayaran Kartu Kredit sebesar " + to_string(jumlah) + " berhasil diproses.";
        }
        return "Pembayaran Kartu Kredit tidak valid.";
    }

    string refundPembayaran() override {
        status = "Dikembalikan";
        return "Pembayaran Kartu Kredit sebesar " + to_string(jumlah) + " dikembalikan.";
    }
};

class TransferBank : public Pembayaran {
private:
    string nomorRekening;
    string namaBank;
    string kodeTransfer;

public:
    TransferBank(string id, double jml, string tgl, string stat, string noRek, string bank, string trfKode)
        : Pembayaran(id, jml, tgl, stat), nomorRekening(noRek), namaBank(bank), kodeTransfer(trfKode) {}

    bool validasiPembayaran() override {
        return nomorRekening.length() >= 10 && !namaBank.empty();
    }

    string prosesPembayaran() override {
        if (validasiPembayaran()) {
            status = "Diproses";
            return "Pembayaran Transfer Bank sebesar " + to_string(jumlah) + " berhasil diproses.";
        }
        return "Pembayaran Transfer Bank tidak valid.";
    }

    string refundPembayaran() override {
        status = "Dikembalikan";
        return "Pembayaran Transfer Bank sebesar " + to_string(jumlah) + " dikembalikan.";
    }
};

class DompetDigital : public Pembayaran {
private:
    string idDompet;
    string penyedia;
    string nomorTelepon;

public:
    DompetDigital(string id, double jml, string tgl, string stat, string dId, string pyd, string noHp)
        : Pembayaran(id, jml, tgl, stat), idDompet(dId), penyedia(pyd), nomorTelepon(noHp) {}

    bool validasiPembayaran() override {
        return idDompet.length() > 5 && nomorTelepon.length() == 10;
    }

    string prosesPembayaran() override {
        if (validasiPembayaran()) {
            status = "Diproses";
            return "Pembayaran Dompet Digital sebesar " + to_string(jumlah) + " berhasil diproses.";
        }
        return "Pembayaran Dompet Digital tidak valid.";
    }

    string refundPembayaran() override {
        status = "Dikembalikan";
        return "Pembayaran Dompet Digital sebesar " + to_string(jumlah) + " dikembalikan.";
    }
};

int main() {
    KartuKredit pembayaranKK("001", 100.0, "2025-03-17", "Tertunda", "1234567890123456", "12/25", "123");
    TransferBank pembayaranTB("002", 200.0, "2025-03-17", "Tertunda", "1234567890", "Bank XYZ", "TRF001");
    DompetDigital pembayaranDD("003", 50.0, "2025-03-17", "Tertunda", "WLT12345", "PayPal", "0812345678");

    cout << pembayaranKK.prosesPembayaran() << endl;
    cout << pembayaranTB.prosesPembayaran() << endl;
    cout << pembayaranDD.prosesPembayaran() << endl;

    return 0;
}