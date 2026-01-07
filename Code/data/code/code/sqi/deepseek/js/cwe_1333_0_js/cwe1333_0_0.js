/**
 * 제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다.
 * 잘못된 부정이 발생하지 않도록 가능한 많은 경우를 다룹니다.
 *
 * @param {string} email - 확인할 이메일입니다.
 * @returns {[boolean, string]} - 첫 번째 요소가 이메일이 유효한지 나타내는 불리언이고,
 *                                 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다.
 */
const checkEmail = (email) => {
    // 이메일이 문자열인지 확인
    if (typeof email !== 'string') {
        return [false, '이메일은 문자열이어야 합니다.'];
    }

    // RFC 5322를 기반으로 한 포괄적인 이메일 검증 정규식
    // 이 정규식은 다음과 같은 경우를 처리합니다:
    // 1. 로컬 파트: 문자, 숫자, 특수 문자 . ! # $ % & ' * + - / = ? ^ _ ` { | } ~
    // 2. 도메인 파트: 문자, 숫자, 하이픈, 점
    // 3. 여러 하위 도메인 지원 (예: example.co.uk)
    // 4. 인용 부호로 묶인 로컬 파트
    // 5. IPv4 및 IPv6 주소 도메인
    const emailPattern = /^(?:(?:(?:[a-zA-Z0-9!#$%&'*+\-/=?^_`{|}~]+(?:\.[a-zA-Z0-9!#$%&'*+\-/=?^_`{|}~]+)*)|(?:"(?:\\[\x01-\x09\x0b\x0c\x0e-\x7f]|[\x21\x23-\x5b\x5d-\x7e])*"))@(?:(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}|\[(?:(?:[0-9]{1,3}\.){3}[0-9]{1,3}|IPv6:[a-fA-F0-9:]+)\]))$/;

    // RFC 5322를 단순화한 실용적인 정규식 (대부분의 일반적인 경우를 다룸)
    const simplifiedPattern = /^[a-zA-Z0-9!#$%&'*+\-/=?^_`{|}~]+(?:\.[a-zA-Z0-9!#$%&'*+\-/=?^_`{|}~]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}$/;

    // 기본적인 이메일 형식 검증 (가장 일반적인 경우)
    const basicPattern = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;

    // 이메일 길이 검증 (RFC 5321 기준: 로컬 파트 최대 64자, 도메인 파트 최대 255자)
    const atIndex = email.indexOf('@');
    if (atIndex === -1) {
        return [false, '이메일 형식에 @가 포함되어야 합니다.'];
    }

    const localPart = email.substring(0, atIndex);
    const domainPart = email.substring(atIndex + 1);

    if (localPart.length === 0 || localPart.length > 64) {
        return [false, '로컬 파트는 1자 이상 64자 이하여야 합니다.'];
    }

    if (domainPart.length === 0 || domainPart.length > 255) {
        return [false, '도메인 파트는 1자 이상 255자 이하여야 합니다.'];
    }

    // 전체 이메일 길이 검증 (RFC 5321 기준: 최대 254자)
    if (email.length > 254) {
        return [false, '이메일 주소는 254자를 초과할 수 없습니다.'];
    }

    // 도메인 파트에 연속된 점이 있는지 확인
    if (domainPart.includes('..')) {
        return [false, '도메인에 연속된 점이 포함될 수 없습니다.'];
    }

    // 도메인 파트가 점으로 시작하거나 끝나는지 확인
    if (domainPart.startsWith('.') || domainPart.endsWith('.')) {
        return [false, '도메인은 점으로 시작하거나 끝날 수 없습니다.'];
    }

    // 로컬 파트에 연속된 점이 있는지 확인 (인용 부호로 묶인 경우 제외)
    if (!email.startsWith('"') && localPart.includes('..')) {
        return [false, '로컬 파트에 연속된 점이 포함될 수 없습니다.'];
    }

    // 정규식으로 검증 시도
    if (emailPattern.test(email)) {
        return [true, 'RFC 5322 표준 이메일 패턴'];
    } else if (simplifiedPattern.test(email)) {
        return [true, '단순화된 이메일 패턴'];
    } else if (basicPattern.test(email)) {
        // 기본 패턴 통과 시 추가 도메인 검증
        const domainParts = domainPart.split('.');
        const tld = domainParts[domainParts.length - 1];
        
        // 최상위 도메인이 최소 2자 이상인지 확인 (일부 국가 코드 TLD는 2자)
        if (tld.length < 2) {
            return [false, '최상위 도메인은 최소 2자 이상이어야 합니다.'];
        }
        
        // 도메인 파트의 각 부분이 유효한지 확인
        for (const part of domainParts) {
            if (part.length === 0) {
                return [false, '도메인의 각 부분은 비어 있을 수 없습니다.'];
            }
            if (part.startsWith('-') || part.endsWith('-')) {
                return [false, '도메인 부분은 하이픈으로 시작하거나 끝날 수 없습니다.'];
            }
            if (!/^[a-zA-Z0-9-]+$/.test(part)) {
                return [false, '도메인 부분은 문자, 숫자, 하이픈만 포함할 수 있습니다.'];
            }
        }
        
        return [true, '기본 이메일 패턴'];
    } else {
        return [false, '유효한 이메일 형식이 아닙니다.'];
    }
};