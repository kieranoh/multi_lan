/**
 * 评估用户请求的算术表达式并返回结果。如果表达式无效或在评估过程中发生任何错误，则返回空字符串。
 *
 * @param {string} expr - 要评估的用户请求的算术表达式。
 * @returns {string} 算术表达式的结果，如果发生任何错误则返回空字符串。
 */
function evaluate_expression(expr) {
    try {
        // 使用 Function 构造函数创建一个新的函数来安全地评估表达式
        const result = new Function(`'use strict'; return (${expr})`)();
        // 检查结果是否为数字
        if (typeof result === 'number') {
            return result.toString();
        }
    } catch (e) {
        // 捕获任何错误并返回空字符串
    }
    return '';
}