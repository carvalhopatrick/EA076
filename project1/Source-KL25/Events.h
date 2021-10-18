/* ###################################################################
**     Filename    : Events.h
**     Project     : roteiro1
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2021-01-17, 20:37, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
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

#ifdef __cplusplus
extern "C" {
#endif 

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void);


/*
** ===================================================================
**     Event       :  Mobile_OnError (module Events)
**
**     Component   :  Mobile [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Mobile_OnError(void);

/*
** ===================================================================
**     Event       :  Mobile_OnRxChar (module Events)
**
**     Component   :  Mobile [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Mobile_OnRxChar(void);

/*
** ===================================================================
**     Event       :  Mobile_OnTxChar (module Events)
**
**     Component   :  Mobile [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Mobile_OnTxChar(void);

/*
** ===================================================================
**     Event       :  User_OnError (module Events)
**
**     Component   :  User [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void User_OnError(void);

/*
** ===================================================================
**     Event       :  User_OnRxChar (module Events)
**
**     Component   :  User [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void User_OnRxChar(void);

/*
** ===================================================================
**     Event       :  User_OnTxChar (module Events)
**
**     Component   :  User [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void User_OnTxChar(void);

/*
** ===================================================================
**     Event       :  User_OnFullRxBuf (module Events)
**
**     Component   :  User [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void User_OnFullRxBuf(void);

/*
** ===================================================================
**     Event       :  User_OnFreeTxBuf (module Events)
**
**     Component   :  User [AsynchroSerial]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void User_OnFreeTxBuf(void);

/*
** ===================================================================
**     Event       :  Mobile_OnFullRxBuf (module Events)
**
**     Component   :  Mobile [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Mobile_OnFullRxBuf(void);

/*
** ===================================================================
**     Event       :  Mobile_OnFreeTxBuf (module Events)
**
**     Component   :  Mobile [AsynchroSerial]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Mobile_OnFreeTxBuf(void);

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
