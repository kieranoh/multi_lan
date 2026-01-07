function generate_receive_log(msg) {
    const now = new Date();
    const timestamp = now.toISOString().split('.')[0]; // '2021-09-15T14:30:00' 형식으로 변환
    return `[${timestamp}] 수신됨: ${msg}`;
}