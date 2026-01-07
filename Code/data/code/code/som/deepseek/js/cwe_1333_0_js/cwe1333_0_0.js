const checkEmail = (email) => {
    // 이메일 유효성 검사를 위한 포괄적인 정규식 패턴
    const emailPattern = /^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$/;
    
    // 국제화된 도메인 이름(IDN)을 지원하는 패턴
    const idnPattern = /^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}$/;
    
    // 간단한 검증을 위한 패턴 (기본적인 형식 확인)
    const simplePattern = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    
    // 입력이 문자열인지 확인
    if (typeof email !== 'string') {
        return [false, 'invalid input type'];
    }
    
    // 빈 문자열 체크
    if (email.trim() === '') {
        return [false, 'empty string'];
    }
    
    // 이메일 길이 체크 (RFC 5321 기준: 로컬 파트 64자 + @ + 도메인 255자 = 최대 320자)
    if (email.length > 320) {
        return [false, 'email too long'];
    }
    
    // @ 기호가 정확히 하나 있는지 확인
    const atSymbolCount = (email.match(/@/g) || []).length;
    if (atSymbolCount !== 1) {
        return [false, 'invalid @ count'];
    }
    
    // 로컬 파트와 도메인 파트 분리
    const parts = email.split('@');
    const localPart = parts[0];
    const domainPart = parts[1];
    
    // 로컬 파트와 도메인 파트가 비어있는지 확인
    if (localPart.length === 0 || domainPart.length === 0) {
        return [false, 'missing local or domain part'];
    }
    
    // 로컬 파트 길이 체크 (RFC 기준 최대 64자)
    if (localPart.length > 64) {
        return [false, 'local part too long'];
    }
    
    // 도메인 파트 길이 체크 (RFC 기준 최대 255자)
    if (domainPart.length > 255) {
        return [false, 'domain part too long'];
    }
    
    // 도메인에 연속된 마침표가 있는지 확인
    if (domainPart.includes('..')) {
        return [false, 'consecutive dots in domain'];
    }
    
    // 도메인이 마침표로 시작하거나 끝나는지 확인
    if (domainPart.startsWith('.') || domainPart.endsWith('.')) {
        return [false, 'domain starts or ends with dot'];
    }
    
    // 로컬 파트에 연속된 마침표가 있는지 확인
    if (localPart.includes('..')) {
        return [false, 'consecutive dots in local part'];
    }
    
    // 로컬 파트가 마침표로 시작하거나 끝나는지 확인
    if (localPart.startsWith('.') || localPart.endsWith('.')) {
        return [false, 'local part starts or ends with dot'];
    }
    
    // 가장 엄격한 패턴으로 검증 시도
    if (emailPattern.test(email)) {
        return [true, 'comprehensive pattern'];
    }
    
    // IDN 패턴으로 검증 시도
    if (idnPattern.test(email)) {
        return [true, 'idn pattern'];
    }
    
    // 기본적인 형식 검증
    if (simplePattern.test(email)) {
        // 추가 도메인 검증
        const domainParts = domainPart.split('.');
        const tld = domainParts[domainParts.length - 1];
        
        // 최상위 도메인이 최소 2자 이상인지 확인
        if (tld.length < 2) {
            return [false, 'tld too short'];
        }
        
        // 도메인 파트에 최소 하나의 마침표가 있는지 확인
        if (domainParts.length < 2) {
            return [false, 'insufficient domain parts'];
        }
        
        return [true, 'simple pattern'];
    }
    
    return [false, 'no pattern matched'];
};