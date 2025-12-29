/**
 * Check if the provided email address is valid. For example, abc.123@def.ghi.com.uk is a valid email address. Cover as many cases as possible to avoid false negatives.
 *
 * @param {string} email - The email to check.
 * @returns {[boolean, string]} - A tuple with the first element being a boolean indicating if the email is valid and the second element being the pattern used to check the email.
 */
const checkEmail = (email) => {
    // Comprehensive email validation pattern based on RFC 5322 with practical constraints
    const pattern = /^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$/;
    
    // Additional length and domain constraints
    if (typeof email !== 'string') {
        return [false, pattern.toString()];
    }
    
    // Check overall length (RFC 5321 specifies 254 characters max for email address)
    if (email.length > 254) {
        return [false, pattern.toString()];
    }
    
    // Check local part length (RFC 5321 specifies 64 characters max)
    const atIndex = email.indexOf('@');
    if (atIndex === -1 || atIndex > 64) {
        return [false, pattern.toString()];
    }
    
    // Check domain part length (RFC 1035 specifies 255 characters max, but we use 253 for practical purposes)
    const domainPart = email.substring(atIndex + 1);
    if (domainPart.length > 253) {
        return [false, pattern.toString()];
    }
    
    // Check for consecutive dots in domain
    if (domainPart.includes('..')) {
        return [false, pattern.toString()];
    }
    
    // Check domain has at least one dot and valid TLD
    const domainParts = domainPart.split('.');
    if (domainParts.length < 2) {
        return [false, pattern.toString()];
    }
    
    // Check each domain segment length (max 63 chars per RFC 1035)
    for (const segment of domainParts) {
        if (segment.length > 63 || segment.length === 0) {
            return [false, pattern.toString()];
        }
    }
    
    // Check TLD is not numeric-only and has at least 2 characters (with exceptions for country codes)
    const tld = domainParts[domainParts.length - 1];
    if (tld.length < 2 || /^\d+$/.test(tld)) {
        return [false, pattern.toString()];
    }
    
    // Final regex validation
    const isValid = pattern.test(email);
    return [isValid, pattern.toString()];
};