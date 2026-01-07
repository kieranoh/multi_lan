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

func extractTarToPath(tarPath string, destPath string) bool {
	// Obrir el fitxer tar
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	var tarReader *tar.Reader

	// Comprovar si el fitxer està comprimit amb gzip
	if strings.HasSuffix(tarPath, ".tar.gz") || strings.HasSuffix(tarPath, ".tgz") {
		gzReader, err := gzip.NewReader(file)
		if err != nil {
			return false
		}
		defer gzReader.Close()
		tarReader = tar.NewReader(gzReader)
	} else if strings.HasSuffix(tarPath, ".tar") {
		tarReader = tar.NewReader(file)
	} else {
		// Format no suportat
		return false
	}

	// Crear el directori de destinació si no existeix
	if err := os.MkdirAll(destPath, 0755); err != nil {
		return false
	}

	// Iterar a través dels arxius del tar
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // Final del fitxer
		}
		if err != nil {
			return false
		}

		// Construir la ruta de destinació
		targetPath := filepath.Join(destPath, header.Name)

		// Validar que la ruta estigui dins del directori de destinació per evitar atacs de path traversal
		if !strings.HasPrefix(targetPath, filepath.Clean(destPath)+string(os.PathSeparator)) {
			return false
		}

		// Gestionar diferents tipus d'entrades
		switch header.Typeflag {
		case tar.TypeDir:
			// Crear directori
			if err := os.MkdirAll(targetPath, os.FileMode(header.Mode)); err != nil {
				return false
			}
		case tar.TypeReg, tar.TypeRegA:
			// Crear fitxer
			if err := os.MkdirAll(filepath.Dir(targetPath), 0755); err != nil {
				return false
			}

			outFile, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, os.FileMode(header.Mode))
			if err != nil {
				return false
			}

			// Copiar contingut del fitxer
			if _, err := io.CopyN(outFile, tarReader, header.Size); err != nil && err != io.EOF {
				outFile.Close()
				return false
			}
			outFile.Close()
		case tar.TypeSymlink:
			// Crear enllaç simbòlic
			if err := os.Symlink(header.Linkname, targetPath); err != nil {
				return false
			}
		case tar.TypeLink:
			// Crear enllaç dur
			linkTarget := filepath.Join(destPath, header.Linkname)
			if err := os.Link(linkTarget, targetPath); err != nil {
				return false
			}
		default:
			// Tipus no suportat
			return false
		}

		// Actualitzar timestamps
		if err := os.Chtimes(targetPath, header.AccessTime, header.ModTime); err != nil {
			// No retornem false aquí ja que és un error menor
			continue
		}
	}

	return true
}