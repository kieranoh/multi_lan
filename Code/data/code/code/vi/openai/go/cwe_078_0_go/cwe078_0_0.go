package main

import (
	"bytes"
	"os/exec"
)

// getLsResult trả về đầu ra (chỉ stdout) của lệnh `ls -l` khi nó được thực thi trong đường dẫn thư mục do người dùng cung cấp.
// Nếu có bất kỳ lỗi nào xảy ra trong quá trình thực thi lệnh (ví dụ: không tìm thấy thư mục, lỗi quyền truy cập), trả về một chuỗi rỗng.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l")
	cmd.Dir = dirPath

	var out bytes.Buffer
	cmd.Stdout = &out
	err := cmd.Run()
	if err != nil {
		return ""
	}
	return out.String()
}