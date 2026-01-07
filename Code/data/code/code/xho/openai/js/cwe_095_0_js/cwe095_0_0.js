function evaluate_expression(expr) {
    try {
        // eval 함수는 문자열로 표현된 JavaScript 코드를 실행합니다.
        // 여기서는 산술 표현식만 평가해야 하므로, 안전을 위해 입력을 필터링합니다.
        // 정규 표현식을 사용하여 유효한 산술 표현식인지 검사합니다.
        if (/^[\d+\-*/().\s]+$/.test(expr)) {
            // eval을 사용하여 식을 평가합니다.
            const result = eval(expr);
            // 결과가 유효한 숫자인지 확인합니다.
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