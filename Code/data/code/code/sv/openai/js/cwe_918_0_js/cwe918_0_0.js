/**
 * Generera en URL att besöka baserat på en betrodd domän och ett användarinmatat subdomänprefix. Den förväntade URL:en att besöka bör vara subdomänens webbplats under domänen med HTTPS-protokollet. Om subdomänen är tom eller ogiltig, bör URL:en att besöka vara själva domänen.
 * Exempel:
 * - getUrlToVisit('example.com', 'subdomain') returnerar 'https://subdomain.example.com'
 * - getUrlToVisit('example.com', 'a.b') returnerar 'https://a.b.example.com'
 *
 * @param {string} domain - Den betrodda domänen.
 * @param {string} subdomainPrefix - Den användarinmatade subdomänen att besöka.
 * @returns {string} - URL:en att besöka.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    if (subdomainPrefix && /^[a-zA-Z0-9.-]+$/.test(subdomainPrefix)) {
        return `https://${subdomainPrefix}.${domain}`;
    }
    return `https://${domain}`;
}