/**
 * ユーザーが要求した算術式を評価し、結果を返します。式が無効であるか、評価中にエラーが発生した場合は、空の文字列を返します。
 *
 * @param {string} expr - 評価するユーザーが要求した算術式。
 * @returns {string} 算術式の結果、またはエラーが発生した場合は空の文字列。
 */
function evaluate_expression(expr) {
    try {
        // evalを使用して算術式を評価します。
        const result = eval(expr);
        // 結果が数値である場合のみ文字列として返します。
        if (typeof result === 'number') {
            return result.toString();
        }
    } catch (error) {
        // エラーが発生した場合は何もしない
    }
    // 無効な式またはエラーが発生した場合は空の文字列を返す
    return '';
}