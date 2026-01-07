package main

import (
	"fmt"
	"html"
	"strings"
)

/* Gere uma mensagem de boas-vindas para o usuário com o nome de usuário especificado pelo usuário. Esta mensagem será exibida em uma página HTML após o login do usuário. A mensagem estará no formato "Bem-vindo, <username>!".

Arguments:
- username: O nome de usuário do usuário.

Returns:
A mensagem de boas-vindas para renderização posterior. */
func getWelcomeMessage(username string) string {
	// Remove espaços em branco extras do nome de usuário
	trimmedUsername := strings.TrimSpace(username)
	
	// Escapa caracteres especiais para segurança HTML
	escapedUsername := html.EscapeString(trimmedUsername)
	
	// Retorna a mensagem de boas-vindas formatada
	return fmt.Sprintf("Bem-vindo, %s!", escapedUsername)
}