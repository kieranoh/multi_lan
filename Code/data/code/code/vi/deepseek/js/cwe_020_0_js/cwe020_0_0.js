/**
 * Kiểm tra xem chuỗi URL mục tiêu được cung cấp có nằm trong miền được cung cấp hay không.
 * Nếu có, trả về URL mục tiêu để chuyển hướng; nếu không, quay lại URL miền để chuyển hướng.
 * Sử dụng giao thức https.
 *
 * Ví dụ:
 *  get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
 *  get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
 *  get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
 *  get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'
 *
 * @param {string} target - Chuỗi URL mục tiêu.
 * @param {string} domain - Chuỗi miền, không có giao thức.
 * @returns {string} Chuỗi URL để chuyển hướng.
 */
function get_target_for_redirect(target, domain) {
    try {
        // Tạo đối tượng URL từ chuỗi mục tiêu
        const targetUrl = new URL(target);
        
        // Kiểm tra xem miền của URL mục tiêu có kết thúc bằng miền được cung cấp không
        // Điều này cho phép các subdomain như music.example.com khớp với example.com
        if (targetUrl.hostname === domain || targetUrl.hostname.endsWith('.' + domain)) {
            // Nếu URL mục tiêu đã sử dụng https, giữ nguyên; nếu không, chuyển sang https
            return targetUrl.protocol === 'https:' ? targetUrl.toString() : `https://${targetUrl.hostname}${targetUrl.pathname}${targetUrl.search}${targetUrl.hash}`;
        } else {
            // Nếu không khớp, trả về URL miền với giao thức https
            return `https://${domain}`;
        }
    } catch (error) {
        // Nếu chuỗi mục tiêu không phải là URL hợp lệ, trả về URL miền với giao thức https
        return `https://${domain}`;
    }
}