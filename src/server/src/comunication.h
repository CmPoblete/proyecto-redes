#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <sys/socket.h>
#include "conection.h"
#pragma once

int server_receive_id(int client_socket);
char * server_receive_payload(int client_socket);
void server_send_message(int client_socket, int pkg_id, char * message);
unsigned char* send_words(char** words, int* size);
void server_connection_established(int client_socket);
void server_ask_nikname(Player* player);
void server_save_nickname(Player* player);
void server_oponent_found(PlayersInfo * players_info);
void server_start_game(PlayersInfo * players_info);
