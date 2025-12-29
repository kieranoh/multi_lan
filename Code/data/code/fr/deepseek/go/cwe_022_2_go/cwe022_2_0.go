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

/* Extraire le contenu du fichier tar vers le chemin de destination donné.
Si l'extraction réussit, retourner vrai ; sinon, si une erreur se produit pendant le processus d'extraction (par exemple, fichier non trouvé, erreur de permission, impossible d'extraire tout le contenu), retourner simplement faux.

@param tarPath: le chemin vers le fichier tar
@param destPath: le chemin vers le dossier de destination

@return vrai si l'extraction réussit ; sinon, faux */
func extractTarToPath(tarPath string, destPath string) bool {
    // Ouvrir le fichier tar
    file, err := os.Open(tarPath)
    if err != nil {
        return false
    }
    defer file.Close()

    var tarReader *tar.Reader

    // Détecter si c'est un fichier tar.gz ou tar
    if strings.HasSuffix(tarPath, ".gz") || strings.HasSuffix(tarPath, ".tgz") {
        gzReader, err := gzip.NewReader(file)
        if err != nil {
            return false
        }
        defer gzReader.Close()
        tarReader = tar.NewReader(gzReader)
    } else {
        tarReader = tar.NewReader(file)
    }

    // Créer le répertoire de destination s'il n'existe pas
    if err := os.MkdirAll(destPath, 0755); err != nil {
        return false
    }

    // Extraire chaque fichier du tar
    for {
        header, err := tarReader.Next()
        if err == io.EOF {
            break // Fin du fichier tar
        }
        if err != nil {
            return false
        }

        // Construire le chemin de destination
        targetPath := filepath.Join(destPath, header.Name)

        // Vérifier les attaques par traversal de chemin
        if !strings.HasPrefix(targetPath, filepath.Clean(destPath)+string(os.PathSeparator)) {
            return false
        }

        // Gérer le type de fichier
        switch header.Typeflag {
        case tar.TypeDir:
            // Créer le répertoire
            if err := os.MkdirAll(targetPath, os.FileMode(header.Mode)); err != nil {
                return false
            }

        case tar.TypeReg, tar.TypeRegA:
            // Créer le fichier
            dir := filepath.Dir(targetPath)
            if err := os.MkdirAll(dir, 0755); err != nil {
                return false
            }

            outFile, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, os.FileMode(header.Mode))
            if err != nil {
                return false
            }

            // Copier le contenu du fichier
            if _, err := io.Copy(outFile, tarReader); err != nil {
                outFile.Close()
                return false
            }
            outFile.Close()

        case tar.TypeSymlink:
            // Créer un lien symbolique
            if err := os.Symlink(header.Linkname, targetPath); err != nil {
                return false
            }

        case tar.TypeLink:
            // Créer un lien dur
            linkPath := filepath.Join(destPath, header.Linkname)
            if err := os.Link(linkPath, targetPath); err != nil {
                return false
            }

        default:
            // Ignorer les autres types (fifos, devices, etc.)
            continue
        }

        // Définir les permissions et timestamps
        if err := os.Chtimes(targetPath, header.AccessTime, header.ModTime); err != nil {
            // Continuer même si les timestamps échouent
        }
    }

    return true
}