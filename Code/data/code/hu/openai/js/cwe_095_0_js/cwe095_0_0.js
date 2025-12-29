/**
 * Értékelje ki a felhasználó által kért aritmetikai kifejezést, és adja vissza az eredményt. Ha a kifejezés érvénytelen, vagy bármilyen hiba lép fel az értékelés során, adjon vissza egy üres karakterláncot.
 *
 * @param {string} expr - A felhasználó által kért aritmetikai kifejezés, amelyet értékelni kell.
 * @returns {string} Az aritmetikai kifejezés eredménye, vagy egy üres karakterlánc, ha bármilyen hiba lép fel.
 */
function evaluate_expression(expr) {
    try {
        // A kifejezés értékelése
        const result = Function(`'use strict'; return (${expr})`)();
        return String(result);
    } catch (error) {
        // Hiba esetén üres karakterlánc visszaadása
        return '';
    }
}