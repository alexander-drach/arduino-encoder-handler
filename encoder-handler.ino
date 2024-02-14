#define CLK 5 // энкодер вращение
#define DT 6 // энкодер вращение
#define SW 7 // энкодер кнопка

#include <GyverEncoder.h>          // Добавляем необходимые библиотеки

Encoder enc(CLK, DT, SW);          // Инициализация энкодера

volatile int count = 0;   // счётчик влево/вправо
volatile int countLong = 0;   // счётчик нажатия с поворотом
volatile bool encFlag = 0;  // флаг поворота

void setup() {
  Serial.begin(9600);

  enc.setType(TYPE2);
  enc.setTickMode(AUTO);
}

void loop() {
  enc.tick(); 

  if (enc.isTurn()) {
    if (enc.isRight()) {      
      count++;
      printCount("right", count);
    } 
    if (enc.isLeft()) {      
      count--;
      printCount("left", count);
    } 

    if (enc.isRightH()) {
      countLong++;
      printCount("rightH", countLong);
    } 
    if (enc.isLeftH()) {
      countLong--;
      printCount("leftH", countLong);
    } 

    if (count <= -10) count = -10;
    if (count >= 10) count = 0;

    // Serial.println(countLong);

    // Serial.println(count);   
  }

  if (enc.isClick()) Serial.println("click"); // клик по кнопке
  if (enc.isHolded()) Serial.println("holded");  // долгое нажатие по кнопке
  if (enc.isDouble()) Serial.println("double click");  // долгое нажатие по кнопке
}

void printCount(String typeTurn, int count) {
  Serial.print(typeTurn);
  Serial.print(" : ");
  Serial.println(count);
}
