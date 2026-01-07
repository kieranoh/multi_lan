package main

import (
	"io/ioutil"
	"path/filepath"
)

// readFileFromDir đọc tệp từ thư mục và trả về nội dung của nó.
// Nếu có bất kỳ lỗi nào xảy ra trong quá trình đọc tệp (ví dụ: tệp không tìm thấy, lỗi quyền truy cập),
// trả về một chuỗi rỗng. Chuỗi được trả về sẽ được giải phóng bởi người gọi.
//
// @param filename Tên của tệp cần đọc, được yêu cầu bởi người dùng.
// @param dirPath Đường dẫn của thư mục nơi tệp được đặt.
//
// @return Nội dung của tệp nếu nó tồn tại và có thể truy cập, nếu không thì là một chuỗi rỗng.
func readFileFromDir(filename, dirPath string) string {
	filePath := filepath.Join(dirPath, filename)
	content, err := ioutil.ReadFile(filePath)
	if err != nil {
		return ""
	}
	return string(content)
}