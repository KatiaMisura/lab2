#define _CRT_SECURE_NO_WARNINGS  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct osoba {
    char ime[30];
    char prezime[30];
    int godina;
    struct osoba* sljedeci;
} Osoba;


void dodajNaPocetak(Osoba** lista) {
    Osoba* nova = (Osoba*)malloc(sizeof(Osoba));

    if (nova == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return;
    }

    printf("Unesi ime: ");
    scanf("%29s", nova->ime);

    printf("Unesi prezime: ");
    scanf("%29s", nova->prezime);

    printf("Unesi godinu rodenja: ");
    scanf("%d", &nova->godina);

    nova->sljedeci = *lista;
    *lista = nova;
}


void ispisiListu(Osoba* lista) {
    if (lista == NULL) {
        printf("Lista je prazna.\n");
        return;
    }

    while (lista != NULL) {
        printf("%s %s, godina rodenja: %d\n",
            lista->ime, lista->prezime, lista->godina);

        lista = lista->sljedeci;
    }
}


void dodajNaKraj(Osoba** lista) {
    Osoba* nova = (Osoba*)malloc(sizeof(Osoba));

    if (nova == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return;
    }

    printf("Unesi ime: ");
    scanf("%29s", nova->ime);

    printf("Unesi prezime: ");
    scanf("%29s", nova->prezime);

    printf("Unesi godinu rodenja: ");
    scanf("%d", &nova->godina);

    nova->sljedeci = NULL;

    if (*lista == NULL) {
        *lista = nova;
        return;
    }

    Osoba* tekuca = *lista;

    while (tekuca->sljedeci != NULL) {
        tekuca = tekuca->sljedeci;
    }

    tekuca->sljedeci = nova;
}


Osoba* pronadiOsobu(Osoba* lista, char prezime[]) {
    while (lista != NULL) {
        if (strcmp(lista->prezime, prezime) == 0) {
            return lista;
        }

        lista = lista->sljedeci;
    }

    return NULL;
}


void obrisiOsobu(Osoba** lista, char prezime[]) {
    Osoba* tekuca = *lista;
    Osoba* prethodna = NULL;

    while (tekuca != NULL &&
        strcmp(tekuca->prezime, prezime) != 0) {
        prethodna = tekuca;
        tekuca = tekuca->sljedeci;
    }

    if (tekuca == NULL) {
        printf("Osoba nije pronadena.\n");
        return;
    }

    if (prethodna == NULL) {
        *lista = tekuca->sljedeci;
    }
    else {
        prethodna->sljedeci = tekuca->sljedeci;
    }

    free(tekuca);
    printf("Osoba je uspjesno obrisana.\n");
}


int main(void) {
    Osoba* lista = NULL;
    Osoba* pronadena;
    char prezime[30];
    int izbor;

    do {
        printf("\n--- IZBORNIK ---\n");
        printf("1. Dodaj osobu na pocetak\n");
        printf("2. Ispisi listu\n");
        printf("3. Dodaj osobu na kraj\n");
        printf("4. Pronadi osobu po prezimenu\n");
        printf("5. Obrisi osobu po prezimenu\n");
        printf("0. Izlaz\n");
        printf("Odabir: ");
        scanf("%d", &izbor);

        switch (izbor) {
        case 1:
            dodajNaPocetak(&lista);
            break;

        case 2:
            ispisiListu(lista);
            break;

        case 3:
            dodajNaKraj(&lista);
            break;

        case 4:
            printf("Unesi prezime za pretragu: ");
            scanf("%29s", prezime);

            pronadena = pronadiOsobu(lista, prezime);

            if (pronadena != NULL) {
                printf("Pronadena osoba: %s %s, godina rodenja: %d\n",
                    pronadena->ime,
                    pronadena->prezime,
                    pronadena->godina);
            }
            else {
                printf("Osoba nije pronadena.\n");
            }
            break;

        case 5:
            printf("Unesi prezime za brisanje: ");
            scanf("%29s", prezime);
            obrisiOsobu(&lista, prezime);
            break;

        case 0:
            printf("Kraj programa.\n");
            break;

        default:
            printf("Neispravan odabir!\n");
        }

    } while (izbor != 0);

    
    while (lista != NULL) {
        Osoba* zaBrisanje = lista;
        lista = lista->sljedeci;
        free(zaBrisanje);
    }

    return 0;
}
