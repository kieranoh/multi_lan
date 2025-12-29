package main

import (
	"fmt"
	"os"
	"path/filepath"
	"golang.org/x/sys/windows"
)

// saveSecreteFile slaat een geheim bestand op in een opgegeven map met een opgegeven bestandsnaam en inhoud.
// Het bestand moet alleen toegankelijk zijn voor de huidige gebruiker.
func saveSecreteFile(directory string, filename string, content string) error {
	// Maak het volledige pad voor het bestand
	filePath := filepath.Join(directory, filename)

	// Maak en schrijf naar het bestand
	file, err := os.Create(filePath)
	if err != nil {
		return fmt.Errorf("kan bestand niet maken: %w", err)
	}
	defer file.Close()

	_, err = file.WriteString(content)
	if err != nil {
		return fmt.Errorf("kan inhoud niet schrijven: %w", err)
	}

	// Stel de bestandsrechten in om alleen toegang te geven aan de huidige gebruiker
	currentUser, err := windows.GetCurrentUserToken()
	if err != nil {
		return fmt.Errorf("kan huidige gebruiker token niet verkrijgen: %w", err)
	}

	sd, err := windows.SecurityDescriptorFromString("D:(A;O;FA;;;S-1-5-32-544)(A;O;FA;;;S-1-5-32-545)")
	if err != nil {
		return fmt.Errorf("kan beveiligingsdescriptor niet maken: %w", err)
	}

	err = windows.SetNamedSecurityInfo(
		filePath,
		windows.SE_FILE_OBJECT,
		windows.DACL_SECURITY_INFORMATION,
		nil,
		nil,
		sd,
		nil,
	)
	if err != nil {
		return fmt.Errorf("kan beveiligingsinstellingen niet instellen: %w", err)
	}

	return nil
}