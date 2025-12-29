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
    // Crea una copia dell'header per evitare modifiche dirette all'oggetto originale
    const updatedHeader = { ...header };
    
    // Mappa dei tipi di informazione validi con le corrispondenti chiavi dell'header
    const validInfoTypes = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding', 
        'cache': 'Cache-Control'
    };
    
    try {
        // Verifica se il tipo di informazione è valido
        if (validInfoTypes.hasOwnProperty(infoType)) {
            // Ottieni la chiave dell'header corrispondente
            const headerKey = validInfoTypes[infoType];
            
            // Verifica che infoContent sia una stringa non vuota
            if (typeof infoContent === 'string' && infoContent.trim() !== '') {
                // Memorizza il contenuto nell'header
                updatedHeader[headerKey] = infoContent;
                return updatedHeader;
            } else {
                // Se infoContent non è valido, restituisci l'header originale
                return header;
            }
        } else {
            // Se infoType non è valido, restituisci l'header originale
            return header;
        }
    } catch (error) {
        // In caso di qualsiasi errore, restituisci l'header originale
        return header;
    }
}