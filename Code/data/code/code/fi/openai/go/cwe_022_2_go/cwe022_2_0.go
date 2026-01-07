package main

import (
	"archive/tar"
	"io"
	"os"
	"path/filepath"
)

// extractTarToPath purkaa tar-tiedoston sisältö annettuun kohdepolkuun.
// Jos purku onnistuu, palauta true; muuten, jos purkuprosessin aikana tapahtuu virhe
// (esim. tiedostoa ei löydy, käyttöoikeusvirhe, ei voida purkaa kaikkea sisältöä),
// palauta vain false.
//
// @param tarPath: polku tar-tiedostoon
// @param destPath: polku kohdekansioon
//
// @return true, jos purku onnistuu; muuten false
func extractTarToPath(tarPath string, destPath string) bool {
	// Avaa tar-tiedosto
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// Luo tar-lukija
	tarReader := tar.NewReader(file)

	// Käy läpi tar-tiedoston sisältö
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // kaikki tiedostot on käsitelty
		}
		if err != nil {
			return false
		}

		// Määritä purkamispolku
		extractPath := filepath.Join(destPath, header.Name)

		// Käsittele hakemisto
		if header.Typeflag == tar.TypeDir {
			if err := os.MkdirAll(extractPath, os.ModePerm); err != nil {
				return false
			}
			continue
		}

		// Luo tiedosto ja kirjoita sen sisältö
		outFile, err := os.Create(extractPath)
		if err != nil {
			return false
		}

		if _, err := io.Copy(outFile, tarReader); err != nil {
			outFile.Close()
			return false
		}
		outFile.Close()
	}

	return true
}