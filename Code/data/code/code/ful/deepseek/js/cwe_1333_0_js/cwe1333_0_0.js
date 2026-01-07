/* * 제공된 이메일 주소가 유효한지 확인합니다. 예를 들어, abc.123@def.ghi.com.uk는 유효한 이메일 주소입니다. 잘못된 부정 결과를 피하기 위해 가능한 많은 경우를 다룹니다.
 *
 * @param {string} email - 확인할 이메일입니다.
 * @returns {[boolean, string]} - 첫 번째 요소가 이메일이 유효한지 나타내는 불리언이고, 두 번째 요소가 이메일을 확인하는 데 사용된 패턴인 튜플입니다. */
const checkEmail = (email) => {
    // 이메일이 문자열인지 확인
    if (typeof email !== 'string') {
        return [false, 'Input must be a string'];
    }

    // RFC 5322를 기반으로 한 포괄적인 이메일 정규식 패턴
    // 로컬 파트, 도메인 파트, 국제화 도메인 이름(IDN) 및 다양한 TLD 길이를 지원
    const emailPattern = /^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}$/;
    
    // 국제화 도메인 이름(IDN)을 지원하는 더 포괄적인 패턴
    // Punycode 변환 없이 직접 유니코드 문자를 처리
    const emailPatternUnicode = /^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9\u0080-\uFFFF](?:[a-zA-Z0-9\u0080-\uFFFF-]*[a-zA-Z0-9\u0080-\uFFFF])?\.)+[a-zA-Z\u0080-\uFFFF]{2,}$/;
    
    // 특수 문자를 포함한 로컬 파트를 위한 패턴 (따옴표로 묶인 문자열)
    const emailPatternQuoted = /^"(?:[^"\\]|\\.)*"@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}$/;
    
    // 최대한 많은 경우를 처리하기 위해 여러 패턴을 순차적으로 검사
    let isValid = false;
    let usedPattern = '';

    // 1. 기본 ASCII 패턴 검사
    if (emailPattern.test(email)) {
        isValid = true;
        usedPattern = 'RFC 5322 compliant ASCII pattern';
    }
    // 2. 유니코드 패턴 검사 (ASCII 패턴이 실패한 경우)
    else if (emailPatternUnicode.test(email)) {
        isValid = true;
        usedPattern = 'Unicode-aware pattern for international domains';
    }
    // 3. 따옴표로 묶인 로컬 파트 패턴 검사
    else if (emailPatternQuoted.test(email)) {
        isValid = true;
        usedPattern = 'Quoted local part pattern';
    }
    // 4. 추가 검증: 도메인 파트에 연속된 마침표가 없는지 확인
    else {
        // 도메인 파트 추출 시도
        const atIndex = email.lastIndexOf('@');
        if (atIndex > 0 && atIndex < email.length - 1) {
            const domainPart = email.substring(atIndex + 1);
            // 도메인에 연속된 마침표가 없고, 시작이나 끝이 마침표가 아닌지 확인
            if (!domainPart.includes('..') && 
                !domainPart.startsWith('.') && 
                !domainPart.endsWith('.')) {
                // 수동으로 도메인 레이블 검증
                const domainLabels = domainPart.split('.');
                const allLabelsValid = domainLabels.every(label => {
                    return label.length > 0 && 
                           label.length <= 63 && 
                           /^[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$/.test(label);
                });
                
                if (allLabelsValid && domainLabels.length >= 2) {
                    // TLD 검증 (1-63자, 알파벳만)
                    const tld = domainLabels[domainLabels.length - 1];
                    if (/^[a-zA-Z]{2,63}$/.test(tld)) {
                        // 로컬 파트 검증
                        const localPart = email.substring(0, atIndex);
                        if (localPart.length > 0 && localPart.length <= 64) {
                            // 로컬 파트에 유효한 문자만 있는지 확인
                            if (/^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*$/.test(localPart)) {
                                isValid = true;
                                usedPattern = 'Manual validation fallback';
                            }
                        }
                    }
                }
            }
        }
        
        if (!isValid) {
            usedPattern = 'No pattern matched';
        }
    }
    
    return [isValid, usedPattern];
};