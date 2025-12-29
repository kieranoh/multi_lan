package main

import (
	"archive/tar"
	"io"
	"log"
	"os"
	"path/filepath"
)

// extractTarToPath estrae il contenuto del file tar nel percorso di destinazione fornito.
// Se l'estrazione ha successo, restituisce true; altrimenti, restituisce false in caso di errore.
func extractTarToPath(tarPath string, destPath string) bool {
	// Apri il file tar
	file, err := os.Open(tarPath)
	if err != nil {
		log.Println("Errore nell'aprire il file tar:", err)
		return false
	}
	defer file.Close()

	// Crea un lettore tar
	tarReader := tar.NewReader(file)

	// Estrai i file dal tar
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // Fine dell'archivio tar
		}
		if err != nil {
			log.Println("Errore durante la lettura del file tar:", err)
			return false
		}

		// Calcola il percorso completo per il file estratto
		targetPath := filepath.Join(destPath, header.Name)

		switch header.Typeflag {
		case tar.TypeDir:
			// Crea la directory
			if err := os.MkdirAll(targetPath, os.ModePerm); err != nil {
				log.Println("Errore nella creazione della directory:", err)
				return false
			}
		case tar.TypeReg:
			// Crea i file regolari
			fileToWrite, err := os.OpenFile(targetPath, os.O_CREATE|os.O_RDWR, os.FileMode(header.Mode))
			if err != nil {
				log.Println("Errore nell'aprire il file per scrittura:", err)
				return false
			}

			// Copia il contenuto del file dal lettore tar al file
			if _, err := io.Copy(fileToWrite, tarReader); err != nil {
				fileToWrite.Close()
				log.Println("Errore nella scrittura del file:", err)
				return false
			}
			fileToWrite.Close()
		default:
			log.Println("Tipo di file non gestito:", header.Typeflag)
			return false
		}
	}

	return true
}