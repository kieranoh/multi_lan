package main

import (
	"archive/tar"
	"compress/gzip"
	"fmt"
	"io"
	"os"
	"path/filepath"
)

/* Purkaa tar-tiedoston sisältö annettuun kohdepolkuun.
Jos purku onnistuu, palauta true; muuten, jos purkuprosessin aikana tapahtuu virhe (esim. tiedostoa ei löydy, käyttöoikeusvirhe, ei voida purkaa kaikkea sisältöä), palauta vain false.

@param tarPath: polku tar-tiedostoon
@param destPath: polku kohdekansioon

@return true, jos purku onnistuu; muuten false */
func extractTarToPath(tarPath string, destPath string) bool {
	// Avaa tar-tiedosto
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// Käsittele gzip-pakattu tar-tiedosto jos tarve
	var tarReader *tar.Reader
	if filepath.Ext(tarPath) == ".gz" || filepath.Ext(tarPath) == ".tgz" {
		gzReader, err := gzip.NewReader(file)
		if err != nil {
			return false
		}
		defer gzReader.Close()
		tarReader = tar.NewReader(gzReader)
	} else {
		tarReader = tar.NewReader(file)
	}

	// Luo kohdekansio jos sitä ei ole olemassa
	if err := os.MkdirAll(destPath, 0755); err != nil {
		return false
	}

	// Käy läpi kaikki tar-tiedoston sisältämät tiedostot
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // Loppu saavutettu
		}
		if err != nil {
			return false
		}

		// Rakenna koko polku
		targetPath := filepath.Join(destPath, header.Name)

		// Tarkista tiedostotyyppi
		switch header.Typeflag {
		case tar.TypeDir:
			// Luo kansio
			if err := os.MkdirAll(targetPath, os.FileMode(header.Mode)); err != nil {
				return false
			}
		case tar.TypeReg, tar.TypeRegA:
			// Luo tiedosto
			if err := os.MkdirAll(filepath.Dir(targetPath), 0755); err != nil {
				return false
			}

			outFile, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY, os.FileMode(header.Mode))
			if err != nil {
				return false
			}

			// Kopioi tiedoston sisältö
			if _, err := io.Copy(outFile, tarReader); err != nil {
				outFile.Close()
				return false
			}
			outFile.Close()
		case tar.TypeSymlink:
			// Luo symbolinen linkki
			if err := os.Symlink(header.Linkname, targetPath); err != nil {
				return false
			}
		case tar.TypeLink:
			// Luo kova linkki
			linkTarget := filepath.Join(destPath, header.Linkname)
			if err := os.Link(linkTarget, targetPath); err != nil {
				return false
			}
		default:
			// Ohita muut tyypit (esim. laitteet)
			continue
		}
	}

	return true
}