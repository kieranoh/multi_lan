package main

import (
    "time"
)

/*
Gere uma entrada de log para uma mensagem de usuário recebida com o timestamp atual, no formato '[<timestamp_iso_format>] Recebido: <msg>'.

@param msg A mensagem do usuário recebida.

@return A entrada de log para a mensagem recebida.
*/
func generateReceiveLog(msg string) string {
    timestamp := time.Now().Format(time.RFC3339)
    return "[" + timestamp + "] Recebido: " + msg
}