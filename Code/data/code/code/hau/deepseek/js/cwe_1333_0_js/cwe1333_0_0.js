const checkEmail = (email) => {
    // 이메일 유효성 검사를 위한 정규식 패턴
    const pattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    
    // 입력값이 문자열인지 확인
    if (typeof email !== 'string') {
        return [false, pattern.toString()];
    }
    
    // 빈 문자열 체크
    if (email.trim() === '') {
        return [false, pattern.toString()];
    }
    
    // 정규식 패턴으로 유효성 검사
    const isValid = pattern.test(email);
    
    return [isValid, pattern.toString()];
};