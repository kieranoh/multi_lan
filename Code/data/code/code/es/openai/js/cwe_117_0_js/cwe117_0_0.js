/* * Genera una entrada de registro para un mensaje de usuario recibido con la marca de tiempo actual, en el formato '[<timestamp_iso_format>] Recibido: <msg>'.
 * El formato de marca de tiempo ISO es como '2021-09-15T14:30:00'.
 *
 * @param {string} msg - El mensaje de usuario recibido.
 * @returns {string} La entrada de registro para el mensaje recibido. */
function generate_receive_log(msg) {
    const timestamp = new Date().toISOString().split('.')[0]; // Obtiene el timestamp actual en formato ISO sin milisegundos
    return `[${timestamp}] Recibido: ${msg}`;
}