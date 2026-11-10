
#include <stdio.h>
#include <stdlib.h>

typedef struct Cvor {
    double vrijednost;
    struct Cvor *sljedeci;
} Cvor;

// Dodavanje elementa na vrh stoga
int push(Cvor **vrh, double vrijednost) {
    Cvor *novi = malloc(sizeof(Cvor));

    if (novi == NULL)
        return 0;

    novi->vrijednost = vrijednost;
    novi->sljedeci = *vrh;
    *vrh = novi;

    return 1;
}

// Uklanjanje elementa s vrha stoga
int pop(Cvor **vrh, double *vrijednost) {
    if (*vrh == NULL)
        return 0;

    Cvor *pom = *vrh;

    *vrijednost = pom->vrijednost;
    *vrh = pom->sljedeci;

    free(pom);

    return 1;
}

// Oslobadanje cijelog stoga
int oslobodi(Cvor **vrh) {
    Cvor *pom;

    while (*vrh != NULL) {
        pom = *vrh;
        *vrh = (*vrh)->sljedeci;
        free(pom);
    }

    return 1;
}

// Provjera je li znak operator
int operator(char znak) {
    return znak == '+' || znak == '-' ||
           znak == '*' || znak == '/';
}

// Racunanje postfiksnog izraza
int izracunaj(FILE *datoteka, double *rezultat) {
    Cvor *vrh = NULL;

    char token[100];
    char *kraj;

    double a, b, broj;

    while (fscanf(datoteka, "%99s", token) == 1) {

        broj = strtod(token, &kraj);

        if (kraj != token && *kraj == '\0') {

            if (!push(&vrh, broj)) {
                printf("Greska pri alokaciji memorije!\n");
                oslobodi(&vrh);
                return 0;
            }
        }

        else if (token[1] == '\0' && operator(token[0])) {

            if (!pop(&vrh, &b) || !pop(&vrh, &a)) {
                printf("Greska: nedovoljan broj operanada!\n");
                oslobodi(&vrh);
                return 0;
            }

            switch (token[0]) {
                case '+':
                    broj = a + b;
                    break;

                case '-':
                    broj = a - b;
                    break;

                case '*':
                    broj = a * b;
                    break;

                case '/':
                    if (b == 0) {
                        printf("Greska: dijeljenje s nulom!\n");
                        oslobodi(&vrh);
                        return 0;
                    }

                    broj = a / b;
                    break;
            }

            if (!push(&vrh, broj)) {
                printf("Greska pri alokaciji memorije!\n");
                oslobodi(&vrh);
                return 0;
            }
        }

        else {
            printf("Greska: neispravan token %s!\n", token);
            oslobodi(&vrh);
            return 0;
        }
    }

    if (ferror(datoteka)) {
        printf("Greska pri citanju datoteke!\n");
        oslobodi(&vrh);
        return 0;
    }

    if (!pop(&vrh, rezultat)) {
        printf("Greska: prazan ili neispravan izraz!\n");
        oslobodi(&vrh);
        return 0;
    }

    if (vrh != NULL) {
        printf("Greska: visak operanada!\n");
        oslobodi(&vrh);
        return 0;
    }

    oslobodi(&vrh);

    return 1;
}

int main() {
    FILE *datoteka;
    double rezultat;

    datoteka = fopen("izraz.txt", "r");

    if (datoteka == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        return 1;
    }

    if (izracunaj(datoteka, &rezultat)) {
        printf("Rezultat je: %.2f\n", rezultat);
    }

    fclose(datoteka);

    return 0;
}
