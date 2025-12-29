package main

import (
	"os"
	"path/filepath"
	"golang.org/x/sys/windows"
)

// saveSecreteFile Mentse el a titkos fájlt egy megadott könyvtárba a megadott fájlnévvel és tartalommal.
// A fájl csak a jelenlegi felhasználó számára legyen elérhető.
// @param directory A könyvtár, ahová a titkos fájlt menteni kell.
// @param filename A titkos fájl fájlneve.
// @param content A titkos fájl tartalma.
func saveSecreteFile(directory string, filename string, content string) error {
	// Hozzon létre egy fájl elérési utat
	filePath := filepath.Join(directory, filename)

	// Hozzon létre a fájlba írásra
	file, err := os.Create(filePath)
	if err != nil {
		return err
	}
	defer file.Close()

	// Írja bele a tartalmat
	_, err = file.WriteString(content)
	if err != nil {
		return err
	}

	// Állítsa be a fájl jogosultságait, hogy csak a jelenlegi felhasználó férhessen hozzá
	err = os.Chmod(filePath, 0600)
	if err != nil {
		return err
	}

	// Fájl tulajdonjogának beállítása a jelenlegi felhasználóra
	currentUser, err := os.UserHomeDir()
	if err != nil {
		return err
	}

	// Az aktuális felhasználó SID-jének megszerzése
	sid, err := windows.LookupAccountName("", currentUser)
	if err != nil {
		return err
	}

	// A fájl biztonsági attribútumainak beállítása
	secAttr := &windows.SecurityAttributes{
		Length: windows.SecurityAttributeLength,
		SecurityDescriptor: sid,
	}

	// Az új fájl létrehozása a megadott biztonsági attribútumokkal
	_, err = windows.CreateFile(
		filePath,
		windows.GENERIC_WRITE,
		windows.FILE_SHARE_READ,
		secAttr,
		windows.CREATE_ALWAYS,
		windows.FILE_ATTRIBUTE_NORMAL,
		0,
	)
	if err != nil {
		return err
	}

	return nil
}