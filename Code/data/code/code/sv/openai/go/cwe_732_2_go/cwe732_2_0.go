package main

import (
	"fmt"
	"os"
	"path/filepath"
	"syscall"
)

// saveSecreteFile Spara en hemlig fil i en angiven katalog med ett angivet filnamn och innehåll.
// Filen ska endast vara tillgänglig för den nuvarande användaren.
func saveSecreteFile(directory string, filename string, content string) error {
	// Skapa den fullständiga sökvägen för den hemliga filen
	filePath := filepath.Join(directory, filename)

	// Skapa och skriv till filen
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0600) // Endast ägaren kan läsa och skriva
	if err != nil {
		return fmt.Errorf("kunde inte skapa fil: %v", err)
	}
	defer file.Close()

	// Skriv innehållet till filen
	_, err = file.WriteString(content)
	if err != nil {
		return fmt.Errorf("kunde inte skriva till fil: %v", err)
	}

	// Ställ in filens äganderätt till den aktuella användaren
	if err := os.Chown(filePath, os.Getuid(), os.Getgid()); err != nil {
		return fmt.Errorf("kunde inte ställa in äganderätt: %v", err)
	}

	return nil
}