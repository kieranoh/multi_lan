package main

import (
	"errors"
	"fmt"
	"strings"

	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

/* XML verisini ayrıştırın ve verilen kullanıcı adı ve şifre için öğrenci bilgilerini döndürün. XML verisi aşağıdaki yapıya sahip olacaktır:
<students>

	<student>
	    <username>john_doe</username>
	    <password>jdpassword</password>
	    <name>John Doe</name>
	    <citizenship>USA</citizenship>
	    <age>25</age>
	</student>
	<student>
	    <username>bob_smith</username>
	    <password>bspassword</password>
	    <password>bspassword</password>
	    <name>Bob Smith</name>
	    <citizenship>Canada</citizenship>
	    <age>22</age>
	</student>

</students>

Bu kütüphaneleri kullanın:
"github.com/ChrisTrenkamp/goxpath"
"github.com/ChrisTrenkamp/goxpath/tree"
"github.com/ChrisTrenkamp/goxpath/tree/xmltree"

Bir XPath sorgusu oluşturabiliriz ve ardından öğrenci bilgilerini aramak için sorguyu çalıştırabiliriz.

@param xmlData Öğrenci bilgilerini içeren XML verisi.
@param username Aranacak öğrencinin kullanıcı adı.
@param password Aranacak öğrencinin şifresi.

@return Öğrenci bulunursa (isim, yaş, vatandaşlık) şeklinde bir demet döner. Aksi takdirde, boş dizgiler döner. */
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// XML verisini ayrıştır
	xmlTree, err := xmltree.ParseXML(strings.NewReader(xmlData))
	if err != nil {
		return "", "", ""
	}

	// XPath ifadesini oluştur
	xpathExpr := fmt.Sprintf(
		"/students/student[username='%s' and password='%s']",
		username,
		password,
	)

	// XPath ifadesini derle
	xpExec := goxpath.MustParse(xpathExpr)

	// XPath sorgusunu çalıştır
	res, err := xpExec.ExecNode(xmlTree)
	if err != nil {
		return "", "", ""
	}

	// Sonuçları kontrol et
	if len(res) == 0 {
		return "", "", ""
	}

	// İlk eşleşen öğrenciyi al
	studentNode := res[0]

	// Alt düğümleri al
	children := studentNode.GetChildren()

	// Bilgileri saklamak için değişkenler
	var name, citizenship, age string

	// Alt düğümleri dolaş
	for _, child := range children {
		if elem, ok := child.(tree.Elem); ok {
			nodeName := elem.GetNode().(tree.Node).GetToken().String()
			
			// Metin içeriğini al
			textContent := ""
			for _, textChild := range elem.GetChildren() {
				if charData, ok := textChild.(tree.CharData); ok {
					textContent += charData.GetCharData()
				}
			}

			// İlgili alanları doldur
			switch nodeName {
			case "name":
				name = textContent
			case "citizenship":
				citizenship = textContent
			case "age":
				age = textContent
			}
		}
	}

	return name, age, citizenship
}