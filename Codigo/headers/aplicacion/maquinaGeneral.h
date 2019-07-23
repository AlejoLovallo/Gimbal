/**
  \file maquinaGeneral.h
  \brief Contiene la definición de #defines y rutinas relacionadas con el funcionamiento de las máquinas de estados. En particular de la máquina maquinaGeneral().
  \author Grupo 8 - R2003
  \date 2019.07.23
  \version 1.2
*/

/*Standar Libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Bibliotecas propias*/
#include "headers/primitivas/bibliotecaInfoII.h"
#include "headers/aplicacion/timers.h"
#include "headers/aplicacion/maquinaControl.h"
#include "headers/aplicacion/maquinaEjecutando.h"


/*Maquina principal*/
#define E_CALIBRANDO 5
#define E_FUNCIONANDO 6

/*Maquina_Funcionando*/   //Esto no se esta usando!
#define E_CONTROLANDO 7
#define E_EJECUTANDO 8



/*Declaracion de rutinas*/
  /*funciones*/
  void Inicializar();
  bool Recalibrar_Confirm();
  void F_Funcionando();


  /*maquinas*/
  void Maquina_General();
  void Maquina_Control();
  void Maquina_Calibrando();
