#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Osoba {
    char ime[30];
    char prezime[30];
    int godinaRodjenja;
    struct Osoba *sljedeci;
}Osoba;

int main()
{
    struct Osoba *head = NULL;
    struct Osoba *nova;
    struct Osoba *trenutni;
    struct Osoba *prethodni;

    /*Dodavanje novog elementa na pocetak liste*/

    nova = malloc(sizeof(struct Osoba));

    strcpy(nova->ime, "Ivan");
    strcpy(nova->prezime, "Ivic");
    nova->godinaRodjenja = 2000;

    nova->sljedeci = head;
    head = nova;


    nova = malloc(sizeof(struct Osoba));

    strcpy(nova->ime, "Marko");
    strcpy(nova->prezime, "Markovic");
    nova->godinaRodjenja = 1999;

    nova->sljedeci = head;
    head = nova;


    /*Dodavanje novog elementa na kraj liste*/

    nova = malloc(sizeof(struct Osoba));

    strcpy(nova->ime, "Ana");
    strcpy(nova->prezime, "Anic");
    nova->godinaRodjenja = 2001;

    nova->sljedeci = NULL;

    trenutni = head;

    while (trenutni->sljedeci != NULL)
    {
        trenutni = trenutni->sljedeci;
    }

    trenutni->sljedeci = nova;


    /*Ispisivanje liste*/

    printf("Lista osoba:\n");

    trenutni = head;

    while (trenutni != NULL)
    {
        printf("%s %s - %d\n",
               trenutni->ime,
               trenutni->prezime,
               trenutni->godinaRodjenja);

        trenutni = trenutni->sljedeci;
    }


    /*Sortiranje osoba po prezimenu*/

    printf("\nPretraga po prezimenu:\n");

    trenutni = head;

    while (trenutni != NULL)
    {
        if (strcmp(trenutni->prezime, "Anic") == 0)
        {
            printf("Pronadena osoba: %s %s - %d\n",
                   trenutni->ime,
                   trenutni->prezime,
                   trenutni->godinaRodjenja);
            break;
        }

        trenutni = trenutni->sljedeci;
    }


    /*Brisanje osobe po prezimenu*/

    trenutni = head;
    prethodni = NULL;

    while (trenutni != NULL)
    {
        if (strcmp(trenutni->prezime, "Ivic") == 0)
        {
            if (prethodni == NULL)
            {
                head= trenutni->sljedeci;
            }
            else
            {
                prethodni->sljedeci = trenutni->sljedeci;
            }

            free(trenutni);
            break;
        }

        prethodni = trenutni;
        trenutni = trenutni->sljedeci;
    }



    printf("\nLista nakon brisanja:\n");

    trenutni = head;

    while (trenutni != NULL)
    {
        printf("%s %s - %d\n",
               trenutni->ime,
               trenutni->prezime,
               trenutni->godinaRodjenja);

        trenutni = trenutni->sljedeci;
    }


    /* free(mem) */

    trenutni = head;

    while (trenutni != NULL)
    {
        nova = trenutni;
        trenutni = trenutni->sljedeci;
        free(nova);
    }

    return 0;
}