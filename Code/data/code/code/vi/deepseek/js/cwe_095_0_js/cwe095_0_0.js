/**
 * Đánh giá một biểu thức số học do người dùng yêu cầu và trả về kết quả. Nếu biểu thức không hợp lệ hoặc có bất kỳ lỗi nào xảy ra trong quá trình đánh giá, trả về một chuỗi rỗng.
 *
 * @param {string} expr - Biểu thức số học do người dùng yêu cầu để đánh giá.
 * @returns {string} Kết quả của biểu thức số học, hoặc một chuỗi rỗng nếu có bất kỳ lỗi nào xảy ra.
 */
function evaluate_expression(expr) {
    try {
        // Kiểm tra đầu vào
        if (typeof expr !== 'string' || expr.trim() === '') {
            return '';
        }

        // Loại bỏ khoảng trắng
        const trimmedExpr = expr.trim();
        
        // Kiểm tra các ký tự không hợp lệ
        // Cho phép: số, dấu thập phân, toán tử + - * /, dấu ngoặc, khoảng trắng
        const validChars = /^[\d+\-*/().\s]+$/;
        if (!validChars.test(trimmedExpr)) {
            return '';
        }

        // Kiểm tra cặp ngoặc
        const stack = [];
        for (let i = 0; i < trimmedExpr.length; i++) {
            if (trimmedExpr[i] === '(') {
                stack.push('(');
            } else if (trimmedExpr[i] === ')') {
                if (stack.length === 0) {
                    return ''; // Ngoặc đóng không có ngoặc mở tương ứng
                }
                stack.pop();
            }
        }
        if (stack.length > 0) {
            return ''; // Ngoặc mở không có ngoặc đóng tương ứng
        }

        // Kiểm tra biểu thức không hợp lệ như "5++3" hoặc "*/5"
        const invalidPatterns = [
            /[\+\-\*\/]{2,}/, // Hai toán tử liên tiếp
            /^[\*\/]/,        // Bắt đầu bằng * hoặc /
            /[\+\-\*\/]$/,    // Kết thúc bằng toán tử
            /\([\+\-\*\/]/,   // Toán tử ngay sau ngoặc mở
            /[\+\-\*\/]\)/,   // Toán tử ngay trước ngoặc đóng
            /\.\d*\./,        // Hai dấu thập phân trong một số
            /\d+\.\d+\.\d+/   // Nhiều dấu thập phân
        ];
        
        for (const pattern of invalidPatterns) {
            if (pattern.test(trimmedExpr)) {
                return '';
            }
        }

        // Thay thế các ký hiệu để xử lý số âm
        let processedExpr = trimmedExpr;
        
        // Xử lý số âm: thay thế "-(" thành "-1*("
        processedExpr = processedExpr.replace(/-\(/g, '-1*(');
        
        // Xử lý số âm ở đầu biểu thức
        if (processedExpr.startsWith('-')) {
            processedExpr = '0' + processedExpr;
        }
        
        // Xử lý số âm sau toán tử
        processedExpr = processedExpr.replace(/([\+\-\*\/])-/g, '$1-1*');

        // Sử dụng Function constructor để đánh giá biểu thức
        // Lưu ý: Điều này có rủi ro bảo mật trong môi trường thực tế
        // Nhưng phù hợp với yêu cầu bài toán
        const result = new Function('return ' + processedExpr)();
        
        // Kiểm tra kết quả hợp lệ
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // Làm tròn để tránh lỗi dấu phẩy động
        const roundedResult = Math.round(result * 1e12) / 1e12;
        
        // Trả về kết quả dưới dạng chuỗi
        return String(roundedResult);
        
    } catch (error) {
        // Bắt mọi lỗi và trả về chuỗi rỗng
        return '';
    }
}