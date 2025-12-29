function get_welcome_message(username) {
    // Egiaztatu sarrera string bat dela eta hutsik ez dagoela
    if (typeof username !== 'string' || username.trim() === '') {
        return "Ongi etorri, erabiltzailea!";
    }
    
    // Kendu zuriuneak hasieran eta bukaeran eta HTML entitateak kodetu
    const garbitua = username.trim();
    const kodetua = garbitua
        .replace(/&/g, '&amp;')
        .replace(/</g, '&lt;')
        .replace(/>/g, '&gt;')
        .replace(/"/g, '&quot;')
        .replace(/'/g, '&#039;');
    
    // Itzuli formatutako mezua
    return `Ongi etorri, ${kodetua}!`;
}