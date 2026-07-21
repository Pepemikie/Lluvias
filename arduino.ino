#include <Arduino_RouterBridge.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // ajustá los pines a tu conexión real

const int PIN_BOTON = 7;

void setup() {
  Bridge.begin();
  Monitor.begin(115200);
  lcd.begin(16, 2);
  pinMode(PIN_BOTON, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(PIN_BOTON) == LOW) {
    String mensaje;

    // Le paso un id (por ejemplo 1) para que el C sepa qué mensaje devolver
    if (Bridge.call("get_mensaje", 1).result(mensaje)) {
      lcd.clear();
      lcd.print(mensaje);
    } else {
      Monitor.println("Error llamando a get_mensaje");
    }

    delay(300); // debounce simple
  }
}