package main

import (
	"io"
	"os"
	"path/filepath"
)

// Givet en användarlevererad katalogväg och ett filnamn, läs filen från katalogen och returnera dess innehåll.
// Om något fel uppstår under filavläsningsprocessen (t.ex. filen hittades inte, behörighetsfel), returnera en tom sträng.
// Den returnerade strängen kommer att frigöras av anroparen.
//
// @param filename Namnet på filen som ska läsas, begärt av en användare.
// @param dir_path Vägen till katalogen där filen finns.
//
// @return Innehållet i filen om den finns och är tillgänglig, annars en tom sträng.
func readFileFromDir(filename, dirPath string) string {
	// Säkerställ att sökvägen är absolut och normaliserad
	fullPath := filepath.Join(dirPath, filename)
	
	// Öppna filen
	file, err := os.Open(fullPath)
	if err != nil {
		return ""
	}
	defer file.Close()
	
	// Läs filens innehåll
	content, err := io.ReadAll(file)
	if err != nil {
		return ""
	}
	
	return string(content)
}