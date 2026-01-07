/**
 * Genera una entrada de registro para un mensaje de usuario recibido con la marca de tiempo actual, en el formato '[<timestamp_iso_format>] Recibido: <msg>'.
 * El formato de marca de tiempo ISO es como '2021-09-15T14:30:00'.
 *
 * @param {string} msg - El mensaje de usuario recibido.
 * @returns {string} La entrada de registro para el mensaje recibido.
 */
function generate_receive_log(msg) {
    // Obtener la fecha y hora actual
    const now = new Date();
    
    // Formatear la fecha en formato ISO sin milisegundos y sin información de zona horaria
    const year = now.getFullYear();
    const month = String(now.getMonth() + 1).padStart(2, '0'); // Los meses son 0-indexados
    const day = String(now.getDate()).padStart(2, '0');
    const hours = String(now.getHours()).padStart(2, '0');
    const minutes = String(now.getMinutes()).padStart(2, '0');
    const seconds = String(now.getSeconds()).padStart(2, '0');
    
    // Crear la marca de tiempo en formato ISO (sin milisegundos)
    const timestamp = `${year}-${month}-${day}T${hours}:${minutes}:${seconds}`;
    
    // Construir y retornar la entrada de registro
    return `[${timestamp}] Recibido: ${msg}`;
}