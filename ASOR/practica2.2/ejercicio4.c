/*

En este caso, Ejemplo es el directorio de prueba.

$chmod 666 Ejemplo

Es 666: 110 110 110
usuario read 1 write 1 execute 0
group read 1 write 1 execute 0
otros read 1 write 1 execute 1

Cuando se intenta acceder al Ejemplo tras hacer el chmod:
[cursoredes@localhost P2]$ cd Ejemplo/
bash: cd: Ejemplo/: Permission denied

Si se hace
$chmod 777 Ejemplo
ya se podría volver a acceder.
*/
