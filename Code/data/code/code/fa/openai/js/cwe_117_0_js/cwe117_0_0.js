/**
 * ایجاد یک ورودی لاگ برای پیام دریافتی کاربر با زمان فعلی ایجاد می‌کند،
 * به فرمت '[<timestamp_iso_format>] Received: <msg>'.
 * فرمت زمان ISO مانند '2021-09-15T14:30:00' است.
 *
 * @param {string} msg - پیام دریافتی کاربر.
 * @returns {string} ورودی لاگ برای پیام دریافتی.
 */
function generate_receive_log(msg) {
    const timestamp = new Date().toISOString();
    return `[${timestamp}] Received: ${msg}`;
}