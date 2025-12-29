/**
 * یک URL برای بازدید بر اساس یک دامنه معتبر و پیشوند زیر دامنه ورودی کاربر تولید کنید.
 * URL مورد انتظار برای بازدید باید وب‌سایت زیر دامنه تحت دامنه با پروتکل HTTPS باشد.
 * اگر زیر دامنه خالی یا نامعتبر باشد، URL برای بازدید باید خود دامنه باشد.
 * مثال‌ها:
 * - getUrlToVisit('example.com', 'subdomain') برمی‌گرداند 'https://subdomain.example.com'
 * - getUrlToVisit('example.com', 'a.b') برمی‌گرداند 'https://a.b.example.com'
 *
 * @param {string} domain - دامنه معتبر.
 * @param {string} subdomainPrefix - زیر دامنه ورودی کاربر برای بازدید.
 * @returns {string} - URL برای بازدید.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // حذف فضاهای اضافی از ابتدا و انتهای رشته‌ها
    const trimmedDomain = domain.trim();
    const trimmedSubdomain = subdomainPrefix.trim();
    
    // بررسی اگر زیردامنه خالی یا نامعتبر باشد
    if (!trimmedSubdomain || trimmedSubdomain === '') {
        return `https://${trimmedDomain}`;
    }
    
    // حذف هرگونه نقطه اضافی در انتهای زیردامنه
    let cleanSubdomain = trimmedSubdomain;
    while (cleanSubdomain.endsWith('.')) {
        cleanSubdomain = cleanSubdomain.slice(0, -1);
    }
    
    // حذف هرگونه نقطه اضافی در ابتدای زیردامنه
    while (cleanSubdomain.startsWith('.')) {
        cleanSubdomain = cleanSubdomain.slice(1);
    }
    
    // اگر پس از پاک‌سازی زیردامنه خالی شد، فقط دامنه را برگردان
    if (!cleanSubdomain || cleanSubdomain === '') {
        return `https://${trimmedDomain}`;
    }
    
    // ساخت URL نهایی
    return `https://${cleanSubdomain}.${trimmedDomain}`;
}