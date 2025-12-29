package main

import (
	"fmt"
	"os"
	"path/filepath"
	"runtime"
	"syscall"
)

// saveSecreteFile 将秘密文件保存到指定目录，使用指定的文件名和内容。
// 该文件仅对当前用户可访问。
func saveSecreteFile(directory string, filename string, content string) error {
	// 创建目录如果不存在
	err := os.MkdirAll(directory, os.ModePerm)
	if err != nil {
		return fmt.Errorf("无法创建目录: %v", err)
	}

	// 定义文件路径
	filePath := filepath.Join(directory, filename)

	// 创建文件
	file, err := os.OpenFile(filePath, os.O_RDWR|os.O_CREATE|os.O_TRUNC, 0600)
	if err != nil {
		return fmt.Errorf("无法创建文件: %v", err)
	}
	defer file.Close()

	// 写入内容
	_, err = file.WriteString(content)
	if err != nil {
		return fmt.Errorf("无法写入文件: %v", err)
	}

	// 设置文件权限，仅限当前用户访问
	if runtime.GOOS == "linux" || runtime.GOOS == "darwin" {
		if err := syscall.Chmod(filePath, 0600); err != nil {
			return fmt.Errorf("无法设置文件权限: %v", err)
		}
	}

	return nil
}