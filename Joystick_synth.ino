int ejey = 0; //Valor del eje y
int ejex = 0; //Valor del eje x
//int boton = 0; // Estado del boton
int nota_oct = 36; //Nota DO Octava 3
int switch_nota_inicial = 0; //Estado del switch para seleccionar la nota inicial
int flag_notas_recorridas = 0; //Bandera notas recorridas para reinicio del contador
int flag_boton = 0; //Bandera del estado del boton para evitar varios pulsos
int nota_envio = 35; //Nota enviada
int led_indi_oct_up = 9, led_indi_oct_down = 8, les_indi_cambio_nota = 10, led_nota = 11;
int pot_ampli = 8, pot_selec = 9;
int control_ampli = 0, control_selec = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(led_indi_oct_up, OUTPUT);
  pinMode(led_indi_oct_down, OUTPUT);
  pinMode(les_indi_cambio_nota, OUTPUT);
  pinMode(led_nota, OUTPUT);
}

void loop() 
{
  ejex = int(map(analogRead(A0),0,1023,1,4));
  ejey = int(map(analogRead(A1),0,1023,1,4));
  ///////////Activacion y estados del switch del joystick///////////////////////
  switch_nota_inicial = digitalRead(2); ///Lectura de la entrada digital del switch

  if(switch_nota_inicial == 0)
    {
      flag_boton = 2; //El boton esta precionado
    }
    
  if(flag_boton == 2 && switch_nota_inicial == 1) //El boton esta precionado y se dejo de presionar
    {
      flag_boton = 3;
    }

///CAMBIO DE OCTAVA////////////
  if(flag_boton == 2 && ejex == 1) ///BAJANDO UNA OCTAVA
  {
    flag_boton = 4;
  }

    if(flag_boton == 2 && ejex == 4) ///BAJANDO UNA OCTAVA
  {
    flag_boton = 5;
  }

  if(flag_boton == 4 && (ejex == 2 || ejex == 3)) ///BAJANDO UNA OCTAVA
    {
      nota_oct = nota_oct - 12;
      flag_boton = 0;
      digitalWrite(led_indi_oct_down, HIGH);
    }

  if(flag_boton == 5 && (ejex == 2 || ejex == 3)) ///SUBIENDO UNA OCTAVA
    {
      nota_oct = nota_oct + 12;
      flag_boton = 0;
      digitalWrite(led_indi_oct_up, HIGH);
    }

///CAMBIO DE NOTA INICIAL//////

  if(flag_boton == 3) //Cambio de la nota inicial
  {
    nota_oct = nota_oct + 1;
    flag_notas_recorridas = flag_notas_recorridas + 1;
    flag_boton = 0;
    digitalWrite(les_indi_cambio_nota, HIGH);
      if(flag_notas_recorridas == 12) 
      {
        nota_oct = nota_oct - 12;
        flag_notas_recorridas = 0;
      }
  }

////POTENCIOMETROS//////////////////////////////
control_ampli = map(analogRead(pot_ampli), 0, 1023, 0, 127);
cc(0, 2, control_ampli);  
control_selec = map(analogRead(pot_selec), 0, 1023, 0, 7);
cc(0, 3, control_selec); 
////////IF ANIDADOS//////////////////////////////  
  if(ejex == 1 && ejey == 4)
  {
    nota_envio = nota_oct; //Grado I Escala
    digitalWrite(led_nota, HIGH);
    cc(0, 1, nota_envio);
  }
  else if(ejex == 2 && ejey == 4)
  {
    nota_envio = nota_oct;
    nota_envio = nota_oct + 2; //Grado II Escala
    digitalWrite(led_nota, HIGH);
    cc(0, 1, nota_envio);
  }
    else if(ejex == 3 && ejey == 4)
  {
    nota_envio = nota_oct;
    nota_envio = nota_oct + 4; //Grado III Escala
    digitalWrite(led_nota, HIGH);
    cc(0, 1, nota_envio);
  }
  else if(ejex == 4 && ejey == 4)
  {
    nota_envio = nota_oct;
    nota_envio = nota_oct + 5; //Grado IV Escala
    digitalWrite(led_nota, HIGH);
    cc(0, 1, nota_envio);
  }
  else if(ejex == 1 && ejey == 3)
  {
    nota_envio = nota_oct;
    nota_envio = nota_oct + 19; //Grado V Escala Octava Siguiente
    digitalWrite(led_nota, HIGH);
    cc(0, 1, nota_envio);
  }
  else if(ejex == 4 && ejey == 3)
  {
    nota_envio = nota_oct;
    nota_envio = nota_oct + 7; //Grado V Escala
    digitalWrite(led_nota, HIGH);
    cc(0, 1, nota_envio);
  }
  else if(ejex == 1 && ejey == 2)
  {
    nota_envio = nota_oct;
    nota_envio = nota_oct + 17; //Grado IV Escala Octava Siguiente
    digitalWrite(led_nota, HIGH);
    cc(0, 1, nota_envio);
  }
  else if(ejex == 4 && ejey == 2)
  {
    nota_envio = nota_oct;
    nota_envio = nota_oct + 9; //Grado VI
    digitalWrite(led_nota, HIGH);
    cc(0, 1, nota_envio);
  }
  else if(ejex == 1 && ejey == 1)
  {
    nota_envio = nota_oct;
    nota_envio = nota_oct + 16; //Grado III Escala Octava Siguiente
    digitalWrite(led_nota, HIGH);
    cc(0, 1, nota_envio);
  }
  else if(ejex == 2 && ejey == 1)
  {
    nota_envio = nota_oct;
    nota_envio = nota_oct + 14; //Grado II Escala Octava Siguiente
    digitalWrite(led_nota, HIGH);
    cc(0, 1, nota_envio);
  }
  else if(ejex == 3 && ejey == 1)
  {
    nota_envio = nota_oct;
    nota_envio = nota_oct + 12; //Grado I Escala Octava Siguiente
    digitalWrite(led_nota, HIGH);
    cc(0, 1, nota_envio);
  }
  else if(ejex == 4 && ejey == 1)
  {
    nota_envio = nota_oct;
    nota_envio = nota_oct + 11; //Grado VII Escala
    digitalWrite(led_nota, HIGH);
    cc(0, 1, nota_envio);
  }
  else
  {
    //Serial.println("EMPY");
    cc(0, 1, 0); ///NOTA MUDA
  }
///FIN DE IFs/////////////////////////////////
  delay(100);
  digitalWrite(led_indi_oct_down, LOW);
  digitalWrite(led_indi_oct_up, LOW);
  digitalWrite(les_indi_cambio_nota, LOW);
  digitalWrite(led_nota, LOW);
}


void cc(int chan, int num, int val) {
  int cmd = 0xb0 | chan;
  ///LIMITES DE NOTAS/////////////////
  if(val >= 127) val = 127;
  if(val <= 0) val = 0;
  Serial.write(cmd);
  Serial.write(num);
  Serial.write(val);
};
