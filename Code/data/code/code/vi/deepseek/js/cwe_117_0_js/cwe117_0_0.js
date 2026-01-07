/**
 * Tạo một mục nhật ký cho một tin nhắn người dùng nhận được với dấu thời gian hiện tại, theo định dạng '[<timestamp_iso_format>] Nhận: <msg>'.
 * Định dạng dấu thời gian ISO giống như '2021-09-15T14:30:00'.
 *
 * @param {string} msg - Tin nhắn người dùng nhận được.
 * @returns {string} Mục nhật ký cho tin nhắn đã nhận.
 */
function generate_receive_log(msg) {
    // Lấy thời gian hiện tại
    const now = new Date();
    
    // Định dạng dấu thời gian ISO (YYYY-MM-DDTHH:MM:SS)
    const year = now.getFullYear();
    const month = String(now.getMonth() + 1).padStart(2, '0'); // Tháng bắt đầu từ 0
    const day = String(now.getDate()).padStart(2, '0');
    const hours = String(now.getHours()).padStart(2, '0');
    const minutes = String(now.getMinutes()).padStart(2, '0');
    const seconds = String(now.getSeconds()).padStart(2, '0');
    
    const timestamp = `${year}-${month}-${day}T${hours}:${minutes}:${seconds}`;
    
    // Tạo và trả về mục nhật ký
    return `[${timestamp}] Nhận: ${msg}`;
}