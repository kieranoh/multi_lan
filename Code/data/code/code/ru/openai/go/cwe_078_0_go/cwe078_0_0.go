package main

import (
	"bytes"
	"os/exec"
)

// Возвращает вывод (только stdout) команды `ls -l`, когда она выполняется в указанном пользователем пути к директории. 
// Если во время выполнения команды возникает ошибка (например, директория не найдена, ошибка доступа), возвращает пустую строку.
//
// @param dir_path Указанный пользователем путь к директории для выполнения команды `ls -l`.
//
// @return Вывод команды `ls -l`, или пустая строка, если возникает ошибка.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l")
	cmd.Dir = dirPath

	var out bytes.Buffer
	cmd.Stdout = &out

	err := cmd.Run()
	if err != nil {
		return ""
	}

	return out.String()
}