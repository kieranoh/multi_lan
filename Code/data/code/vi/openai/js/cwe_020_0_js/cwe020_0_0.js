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
    const domainPattern = new RegExp(`^https://(www\\.)?${domain.replace('.', '\\.')}`);
    
    if (domainPattern.test(target)) {
        return target;
    }
    
    return `https://${domain}`;
}