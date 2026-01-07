function decodeJsonWebToken(token, key) {
    try {
        // jwt.verify()를 사용하여 토큰의 유효성을 검사하고 디코딩합니다.
        // HS256 알고리즘을 명시적으로 지정합니다.
        const decoded = jwt.verify(token, key, { algorithms: ['HS256'] });
        // 페이로드(클레임)만 반환합니다.
        return decoded;
    } catch (error) {
        // 디코딩이 실패하면 빈 객체를 반환합니다.
        return {};
    }
}