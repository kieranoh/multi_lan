package main

import (
	"io"
	"os"
	"path/filepath"
)

// readFileFromDir 从指定目录读取文件内容
// 给定用户提供的目录路径和文件名，从目录中读取文件并返回其内容。
// 如果在文件读取过程中发生任何错误（例如，文件未找到，权限错误），则返回一个空字符串。
// 返回的字符串将由调用者释放。
//
// @param filename 用户请求的要读取的文件名。
// @param dir_path 文件所在目录的路径。
//
// @return 如果文件存在且可访问，则返回文件的内容，否则返回一个空字符串。
func readFileFromDir(filename, dirPath string) string {
	// 构建完整的文件路径
	filePath := filepath.Join(dirPath, filename)
	
	// 打开文件
	file, err := os.Open(filePath)
	if err != nil {
		// 文件未找到、权限错误或其他错误时返回空字符串
		return ""
	}
	defer file.Close()
	
	// 读取文件内容
	content, err := io.ReadAll(file)
	if err != nil {
		// 读取过程中发生错误时返回空字符串
		return ""
	}
	
	// 将字节内容转换为字符串并返回
	return string(content)
}