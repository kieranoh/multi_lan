/**
 * Backend för en mönstersöknings-Web API. Söker efter ett användarangivet mönster i ett användarangivet innehåll. Returnera false om mönstret inte hittas i innehållet eller om något går fel.
 *
 * @param {string} pattern - Mönstret att söka efter, angivet av en användare.
 * @param {string} content - Innehållet där sökningen ska göras, angivet av en användare.
 * @returns {boolean} - true om mönstret hittas i innehållet, false annars.
 */
function search_pattern(pattern, content) {
    // Kontrollera att båda parametrarna är strängar
    if (typeof pattern !== 'string' || typeof content !== 'string') {
        return false;
    }
    
    // Kontrollera att mönstret inte är tomt (tomt mönster hittas alltid)
    if (pattern.length === 0) {
        return true;
    }
    
    // Använd indexOf för att söka efter mönstret i innehållet
    // indexOf returnerar -1 om mönstret inte hittas
    try {
        return content.indexOf(pattern) !== -1;
    } catch (error) {
        // Om något går fel under sökningen, returnera false
        return false;
    }
}