/*

  Trabalho de IEC Turma 2020.2
  @equipe ALEMA
  --version 1.4 - data 28/06/2021

*/
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

//Criando as conexões dos elementos do circuito
#define BOTAO_1 10
#define BOTAO_2 9 
#define BOTAO_3 8
#define BOTAO_4 12

#define MOTOR 11

byte Cedilha[8]={B00000,B11110,B10000,B10000,B10000,B11110,B00100,B01000};

//Variáveis p/ controle de ações das funções
unsigned short int tempMotor, hora, minut = 1, sec;
bool bcachorro = 0, 
     bgato = 0, 
     bfilhote = 0, 
     badulto = 0, 
     ligaMotor = 0, 
     entraNaFuncao = 0, 
     qac = 0, 
     qag = 0, 
     qfc = 0, 
     qfg = 0;
     
//Variáveis responsáveis pela a configuração do relógio.
bool state1 = 0; //Controla o botão p/ ajustar a hora
bool state2 = 0; //Controla o botão p/ ajustar os minutos
unsigned short int h = 0;
unsigned short int m = 0;
unsigned short int s = 0;

void setup() {
    lcd.begin(16, 2);

    lcd.createChar(1, Cedilha);
    pinMode(BOTAO_1, INPUT);
    pinMode(BOTAO_2, INPUT);
    pinMode(BOTAO_3, INPUT);
    pinMode(MOTOR, OUTPUT); 
    InstrucaoHora();
}

void loop() {
  if (bcachorro == 0 && bgato == 0 && entraNaFuncao == 1){
    while (1){
      lcd.setCursor(1, 0);
      lcd.print(F("Press >B2"));
      delay(500);
      GatoCachorro();

      if (bcachorro == 1 || bgato == 1) break;
    }
  }

  if (digitalRead(BOTAO_4) == HIGH){
    bcachorro = bgato = bfilhote = badulto = qac = qag = qfc = qfg = 0;
    while (1){
      lcd.setCursor(1, 0);
      lcd.print(F("Press >B2"));
      delay(500);
      GatoCachorro();

      if (bcachorro == 1 || bgato == 1) break;
    }
  }

  if (h == hora && m == minut && ligaMotor != 1){
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print(F("ENCHENDO..."));
    delay(500);
    if(tempMotor > 4){
      digitalWrite(MOTOR, HIGH);
      delay(tempMotor * 1000);
      digitalWrite(MOTOR, LOW);
    } 
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print(F("<<TERMINADO>>"));
    delay(1000);
    ligaMotor = 1;
  }

  if (h > hora) ligaMotor = 0;

  lcd.clear();
  ConfiguraHora();

  
}


/*
 * A função a seguir é responsável pela estruturação da tela 1,
 * que nada mais é que a tela que pergunta ao usuário se ele deseja
 * escolher o animal, gato ou cachorro.
*/


void GatoCachorro(){

  //As linhas a seguir só são responsáveis pela organização dos elementos na tela
  if (digitalRead(BOTAO_2) == HIGH){
    lcd.clear();

    lcd.setCursor(2, 0);
    lcd.print(F("Seu Pet eh? ")); //Escolher nome depois //
    delay(2000);

    lcd.clear();

    lcd.setCursor(1, 0);
    lcd.print(F("Cachorro")); //Pode ser outro nome

    lcd.setCursor(11, 0);
    lcd.print(F("Gato"));

    lcd.setCursor(1, 1);
    lcd.print(F(">B1"));
    delay(1000);

    lcd.clear();

    lcd.setCursor(1, 0);
    lcd.print(F("Cachorro")); //Pode ser outro nome

    lcd.setCursor(11, 0);
    lcd.print(F("Gato"));

    lcd.setCursor(12, 1);
    lcd.print(F(">B3"));
    delay(1000);

    lcd.clear();

    lcd.setCursor(1, 0);
    lcd.print(F("Cachorro")); //Pode ser outro nome

    lcd.setCursor(11, 0);
    lcd.print(F("Gato"));

    lcd.setCursor(1, 1);
    lcd.print(F(">B1"));

    lcd.setCursor(12, 1);
    lcd.print(F(">B3"));

    //Aqui está a lógica dos botões, que a partir daqui vai p/ outras telas. 
    while (1){
      if (digitalRead(BOTAO_1) == HIGH){
        AdultoFilhoteCachorro();
        bcachorro = 1;
      }else if (digitalRead(BOTAO_3) == HIGH){
        AdultoFilhoteGato();
        bgato = 1;
      }
          
      if (bcachorro == 1){
        break;
      }else if (bgato == 1){
        break;
      }  
    }
        
  }
}

