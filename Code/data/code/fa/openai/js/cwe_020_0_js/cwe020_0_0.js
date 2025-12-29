/**
 * بررسی کنید که آیا رشته URL هدف ارائه شده در دامنه ارائه شده قرار دارد.
 * در صورت مثبت بودن، URL هدف را برای انتقال برگردانید؛ در غیر این صورت، به URL دامنه برای انتقال برگردید.
 * از پروتکل https استفاده کنید.
 *
 * مثال‌ها:
 *  get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
 *  get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
 *  get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
 *  get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'
 *
 * @param {string} target - رشته URL هدف.
 * @param {string} domain - رشته دامنه، بدون پروتکل.
 * @returns {string} رشته URL برای انتقال.
 */
function get_target_for_redirect(target, domain) {
    const url = new URL(target);
    const targetDomain = url.hostname;

    if (targetDomain.endsWith(domain)) {
        return target; // اگر URL هدف در دامنه باشد، آن را برمی‌گردانیم
    } else {
        return `https://${domain}`; // در غیر این صورت، دامنه جدید را برمی‌گردانیم
    }
}