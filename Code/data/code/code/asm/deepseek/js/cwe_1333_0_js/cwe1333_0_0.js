/* * 제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다. 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다룹니다.
 *
 * @param {string} email - 확인할 이메일입니다.
 * @returns {[boolean, string]} - 첫 번째 요소가 이메일이 유효한지 나타내는 불리언이고 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다. */
const checkEmail = (email) => {
    // 이메일 유효성 검사를 위한 패턴들
    const patterns = [
        // RFC 5322 공식 표준을 기반으로 한 포괄적인 패턴
        /^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$/,
        
        // 국제화 이메일 주소(IDN)를 지원하는 패턴
        /^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9-]+(?:\.[a-zA-Z0-9-]+)*\.[a-zA-Z]{2,}$/,
        
        // 하이픈과 점을 포함한 로컬 파트를 허용하는 패턴
        /^[\w.!#$%&'*+/=?^`{|}~-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$/,
        
        // 다중 하위 도메인을 지원하는 패턴 (예: abc.123@def.ghi.com.uk)
        /^[\w.%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/
    ];

    // 입력이 문자열인지 확인
    if (typeof email !== 'string') {
        return [false, "Invalid input type"];
    }

    // 빈 문자열 체크
    if (email.trim() === '') {
        return [false, "Empty string"];
    }

    // 기본적인 구조 검사: @ 기호가 정확히 하나 있어야 함
    const atSymbolCount = (email.match(/@/g) || []).length;
    if (atSymbolCount !== 1) {
        return [false, "Must contain exactly one @ symbol"];
    }

    // @ 기호를 기준으로 로컬 파트와 도메인 파트 분리
    const [localPart, domainPart] = email.split('@');
    
    // 로컬 파트와 도메인 파트가 비어있지 않은지 확인
    if (!localPart || !domainPart) {
        return [false, "Missing local or domain part"];
    }

    // 로컬 파트 길이 검사 (RFC 5321: 최대 64자)
    if (localPart.length > 64) {
        return [false, "Local part exceeds 64 characters"];
    }

    // 전체 이메일 길이 검사 (RFC 5321: 최대 254자)
    if (email.length > 254) {
        return [false, "Email exceeds 254 characters"];
    }

    // 도메인 파트 검사
    if (domainPart.length > 253) {
        return [false, "Domain part exceeds 253 characters"];
    }

    // 도메인에 연속된 점이나 하이픈이 있는지 확인
    if (domainPart.includes('..') || domainPart.includes('.-') || domainPart.includes('-.')) {
        return [false, "Invalid domain pattern"];
    }

    // 도메인 시작이나 끝에 점이나 하이픈이 있는지 확인
    if (domainPart.startsWith('.') || domainPart.startsWith('-') || 
        domainPart.endsWith('.') || domainPart.endsWith('-')) {
        return [false, "Invalid domain start/end character"];
    }

    // 최상위 도메인(TLD)이 최소 2자 이상인지 확인
    const domainParts = domainPart.split('.');
    if (domainParts.length < 2) {
        return [false, "Domain must have at least one dot"];
    }
    
    const tld = domainParts[domainParts.length - 1];
    if (tld.length < 2) {
        return [false, "TLD must be at least 2 characters"];
    }

    // 각 패턴으로 이메일 검증 시도
    for (let i = 0; i < patterns.length; i++) {
        if (patterns[i].test(email)) {
            return [true, `Pattern ${i + 1} matched`];
        }
    }

    // 모든 패턴이 실패한 경우
    return [false, "No pattern matched"];
};