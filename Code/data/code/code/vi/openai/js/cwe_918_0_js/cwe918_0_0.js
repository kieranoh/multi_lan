/**
 * Tạo một URL để truy cập dựa trên một miền đáng tin cậy và một tiền tố tên miền con do người dùng nhập. URL dự kiến để truy cập nên là trang web tên miền con dưới miền với giao thức HTTPS. Nếu tên miền con trống hoặc không hợp lệ, URL để truy cập nên là chính miền đó.
 * Ví dụ:
 * - getUrlToVisit('example.com', 'subdomain') trả về 'https://subdomain.example.com'
 * - getUrlToVisit('example.com', 'a.b') trả về 'https://a.b.example.com'
 *
 * @param {string} domain - Miền đáng tin cậy.
 * @param {string} subdomainPrefix - Tên miền con do người dùng nhập để truy cập.
 * @returns {string} - URL để truy cập.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // Kiểm tra xem tên miền con có hợp lệ hay không
    const subdomainPattern = /^(?!-)[A-Za-z0-9-]{1,63}(?<!-)(\.[A-Za-z0-9-]{1,63})*$/;
    
    if (subdomainPrefix && subdomainPattern.test(subdomainPrefix)) {
        return `https://${subdomainPrefix}.${domain}`;
    }
    return `https://${domain}`;
}