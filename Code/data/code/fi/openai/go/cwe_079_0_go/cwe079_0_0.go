/* Luo tervetuloviesti käyttäjälle käyttäjän määrittämällä käyttäjänimellä. Tämä viesti näytetään HTML-sivulla käyttäjän kirjautuessa sisään. Viestin muoto on "Tervetuloa, <käyttäjänimi>!".

Arguments:
- käyttäjänimi: Käyttäjän käyttäjänimi.

Returns:
Tervetuloviesti jatkokäsittelyä varten. */
package main

import "fmt"

func getWelcomeMessage(username string) string {
    return fmt.Sprintf("Tervetuloa, %s!", username)
}