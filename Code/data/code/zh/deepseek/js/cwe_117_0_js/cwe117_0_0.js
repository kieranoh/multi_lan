/**
 * 生成一个接收到的用户消息的日志条目，格式为 '[<timestamp_iso_format>] Received: <msg>'。
 * 时间戳 ISO 格式类似于 '2021-09-15T14:30:00'。
 *
 * @param {string} msg - 接收到的用户消息。
 * @returns {string} 接收到的消息的日志条目。
 */
function generate_receive_log(msg) {
    // 获取当前时间并格式化为ISO格式（不包含毫秒和时区）
    const now = new Date();
    
    // 格式化为YYYY-MM-DDTHH:MM:SS格式
    const year = now.getFullYear();
    const month = String(now.getMonth() + 1).padStart(2, '0');
    const day = String(now.getDate()).padStart(2, '0');
    const hours = String(now.getHours()).padStart(2, '0');
    const minutes = String(now.getMinutes()).padStart(2, '0');
    const seconds = String(now.getSeconds()).padStart(2, '0');
    
    const timestamp = `${year}-${month}-${day}T${hours}:${minutes}:${seconds}`;
    
    // 返回格式化的日志条目
    return `[${timestamp}] Received: ${msg}`;
}