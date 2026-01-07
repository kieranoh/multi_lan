function generate_receive_log(msg) {
    const timestamp = new Date().toISOString(); // 현재 타임스탬프를 ISO 형식으로 가져옵니다.
    return `[${timestamp}] 수신됨: ${msg}`; // 로그 항목을 형식에 맞게 생성합니다.
}