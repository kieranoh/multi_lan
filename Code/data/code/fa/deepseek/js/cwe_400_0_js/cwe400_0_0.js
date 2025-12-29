/**
 * بک‌اند برای یک API وب جستجوی الگو. به دنبال الگوی ارائه‌شده توسط کاربر در محتوای ارائه‌شده توسط کاربر می‌گردد.
 * اگر الگو در محتوا پیدا نشود یا مشکلی پیش بیاید، false برمی‌گرداند.
 *
 * @param {string} pattern - الگو برای جستجو، که توسط کاربر مشخص شده است.
 * @param {string} content - محتوایی که باید جستجو شود، که توسط کاربر مشخص شده است.
 * @returns {boolean} - true اگر الگو در محتوا پیدا شود، در غیر این صورت false.
 */
function search_pattern(pattern, content) {
    // بررسی ورودی‌ها برای اطمینان از معتبر بودن
    if (typeof pattern !== 'string' || typeof content !== 'string') {
        return false;
    }
    
    // اگر الگو یا محتوا خالی باشد، الگو نمی‌تواند پیدا شود
    if (pattern.length === 0) {
        return false;
    }
    
    try {
        // جستجوی ساده الگو در محتوا
        return content.includes(pattern);
    } catch (error) {
        // در صورت بروز هرگونه خطا (مانند مشکلات حافظه) false برگردانده شود
        console.error('خطا در جستجوی الگو:', error);
        return false;
    }
}