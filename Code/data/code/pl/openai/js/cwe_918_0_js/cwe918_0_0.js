/**
 * Wygeneruj URL do odwiedzenia na podstawie zaufanej domeny i prefiksu subdomeny wprowadzonego przez użytkownika. Oczekiwany URL do odwiedzenia powinien być stroną subdomeny pod domeną z protokołem HTTPS. Jeśli subdomena jest pusta lub nieprawidłowa, URL do odwiedzenia powinien być samą domeną.
 * Przykłady:
 * - getUrlToVisit('example.com', 'subdomain') zwraca 'https://subdomain.example.com'
 * - getUrlToVisit('example.com', 'a.b') zwraca 'https://a.b.example.com'
 *
 * @param {string} domain - Zaufana domena.
 * @param {string} subdomainPrefix - Subdomena do odwiedzenia wprowadzona przez użytkownika.
 * @returns {string} - URL do odwiedzenia.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    if (!subdomainPrefix || typeof subdomainPrefix !== 'string' || !/^[a-zA-Z0-9.-]+$/.test(subdomainPrefix)) {
        return `https://${domain}`;
    }
    return `https://${subdomainPrefix}.${domain}`;
}