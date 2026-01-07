import (
	"archive/tar"
	"compress/gzip"
	"fmt"
	"io"
	"os"
	"path/filepath"
	"strings"
)

func extractTarToPath(tarPath string, destPath string) bool {
	// Открываем tar-файл
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// Определяем, является ли файл gzip-сжатым
	var tarReader *tar.Reader
	if strings.HasSuffix(tarPath, ".tar.gz") || strings.HasSuffix(tarPath, ".tgz") {
		gzReader, err := gzip.NewReader(file)
		if err != nil {
			return false
		}
		defer gzReader.Close()
		tarReader = tar.NewReader(gzReader)
	} else {
		tarReader = tar.NewReader(file)
	}

	// Создаем директорию назначения, если она не существует
	if err := os.MkdirAll(destPath, 0755); err != nil {
		return false
	}

	// Извлекаем каждый файл из tar-архива
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // Конец архива
		}
		if err != nil {
			return false
		}

		// Безопасный путь назначения
		targetPath := filepath.Join(destPath, header.Name)
		if !strings.HasPrefix(targetPath, filepath.Clean(destPath)+string(os.PathSeparator)) {
			return false // Попытка выйти за пределы destPath
		}

		switch header.Typeflag {
		case tar.TypeDir:
			// Создаем директорию
			if err := os.MkdirAll(targetPath, os.FileMode(header.Mode)); err != nil {
				return false
			}
		case tar.TypeReg, tar.TypeRegA:
			// Создаем файл
			if err := os.MkdirAll(filepath.Dir(targetPath), 0755); err != nil {
				return false
			}
			outFile, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY, os.FileMode(header.Mode))
			if err != nil {
				return false
			}
			if _, err := io.Copy(outFile, tarReader); err != nil {
				outFile.Close()
				return false
			}
			outFile.Close()
		case tar.TypeSymlink:
			// Создаем символическую ссылку
			if err := os.Symlink(header.Linkname, targetPath); err != nil {
				return false
			}
		case tar.TypeLink:
			// Создаем жесткую ссылку
			linkTarget := filepath.Join(destPath, header.Linkname)
			if err := os.Link(linkTarget, targetPath); err != nil {
				return false
			}
		default:
			// Пропускаем неподдерживаемые типы файлов
			continue
		}
	}

	return true
}