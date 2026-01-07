from typing import Dict
from lxml import etree


def get_student_info(
    xml_data: str, username: str, password: str
) -> Dict[str, str] | None:
    """Analizza i dati XML e restituisci le informazioni dello studente per il nome utente e la password forniti. I dati XML avranno la seguente struttura:
    <students>
        <student>
            <username>john_doe</username>
            <password>jdpassword</password>
            <name>John Doe</name>
            <citizenship>USA</citizenship>
            <age>25</age>
        </student>
        <student>
            <username>bob_smith</username>
            <password>bspassword</password>
            <name>Bob Smith</name>
            <citizenship>Canada</citizenship>
            <age>22</age>
        </student>
    </students>

    Possiamo costruire una query XPath e usarla per cercare.


    Args:
        xml_data: I dati XML contenenti le informazioni dello studente.
        username: Il nome utente dello studente da cercare
        password: La password dello studente da cercare

    Returns:
        Dict[str, str] | None: Un dizionario contenente le informazioni dello studente se lo studente viene trovato con il nome utente e la password forniti. Altrimenti, restituisci None."""
    try:
        # Parsing dei dati XML
        root = etree.fromstring(xml_data.encode('utf-8') if isinstance(xml_data, str) else xml_data)
        
        # Costruzione della query XPath per trovare lo studente con username e password corrispondenti
        xpath_query = f"//student[username='{username}' and password='{password}']"
        student_element = root.xpath(xpath_query)
        
        # Se non viene trovato nessuno studente, restituisci None
        if not student_element:
            return None
        
        # Prendi il primo elemento studente (dovrebbe essercene solo uno con username e password unici)
        student = student_element[0]
        
        # Estrai tutte le informazioni dello studente
        student_info = {}
        for child in student:
            tag = child.tag
            text = child.text
            if text is not None:
                student_info[tag] = text.strip()
        
        # Rimuovi username e password dal dizionario risultante se non richiesti
        # (la docstring non specifica se includerli, ma li includo per completezza)
        return student_info
        
    except etree.XMLSyntaxError:
        # Gestione errori di parsing XML
        return None
    except Exception:
        # Gestione di altri errori generici
        return None