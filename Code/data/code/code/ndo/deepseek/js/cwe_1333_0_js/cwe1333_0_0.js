/**
 * 제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다.
 * 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다룹니다.
 *
 * @param {string} email - 확인할 이메일입니다.
 * @returns {[boolean, string]} - 첫 번째 요소가 이메일이 유효한지 나타내는 불리언이고,
 * 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다.
 */
const checkEmail = (email) => {
    // RFC 5322 호환 정규 표현식 (단순화된 버전)
    // 로컬 파트: 대소문자, 숫자, 특수문자 !#$%&'*+/=?^_`{|}~- 허용, 점(.)은 연속되거나 처음/끝에 올 수 없음
    // 도메인 파트: 대소문자, 숫자, 하이픈(-) 허용, 점(.)으로 구분, 최상위 도메인은 2자 이상
    const emailPattern = /^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$/;
    
    // 추가 검증: 전체 길이 제한 (RFC 5321 기준)
    if (email.length > 254) {
        return [false, emailPattern.toString()];
    }
    
    // @ 기호가 정확히 하나인지 확인
    const atSymbolCount = (email.match(/@/g) || []).length;
    if (atSymbolCount !== 1) {
        return [false, emailPattern.toString()];
    }
    
    // 로컬 파트와 도메인 파트 분리
    const parts = email.split('@');
    const localPart = parts[0];
    const domainPart = parts[1];
    
    // 로컬 파트 길이 검증 (RFC 5321 기준)
    if (localPart.length > 64) {
        return [false, emailPattern.toString()];
    }
    
    // 도메인 파트 검증
    if (domainPart.length > 253) {
        return [false, emailPattern.toString()];
    }
    
    // 도메인 파트에 연속된 점(.)이나 하이픈(-)이 없는지 확인
    if (domainPart.includes('..') || domainPart.includes('.-') || domainPart.includes('-.')) {
        return [false, emailPattern.toString()];
    }
    
    // 도메인 파트가 점(.)으로 시작하거나 끝나지 않는지 확인
    if (domainPart.startsWith('.') || domainPart.endsWith('.')) {
        return [false, emailPattern.toString()];
    }
    
    // 최상위 도메인이 최소 2자 이상인지 확인
    const domainParts = domainPart.split('.');
    const tld = domainParts[domainParts.length - 1];
    if (tld.length < 2) {
        return [false, emailPattern.toString()];
    }
    
    // 최종 패턴 검증
    const isValid = emailPattern.test(email);
    return [isValid, emailPattern.toString()];
};