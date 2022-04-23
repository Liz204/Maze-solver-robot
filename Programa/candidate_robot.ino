
//Motor derecho
int PinIN1_de = 12;
int PinIN2_de = 11;
int EN_de = 6;

//Motor izquierdo
int PinIN1_iz = 10;
int PinIN2_iz = 9;
int EN_iz = 5;

//Sensor fronal
int front_trg = 8;
int front_ec = A5;

//Sensor izquierdo
int left_trg = 7;
int left_ec = A4;

//Sensor derecho
int right_trg = 4;
int right_ec = A3;

//Lector frontal
int front_lector = A2;

//Lector izquierdo
int left_lector = A1;

//Lector derecho
int right_lector = A0;

float front_m = 0;
float left_m = 0;
float right_m = 0;

void setup() {


// Inicializacion de monitor serial
  Serial.begin(9600);

  pinMode(PinIN1_de, OUTPUT);
  pinMode(PinIN2_de, OUTPUT);
  pinMode(EN_de, OUTPUT);

  pinMode(PinIN1_iz, OUTPUT);
  pinMode(PinIN2_iz, OUTPUT);
  pinMode(EN_iz, OUTPUT);

  pinMode(front_trg, OUTPUT);
  pinMode(front_ec, INPUT);

  pinMode(left_trg, OUTPUT);
  pinMode(left_ec, INPUT);

  pinMode(right_trg, OUTPUT);
  pinMode(right_ec, INPUT);

  pinMode(front_lector, INPUT);
  pinMode(left_lector, INPUT);
  pinMode(right_lector, INPUT);

  digitalWrite(front_trg,LOW);
  digitalWrite(left_trg,LOW);
  digitalWrite(right_trg,LOW);

  digitalWrite(EN_de,75);
  digitalWrite(EN_iz,75);
  Serial.print("s_l\t s_f\t s_r\t\t");
  Serial.println();
}

//Funcion de medicion de sensores ultrasonido
// Parametros ---> (puerto echo, puerto triger)
float measure(int ec,int trg){
  long t; //tiempo
  long d; //centimetros
  digitalWrite(trg, HIGH);
  delayMicroseconds(10);
  digitalWrite(trg, LOW);

  t = pulseIn(ec, HIGH); 
  d = t/59;

  Serial.print(d);
  Serial.print("cm\t");
  delay(50);
  return d; 
}

//Giro Derecha
void Right()
{
  digitalWrite (PinIN1_de, HIGH);
  digitalWrite (PinIN2_de, LOW);
  digitalWrite (PinIN1_iz, HIGH);
  digitalWrite (PinIN2_iz, LOW);
  digitalWrite(EN_de,50);
  digitalWrite(EN_iz,50);
}

//Giro izquierda
void Left()
{
  digitalWrite (PinIN1_de, LOW);
  digitalWrite (PinIN2_de, HIGH);
  digitalWrite (PinIN1_iz, LOW);
  digitalWrite (PinIN2_iz, HIGH);
  digitalWrite(EN_de,50);
  digitalWrite(EN_iz,50);
}

//Derecho
void Front()
{
  digitalWrite (PinIN1_de, HIGH);
  digitalWrite (PinIN2_de, LOW);
  digitalWrite (PinIN1_iz, LOW);
  digitalWrite (PinIN2_iz, HIGH);
  digitalWrite(EN_de,40);
  digitalWrite(EN_iz,40);
}

//Derecho con desface hacia derecha
void Right_front()
{
  digitalWrite (PinIN1_de, HIGH);
  digitalWrite (PinIN2_de, LOW);
  digitalWrite (PinIN1_iz, LOW);
  digitalWrite (PinIN2_iz, HIGH);
  digitalWrite(EN_de,10);
  digitalWrite(EN_iz,200);
}

//Derecho con desface a izquierda
void Left_front()
{
  digitalWrite (PinIN1_de, HIGH);
  digitalWrite (PinIN2_de, LOW);
  digitalWrite (PinIN1_iz, LOW);
  digitalWrite (PinIN2_iz, HIGH);
  digitalWrite(EN_de,200);
  digitalWrite(EN_iz,10);
}

//Detener motor
void Stop()
{
  digitalWrite (PinIN1_de, LOW);
  digitalWrite (PinIN2_de, LOW);
  digitalWrite (PinIN1_iz, LOW);
  digitalWrite (PinIN2_iz, LOW);
}

//Sin programar 
void calibrar(){
  Stop();
  }

//Algoritmo seguir linea
int followLine(){
  int f = digitalRead(front_lector);
  int l = digitalRead(left_lector);
  int r = digitalRead(right_lector);
  Serial.print("l\tf\tr\t");
    while(l!=1 || r!=1){
        f = digitalRead(front_lector);
        l = digitalRead(left_lector);
        r = digitalRead(right_lector);
        if(l==1 && r==0){
          Left_front();
        }
        else if(l==0 && r==1){
          Right_front();
        }
        else{
          Front();
        }
        Serial.print(l);
        Serial.print("\t");
        Serial.print(f);
        Serial.print("\t");
        Serial.print(r);
        Serial.println();
      }
    return 1;
  
}


//Programa inicial
void loop() {
    
    followLine();
    Serial.println();
  
  
}
