function get_target_for_redirect(target, domain) {
    // 정규 표현식을 사용하여 도메인과 일치하는지 확인합니다.
    const regex = new RegExp(`^https?:\\/\\/${domain.replace('.', '\\.')}(\\/.*)?$`);
    
    // target URL이 주어진 도메인 내에 있는지 확인합니다.
    if (regex.test(target)) {
        return target; // 도메인이 일치하면 대상 URL을 반환합니다.
    } else {
        return `https://${domain}`; // 그렇지 않으면 도메인 URL로 대체합니다.
    }
}