//--------------------Fim da função GatoCachorro-----------------------


//-----------------------Inicio AdultoFilhoteCachorro------------------------

/*
 * A função em questão não tem retorno e novamente, o seu tamanho
 * se dar por conta da utilazação do lcd.Ela é responsável pela tela 
 * de escolha p/ ver se o animal escolhido é adulto,neste caso o do cachorro.
*/

void AdultoFilhoteCachorro(){
  lcd.clear();

  lcd.setCursor(5, 0);
  lcd.print(F("Voltar")); //Pode ser outro nome

  lcd.setCursor(2, 1);
  lcd.print(F("Press"));

  lcd.setCursor(10, 1);
  lcd.print(F(">B2"));
  delay(2000);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(F("Tamanho: ")); //Escolher nome depois //
  delay(2000);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(F("Pequena")); //Pode ser outro nome

  lcd.setCursor(10, 0);
  lcd.print(F("Grande"));

  lcd.setCursor(1, 1);
  lcd.print(F(">B1"));
  delay(1000);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(F("Pequena")); //Pode ser outro nome

  lcd.setCursor(10, 0);
  lcd.print(F("Grande"));

  lcd.setCursor(12, 1);
  lcd.print(F(">B3"));
  delay(1000);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(F("Pequena")); //Pode ser outro nome

  lcd.setCursor(10, 0);
  lcd.print(F("Grande"));

  lcd.setCursor(1, 1);
  lcd.print(F(">B1"));

  lcd.setCursor(12, 1);
  lcd.print(F(">B3"));

  lcd.setCursor(7, 1);
  lcd.print(F(">B2"));

  while (1){
    if (digitalRead(BOTAO_1) == HIGH){
      FilhoteQuantCachorro();
      bfilhote = 1;
    }else if (digitalRead(BOTAO_3) == HIGH){
      AdultoQuantCachorro();
      badulto = 1;
    }else if (digitalRead(BOTAO_2) == HIGH){
      bcachorro = 0;
      GatoCachorro();
    }
          
    if (bfilhote == 1){
       break;
    }else if (badulto == 1){
       break;
    }  
 }
 
//-----------------------Fim AdultoFilhoteCachorro------------------------

}

//-----------------------Inicio AdultoFilhoteGato------------------------
void AdultoFilhoteGato(){
  lcd.clear();

  lcd.setCursor(5, 0);
  lcd.print(F("Voltar")); //Pode ser outro nome

  lcd.setCursor(2, 1);
  lcd.print(F("Press"));

  lcd.setCursor(10, 1);
  lcd.print(F(">B2"));
  delay(2000);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(F("Escolha: ")); //Escolher nome depois //
  delay(2000);

  lcd.clear();

  lcd.setCursor(1, 0);
  lcd.print(F("Pequeno")); //Pode ser outro nome

  lcd.setCursor(10, 0);
  lcd.print(F("Grande"));

  lcd.setCursor(1, 1);
  lcd.print(F(">B1"));
  delay(1000);

  lcd.clear();

  lcd.setCursor(1, 0);
  lcd.print(F("Pequeno")); //Pode ser outro nome

  lcd.setCursor(10, 0);
  lcd.print(F("Grande"));

  lcd.setCursor(12, 1);
  lcd.print(F(">B3"));
  delay(1000);

  lcd.clear();

  lcd.setCursor(1, 0);
  lcd.print(F("Pequena")); //Pode ser outro nome

  lcd.setCursor(10, 0);
  lcd.print(F("Grande"));

  lcd.setCursor(1, 1);
  lcd.print(F(">B1"));

  lcd.setCursor(12, 1);
  lcd.print(F(">B3"));

  lcd.setCursor(7, 1);
  lcd.print(F(">B2"));

  while (1){
    if (digitalRead(BOTAO_1) == HIGH){
      FilhoteQuantGato();
      bfilhote = 1;
    }else if (digitalRead(BOTAO_3) == HIGH){
      AdultoQuantGato();
      badulto = 1;
    }else if (digitalRead(BOTAO_2) == HIGH){
      bgato = 0;
      GatoCachorro();
    }
          
      if (bfilhote == 1){
         break;
      }else if (badulto == 1){
         break;
      }  
   }
 

}
//-----------------------Fim AdultoFilhoteGato------------------------

