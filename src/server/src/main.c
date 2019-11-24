#include "comunication.h"
#include "conection.h"
#include "functions.h"
#include "globals.h"
#include "logs.h"
#include "response.h"
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *revert(char *message)
{
  int len = strlen(message) + 1;
  char *response = malloc(len);

  for (int i = 0; i < len - 1; i++)
  {
    response[i] = message[len - 2 - i];
  }
  response[len - 1] = '\0';
  return response;
}

int load_input(uint8_t *log, int *port, char **ip, int argc, char *argv[])
{
  char *help_mg = " ./server -i <ip_address> -p <tcp-port> [-l]"; // Correct Usage String
  char *ip_flag = "-i";                                           // Flag for ip address
  char *pt_flag = "-p";                                           // flag for port
  char *lg_flag = "-l";                                           // flag for log
  int ip_founded = 0;                                             // to check if ip is founded
  int pt_founded = 0;                                             // to check if port is founded
  int lg_founded = 0;                                             // to check if log is founded

  if (argc == 6 || argc == 5)
  {
    for (int x = 0; x < argc; x++)
    {
      if (!strcmp(lg_flag, argv[x]) && !lg_founded)
      {
        lg_founded = 1;
        *log = 1;
      }

      if (!strcmp(ip_flag, argv[x]) && !ip_founded)
      {
        ip_founded = 1;
        x++;
        int addr_len = strlen(argv[x]);
        if (addr_len < 7 || 15 < addr_len)
        {
          printf("\nERROR [%s]: Worng ip adress<%s>\n", __func__, argv[x]);
          return -1;
        }
        *ip = argv[x];
      }

      if (!strcmp(pt_flag, argv[x]) && !pt_founded)
      {
        pt_founded = 1;
        x++;
        int port_entered = atoi(argv[x]);
        if (port_entered < 0 || 65536 < port_entered)
        {
          printf("\nERROR [%s]: Worng port number<%s>\n", __func__, argv[x]);
          return -2;
        }
        *port = port_entered;
      }
    }

    if (!pt_founded || !ip_founded)
    {
      printf("\nERROR [%s]: Missing important parameters(IP adresss and/or PORT)\n Correct usage: $%s\n", __func__, help_mg);
      return -3;
    }

    if (!lg_founded && argc == 6)
    {
      printf("\nERROR [%s]: Missing -l flag\n Correct usage: $%s\n", __func__, help_mg);
      return -4;
    }
    return 0;
  }

  printf("\nERROR [%s]: Wrong number of arguments <%d>\n Correct usage: $%s\n", __func__, argc, help_mg);
  return -5;
}

int main(int argc, char *argv[])
{
  DEBUGGER = 1;
  char *IP;
  int PORT;
  rounds = 0;
  uint8_t LOGG = 0; // Si es 0, entonces no se hace logging, en otro caso si
  // Se define una IP y un puerto
  if (DEBUGGER)
  {
    IP = "127.0.0.1";
    PORT = 3000;
  }
  else
  {
    if (load_input(&LOGG, &PORT, &IP, argc, argv))
    {
      return -1;
    }
  }
  setup_logger("log.txt", LOGG);
  debuger("Iniciando Servidor, llamando funcion: {set_words()}");
  set_words();

  // Se crea el servidor y se obtienen los sockets de ambos clientes.
  char msg[255];
  // sprintf(msg, "Llamando a funcion {prepare_sockets_and_get_clients(%s, %d)}", IP, PORT);
  // debuger(msg);
  PlayersInfo *players_info = prepare_sockets_and_get_clients(IP, PORT);

  // Le enviamos al primer cliente un mensaje de bienvenida

  // Guardaremos los sockets en un arreglo e iremos alternando a quién escuchar.

  int my_attention = 0;
  while (1)
  {
    int msg_code = server_receive_id(players_info->players[my_attention]->socket);
    if (msg_code)
    {
      sprintf(msg, "%s::Received message ID=%d", __func__, msg_code);
      infolog(msg);
      handle_message(players_info, my_attention, msg_code);
    }
    if (my_attention + 1 < players_info->connected)
      my_attention++;
    else
      my_attention = 0;

    if (end_games)
      break;
  }
  sprintf(msg, "Destroying Players:\n%s\n%s\n", players_info->players[0]->nickname, players_info->players[1]->nickname);
  debuger(msg);
  destroy_players_info(players_info);
  debuger("Liberando Cards");
  free(cards);
  debuger("Liberando Palabras");
  for (int i = 0; i < 1001; i++)
  {
    free(words[i]);
  }
  free(words);
  free(size);
  free(obj_word);
  debuger("Cerrando Programa y Logs");
  close_logger();
  return 0;
}
