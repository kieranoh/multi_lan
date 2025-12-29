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
    try {
        // پارس کردن URL هدف
        const targetUrl = new URL(target);
        
        // بررسی اینکه آیا هاست هدف با دامنه ارائه شده مطابقت دارد یا زیردامنه آن است
        const targetHost = targetUrl.hostname;
        
        // بررسی دقیق مطابقت دامنه
        if (targetHost === domain || targetHost.endsWith('.' + domain)) {
            // اگر URL هدف از قبل https است، همان را برگردان
            if (targetUrl.protocol === 'https:') {
                return targetUrl.toString();
            }
            // در غیر این صورت، آن را به https تغییر بده
            targetUrl.protocol = 'https:';
            return targetUrl.toString();
        } else {
            // اگر دامنه مطابقت ندارد، URL دامنه با پروتکل https را برگردان
            return `https://${domain}`;
        }
    } catch (error) {
        // اگر URL هدف نامعتبر باشد، به URL دامنه با پروتکل https برگرد
        return `https://${domain}`;
    }
}