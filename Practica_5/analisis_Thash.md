# Análisis de tablas de dispersión

* *Stefan Giovanni Imperato Lozano*

## Tamaño de tabla: 117497
| función    | máximo de colisiones | factor de carga | promedio de colisiones | num. veces que han habido 10 o más colisiones |
|------------|:--------------------:|:---------------:|:----------------------:|:---------------------------------------------:|
| Cuadratica |          27          |      0.65       |           0            |                      238                      |
| Doble 1    |          18          |      0.65       |           0            |                      112                      |
| Doble 2    |          19          |      0.65       |           0            |                      98                       |

## Tamaño de tabla: 112303
| función    | máximo de colisiones | factor de carga | promedio de colisiones | num. veces que han habido 10 o más colisiones |
|------------|:--------------------:|:---------------:|:----------------------:|:---------------------------------------------:|
| Cuadratica |          27          |      0.68       |           0            |                      285                      |
| Doble 1    |          26          |      0.68       |           0            |                      193                      |
| Doble 2    |          23          |      0.68       |           0            |                      146                      |

## Justificación de la configuración elegida
He optado por usar un factor de carga del 0.65 y la función de dispersión doble 2. Esta, a pesar de tener un máximo de colisiones de 19 frente a las 18 de la dispersión doble 1, solo se superan las 10 colisiones un total de 98 veces, frente a las 112 de la dispersión doble 1. Por tanto, en términos de eficiencia, la mejor de las soluciones sería optar por la función de dispersión doble con un factor de carga del 0.65.

## Eficiencia de la tabla.
Si realizamos la búsqueda de 1.000.000 elementos en la tabla y la comparamos con la búsqueda del mismo número de elementos en un mapa podemos observar que el mapa es casi 5 veces más lento.

