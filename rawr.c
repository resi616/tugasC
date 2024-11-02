#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ANIME 100

typedef struct {
    char nama[50];
    char genre[20];
    int releaseDate;
} Anime;

Anime animeList[MAX_ANIME];
int animeCount = 0;

void loadAnimeData() {
    FILE *file = fopen("dataanime.txt", "r");
    if (file == NULL) {
        printf("File tidak ditemukan.\n");
        return;
    }
    while (fscanf(file, "%49s %19s %d", animeList[animeCount].nama, animeList[animeCount].genre, &animeList[animeCount].releaseDate) != EOF) {
        animeCount++;
    }
    fclose(file);
}

void saveAnimeData() {
    FILE *file = fopen("dataanime.txt", "w");
    for (int i = 0; i < animeCount; i++) {
        fprintf(file, "%s %s %d\n", animeList[i].nama, animeList[i].genre, animeList[i].releaseDate);
    }
    fclose(file);
    printf("Data berhasil disimpan!\n");
}

void inputAnime() {
    if (animeCount >= MAX_ANIME) {
        printf("Kapasitas anime penuh.\n");
        return;
    }

    getchar(); // Menghapus newline dari input sebelumnya

    printf("Masukkan nama anime: ");
    fgets(animeList[animeCount].nama, sizeof(animeList[animeCount].nama), stdin);
    animeList[animeCount].nama[strcspn(animeList[animeCount].nama, "\n")] = 0; // Menghapus newline

    printf("Masukkan genre anime: ");
    fgets(animeList[animeCount].genre, sizeof(animeList[animeCount].genre), stdin);
    animeList[animeCount].genre[strcspn(animeList[animeCount].genre, "\n")] = 0; // Menghapus newline

    printf("Masukkan tahun rilis anime: ");
    scanf("%d", &animeList[animeCount].releaseDate);

    animeCount++;
    printf("Anime berhasil ditambahkan.\n");
}


void viewAnime() {
    if (animeCount == 0) {
        printf("Tidak ada data anime.\n");
        return;
    }
    printf("Daftar Anime:\n");
    for (int i = 0; i < animeCount; i++) {
        printf("%d. Nama: %s | Genre: %s | Tahun Rilis: %d\n",
               i + 1, animeList[i].nama, animeList[i].genre, animeList[i].releaseDate);
    }
}

void sortAnimeByReleaseDate() {
    for (int i = 0; i < animeCount - 1; i++) {
        for (int j = 0; j < animeCount - i - 1; j++) {
            if (animeList[j].releaseDate > animeList[j + 1].releaseDate) {
                Anime temp = animeList[j];
                animeList[j] = animeList[j + 1];
                animeList[j + 1] = temp;
            }
        }
    }
    printf("Anime telah diurutkan berdasarkan tahun rilis.\n");
}


void editAnime() {
    if (animeCount == 0) {
        printf("Tidak ada data anime untuk diedit.\n");
        return;
    }
    int index;
    viewAnime();
    printf("Masukkan nomor anime yang ingin diedit: ");
    scanf("%d", &index);

    if (index < 1 || index > animeCount) {
        printf("Index tidak valid.\n");
        return;
    }
    index--;  // Konversi ke indeks array

    printf("Masukkan nama anime baru: ");
    scanf("%s", animeList[index].nama);
    printf("Masukkan genre anime baru: ");
    scanf("%s", animeList[index].genre);
    printf("Masukkan tahun rilis anime baru: ");
    scanf("%d", &animeList[index].releaseDate);

    printf("Anime berhasil diperbarui.\n");
}


void deleteAnime() {
    if (animeCount == 0) {
        printf("Tidak ada data anime untuk dihapus.\n");
        return;
    }
    int index;
    viewAnime();
    printf("Masukkan nomor anime yang ingin dihapus: ");
    scanf("%d", &index);

    if (index < 1 || index > animeCount) {
        printf("Index tidak valid.\n");
        return;
    }
    index--;  // Konversi ke indeks array

    for (int i = index; i < animeCount - 1; i++) {
        animeList[i] = animeList[i + 1];
    }
    animeCount--;
    printf("Data berhasil dihapus.\n");
}

void menu() {
    int choice;
    do {
        printf("\nSi admin mau ngapain jir:\n");
        printf("1. Input Data Anime\n");
        printf("2. View Anime\n");
        printf("3. Edit Anime\n");
        printf("4. Delete Anime\n");
        printf("5. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inputAnime();
                break;
            case 2:
                viewAnime();
                break;
            case 3:
                editAnime();
                break;
            case 4:
                deleteAnime();
                break;
            case 5:
                saveAnimeData();
                printf("Keluar program.\n");
                break;
            default:
                printf("Pilihan tidak valdi.\n");
        }
    } while (choice != 5);
}

int main() {
    loadAnimeData();
    menu();
    return 0;
}

