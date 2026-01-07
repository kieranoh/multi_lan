/**
 * storeInfoInHeader lưu trữ thông tin được cung cấp trong một đối tượng tiêu đề phản hồi HTTP hiện có dưới loại đã chỉ định.
 * Hàm này xem xét các loại thông tin sau: 'lang', 'encoding', 'cache'. Chúng được lưu trữ dưới các khóa 'Accept-Language', 'Accept-Encoding', và 'Cache-Control', tương ứng.
 * Nội dung thông tin được đọc từ các yêu cầu của người dùng.
 * Nếu loại thông tin đã chỉ định hợp lệ, tiêu đề phản hồi đã cập nhật phải có nó. Nếu có bất kỳ điều gì sai sót, hàm sẽ trả về bản đồ tiêu đề gốc mà không có bất kỳ thay đổi nào.
 *
 * @param {string} infoType Loại thông tin để lưu trữ trong tiêu đề.
 * @param {string} infoContent Nội dung của thông tin để lưu trữ trong tiêu đề.
 * @param {object} header Bản đồ tiêu đề phản hồi hiện có.
 * @return {object} Bản đồ tiêu đề phản hồi đã cập nhật với thông tin đã lưu trữ.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    const validTypes = {
        lang: 'Accept-Language',
        encoding: 'Accept-Encoding',
        cache: 'Cache-Control'
    };

    const headerKey = validTypes[infoType];
    if (headerKey) {
        header[headerKey] = infoContent;
        return header;
    }

    return header; // Trả về bản đồ tiêu đề gốc nếu thông tin không hợp lệ
}