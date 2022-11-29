// Por Roberto A.Zavala
// Breve : https://es.overleaf.com/read/ypbswnmywdcn
// Libro : https://www.amazon.com.mx/dp/B074TTGLL2
// 🙏🏼   : DNv7acPAeVBhTXbKv26itJecPG1SPy2o4F
// https://docs.google.com/spreadsheets/d/1v66FqD7zOg-H4kmhq8ojUr9T9_6hwO1IgihTE_KEoy4/edit?usp=sharing

int A = 6;              // puertos PWM                         
int B = 9;
int C = 10;
int D = 11;

int c;                  // Un contador de pasos
int f;                  // un contador de fase

int Paso [4][4]=        // matriz de estados paso simple
{
{1,0,0,0},
{0,1,0,0},
{0,0,1,0},            
{0,0,0,1},
};

int mPaso [8][4]=       // matriz de estados medio paso
{
{1,0,0,0},
{1,1,0,0},
{0,1,0,0},            
{0,1,1,0},
{0,0,1,0},
{0,0,1,1},
{0,0,0,1},
{1,0,0,1}
};

int tPaso [8][4]=       // matriz de estados alto torque
{
{1,1,0,0},
{0,1,1,0},
{0,0,1,1},
{1,0,0,1}
};

int Suave [145][4]=     // matriz de estados paso suave
{
{ 255.0 , 0.0 , 0.0 , 0 } ,
{ 254.8 , 11.1  , 0.0 , 0 } ,
{ 254.0 , 22.2  , 0.0 , 0 } ,
{ 252.8 , 33.3  , 0.0 , 0 } ,
{ 251.1 , 44.3  , 0.0 , 0 } ,
{ 249.0 , 55.2  , 0.0 , 0 } ,
{ 246.3 , 66.0  , 0.0 , 0 } ,
{ 243.2 , 76.7  , 0.0 , 0 } ,
{ 239.6 , 87.2  , 0.0 , 0 } ,
{ 235.6 , 97.6  , 0.0 , 0 } ,
{ 231.1 , 107.8 , 0.0 , 0 } ,
{ 226.2 , 117.7 , 0.0 , 0 } ,
{ 220.8 , 127.5 , 0.0 , 0 } ,
{ 215.1 , 137.0 , 0.0 , 0 } ,
{ 208.9 , 146.3 , 0.0 , 0 } ,
{ 202.3 , 155.2 , 0.0 , 0 } ,
{ 195.3 , 163.9 , 0.0 , 0 } ,
{ 188.0 , 172.3 , 0.0 , 0 } ,
{ 180.3 , 180.3 , 0.0 , 0 } ,
{ 172.3 , 188.0 , 0.0 , 0 } ,
{ 163.9 , 195.3 , 0.0 , 0 } ,
{ 155.2 , 202.3 , 0.0 , 0 } ,
{ 146.3 , 208.9 , 0.0 , 0 } ,
{ 137.0 , 215.1 , 0.0 , 0 } ,
{ 127.5 , 220.8 , 0.0 , 0 } ,
{ 117.7 , 226.2 , 0.0 , 0 } ,
{ 107.8 , 231.1 , 0.0 , 0 } ,
{ 97.6  , 235.6 , 0.0 , 0 } ,
{ 87.2  , 239.6 , 0.0 , 0 } ,
{ 76.7  , 243.2 , 0.0 , 0 } ,
{ 66.0  , 246.3 , 0.0 , 0 } ,
{ 55.2  , 249.0 , 0.0 , 0 } ,
{ 44.3  , 251.1 , 0.0 , 0 } ,
{ 33.3  , 252.8 , 0.0 , 0 } ,
{ 22.2  , 254.0 , 0.0 , 0 } ,
{ 11.1  , 254.8 , 0.0 , 0 } ,
{ 0.0 , 255.0 , 0.0 , 0 } ,
{ 0 , 254.8 , 11.1  , 0 } ,
{ 0 , 254.0 , 22.2  , 0 } ,
{ 0 , 252.8 , 33.3  , 0 } ,
{ 0 , 251.1 , 44.3  , 0 } ,
{ 0 , 249.0 , 55.2  , 0 } ,
{ 0 , 246.3 , 66.0  , 0 } ,
{ 0 , 243.2 , 76.7  , 0 } ,
{ 0 , 239.6 , 87.2  , 0 } ,
{ 0 , 235.6 , 97.6  , 0 } ,
{ 0 , 231.1 , 107.8 , 0 } ,
{ 0 , 226.2 , 117.7 , 0 } ,
{ 0 , 220.8 , 127.5 , 0 } ,
{ 0 , 215.1 , 137.0 , 0 } ,
{ 0 , 208.9 , 146.3 , 0 } ,
{ 0 , 202.3 , 155.2 , 0 } ,
{ 0 , 195.3 , 163.9 , 0 } ,
{ 0 , 188.0 , 172.3 , 0 } ,
{ 0 , 180.3 , 180.3 , 0 } ,
{ 0 , 172.3 , 188.0 , 0 } ,
{ 0 , 163.9 , 195.3 , 0 } ,
{ 0 , 155.2 , 202.3 , 0 } ,
{ 0 , 146.3 , 208.9 , 0 } ,
{ 0 , 137.0 , 215.1 , 0 } ,
{ 0 , 127.5 , 220.8 , 0 } ,
{ 0 , 117.7 , 226.2 , 0 } ,
{ 0 , 107.8 , 231.1 , 0 } ,
{ 0 , 97.6  , 235.6 , 0 } ,
{ 0 , 87.2  , 239.6 , 0 } ,
{ 0 , 76.7  , 243.2 , 0 } ,
{ 0 , 66.0  , 246.3 , 0 } ,
{ 0 , 55.2  , 249.0 , 0 } ,
{ 0 , 44.3  , 251.1 , 0 } ,
{ 0 , 33.3  , 252.8 , 0 } ,
{ 0 , 22.2  , 254.0 , 0 } ,
{ 0 , 11.1  , 254.8 , 0 } ,
{ 0 , 0.0 , 255.0 , 0 } ,
{ 0 , 0 , 254.8 , 11.1  } ,
{ 0.0 , 0.0 , 254.0 , 22.2  } ,
{ 0.0 , 0.0 , 252.8 , 33.3  } ,
{ 0.0 , 0.0 , 251.1 , 44.3  } ,
{ 0.0 , 0.0 , 249.0 , 55.2  } ,
{ 0.0 , 0.0 , 246.3 , 66.0  } ,
{ 0.0 , 0.0 , 243.2 , 76.7  } ,
{ 0.0 , 0.0 , 239.6 , 87.2  } ,
{ 0.0 , 0.0 , 235.6 , 97.6  } ,
{ 0.0 , 0.0 , 231.1 , 107.8 } ,
{ 0.0 , 0.0 , 226.2 , 117.7 } ,
{ 0.0 , 0.0 , 220.8 , 127.5 } ,
{ 0.0 , 0.0 , 215.1 , 137.0 } ,
{ 0.0 , 0.0 , 208.9 , 146.3 } ,
{ 0.0 , 0.0 , 202.3 , 155.2 } ,
{ 0.0 , 0.0 , 195.3 , 163.9 } ,
{ 0.0 , 0.0 , 188.0 , 172.3 } ,
{ 0.0 , 0.0 , 180.3 , 180.3 } ,
{ 0.0 , 0.0 , 172.3 , 188.0 } ,
{ 0.0 , 0.0 , 163.9 , 195.3 } ,
{ 0.0 , 0.0 , 155.2 , 202.3 } ,
{ 0.0 , 0.0 , 146.3 , 208.9 } ,
{ 0.0 , 0.0 , 137.0 , 215.1 } ,
{ 0.0 , 0.0 , 127.5 , 220.8 } ,
{ 0.0 , 0.0 , 117.7 , 226.2 } ,
{ 0.0 , 0.0 , 107.8 , 231.1 } ,
{ 0.0 , 0.0 , 97.6  , 235.6 } ,
{ 0.0 , 0.0 , 87.2  , 239.6 } ,
{ 0.0 , 0.0 , 76.7  , 243.2 } ,
{ 0.0 , 0.0 , 66.0  , 246.3 } ,
{ 0.0 , 0.0 , 55.2  , 249.0 } ,
{ 0.0 , 0.0 , 44.3  , 251.1 } ,
{ 0.0 , 0.0 , 33.3  , 252.8 } ,
{ 0.0 , 0.0 , 22.2  , 254.0 } ,
{ 0.0 , 0.0 , 11.1  , 254.8 } ,
{ 0.0 , 0.0 , 0.0 , 255.0 } ,
{ 11.1  , 0 , 0.0 , 254.8 } ,
{ 22.2  , 0.0 , 0.0 , 254.0 } ,
{ 33.3  , 0.0 , 0.0 , 252.8 } ,
{ 44.3  , 0.0 , 0.0 , 251.1 } ,
{ 55.2  , 0.0 , 0.0 , 249.0 } ,
{ 66.0  , 0.0 , 0.0 , 246.3 } ,
{ 76.7  , 0.0 , 0.0 , 243.2 } ,
{ 87.2  , 0.0 , 0.0 , 239.6 } ,
{ 97.6  , 0.0 , 0.0 , 235.6 } ,
{ 107.8 , 0.0 , 0.0 , 231.1 } ,
{ 117.7 , 0.0 , 0.0 , 226.2 } ,
{ 127.5 , 0.0 , 0.0 , 220.8 } ,
{ 137.0 , 0.0 , 0.0 , 215.1 } ,
{ 146.3 , 0.0 , 0.0 , 208.9 } ,
{ 155.2 , 0.0 , 0.0 , 202.3 } ,
{ 163.9 , 0.0 , 0.0 , 195.3 } ,
{ 172.3 , 0.0 , 0.0 , 188.0 } ,
{ 180.3 , 0.0 , 0.0 , 180.3 } ,
{ 188.0 , 0.0 , 0.0 , 172.3 } ,
{ 195.3 , 0.0 , 0.0 , 163.9 } ,
{ 202.3 , 0.0 , 0.0 , 155.2 } ,
{ 208.9 , 0.0 , 0.0 , 146.3 } ,
{ 215.1 , 0.0 , 0.0 , 137.0 } ,
{ 220.8 , 0.0 , 0.0 , 127.5 } ,
{ 226.2 , 0.0 , 0.0 , 117.7 } ,
{ 231.1 , 0.0 , 0.0 , 107.8 } ,
{ 235.6 , 0.0 , 0.0 , 97.6  } ,
{ 239.6 , 0.0 , 0.0 , 87.2  } ,
{ 243.2 , 0.0 , 0.0 , 76.7  } ,
{ 246.3 , 0.0 , 0.0 , 66.0  } ,
{ 249.0 , 0.0 , 0.0 , 55.2  } ,
{ 251.1 , 0.0 , 0.0 , 44.3  } ,
{ 252.8 , 0.0 , 0.0 , 33.3  } ,
{ 254.0 , 0.0 , 0.0 , 22.2  } ,
{ 254.8 , 0.0 , 0.0 , 11.1  } ,
{ 255.0 , 0.0 , 0.0 , 0.0 } 
};

