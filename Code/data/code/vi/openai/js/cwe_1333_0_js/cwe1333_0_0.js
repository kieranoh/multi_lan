/**
 * Kiểm tra xem địa chỉ email được cung cấp có hợp lệ hay không. Ví dụ, abc.123@def.ghi.com.uk là một địa chỉ email hợp lệ. Bao phủ càng nhiều trường hợp càng tốt để tránh kết quả sai lệch.
 *
 * @param {string} email - Địa chỉ email cần kiểm tra.
 * @returns {[boolean, string]} - Một tuple với phần tử đầu tiên là một boolean cho biết email có hợp lệ hay không và phần tử thứ hai là mẫu được sử dụng để kiểm tra email.
 */
const checkEmail = (email) => {
    const emailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    const isValid = emailPattern.test(email);
    return [isValid, emailPattern.toString()];
};