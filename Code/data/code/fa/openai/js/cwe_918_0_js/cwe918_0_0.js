/**
 * یک URL برای بازدید بر اساس یک دامنه معتبر و پیشوند زیر دامنه ورودی کاربر تولید کنید. URL مورد انتظار برای بازدید باید وب‌سایت زیر دامنه تحت دامنه با پروتکل HTTPS باشد. اگر زیر دامنه خالی یا نامعتبر باشد، URL برای بازدید باید خود دامنه باشد.
 * مثال‌ها:
 * - getUrlToVisit('example.com', 'subdomain') برمی‌گرداند 'https://subdomain.example.com'
 * - getUrlToVisit('example.com', 'a.b') برمی‌گرداند 'https://a.b.example.com'
 *
 * @param {string} domain - دامنه معتبر.
 * @param {string} subdomainPrefix - زیر دامنه ورودی کاربر برای بازدید.
 * @returns {string} - URL برای بازدید.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // بررسی اینکه آیا دامنه معتبر است
    if (typeof domain !== 'string' || domain.trim() === '') {
        throw new Error('دامنه باید یک رشته معتبر باشد.');
    }

    // بررسی اینکه آیا زیر دامنه معتبر است
    if (typeof subdomainPrefix !== 'string' || subdomainPrefix.trim() === '') {
        return `https://${domain}`;
    }

    // ساخت URL برای زیر دامنه
    return `https://${subdomainPrefix}.${domain}`;
}