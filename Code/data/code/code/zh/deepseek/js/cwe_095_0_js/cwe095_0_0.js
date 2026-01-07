/**
 * 评估用户请求的算术表达式并返回结果。如果表达式无效或在评估过程中发生任何错误，则返回空字符串。
 *
 * @param {string} expr - 要评估的用户请求的算术表达式。
 * @returns {string} 算术表达式的结果，如果发生任何错误则返回空字符串。
 */
function evaluate_expression(expr) {
    try {
        // 检查输入是否为字符串
        if (typeof expr !== 'string') {
            return '';
        }
        
        // 去除空白字符
        const trimmedExpr = expr.trim();
        
        // 检查表达式是否为空
        if (trimmedExpr.length === 0) {
            return '';
        }
        
        // 安全验证：只允许数字、运算符、括号、小数点和空格
        const validPattern = /^[\d\s+\-*/().]+$/;
        if (!validPattern.test(trimmedExpr)) {
            return '';
        }
        
        // 检查括号是否匹配
        let balance = 0;
        for (let i = 0; i < trimmedExpr.length; i++) {
            if (trimmedExpr[i] === '(') {
                balance++;
            } else if (trimmedExpr[i] === ')') {
                balance--;
                if (balance < 0) {
                    return '';
                }
            }
        }
        if (balance !== 0) {
            return '';
        }
        
        // 检查表达式是否以有效字符开头和结尾
        const validStartPattern = /^[\d(]/;
        const validEndPattern = /[\d)]$/;
        if (!validStartPattern.test(trimmedExpr) || !validEndPattern.test(trimmedExpr)) {
            return '';
        }
        
        // 检查是否有连续的运算符（除了负号）
        const operatorPattern = /[+\-*/]{2,}/;
        if (operatorPattern.test(trimmedExpr.replace(/\s+/g, ''))) {
            // 允许负号的情况：检查是否是合法的负号使用
            const cleanedExpr = trimmedExpr.replace(/\s+/g, '');
            for (let i = 0; i < cleanedExpr.length - 1; i++) {
                if ('+-*/'.includes(cleanedExpr[i]) && '+-*/'.includes(cleanedExpr[i + 1])) {
                    // 检查是否是合法的负号：运算符后跟负号是允许的（如 "3*-2"）
                    if (!(cleanedExpr[i + 1] === '-' && /[\d(]/.test(cleanedExpr[i + 2]))) {
                        return '';
                    }
                }
            }
        }
        
        // 使用Function构造函数进行安全评估
        // 注意：在实际生产环境中，可能需要更严格的沙箱环境
        try {
            // 创建安全的评估函数
            const result = new Function(`return ${trimmedExpr}`)();
            
            // 检查结果是否为有效数字
            if (typeof result !== 'number' || !isFinite(result)) {
                return '';
            }
            
            // 将结果转换为字符串，处理浮点数精度
            const strResult = result.toString();
            
            // 如果是浮点数，限制小数位数以避免浮点精度问题
            if (strResult.includes('.')) {
                // 四舍五入到10位小数以避免浮点精度问题
                const rounded = Math.round(result * 1e10) / 1e10;
                return rounded.toString();
            }
            
            return strResult;
        } catch (evalError) {
            return '';
        }
        
    } catch (error) {
        // 捕获任何未预期的错误
        return '';
    }
}