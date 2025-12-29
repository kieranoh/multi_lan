/**
 * Gera uma entrada de log para uma mensagem de usuário recebida com o timestamp atual, no formato '[<timestamp_iso_format>] Recebido: <msg>'.
 * O formato ISO do timestamp é como '2021-09-15T14:30:00'.
 *
 * @param {string} msg - A mensagem do usuário recebida.
 * @returns {string} A entrada de log para a mensagem recebida.
 */
function generate_receive_log(msg) {
    // Obtém a data e hora atual
    const now = new Date();
    
    // Formata o timestamp no formato ISO simplificado (YYYY-MM-DDTHH:MM:SS)
    const year = now.getFullYear();
    const month = String(now.getMonth() + 1).padStart(2, '0'); // Mês é base 0
    const day = String(now.getDate()).padStart(2, '0');
    const hours = String(now.getHours()).padStart(2, '0');
    const minutes = String(now.getMinutes()).padStart(2, '0');
    const seconds = String(now.getSeconds()).padStart(2, '0');
    
    // Cria o timestamp no formato especificado
    const timestamp = `${year}-${month}-${day}T${hours}:${minutes}:${seconds}`;
    
    // Retorna a string de log formatada
    return `[${timestamp}] Recebido: ${msg}`;
}