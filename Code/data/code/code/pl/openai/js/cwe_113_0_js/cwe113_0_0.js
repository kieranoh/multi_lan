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
    // Sprawdzanie poprawności typów informacji
    if (typeof infoType !== 'string' || typeof infoContent !== 'string' || typeof header !== 'object' || header === null) {
        return header; // Zwraca oryginalną mapę nagłówków w przypadku błędu
    }
    
    // Mapowanie typów informacji na odpowiednie nagłówki
    const headerMap = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    };
    
    // Sprawdzanie, czy infoType jest ważne
    if (headerMap[infoType]) {
        header[headerMap[infoType]] = infoContent; // Aktualizacja nagłówka
    }
    
    return header; // Zwracanie zaktualizowanej mapy nagłówków
}