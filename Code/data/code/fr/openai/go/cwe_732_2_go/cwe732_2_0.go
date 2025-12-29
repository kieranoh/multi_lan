package main

import (
	"fmt"
	"os"
	"path/filepath"
	"syscall"
)

// saveSecreteFile enregistre un fichier secret dans un répertoire donné avec un nom de fichier et un contenu spécifiés.
// Le fichier ne doit être accessible que par l'utilisateur actuel.
func saveSecreteFile(directory string, filename string, content string) error {
	// Créer le chemin complet du fichier
	filePath := filepath.Join(directory, filename)

	// Créer et ouvrir le fichier avec des permissions restreintes
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0600)
	if err != nil {
		return fmt.Errorf("erreur à l'ouverture du fichier: %w", err)
	}
	defer file.Close()

	// Écrire le contenu dans le fichier
	if _, err := file.WriteString(content); err != nil {
		return fmt.Errorf("erreur à l'écriture dans le fichier: %w", err)
	}

	// Changer les permissions du fichier pour s'assurer qu'il n'est accessible que par l'utilisateur
	if err := os.Chmod(filePath, 0600); err != nil {
		return fmt.Errorf("erreur à la modification des permissions du fichier: %w", err)
	}

	return nil
}