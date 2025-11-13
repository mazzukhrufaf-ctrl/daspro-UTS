#include <stdio.h>
#include <string.h>

// Prototipe fungsi
void tampilkanMenu();
float hitungTotal(float harga, int jumlah);
float hitungPajak(float total);
void tampilkanStruk(char namaPelanggan[], char items[][20], float harga[], int jumlah[], int itemCount, float total, float pajak, float grandTotal);
void tambahBarangBaru();
void prosesPembayaran(float grandTotal);
float hitungKembalian(float total, float bayar);

// Array untuk menyimpan menu barang
char menuItems[20][20];
float menuHarga[20];
int jumlahBarang = 5;

// Inisialisasi barang default
void inisialisasiBarang() {
    strcpy(menuItems[0], "Roti");
    menuHarga[0] = 5000;
    strcpy(menuItems[1], "Susu");
    menuHarga[1] = 8000;
    strcpy(menuItems[2], "Telur");
    menuHarga[2] = 25000;
    strcpy(menuItems[3], "Minyak");
    menuHarga[3] = 15000;
    strcpy(menuItems[4], "Gula");
    menuHarga[4] = 12000;
}

int main() {
    inisialisasiBarang();
    
    char namaPelanggan[50];
    char items[10][20];
    float harga[10];
    int jumlah[10];
    int itemCount = 0;
    char lanjut;
    float total = 0, pajak, grandTotal;
    int pilihan, qty;
    char pilihanMenu;

    printf("=== PROGRAM KASIR MINI MARKET ===\n");
    
    do {
        printf("\nMenu Utama:\n");
        printf("1. Lihat Menu dan Lakukan Transaksi\n");
        printf("2. Tambah Barang Baru\n");
        printf("3. Keluar\n");
        printf("Pilih menu (1-3): ");
        scanf(" %c", &pilihanMenu);
        getchar();

        switch(pilihanMenu) {
            case '1':
                printf("\nMasukkan nama pelanggan: ");
                fgets(namaPelanggan, 50, stdin);
                namaPelanggan[strcspn(namaPelanggan, "\n")] = 0;

                do {
                    tampilkanMenu();
                    
                    printf("\nMasukkan nomor barang (1-%d): ", jumlahBarang);
                    scanf("%d", &pilihan);
                    
                    if (pilihan < 1 || pilihan > jumlahBarang) {
                        printf("Nomor barang tidak valid! Silakan pilih 1-%d.\n", jumlahBarang);
                        continue;
                    }
                    
                    printf("Masukkan jumlah: ");
                    scanf("%d", &qty);
                    
                    if (qty <= 0) {
                        printf("Jumlah harus lebih dari 0!\n");
                        continue;
                    }
                    
                    strcpy(items[itemCount], menuItems[pilihan-1]);
                    harga[itemCount] = menuHarga[pilihan-1];
                    jumlah[itemCount] = qty;
                    
                    total += hitungTotal(harga[itemCount], jumlah[itemCount]);
                    itemCount++;
                    
                    printf("Barang '%s' berhasil ditambahkan!\n", menuItems[pilihan-1]);
                    printf("Tambah item lagi? (y/n): ");
                    scanf(" %c", &lanjut);
                    
                } while (lanjut == 'y' || lanjut == 'Y');

                pajak = hitungPajak(total);
                grandTotal = total + pajak;

                tampilkanStruk(namaPelanggan, items, harga, jumlah, itemCount, total, pajak, grandTotal);
                
                // PROSES PEMBAYARAN
                prosesPembayaran(grandTotal);
                
                itemCount = 0;
                total = 0;
                break;

            case '2':
                tambahBarangBaru();
                break;

            case '3':
                printf("Terima kasih telah menggunakan program kasir!\n");
                break;

            default:
                printf("Pilihan tidak valid! Silakan pilih 1-3.\n");
        }
    } while (pilihanMenu != '3');

    return 0;
}

void tampilkanMenu() {
    printf("\n========== MENU TOKO ==========\n");
    for (int i = 0; i < jumlahBarang; i++) {
        printf("%d. %-12s - Rp %-6.0f\n", i+1, menuItems[i], menuHarga[i]);
    }
    printf("===============================\n");
}

float hitungTotal(float harga, int jumlah) {
    return harga * jumlah;
}

float hitungPajak(float total) {
    const float PERSEN_PAJAK = 0.1;
    return total * PERSEN_PAJAK;
}

