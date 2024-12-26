Ali El Ouali Lakssiouar - 29529313G

PRACTICA 9 - DCA

Comenzando con la práctica, lo primero que hice fue crear el repositorio de github en la web donde añadí un commit con el código de CuentaVocales que ya he usado en prácticas anteriores.

Seguidamente me cloné el repositorio en local con el siguiente comando: 
git clone https://github.com/Aliiell/practica9-DCA.git

Pasando a la creación de alias locales y globales lo he realizado con los siguientes comandos:
git config --global alias.co checkout
git config --global alias.br branch
git config --global alias.cm commit
git config --global alias.st status
git config alias.hist "log --oneline --graph --all"
git config alias.files "show --pretty='' --name-only"

Pasando ahora a crear las ramas, he creado la rama1 y rama2 con los siguientes comandos:
git branch rama1
git branch rama2

Y con el comando git branch podemos ver las ramas que tenemos en local:
practica9-DCA (main) $ git branch
* main
  rama1
  rama2

Para subir las ramas al repositorio remoto he usado el siguiente comando:
git push origin rama1
git push origin rama2

Ahora seguiré con la parte de git bisect y añadiré un error intencionado en el codigo y lo subiré
practica9-DCA (main) $ git add .
practica9-DCA (main) $ git commit -m "Fallo intencionado en codigo"

Ahora creo dos commits mas sobre este codigo sin arreglar dicho fallo, donde este nuevo codigo solo tendra un comentario y ya.

Hechos los dos tres commits ahora comenzaremos empleando el comando:
git bisect start

Luego marcamos el commit donde introdujimos el fallo como malo con el comando
git bisect bad

Ahora tenemos que marcar el commit previo al fallo y que funcionaba bien y primero obtenemos su id con el comando git log,
una vez tenemos el id del commit introducimos el siguiente comando:
git bisect good e2217a80fec1d8c9a5af4c36699c2447c4b9bcd5

Ahora git seleccionara un commit intermedio y tendremos que probarlo y si funciona correctamente lo marcamos con el comando git bisect good
y si ese codigo tambien falla lo marcamos con el comando git bisect bad y seguiremos reproduciendo este proceso hasta que git encuentre el fallo

Aqui podemos comprobar como pruebo primero con el commit donde añadi un comentario y lo marco como bad y git prueba con el commit donde introduje el
fallo intencionado y lo marco tambien como bad y git detecta ese automaticamente donde introduje el fallo porque no hay otro commit anterior a ese que sea intermedio
entre él y el commit "bueno".

14:43 practica9-DCA (main) $ git bisect good e2217a80fec1d8c9a5af4c36699c2447c4b9bcd5
Biseccionando: faltan 0 revisiones por probar después de esta (aproximadamente 1 paso)
[ffe54ce1125b7fffefe14bb5feffe0e651428e78] Añadido comentario de prueba
14:44 practica9-DCA ((no hay rama, comenzando biseccón en main)) $ git bisect bad
Biseccionando: faltan 0 revisiones por probar después de esta (aproximadamente 0 pasos)
[a401a44c56c5a79a1719939cb4df65c4ea5b244f] Fallo intencionado en codigo
14:49 practica9-DCA ((no hay rama, comenzando biseccón en main)) $ git bisect bad
a401a44c56c5a79a1719939cb4df65c4ea5b244f is the first bad commit
commit a401a44c56c5a79a1719939cb4df65c4ea5b244f
Author: Ali El Ouali Lakssiouar <aeol1@gcloud.ua.es>
Date:   Thu Dec 26 14:34:16 2024 +0100

    Fallo intencionado en codigo

 contador_vocales.cpp | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)
14:49 practica9-DCA ((no hay rama, comenzando biseccón en main))

Finalmente identificado la línea donde se introdujo el fallo, modificamos el codigo para que vuelva a funcionar y subimos a nuestra rama y finalizamos bisect con el comando:
git bisect reset

Subimos los cambios nuevos con el comando git push

Pasando a la parte final de uso de hooks, primero nos vemos a la carpeta .git/hooks que es onde se encuentran los .sample que son sripts que se ejecutan automáticamente cuando ocurren ciertos eventos en el repositorio como push o pull por ejemplo

En mi caso usaré el hook pre-commit, que se ejecuta antes de cada commit para realizar verificaciones adicionales.

Primero creamos el fichero con el nombre pre-commit sin extension y nos aseguramos de que sea ejecutable con el comando:
chmod +x pre-commit

Y en dicho archivo añadimos la siguiente comprobacion donde si dice TODO o FIXME evite ese commit:
#!/bin/sh

# Excluir la carpeta .git/hooks y otros archivos que no hay que comprobar
if grep -r -E "TODO|FIXME" . --exclude-dir=".git" --exclude-dir="*.md" --exclude-dir="*.txt"; then
    echo "No puedes hacer un commit mientras haya TO-DO o FIX-ME en el código"
    exit 1
fi


Modificamos nuestro codigo añadiendo un comentario que diga TODO y comprobamos si funciona el hook y vemos que sí lo hace:
practica9-DCA (main) $ git status
En la rama main
Tu rama está actualizada con 'origin/main'.

Cambios no rastreados para el commit:
  (usa "git add <archivo>..." para actualizar lo que será confirmado)
  (usa "git restore <archivo>..." para descartar los cambios en el directorio de trabajo)
	modificados:     contador_vocales.cpp

sin cambios agregados al commit (usa "git add" y/o "git commit -a")
practica9-DCA (main) $ git add .
practica9-DCA (main) $ git commit -m "Añadir TODO"
./contador_vocales.cpp:    "// TODO: Mejorar la función de contar vocales"
No puedes hacer un commit mientras haya TODO o FIXME en el código

Finalmente modificamos el archivo eliminando es alinea y probamos a hacer un commit y nos deja sin problemas.









