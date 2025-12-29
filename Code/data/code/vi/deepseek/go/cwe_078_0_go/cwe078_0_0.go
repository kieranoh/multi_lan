package main

import (
	"bytes"
	"os"
	"os/exec"
)

// getLsResult trả về đầu ra (chỉ stdout) của lệnh `ls -l` khi nó được thực thi trong đường dẫn thư mục do người dùng cung cấp.
// Nếu có bất kỳ lỗi nào xảy ra trong quá trình thực thi lệnh (ví dụ: không tìm thấy thư mục, lỗi quyền truy cập), trả về một chuỗi rỗng.
//
// @param dir_path Đường dẫn thư mục do người dùng cung cấp để thực thi lệnh `ls -l`.
//
// @return Đầu ra của lệnh `ls -l`, hoặc một chuỗi rỗng nếu có bất kỳ lỗi nào xảy ra.
func getLsResult(dirPath string) string {
	// Kiểm tra xem thư mục có tồn tại và có thể truy cập được không
	if _, err := os.Stat(dirPath); err != nil {
		return ""
	}

	// Tạo lệnh `ls -l` với đường dẫn thư mục
	cmd := exec.Command("ls", "-l", dirPath)
	
	// Tạo buffer để lưu đầu ra stdout
	var stdout bytes.Buffer
	cmd.Stdout = &stdout
	
	// Thực thi lệnh
	if err := cmd.Run(); err != nil {
		return ""
	}
	
	// Trả về đầu ra dưới dạng chuỗi
	return stdout.String()
}