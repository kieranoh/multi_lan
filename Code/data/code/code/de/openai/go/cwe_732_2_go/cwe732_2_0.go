package main

import (
	"os"
	"path/filepath"
	"golang.org/x/sys/windows"
)

// saveSecreteFile speichert eine geheime Datei in einem bestimmten Verzeichnis mit einem bestimmten Dateinamen und Inhalt.
// Die Datei sollte nur für den aktuellen Benutzer zugänglich sein.
func saveSecreteFile(directory string, filename string, content string) error {
	// Erstelle das Verzeichnis, falls es nicht existiert
	err := os.MkdirAll(directory, os.ModePerm)
	if err != nil {
		return err
	}

	// Erstelle den vollständigen Pfad zur Datei
	filePath := filepath.Join(directory, filename)

	// Erstelle die Datei
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0600)
	if err != nil {
		return err
	}
	defer file.Close()

	// Schreibe den Inhalt in die Datei
	_, err = file.WriteString(content)
	if err != nil {
		return err
	}

	// Setze die Berechtigungen für die Datei, um sie nur für den aktuellen Benutzer zugänglich zu machen
	if err := setFilePermissions(filePath); err != nil {
		return err
	}

	return nil
}

// setFilePermissions konfiguriert die Berechtigungen der Datei, damit sie nur für den aktuellen Benutzer zugänglich ist.
func setFilePermissions(filePath string) error {
	// Holen Sie sich die aktuelle Benutzer-SID
	currentUser, err := windows.CurrentProcessToken()
	if err != nil {
		return err
	}
	defer currentUser.Close()

	// Setze die Sicherheitsattribute
	securityAttributes := &windows.SecurityAttributes{
		NLength:   uint32(unsafe.Sizeof(securityAttributes)),
		lpSecurityDescriptor: nil,
		bInheritHandle: false,
	}

	return windows.SetNamedSecurityInfo(
		windows.StringToUTF16Ptr(filePath),
		windows.SE_FILE_OBJECT,
		windows.DACL_SECURITY_INFORMATION,
		nil,
		nil,
		&currentUser,
		nil,
	)
}