//yapılacak işler
/*
sıcaklık değerinin alınması (yapıldı)
ve bu işlemin millis ile belirli aralıklarla yapılması(yapıldı)
sıcaklık değerininin lcd ekrana bastırılması(yapıldı)
sıcaklık değerinin karşılaştırılması(yapıldı)

*/
//library tanımlamaları
//lcd ekran için (i2c li)
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>



//lcd ekran tanımlaması
LiquidCrystal_I2C lcd(0x27,16,2);
//pin  tanımlamaları
//lm35
const int lm35=A1;
//motor kontrol kartı değişken tanımlamaları
const int motorKontrolKartipwmpin = 3;
const int motor1pinbir =8;
const int motor1piniki = 9;
//sabit değişken tanımlamaları(konfigrasyon)
const int delayTime = 1000; //ms cinsinden
const unsigned long msfarki = 1000;//millis fark değişkeni
const int motorgucu = 150; //motorun ne kadar güçte çalışacağı(0-255 arası bir değer yazın)
const float istenmiyensicaklikDegeri = 25.0;//kaç derece üstüne çıkılır ise motorun kapanacağı


//global değişken tanımlamaları
//millis değişkenleri
unsigned long eskiZaman=0;
unsigned long yeniZaman;
//sicaklikDurumbilgilendirmeTanimlanmasi
bool sicaklikDurum = true; // eğer sıcaklık normal ise true sıcaklık fazla ise false 

void setup() {
  //pinmode tanımlamaları
  pinMode(motor1pinbir,OUTPUT);
  pinMode(motor1piniki,OUTPUT);
  pinMode(motorKontrolKartipwmpin,OUTPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Coded By");
  lcd.setCursor(0,1);
  lcd.print("Fatih KILINC");
  delay(msfarki);
    
}

void loop() {
  analogWrite(motorKontrolKartipwmpin,motorgucu);
  yeniZaman = millis();
  if(yeniZaman - eskiZaman > msfarki){
    float sicaklik = sicaklikdegerinial();
    sicaklikDurum = (sicaklik > istenmiyensicaklikDegeri);
    if(sicaklikDurum){
      //buraya sıcaklık fazla ise ne yapılacağı yazılacak
      motorDurdur();
    }//sicaklikDurum if end
    else{
      motorCalistir();
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("sicaklik");
    lcd.print(" ");
    lcd.print(sicaklik);
    lcd.print(" C");
    String sicaklikDurumYazisi = sicaklikDurum ? "Fazla" : "normal";
    lcd.setCursor(0,1);
    lcd.print(sicaklikDurumYazisi);
    lcd.print("(");
    lcd.print(istenmiyensicaklikDegeri);
    lcd.print(" C)");
    Serial.print("Sıcaklık Degeri: "); //  Serial ekrana sıcaklık degeri yazdırıyoruz.
    Serial.print(sicaklik); // serial ekrana Sıcaklıgı yazdırıyoruz. 
    Serial.println(" C");
    /* Eski zaman değeri yeni zaman değeri ile güncelleniyor */
    eskiZaman = yeniZaman;
  }//millis if end

}


void motorCalistir(){
  digitalWrite(motor1pinbir,HIGH);
  digitalWrite(motor1piniki,LOW);
}

void motorDurdur(){
  digitalWrite(motor1pinbir,LOW);
  digitalWrite(motor1piniki,LOW);
}

float sicaklikdegerinial(){
  //kaynak:https://omerfarukyildiz.com/arduino-lm35-kullanimi/
  int deger=analogRead(lm35); //deger degişkenini lm35den gelen degere tanımlıyoruz. 
  float voltaj= deger* (5000/1024.0); //Lm35 sıcaklık degerinin hesaplamasını yapıyoruz. 
  float sicaklik= voltaj/10.0;
  return sicaklik;
}