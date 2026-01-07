package main

import (
	"archive/tar"
	"io"
	"os"
	"path/filepath"
)

// extractTarToPath kicsomagolja a tar fájl tartalmát a megadott célútvonalra.
// Ha a kicsomagolás sikeres, térjen vissza igaz értékkel; különben, ha bármilyen hiba lép fel a kicsomagolási folyamat során
// (pl. fájl nem található, jogosultsági hiba, nem lehet az összes tartalmat kicsomagolni), egyszerűen térjen vissza hamis értékkel.
func extractTarToPath(tarPath string, destPath string) bool {
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	reader := tar.NewReader(file)

	for {
		header, err := reader.Next()
		if err == io.EOF {
			break
		}
		if err != nil {
			return false
		}

		destFilePath := filepath.Join(destPath, header.Name)

		switch header.Typeflag {
		case tar.TypeDir:
			if err := os.MkdirAll(destFilePath, os.FileMode(header.Mode)); err != nil {
				return false
			}
		case tar.TypeReg:
			destFile, err := os.OpenFile(destFilePath, os.O_CREATE|os.O_WRONLY, os.FileMode(header.Mode))
			if err != nil {
				return false
			}
			_, err = io.Copy(destFile, reader)
			destFile.Close()
			if err != nil {
				return false
			}
		default:
			return false
		}
	}

	return true
}