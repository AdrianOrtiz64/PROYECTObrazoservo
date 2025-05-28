# PROYECTObrazoservo
Repositorio para constancia de versiones de trabajo para el proyecto 2 de electrónica digital

Introducción:

El propósito general del proyecto es hacer funcionar una garra mecánica accionada por cuatro servomotores mediante programación en arduino.
Siendo un proyecto de evaluación se busca tanto un funcionamiento óptimo de un archivo .ino como de una correcta configuración electrónica.

Información de uso:

Para el funcionamiento del archivo se requiere tanto del programa ARDUINO IDE como de una placa arduino para la implementación del código.
En la parte física se requiere principalmente de 5 potenciometros para el control de cada motor y el cambio de modo, 2 botones para el alternado de poses y 4 servo motores para mover las partes de la garra implementada.

Ayuda y Soporte:

Guía para la construcción de la garra: https://www.instructables.com/Pocket-Sized-Robot-Arm-meArm-V04/

Información de contacto de los creadores:

ort231133@uvg.edu.gt
gam23546@uvg.edu.gt

Documentación:

El archivo se divide en cuatro partes:
1. Declaración de variables que se emplea a lo largo de todo el archivo
2. void loop, donde se declara el ciclo constante que define el cambio de modo segun el valor del potenciómetro de cambio
3. modo manual, hace una lectura de cada uno de los 4 potenciometros de control y un mapeo para imprimir los valores según los grados de libertad.
4. modo automático, entra en un ciclo de verificación para cada botón donde mediante un contador puede moverse a una pose definida u otra.
