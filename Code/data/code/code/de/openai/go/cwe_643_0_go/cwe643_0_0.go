package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"encoding/xml"
	"strings"
)

// Student repräsentiert die Struktur eines Schülers in der XML-Daten
type Student struct {
	Username    string `xml:"username"`
	Password    string `xml:"password"`
	Name        string `xml:"name"`
	Citizenship string `xml:"citizenship"`
	Age         string `xml:"age"`
}

// getStudentInfo analysiert die XML-Daten und gibt die Informationen des Schülers für den angegebenen Benutzernamen und das Passwort zurück.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// XML-Daten parsen
	var students struct {
		Students []Student `xml:"student"`
	}
	if err := xml.Unmarshal([]byte(xmlData), &students); err != nil {
		return "", "", ""
	}

	// Überprüfen, ob der Benutzername und das Passwort übereinstimmen
	for _, student := range students.Students {
		if student.Username == username && student.Password == password {
			return student.Name, student.Age, student.Citizenship
		}
	}

	// Wenn kein passender Schüler gefunden wurde, leere Strings zurückgeben
	return "", "", ""
}