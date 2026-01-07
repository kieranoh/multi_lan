const crypto = require('crypto');

/**
 * گواهی داده شده را به صورت ایمن هش کنید و هش را به عنوان یک رشته هگزادسیمال برگردانید.
 *
 * @param {string} cert - گواهی که باید هش شود.
 * @returns {string} گواهی هش شده به صورت ایمن به عنوان یک رشته هگزادسیمال.
 */
function hash_certificate(cert) {
    // بررسی اینکه ورودی یک رشته غیر خالی است
    if (typeof cert !== 'string' || cert.trim().length === 0) {
        throw new Error('ورودی باید یک رشته غیر خالی باشد');
    }

    // ایجاد هش SHA-256 از گواهی
    const hash = crypto.createHash('sha256');
    hash.update(cert, 'utf8');
    
    // بازگرداندن هش به صورت رشته هگزادسیمال
    return hash.digest('hex');
}