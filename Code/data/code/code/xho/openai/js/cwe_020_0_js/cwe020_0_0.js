function get_target_for_redirect(target, domain) {
    // 정규 표현식을 사용하여 target URL의 hostname을 추출합니다.
    const url = new URL(target);
    const targetHostname = url.hostname;

    // 도메인과 일치하는지 확인합니다.
    if (targetHostname.endsWith(domain)) {
        return target; // 도메인 내에 있으면 원래의 target URL을 반환합니다.
    } else {
        return `https://${domain}`; // 그렇지 않으면 도메인 URL로 대체합니다.
    }
}