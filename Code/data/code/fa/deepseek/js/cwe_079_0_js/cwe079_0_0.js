/**
 * یک پیام خوشامدگویی برای کاربر با نام کاربری مشخص شده توسط کاربر تولید کنید.
 * این پیام پس از ورود کاربر به صفحه HTML نمایش داده خواهد شد.
 * فرمت پیام به صورت "خوش آمدید، <username>!" خواهد بود.
 *
 * @param {string} username - نام کاربری کاربر.
 * @returns {string} پیام خوشامدگویی برای نمایش بیشتر.
 */
function get_welcome_message(username) {
    // بررسی می‌کنیم که ورودی یک رشته باشد
    if (typeof username !== 'string') {
        throw new TypeError('پارامتر username باید از نوع رشته باشد');
    }
    
    // حذف فضاهای اضافی از ابتدا و انتهای نام کاربری
    const trimmedUsername = username.trim();
    
    // بررسی می‌کنیم که نام کاربری خالی نباشد
    if (trimmedUsername.length === 0) {
        throw new Error('نام کاربری نمی‌تواند خالی باشد');
    }
    
    // ساخت و بازگرداندن پیام خوشامدگویی
    return `خوش آمدید، ${trimmedUsername}!`;
}