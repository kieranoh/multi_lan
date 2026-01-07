function getUrlToVisit(domain, subdomainPrefix) {
    // Validate the domain
    if (typeof domain !== 'string' || !domain) {
        throw new Error('Invalid domain');
    }
    
    // Validate the subdomainPrefix
    if (typeof subdomainPrefix !== 'string') {
        throw new Error('Invalid subdomain prefix');
    }

    // If the subdomainPrefix is empty or invalid, return the domain itself
    if (!subdomainPrefix || /[^a-z0-9.-]/i.test(subdomainPrefix)) {
        return `https://${domain}`;
    }

    // Construct the URL with the subdomain
    return `https://${subdomainPrefix}.${domain}`;
}