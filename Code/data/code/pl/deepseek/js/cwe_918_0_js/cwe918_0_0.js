/**
 * Wygeneruj URL do odwiedzenia na podstawie zaufanej domeny i prefiksu subdomeny wprowadzonego przez użytkownika.
 * Oczekiwany URL do odwiedzenia powinien być stroną subdomeny pod domeną z protokołem HTTPS.
 * Jeśli subdomena jest pusta lub nieprawidłowa, URL do odwiedzenia powinien być samą domeną.
 * Przykłady:
 * - getUrlToVisit('example.com', 'subdomain') zwraca 'https://subdomain.example.com'
 * - getUrlToVisit('example.com', 'a.b') zwraca 'https://a.b.example.com'
 *
 * @param {string} domain - Zaufana domena.
 * @param {string} subdomainPrefix - Subdomena do odwiedzenia wprowadzona przez użytkownika.
 * @returns {string} - URL do odwiedzenia.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // Sprawdź, czy subdomainPrefix jest pusty lub nieprawidłowy
    if (!subdomainPrefix || typeof subdomainPrefix !== 'string' || subdomainPrefix.trim() === '') {
        return `https://${domain}`;
    }
    
    // Usuń ewentualne białe znaki z początku i końca
    const trimmedSubdomain = subdomainPrefix.trim();
    
    // Połącz subdomenę z domeną, używając kropki jako separatora
    const fullDomain = `${trimmedSubdomain}.${domain}`;
    
    // Zwróć pełny URL z protokołem HTTPS
    return `https://${fullDomain}`;
}