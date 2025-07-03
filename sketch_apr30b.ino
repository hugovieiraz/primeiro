class Pin {
  private:
    int pinNumber;
  public:
    Pin(int pin) : pinNumber(pin) {
      pinMode(pinNumber, OUTPUT);
    }
    void setHigh() {
      digitalWrite(pinNumber, HIGH);
    }
    void setLow() {
      digitalWrite(pinNumber, LOW);
    }
};

class Buzzer {
  private:
    int buzzerPin;
  public:
    Buzzer(int bz) : buzzerPin(bz) {}
    void playTone(int frequency, int duration) {
      tone(buzzerPin, frequency, duration);
      delay(duration);
      noTone(buzzerPin);
      delay(2000);
    }
};

class Sensor {
  private:
    Pin pin1, pin2, pin3;
    Buzzer buzzer;
  public:
    Sensor(int p1, int p2, int p3, int bz) : pin1(p1), pin2(p2), pin3(p3), buzzer(bz) {}
    void checkGasLevel(int valor) {
      if (valor >= 1 && valor <= 45) {
        pin1.setHigh();
        pin2.setLow();
        pin3.setLow();
        delay(1000);
      } else if (valor > 40 && valor <=100) {
        pin2.setHigh();
        pin1.setLow();
        pin3.setLow();
        buzzer.playTone(500, 1000); 
      } else if (valor > 100) {
        pin3.setHigh();
        pin2.setLow();
        pin1.setLow();
        buzzer.playTone(800, 1000);
      }
    }
};

Sensor sensor(3, 4, 5, 6);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int valor = analogRead(A0);
  sensor.checkGasLevel(valor);
  Serial.println(valor);
}