//-----------------------Inicio FilhoteQuantCachorro------------------------
void FilhoteQuantCachorro(){
  lcd.clear();

  lcd.setCursor(5, 0);
  lcd.print(F("Voltar")); //Pode ser outro nome

  lcd.setCursor(2, 1);
  lcd.print(F("Press"));

  lcd.setCursor(10, 1);
  lcd.print(F(">B2"));
  delay(2000);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(F("Escolha a quant: ")); //Escolher nome depois //
  delay(2000);

  tempMotor = 4;
  for (short int i = 1; i < 10; i++){
    lcd.clear();

    lcd.setCursor(5, 0);
    lcd.print(i); //Pode ser outro nome
    lcd.setCursor(6, 0);
    lcd.print(F("00 G")); //Pode ser outro nome
    lcd.setCursor(0, 1);
    lcd.print(F("Confirma"));
    delay(1000);

    lcd.clear();

    lcd.setCursor(5, 0);
    lcd.print(i); //Pode ser outro nome
    lcd.setCursor(6, 0);
    lcd.print(F("00 G")); //Pode ser outro nome
    lcd.setCursor(12, 1);
    lcd.print(F(">>+"));
    delay(1000);

    lcd.clear();

    lcd.setCursor(5, 0);
    lcd.print(i); //Pode ser outro nome
    lcd.setCursor(6, 0);
    lcd.print(F("00 G")); //Pode ser outro nome
    lcd.setCursor(0, 1);
    lcd.print(F("Confirma"));
    lcd.setCursor(13, 1);
    lcd.print(F(">>+"));

    while (1){
      if (digitalRead(BOTAO_1) == HIGH){
        tempMotor += i;
        qfc = 1;
        HorarioFuciona();
        lcd.clear();
        return;
      }else if (digitalRead(BOTAO_3) == HIGH){
        if (i == 9){
          FilhoteQuantCachorro();
        }
        break;
      }else if (digitalRead(BOTAO_2) == HIGH){
        bfilhote = 0;
        AdultoFilhoteCachorro();
        return;
      }
    }

  }
    
}
//-----------------------FIM FilhoteQuantCachorro------------------------

