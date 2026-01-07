/**
 * 제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다.
 * 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다룹니다.
 *
 * @param {string} email - 확인할 이메일입니다.
 * @returns {[boolean, string]} - 첫 번째 요소가 이메일이 유효한지 나타내는 불리언이고
 *                                 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다.
 */
const checkEmail = (email) => {
    // 이메일 패턴 정의
    const patterns = [
        // RFC 5322 공식 표준을 기반으로 한 일반적인 이메일 패턴
        /^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$/,
        
        // 국제화된 도메인 이름(IDN) 및 특수 문자를 포함하는 패턴
        /^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9-]+(?:\.[a-zA-Z0-9-]+)*\.[a-zA-Z]{2,}$/,
        
        // 다중 하위 도메인을 허용하는 패턴 (예: abc.123@def.ghi.com.uk)
        /^[\w.%+-]+@(?:[a-zA-Z0-9-]+\.)+[a-zA-Z]{2,}$/,
        
        // 숫자와 특수 문자를 포함한 로컬 파트를 허용하는 패턴
        /^[\w.!#$%&'*+/=?^_`{|}~-]+@[\w.-]+\.[a-zA-Z]{2,}$/
    ];

    // 입력이 문자열인지 확인
    if (typeof email !== 'string') {
        return [false, 'Invalid input type'];
    }

    // 빈 문자열 또는 공백만 있는 경우 확인
    if (email.trim() === '') {
        return [false, 'Empty email'];
    }

    // 기본적인 구조 검사
    const atIndex = email.indexOf('@');
    if (atIndex <= 0 || atIndex === email.length - 1) {
        return [false, 'Missing or misplaced @ symbol'];
    }

    // 로컬 파트와 도메인 파트 분리
    const localPart = email.substring(0, atIndex);
    const domainPart = email.substring(atIndex + 1);

    // 로컬 파트와 도메인 파트의 기본 검증
    if (localPart.length === 0 || domainPart.length === 0) {
        return [false, 'Empty local or domain part'];
    }

    // 로컬 파트의 시작이나 끝에 점이 있는지 확인
    if (localPart.startsWith('.') || localPart.endsWith('.')) {
        return [false, 'Local part starts or ends with dot'];
    }

    // 연속된 점 확인
    if (localPart.includes('..')) {
        return [false, 'Consecutive dots in local part'];
    }

    // 도메인 파트의 시작이나 끝에 점이 있는지 확인
    if (domainPart.startsWith('.') || domainPart.endsWith('.')) {
        return [false, 'Domain starts or ends with dot'];
    }

    // 도메인에 연속된 점 확인
    if (domainPart.includes('..')) {
        return [false, 'Consecutive dots in domain'];
    }

    // 도메인에 최소 하나의 점이 있는지 확인
    if (!domainPart.includes('.')) {
        return [false, 'Domain missing top-level domain'];
    }

    // 최상위 도메인(TLD) 길이 확인 (최소 2자)
    const tld = domainPart.substring(domainPart.lastIndexOf('.') + 1);
    if (tld.length < 2) {
        return [false, 'Top-level domain too short'];
    }

    // 정의된 패턴으로 이메일 검증 시도
    for (let i = 0; i < patterns.length; i++) {
        if (patterns[i].test(email)) {
            return [true, `Pattern ${i + 1}`];
        }
    }

    // 모든 패턴에 실패한 경우
    return [false, 'No matching pattern'];
};