package main

import (
	"os"
	"path/filepath"
	"io/ioutil"
	archive/tar"
	"log"
)

// extractTarToPath - Tarteko fitxategiaren edukia emandako helmuga bidera ateratzeko.
// Ateratzea arrakastatsua bada, itzuli true; bestela, ateratze prozesuan errore bat gertatzen bada (adibidez, fitxategia ez da aurkitu, baimen errorea, ez da eduki guztia ateratzen), itzuli false.
//
// @param tarPath: tar fitxategiaren bidea
// @param destPath: helmuga karpeta bidera
//
// @return ateratzea arrakastatsua bada, true; bestela, false
func extractTarToPath(tarPath string, destPath string) bool {
	file, err := os.Open(tarPath)
	if err != nil {
		log.Println("Error opening tar file:", err)
		return false
	}
	defer file.Close()

	tarReader := tar.NewReader(file)

	for {
		header, err := tarReader.Next()
		if err != nil {
			if err == io.EOF {
				break
			}
			log.Println("Error reading tar entry:", err)
			return false
		}

		targetPath := filepath.Join(destPath, header.Name)

		switch header.Typeflag {
		case tar.TypeDir:
			if err := os.MkdirAll(targetPath, os.ModePerm); err != nil {
				log.Println("Error creating directory:", err)
				return false
			}
		case tar.TypeReg:
			outFile, err := os.Create(targetPath)
			if err != nil {
				log.Println("Error creating file:", err)
				return false
			}
			defer outFile.Close()

			if _, err := io.Copy(outFile, tarReader); err != nil {
				log.Println("Error extracting file:", err)
				return false
			}
		default:
			log.Println("Unknown type:", header.Typeflag)
			return false
		}
	}

	return true
}