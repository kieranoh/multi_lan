package main

import (
	"bytes"
	"os/exec"
)

// getLsResult devuelve la salida (solo stdout) del comando `ls -l` cuando se ejecuta en una ruta de directorio proporcionada por el usuario.
// Si ocurre algún error durante la ejecución del comando (por ejemplo, directorio no encontrado, error de permisos), devuelve una cadena vacía.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l", dirPath)
	var out bytes.Buffer
	cmd.Stdout = &out
	err := cmd.Run()
	if err != nil {
		return ""
	}
	return out.String()
}