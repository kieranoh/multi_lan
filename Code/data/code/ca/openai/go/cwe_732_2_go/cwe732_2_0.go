package main

import (
	"os"
	"path/filepath"
	"golang.org/x/sys/windows"
)

// saveSecreteFile desa un fitxer secret en un directori donat amb un nom de fitxer i contingut donats.
// El fitxer ha de ser accessible només pel usuari actual.
func saveSecreteFile(directory string, filename string, content string) error {
	// Crear el directori si no existeix
	if err := os.MkdirAll(directory, 0755); err != nil {
		return err
	}

	// Crear la ruta completa del fitxer
	filePath := filepath.Join(directory, filename)

	// Crear i escriure en el fitxer
	err := os.WriteFile(filePath, []byte(content), 0600) // permisos només per al propietari
	if err != nil {
		return err
	}

	// Ajustar els permisos del fitxer per fer-lo accessible només pel usuari actual (Windows)
	if err := windows.SetFileSecurity(filePath, windows.DACL_SECURITY_INFORMATION, nil); err != nil {
		return err
	}

	return nil
}