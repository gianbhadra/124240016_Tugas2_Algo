#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct Barang {
    string nama;
    string kode;
    int harga;
    int stok;
    Barang* next;
};

Barang* head = nullptr;

void simpanKeFile() {
    ofstream file("stok_barang.txt");
    Barang* temp = head;
    while (temp) {
        file << temp->nama << "|" << temp->kode << "|" << temp->harga << "|" << temp->stok << endl;
        temp = temp->next;
    }
    file.close();
}

void bacaDariFile() {
    ifstream file("stok_barang.txt");
    if (!file) {
        cout << "File tidak ditemukan, memulai daftar kosong.\n";
        return;
    }
    string line;
    while (getline(file, line)) {
        Barang* barangBaru = new Barang;
        size_t pos = 0;

        pos = line.find("|");
        barangBaru->nama = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find("|");
        barangBaru->kode = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find("|");
        string hargaStr = line.substr(0, pos);
        stringstream ssHarga(hargaStr);
        ssHarga >> barangBaru->harga;
        line.erase(0, pos + 1);

        string stokStr = line;
        stringstream ssStok(stokStr);
        ssStok >> barangBaru->stok;

        barangBaru->next = head;
        head = barangBaru;
    }
    file.close();
}


void tambahBarang(string nama, string kode, int harga, int stok) {
    Barang* barangBaru = new Barang;
    barangBaru->nama = nama;
    barangBaru->kode = kode;
    barangBaru->harga = harga;
    barangBaru->stok = stok;
    barangBaru->next = nullptr;

    if (head == nullptr) {
        head = barangBaru;
    } else {
        Barang* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = barangBaru;
    }
    simpanKeFile();
}

void tukar(Barang* a, Barang* b) {
    string tempNama = a->nama;
    string tempKode = a->kode;
    int tempHarga = a->harga;
    int tempStok = a->stok;

    a->nama = b->nama;
    a->kode = b->kode;
    a->harga = b->harga;
    a->stok = b->stok;

    b->nama = tempNama;
    b->kode = tempKode;
    b->harga = tempHarga;
    b->stok = tempStok;
}

void tampilkanBarang(bool ascending = true) {
    if (head == nullptr) {
        cout << "Tidak ada barang dalam daftar.\n";
        return;
    }

    for (Barang* i = head; i != nullptr; i = i->next) {
        for (Barang* j = i->next; j != nullptr; j = j->next) {
            if ((ascending && i->harga > j->harga) || (!ascending && i->harga < j->harga)) {
                tukar(i, j);
            }
        }
    }

    Barang* temp = head;
    cout << "\n=== Daftar Stok Barang ===\n";
    while (temp != nullptr) {
        cout << "Nama: " << temp->nama
             << ", Kode: " << temp->kode
             << ", Harga: " << temp->harga
             << ", Stok: " << temp->stok << endl;
        temp = temp->next;
    }
}

void hapusBarang(string nama) {
    if (head == nullptr) {
        cout << "Tidak ada barang dalam daftar.\n";
        return;
    }

    Barang* temp = head;
    Barang* prev = nullptr;

    while (temp && temp->nama != nama) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Barang dengan nama \"" << nama << "\" tidak ditemukan.\n";
        return;
    }

    if (prev == nullptr) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }
    delete temp;
    cout << "Barang dengan nama \"" << nama << "\" telah dihapus.\n";
    simpanKeFile();
    tampilkanBarang();
}

int main() {
    bacaDariFile();
    int pilihan;

    do {
        cout << "\n=== Menu Manajemen Stok Barang ===\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Tampilkan Barang\n"; 
        cout << "3. Hapus Barang\n";
        cout << "4. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            int jumlah;
            cout << "\nMasukkan jumlah barang yang ingin ditambahkan: ";
            cin >> jumlah;
            cin.ignore();
            for (int i = 0; i < jumlah; i++) {
                string nama, kode;
                int harga, stok;
                cout << "\n=== Barang " << (i + 1) << " ===\n";
                cout << "Masukkan nama barang: ";
                getline(cin, nama);
                cout << "Masukkan kode barang: ";
                getline(cin, kode);
                cout << "Masukkan harga barang: ";
                cin >> harga;
                cout << "Masukkan stok barang: ";
                cin >> stok;
                cin.ignore();
                tambahBarang(nama, kode, harga, stok);
            }
        } else if (pilihan == 2) {
            int submenu;
            do {
                cout << "\nTampilkan barang berdasarkan:\n";
                cout << "1. Harga Ascending\n";
                cout << "2. Harga Descending\n";
                cout << "Pilih opsi: ";
                cin >> submenu;
                if (submenu == 1) {
                    tampilkanBarang(true);
                } else if (submenu == 2) {
                    tampilkanBarang(false);
                } else {
                    cout << "Pilihan tidak valid.\n";
                }
            } while (submenu != 1 && submenu != 2);
        } else if (pilihan == 3) {
            string nama;
            cout << "Masukkan nama barang yang ingin dihapus: ";
            getline(cin, nama);
            hapusBarang(nama);
        } else if (pilihan == 4) {
            cout << "Keluar dari program.\n";
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 4);

    return 0;
}
