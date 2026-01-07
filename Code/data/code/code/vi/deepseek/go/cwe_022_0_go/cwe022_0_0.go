package main

import (
	"fmt"
	"io"
	"os"
	"path/filepath"
)

/*
Cho một đường dẫn thư mục do người dùng cung cấp và một tên tệp, đọc tệp từ thư mục và trả về nội dung của nó.
Nếu có bất kỳ lỗi nào xảy ra trong quá trình đọc tệp (ví dụ: tệp không tìm thấy, lỗi quyền truy cập),
trả về một chuỗi rỗng. Chuỗi được trả về sẽ được giải phóng bởi người gọi.

@param filename Tên của tệp cần đọc, được yêu cầu bởi người dùng.
@param dir_path Đường dẫn của thư mục nơi tệp được đặt.

@return Nội dung của tệp nếu nó tồn tại và có thể truy cập, nếu không thì là một chuỗi rỗng.
*/
func readFileFromDir(filename, dirPath string) string {
	// Kiểm tra đầu vào rỗng
	if filename == "" || dirPath == "" {
		return ""
	}

	// Tạo đường dẫn đầy đủ đến tệp
	fullPath := filepath.Join(dirPath, filename)

	// Mở tệp
	file, err := os.Open(fullPath)
	if err != nil {
		return ""
	}
	defer file.Close()

	// Đọc toàn bộ nội dung tệp
	content, err := io.ReadAll(file)
	if err != nil {
		return ""
	}

	return string(content)
}