/**
 * @file main.c
 * @version 1.0
 * @brief Logovanje
 * @author
 * @date 15.5.2021.
 */

///biblioteka koja omogucava delay
#include <util/delay.h>

///biblioteka koja omogucava citanje integer tipova
#include <stdint.h>

///biblioteka sa funkcijama za koriscenje stringova
#include <stdlib.h>

///biblioteka za serijsku komunikaciju
#include "../usart/usart.h"


int8_t user[] = "test";
int8_t pass[] = "test1";

int main()
{

	int8_t usinput[64];
	int8_t pasinput[64];
	uint8_t duzime;
	uint8_t duzloz;
	int8_t indikator = 1;

	usartInit(9600);

	while(1)
	{
		indikator = 1;
		/**
		* usartPutString - funkcija koja na serijskom izlazu ispisuje string
		* @param - s - string koji unosimo
		* @return Nema povratnu vrednost
		*/
		usartPutString("Unesite korisnicko ime: ");
		while(!usartAvailable())
			;
		_delay_ms(100);

		duzime = usartGetString(usinput);
		usartPutString(usinput);
		usartPutString("\r\n");
		usinput[duzime] = '\0';

		usartPutString("Unesite lozinku: ");
		while(!usartAvailable())
			;
		_delay_ms(100);

		duzloz = usartGetString(pasinput);
		usartPutString(pasinput);
		usartPutString("\r\n");
		pasinput[duzloz] = '\0';

		if(duzime != strlen(user) || duzloz != strlen(pass))
		{
			indikator = 0;
		}
		else
		{
			for(int8_t i = 0; i < strlen(usinput); i++)
			{
				if(usinput[i] != user[i] || pasinput[i] != pass[i])
					indikator = 0;
			}
		}
		if(indikator == 0)
		{
			usartPutString("Logovanje neuspesno.");
			usartPutString("\r\n");
		}
		else
		{
			usartPutString("Dobrodosao/la, ");
			usartPutString(user);
			usartPutString("\r\n");
		}

	}
	return 0;
}
