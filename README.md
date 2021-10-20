# EA076
Code developed during the course of EA076 - Embedded Systems Laboratory (2nd semester of 2020) at University of Campinas

---

### Project 1 -- MQTT-based infra-structure
Simple IoT system using an ARM-based microcontroller (Freedom FRDM-KL25) together with a ESP-01 module. 

The ESP-01 receives commands from the KL25 via serial UART to connect to a network, MQTT broker, subscribe to specified topics and eventually send messages to a specified topic.
All data received in one of the subscribed topics is relayed to the KL25 via serial UART.

As a proof of concept, the KL25 controls an onboard RGB LED via commands received from MQQT, while sending temperature readings from a I2C sensor to a specific topic.
