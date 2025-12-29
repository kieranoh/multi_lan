from Crypto.PublicKey import RSA
from Crypto.PublicKey.RSA import RsaKey

def create_private_key() -> str:
    """Générez une clé RSA privée, exportez-la au format PEM et renvoyez-la sous forme de chaîne.

    Returns:
        str: La clé RSA privée au format PEM."""
    try:
        # Générer une paire de clés RSA avec une taille de 2048 bits (standard sécurisé)
        key = RSA.generate(2048)
        
        # Exporter la clé privée au format PEM
        private_key_pem = key.export_key(format='PEM')
        
        # Convertir en chaîne si nécessaire (export_key() retourne bytes)
        if isinstance(private_key_pem, bytes):
            private_key_str = private_key_pem.decode('utf-8')
        else:
            private_key_str = str(private_key_pem)
            
        return private_key_str
    except Exception as e:
        # Retourner une chaîne vide en cas d'erreur pour un retour gracieux
        # Vous pourriez aussi logger l'erreur dans un contexte réel
        return f""