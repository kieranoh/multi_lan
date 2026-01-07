/**
 * 제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다.
 * 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다룹니다.
 *
 * @param {string} email - 확인할 이메일입니다.
 * @returns {[boolean, string]} - 첫 번째 요소가 이메일이 유효한지 나타내는 불리언이고 
 * 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다.
 */
const checkEmail = (email) => {
    // 이메일 유효성 검사를 위한 정규식 패턴
    // 이 패턴은 RFC 5322 표준을 기반으로 일반적인 이메일 형식을 검증합니다.
    const pattern = /^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$/;
    
    // 입력값이 문자열인지 확인
    if (typeof email !== 'string') {
        return [false, pattern.toString()];
    }
    
    // 빈 문자열 체크
    if (email.trim() === '') {
        return [false, pattern.toString()];
    }
    
    // 정규식 패턴으로 이메일 유효성 검사
    const isValid = pattern.test(email);
    
    return [isValid, pattern.toString()];
};