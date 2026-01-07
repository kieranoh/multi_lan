/* * 제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다. 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다룹니다.
 *
 * @param {string} email - 확인할 이메일입니다.
 * @returns {[boolean, string]} - 첫 번째 요소가 이메일이 유효한지 나타내는 불리언이고, 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다. */
const checkEmail = (email) => {
    // 이메일 유효성 검사를 위한 패턴들
    const patterns = [
        // RFC 5322 공식 표준을 따르는 포괄적인 패턴
        /^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$/,
        
        // 국제화된 도메인 이름(IDN)을 지원하는 패턴
        /^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)+(?:\.[a-zA-Z]{2,})?$/,
        
        // 하이픈과 점을 포함한 로컬 파트를 허용하는 패턴
        /^[a-zA-Z0-9](?:[a-zA-Z0-9._-]*[a-zA-Z0-9])?@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)+$/,
        
        // 다중 하위 도메인을 지원하는 패턴 (예: abc.123@def.ghi.com.uk)
        /^[\w.%+-]+@(?:[\w-]+\.)+[a-zA-Z]{2,}$/,
        
        // 간단하면서도 효과적인 일반적인 이메일 패턴
        /^[^\s@]+@[^\s@]+\.[^\s@]+$/
    ];
    
    // 패턴 설명
    const patternDescriptions = [
        "RFC 5322 표준 준수 패턴",
        "국제화 도메인 이름(IDN) 지원 패턴",
        "하이픈/점 포함 로컬 파트 패턴",
        "다중 하위 도메인 지원 패턴",
        "일반적인 이메일 검증 패턴"
    ];
    
    // 기본 검사: 문자열인지 확인
    if (typeof email !== 'string') {
        return [false, "입력이 문자열이 아닙니다"];
    }
    
    // 빈 문자열 검사
    if (email.trim() === '') {
        return [false, "빈 이메일 주소"];
    }
    
    // @ 기호가 정확히 하나 있는지 확인
    const atSymbolCount = (email.match(/@/g) || []).length;
    if (atSymbolCount !== 1) {
        return [false, "@ 기호가 1개가 아닙니다"];
    }
    
    // @ 기호 위치 확인 (첫 번째 또는 마지막 문자일 수 없음)
    if (email.startsWith('@') || email.endsWith('@')) {
        return [false, "@ 기호가 잘못된 위치에 있습니다"];
    }
    
    // 로컬 파트와 도메인 파트 분리
    const parts = email.split('@');
    const localPart = parts[0];
    const domainPart = parts[1];
    
    // 로컬 파트 검사
    if (localPart.length === 0) {
        return [false, "로컬 파트가 비어 있습니다"];
    }
    
    if (localPart.length > 64) {
        return [false, "로컬 파트가 너무 깁니다 (64자 초과)"];
    }
    
    // 로컬 파트가 점으로 시작하거나 끝나지 않는지 확인
    if (localPart.startsWith('.') || localPart.endsWith('.')) {
        return [false, "로컬 파트가 점으로 시작하거나 끝납니다"];
    }
    
    // 연속된 점 확인
    if (localPart.includes('..')) {
        return [false, "로컬 파트에 연속된 점이 있습니다"];
    }
    
    // 도메인 파트 검사
    if (domainPart.length === 0) {
        return [false, "도메인 파트가 비어 있습니다"];
    }
    
    if (domainPart.length > 255) {
        return [false, "도메인 파트가 너무 깁니다 (255자 초과)"];
    }
    
    // 도메인 파트가 점으로 시작하거나 끝나지 않는지 확인
    if (domainPart.startsWith('.') || domainPart.endsWith('.')) {
        return [false, "도메인 파트가 점으로 시작하거나 끝납니다"];
    }
    
    // 도메인에 연속된 점 확인
    if (domainPart.includes('..')) {
        return [false, "도메인 파트에 연속된 점이 있습니다"];
    }
    
    // 도메인 파트에 최소한 하나의 점이 있는지 확인
    if (!domainPart.includes('.')) {
        return [false, "도메인에 점이 없습니다"];
    }
    
    // 최상위 도메인(TLD) 검사
    const domainParts = domainPart.split('.');
    const tld = domainParts[domainParts.length - 1];
    
    if (tld.length < 2) {
        return [false, "최상위 도메인이 너무 짧습니다 (2자 미만)"];
    }
    
    // TLD가 오직 알파벳으로만 구성되었는지 확인
    if (!/^[a-zA-Z]+$/.test(tld)) {
        return [false, "최상위 도메인이 알파벳만으로 구성되지 않았습니다"];
    }
    
    // 각 패턴으로 검증 시도
    for (let i = 0; i < patterns.length; i++) {
        if (patterns[i].test(email)) {
            return [true, patternDescriptions[i]];
        }
    }
    
    // 모든 패턴에 실패한 경우
    return [false, "모든 검증 패턴에 실패했습니다"];
};