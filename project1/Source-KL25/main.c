/* ###################################################################
**     Filename    : main.c
**	   Author	   : Patrick Penacho Carvalho
**     Project     : roteiro1-ppc3
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2021-01-20, 20:05, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
 ** @file main.c
 ** @version 01.01
 ** @brief
 ** Main module.
 ** This module contains user's application code.
 */
/*!
 ** @addtogroup main_module main module documentation
 ** @{
 */
/* MODULE main */
/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "User.h"
#include "ASerialLdd1.h"
#include "Mobile.h"
#include "ASerialLdd2.h"
#include "MCUC1.h"
#include "WAIT.h"
#include "LEDR.h"
#include "BitIoLdd1.h"
#include "LEDG.h"
#include "BitIoLdd2.h"
#include "LEDB.h"
#include "BitIoLdd3.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "string.h"

// Specify the network and broker parameters:
#define W_SSID	 	"wifi_ssid"
#define W_PASSWORD 	"wifi_password"
#define MQTT_IP		"123.456.7.890"
#define MQTT_PORT	"1883"

volatile uint8_t mobile_rx;
volatile uint8_t user_rx;
volatile uint8_t user_freeTx;
volatile char msgbuf[128];
volatile int pos;

void send_pc(char *s){
	int k = 0;		
	while(User_SendBlock(s, strlen(s), &k));
	while(User_SendChar(0x0D));
	while(User_SendChar(0x0A));
}

void send_esp(char *s){
	int k;
	while(Mobile_SendBlock(s, strlen(s), &k));
}

int esp_receive(char *s){
	int i = 0;
	char ch;
	while(1){
		while(Mobile_RecvChar(&ch));
		if(ch == '\n'){
			s[i] = ch;
			i++;
			s[i] = '\0';
			mobile_rx = 0;
			return i;
		}
		s[i] = ch;
		i++;
	}
}

int pool_for_messages(){
	char c;
	while(!mobile_rx);

	do {
		while(Mobile_RecvChar(&c));
		msgbuf[pos] = c;
		pos++;
	} while (c != '\n');

	pos = 0;
	mobile_rx = 0;
	return 1;
}

void handleMqttMessage(char* topic, char* msg) {
	// LEDR
	if (!strcmp(topic, "[EA076/185388/LEDR]")) {
		if (!strcmp(msg, "[ON]")) {
			LEDR_PutVal(0);
			send_esp("PUBLISH \"EA076/185388/reply\",\"LEDR ON\"\r\n");
			pool_for_messages();
		} 
		else if (!strcmp(msg, "[OFF]")) {
			LEDR_PutVal(1);
			send_esp("PUBLISH \"EA076/185388/reply\",\"LEDR OFF\"\r\n");
			pool_for_messages();
		} 
	}
	// LEDG
	if (!strcmp(topic, "[EA076/185388/LEDG]")) {
		if (!strcmp(msg, "[ON]")) {
			LEDG_PutVal(0);
			send_esp("PUBLISH \"EA076/185388/reply\",\"LEDG ON\"\r\n");
			pool_for_messages();
		} 
		else if (!strcmp(msg, "[OFF]")) {
			LEDG_PutVal(1);
			send_esp("PUBLISH \"EA076/185388/reply\",\"LEDG OFF\"\r\n");
			pool_for_messages();
		} 
	}
	// LEDB
	if (!strcmp(topic, "[EA076/185388/LEDB]")) {
		if (!strcmp(msg, "[ON]")) {
			LEDB_PutVal(0);
			send_esp("PUBLISH \"EA076/185388/reply\",\"LEDB ON\"\r\n");
			pool_for_messages();
		} 
		else if (!strcmp(msg, "[OFF]")) {
			LEDB_PutVal(1);
			send_esp("PUBLISH \"EA076/185388/reply\",\"LEDB OFF\"\r\n");
			pool_for_messages();
		} 
	}
	
}

