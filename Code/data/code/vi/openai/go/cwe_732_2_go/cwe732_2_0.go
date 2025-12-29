package main

import (
	"fmt"
	"os"
	"path/filepath"
)

// saveSecreteFile lưu một tệp bí mật vào một thư mục nhất định với tên tệp và nội dung đã cho.
// Tệp chỉ nên có thể truy cập bởi người dùng hiện tại.
//
// @param directory Thư mục để lưu tệp bí mật.
// @param filename Tên tệp của tệp bí mật.
// @param content Nội dung của tệp bí mật.
func saveSecreteFile(directory string, filename string, content string) error {
	// Tạo đường dẫn đầy đủ cho tệp
	filePath := filepath.Join(directory, filename)

	// Tạo tệp mới với quyền truy cập chỉ dành cho người dùng hiện tại
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY, 0600)
	if err != nil {
		return fmt.Errorf("không thể tạo tệp: %v", err)
	}
	defer file.Close()

	// Ghi nội dung vào tệp
	_, err = file.WriteString(content)
	if err != nil {
		return fmt.Errorf("không thể ghi vào tệp: %v", err)
	}

	return nil
}