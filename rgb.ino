// Pin del LED RGB
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

// Struttura per lettere
struct Lettera {
  char simbolo;
  int red;
  int green;
  int blue;
  int lampeggi;
};

// Tabella codifica lettere (colori RGB + lampeggi)
Lettera codice[] = {
  {'A', 255, 0, 0, 1},      // Rosso
  {'B', 255, 0, 0, 2},
  {'C', 0,0,255, 1},      // Blu
  {'D', 0,0,255, 2},
  {'E', 255, 0, 255, 1},    // Viola
  {'F', 255, 0, 255, 2},
  {'G', 0, 255, 0, 1},      // Verde
  {'H', 0, 255, 0, 2},
  {'I', 150, 40, 0, 1},    // Giallo
  {'J', 150, 40, 0, 2},
  {'K', 255, 25, 0, 1},    // Arancione
  {'L', 255, 25, 0, 2},
  {'M', 255, 60,100,1 },  // Rosa
  {'N', 255, 60, 100, 2},
  {'O', 0, 255, 255, 1},    // Azzurro
  {'P', 0, 255, 255, 2},
  {'Q', 255, 100, 110, 1},  // Bianco
  {'R', 255, 100, 110, 2},
  {'S', 100, 0, 100, 1},    // Magenta
  {'T', 100, 0, 100, 2},
  {'U', 48, 255, 100, 1},   // Turchese
  {'V', 48, 255, 100, 2},
  {'W', 255, 100, 200, 1},  // Lavanda
  {'X', 255, 100, 200, 2},
  {'Y', 150, 100, 0, 1},      // Lime
  {'Z', 150, 100, 0, 2}
};

const int numLettere = sizeof(codice) / sizeof(codice[0]);

void setup() {
  Serial.begin(9600);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  Serial.println("Inserisci un messaggio da trasmettere:");
}

// Accende il LED RGB con colore specifico
void accendiLED(int r, int g, int b) {
  analogWrite(RED_PIN, r);
  analogWrite(GREEN_PIN, g);
  analogWrite(BLUE_PIN, b);
}

// Lampeggia LED RGB un certo numero di volte
void lampeggiaLED(int r, int g, int b, int volte) {
  for (int i = 0; i < volte; i++) {
    accendiLED(r, g, b);
    delay(500);
    accendiLED(0, 0, 0);
    delay(300);
  }
  delay(1000); // Pausa tra lettere
}

// Funzione per inviare messaggio
void inviaMessaggio(String messaggio) {
  messaggio.toUpperCase();
  for (int i = 0; i < messaggio.length(); i++) {
    char c = messaggio.charAt(i);

    // Considera solo lettere A-Z
    if (c < 'A' || c > 'Z') {
      continue; // Ignora caratteri non validi
    }

    for (int j = 0; j < numLettere; j++) {
      if (codice[j].simbolo == c) {
        lampeggiaLED(codice[j].red, codice[j].green, codice[j].blue, codice[j].lampeggi);
        break;
      }
    }
  }
}

void loop() {
  if (Serial.available()) {
    String messaggio = Serial.readStringUntil('\n');
    messaggio.trim();  // Rimuove spazi e ritorni a capo
    if (messaggio.length() > 0) {
      Serial.print("Trasmettendo messaggio: ");
      Serial.println(messaggio);
      inviaMessaggio(messaggio);
      Serial.println("Messaggio trasmesso. Inserisci un altro messaggio:");
    }
  }
}
