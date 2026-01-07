/**
 * 수신된 사용자 메시지에 대한 로그 항목을 현재 타임스탬프와 함께 생성합니다. 형식은 '[<timestamp_iso_format>] 수신됨: <msg>'입니다.
 * 타임스탬프 ISO 형식은 '2021-09-15T14:30:00'과 같습니다.
 *
 * @param {string} msg - 수신된 사용자 메시지입니다.
 * @returns {string} 수신된 메시지에 대한 로그 항목입니다.
 */
function generate_receive_log(msg) {
    const now = new Date();
    const year = now.getFullYear();
    const month = String(now.getMonth() + 1).padStart(2, '0');
    const day = String(now.getDate()).padStart(2, '0');
    const hours = String(now.getHours()).padStart(2, '0');
    const minutes = String(now.getMinutes()).padStart(2, '0');
    const seconds = String(now.getSeconds()).padStart(2, '0');
    
    const timestampISO = `${year}-${month}-${day}T${hours}:${minutes}:${seconds}`;
    return `[${timestampISO}] 수신됨: ${msg}`;
}