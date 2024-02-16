#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur untuk menyimpan informasi tiket
struct Tiket {
    char namaPemesan[50];
    int nomorTiket;
    float harga;
    int tipe;  // 0: Ekonomi, 1: VIP
};

// Struktur untuk melacak jumlah pesanan
struct JumlahPesanan {
    int ekonomi;
    int vip;
};

// Struktur untuk menyimpan tiket yang sudah dipesan
struct TiketDipesan {
    struct Tiket tiket;
    struct TiketDipesan *next;
};

// Fungsi untuk memesan tiket
void pesanTiket(struct Tiket *tiket, struct JumlahPesanan *jumlahPesanan, struct TiketDipesan **head) {
    printf("Masukkan nama pemesan: ");
    scanf("%s", tiket->namaPemesan);

    int jumlah;
    printf("Masukkan jumlah tiket yang ingin dipesan: ");
    scanf("%d", &jumlah);

    printf("Pilih tipe tiket (0: Ekonomi, 1: VIP): ");
    scanf("%d", &tiket->tipe);

    // Mengisi nomor tiket secara acak sebagai contoh
    tiket->nomorTiket = rand() % 1000 + 1;

    // Menentukan harga berdasarkan tipe tiket
    if (tiket->tipe == 0) {
        tiket->harga = 150000.0;
        jumlahPesanan->ekonomi += jumlah;
    } else if (tiket->tipe == 1) {
        tiket->harga = 420000.0;
        jumlahPesanan->vip += jumlah;
    }

    // Mengalikan harga dengan jumlah tiket
    tiket->harga *= jumlah;

    // Menyimpan tiket yang sudah dipesan ke dalam linked list
    struct TiketDipesan *newTiketDipesan = (struct TiketDipesan *)malloc(sizeof(struct TiketDipesan));
    newTiketDipesan->tiket = *tiket;
    newTiketDipesan->next = *head;
    *head = newTiketDipesan;

    printf("\nPemesanan berhasil!\n");

    // Kembali ke menu utama setelah memesan tiket
    return;
}

// Fungsi untuk membatalkan salah satu tiket yang sudah dipesan
void batalkanSalahSatuTiket(struct TiketDipesan **head, struct JumlahPesanan *jumlahPesanan) {
    if (*head == NULL) {
        printf("Belum ada tiket yang dipesan.\n");
        return;
    }

    printf("\nDaftar Tiket yang Sudah Dipesan:\n");
    struct TiketDipesan *current = *head;
    int count = 1;
    while (current != NULL) {
        printf("%d. Nomor Tiket: %d, Nama Pemesan: %s, Tipe Tiket: %s\n", count, current->tiket.nomorTiket, current->tiket.namaPemesan, current->tiket.tipe == 0 ? "Ekonomi" : "VIP");
        current = current->next;
        count++;
    }

    int nomorTiket;
    printf("Masukkan nomor tiket yang ingin dibatalkan: ");
    scanf("%d", &nomorTiket);

    current = *head;
    struct TiketDipesan *previous = NULL;
    while (current != NULL && current->tiket.nomorTiket != nomorTiket) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Nomor tiket tidak valid.\n");
        return;
    }

    if (previous == NULL) {
        *head = current->next;
    } else {
        previous->next = current->next;
    }

    if (current->tiket.tipe == 0) {
        jumlahPesanan->ekonomi--;
    } else {
        jumlahPesanan->vip--;
    }

    free(current);
    printf("Tiket berhasil dibatalkan.\n");

    // Kembali ke menu utama setelah membatalkan tiket
    return;
}

// Fungsi untuk menampilkan informasi tiket
void tampilkanTiket(struct Tiket tiket) {
    printf("Nomor Tiket: %d\n", tiket.nomorTiket);
    printf("Nama Pemesan: %s\n", tiket.namaPemesan);
    printf("Tipe Tiket: %s\n", tiket.tipe == 0 ? "Ekonomi" : "VIP");
    printf("Harga Tiket: %.2f\n", tiket.harga);
}

// Fungsi untuk menampilkan jumlah pesanan
void tampilkanJumlahPesanan(struct JumlahPesanan jumlahPesanan) {
    printf("\nJumlah Pesanan:\n");
    printf("Ekonomi: %d tiket\n", jumlahPesanan.ekonomi);
    printf("VIP: %d tiket\n", jumlahPesanan.vip);
}

// Fungsi untuk menampilkan tiket yang sudah dipesan sebelumnya
void tampilkanTiketDipesan(struct TiketDipesan *head) {
    printf("\nTiket yang sudah dipesan sebelumnya:\n");
    struct TiketDipesan *current = head;
    while (current != NULL) {
        tampilkanTiket(current->tiket);
        current = current->next;
        printf("\n");
    }
}

int main() {
    struct Tiket tiket;
    struct JumlahPesanan jumlahPesanan = {0, 0};
    struct TiketDipesan *tiketDipesanHead = NULL;
    int pilihan;
    float totalHarga = 0.0;

    printf("=== Sistem Pemesanan Tiket ===\n");

    do {
        printf("\nMenu:\n");
        printf("1. Pesan Tiket\n");
        printf("2. Batalkan Salah Satu Tiket\n");
        printf("3. Tampilkan Tiket dan Total Harga\n");
        printf("4. Tampilkan Tiket yang Sudah Dipesan\n");
        printf("5. Keluar\n");
        printf("Pilih opsi (1-5): ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                pesanTiket(&tiket, &jumlahPesanan, &tiketDipesanHead);
                break;
            case 2:
                batalkanSalahSatuTiket(&tiketDipesanHead, &jumlahPesanan);
                break;
            case 3:
                printf("\nTiket yang dipesan:\n");
                tampilkanTiket(tiket);
                tampilkanJumlahPesanan(jumlahPesanan);
                printf("\nTotal Harga Tiket: %.2f\n", totalHarga);
                break;
            case 4:
                tampilkanTiketDipesan(tiketDipesanHead);
                break;
            case 5:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan pilih lagi.\n");
        }

    } while (pilihan != 5);

    // Menghapus linked list tiket yang sudah dipesan setelah program selesai
    struct TiketDipesan *current = tiketDipesanHead;
    while (current != NULL) {
        struct TiketDipesan *next = current->next;
        free(current);
        current = next;
    }

    return 0;
}
