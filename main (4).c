/* A. Dodavanje novog elementa iza odredene osobe */
int dodajIza(Osoba *head, char *trazenoPrezime,
             char *ime, char *prezime, int godina)
{
    Osoba *trenutni = head;
    Osoba *nova;

    while (trenutni != NULL &&
           strcmp(trenutni->prezime, trazenoPrezime) != 0)
    {
        trenutni = trenutni->sljedeci;
    }

    if (trenutni == NULL)
        return 0;

    nova = malloc(sizeof(Osoba));

    if (nova == NULL)
        return 0;

    strcpy(nova->ime, ime);
    strcpy(nova->prezime, prezime);
    nova->godinaRodjenja = godina;

    nova->sljedeci = trenutni->sljedeci;
    trenutni->sljedeci = nova;

    return 1;
}

/* B. Dodavanje novog elementa ispred odredene osobe */
int dodajIspred(Osoba **head, char *trazenoPrezime,
                char *ime, char *prezime, int godina)
{
    Osoba *trenutni = *head;
    Osoba *prethodni = NULL;
    Osoba *nova;

    while (trenutni != NULL &&
           strcmp(trenutni->prezime, trazenoPrezime) != 0)
    {
        prethodni = trenutni;
        trenutni = trenutni->sljedeci;
    }

    if (trenutni == NULL)
        return 0;

    nova = malloc(sizeof(Osoba));

    if (nova == NULL)
        return 0;

    strcpy(nova->ime, ime);
    strcpy(nova->prezime, prezime);
    nova->godinaRodjenja = godina;

    nova->sljedeci = trenutni;

    if (prethodni == NULL)
        *head = nova;
    else
        prethodni->sljedeci = nova;

    return 1;
}

/* C. Sortiranje liste po prezimenu */
int sortirajListu(Osoba *head)
{
    Osoba *i, *j;
    Osoba privremena;

    if (head == NULL)
        return 0;

    for (i = head; i->sljedeci != NULL; i = i->sljedeci)
    {
        for (j = i->sljedeci; j != NULL; j = j->sljedeci)
        {
            if (strcmp(i->prezime, j->prezime) > 0)
            {
                strcpy(privremena.ime, i->ime);
                strcpy(privremena.prezime, i->prezime);
                privremena.godinaRodjenja = i->godinaRodjenja;

                strcpy(i->ime, j->ime);
                strcpy(i->prezime, j->prezime);
                i->godinaRodjenja = j->godinaRodjenja;

                strcpy(j->ime, privremena.ime);
                strcpy(j->prezime, privremena.prezime);
                j->godinaRodjenja = privremena.godinaRodjenja;
            }
        }
    }

    return 1;
}

/* D. Zapisivanje liste u datoteku */
int zapisiUDatoteku(Osoba *head, char *nazivDatoteke)
{
    FILE *datoteka;
    Osoba *trenutni = head;

    datoteka = fopen(nazivDatoteke, "w");

    if (datoteka == NULL)
        return 0;

    while (trenutni != NULL)
    {
        fprintf(datoteka, "%s %s %d\n",
                trenutni->ime,
                trenutni->prezime,
                trenutni->godinaRodjenja);

        trenutni = trenutni->sljedeci;
    }

    if (fclose(datoteka) != 0)
        return 0;

    return 1;
}

/* E. Citanje liste iz datoteke */
int citajIzDatoteke(Osoba **head, char *nazivDatoteke)
{
    FILE *datoteka;
    Osoba *nova;
    Osoba *zadnji = NULL;

    char ime[30];
    char prezime[30];
    int godina;

    datoteka = fopen(nazivDatoteke, "r");

    if (datoteka == NULL)
        return 0;

    while (fscanf(datoteka, "%29s %29s %d",
                  ime, prezime, &godina) == 3)
    {
        nova = malloc(sizeof(Osoba));

        if (nova == NULL)
        {
            fclose(datoteka);
            return 0;
        }

        strcpy(nova->ime, ime);
        strcpy(nova->prezime, prezime);
        nova->godinaRodjenja = godina;
        nova->sljedeci = NULL;

        if (*head == NULL)
            *head = nova;
        else
            zadnji->sljedeci = nova;

        zadnji = nova;
    }

    if (ferror(datoteka))
    {
        fclose(datoteka);
        return 0;
    }

    fclose(datoteka);

    return 1;
}