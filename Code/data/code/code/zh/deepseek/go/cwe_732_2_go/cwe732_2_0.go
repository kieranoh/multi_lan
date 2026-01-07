package main

import (
	"os"
	"path/filepath"
)

// 将秘密文件保存到指定目录，使用指定的文件名和内容。
// 该文件仅对当前用户可访问。
//
// @param directory 保存秘密文件的目录。
// @param filename 秘密文件的文件名。
// @param content 秘密文件的内容。
func saveSecreteFile(directory string, filename string, content string) error {
	// 确保目录存在
	if err := os.MkdirAll(directory, 0700); err != nil {
		return err
	}
	
	// 构建完整的文件路径
	filePath := filepath.Join(directory, filename)
	
	// 创建文件，设置权限为仅当前用户可读写（0600）
	file, err := os.OpenFile(filePath, os.O_WRONLY|os.O_CREATE|os.O_TRUNC, 0600)
	if err != nil {
		return err
	}
	defer file.Close()
	
	// 写入内容
	_, err = file.WriteString(content)
	if err != nil {
		return err
	}
	
	// 确保数据写入磁盘
	err = file.Sync()
	if err != nil {
		return err
	}
	
	return nil
}