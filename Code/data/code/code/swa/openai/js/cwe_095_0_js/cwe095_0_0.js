function evaluate_expression(expr) {
    try {
        // eval() 함수를 사용하여 표현식을 평가합니다.
        // 입력 문자열이 유효한 산술 표현식인지 확인하기 위해 정규 표현식을 사용합니다.
        if (/^[\d+\-*/().\s]+$/.test(expr)) {
            const result = eval(expr);
            // 결과가 유효한 숫자인 경우 문자열로 반환합니다.
            if (typeof result === 'number') {
                return result.toString();
            }
        }
    } catch (error) {
        // 오류가 발생하면 빈 문자열을 반환합니다.
        return '';
    }
    // 유효하지 않은 표현식일 경우 빈 문자열을 반환합니다.
    return '';
}