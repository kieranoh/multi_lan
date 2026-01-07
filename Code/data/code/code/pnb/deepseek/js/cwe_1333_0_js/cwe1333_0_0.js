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
    // 이 패턴은 RFC 5322 표준을 완벽히 준수하지는 않지만, 일반적인 이메일 형식을 검증합니다.
    const emailPattern = /^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$/;
    
    // 추가 검증: 도메인 부분에 최소한 하나의 점이 있어야 하며,
    // 점 뒤에 최소한 2자 이상의 알파벳이 있어야 합니다.
    const domainPattern = /@[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?)+$/;
    
    // 이메일 길이 검증 (RFC 5321 기준: 로컬파트 64자 + @ + 도메인 255자 = 최대 320자)
    if (email.length > 320) {
        return [false, "길이 초과"];
    }
    
    // 로컬파트(골뱅이 앞부분)와 도메인 부분 분리
    const atIndex = email.indexOf('@');
    if (atIndex === -1 || atIndex === 0 || atIndex === email.length - 1) {
        return [false, "@ 위치 오류"];
    }
    
    const localPart = email.substring(0, atIndex);
    const domainPart = email.substring(atIndex + 1);
    
    // 로컬파트 길이 검증 (최대 64자)
    if (localPart.length > 64) {
        return [false, "로컬파트 길이 초과"];
    }
    
    // 도메인 길이 검증 (최대 255자)
    if (domainPart.length > 255) {
        return [false, "도메인 길이 초과"];
    }
    
    // 로컬파트가 점으로 시작하거나 끝나지 않는지 확인
    if (localPart.startsWith('.') || localPart.endsWith('.')) {
        return [false, "로컬파트 점 위치 오류"];
    }
    
    // 연속된 점이 없는지 확인
    if (localPart.includes('..')) {
        return [false, "연속된 점"];
    }
    
    // 도메인 부분 검증
    if (domainPart.startsWith('.') || domainPart.endsWith('.')) {
        return [false, "도메인 점 위치 오류"];
    }
    
    if (domainPart.includes('..')) {
        return [false, "도메인 연속된 점"];
    }
    
    // 도메인에 최소한 하나의 점이 있는지 확인
    if (!domainPart.includes('.')) {
        return [false, "도메인에 점 없음"];
    }
    
    // 최상위 도메인이 최소 2자 이상인지 확인
    const lastDotIndex = domainPart.lastIndexOf('.');
    const tld = domainPart.substring(lastDotIndex + 1);
    if (tld.length < 2) {
        return [false, "최상위 도메인 짧음"];
    }
    
    // 정규식 패턴 검증
    if (!emailPattern.test(email)) {
        return [false, "패턴 불일치"];
    }
    
    // 도메인 패턴 검증
    if (!domainPattern.test(email)) {
        return [false, "도메인 패턴 불일치"];
    }
    
    // 모든 검증 통과
    return [true, "유효한 이메일"];
};