void AdultoQuantCachorro(){
  lcd.clear();

  lcd.setCursor(5, 0);
  lcd.print(F("Voltar")); //Pode ser outro nome

  lcd.setCursor(2, 1);
  lcd.print(F("Press"));

  lcd.setCursor(10, 1);
  lcd.print(F(">B2"));
  delay(2000);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(F("Escolha a quant: ")); //Escolher nome depois //
  delay(2000);

  tempMotor = 2;
  for (int i = 1; i < 10; i++){
    lcd.clear();

    lcd.setCursor(5, 0);
    lcd.print(i); //Pode ser outro nome
    lcd.setCursor(6, 0);
    lcd.print(F("00 G")); //Pode ser outro nome
    lcd.setCursor(0, 1);
    lcd.print(F("Confirma"));
    delay(1000);

    lcd.clear();

    lcd.setCursor(5, 0);
    lcd.print(i); //Pode ser outro nome
    lcd.setCursor(6, 0);
    lcd.print(F("00 G")); //Pode ser outro nome
    lcd.setCursor(12, 1);
    lcd.print(F(">>+"));
    delay(1000);

    lcd.clear();

    lcd.setCursor(5, 0);
    lcd.print(i); //Pode ser outro nome
    lcd.setCursor(6, 0);
    lcd.print(F("00 G")); //Pode ser outro nome
    lcd.setCursor(0, 1);
    lcd.print(F("Confirma"));
    lcd.setCursor(12, 1);
    lcd.print(F(">>+"));

    while (1){
      if (digitalRead(BOTAO_1) == HIGH){
        tempMotor += i;
        qac = 1;
        HorarioFuciona();
        lcd.clear();
        return;
      }else if (digitalRead(BOTAO_3) == HIGH){
        if (i == 9){
          AdultoQuantCachorro();
        }  
        break;
      }else if (digitalRead(BOTAO_2) == HIGH){
        badulto = 0;
        AdultoFilhoteCachorro();
        return;
      }
    }

  }
}
void AdultoQuantGato(){
  lcd.clear();

  lcd.setCursor(5, 0);
  lcd.print(F("Voltar")); //Pode ser outro nome

  lcd.setCursor(2, 1);
  lcd.print(F("Press"));

  lcd.setCursor(10, 1);
  lcd.print(F(">B2"));
  delay(2000);

  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print(F("Escolha a quant: ")); //Escolher nome depois //
  delay(2000);

  tempMotor = 4;
  for (int i = 1; i < 10; i++){
    lcd.clear();

    lcd.setCursor(5, 0);
    lcd.print(i); //Pode ser outro nome
    lcd.setCursor(6, 0);
    lcd.print(F("00 G")); //Pode ser outro nome
    lcd.setCursor(0, 1);
    lcd.print(F("Confirma"));
    delay(1000);

    lcd.clear();

    lcd.setCursor(5, 0);
    lcd.print(i); //Pode ser outro nome
    lcd.setCursor(6, 0);
    lcd.print(F("00 G")); //Pode ser outro nome
    lcd.setCursor(12, 1);
    lcd.print(F(">>+"));
    delay(1000);

    lcd.clear();

    lcd.setCursor(5, 0);
    lcd.print(i); //Pode ser outro nome
    lcd.setCursor(6, 0);
    lcd.print(F("00 G")); //Pode ser outro nome
    lcd.setCursor(0, 1);
    lcd.print(F("Confirma"));
    lcd.setCursor(12, 1);
    lcd.print(F(">>+"));

    while (1){
      if (digitalRead(BOTAO_1) == HIGH){
        tempMotor += i;
        qag = 1;
        HorarioFuciona();
        lcd.clear();
        return;
      }else if (digitalRead(BOTAO_3) == HIGH){
        if (i == 9){
          AdultoQuantGato();
        } 
        break;
      }else if (digitalRead(BOTAO_2) == HIGH){
        badulto = 0;
        AdultoFilhoteGato();
        return;
      }
    }

  }
}

