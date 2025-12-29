/**
 * 사용자 요청 수학 표현식을 평가하고 결과를 반환합니다. 표현식이 유효하지 않거나 평가 중 오류가 발생하면 빈 문자열을 반환합니다.
 *
 * @param {string} expr - 평가할 사용자 요청 수학 표현식.
 * @returns {string} 수학 표현식의 결과, 또는 오류가 발생하면 빈 문자열.
 */
function evaluate_expression(expr) {
    // 입력 검증: expr이 문자열이 아니거나 비어있으면 빈 문자열 반환
    if (typeof expr !== 'string' || expr.trim() === '') {
        return '';
    }

    // 잠재적으로 위험한 문자나 패턴을 제거하여 보안 강화
    const sanitizedExpr = expr.replace(/[^0-9+\-*/().\s]/g, '');
    if (sanitizedExpr !== expr) {
        return ''; // 허용되지 않은 문자가 포함된 경우 빈 문자열 반환
    }

    try {
        // 괄호 짝이 맞는지 확인
        const stack = [];
        for (let char of sanitizedExpr) {
            if (char === '(') {
                stack.push(char);
            } else if (char === ')') {
                if (stack.length === 0) {
                    return ''; // 닫는 괄호가 여는 괄호보다 많은 경우
                }
                stack.pop();
            }
        }
        if (stack.length !== 0) {
            return ''; // 여는 괄호가 닫는 괄호보다 많은 경우
        }

        // 표현식 평가
        // 주의: eval은 보안상 위험할 수 있으므로, 신뢰할 수 없는 입력에는 사용하지 않는 것이 좋습니다.
        // 여기서는 이미 입력 검증을 거쳤으므로 사용합니다.
        const result = eval(sanitizedExpr);

        // 결과가 유효한 숫자인지 확인
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }

        // 결과를 문자열로 변환하여 반환
        return String(result);
    } catch (error) {
        // 평가 중 발생한 모든 오류에 대해 빈 문자열 반환
        return '';
    }
}