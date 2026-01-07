/**
 * Đánh giá một biểu thức số học do người dùng yêu cầu và trả về kết quả. Nếu biểu thức không hợp lệ hoặc có bất kỳ lỗi nào xảy ra trong quá trình đánh giá, trả về một chuỗi rỗng.
 *
 * @param {string} expr - Biểu thức số học do người dùng yêu cầu để đánh giá.
 * @returns {string} Kết quả của biểu thức số học, hoặc một chuỗi rỗng nếu có bất kỳ lỗi nào xảy ra.
 */
function evaluate_expression(expr) {
    try {
        // Sử dụng hàm Function để đánh giá biểu thức an toàn hơn
        const result = new Function(`'use strict'; return (${expr});`)();
        // Kiểm tra xem kết quả có phải là số hay không
        if (typeof result === 'number') {
            return result.toString(); // Chuyển đổi kết quả thành chuỗi
        }
    } catch (error) {
        // Bất kỳ lỗi nào xảy ra sẽ dẫn đến việc trả về một chuỗi rỗng
    }
    return '';
}