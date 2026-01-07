/* 
 * 제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다. 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다룹니다.
 *
 * @param {string} email - 확인할 이메일입니다.
 * @returns {[boolean, string]} - 첫 번째 요소가 이메일이 유효한지 나타내는 불리언이고, 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다.
 */
const checkEmail = (email) => {
    // 이메일이 문자열인지 확인
    if (typeof email !== 'string') {
        return [false, '이메일은 문자열이어야 합니다.'];
    }

    // RFC 5322를 기반으로 한 포괄적인 이메일 검증 정규식
    // 로컬 파트, 도메인 파트, 국제화 도메인 이름(IDN) 및 다양한 하위 도메인을 지원
    const emailPattern = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;

    // 추가적인 엄격한 검증을 위한 패턴
    // 1. 로컬 파트는 64자 이하, 도메인 파트는 255자 이하
    // 2. 전체 이메일 길이는 254자 이하
    // 3. 연속된 마침표 금지
    // 4. 도메인 파트에 하이픈이 시작이나 끝에 오지 않도록 함
    const strictEmailPattern = /^(?!\.)(?!.*\.\.)(?!.*\.$)[a-zA-Z0-9.!#$%&'*+\/=?^_`{|}~-]{1,64}@(?!-)(?!.*--)(?!.*-$)([a-zA-Z0-9-]{1,63}\.)+[a-zA-Z]{2,}$/;

    // 간단한 검증 패턴 (기본적인 형식 검사)
    const simpleEmailPattern = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;

    // 국제화 도메인 이름(IDN)을 지원하는 패턴
    const idnEmailPattern = /^[^\s@]+@[^\s@]+\.[^\s@]{2,}$/;

    // 이메일이 비어 있는지 확인
    if (email.trim() === '') {
        return [false, '이메일이 비어 있습니다.'];
    }

    // 전체 길이 검사 (RFC 5321 기준: 최대 254자)
    if (email.length > 254) {
        return [false, '이메일이 너무 깁니다 (최대 254자).'];
    }

    // @ 기호가 정확히 하나인지 확인
    const atSymbolCount = (email.match(/@/g) || []).length;
    if (atSymbolCount !== 1) {
        return [false, '@ 기호가 없거나 너무 많습니다.'];
    }

    // @ 기호를 기준으로 로컬 파트와 도메인 파트 분리
    const parts = email.split('@');
    const localPart = parts[0];
    const domainPart = parts[1];

    // 로컬 파트 길이 검사 (RFC 5321 기준: 최대 64자)
    if (localPart.length > 64) {
        return [false, '로컬 파트가 너무 깁니다 (최대 64자).'];
    }

    // 도메인 파트 길이 검사 (RFC 1035 기준: 최대 255자)
    if (domainPart.length > 255) {
        return [false, '도메인 파트가 너무 깁니다 (최대 255자).'];
    }

    // 도메인 파트에 마침표가 있는지 확인
    if (!domainPart.includes('.')) {
        return [false, '도메인에 마침표가 없습니다.'];
    }

    // 도메인 파트의 마지막 부분(최상위 도메인)이 2자 이상인지 확인
    const domainParts = domainPart.split('.');
    const tld = domainParts[domainParts.length - 1];
    if (tld.length < 2) {
        return [false, '최상위 도메인이 너무 짧습니다 (최소 2자).'];
    }

    // 도메인 파트에 연속된 마침표가 있는지 확인
    if (domainPart.includes('..')) {
        return [false, '도메인에 연속된 마침표가 있습니다.'];
    }

    // 도메인 파트가 하이픈으로 시작하거나 끝나는지 확인
    if (domainPart.startsWith('-') || domainPart.endsWith('-')) {
        return [false, '도메인이 하이픈으로 시작하거나 끝납니다.'];
    }

    // 로컬 파트가 마침표로 시작하거나 끝나는지 확인
    if (localPart.startsWith('.') || localPart.endsWith('.')) {
        return [false, '로컬 파트가 마침표로 시작하거나 끝납니다.'];
    }

    // 로컬 파트에 연속된 마침표가 있는지 확인
    if (localPart.includes('..')) {
        return [false, '로컬 파트에 연속된 마침표가 있습니다.'];
    }

    // 가장 엄격한 패턴으로 검증 시도
    if (strictEmailPattern.test(email)) {
        return [true, 'strictEmailPattern'];
    }

    // RFC 5322 패턴으로 검증 시도
    if (emailPattern.test(email)) {
        return [true, 'emailPattern'];
    }

    // IDN 패턴으로 검증 시도
    if (idnEmailPattern.test(email)) {
        return [true, 'idnEmailPattern'];
    }

    // 간단한 패턴으로 검증 시도
    if (simpleEmailPattern.test(email)) {
        return [true, 'simpleEmailPattern'];
    }

    // 모든 검증 실패
    return [false, '모든 패턴 검증 실패'];
};