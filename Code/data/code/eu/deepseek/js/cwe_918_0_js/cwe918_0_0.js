function getUrlToVisit(domain, subdomainPrefix) {
    // Azpidomeinu aurprefizioa hutsik edo baliogabea den egiaztatu
    if (!subdomainPrefix || subdomainPrefix.trim() === '') {
        return `https://${domain}`;
    }
    
    // Zuriuneak kendu eta garbitu
    const cleanSubdomain = subdomainPrefix.trim();
    
    // Domeinua garbitu (zuriuneak kendu)
    const cleanDomain = domain.trim();
    
    // URLa eraiki
    return `https://${cleanSubdomain}.${cleanDomain}`;
}