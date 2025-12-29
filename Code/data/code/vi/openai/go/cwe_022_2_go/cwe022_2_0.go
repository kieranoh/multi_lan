package main

import (
	"archive/tar"
	"os"
	"path/filepath"
)

// extractTarToPath giải nén nội dung của tệp tar đến đường dẫn đích đã cho.
// Nếu việc giải nén thành công, trả về true; nếu không, nếu có bất kỳ lỗi nào xảy ra trong quá trình giải nén
// (ví dụ: tệp không tìm thấy, lỗi quyền, không thể giải nén toàn bộ nội dung), chỉ cần trả về false.
func extractTarToPath(tarPath string, destPath string) bool {
	// Mở tệp tar
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// Tạo một reader tar
	tarReader := tar.NewReader(file)

	// Giải nén từng phần tử trong tệp tar
	for {
		// Đọc phần tử kế tiếp
		header, err := tarReader.Next()
		if err != nil {
			if err == io.EOF {
				break // Đã đọc hết tệp
			}
			return false // Lỗi khi đọc tệp
		}

		// Tạo đường dẫn đầy đủ đến tệp hoặc thư mục
		targetPath := filepath.Join(destPath, header.Name)

		// Nếu là thư mục, tạo thư mục
		if header.Typeflag == tar.TypeDir {
			if err := os.MkdirAll(targetPath, os.ModePerm); err != nil {
				return false // Lỗi khi tạo thư mục
			}
			continue
		}

		// Nếu là tệp, tạo tệp
		targetFile, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY, os.FileMode(header.Mode))
		if err != nil {
			return false // Lỗi khi tạo tệp
		}

		// Sao chép nội dung tệp từ tar vào tệp mới
		if _, err := io.Copy(targetFile, tarReader); err != nil {
			targetFile.Close()
			return false // Lỗi khi sao chép nội dung
		}

		// Đóng tệp sau khi sao chép
		targetFile.Close()
	}

	return true // Giải nén thành công
}