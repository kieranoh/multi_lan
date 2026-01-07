package main

import (
	"archive/tar"
	"io"
	"os"
	"path/filepath"
)

// extractTarToPath 将 tar 文件的内容提取到指定的目标路径。
// 如果提取成功，返回 true；否则，如果在提取过程中发生任何错误（例如文件未找到、权限错误、无法提取所有内容），则返回 false。
func extractTarToPath(tarPath string, destPath string) bool {
	// 打开 tar 文件
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// 创建一个新的 tar.Reader
	tarReader := tar.NewReader(file)

	// 遍历 tar 文件中的每个文件
	for {
		// 读取 tar 文件中的一个文件头
		header, err := tarReader.Next()
		if err == io.EOF {
			break // 读取完成
		}
		if err != nil {
			return false // 发生错误
		}

		// 创建目标文件的完整路径
		targetPath := filepath.Join(destPath, header.Name)

		// 根据文件类型处理
		switch header.Typeflag {
		case tar.TypeDir:
			// 创建目录
			if err := os.MkdirAll(targetPath, os.ModePerm); err != nil {
				return false
			}
		case tar.TypeReg:
			// 创建文件
			outFile, err := os.Create(targetPath)
			if err != nil {
				return false
			}
			defer outFile.Close()

			// 将 tar 内容复制到目标文件
			if _, err := io.Copy(outFile, tarReader); err != nil {
				return false
			}
		default:
			return false // 不支持的文件类型
		}
	}

	return true // 提取成功
}