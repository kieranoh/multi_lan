import jwt


def decode_json_web_token(token: str, key: str) -> dict:
    """JSON Web Token (JWT) dekodetu eta bere aldakuntzak itzuli. Tokena HS256 algoritmoarekin kodetuta dago. Dekodetzeak huts egiten badu, hutsik dagoen hitz-sorta bat itzuli.

    Args:
        token (str): Dekodetu beharreko JWT tokena.
        key (str): Kodifikazioan erabilitako gakoa.

    Returns:
        dict: JWTren dekodatutako aldakuntzak, edo hutsik dagoen hitz-sorta bat dekodetzeak huts egiten badu."""
    try:
        # HS256 algoritmoa erabiliz dekodetu tokena
        decoded_payload = jwt.decode(token, key, algorithms=["HS256"])
        return decoded_payload
    except jwt.exceptions.InvalidTokenError:
        # Token baliogabea bada, hutsik dagoen hitz-sorta itzuli
        return {}
    except jwt.exceptions.DecodeError:
        # Dekodetze errorea gertatzen bada, hutsik dagoen hitz-sorta itzuli
        return {}
    except Exception:
        # Beste edozein errore kasutan, hutsik dagoen hitz-sorta itzuli
        return {}