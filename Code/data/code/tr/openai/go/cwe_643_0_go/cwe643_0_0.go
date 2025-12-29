package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"encoding/xml"
	"strings"
)

// getStudentInfo XML verisini ayrıştırın ve verilen kullanıcı adı ve şifre için öğrenci bilgilerini döndürün.
// @param xmlData Öğrenci bilgilerini içeren XML verisi.
// @param username Aranacak öğrencinin kullanıcı adı.
// @param password Aranacak öğrencinin şifresi.
// @return Öğrenci bulunursa (isim, yaş, vatandaşlık) şeklinde bir demet döner. Aksi takdirde, boş dizgiler döner.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	var students struct {
		Students []struct {
			Username    string `xml:"username"`
			Password    string `xml:"password"`
			Name        string `xml:"name"`
			Citizenship string `xml:"citizenship"`
			Age         string `xml:"age"`
		} `xml:"student"`
	}

	// XML verisini ayrıştır
	err := xml.Unmarshal([]byte(xmlData), &students)
	if err != nil {
		return "", "", ""
	}

	// Öğrenci bilgilerini kontrol et
	for _, student := range students.Students {
		if student.Username == username && student.Password == password {
			return student.Name, student.Age, student.Citizenship
		}
	}

	return "", "", ""
}