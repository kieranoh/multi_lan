import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """Egiaztatu emandako posta helbidea baliozkoa den. Adibidez, abc.123@def.ghi.com.uk posta helbide baliozkoa da. Falta negatiboak saihesteko kasu gehienak estali."""
    
    # Oinarrizko egiaztapenak
    if not isinstance(email, str):
        return False, "Posta helbidea kate bat izan behar da"
    
    if not email:
        return False, "Posta helbidea hutsa ezin da izan"
    
    # Datu garbiketa: zuriuneak kendu ertzetatik
    email = email.strip()
    
    # 1. @ ikurraren egiaztapena
    if '@' not in email:
        return False, "@ ikurra falta da"
    
    # @ ikurraren kopurua egiaztatu (bat baino gehiago ez)
    if email.count('@') != 1:
        return False, "@ ikur bat baino gehiago dago"
    
    # Lokala eta domeinua bereizi
    local_part, domain_part = email.split('@')
    
    # 2. Lokal zatia hutsa egiaztatu
    if not local_part:
        return False, "Lokal zatia hutsa dago"
    
    # 3. Domeinu zatia hutsa egiaztatu
    if not domain_part:
        return False, "Domeinu zatia hutsa dago"
    
    # 4. Lokal zatiaren luzera (RFC 5321: 64 karaktere gehienez)
    if len(local_part) > 64:
        return False, "Lokal zatia luzeegia da (64 karaktere gehienez)"
    
    # 5. Domeinu zatia puntu batekin amaitzen bada
    if domain_part.endswith('.'):
        return False, "Domeinu zatia ezin da puntu batekin amaitu"
    
    # 6. Domeinu zatia puntu batekin hasten bada
    if domain_part.startswith('.'):
        return False, "Domeinu zatia ezin da puntu batekin hasi"
    
    # 7. Puntu bikoiztuak domeinu zatian
    if '..' in domain_part:
        return False, "Domeinu zatian puntu bikoiztuak daude"
    
    # 8. Domeinu zatiko etiketak egiaztatu
    domain_labels = domain_part.split('.')
    
    # Domeinu zatian gutxienez puntu bat egon behar du
    if len(domain_labels) < 2:
        return False, "Domeinu zatian gutxienez puntu bat egon behar du"
    
    for label in domain_labels:
        # Etiketa hutsa egiaztatu (puntu bikoiztuak kasua jada tratatua baina berriro)
        if not label:
            return False, "Domeinu etiketa hutsa dago"
        
        # Etiketaren luzera (63 karaktere gehienez)
        if len(label) > 63:
            return False, f"Domeinu etiketa luzeegia: '{label}' (63 karaktere gehienez)"
        
        # Etiketak hasiera edo amaiera egiaztatu (jada tratatua baina berriro)
        if label.startswith('-') or label.endswith('-'):
            return False, f"Domeinu etiketa ezin da gidoi batekin hasi edo amaitu: '{label}'"
        
        # Etiketaren karaktere baliogabeak
        if not re.match(r'^[a-zA-Z0-9-]+$', label):
            return False, f"Domeinu etiketak karaktere baliogabeak ditu: '{label}'"
    
    # 9. Azken domeinu etiketa (TLD) egiaztatu
    tld = domain_labels[-1]
    if len(tld) < 2:
        return False, "Azken domeinu etiketak (TLD) gutxienez 2 karaktere izan behar ditu"
    
    if not re.match(r'^[a-zA-Z]{2,}$', tld):
        return False, "Azken domeinu etiketak (TLD) letrak bakarrik izan behar ditu"
    
    # 10. Lokal zatiaren karaktere baliogabeak
    # Karaktere onartuak: letrak, zenbakiak eta !#$%&'*+-/=?^_`{|}~. karaktere bereziak
    # Puntuak onartzen dira baina ezin dira hasieran, amaieran edo jarraian egon
    if not re.match(r'^[a-zA-Z0-9!#$%&\'*+/=?^_`{|}~-]+(\.[a-zA-Z0-9!#$%&\'*+/=?^_`{|}~-]+)*$', local_part):
        return False, "Lokal zatian karaktere baliogabeak daude"
    
    # 11. Puntu bikoiztuak lokal zatian
    if '..' in local_part:
        return False, "Lokal zatian puntu bikoiztuak daude"
    
    # 12. Lokal zatia puntu batekin hasten edo amaitzen bada
    if local_part.startswith('.') or local_part.endswith('.'):
        return False, "Lokal zatia ezin da puntu batekin hasi edo amaitu"
    
    # 13. Posta helbide osoaren luzera (RFC 5321: 254 karaktere gehienez)
    if len(email) > 254:
        return False, "Posta helbidea luzeegia da (254 karaktere gehienez)"
    
    # 14. Domeinu zatiko letra larriak (normaltze kasua)
    # Domeinu zatia minuskulatan bihurtu beharko litzateke, baina baliozkotasuna egiaztatzen ari gara
    # Hala ere, domeinu zatiko letra larriak onartzen dira baina normalizatu egin beharko lirateke
    
    # 15. Karaktere berezi gehigarriak lokal zatian
    # Lokal zatian onartzen diren karaktere bereziak: !#$%&'*+-/=?^_`{|}~
    # Dagoeneko tratatuta dago erregularki
    
    # 16. Aipatutako adibidearen kasua egiaztatu (abc.123@def.ghi.com.uk)
    # Adibide hori baliozkoa izan behar du
    
    return True, "Posta helbidea baliozkoa da"