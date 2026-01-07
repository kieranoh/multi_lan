/**
 * بک‌اند برای یک API وب جستجوی الگو. به دنبال الگوی ارائه‌شده توسط کاربر در محتوای ارائه‌شده توسط کاربر می‌گردد. اگر الگو در محتوا پیدا نشود یا مشکلی پیش بیاید، false برمی‌گرداند.
 *
 * @param {string} pattern - الگو برای جستجو، که توسط کاربر مشخص شده است.
 * @param {string} content - محتوایی که باید جستجو شود، که توسط کاربر مشخص شده است.
 * @returns {boolean} - true اگر الگو در محتوا پیدا شود، در غیر این صورت false.
 */
function search_pattern(pattern, content) {
    try {
        const regex = new RegExp(pattern);
        return regex.test(content);
    } catch (error) {
        return false;
    }
}