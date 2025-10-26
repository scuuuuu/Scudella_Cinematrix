#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char titolo[100];
    char autore[100];
    int anno;
    float durata;
} Film;

static char *const filename = "../catalogo.dat";

int file_esiste(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (f) {
        return 1;
    }
    return 0;
}

Film *leggi_file(const char *filename, int *dim) {
    FILE *filebin = fopen(filename, "rb");
    if (filebin == NULL) {
        printf("ERRORE LETTURA FILE");
        *dim = 0;
        return NULL;
    }

    fread(dim,sizeof(int),1,filebin);

    Film *catalogo = malloc(sizeof(Film)*(*dim));
        if (catalogo == NULL) {
            printf("ERRORE ALLOCAZIONE MEMORIA");
            fclose(filebin);
            *dim =0;
            return NULL;
        }
    fread(catalogo,sizeof(Film),*dim,filebin);
    fclose(filebin);
    return catalogo;
}

void scrivi_file(const char *filename, int dim, Film *catalogo) {
    FILE *filewr = fopen(filename, "wb");
    if (filewr == NULL) {
        printf("ERRORE LETTURA FILE");
        return;
    }

    fwrite(&dim,sizeof(int),1,filewr);
    fwrite(catalogo,sizeof(Film),dim,filewr);
    fclose(filewr);
}
Film *aggiungi_film(Film *catalogo, char *titolo, char *autore, int *dim, int anno, float durata) {
    (*dim)++;
    Film *film = realloc(catalogo,sizeof(Film)*(*dim));
    if (film == NULL) {
        printf("ERRORE ALLOCAZIONE MEMORIA");
        free(catalogo);
        exit(1);
    }
    catalogo = film;

    strncpy(catalogo[*dim-1].titolo, titolo,sizeof(catalogo[*dim-1].titolo));
    strncpy(catalogo[*dim-1].autore,autore,sizeof(catalogo[*dim-1].autore));
    catalogo[*dim-1].anno = anno;
    catalogo[*dim-1].durata = durata;

    return catalogo;
}

void stampa_film(Film *catalogo,int dim) {
    for (int i = 0;i < dim;i++) {
        printf("Titolo: %s \n", catalogo[i].titolo);
        printf("Autore: %s \n", catalogo[i].autore);
        printf("Anno: %d \n", catalogo[i].anno);
        printf("Durata: %.2f \n", catalogo[i].durata);
        printf("--------------------------\n");
    }
}

void ordina_anno(Film *catalogo, int dim) {
    for(int i=0;i<dim-1;i++) {
        for(int j=0;j<dim-1-i;j++) {
            if(catalogo[j].anno > catalogo[j+1].anno) {
                Film temp = catalogo[j];
                catalogo[j] = catalogo[j+1];
                catalogo[j+1] = temp;
            }
        }
    }
}


void cerca_riferimento(Film *catalogo,int dim,char *riferimento) {
    if (dim == 0) {
        printf("Il catalogo è vuoto");
        return;
    }
    int trovato = 0;
    for (int i = 0;i < dim;i++) {
        if (strstr(catalogo[i].titolo, riferimento)) {
            printf("Titolo: %s \n", catalogo[i].titolo);
            printf("Autore: %s \n", catalogo[i].autore);
            printf("Anno: %d \n", catalogo[i].anno);
            printf("Durata: %.2f \n", catalogo[i].durata);
            trovato = 1;
        }
    }
    if (!trovato) {
        printf("Nessun film trovato con il seguente titolo: %s",riferimento);
    }
}
int main(void) {
    int dimensione =0;
    Film *catalogo = NULL;
    if (file_esiste(filename)) {
    catalogo = leggi_file(filename,&dimensione);
    }
    else {
        catalogo = malloc(sizeof(Film)*(dimensione));
    }
    if (catalogo == NULL) {
        printf("ERRORE ALLOCAZIONE MEMORIA");
        free(catalogo);
        exit(1);
    }

    int scelta;
    do {
        printf("-----BENVENUTO AL CINEMATRIX-----\n");
        printf("Inserisci la tua scelta: \n");
        printf("1- Aggiungi film: \n");
        printf("2- Visualizza Catalogo: \n");
        printf("3- Cerca per titolo: \n");
        printf("4- Ordina libreria per anno: \n");
        printf("5- Salva ed esci: \n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        switch (scelta) {
            case 1:
                char titolo[100];
                char autore[100];
                int anno;
                float durata;
                printf("Inserisci il titolo del film: ");
                scanf(" %[^\n]", titolo);
                printf("Inserisci l'autore: ");
                scanf(" %[^\n]", autore);
                printf("Inserisci l'anno del film: ");
                scanf("%d", &anno);
                printf("Inserisci la durata del film: ");
                scanf("%f", &durata);
                catalogo = aggiungi_film(catalogo, titolo, autore, &dimensione, anno, durata);
                scrivi_file(filename,dimensione,catalogo);
                break;
            case 2:
                printf("---CATALOGO CINEMATRIX---\n");
                stampa_film(catalogo, dimensione);
                break;
            case 3:
                char riferimento[100];
                printf("Inserisci il titolo di riferimento: ");
                scanf(" %[^\n]", riferimento);
                cerca_riferimento(catalogo,dimensione,riferimento);
                break;
            case 4:
                ordina_anno(catalogo, dimensione);
                scrivi_file(filename,dimensione,catalogo);
                break;
            case 5:
                printf(("Salvato... Uscita in corso..."));

        }
    }while (scelta>0 && scelta <5 && scelta != 5);
    free(catalogo);
    return 0;

}
