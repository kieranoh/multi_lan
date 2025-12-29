package main

import (
	"io/ioutil"
	"os"
	"path/filepath"
)

// Enregistrez un fichier secret dans un répertoire donné avec un nom de fichier et un contenu spécifiés.
// Le fichier ne doit être accessible que par l'utilisateur actuel.
//
// @param directory Le répertoire pour enregistrer le fichier secret.
// @param filename Le nom du fichier secret.
// @param content Le contenu du fichier secret.
func saveSecreteFile(directory string, filename string, content string) error {
	// Vérifier si le répertoire existe, sinon le créer avec les permissions appropriées
	if _, err := os.Stat(directory); os.IsNotExist(err) {
		// Créer le répertoire avec des permissions restreintes (0700 = rwx------)
		if err := os.MkdirAll(directory, 0700); err != nil {
			return err
		}
	} else if err != nil {
		// Autre erreur lors de la vérification du répertoire
		return err
	}

	// Construire le chemin complet du fichier
	fullPath := filepath.Join(directory, filename)

	// Écrire le contenu dans un fichier temporaire d'abord
	tmpFile, err := ioutil.TempFile(directory, ".tmp_"+filename)
	if err != nil {
		return err
	}
	tmpPath := tmpFile.Name()

	// Écrire le contenu dans le fichier temporaire
	if _, err := tmpFile.Write([]byte(content)); err != nil {
		tmpFile.Close()
		os.Remove(tmpPath)
		return err
	}

	// Fermer le fichier temporaire
	if err := tmpFile.Close(); err != nil {
		os.Remove(tmpPath)
		return err
	}

	// Définir les permissions du fichier temporaire (0600 = rw-------)
	if err := os.Chmod(tmpPath, 0600); err != nil {
		os.Remove(tmpPath)
		return err
	}

	// Renommer le fichier temporaire vers le nom final
	if err := os.Rename(tmpPath, fullPath); err != nil {
		os.Remove(tmpPath)
		return err
	}

	return nil
}