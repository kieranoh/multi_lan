/**
 * 제공된 이메일 주소가 유효한지 확인합니다.
 * 이 함수는 RFC 5322 표준을 완전히 준수하지는 않지만, 일반적인 이메일 형식을 검증합니다.
 * 
 * @param {string} email - 확인할 이메일입니다.
 * @returns {[boolean, string]} - 첫 번째 요소가 이메일이 유효한지 나타내는 불리언이고, 
 *                                 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다.
 */
const checkEmail = (email) => {
    // 이메일 검증을 위한 정규식 패턴
    // 이 패턴은 다음을 검증합니다:
    // 1. 로컬 파트(골뱅이 앞): 문자, 숫자, 점, 하이픈, 언더스코어, 플러스 허용
    // 2. 도메인 파트(골뱅이 뒤): 문자, 숫자, 하이픈, 점 허용
    // 3. 최상위 도메인: 2-6자의 문자만 허용
    // 4. 점으로 시작하거나 끝나지 않음
    // 5. 연속된 점 없음
    const emailPattern = /^(?!\.)(?!.*\.\.)(?!.*@.*@)[a-zA-Z0-9._%+-]+@(?!\.)[a-zA-Z0-9.-]+\.[a-zA-Z]{2,6}$/;
    
    // 입력값이 문자열인지 확인
    if (typeof email !== 'string') {
        return [false, '유효하지 않은 입력 형식'];
    }
    
    // 이메일 길이 검증 (일반적인 제한: 254자 이하)
    if (email.length > 254) {
        return [false, '이메일이 너무 깁니다 (254자 초과)'];
    }
    
    // 로컬 파트 길이 검증 (일반적인 제한: 64자 이하)
    const atIndex = email.indexOf('@');
    if (atIndex > 64) {
        return [false, '로컬 파트가 너무 깁니다 (64자 초과)'];
    }
    
    // 정규식 패턴으로 검증
    const isValid = emailPattern.test(email);
    
    return [isValid, emailPattern.toString()];
};

// 추가적인 검증을 위한 도우미 함수들
const emailUtils = {
    /**
     * 이메일의 로컬 파트를 추출합니다.
     * @param {string} email - 이메일 주소
     * @returns {string} 로컬 파트
     */
    getLocalPart: (email) => {
        const atIndex = email.indexOf('@');
        return atIndex !== -1 ? email.substring(0, atIndex) : '';
    },
    
    /**
     * 이메일의 도메인 파트를 추출합니다.
     * @param {string} email - 이메일 주소
     * @returns {string} 도메인 파트
     */
    getDomainPart: (email) => {
        const atIndex = email.indexOf('@');
        return atIndex !== -1 ? email.substring(atIndex + 1) : '';
    },
    
    /**
     * 더 엄격한 검증이 필요한 경우 사용할 수 있는 확장된 검증 함수
     * @param {string} email - 확인할 이메일
     * @returns {[boolean, string]} 검증 결과
     */
    strictCheck: (email) => {
        // 더 엄격한 RFC 5322 호환 패턴 (단순화된 버전)
        const strictPattern = /^(?!\.)(?!.*\.\.)(?!.*@.*@)[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}$/;
        
        const [basicValid, basicPattern] = checkEmail(email);
        const strictValid = strictPattern.test(email);
        
        return [basicValid && strictValid, strictPattern.toString()];
    }
};

// 예제 사용법을 보여주는 주석
/*
// 사용 예시:
console.log(checkEmail("abc.123@def.ghi.com.uk")); // [true, "/^(?!\.)(?!.*\.\.)(...)/"]
console.log(checkEmail("invalid-email")); // [false, "/^(?!\.)(?!.*\.\.)(...)/"]
console.log(checkEmail("test@example.com")); // [true, "/^(?!\.)(?!.*\.\.)(...)/"]
console.log(checkEmail("user@subdomain.example.co.uk")); // [true, "/^(?!\.)(?!.*\.\.)(...)/"]
console.log(checkEmail("user.name+tag@example.com")); // [true, "/^(?!\.)(?!.*\.\.)(...)/"]
*/