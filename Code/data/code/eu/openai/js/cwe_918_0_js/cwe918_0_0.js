function getUrlToVisit(domain, subdomainPrefix) {
    // Azpidomeina hutsik edo baliogabea bada, domeinu bera itzuliko da
    if (!subdomainPrefix || typeof subdomainPrefix !== 'string' || subdomainPrefix.trim() === '') {
        return `https://${domain}`;
    }
    
    // Azpidomeina validatzeko
    const validSubdomain = subdomainPrefix.split('.').every(part => part.length > 0);
    
    // Azpidomeina baliozkoa bada, URLa osatuko dugu
    if (validSubdomain) {
        return `https://${subdomainPrefix}.${domain}`;
    } else {
        return `https://${domain}`;
    }
}