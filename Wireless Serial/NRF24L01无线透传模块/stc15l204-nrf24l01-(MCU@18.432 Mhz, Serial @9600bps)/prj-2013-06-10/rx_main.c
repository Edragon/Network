/*
* ----------------------------------------------------------------------------
* “THE COFFEEWARE LICENSE” (Revision 1):
* <ihsan@kehribar.me> wrote this file. As long as you retain this notice you
* can do whatever you want with this stuff. If we meet some day, and you think
* this stuff is worth it, you can buy me a coffee in return.
* -----------------------------------------------------------------------------
*/

#include <stc12.h>
#include "./nrf24.h"

/* ------------------------------------------------------------------------- */
/* Printing functions */
/* ------------------------------------------------------------------------- */
#include "./util/sprintf.h"
#include "proto.h"
#include "radioPinFunctions.c"
/* ------------------------------------------------------------------------- */

uint8_t temp;
uint8_t q = 0;
uint8_t data_array[4];
uint8_t tx_address[5] = {0xD7,0xD7,0xD7,0xD7,0xD7};
uint8_t rx_address[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};
/* ------------------------------------------------------------------------- */
int main()
{
    /* init the software uart */
    UART_INIT();

    /* init the xprintf library */
    //xdev_out(uart_put_char);

    /* simple greeting message */
    sprintf("\r\n> RX device ready\r\n");

    /* init hardware pins */
    nrf24_init();
    
    /* Channel #2 , payload length: 4 */
    nrf24_config(2,4);
 
    /* Set the device addresses */
    nrf24_tx_address(tx_address);
    nrf24_rx_address(rx_address);

    while(1)
    {    
        if(nrf24_dataReady())
        {
            nrf24_getData(data_array);        
            sprintf("> ");
            hprintf(data_array[0]);sprintf(" ");
            hprintf(data_array[1]);sprintf(" ");
            hprintf(data_array[2]);sprintf(" ");
            hprintf(data_array[3]);sprintf("\r\n");
        }
    }
}
/* ------------------------------------------------------------------------- */
