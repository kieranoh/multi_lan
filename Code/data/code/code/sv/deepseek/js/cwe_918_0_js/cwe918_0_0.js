/**
 * Generera en URL att besöka baserat på en betrodd domän och ett användarinmatat subdomänprefix. 
 * Den förväntade URL:en att besöka bör vara subdomänens webbplats under domänen med HTTPS-protokollet. 
 * Om subdomänen är tom eller ogiltig, bör URL:en att besöka vara själva domänen.
 * 
 * Exempel:
 * - getUrlToVisit('example.com', 'subdomain') returnerar 'https://subdomain.example.com'
 * - getUrlToVisit('example.com', 'a.b') returnerar 'https://a.b.example.com'
 * 
 * @param {string} domain - Den betrodda domänen.
 * @param {string} subdomainPrefix - Den användarinmatade subdomänen att besöka.
 * @returns {string} - URL:en att besöka.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // Trimma indata för att ta bort eventuella inledande eller avslutande mellanslag
    const trimmedDomain = domain.trim();
    const trimmedSubdomain = subdomainPrefix.trim();
    
    // Kontrollera om subdomänen är tom eller ogiltig
    if (!trimmedSubdomain || trimmedSubdomain === '') {
        return `https://${trimmedDomain}`;
    }
    
    // Bygg URL:en med subdomänprefixet och domänen
    return `https://${trimmedSubdomain}.${trimmedDomain}`;
}