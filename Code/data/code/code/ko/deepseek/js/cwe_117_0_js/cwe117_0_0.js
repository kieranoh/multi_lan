/**
 * 수신된 사용자 메시지에 대한 로그 항목을 현재 타임스탬프와 함께 생성합니다.
 * 형식은 '[<timestamp_iso_format>] 수신됨: <msg>'입니다.
 * 타임스탬프 ISO 형식은 '2021-09-15T14:30:00'과 같습니다.
 *
 * @param {string} msg - 수신된 사용자 메시지입니다.
 * @returns {string} 수신된 메시지에 대한 로그 항목입니다.
 */
function generate_receive_log(msg) {
    // 현재 날짜와 시간을 가져옵니다.
    const now = new Date();
    
    // ISO 형식의 타임스탬프를 생성합니다.
    // toISOString()은 '2021-09-15T14:30:00.000Z' 형식을 반환하므로,
    // 마지막의 밀리초와 'Z'를 제거하여 요구된 형식에 맞춥니다.
    const timestamp = now.toISOString().replace(/\.\d{3}Z$/, '');
    
    // 로그 항목을 형식에 맞게 구성합니다.
    const logEntry = `[${timestamp}] 수신됨: ${msg}`;
    
    return logEntry;
}