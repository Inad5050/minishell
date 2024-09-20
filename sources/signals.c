/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:16:11 by dangonz3          #+#    #+#             */
/*   Updated: 2024/09/19 19:13:59 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 130; //Establece el valor de la variable global g_status a 130. Este valor suele indicar que el comando ha sido interrumpido por una señal (SIGINT). En muchas convenciones de shells, el código de salida 130 representa una terminación por señal de interrupción (130 = 128 + 2, donde 2 es el número de la señal SIGINT).
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

// ioctl() es una función de sistema en Unix/Linux que se utiliza para configurar parámetros y obtener información sobre dispositivos y archivos. Su uso principal es para realizar operaciones específicas de entrada/salida en dispositivos de archivo que no están cubiertas por las funciones estándar de lectura y escritura.

/* int ioctl(int fd, unsigned long request, ...);
fd es el descriptor de archivo (en este caso, STDIN_FILENO para la entrada estándar).
request es un código que especifica la operación que se desea realizar (como TIOCSTI).
El tercer parámetro es un argumento opcional, que en este caso es el carácter de nueva línea \n. */

/* ¿Qué es TIOCSTI?
TIOCSTI es una solicitud (request code) que se usa con ioctl() para insertar un carácter en el buffer de entrada del terminal. Permite simular la entrada de caracteres como si el usuario los hubiera tecleado.
TIOCSTI es una operación de bajo nivel y, por razones de seguridad y estabilidad, no es comúnmente utilizada en aplicaciones estándar. */

/* Ejemplo Simplificado
Imagina que estás escribiendo un comando y presionas Ctrl+C. Sin el uso de ioctl(), el terminal podría quedarse con un cursor al final de la línea incompleta. Esto podría causar que el nuevo prompt aparezca en una posición incorrecta.

Al insertar un carácter de nueva línea con ioctl(), se fuerza al terminal a procesar la línea actual, moviendo el cursor a una nueva línea y permitiendo que el prompt vuelva a aparecer en la parte superior de la siguiente línea limpia.

Resumen
ioctl(STDIN_FILENO, TIOCSTI, "\n"); simula la entrada de una nueva línea, moviendo el cursor a la siguiente línea en el terminal.
Esto ayuda a que el prompt del shell aparezca correctamente después de una interrupción por SIGINT, evitando que el prompt y la línea de entrada queden enredados o incompletos. */

/* 
rl_replace_line() reemplaza el contenido de la línea actual en el buffer de Readline con la cadena text.

En el contexto de tu función handle_sigint(), se pasa una cadena vacía ("") como argumento. Esto borra el contenido de la línea actual.

void rl_replace_line(const char *text, int clear_undo);
Parámetros:

text: La cadena de texto que reemplazará la línea actual. Si se pasa una cadena vacía (""), la línea actual se borrará.
clear_undo: Un entero que indica si se debe limpiar el historial de deshacer (undo). Si es 0, el historial de deshacer no se limpia; si es 1, se limpia. 

Uso en el Contexto:

Después de recibir una señal SIGINT (como Ctrl+C), rl_replace_line("", 0) borra la línea actual del buffer de Readline. Esto asegura que cualquier texto incompleto o confuso generado por la interrupción no se mantenga en la pantalla.
*/

/* 
void rl_on_new_line(void);
Descripción:

rl_on_new_line() indica a Readline que debe preparar el buffer para la entrada de una nueva línea.
Esto implica que el cursor debe moverse a una nueva línea y que cualquier texto pendiente debe ser procesado.
A menudo se utiliza para garantizar que el prompt del usuario aparezca en la nueva línea después de que se haya borrado la línea anterior o se haya realizado una actualización en el buffer.
Uso en el Contexto:

Después de borrar la línea actual con rl_replace_line(), rl_on_new_line() se asegura de que el prompt de la línea de comandos aparezca en una nueva línea. Esto ayuda a mantener la presentación limpia y evita que el prompt y la línea de entrada incompleta se mezclen.
 */

