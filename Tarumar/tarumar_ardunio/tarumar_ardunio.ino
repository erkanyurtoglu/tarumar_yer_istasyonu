// Motor pin tanımları (donanımınıza göre değiştirin)
#define LEFT_MOTOR_PWM 9   // Sol motor hız kontrolü (PWM)
#define RIGHT_MOTOR_PWM 10 // Sağ motor hız kontrolü (PWM)
#define LEFT_MOTOR_DIR 11  // Sol motor yön (1: ileri, 0: geri)
#define RIGHT_MOTOR_DIR 12 // Sağ motor yön (1: ileri, 0: geri)

// Hız sabitleri (PWM: 0-255)
#define SPEED_STOP 0
#define SPEED_SLOW 100      // Dik Engel
#define SPEED_MEDIUM 150    // Çakıllı Yol
#define SPEED_CAUTIOUS 80   // Yan Eğimli Yol
#define SPEED_FAST 255      // Hızlanma
#define SPEED_WATER 120     // Sudan Geçiş
#define SPEED_ROUGH 90      // Engebeli Arazi
#define SPEED_NAVIGATE_LEFT 100   // Trafik Konileri (sol motor)
#define SPEED_NAVIGATE_RIGHT 150  // Trafik Konileri (sağ motor)

// Mevcut hız değerlerini sakla
int currentLeftSpeed = 0;
int currentRightSpeed = 0;

void setup() {
  // Seri portu başlat
  Serial.begin(9600);
  Serial.println("TARUMAR aracı çalışıyor...");

  // Motor pinlerini ayarla
  pinMode(LEFT_MOTOR_PWM, OUTPUT);
  pinMode(RIGHT_MOTOR_PWM, OUTPUT);
  pinMode(LEFT_MOTOR_DIR, OUTPUT);
  pinMode(RIGHT_MOTOR_DIR, OUTPUT);

  // Motorları durdur
  stopMotors();
}

void loop() {
  // Seri porttan gelen komutları oku
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    Serial.println("Alınan komut: " + command);

    // Komutlara göre hareket
    if (command == "TERRAIN_1") {
      moveSlow(); // Dik Engel
    } else if (command == "TERRAIN_2") {
      moveMedium(); // Çakıllı Yol
    } else if (command == "TERRAIN_3") {
      moveCautious(); // Yan Eğimli Yol
    } else if (command == "TERRAIN_4") {
      moveFast(); // Hızlanma
    } else if (command == "TERRAIN_5") {
      moveWater(); // Sudan Geçiş
    } else if (command == "TERRAIN_6") {
      navigateObstacles(); // Trafik Konileri
    } else if (command == "TERRAIN_7") {
      moveRough(); // Engebeli Arazi
    } else if (command == "STOP") {
      stopMotors(); // Acil Durdurma
    } else {
      Serial.println("Geçersiz komut: " + command);
      stopMotors(); // Güvenlik için durdur
    }
  }

  // Hız verisini gönder
  float speed = calculateSpeed();
  Serial.println(speed, 2); // 2 ondalık basamak
  delay(100); // 100ms gecikme
}

void stopMotors() {
  analogWrite(LEFT_MOTOR_PWM, SPEED_STOP);
  analogWrite(RIGHT_MOTOR_PWM, SPEED_STOP);
  digitalWrite(LEFT_MOTOR_DIR, LOW);
  digitalWrite(RIGHT_MOTOR_DIR, LOW);
  currentLeftSpeed = SPEED_STOP;
  currentRightSpeed = SPEED_STOP;
  Serial.println("Motorlar durduruldu!");
}

void moveSlow() {
  analogWrite(LEFT_MOTOR_PWM, SPEED_SLOW);
  analogWrite(RIGHT_MOTOR_PWM, SPEED_SLOW);
  digitalWrite(LEFT_MOTOR_DIR, HIGH);
  digitalWrite(RIGHT_MOTOR_DIR, HIGH);
  currentLeftSpeed = SPEED_SLOW;
  currentRightSpeed = SPEED_SLOW;
  Serial.println("Yavaş hareket: Dik Engel");
}

