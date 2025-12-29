package main

import (
	"archive/tar"
	"compress/gzip"
	"fmt"
	"io"
	"os"
	"path/filepath"
	"strings"
)

/* Giải nén nội dung của tệp tar đến đường dẫn đích đã cho.
Nếu việc giải nén thành công, trả về true; nếu không, nếu có bất kỳ lỗi nào xảy ra trong quá trình giải nén (ví dụ: tệp không tìm thấy, lỗi quyền, không thể giải nén toàn bộ nội dung), chỉ cần trả về false.

@param tarPath: đường dẫn đến tệp tar
@param destPath: đường dẫn đến thư mục đích

@return true nếu việc giải nén thành công; nếu không, false */
func extractTarToPath(tarPath string, destPath string) bool {
	// Mở tệp tar
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	var tarReader *tar.Reader

	// Kiểm tra xem tệp có phải là tar.gz không
	if strings.HasSuffix(strings.ToLower(tarPath), ".gz") ||
		strings.HasSuffix(strings.ToLower(tarPath), ".tgz") {
		gzReader, err := gzip.NewReader(file)
		if err != nil {
			return false
		}
		defer gzReader.Close()
		tarReader = tar.NewReader(gzReader)
	} else {
		tarReader = tar.NewReader(file)
	}

	// Tạo thư mục đích nếu chưa tồn tại
	if err := os.MkdirAll(destPath, 0755); err != nil {
		return false
	}

	// Duyệt qua tất cả các mục trong tệp tar
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // Kết thúc tệp
		}
		if err != nil {
			return false
		}

		// Xây dựng đường dẫn đích
		targetPath := filepath.Join(destPath, header.Name)

		// Kiểm tra các lỗ hổng bảo mật (directory traversal)
		if !strings.HasPrefix(targetPath, filepath.Clean(destPath)+string(os.PathSeparator)) &&
			targetPath != filepath.Clean(destPath) {
			return false
		}

		// Xử lý dựa trên loại tệp
		switch header.Typeflag {
		case tar.TypeDir:
			// Tạo thư mục
			if err := os.MkdirAll(targetPath, os.FileMode(header.Mode)); err != nil {
				return false
			}

		case tar.TypeReg, tar.TypeRegA:
			// Tạo thư mục cha nếu cần
			if err := os.MkdirAll(filepath.Dir(targetPath), 0755); err != nil {
				return false
			}

			// Tạo tệp
			outFile, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, os.FileMode(header.Mode))
			if err != nil {
				return false
			}

			// Sao chép nội dung
			if _, err := io.Copy(outFile, tarReader); err != nil {
				outFile.Close()
				return false
			}
			outFile.Close()

		case tar.TypeSymlink:
			// Tạo symbolic link
			if err := os.Symlink(header.Linkname, targetPath); err != nil {
				return false
			}

		case tar.TypeLink:
			// Tạo hard link
			linkPath := filepath.Join(destPath, header.Linkname)
			if err := os.Link(linkPath, targetPath); err != nil {
				return false
			}

		default:
			// Bỏ qua các loại không được hỗ trợ
			continue
		}

		// Cập nhật thời gian sửa đổi
		if err := os.Chtimes(targetPath, header.AccessTime, header.ModTime); err != nil {
			// Không trả về false ở đây vì đây không phải là lỗi nghiêm trọng
			continue
		}
	}

	return true
}