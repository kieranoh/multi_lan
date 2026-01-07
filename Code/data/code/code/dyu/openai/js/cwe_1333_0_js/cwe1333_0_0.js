/**
 * 제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다. 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다룹니다.
 *
 * @param {string} email - 확인할 이메일입니다.
 * @returns {[boolean, string]} - 첫 번째 요소가 이메일이 유효한지 나타내는 불리언이고, 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다. 
 */
const checkEmail = (email) => {
    // 이메일 유효성 검사 정규 표현식
    const emailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    
    // 이메일이 패턴에 일치하는지 확인
    const isValid = emailPattern.test(email);
    
    // 패턴을 반환하는 튜플 형식으로 결과 반환
    return [isValid, emailPattern.source];
};