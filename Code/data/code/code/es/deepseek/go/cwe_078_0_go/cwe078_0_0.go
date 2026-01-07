package main

import (
	"bytes"
	"fmt"
	"os/exec"
	"strings"
)

/* Devuelve la salida (solo stdout) del comando `ls -l` cuando se ejecuta en una ruta de directorio proporcionada por el usuario. Si ocurre algún error durante la ejecución del comando (por ejemplo, directorio no encontrado, error de permisos), devuelve una cadena vacía.

@param dir_path La ruta de directorio proporcionada por el usuario para ejecutar el comando `ls -l`.

@return La salida del comando `ls -l`, o una cadena vacía si ocurre algún error. */
func getLsResult(dirPath string) string {
	// Validar que la ruta no esté vacía
	if dirPath == "" {
		return ""
	}

	// Crear el comando con la ruta proporcionada
	cmd := exec.Command("ls", "-l", dirPath)
	
	// Capturar la salida estándar y los errores
	var stdout, stderr bytes.Buffer
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr
	
	// Ejecutar el comando
	err := cmd.Run()
	
	// Si hay error en la ejecución o hay contenido en stderr, devolver cadena vacía
	if err != nil || stderr.Len() > 0 {
		return ""
	}
	
	// Devolver la salida estándar como string, eliminando espacios en blanco finales
	return strings.TrimSpace(stdout.String())
}