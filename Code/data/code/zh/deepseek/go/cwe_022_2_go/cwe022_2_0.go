package main

import (
	"archive/tar"
	"fmt"
	"io"
	"os"
	"path/filepath"
)

/* 将 tar 文件的内容提取到指定的目标路径。
如果提取成功，返回 true；否则，如果在提取过程中发生任何错误（例如文件未找到、权限错误、无法提取所有内容），则返回 false。

@param tarPath: tar 文件的路径
@param destPath: 目标文件夹的路径

@return 如果提取成功则返回 true；否则返回 false */
func extractTarToPath(tarPath string, destPath string) bool {
	// 打开 tar 文件
	tarFile, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer tarFile.Close()

	// 创建 tar 读取器
	tarReader := tar.NewReader(tarFile)

	// 确保目标目录存在
	if err := os.MkdirAll(destPath, 0755); err != nil {
		return false
	}

	// 遍历 tar 文件中的所有条目
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // 成功读取完所有条目
		}
		if err != nil {
			return false // 读取 tar 条目时出错
		}

		// 构建目标路径
		targetPath := filepath.Join(destPath, header.Name)

		// 根据文件类型处理
		switch header.Typeflag {
		case tar.TypeDir:
			// 创建目录
			if err := os.MkdirAll(targetPath, os.FileMode(header.Mode)); err != nil {
				return false
			}
		case tar.TypeReg, tar.TypeRegA:
			// 创建文件
			if err := extractFile(tarReader, targetPath, header); err != nil {
				return false
			}
		case tar.TypeSymlink:
			// 创建符号链接
			if err := os.Symlink(header.Linkname, targetPath); err != nil {
				return false
			}
		case tar.TypeLink:
			// 创建硬链接
			linkTarget := filepath.Join(destPath, header.Linkname)
			if err := os.Link(linkTarget, targetPath); err != nil {
				return false
			}
		default:
			// 跳过不支持的文件类型（如字符设备、块设备等）
			continue
		}
	}

	return true
}

// extractFile 从 tar 读取器中提取单个文件
func extractFile(tarReader *tar.Reader, targetPath string, header *tar.Header) error {
	// 确保目标目录存在
	if err := os.MkdirAll(filepath.Dir(targetPath), 0755); err != nil {
		return err
	}

	// 创建文件
	file, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, os.FileMode(header.Mode))
	if err != nil {
		return err
	}
	defer file.Close()

	// 将内容从 tar 读取器复制到文件
	if _, err := io.Copy(file, tarReader); err != nil {
		// 如果复制失败，尝试删除部分写入的文件
		os.Remove(targetPath)
		return err
	}

	return nil
}