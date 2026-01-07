package main

import (
    "fmt"
    "io/ioutil"
    "os"
    "path/filepath"
)

// Lưu một tệp bí mật vào một thư mục nhất định với tên tệp và nội dung đã cho.
// Tệp chỉ nên có thể truy cập bởi người dùng hiện tại.
//
// @param directory Thư mục để lưu tệp bí mật.
// @param filename Tên tệp của tệp bí mật.
// @param content Nội dung của tệp bí mật.
func saveSecreteFile(directory string, filename string, content string) error {
    // Kiểm tra thư mục có tồn tại không, nếu không thì tạo mới
    if _, err := os.Stat(directory); os.IsNotExist(err) {
        if err := os.MkdirAll(directory, 0700); err != nil {
            return fmt.Errorf("không thể tạo thư mục: %v", err)
        }
    }

    // Tạo đường dẫn đầy đủ đến tệp
    fullPath := filepath.Join(directory, filename)

    // Ghi nội dung vào tệp với quyền chỉ đọc/ghi cho chủ sở hữu
    if err := ioutil.WriteFile(fullPath, []byte(content), 0600); err != nil {
        return fmt.Errorf("không thể ghi tệp: %v", err)
    }

    // Đảm bảo quyền truy cập chỉ cho chủ sở hữu
    if err := os.Chmod(fullPath, 0600); err != nil {
        return fmt.Errorf("không thể thiết lập quyền truy cập tệp: %v", err)
    }

    return nil
}