package main

// getWelcomeMessage genera un mensaje de bienvenida para el usuario con el nombre de usuario especificado.
// El mensaje estará en el formato "¡Bienvenido, <username>!".
//
// Arguments:
// - username: El nombre de usuario del usuario.
//
// Returns:
// El mensaje de bienvenida para su posterior renderización.
func getWelcomeMessage(username string) string {
    return "¡Bienvenido, " + username + "!"
}