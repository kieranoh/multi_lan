/**
 * Tạo một URL để truy cập dựa trên một miền đáng tin cậy và một tiền tố tên miền con do người dùng nhập.
 * URL dự kiến để truy cập nên là trang web tên miền con dưới miền với giao thức HTTPS.
 * Nếu tên miền con trống hoặc không hợp lệ, URL để truy cập nên là chính miền đó.
 * 
 * @param {string} domain - Miền đáng tin cậy.
 * @param {string} subdomainPrefix - Tên miền con do người dùng nhập để truy cập.
 * @returns {string} - URL để truy cập.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // Kiểm tra nếu domain không hợp lệ
    if (!domain || typeof domain !== 'string' || domain.trim() === '') {
        return 'https://';
    }
    
    // Loại bỏ khoảng trắng thừa
    const cleanDomain = domain.trim();
    const cleanSubdomainPrefix = subdomainPrefix ? subdomainPrefix.trim() : '';
    
    // Kiểm tra nếu subdomainPrefix trống hoặc không hợp lệ
    if (!cleanSubdomainPrefix || cleanSubdomainPrefix === '') {
        return `https://${cleanDomain}`;
    }
    
    // Xây dựng URL với subdomain prefix
    return `https://${cleanSubdomainPrefix}.${cleanDomain}`;
}