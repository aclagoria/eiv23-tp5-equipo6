# ELECTRÓNICA IV 2023. Trabajo Práctico n°5 : Actuador de posición angular. 

## Objetivo
Elaborar un controlador de actuación de  un servomotor mediante comandos desde la PC. 

## Desarrollo
Para realizar el controlador se dispuso de:
- Placa con microcontrolador: **STM32F103C8T6**
- Debugger: **STLINK_V2**
- Adaptador USB a UART: **CH340**
- Servomotor: **SG90**

Se debió configurar en el microcontrolador los periféricos :
- **USART 1** : Para establecer la comunicación bidireccional entre el microcontrolador y la PC.
- **TIM 2** : Para controlar mediante una señal PWM la posición del ángulo del servomotor.

## Descripción de funcionalidad
El controlador responde a los comandos:
- **ANG?** : Para preguntar la posición del ángulo del servomotor. Muestra por pantalla el ángulo en grados.
- **ANG <num>** : Donde <num> debe ser un numero entero entre 0 y 180, para establecer la posición del ángulo del servomotor. Muestra por pantalla el ángulo establecido en grados. Si se ingresa un numero mayor a 180 muestra un mensaje de error de ángulo.
  
Cualquier combinación de caracteres que se ingrese, distinta a las ya mencionadas, muestra en pantalla un mensaje de error de comando.
