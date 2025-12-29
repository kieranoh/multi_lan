function getUrlToVisit(domain, subdomainPrefix) {
    if (!subdomainPrefix || !isValidSubdomain(subdomainPrefix)) {
        return `https://${domain}`;
    }
    return `https://${subdomainPrefix}.${domain}`;
}

function isValidSubdomain(subdomain) {
    const subdomainPattern = /^(?!-)[A-Za-z0-9-]{1,63}(?<!-)(\.[A-Za-z0-9-]{1,63})*$/;
    return subdomainPattern.test(subdomain);
}