void FilhoteQuantGato(){
  lcd.clear();

  lcd.setCursor(5, 0);
  lcd.print(F("Voltar")); //Pode ser outro nome

  lcd.setCursor(2, 1);
  lcd.print(F("Press"));

  lcd.setCursor(10, 1);
  lcd.print(F(">B2"));
  delay(2000);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(F("Escolha a quant: ")); //Escolher nome depois //
  delay(2000);

  tempMotor = 6;
  for (int i = 1; i < 10; i++){
    lcd.clear();

    lcd.setCursor(5, 0);
    lcd.print(i); //Pode ser outro nome
    lcd.setCursor(6, 0);
    lcd.print(F("00 G")); //Pode ser outro nome
    lcd.setCursor(0, 1);
    lcd.print(F("Confirma"));
    delay(1000);

    lcd.clear();

    lcd.setCursor(5, 0);
    lcd.print(i); //Pode ser outro nome
    lcd.setCursor(6, 0);
    lcd.print(F("00 G")); //Pode ser outro nome
    lcd.setCursor(12, 1);
    lcd.print(F(">>+"));
    delay(1000);

    lcd.clear();

    lcd.setCursor(5, 0);
    lcd.print(i); //Pode ser outro nome
    lcd.setCursor(6, 0);
    lcd.print(F("00 G")); //Pode ser outro nome
    lcd.setCursor(0, 1);
    lcd.print(F("Confirma"));
    lcd.setCursor(12, 1);
    lcd.print(F(">>+"));

    while (1){
      if (digitalRead(BOTAO_1) == HIGH){
        tempMotor += i;
        qfg = 1;
        HorarioFuciona();
        lcd.clear();
        return;
      }else if (digitalRead(BOTAO_3) == HIGH){
        if (i == 9){
          FilhoteQuantGato();
        } 
        break;
      }else if (digitalRead(BOTAO_2) == HIGH){
        bfilhote = 0;
        AdultoFilhoteGato();
        return;
      }
    }

  }
}

//Essa daqui não precisaria fazer uma função geral
void HorarioFuciona(){
  lcd.clear();

  lcd.setCursor(5, 0);
  lcd.print(F("Voltar")); //Pode ser outro nome

  lcd.setCursor(2, 1);
  lcd.print(F("Press"));

  lcd.setCursor(10, 1);
  lcd.print(F(">B2"));
  delay(2000);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(F("Escolha a hora: ")); //Escolher nome depois //
  delay(2000);

  lcd.clear();

  lcd.setCursor(5, 0);
  lcd.print(F("08:00H")); //Pode ser outro nome

  lcd.setCursor(0, 1);
  lcd.print(F("Confirma"));
  delay(1000);

  lcd.clear();

  lcd.setCursor(5, 0);
  lcd.print(F("08:00H")); //Pode ser outro nome

  lcd.setCursor(12, 1);
  lcd.print(F(">>+"));
  delay(1000);

  lcd.clear();

  lcd.setCursor(5, 0);
  lcd.print(F("08:00H")); //Pode ser outro nome

  lcd.setCursor(0, 1);
  lcd.print(F("Confirma"));

  lcd.setCursor(12, 1);
  lcd.print(F(">>+"));

  while (1){
    if (digitalRead(BOTAO_1) == HIGH){
      hora = 8;
      minut = 0;
      sec = 0;
      return;
    }else if (digitalRead(BOTAO_3) == HIGH){
      break;
    }else if (digitalRead(BOTAO_2) == HIGH){
      if (qac == 1){
        qac = 0;
        AdultoQuantCachorro();
        return;
      }else if (qfc == 1){
        qfc = 0;
        FilhoteQuantCachorro();
        return;
      }else if (qag == 1){
        qag = 0;
        AdultoQuantGato();
        return;
      }else if (qfg == 1){
        qfg = 0;
        FilhoteQuantGato();
        return;
      }
    }
  }

  lcd.clear();

  lcd.setCursor(5, 0);
  lcd.print(F("15:00H")); //Pode ser outro nome

  lcd.setCursor(0, 1);
  lcd.print(F("Confirma"));
  delay(1000);

  lcd.clear();

  lcd.setCursor(5, 0);
  lcd.print(F("15:00H")); //Pode ser outro nome

  lcd.setCursor(12, 1);
  lcd.print(F(">>+"));
  delay(1000);

  lcd.clear();

  lcd.setCursor(5, 0);
  lcd.print(F("15:00H")); //Pode ser outro nome

  lcd.setCursor(0, 1);
  lcd.print(F("Confirma"));

  lcd.setCursor(12, 1);
  lcd.print(F(">>+"));

  while (1){
    if (digitalRead(BOTAO_1) == HIGH){
      hora = 15;
      minut = 0;
      sec = 0;
      return;
    }else if (digitalRead(BOTAO_3) == HIGH){
      break;
    }else if (digitalRead(BOTAO_2) == HIGH){
      if (qac == 1){
        qac = 0;
        AdultoQuantCachorro();
        return;
      }else if (qfc == 1){
        qfc = 0;
        FilhoteQuantCachorro();
        return;
      }else if (qag == 1){
        qag = 0;
        AdultoQuantGato();
        return;
      }else if (qfg == 1){
        qfg = 0;
        FilhoteQuantGato();
        return;
      }
    }
  }

  lcd.clear();

  lcd.setCursor(5, 0);
  lcd.print(F("20:00H")); //Pode ser outro nome

  lcd.setCursor(0, 1);
  lcd.print(F("Confirma"));
  delay(1000);

  lcd.clear();

  lcd.setCursor(5, 0);
  lcd.print(F("20:00H")); //Pode ser outro nome

  lcd.setCursor(12, 1);
  lcd.print(F(">>+"));
  delay(1000);

  lcd.clear();

  lcd.setCursor(5, 0);
  lcd.print(F("20:00H")); //Pode ser outro nome

  lcd.setCursor(0, 1);
  lcd.print(F("Confirma"));

  lcd.setCursor(12, 1);
  lcd.print(F(">>+"));

  while (1){
    if (digitalRead(BOTAO_1) == HIGH){
      hora = 20;
      minut = 0;
      sec = 0;
      return;
    }else if (digitalRead(BOTAO_3) == HIGH){
      HorarioFuciona();
      return;
    }else if (digitalRead(BOTAO_2) == HIGH){
      if (qac == 1){
        qac = 0;
        AdultoQuantCachorro();
        return;
      }else if (qfc == 1){
        qfc = 0;
        FilhoteQuantCachorro();
        return;
      }else if (qag == 1){
        qag = 0;
        AdultoQuantGato();
        return;
      }else if (qfg == 1){
        qfg = 0;
        FilhoteQuantGato();
        return;
      }
    }
  }
  
}

