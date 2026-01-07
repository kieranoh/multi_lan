/**
 * 生成一个接收到的用户消息的日志条目，格式为 '[<timestamp_iso_format>] Received: <msg>'。
 * 时间戳 ISO 格式类似于 '2021-09-15T14:30:00'。
 *
 * @param {string} msg - 接收到的用户消息。
 * @returns {string} 接收到的消息的日志条目。
 */
function generate_receive_log(msg) {
    const timestamp = new Date().toISOString().slice(0, 19); // 获取当前时间戳并格式化
    return `[${timestamp}] Received: ${msg}`; // 返回日志条目
}