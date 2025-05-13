#include <iostream>
#include <string>
using namespace std;

struct Barang {
    string nama;
    string kode;
    int harga;
    int stok;
    Barang* next;
};

Barang* head = nullptr;

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
        for (Barang* j = head; j != nullptr; j = j->next) {
            if ((ascending && i->harga < j->harga) || (!ascending && i->harga > j->harga)) {
                tukar(i, j);
            }
        }
    }

    Barang* temp = head;
    while (temp != nullptr) {
        cout << "Nama: " << temp->nama << ", Kode: " << temp->kode
             << ", Harga: " << temp->harga << ", Stok: " << temp->stok << endl;
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
        cout << "Barang dengan " << nama << " tidak ditemukan.\n";
        return;
    }

    if (prev == nullptr) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }
    delete temp;
    cout << "Barang dengan nama " << nama << " telah dihapus.\n";
}