void InstrucaoHora(){

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print(F("Vamos Come"));
    lcd.setCursor(10, 0);
    lcd.write(1);
    lcd.setCursor(11, 0);
    lcd.print(F("ar!!!"));
    delay(45000);

    lcd.clear();

    lcd.setCursor(1, 0);
    lcd.print(F("Configura Hora"));
    
    lcd.setCursor(2, 1);
    lcd.print(F("Como usar? ):"));
    
    delay(45000);

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print(F("B1:hora"));
    
    lcd.setCursor(9, 0);
    lcd.print(F("B3:min"));
    
    lcd.setCursor(2, 3);
    lcd.print(F("B2:Confirma"));

    delay(45000);

    lcd.setCursor(0, 0);   //Corrigir bug desconhecido :(
    lcd.print(F("B1:hora"));
    delay(3500);
  
}

void ConfiguraHora(){
    lcd.setCursor(1, 0);
    lcd.print(F("Seja Bem Vindo"));
    
    lcd.setCursor(0, 4);
    
    lcd.setCursor(6, 1);
    s = s + 1;
    if (h <= 9){
      lcd.print(F("0"));
    }
    lcd.print(h);
    lcd.print(F(":"));
    if(m <= 9){
      lcd.print(F("0"));
    }
    lcd.print(m);
    
    delay(1000);
    lcd.clear();
    if (s == 60){
        s = 0;
        m = m + 1;
    }
    if (m == 60){
        m = 0;
        h = h + 1;
    }
    if (h == 13){
        h = 13;
    }
    lcd.setCursor(0, 1);
    
    state1 = digitalRead(BOTAO_1);
    if (state1 == 1){
        h = h + 1;
        if (h == 13) h = 13;
        if (h == 24) h = 0;
    }
    state2 = digitalRead(BOTAO_3);
    if (!state2 == 0){
        s = 0;
        m = m + 1;
    }

    if (digitalRead(BOTAO_2) == HIGH){
      entraNaFuncao = 1;
    }
    
}
