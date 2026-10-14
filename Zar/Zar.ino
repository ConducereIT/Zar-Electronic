// Definirea pinilor ESP32 conectați la segmentele afișajului 7-segmente (prin rezistențe)
const int pinA = 23; // Pinul pentru segmentul A
const int pinB = 22; // Pinul pentru segmentul B
const int pinC = 21; // Pinul pentru segmentul C
const int pinD = 19; // Pinul pentru segmentul D
const int pinE = 18; // Pinul pentru segmentul E
const int pinF = 5;  // Pinul pentru segmentul F
const int pinG = 4;  // Pinul pentru segmentul G

// Definirea pinului pentru butonul tactil (push button)
const int buttonPin = 13; 

// Matricea de codificare pentru cifrele de la 0 la 6 (Catod Comun: HIGH aprinde segmentul)
// Ordinea segmentelor în matrice: {A, B, C, D, E, F, G}
const byte numbers[7][7] = {
  {0, 0, 0, 0, 0, 0, 0}, // 0: Gol (starea inițială)
  {0, 1, 1, 0, 0, 0, 0}, // 1: Segmentele B și C
  {1, 1, 0, 1, 1, 0, 1}, // 2: Segmentele A, B, D, E, G
  {1, 1, 1, 1, 0, 0, 1}, // 3: Segmentele A, B, C, D, G
  {0, 1, 1, 0, 0, 1, 1}, // 4: Segmentele B, C, F, G
  {1, 0, 1, 1, 0, 1, 1}, // 5: Segmentele A, C, D, F, G
  {1, 0, 1, 1, 1, 1, 1}  // 6: Segmentele A, C, D, E, F, G
};

void setup() {
  // Configurarea pinilor de segmente ca ieșiri (OUTPUT)
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);

  // Configurarea pinului butonului ca intrare cu rezistență internă de pull-up activată
  pinMode(buttonPin, INPUT_PULLUP);

  // Inițializarea generatorului de numere aleatoare folosind zgomotul de pe un pin analogic
  randomSeed(analogRead(34));

  // Afișează cifra 1 la pornirea sistemului
  displayNumber(1);
}

void loop() {
  // Verifică dacă butonul este apăsat (devine LOW datorită INPUT_PULLUP)
  if (digitalRead(buttonPin) == LOW) {
    rollDice();
  }
}

// Funcție pentru trimiterea stărilor către pinii segmentelor
void displayNumber(int num) {
  digitalWrite(pinA, numbers[num][0]);
  digitalWrite(pinB, numbers[num][1]);
  digitalWrite(pinC, numbers[num][2]);
  digitalWrite(pinD, numbers[num][3]);
  digitalWrite(pinE, numbers[num][4]);
  digitalWrite(pinF, numbers[num][5]);
  digitalWrite(pinG, numbers[num][6]);
}

// Funcția care simulează aruncarea zarului cu animație de rulare
void rollDice() {
  // Animație: afișează numere aleatoare rapid de 10 până la 15 ori
  int rolls = random(10, 16);
  for (int i = 0; i < rolls; i++) {
    int tempNum = random(1, 7);
    displayNumber(tempNum);
    delay(50 + (i * 10)); // Mărește treptat întârzierea pentru efectul de încetinire a zarului
  }

  // Extragerea rezultatului final al zarului (valoare între 1 și 6)
  int finalRoll = random(1, 7);
  displayNumber(finalRoll);

  // Mică pauză pentru a evita citirile multiple dertuburate (debounce)
  delay(300);
  
  // Așteaptă ca utilizatorul să elibereze butonul înainte de a permite o nouă aruncare
  while (digitalRead(buttonPin) == LOW) {
    delay(10);
  }
}