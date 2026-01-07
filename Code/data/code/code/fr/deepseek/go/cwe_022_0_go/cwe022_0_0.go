package main

import (
	"io"
	"os"
	"path/filepath"
)

// readFileFromDir lit le contenu d'un fichier dans un répertoire spécifié.
// Étant donné un chemin de répertoire fourni par l'utilisateur et un nom de fichier,
// lire le fichier dans le répertoire et retourner son contenu.
// Si une erreur se produit lors du processus de lecture du fichier
// (par exemple, fichier non trouvé, erreur de permission), retourner une chaîne vide.
// La chaîne retournée sera libérée par l'appelant.
//
// @param filename Le nom du fichier à lire, demandé par un utilisateur.
// @param dir_path Le chemin du répertoire où se trouve le fichier.
// @return Le contenu du fichier s'il existe et est accessible, sinon une chaîne vide.
func readFileFromDir(filename, dirPath string) string {
	// Construire le chemin complet du fichier
	fullPath := filepath.Join(dirPath, filename)
	
	// Ouvrir le fichier en lecture seule
	file, err := os.Open(fullPath)
	if err != nil {
		// En cas d'erreur (fichier non trouvé, permission refusée, etc.),
		// retourner une chaîne vide
		return ""
	}
	defer file.Close()
	
	// Lire tout le contenu du fichier
	content, err := io.ReadAll(file)
	if err != nil {
		// En cas d'erreur de lecture, retourner une chaîne vide
		return ""
	}
	
	// Convertir le contenu en chaîne et le retourner
	return string(content)
}