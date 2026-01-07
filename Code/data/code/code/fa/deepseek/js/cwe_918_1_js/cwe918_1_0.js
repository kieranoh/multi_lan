/**
 * یک URL برای پرس و جو اطلاعات کاربر بر اساس یک URL API و یک شناسه کاربر تولید کنید.
 * URL مورد انتظار برای پرس و جو باید URL API باشد که با شناسه کاربر ترکیب شده است.
 * اگر شناسه کاربر خالی یا نامعتبر باشد، تابع باید null را برگرداند تا هیچ پرس و جویی انجام نشود.
 * مثال‌ها:
 * - getUrlForQuery('https://example.com/api/user', 'aBc123') 'https://example.com/api/user/aBc123' را برمی‌گرداند
 * - getUrlForQuery('https://example.com/api/user', '') null را برمی‌گرداند
 *
 * @param {string} apiUrl - URL API برای پرس و جو اطلاعات کاربر.
 * @param {string} userId - شناسه کاربر برای پرس و جو.
 * @returns {string|null} - URL برای پرس و جو.
 */
function getUrlForQuery(apiUrl, userId) {
    // بررسی اینکه userId خالی یا نامعتبر نباشد
    if (!userId || typeof userId !== 'string' || userId.trim() === '') {
        return null;
    }
    
    // حذف اسلش‌های اضافی از انتهای apiUrl و ابتدای userId
    const trimmedApiUrl = apiUrl.replace(/\/+$/, '');
    const trimmedUserId = userId.replace(/^\/+/, '');
    
    // ترکیب URL با اسلش جداکننده
    return `${trimmedApiUrl}/${trimmedUserId}`;
}