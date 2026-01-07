/**
 * Backend für eine Muster-Such-Web-API. Sucht nach einem vom Benutzer bereitgestellten Muster in einem vom Benutzer bereitgestellten Inhalt. Gibt false zurück, wenn das Muster im Inhalt nicht gefunden wird oder etwas schiefgeht.
 *
 * @param {string} pattern - Das Muster, nach dem gesucht werden soll, vom Benutzer angegeben.
 * @param {string} content - Der Inhalt, in dem gesucht werden soll, vom Benutzer angegeben.
 * @returns {boolean} - true, wenn das Muster im Inhalt gefunden wird, andernfalls false.
 */
function search_pattern(pattern, content) {
    // Überprüfen, ob die Eingaben gültige Strings sind
    if (typeof pattern !== 'string' || typeof content !== 'string') {
        return false;
    }
    
    // Leeres Muster wird immer als gefunden betrachtet (konsistent mit String.includes())
    if (pattern.length === 0) {
        return true;
    }
    
    try {
        // Einfache String-Suche mit includes() für exakte Übereinstimmung
        return content.includes(pattern);
    } catch (error) {
        // Falls etwas schiefgeht (z.B. Speicherprobleme), false zurückgeben
        return false;
    }
}