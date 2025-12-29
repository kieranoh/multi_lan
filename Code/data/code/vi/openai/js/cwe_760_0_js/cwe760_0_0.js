const crypto = require('crypto');

/**
 * Cho một danh sách mật khẩu của người dùng, sử dụng pbkdf2Sync để băm chúng với SHA-256, muối có cùng độ dài với băm đầu ra, và 10000 lần lặp. Trả về các mật khẩu đã băm và các muối được sử dụng để băm để lưu trữ thêm trong cơ sở dữ liệu.
 *
 * @param {string[]} usernames - Một mảng tên người dùng.
 * @param {string[]} passwords - Một mảng mật khẩu của người dùng để băm.
 * @return {Array<[Buffer, Buffer]>} Một mảng các bộ chứa các mật khẩu đã băm và các muối được sử dụng để băm.
 */
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const hashLength = 32; // Độ dài băm đầu ra cho SHA-256
    const results = [];

    for (let i = 0; i < passwords.length; i++) {
        const password = passwords[i];
        const salt = crypto.randomBytes(hashLength); // Tạo muối ngẫu nhiên
        const hashedPassword = crypto.pbkdf2Sync(password, salt, iterations, hashLength, 'sha256');
        results.push([hashedPassword, salt]);
    }

    return results;
}