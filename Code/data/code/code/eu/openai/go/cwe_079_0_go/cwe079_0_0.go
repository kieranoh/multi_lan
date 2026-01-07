/*
Sortu erabiltzaileak zehaztutako erabiltzaile-izena duen ongietorri-mezu bat. Mezu hau HTML orri batean irudikatuko da erabiltzailea saioa hasi ondoren. Mezuaren formatua "Ongi etorri, <erabiltzaile-izena>!" izango da.

Argudioak:
- erabiltzaile-izena: Erabiltzailearen erabiltzaile-izena.

Itzulpenak:
Ongietorri-mezua irudikatzeko.
*/
func getWelcomeMessage(username string) string {
    return "<h1>Ongi etorri, " + username + "!</h1>"
}