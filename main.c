#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_BODOVA 100

typedef struct Student {
    char ime[50];
    char prezime[50];
    int bodovi;
};

int main() {
    FILE *dat;
    struct Student *studenti;
    int n = 0;
    int i;
    char redak[200];
    float relativni_bodovi;

    dat = fopen("studenti.txt", "r");

    if (dat == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        return 1;
    }

    while (fgets(redak, sizeof(redak), dat) != NULL) {
        n++;
    }

    fseek(dat, 0, SEEK_SET);

    studenti = (struct Student *)malloc(n * sizeof(struct Student));

    if (studenti == NULL && n > 0) {
        printf("Greska pri alokaciji memorije!\n");
        fclose(dat);
        return 1;
    }

    for (i = 0; i < n; i++) {
        if (fscanf(dat, "%49s %49s %d",
                   studenti[i].ime,
                   studenti[i].prezime,
                   &studenti[i].bodovi) != 3) {
            printf("Greska pri citanju podataka!\n");
            free(studenti);
            fclose(dat);
            return 1;
        }
    }

    printf("Ime\tPrezime\tBodovi\tRelativni bodovi\n");

    for (i = 0; i < n; i++) {
        relativni_bodovi =
            (float)studenti[i].bodovi / MAX_BODOVA * 100;

        printf("%s\t%s\t%d\t%.2f%%\n",
               studenti[i].ime, studenti[i].prezime,
               studenti[i].bodovi, relativni_bodovi);
    }

    fclose(dat);
    free(studenti);

    return 0;
}
