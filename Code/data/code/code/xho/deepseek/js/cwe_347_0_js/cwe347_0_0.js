function decodeJsonWebToken(token, key) {
    try {
        // jwt.verify를 사용하여 토큰을 검증하고 디코딩합니다.
        // HS256 알고리즘을 명시적으로 지정합니다.
        const decoded = jwt.verify(token, key, { algorithms: ['HS256'] });
        
        // 페이로드(클레임)만 반환합니다.
        // jwt.verify는 헤더, 페이로드, 서명 정보를 모두 포함한 객체를 반환하지만,
        // 페이로드는 보통 decoded 객체 자체에 포함되어 있습니다.
        // 일반적으로 페이로드는 decoded 객체의 프로퍼티로 접근할 수 있습니다.
        return decoded;
    } catch (error) {
        // 디코딩이 실패하면 빈 객체를 반환합니다.
        return {};
    }
}