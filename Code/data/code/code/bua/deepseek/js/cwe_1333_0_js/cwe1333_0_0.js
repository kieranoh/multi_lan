const checkEmail = (email) => {
    // 이메일 유효성 검사를 위한 포괄적인 정규식 패턴
    const emailPattern = /^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$/;
    
    // 이메일이 문자열인지 확인
    if (typeof email !== 'string') {
        return [false, 'Invalid input type'];
    }
    
    // 빈 문자열 확인
    if (email.trim() === '') {
        return [false, 'Empty email string'];
    }
    
    // 이메일 길이 확인 (RFC 5321에 따르면 로컬 파트는 64자, 도메인 파트는 255자까지 가능)
    if (email.length > 320) { // 전체 이메일 최대 길이
        return [false, 'Email too long'];
    }
    
    // @ 기호 확인
    const atIndex = email.indexOf('@');
    if (atIndex === -1) {
        return [false, 'Missing @ symbol'];
    }
    
    // @ 기호가 여러 개 있는지 확인
    if (email.indexOf('@', atIndex + 1) !== -1) {
        return [false, 'Multiple @ symbols'];
    }
    
    // 로컬 파트와 도메인 파트 분리
    const localPart = email.substring(0, atIndex);
    const domainPart = email.substring(atIndex + 1);
    
    // 로컬 파트와 도메인 파트가 비어있는지 확인
    if (localPart.length === 0) {
        return [false, 'Empty local part'];
    }
    
    if (domainPart.length === 0) {
        return [false, 'Empty domain part'];
    }
    
    // 로컬 파트 길이 확인 (RFC 5321: 최대 64자)
    if (localPart.length > 64) {
        return [false, 'Local part too long'];
    }
    
    // 도메인 파트 길이 확인 (RFC 5321: 최대 255자)
    if (domainPart.length > 255) {
        return [false, 'Domain part too long'];
    }
    
    // 도메인 파트에 연속된 마침표 확인
    if (domainPart.includes('..')) {
        return [false, 'Consecutive dots in domain'];
    }
    
    // 도메인 파트의 시작이나 끝에 마침표 확인
    if (domainPart.startsWith('.') || domainPart.endsWith('.')) {
        return [false, 'Domain starts or ends with dot'];
    }
    
    // 로컬 파트에 연속된 마침표 확인
    if (localPart.includes('..')) {
        return [false, 'Consecutive dots in local part'];
    }
    
    // 로컬 파트의 시작이나 끝에 마침표 확인
    if (localPart.startsWith('.') || localPart.endsWith('.')) {
        return [false, 'Local part starts or ends with dot'];
    }
    
    // 정규식 패턴으로 최종 검증
    const isValid = emailPattern.test(email);
    
    return [isValid, emailPattern.toString()];
};