function getUrlToVisit(domain, subdomainPrefix) {
    if (!domain || typeof domain !== 'string') {
        throw new Error('Invalid domain');
    }
    if (!subdomainPrefix || typeof subdomainPrefix !== 'string' || subdomainPrefix.trim() === '') {
        return `https://${domain}`;
    }

    const subdomains = subdomainPrefix.split('.');
    const validSubdomains = subdomains.filter(subdomain => /^[a-zA-Z0-9-]+$/.test(subdomain));

    if (validSubdomains.length === 0) {
        return `https://${domain}`;
    }

    return `https://${validSubdomains.join('.')}.${domain}`;
}