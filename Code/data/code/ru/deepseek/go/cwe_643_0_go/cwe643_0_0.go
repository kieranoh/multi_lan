package main

import (
	"strings"

	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Парсим XML-данные
	xmlTree, err := xmltree.ParseXML(strings.NewReader(xmlData))
	if err != nil {
		return "", "", ""
	}

	// Создаем XPath-запрос для поиска студента с заданным именем пользователя и паролем
	xpathExpr := goxpath.MustParse(
		"/students/student[username='" + username + "' and password='" + password + "']",
	)

	// Выполняем запрос
	res, err := xpathExpr.ExecNode(xmlTree)
	if err != nil {
		return "", "", ""
	}

	// Проверяем, найден ли студент
	if len(res) == 0 {
		return "", "", ""
	}

	// Получаем первый найденный элемент student (должен быть только один)
	studentNode := res[0]

	// Функция для извлечения текстового содержимого дочернего элемента
	getChildText := func(parent tree.Node, childName string) string {
		xpathChild := goxpath.MustParse(childName)
		childRes, err := xpathChild.ExecNode(parent)
		if err != nil || len(childRes) == 0 {
			return ""
		}
		
		// Получаем текстовое содержимое элемента
		if elem, ok := childRes[0].(tree.Elem); ok {
			return elem.GetToken().String()
		}
		return ""
	}

	// Извлекаем информацию о студенте
	name := getChildText(studentNode, "name")
	age := getChildText(studentNode, "age")
	citizenship := getChildText(studentNode, "citizenship")

	return name, age, citizenship
}