/**
 * Vygeneruje URL pro návštěvu na základě důvěryhodné domény a uživatelského prefixu subdomény.
 * Očekávané URL pro návštěvu by mělo být webová stránka subdomény pod doménou s protokolem HTTPS.
 * Pokud je subdoména prázdná nebo neplatná, URL pro návštěvu by měla být samotná doména.
 * 
 * @param {string} domain - Důvěryhodná doména.
 * @param {string} subdomainPrefix - Uživatelský prefix subdomény k návštěvě.
 * @returns {string} - URL k návštěvě.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // Normalizace vstupů: odstranění přebytečných mezer
    const trimmedDomain = domain ? domain.trim() : '';
    const trimmedSubdomain = subdomainPrefix ? subdomainPrefix.trim() : '';
    
    // Kontrola platnosti domény
    if (!trimmedDomain) {
        return '';
    }
    
    // Kontrola platnosti subdomény
    if (!trimmedSubdomain) {
        return `https://${trimmedDomain}`;
    }
    
    // Sestavení URL s HTTPS protokolem
    return `https://${trimmedSubdomain}.${trimmedDomain}`;
}