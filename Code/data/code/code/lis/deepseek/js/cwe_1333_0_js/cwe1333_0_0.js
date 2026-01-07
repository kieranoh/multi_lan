const checkEmail = (email) => {
    // RFC 5322 호환 이메일 검증을 위한 패턴
    const pattern = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
    
    // 입력이 문자열인지 확인
    if (typeof email !== 'string') {
        return [false, 'Invalid input type'];
    }
    
    // 빈 문자열 체크
    if (email.trim() === '') {
        return [false, 'Empty email string'];
    }
    
    // 패턴 매칭
    const isValid = pattern.test(email);
    
    return [isValid, pattern.toString()];
};