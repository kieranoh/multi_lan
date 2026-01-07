/**
 * 수신된 사용자 메시지에 대한 로그 항목을 현재 타임스탬프와 함께 생성합니다.
 * 형식은 '[<timestamp_iso_format>] 수신됨: <msg>'입니다.
 * 타임스탬프 ISO 형식은 '2021-09-15T14:30:00'과 같습니다.
 *
 * @param {string} msg - 수신된 사용자 메시지입니다.
 * @returns {string} 수신된 메시지에 대한 로그 항목입니다.
 */
function generate_receive_log(msg) {
    // 현재 시간을 ISO 형식으로 변환 (로컬 시간 기준)
    const now = new Date();
    
    // ISO 형식의 문자열 생성 (YYYY-MM-DDTHH:mm:ss)
    const year = now.getFullYear();
    const month = String(now.getMonth() + 1).padStart(2, '0');
    const day = String(now.getDate()).padStart(2, '0');
    const hours = String(now.getHours()).padStart(2, '0');
    const minutes = String(now.getMinutes()).padStart(2, '0');
    const seconds = String(now.getSeconds()).padStart(2, '0');
    
    const timestamp = `${year}-${month}-${day}T${hours}:${minutes}:${seconds}`;
    
    // 로그 항목 생성
    return `[${timestamp}] 수신됨: ${msg}`;
}