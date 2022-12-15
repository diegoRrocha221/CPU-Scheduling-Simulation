#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <unistd.h>
#include <stdlib.h>
using namespace std;


struct Processo {
  int id;
  int ioRun; 
  int burst; 
};


Processo processos[10];

queue<Processo> fila;

void FCFS() {
  for (int i = 0; i < 10; i++) {
  	processos[i].id = i + 1; 
  	processos[i].ioRun = rand() % 10 + 1;
  	processos[i].burst = rand() % 10 + 1;
  }

  cout << "Executando FCFS..." << endl;

  for (int i = 0; i < 10; i++) {
    cout << "Executando processo " << processos[i].id << " com IO run " << processos[i].ioRun << " e burst " << processos[i].burst << endl;
    sleep(processos[i].ioRun + processos[i].burst);
  }
}

void SJF() {
  for (int i = 0; i < 10; i++) {
  	processos[i].id = i + 1; 
  	processos[i].ioRun = rand() % 10 + 1;
  	processos[i].burst = rand() % 10 + 1;
  }

  cout << "Executando SJF..." << endl;

  sort(processos, processos + 10, [](const Processo &a, const Processo &b) {
    return a.burst < b.burst;
  });


  for (int i = 0; i < 10; i++) {
    cout << "Executando processo " << processos[i].id << " com IO run " << processos[i].ioRun << " e burst " << processos[i].burst << endl;
    sleep(processos[i].ioRun + processos[i].burst);
  }
}

struct Fila {
  vector<Processo> processos;
  int nivelPrioridade;
  int quantum;
};

Fila filas[3];

for (int i = 0; i < 3; i++) {
  filas[i].nivelPrioridade = i + 1;
  filas[i].quantum = (i + 1) * 2;
}

void MLFQ() {
  for (int i = 0; i < 10; i++) {
  processos[i].id = i + 1;
  processos[i].ioRun = rand() % 10 + 1;
  processos[i].burst = rand() % 10 + 1;
  }
  int quantum = 2;
  cout << "Executando MLFQ..." << endl;
		

  for (int i = 0; i < 10; i++) {
    filas[0].processos.push_back(processos[i]);

    for (int j = 0; j < 3; j++) {
      if (filas[j].processos.empty()) continue;
      Processo processo = filas[j].processos.front();
      filas[j].processos.erase(filas[j].processos.begin());

      cout << "Executando processo " << processo.id << " com IO run " << processo.ioRun << " e burst " << processo.burst << " na fila de n�vel de prioridade " << filas[j].nivelPrioridade << endl;
      sleep(processo.ioRun + processo.burst);

      if (processo.burst > filas[j].quantum) {
        filas[j + 1].processos.push_back(processo);
      }
    }
  }
}
