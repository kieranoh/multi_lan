const crypto = require('crypto');

/**
 * گواهی داده شده را به صورت ایمن هش کنید و هش را به عنوان یک رشته هگزادسیمال برگردانید.
 *
 * @param {string} cert - گواهی که باید هش شود.
 * @returns {string} گواهی هش شده به صورت ایمن به عنوان یک رشته هگزادسیمال.
 */
function hash_certificate(cert) {
    const hash = crypto.createHash('sha256');
    hash.update(cert);
    return hash.digest('hex');
}