void setup()
{
Serial.begin(9600);
pinMode(A,OUTPUT);
pinMode(B,OUTPUT);
pinMode(C,OUTPUT);
pinMode(D,OUTPUT);
}

void loop()
{
for (int i=0; i<=3; i++)           // Un ciclo de paso simple
    {
    digitalWrite(A, Paso[i][0]);
    digitalWrite(B, Paso[i][1]);
    digitalWrite(C, Paso[i][2]);
    digitalWrite(D, Paso[i][3]);
    Serial.println(i);
    delay(500);
    }

for (int i=0; i<=7; i++)           // Un ciclo de medio paso
    {
    digitalWrite(A, mPaso[i][0]);
    digitalWrite(B, mPaso[i][1]);
    digitalWrite(C, mPaso[i][2]);
    digitalWrite(D, mPaso[i][3]);
    Serial.println(i);
    delay(500);
    }
    
for (int i=0; i<=3; i++)           // Un ciclo de alto torque
    {
    digitalWrite(A, tPaso[i][0]);
    digitalWrite(B, tPaso[i][1]);
    digitalWrite(C, tPaso[i][2]);
    digitalWrite(D, tPaso[i][3]);
    Serial.println(i);
    delay(500);
    }

for (int i=0; i<=67; i++)           // Un ciclo de paso suave
    {
    analogWrite(A, Suave[i][0]);
    analogWrite(B, Suave[i][1]);
    analogWrite(C, Suave[i][2]);
    analogWrite(D, Suave[i][3]);
    Serial.println(i);
    delay(20);
    }
    
 while ( int i=0; i<100; i++ ) { Pas(); }
 while ( int i=0; i<100; i++ ) { paS(); }
}

void Pas ()
  {
  if ( f > 7 ) { f = 0; }
  digitalWrite(A, mPaso[f][0]);
  digitalWrite(B, mPaso[f][1]);
  digitalWrite(C, mPaso[f][2]);
  digitalWrite(D, mPaso[f][3]);
  delay(10);
  j++;
  }

void paS ()
  {
  if ( f < 0 ) { f = 7; }
  digitalWrite(A, mPaso[f][0]);
  digitalWrite(B, mPaso[f][1]);
  digitalWrite(C, mPaso[f][2]);
  digitalWrite(D, mPaso[f][3]);
  delay(20);
  i--;
  }
