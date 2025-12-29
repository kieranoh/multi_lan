package main

import "fmt"

// getWelcomeMessage генерирует приветственное сообщение для пользователя с указанным именем пользователя.
func getWelcomeMessage(username string) string {
    return fmt.Sprintf("Добро пожаловать, %s!", username)
}