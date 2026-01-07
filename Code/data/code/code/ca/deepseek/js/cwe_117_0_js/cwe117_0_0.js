function generate_receive_log(msg) {
    // Obtenir la data i hora actuals
    const now = new Date();
    
    // Format ISO 8601 sense mil·lisegons i sense informació de zona horària
    const year = now.getFullYear();
    const month = String(now.getMonth() + 1).padStart(2, '0'); // Els mesos comencen des de 0
    const day = String(now.getDate()).padStart(2, '0');
    const hours = String(now.getHours()).padStart(2, '0');
    const minutes = String(now.getMinutes()).padStart(2, '0');
    const seconds = String(now.getSeconds()).padStart(2, '0');
    
    // Crear la marca de temps en format ISO (YYYY-MM-DDThh:mm:ss)
    const timestamp = `${year}-${month}-${day}T${hours}:${minutes}:${seconds}`;
    
    // Retornar l'entrada de registre en el format especificat
    return `[${timestamp}] Rebut: ${msg}`;
}