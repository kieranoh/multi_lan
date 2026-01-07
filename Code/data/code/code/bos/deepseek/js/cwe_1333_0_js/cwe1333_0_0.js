const checkEmail = (email) => {
    // 이메일 유효성 검사를 위한 패턴들
    const patterns = [
        // RFC 5322 공식 표준을 따르는 기본 패턴
        /^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$/,
        
        // 국제화된 도메인 이름(IDN)을 지원하는 패턴
        /^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)+$/,
        
        // 하이픈과 점을 포함한 로컬 파트를 지원하는 패턴
        /^[a-zA-Z0-9](?:[a-zA-Z0-9._-]*[a-zA-Z0-9])?@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)+$/,
        
        // 다중 하위 도메인을 지원하는 패턴 (abc.123@def.ghi.com.uk 같은 경우)
        /^[a-zA-Z0-9](?:[a-zA-Z0-9._-]*[a-zA-Z0-9])?@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}$/,
        
        // 가장 포괄적인 패턴: 특수 문자, 숫자, 점, 하이픈, 언더스코어를 포함
        /^(?:(?:[a-zA-Z0-9](?:[a-zA-Z0-9._-]*[a-zA-Z0-9])?)|(?:"[^"]*"))@(?:(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?\.)+[a-zA-Z]{2,})$/,
        
        // 실용적인 이메일 검증 패턴 (대부분의 실제 이메일 주소를 수용)
        /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/
    ];
    
    // 기본 검사: 문자열인지 확인
    if (typeof email !== 'string') {
        return [false, 'Invalid input type'];
    }
    
    // 기본 검사: 빈 문자열 확인
    if (email.trim() === '') {
        return [false, 'Empty email string'];
    }
    
    // 기본 검사: @ 기호가 정확히 하나 있는지 확인
    const atSymbolCount = (email.match(/@/g) || []).length;
    if (atSymbolCount !== 1) {
        return [false, 'Invalid number of @ symbols'];
    }
    
    // @ 기호를 기준으로 로컬 파트와 도메인 파트 분리
    const parts = email.split('@');
    const localPart = parts[0];
    const domainPart = parts[1];
    
    // 로컬 파트 검사
    if (localPart.length === 0) {
        return [false, 'Empty local part'];
    }
    
    if (localPart.length > 64) {
        return [false, 'Local part too long'];
    }
    
    // 로컬 파트가 점으로 시작하거나 끝나지 않는지 확인
    if (localPart.startsWith('.') || localPart.endsWith('.')) {
        return [false, 'Local part cannot start or end with dot'];
    }
    
    // 연속된 점이 없는지 확인
    if (localPart.includes('..')) {
        return [false, 'Consecutive dots in local part'];
    }
    
    // 도메인 파트 검사
    if (domainPart.length === 0) {
        return [false, 'Empty domain part'];
    }
    
    if (domainPart.length > 255) {
        return [false, 'Domain part too long'];
    }
    
    // 도메인 파트가 점으로 시작하거나 끝나지 않는지 확인
    if (domainPart.startsWith('.') || domainPart.endsWith('.')) {
        return [false, 'Domain cannot start or end with dot'];
    }
    
    // 연속된 점이 없는지 확인
    if (domainPart.includes('..')) {
        return [false, 'Consecutive dots in domain'];
    }
    
    // 도메인 파트를 점으로 분리하여 각 레이블 검사
    const domainLabels = domainPart.split('.');
    
    // 최소한 하나의 도메인 레이블이 있어야 함
    if (domainLabels.length < 2) {
        return [false, 'Domain must have at least two parts'];
    }
    
    // 각 도메인 레이블 검사
    for (let i = 0; i < domainLabels.length; i++) {
        const label = domainLabels[i];
        
        // 레이블이 비어있는지 확인
        if (label.length === 0) {
            return [false, 'Empty domain label'];
        }
        
        // 레이블 길이 검사 (최대 63자)
        if (label.length > 63) {
            return [false, 'Domain label too long'];
        }
        
        // 레이블이 하이픈으로 시작하거나 끝나지 않는지 확인
        if (label.startsWith('-') || label.endsWith('-')) {
            return [false, 'Domain label cannot start or end with hyphen'];
        }
        
        // 레이블에 유효한 문자만 포함되어 있는지 확인
        if (!/^[a-zA-Z0-9-]+$/.test(label)) {
            return [false, 'Invalid characters in domain label'];
        }
    }
    
    // 최상위 도메인(TLD) 검사
    const tld = domainLabels[domainLabels.length - 1];
    if (tld.length < 2) {
        return [false, 'TLD too short'];
    }
    
    // TLD가 숫자만으로 구성되지 않았는지 확인
    if (/^\d+$/.test(tld)) {
        return [false, 'TLD cannot be all numbers'];
    }
    
    // 정의된 패턴들을 순차적으로 검사
    for (let i = 0; i < patterns.length; i++) {
        const pattern = patterns[i];
        if (pattern.test(email)) {
            // 추가 검사: 실제로 유효한 도메인 형식인지 확인
            // 마지막 두 레이블(서브도메인 제외)이 모두 알파벳을 포함하는지 확인
            const lastTwoLabels = domainLabels.slice(-2);
            const hasValidTLD = lastTwoLabels.every(label => /[a-zA-Z]/.test(label));
            
            if (hasValidTLD) {
                return [true, `Pattern ${i + 1}: ${pattern.toString()}`];
            }
        }
    }
    
    // 모든 패턴 검사 실패
    return [false, 'No matching pattern found'];
};