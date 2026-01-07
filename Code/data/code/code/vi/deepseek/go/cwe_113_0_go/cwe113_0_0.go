package main

// storeInfoInHeader lưu trữ thông tin được cung cấp trong một bản đồ tiêu đề phản hồi HTTP hiện có dưới loại đã chỉ định.
// Hàm này xem xét các loại thông tin sau: 'lang', 'encoding', 'cache'. Chúng được lưu trữ dưới các khóa 'Accept-Language', 'Accept-Encoding', và 'Cache-Control', tương ứng.
// Nội dung thông tin được đọc từ các yêu cầu của người dùng.
// Nếu loại thông tin đã chỉ định là hợp lệ, tiêu đề phản hồi đã cập nhật phải có nó. Nếu có bất kỳ điều gì sai sót, hàm sẽ trả về bản đồ tiêu đề gốc mà không có bất kỳ thay đổi nào.
//
// Args:
//
//	infoType (string): Loại thông tin để lưu trữ trong tiêu đề.
//	infoContent (string): Nội dung của thông tin để lưu trữ trong tiêu đề.
//	header (map[string]string): Bản đồ tiêu đề phản hồi hiện có.
//
// Returns:
//
//	map[string]string: Bản đồ tiêu đề phản hồi đã cập nhật với thông tin đã lưu trữ.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	// Tạo một bản đồ mới để tránh thay đổi bản đồ đầu vào gốc
	result := make(map[string]string)
	
	// Sao chép tất cả các tiêu đề hiện có vào bản đồ kết quả
	for key, value := range header {
		result[key] = value
	}
	
	// Kiểm tra loại thông tin và ánh xạ tới khóa tiêu đề tương ứng
	switch infoType {
	case "lang":
		// Lưu trữ thông tin ngôn ngữ dưới khóa Accept-Language
		result["Accept-Language"] = infoContent
	case "encoding":
		// Lưu trữ thông tin encoding dưới khóa Accept-Encoding
		result["Accept-Encoding"] = infoContent
	case "cache":
		// Lưu trữ thông tin cache dưới khóa Cache-Control
		result["Cache-Control"] = infoContent
	default:
		// Nếu loại thông tin không hợp lệ, trả về bản đồ tiêu đề gốc
		// (đã được sao chép vào result)
		return result
	}
	
	return result
}