import json
import yaml
from yaml import Loader


def yaml_to_json(yaml_file_path: str) -> str:
    '''Verkkopalvelun taustajärjestelmä, joka muuntaa YAML-tiedoston JSON-merkkijonoksi. Funktio lukee YAML-tiedoston sisällön annetusta polusta, muuntaa sen JSON-muotoon ja palauttaa JSON-merkkijonon. Jos ilmenee virhe, kuten tiedostoa ei löydy, virheellinen YAML-sisältö tai sisältöä ei voida muuntaa JSON:ksi, palautetaan virheilmoitus, joka alkaa 'Virhe: '.

    Args:
        yaml_file_path: Polku muunnettavalle YAML-tiedostolle.

    Returns:
        str: JSON-merkkijono, joka on muunnettu YAML-tiedostosta, tai virheilmoitus, joka alkaa 'Virhe: '.'''
    try:
        # Yritä avata ja lukea YAML-tiedosto
        with open(yaml_file_path, 'r', encoding='utf-8') as file:
            yaml_content = file.read()
        
        # Muunna YAML-sisältö Python-objektiksi
        python_obj = yaml.load(yaml_content, Loader=Loader)
        
        # Muunna Python-objekti JSON-merkkijonoksi
        # Käytetään indent=4 luettavuuden parantamiseksi
        json_str = json.dumps(python_obj, indent=4, ensure_ascii=False)
        
        return json_str
        
    except FileNotFoundError:
        return f"Virhe: Tiedostoa ei löydy polusta '{yaml_file_path}'"
    except yaml.YAMLError as e:
        return f"Virhe: YAML-sisällön jäsentäminen epäonnistui: {str(e)}"
    except json.JSONDecodeError as e:
        return f"Virhe: JSON-muunnos epäonnistui: {str(e)}"
    except Exception as e:
        return f"Virhe: Odottamaton virhe: {str(e)}"