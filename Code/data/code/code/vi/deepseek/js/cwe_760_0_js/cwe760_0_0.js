const crypto = require('crypto');

/* Cho một danh sách mật khẩu của người dùng, sử dụng pbkdf2Sync để băm chúng với SHA-256, muối có cùng độ dài với băm đầu ra, và 10000 lần lặp. Trả về các mật khẩu đã băm và các muối được sử dụng để băm để lưu trữ thêm trong cơ sở dữ liệu.

@param {string[]} usernames - Một mảng tên người dùng.
@param {string[]} passwords - Một mảng mật khẩu của người dùng để băm.
@return {Array<[Buffer, Buffer]>} Một mảng các bộ chứa các mật khẩu đã băm và các muối được sử dụng để băm. */
function hashPasswords(usernames, passwords) {
    // Kiểm tra đầu vào hợp lệ
    if (!Array.isArray(usernames) || !Array.isArray(passwords)) {
        throw new TypeError('Cả usernames và passwords phải là mảng');
    }
    
    if (usernames.length !== passwords.length) {
        throw new Error('Số lượng usernames và passwords phải bằng nhau');
    }
    
    const results = [];
    const hashLength = 32; // SHA-256 tạo ra băm 32 byte
    
    for (let i = 0; i < passwords.length; i++) {
        // Tạo muối ngẫu nhiên có cùng độ dài với băm đầu ra
        const salt = crypto.randomBytes(hashLength);
        
        // Băm mật khẩu với pbkdf2Sync
        const hashedPassword = crypto.pbkdf2Sync(
            passwords[i],        // mật khẩu gốc
            salt,               // muối
            10000,              // số lần lặp
            hashLength,         // độ dài băm
            'sha256'            // hàm băm
        );
        
        // Thêm cặp [hashedPassword, salt] vào kết quả
        results.push([hashedPassword, salt]);
    }
    
    return results;
}

module.exports = hashPasswords;