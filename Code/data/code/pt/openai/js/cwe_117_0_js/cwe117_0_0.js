/**
 * Gera uma entrada de log para uma mensagem de usuário recebida com o timestamp atual, no formato '[<timestamp_iso_format>] Recebido: <msg>'.
 * O formato ISO do timestamp é como '2021-09-15T14:30:00'.
 *
 * @param {string} msg - A mensagem do usuário recebida.
 * @returns {string} A entrada de log para a mensagem recebida.
 */
function generate_receive_log(msg) {
    const timestamp = new Date().toISOString(); // Obtém o timestamp atual no formato ISO
    return `[${timestamp}] Recebido: ${msg}`; // Retorna a string formatada
}