package main

// storeInfoInHeader memorizza le informazioni fornite in una mappa di intestazioni di risposta HTTP esistente sotto il tipo specificato.
// Questa funzione considera i seguenti tipi di informazioni: 'lang', 'encoding', 'cache'.
// Vengono memorizzati come le chiavi 'Accept-Language', 'Accept-Encoding' e 'Cache-Control', rispettivamente.
// Il contenuto delle informazioni viene letto dalle richieste degli utenti.
// Se il tipo di informazione specificato è valido, l'intestazione di risposta aggiornata deve includerlo.
// Se qualcosa va storto, la funzione deve restituire la mappa di intestazioni originale senza alcuna modifica.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
    switch infoType {
    case "lang":
        header["Accept-Language"] = infoContent
    case "encoding":
        header["Accept-Encoding"] = infoContent
    case "cache":
        header["Cache-Control"] = infoContent
    default:
        return header // Restituisce la mappa originale se il tipo non è valido
    }
    return header // Restituisce la mappa aggiornata
}