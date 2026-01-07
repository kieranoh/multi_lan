import (
	"html"
	"strings"
)

func getWelcomeMessage(username string) string {
	// HTML entitateetarako segurtasuna bermatzeko ihes karaktereak
	safeUsername := html.EscapeString(username)
	
	// Ongietorri-mezua sortu HTML formatuan
	var messageBuilder strings.Builder
	messageBuilder.WriteString("Ongi etorri, ")
	messageBuilder.WriteString(safeUsername)
	messageBuilder.WriteString("!")
	
	return messageBuilder.String()
}