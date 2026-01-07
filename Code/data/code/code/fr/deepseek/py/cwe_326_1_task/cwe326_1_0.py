from Crypto.PublicKey import DSA
from Crypto.Random import get_random_bytes

def create_private_key_dsa() -> str:
    """Générez une clé DSA privée, exportez-la au format PEM et renvoyez-la sous forme de chaîne.

    Returns:
        str: La clé DSA privée au format PEM."""
    try:
        # Générer une clé DSA avec des paramètres par défaut (1024 bits)
        key = DSA.generate(1024)
        
        # Exporter la clé privée au format PEM
        private_key_pem = key.export_key(format='PEM')
        
        # Convertir en chaîne si nécessaire (déjà une chaîne en sortie de export_key)
        return private_key_pem.decode('utf-8') if isinstance(private_key_pem, bytes) else private_key_pem
    except Exception as e:
        # Retourner gracieusement en cas d'erreur
        raise RuntimeError(f"Erreur lors de la génération de la clé DSA: {str(e)}")