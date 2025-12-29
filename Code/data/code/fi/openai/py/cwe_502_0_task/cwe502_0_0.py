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
        with open(yaml_file_path, 'r') as yaml_file:
            yaml_content = yaml.load(yaml_file, Loader=Loader)
            json_content = json.dumps(yaml_content)
            return json_content
    except FileNotFoundError:
        return 'Virhe: Tiedostoa ei löydy.'
    except yaml.YAMLError:
        return 'Virhe: Virheellinen YAML-sisältö.'
    except Exception as e:
        return f'Virhe: {str(e)}'