void moveMedium() {
  analogWrite(LEFT_MOTOR_PWM, SPEED_MEDIUM);
  analogWrite(RIGHT_MOTOR_PWM, SPEED_MEDIUM);
  digitalWrite(LEFT_MOTOR_DIR, HIGH);
  digitalWrite(RIGHT_MOTOR_DIR, HIGH);
  currentLeftSpeed = SPEED_MEDIUM;
  currentRightSpeed = SPEED_MEDIUM;
  Serial.println("Orta hız: Çakıllı Yol");
}

void moveCautious() {
  analogWrite(LEFT_MOTOR_PWM, SPEED_CAUTIOUS);
  analogWrite(RIGHT_MOTOR_PWM, SPEED_CAUTIOUS);
  digitalWrite(LEFT_MOTOR_DIR, HIGH);
  digitalWrite(RIGHT_MOTOR_DIR, HIGH);
  currentLeftSpeed = SPEED_CAUTIOUS;
  currentRightSpeed = SPEED_CAUTIOUS;
  Serial.println("Dikkatli hareket: Yan Eğimli Yol");
}

void moveFast() {
  analogWrite(LEFT_MOTOR_PWM, SPEED_FAST);
  analogWrite(RIGHT_MOTOR_PWM, SPEED_FAST);
  digitalWrite(LEFT_MOTOR_DIR, HIGH);
  digitalWrite(RIGHT_MOTOR_DIR, HIGH);
  currentLeftSpeed = SPEED_FAST;
  currentRightSpeed = SPEED_FAST;
  Serial.println("Maksimum hız: Hızlanma");
}

void moveWater() {
  analogWrite(LEFT_MOTOR_PWM, SPEED_WATER);
  analogWrite(RIGHT_MOTOR_PWM, SPEED_WATER);
  digitalWrite(LEFT_MOTOR_DIR, HIGH);
  digitalWrite(RIGHT_MOTOR_DIR, HIGH);
  currentLeftSpeed = SPEED_WATER;
  currentRightSpeed = SPEED_WATER;
  Serial.println("Su geçirmez mod: Sudan Geçiş");
}

void navigateObstacles() {
  // Sağ dönüş yaparak konilerden kaçın
  analogWrite(LEFT_MOTOR_PWM, SPEED_NAVIGATE_LEFT);
  analogWrite(RIGHT_MOTOR_PWM, SPEED_NAVIGATE_RIGHT);
  digitalWrite(LEFT_MOTOR_DIR, HIGH);
  digitalWrite(RIGHT_MOTOR_DIR, HIGH);
  currentLeftSpeed = SPEED_NAVIGATE_LEFT;
  currentRightSpeed = SPEED_NAVIGATE_RIGHT;
  Serial.println("Engel navigasyonu: Trafik Konileri");
  delay(500); // Örnek dönüş süresi
  moveMedium(); // Düz devam
}

void moveRough() {
  analogWrite(LEFT_MOTOR_PWM, SPEED_ROUGH);
  analogWrite(RIGHT_MOTOR_PWM, SPEED_ROUGH);
  digitalWrite(LEFT_MOTOR_DIR, HIGH);
  digitalWrite(RIGHT_MOTOR_DIR, HIGH);
  currentLeftSpeed = SPEED_ROUGH;
  currentRightSpeed = SPEED_ROUGH;
  Serial.println("Engebeli hareket: Engebeli Arazi");
}

float calculateSpeed() {
  // PWM değerlerine göre hız hesapla (255 PWM ~ 6 km/h varsayımı)
  float speed = (currentLeftSpeed + currentRightSpeed) / 2.0 * 0.0235; // PWM'den km/h'e dönüşüm
  return speed;
}