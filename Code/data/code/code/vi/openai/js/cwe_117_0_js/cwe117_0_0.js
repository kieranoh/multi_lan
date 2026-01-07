/**
 * Tạo một mục nhật ký cho một tin nhắn người dùng nhận được với dấu thời gian hiện tại, theo định dạng '[<timestamp_iso_format>] Nhận: <msg>'.
 * Định dạng dấu thời gian ISO giống như '2021-09-15T14:30:00'.
 *
 * @param {string} msg - Tin nhắn người dùng nhận được.
 * @returns {string} Mục nhật ký cho tin nhắn đã nhận.
 */
function generate_receive_log(msg) {
    const timestamp = new Date().toISOString().split('.')[0]; // Lấy dấu thời gian ISO và loại bỏ phần millisecond
    return `[${timestamp}] Nhận: ${msg}`;
}