/*lint -save -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization. ***/
	char cmd[128];
	char answer[128];
	char mac[20];
	char topic[100];
	char msg[100];
	int i = 0;
	int idx = 0;
	int isReady = 0; // indica que está pronto para próxima fase durante configuração
	word len;
	send_esp("\r\n");
	send_pc("Conectado ao PC\n");
	esp_receive(mac);
	send_esp("GETMAC\r\n");
	len = esp_receive(mac);
	mac[len-2] = '\0';
	send_pc(mac);

	// Etapa de configuraçao Wifi/MQTT
	send_pc("Tentando conectar.");
	while(!isReady){
		cmd = "";
		strcpy(cmd, "CONNWIFI \"");
		strcpy(cmd, W_SSID);
		strcpy(cmd, "\",\"");
		strcpy(cmd, W_PASSWORD);
		strcpy(cmd, "\"\r\n");
		
		len = esp_receive(answer);
		//send_pc(answer);
		answer[len-2] = '\0';
		if(!strcmp(answer, "CONNECT WIFI")){
			send_pc("Conexão bem sucedida!");
			isReady = 1; 
			WAIT_Waitms(10);
			send_esp("GETIP\r\n");
			WAIT_Waitms(10);
			len = esp_receive(answer);
			answer[len-2] = '\0';
			send_pc(answer);
		}
		if(!strcmp(answer, "ERROR WIFI")){
			send_pc("Conexão mal sucedida!");
		}
		if(!strcmp(answer, "INVALID CMD")){
			send_pc("Comando Inválido!");
		}
	}
	isReady = 0;
	send_pc("Conectando ao Broker.");
	cmd = "";
	strcpy(cmd, "CONNMQTT \"");
	strcpy(cmd, MQTT_IP);
	strcpy(cmd, "\",");
	strcpy(cmd, MQTT_PORT);
	strcpy(cmd, ",\"");
	strcat(cmd, mac);
	strcat(cmd, "\"\r\n");
	//send_pc(comando);
	while(!isReady){
		send_esp(cmd);
		len = esp_receive(answer);
		//send_pc(answer);
		answer[len-2] = '\0';
		if(!strcmp(answer, "CONNECT MQTT")){
			send_pc("Conexão ao BROKER bem sucedida!");
			isReady = 1; 
		}
		if(!strcmp(answer, "NOWIFI")){
			send_pc("Não há conexão WIFI");
		}
		if(!strcmp(answer, "INVALID CMD")){
			send_pc("Comando Inválido!");
		}
	}
	isReady = 0;
	send_pc("Tentando se inscrever nos tópicos.");
	while(!isReady){
		send_esp("SUBSCRIBE \"EA076/185388/LEDR\"\r\n");
		len = esp_receive(answer);
		answer[len-2] = '\0';
		if(!strcmp(answer, "OK SUBSCRIBE")){
			send_pc("Conectado a LEDR!");
			isReady = 1; 
		}
		if(!strcmp(answer, "NOT CONNECTED")){
			send_pc("Falha ao conectar a LEDR");
		}
		if(!strcmp(answer, "ERROR SUBSCRIBE")){
			send_pc("Erro ao tentar se inscrever. LEDR");
		}
	}
	isReady = 0;
	while(!isReady){
		send_esp("SUBSCRIBE \"EA076/185388/LEDG\"\r\n");
		len = esp_receive(answer);
		answer[len-2] = '\0';
		if(!strcmp(answer, "OK SUBSCRIBE")){
			send_pc("Conectado a LEDG!");
			isReady = 1; 
		}
		if(!strcmp(answer, "NOT CONNECTED")){
			send_pc("Falha ao conectar a LEDG");
		}
		if(!strcmp(answer, "ERROR SUBSCRIBE")){
			send_pc("Erro ao tentar se inscrever. LEDG");
		}
	}
	isReady = 0;
	while(!isReady){
		send_esp("SUBSCRIBE \"EA076/185388/LEDB\"\r\n");
		len = esp_receive(answer);
		answer[len-2] = '\0';
		if(!strcmp(answer, "OK SUBSCRIBE")){
			send_pc("Conectado a LEDB!");
			isReady = 1; 
		}
		if(!strcmp(answer, "NOT CONNECTED")){
			send_pc("Falha ao conectar a LEDB");
		}
		if(!strcmp(answer, "ERROR SUBSCRIBE")){
			send_pc("Erro ao tentar se inscrever. LEDB");
		}
	}
	send_pc("Configuracao completa.");
	// configuração completa.

	// loop principal - espera por mensagens recebidas do ESP e as trata
	char auxstr[128];
	while(1) {
		pool_for_messages();
		send_pc("MSG RECEBIDA!");

		// Verifica se a mensagem é de MQTT
		strcpy(auxstr, msgbuf);
		auxstr[7] = '\0';
		if(!strcmp(auxstr, "MESSAGE")) {
			// mensagem recebida é MQTT
			// separa tópico e mensagem
			i = 0;
			do {
				i++;
			} while (msgbuf[i] != ',' && i<128);
			msgbuf[i] = '\0'; // substitui ',' por terminação de string
			strcpy(topic, &msgbuf[8]); // tópico começa no oitavo char
			
			idx = i;
			do {
				idx++;
			} while (msgbuf[idx] != '\r' && idx<128);
			msgbuf[idx] = '\0'; // substitui '\r' por terminação de string
			strcpy(msg, &msgbuf[i+1]);
			send_pc(topic);
			send_pc(msg);

			// rotina de tratamento das mensagens recebidas
			handleMqttMessage(topic, msg);
		}
		else {
			// Mensagem não é de MQTT - envia à UART do PC
			send_pc("Erro!");
			len = 0;
			do {
				len++;
			} while (msgbuf[len] != '\n' && len<128);
			msgbuf[len-1] = '\0';
			send_pc(msgbuf);
		}
	}
	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/
/* END main */
/*!
 ** @}
 */
