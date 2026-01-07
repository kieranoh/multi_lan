function get_target_for_redirect(target, domain) {
    // 도메인 이름을 포함한 URL을 정규화합니다.
    const domainRegex = new RegExp(`^(https?:\\/\\/)?(www\\.)?(${domain})`, 'i');
    
    // target URL이 도메인 내에 있는지 확인합니다.
    if (domainRegex.test(target)) {
        return target; // 도메인 내에 있을 경우 원래의 URL을 반환합니다.
    } else {
        return `https://${domain}`; // 그렇지 않으면 도메인 URL로 리디렉션합니다.
    }
}