Descrizione
Cinematrix è un semplice programma in linguaggio C per gestire una piccola videoteca digitale.
Il software permette di memorizzare informazioni sui film, effettuare ricerche, ordinare la libreria e salvare i dati su file binario.

Le principali caratteristiche includono:

Gestione dinamica di un catalogo di film tramite struct e puntatori.

Salvataggio e caricamento dei dati su file binario (catalogo.dat).

Aggiunta di nuovi film con allocazione dinamica della memoria.

Visualizzazione dei film in formato tabellare.

Ricerca per titolo.

Ordinamento della libreria per anno di uscita.

Pulizia automatica della memoria prima della chiusura.

Funzionalità
Il programma presenta il seguente menu:

--- CINEMATRIX ---

Aggiungi film

Visualizza catalogo

Cerca film per titolo

Ordina libreria per anno

Salva ed esci
Scelta: _

Dettagli

Aggiungi film: inserimento di titolo, regista, anno e durata. La memoria viene allocata dinamicamente.

Visualizza catalogo: mostra tutti i film presenti in memoria.

Cerca film per titolo: ricerca dei film in base a una stringa fornita.

Ordina libreria per anno: ordina i film in ordine crescente per anno di uscita.

Salva ed esci: salva tutti i film in catalogo.dat e libera la memoria allocata.
