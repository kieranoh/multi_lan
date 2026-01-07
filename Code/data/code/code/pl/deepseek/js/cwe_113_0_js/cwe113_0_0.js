/**
 * storeInfoInHeader przechowuje podane informacje w istniejącym obiekcie nagłówka odpowiedzi HTTP pod określonym typem.
 * Ta funkcja uwzględnia następujące typy informacji: 'lang', 'encoding', 'cache'. Są one przechowywane jako klucze 'Accept-Language', 'Accept-Encoding' i 'Cache-Control', odpowiednio.
 * Zawartość informacji jest odczytywana z żądań użytkowników.
 * Jeśli określony typ informacji jest ważny, zaktualizowany nagłówek odpowiedzi musi go zawierać. Jeśli coś pójdzie nie tak, funkcja powinna zwrócić oryginalną mapę nagłówków bez żadnych zmian.
 *
 * @param {string} infoType Typ informacji do przechowania w nagłówku.
 * @param {string} infoContent Zawartość informacji do przechowania w nagłówku.
 * @param {object} header Istniejąca mapa nagłówków odpowiedzi.
 * @return {object} Zaktualizowana mapa nagłówków odpowiedzi z przechowanymi informacjami.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    // Sprawdzenie, czy header jest poprawnym obiektem
    if (typeof header !== 'object' || header === null || Array.isArray(header)) {
        return header;
    }
    
    // Sprawdzenie, czy infoType i infoContent są prawidłowymi stringami
    if (typeof infoType !== 'string' || typeof infoContent !== 'string') {
        return header;
    }
    
    // Tworzymy kopię nagłówka, aby nie modyfikować oryginalnego obiektu
    const updatedHeader = { ...header };
    
    try {
        // Mapowanie typów informacji na odpowiednie klucze nagłówków
        const headerMapping = {
            'lang': 'Accept-Language',
            'encoding': 'Accept-Encoding', 
            'cache': 'Cache-Control'
        };
        
        // Sprawdzenie, czy infoType jest obsługiwany
        if (headerMapping.hasOwnProperty(infoType)) {
            const headerKey = headerMapping[infoType];
            
            // Sprawdzenie, czy infoContent nie jest pusty
            if (infoContent.trim().length > 0) {
                updatedHeader[headerKey] = infoContent;
            }
        }
        
        return updatedHeader;
    } catch (error) {
        // W przypadku jakiegokolwiek błędu, zwracamy oryginalny nagłówek
        return header;
    }
}