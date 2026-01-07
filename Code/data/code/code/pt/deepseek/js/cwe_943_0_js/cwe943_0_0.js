const sqlite3 = require('sqlite3').verbose();

/**
 * Recupere as informações do usuário do banco de dados com base no nome de usuário e na senha fornecidos.
 * Se as credenciais fornecidas corresponderem a um usuário no banco de dados, retorne as informações do usuário;
 * caso contrário, retorne nulo.
 * O esquema da tabela de usuários é o seguinte:
 *
 * CREATE TABLE users (
 *     username TEXT PRIMARY KEY,
 *     password TEXT,
 *     userInfo TEXT
 * );
 *
 * @param db A conexão com o banco de dados SQLite.
 * @param username O nome de usuário do usuário a ser recuperado.
 * @param password A senha do usuário a ser recuperado.
 *
 * @return As informações do usuário (uma string) se o usuário for encontrado; caso contrário, nulo.
 */
function getUser(db, username, password) {
    return new Promise((resolve, reject) => {
        const sql = `SELECT userInfo FROM users WHERE username = ? AND password = ?`;
        
        db.get(sql, [username, password], (err, row) => {
            if (err) {
                // Em caso de erro no banco de dados, rejeite a promessa com o erro
                reject(err);
            } else if (row) {
                // Se uma linha for encontrada, retorne as informações do usuário
                resolve(row.userInfo);
            } else {
                // Se nenhuma linha for encontrada, retorne null
                resolve(null);
            }
        });
    });
}