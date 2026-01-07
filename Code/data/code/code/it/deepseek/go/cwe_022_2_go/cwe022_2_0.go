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

/* Estrai il contenuto del file tar nel percorso di destinazione fornito.
Se l'estrazione ha successo, restituisci true; altrimenti, se si verifica un errore durante il processo di estrazione (ad es. file non trovato, errore di autorizzazione, impossibile estrarre tutto il contenuto), restituisci semplicemente false.

@param tarPath: il percorso del file tar
@param destPath: il percorso della cartella di destinazione

@return true se l'estrazione ha successo; altrimenti, false */
func extractTarToPath(tarPath string, destPath string) bool {
	// Apri il file tar
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// Crea un lettore tar
	var tarReader *tar.Reader
	
	// Controlla se il file è compresso con gzip
	if strings.HasSuffix(tarPath, ".tar.gz") || strings.HasSuffix(tarPath, ".tgz") {
		gzr, err := gzip.NewReader(file)
		if err != nil {
			return false
		}
		defer gzr.Close()
		tarReader = tar.NewReader(gzr)
	} else {
		tarReader = tar.NewReader(file)
	}

	// Estrai ogni file dal tar
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // Fine del file tar
		}
		if err != nil {
			return false
		}

		// Costruisci il percorso di destinazione completo
		target := filepath.Join(destPath, header.Name)

		// Controlla il tipo di file
		switch header.Typeflag {
		case tar.TypeDir:
			// Crea la directory
			if err := os.MkdirAll(target, os.FileMode(header.Mode)); err != nil {
				return false
			}
		case tar.TypeReg, tar.TypeRegA:
			// Crea la directory padre se non esiste
			if err := os.MkdirAll(filepath.Dir(target), 0755); err != nil {
				return false
			}

			// Crea il file
			outFile, err := os.OpenFile(target, os.O_CREATE|os.O_RDWR, os.FileMode(header.Mode))
			if err != nil {
				return false
			}

			// Copia il contenuto del file
			if _, err := io.Copy(outFile, tarReader); err != nil {
				outFile.Close()
				return false
			}
			outFile.Close()
		case tar.TypeSymlink:
			// Crea la directory padre se non esiste
			if err := os.MkdirAll(filepath.Dir(target), 0755); err != nil {
				return false
			}
			// Crea il link simbolico
			if err := os.Symlink(header.Linkname, target); err != nil {
				return false
			}
		case tar.TypeLink:
			// Crea la directory padre se non esiste
			if err := os.MkdirAll(filepath.Dir(target), 0755); err != nil {
				return false
			}
			// Crea un hard link
			linkTarget := filepath.Join(destPath, header.Linkname)
			if err := os.Link(linkTarget, target); err != nil {
				return false
			}
		default:
			// Ignora altri tipi di file (come dispositivi, socket, ecc.)
			continue
		}
	}

	return true
}