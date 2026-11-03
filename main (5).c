
#include <stdio.h>
#include <stdlib.h>

typedef struct Polinom {
    int koef;
    int exp;
    struct Polinom *sljedeci;
} Polinom;

// Dodavanje clana
int dodaj(Polinom **p, int koef, int exp)
{
    Polinom *novi, *temp = *p;

    while (temp != NULL) {
        if (temp->exp == exp) {
            temp->koef += koef;
            return 1;
        }
        temp = temp->sljedeci;
    }

    novi = malloc(sizeof(Polinom));

    if (novi == NULL)
        return 0;

    novi->koef = koef;
    novi->exp = exp;
    novi->sljedeci = *p;
    *p = novi;

    return 1;
}

// Ispis polinoma
int ispisi(Polinom *p)
{
    while (p != NULL) {
        printf("%dx^%d ", p->koef, p->exp);
        p = p->sljedeci;
    }

    printf("\n");
    return 1;
}

// Glavni program
int main()
{
    FILE *f;
    Polinom *p1 = NULL, *p2 = NULL;
    Polinom *z = NULL, *m = NULL;
    Polinom *a, *b;
    int k, e, i;

    f = fopen("polinomi.txt", "r");

    if (f == NULL) {
        printf("Greska!");
        return 1;
    }

    // Ucitavanje prvog polinoma
    for (i = 0; i < 3; i++) {
        fscanf(f, "%d %d", &k, &e);
        dodaj(&p1, k, e);
    }

    // Ucitavanje drugog polinoma
    for (i = 0; i < 3; i++) {
        fscanf(f, "%d %d", &k, &e);
        dodaj(&p2, k, e);
    }

    fclose(f);

    // Zbrajanje
    a = p1;

    while (a != NULL) {
        dodaj(&z, a->koef, a->exp);
        a = a->sljedeci;
    }

    a = p2;

    while (a != NULL) {
        dodaj(&z, a->koef, a->exp);
        a = a->sljedeci;
    }

    // Mnozenje
    a = p1;

    while (a != NULL) {
        b = p2;

        while (b != NULL) {
            dodaj(&m, a->koef * b->koef,
                  a->exp + b->exp);

            b = b->sljedeci;
        }

        a = a->sljedeci;
    }

    printf("Prvi polinom: ");
    ispisi(p1);

    printf("Drugi polinom: ");
    ispisi(p2);

    printf("Zbroj: ");
    ispisi(z);

    printf("Umnozak: ");
    ispisi(m);

    return 0;
}
