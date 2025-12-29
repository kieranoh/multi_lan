package main

import (
    "archive/tar"
    "io"
    "os"
    "path/filepath"
)

// extractTarToPath extrait le contenu du fichier tar vers le chemin de destination donné.
// Si l'extraction réussit, retourner vrai ; sinon, retourner faux.
func extractTarToPath(tarPath string, destPath string) bool {
    // Ouvrir le fichier tar
    tarFile, err := os.Open(tarPath)
    if err != nil {
        return false
    }
    defer tarFile.Close()

    // Créer un nouveau lecteur tar
    tarReader := tar.NewReader(tarFile)

    // Extraire chaque fichier dans l'archive
    for {
        header, err := tarReader.Next()
        if err == io.EOF {
            break // Fin de l'archive
        }
        if err != nil {
            return false // Erreur lors de la lecture de l'archive
        }

        // Construire le chemin de destination
        targetPath := filepath.Join(destPath, header.Name)

        // Vérifier si le fichier est un dossier
        if header.Typeflag == tar.TypeDir {
            // Créer le dossier
            if err := os.MkdirAll(targetPath, os.ModePerm); err != nil {
                return false // Erreur lors de la création du dossier
            }
            continue
        }

        // Créer le fichier destination
        outFile, err := os.Create(targetPath)
        if err != nil {
            return false // Erreur lors de la création du fichier
        }
        defer outFile.Close()

        // Copier le contenu du tar vers le fichier
        if _, err := io.Copy(outFile, tarReader); err != nil {
            return false // Erreur lors de la copie
        }
    }

    return true // Extraction réussie
}