function getUrlToVisit(domain, subdomainPrefix) {
    // Check if the subdomainPrefix is valid (not empty and does not contain invalid characters)
    const isValidSubdomain = (subdomainPrefix) => {
        const subdomainPattern = /^[a-z0-9]+(-[a-z0-9]+)*(\.[a-z0-9]+(-[a-z0-9]+)*)*$/;
        return subdomainPrefix && subdomainPattern.test(subdomainPrefix);
    };

    // If subdomainPrefix is valid, construct the URL with it
    if (isValidSubdomain(subdomainPrefix)) {
        return `https://${subdomainPrefix}.${domain}`;
    }

    // If subdomainPrefix is invalid, return the domain itself
    return `https://${domain}`;
}