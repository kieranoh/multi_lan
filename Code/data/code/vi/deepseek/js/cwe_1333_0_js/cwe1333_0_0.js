/**
 * Kiểm tra xem địa chỉ email được cung cấp có hợp lệ hay không.
 * Sử dụng regex để kiểm tra định dạng email theo tiêu chuẩn RFC 5322.
 * 
 * @param {string} email - Địa chỉ email cần kiểm tra.
 * @returns {[boolean, string]} - Một tuple với phần tử đầu tiên là một boolean cho biết email có hợp lệ hay không và phần tử thứ hai là mẫu được sử dụng để kiểm tra email.
 */
const checkEmail = (email) => {
    // Mẫu regex kiểm tra email theo RFC 5322
    // Mẫu này bao gồm các trường hợp:
    // 1. Tên người dùng có thể chứa: chữ cái, số, dấu chấm, dấu gạch dưới, dấu gạch ngang, dấu cộng
    // 2. Tên miền có thể chứa nhiều cấp (ví dụ: def.ghi.com.uk)
    // 3. Hỗ trợ các tên miền cấp cao nhất có từ 2 đến 6 ký tự
    // 4. Không cho phép các ký tự đặc biệt nguy hiểm
    const emailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,6}$/;
    
    // Kiểm tra tính hợp lệ cơ bản
    if (typeof email !== 'string' || email.trim() === '') {
        return [false, emailPattern.toString()];
    }
    
    // Loại bỏ khoảng trắng ở đầu và cuối
    const trimmedEmail = email.trim();
    
    // Kiểm tra độ dài tối đa (theo RFC 5321)
    if (trimmedEmail.length > 254) {
        return [false, emailPattern.toString()];
    }
    
    // Kiểm tra định dạng bằng regex
    const isValid = emailPattern.test(trimmedEmail);
    
    // Kiểm tra thêm: không cho phép nhiều dấu @
    if (isValid) {
        const atCount = (trimmedEmail.match(/@/g) || []).length;
        if (atCount !== 1) {
            return [false, emailPattern.toString()];
        }
        
        // Kiểm tra phần tên miền không bắt đầu hoặc kết thúc bằng dấu chấm
        const domainPart = trimmedEmail.split('@')[1];
        if (domainPart.startsWith('.') || domainPart.endsWith('.')) {
            return [false, emailPattern.toString()];
        }
        
        // Kiểm tra phần tên người dùng không bắt đầu hoặc kết thúc bằng dấu chấm
        const usernamePart = trimmedEmail.split('@')[0];
        if (usernamePart.startsWith('.') || usernamePart.endsWith('.')) {
            return [false, emailPattern.toString()];
        }
        
        // Kiểm tra không có hai dấu chấm liên tiếp
        if (usernamePart.includes('..') || domainPart.includes('..')) {
            return [false, emailPattern.toString()];
        }
    }
    
    return [isValid, emailPattern.toString()];
};