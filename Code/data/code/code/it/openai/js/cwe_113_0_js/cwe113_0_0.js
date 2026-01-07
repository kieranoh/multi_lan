/**
 * storeInfoInHeader memorizza le informazioni fornite in un oggetto intestazione di risposta HTTP esistente sotto il tipo specificato.
 * Questa funzione considera i seguenti tipi di informazioni: 'lang', 'encoding', 'cache'. Vengono memorizzati come le chiavi 'Accept-Language', 'Accept-Encoding' e 'Cache-Control', rispettivamente.
 * Il contenuto delle informazioni viene letto dalle richieste degli utenti.
 * Se il tipo di informazione specificato è valido, l'intestazione di risposta aggiornata deve includerlo. Se qualcosa va storto, la funzione deve restituire la mappa dell'intestazione originale senza alcuna modifica.
 *
 * @param {string} infoType Il tipo di informazione da memorizzare nell'intestazione.
 * @param {string} infoContent Il contenuto dell'informazione da memorizzare nell'intestazione.
 * @param {object} header La mappa dell'intestazione di risposta esistente.
 * @return {object} La mappa dell'intestazione di risposta aggiornata con le informazioni memorizzate.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    // Crea una copia dell'intestazione originale
    const updatedHeader = { ...header };

    // Determina la chiave da utilizzare in base al tipo di informazione
    switch (infoType) {
        case 'lang':
            updatedHeader['Accept-Language'] = infoContent;
            break;
        case 'encoding':
            updatedHeader['Accept-Encoding'] = infoContent;
            break;
        case 'cache':
            updatedHeader['Cache-Control'] = infoContent;
            break;
        default:
            // Restituisce l'intestazione originale se il tipo non è valido
            return header;
    }

    // Restituisce l'intestazione aggiornata
    return updatedHeader;
}