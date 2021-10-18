/* ###################################################################
**     Filename    : Events.c
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
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
 ** ###################################################################*/
/*!
 ** @file Events.c
 ** @version 01.00
 ** @brief
 ** This is user's event module.
 ** Put your event handler code here.
 */
/*!
 ** @addtogroup Events_module Events module documentation
 ** @{
 */
/* MODULE Events */
#include "Cpu.h"
#include "Events.h"
#ifdef __cplusplus
extern "C" {
#endif
/* User includes (#include below this line is not maintained by Processor Expert) */
volatile uint8_t mobile_rx;
volatile uint8_t user_rx;
volatile uint8_t user_freeTx;
/*
 ** ===================================================================
 ** Event : Cpu_OnNMIINT (module Events)
 **
 ** Component : Cpu [MKL25Z128LK4]
 */
/*!
 ** @brief
 ** This event is called when the Non maskable interrupt had
 ** occurred. This event is automatically enabled when the [NMI
 ** interrupt] property is set to 'Enabled'.
 */
/* ===================================================================*/
void Cpu_OnNMIINT(void)
{
	/* Write your code here ... */
}
/*
 ** ===================================================================
 ** Event : Mobile_OnError (module Events)
 **
 ** Component : Mobile [AsynchroSerial]
 ** Description :
 ** This event is called when a channel error (not the error
 ** returned by a given method) occurs. The errors can be read
 ** using <GetError> method.
 ** The event is available only when the <Interrupt
 ** service/event> property is enabled.
 ** Parameters : None
 ** Returns : Nothing
 ** ===================================================================
 */
void Mobile_OnError(void)
{
	/* Write your code here ... */
}
/*
 ** ===================================================================
 ** Event : Mobile_OnRxChar (module Events)
 **
 ** Component : Mobile [AsynchroSerial]
 ** Description :
 ** This event is called after a correct character is received.
 ** The event is available only when the <Interrupt
 ** service/event> property is enabled and either the <Receiver>
 ** property is enabled or the <SCI output mode> property (if
 ** supported) is set to Single-wire mode.
 ** Parameters : None
 ** Returns : Nothing
 ** ===================================================================
 */
void Mobile_OnRxChar(void)
{
	mobile_rx = 1;
}
/*
 ** ===================================================================
 ** Event : Mobile_OnTxChar (module Events)
 **
 ** Component : Mobile [AsynchroSerial]
 ** Description :
 ** This event is called after a character is transmitted.
 ** Parameters : None
 ** Returns : Nothing
 ** ===================================================================
 */
void Mobile_OnTxChar(void)
{
	/* Write your code here ... */
}
/*
 ** ===================================================================
 ** Event : Mobile_OnFullRxBuf (module Events)
 **
 ** Component : Mobile [AsynchroSerial]
 ** Description :
 ** This event is called when the input buffer is full;
 ** i.e. after reception of the last character
 ** that was successfully placed into input buffer.
 ** Parameters : None
 ** Returns : Nothing
 ** ===================================================================
 */
void Mobile_OnFullRxBuf(void)
{
	/* Write your code here ... */
}
/*
 ** ===================================================================
 ** Event : Mobile_OnFreeTxBuf (module Events)
 **
 ** Component : Mobile [AsynchroSerial]
 ** Description :
 ** This event is called after the last character in output
 ** buffer is transmitted.
 ** Parameters : None
 ** Returns : Nothing
 ** ===================================================================
 */
void Mobile_OnFreeTxBuf(void)
{
	/* Write your code here ... */
}
/*
 ** ===================================================================
 ** Event : User_OnError (module Events)
 **
 ** Component : User [AsynchroSerial]
 ** Description :
 ** This event is called when a channel error (not the error
 ** returned by a given method) occurs. The errors can be read
 ** using <GetError> method.
 ** The event is available only when the <Interrupt
 ** service/event> property is enabled.
 ** Parameters : None
 ** Returns : Nothing
 ** ===================================================================
 */
void User_OnError(void)
{
	/* Write your code here ... */
}
/*
 ** ===================================================================
 ** Event : User_OnRxChar (module Events)
 **
 ** Component : User [AsynchroSerial]
 ** Description :
 ** This event is called after a correct character is received.
 ** The event is available only when the <Interrupt
 ** service/event> property is enabled and either the <Receiver>
 ** property is enabled or the <SCI output mode> property (if
 ** supported) is set to Single-wire mode.
 ** Parameters : None
 ** Returns : Nothing
 ** ===================================================================
 */
void User_OnRxChar(void)
{
	user_rx = 1;
}
/*
 ** ===================================================================
 ** Event : User_OnTxChar (module Events)
 **
 ** Component : User [AsynchroSerial]
 ** Description :
 ** This event is called after a character is transmitted.
 ** Parameters : None
 ** Returns : Nothing
 ** ===================================================================
 */
void User_OnTxChar(void)
{
	/* Write your code here ... */
}
/*
 ** ===================================================================
 ** Event : User_OnFullRxBuf (module Events)
 **
 ** Component : User [AsynchroSerial]
 ** Description :
 ** This event is called when the input buffer is full;
 ** i.e. after reception of the last character
 ** that was successfully placed into input buffer.
 ** Parameters : None
 ** Returns : Nothing
 ** ===================================================================
 */
void User_OnFullRxBuf(void)
{
	user_freeTx = 1;
}
/*
 ** ===================================================================
 ** Event : User_OnFreeTxBuf (module Events)
 **
 ** Component : User [AsynchroSerial]
 ** Description :
 ** This event is called after the last character in output
 ** buffer is transmitted.
 ** Parameters : None
 ** Returns : Nothing
 ** ===================================================================
 */
void User_OnFreeTxBuf(void)
{
	/* Write your code here ... */
}
/* END Events */
#ifdef __cplusplus
} /* extern "C" */
#endif
/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 ** This file was created by Processor Expert 10.3 [05.09]
 ** for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
