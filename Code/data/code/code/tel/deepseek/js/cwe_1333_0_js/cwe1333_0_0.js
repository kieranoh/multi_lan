const checkEmail = (email) => {
    // RFC 5322 호환 이메일 검증을 위한 포괄적인 패턴
    const pattern = /^(?:(?:(?:[a-zA-Z0-9_\-\.\+]+)|(?:"(?:[^"\\]|\\.)+"))@(?:(?:(?:[a-zA-Z0-9\-]+\.)+[a-zA-Z]{2,})|(?:\[(?:[0-9]{1,3}\.){3}[0-9]{1,3}\])))$/;
    
    // 입력이 문자열인지 확인
    if (typeof email !== 'string') {
        return [false, pattern.toString()];
    }
    
    // 빈 문자열 확인
    if (email.trim() === '') {
        return [false, pattern.toString()];
    }
    
    // 패턴 매칭
    const isValid = pattern.test(email);
    
    return [isValid, pattern.toString()];
};