void tampilkanStruk(char namaPelanggan[], char items[][20], float harga[], int jumlah[], int itemCount, float total, float pajak, float grandTotal) {
    printf("\n========== STRUK PEMBELIAN ==========\n");
    printf("Pelanggan: %s\n", namaPelanggan);
    printf("-------------------------------------\n");
    printf("Item\t\tHarga\tJumlah\tSubtotal\n");
    printf("-------------------------------------\n");
    
    for (int i = 0; i < itemCount; i++) {
        printf("%s\t\t%.0f\t%d\t%.0f\n", items[i], harga[i], jumlah[i], harga[i] * jumlah[i]);
    }
    
    printf("-------------------------------------\n");
    printf("Total Belanja: Rp %.0f\n", total);
    printf("Pajak (10%%): Rp %.0f\n", pajak);
    printf("GRAND TOTAL: Rp %.0f\n", grandTotal);
    printf("=====================================\n");
}

void tambahBarangBaru() {
    if (jumlahBarang >= 20) {
        printf("Maaf, kapasitas menu sudah penuh (maksimal 20 barang).\n");
        return;
    }

    char namaBarang[20];
    float hargaBarang;

    printf("\n--- TAMBAH BARANG BARU ---\n");
    
    printf("Masukkan nama barang: ");
    fgets(namaBarang, 20, stdin);
    namaBarang[strcspn(namaBarang, "\n")] = 0;

    printf("Masukkan harga barang: ");
    scanf("%f", &hargaBarang);
    getchar();

    if (hargaBarang <= 0) {
        printf("Harga harus lebih dari 0!\n");
        return;
    }

    strcpy(menuItems[jumlahBarang], namaBarang);
    menuHarga[jumlahBarang] = hargaBarang;
    jumlahBarang++;

    printf(" Barang '%s' berhasil ditambahkan dengan harga Rp %.0f\n", namaBarang, hargaBarang);
    printf("Total barang sekarang: %d\n", jumlahBarang);
}

// FUNGSI BARU: Proses Pembayaran
void prosesPembayaran(float grandTotal) {
    char metodeBayar;
    float jumlahBayar, saldoDebit = 1000000; // Saldo debit default
    float kembalian;
    
    printf("\n=== PROSES PEMBAYARAN ===\n");
    printf("Total yang harus dibayar: Rp %.0f\n", grandTotal);
    
    do {
        printf("\nPilih metode pembayaran:\n");
        printf("1. Tunai\n");
        printf("2. Debit\n");
        printf("Pilihan (1/2): ");
        scanf(" %c", &metodeBayar);
        getchar();
        
        if (metodeBayar != '1' && metodeBayar != '2') {
            printf(" Pilihan tidak valid! Silakan pilih 1 atau 2.\n");
        }
    } while (metodeBayar != '1' && metodeBayar != '2');
    
    switch(metodeBayar) {
        case '1': // TUNAI
            printf("\n--- PEMBAYARAN TUNAI ---\n");
            
            do {
                printf("Masukkan jumlah uang yang dibayarkan: Rp ");
                scanf("%f", &jumlahBayar);
                getchar();
                
                if (jumlahBayar < grandTotal) {
                    float kurang = grandTotal - jumlahBayar;
                    printf(" Uang tidak cukup! Kurang: Rp %.0f\n", kurang);
                    printf("Silakan masukkan jumlah yang cukup.\n");
                }
            } while (jumlahBayar < grandTotal);
            
            kembalian = hitungKembalian(grandTotal, jumlahBayar);
            printf(" Pembayaran berhasil!\n");
            printf("Kembalian: Rp %.0f\n", kembalian);
            break;
            
        case '2': // DEBIT
            printf("\n--- PEMBAYARAN DEBIT ---\n");
            printf("Saldo debit tersedia: Rp %.0f\n", saldoDebit);
            
            if (saldoDebit < grandTotal) {
                float kurang = grandTotal - saldoDebit;
                printf(" Saldo tidak mencukupi!\n");
                printf("Kurang: Rp %.0f\n", kurang);
                printf("Silakan gunakan metode pembayaran lain.\n");
                return;
            }
            
            printf("Memproses pembayaran debit...\n");
            saldoDebit -= grandTotal; // Kurangi saldo
            printf(" Pembayaran debit berhasil!\n");
            printf("Saldo tersisa: Rp %.0f\n", saldoDebit);
            break;
    }
    
    printf("\n TERIMA KASIH TELAH BERBELANJA! \n");
    printf("=====================================\n");
}

// FUNGSI BARU: Hitung Kembalian
float hitungKembalian(float total, float bayar) {
    return bayar - total;
}