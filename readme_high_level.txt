Controles:

	F2: Activar la interfaz de usuario (hay una pestaña de AudioTests donde
	pueden verse los valores de los recursos de sonido).
	F1: Activar / desactivar el movimiento de la cámara.
	
	Modos de audio:
	Keypad_1: activa el modo "crossfade".
		  con el "modo" crossfade activado, se puede cambiar de estado
		  con las teclas "Y" y "U" (crossfade de una pista a otra).
	Keypad_2: activa el modo "layering".
		  con el "modo" layering activado, se pueden ver todos los recursos
		  de audio con la interfaz y se puede bajar y subir el volumen de cada
		  sample.
	Keypad_3: activa el modo "branching".
		  con el modo "branching", se puede pulsar la tecla "T" para que,
		  cuando acabe la pista que se está reproduciendo, se produzca
		  una transición a la siguiente pista:
			A - transicion - B
			B - transicion - A

	Para que se reproduzcan todos los recursos de sonido, la cámara (listener)
	debe estar dentro del collider (esfera). Al tener el control de la cámara
	activado pueden pulsarse "WASD" para moverte por los ejes.

****NOTA: la cámara no está funcionando exactamente como debería, ya que
aún no está terminada.