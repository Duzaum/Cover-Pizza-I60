String data;        // variable that will receive the software commands to activate the covers
char s;             // the "reset" to data variable
int f = 0;          //counter


#define PizzaSelect 2
#define TampaSelect 3
#define ModeSelect 6
#define CoverSelect 7
#define Tampa 8
#define Pizza 9
#define Selector 10

void setup() 
{
  Serial.begin(9600);
  Serial.println();
  Serial.println("Iniciado!");
 
  pinMode(ModeSelect,INPUT_PULLUP);  // if select is high the system will work as software switch
  pinMode(CoverSelect,INPUT_PULLUP);  // HIGH is cover / LOW is "pizza"
  pinMode(TampaSelect,INPUT_PULLUP);   // Low value close the mirror cover
  pinMode(PizzaSelect,INPUT_PULLUP);   // Low value close the "pizza" cover

  pinMode(Tampa,OUTPUT); //HIGH ACTIVATE
  pinMode(Pizza,OUTPUT); //HIGH ACTIVATE
  pinMode(Selector,OUTPUT); //HIGH IS COVER / LOW IS PIZZA

  delay(100);
}

void loop()
{
  serialRead();
  serialMapper();
  switchMapper();

  Serial.println(data);                 // print on serial the value that was received on serial
  f = 0;                                // reset the serial counter
  data = s;                             // reset the value stored from serial to receive new values
 
  delay(1000);                          // one second delay to not force the system because the system not demand much processement 
}


void serialRead()
{
  while (Serial.available() > 0 && f < 2)
   {
       char c = Serial.read();
       data += c;
       f = f+1 ;
   }
}


void serialMapper()   
{
  if (data == "ta"  && digitalRead(ModeSelect) == LOW)
    {
      digitalWrite(Tampa,HIGH);             // activate the relay plugged on pin 8 that work with the mirror telescope cover
      digitalWrite(Selector,HIGH);
      Serial.println("Tampa Software Ligar");
      delay(100);  
    }

  if (data == "tf" && digitalRead(ModeSelect) == LOW)
    {
      digitalWrite(Tampa,LOW);              // deactivate the relay plugged on pin 8 that work with the mirror telescope cover
      digitalWrite(Selector,HIGH);
      Serial.println("Tampa Software Desligar");
      delay(100);  
    }

  if (data == "pa" && digitalRead(ModeSelect) == LOW)
    {
      digitalWrite(Pizza,HIGH);             // activate the relay plugged on pin 9 tha work with the "pizza" telescope cover
      digitalWrite(Selector,LOW);
      Serial.println("Pizza Software Ligar");
      delay(100);  
    }

  if (data == "pf" && digitalRead(ModeSelect) == LOW)
    {
      digitalWrite(Pizza,LOW);             // deactivate the relay plugged on pin 9 tha work with the "pizza" telescope cover
      digitalWrite(Selector,LOW);
      Serial.println("Pizza Software Desligar");
      delay(100);  
    }
}


void switchMapper()   
{ 
  if (digitalRead(CoverSelect) == LOW && digitalRead(ModeSelect) == HIGH && digitalRead(TampaSelect) == LOW)
  {
      digitalWrite(Tampa,HIGH);              // deactivate the relay plugged on pin 8 that work with the mirror telescope cover
      digitalWrite(Selector,HIGH);
      Serial.println("Tampa Ligar");
      delay(100); 
  }

  if (digitalRead(CoverSelect) == LOW && digitalRead(ModeSelect) == HIGH && digitalRead(TampaSelect) == HIGH)
  {
      digitalWrite(Tampa,LOW);             // activate the relay plugged on pin 8 that work with the mirror telescope cover
      digitalWrite(Selector,HIGH);
      Serial.println("Tampa Desligar");
      delay(100);
  }

  if (digitalRead(CoverSelect) == HIGH && digitalRead(ModeSelect) == HIGH && digitalRead(PizzaSelect) == LOW)
  {
      digitalWrite(Pizza,HIGH);              // deactivate the relay plugged on pin 9 tha work with the "pizza" telescope cover
      digitalWrite(Selector,LOW);
      Serial.println("Pizza Ligar");
      delay(100); 
  }

  if (digitalRead(CoverSelect) == HIGH && digitalRead(ModeSelect) == HIGH && digitalRead(PizzaSelect) == HIGH)
  {
      digitalWrite(Pizza,LOW);              // activate the relay plugged on pin 9 tha work with the "pizza" telescope cover
      digitalWrite(Selector,LOW);
      Serial.println("Pizza Desligar");
      delay(100); 
  }
}