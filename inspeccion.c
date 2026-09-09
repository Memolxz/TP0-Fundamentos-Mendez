#include <stdio.h>
#include <stdbool.h>

// Constantes para la pregunta 1
#define MINIMO_PASAJEROS 1
#define MAXIMO_PASAJEROS 250
#define PASAJEROS_APTOS 180

// Constantes para la pregunta 2
#define DISTANCIA_MINIMA 0.0f
#define DISTANCIA_MAXIMA 150.0f
#define DISTANCIA_APROBADA 50.0f
#define DISTANCIA_NO_APROBADA 100.0f

// Constantes para la pregunta 3
#define HORAS_MINIMAS 0
#define HORAS_MAXIMAS 23
#define MINUTOS_MINIMOS 0
#define MINUTOS_MAXIMOS 59
#define HORA_MINIMA_APROBADA 6
#define HORA_MAXIMA_APROBADA 19

// Constantes para la pregunta 4
#define MATAFUEGOS 'M'
#define ZARIGUEYAS 'Z'
#define VACIO 'V'

// Constantes para el cálculo de puntaje
#define PUNTAJE_INICIAL 10

#define PUNTOS_DISTANCIA_OK 0
#define PUNTOS_DISTANCIA_MEDIO -1
#define PUNTOS_DISTANCIA_MALO -2

#define PUNTOS_HORA_OK 0
#define PUNTOS_HORA_MALO -3

#define PUNTOS_MATAFUEGOS 1
#define PUNTOS_ZARIGUEYAS -1
#define PUNTOS_VACIO -3

// Constantes para la evaluación del resultado
#define PUNTAJE_APTO_MINIMO 8
#define PUNTAJE_REVISION_MINIMO 5

#define ESTADO_APTO "-APTO-"
#define ESTADO_REVISION "-REQUIERE REVISION-"
#define ESTADO_NO_APTO "-NO APTO-"

typedef struct horario {
    int hora;
    int minutos;
} horario_t;

/*
 * Pre: -
 * Post: Solicita al usuario la cantidad de pasajeros y valida que esté dentro del rango permitido [1, 250]
*/
void pedir_pasajeros(int *pasajeros) {
    while ((*pasajeros < MINIMO_PASAJEROS) || (*pasajeros > MAXIMO_PASAJEROS)) {
        printf("¿Cuántos pasajeros realizarán el viaje inaugural?");
        scanf("%d", pasajeros);

        if ((*pasajeros < MINIMO_PASAJEROS) || (*pasajeros > MAXIMO_PASAJEROS)) {
            printf("Cantidad de pasajeros inválida.\n");
        }
    }
}

/*
 * Pre: -
 * Post: Solicita al usuario la distancia recorrida y valida que esté dentro del rango permitido [0.0, 150.0]
*/
void pedir_distancia(float *distancia) {
    while ((*distancia < DISTANCIA_MINIMA) || (*distancia > DISTANCIA_MAXIMA)) {
        printf("¿Qué distancia recorrió el monorriel durante la prueba de los frenos marca Patito?");
        scanf("%f", distancia);

        if ((*distancia < DISTANCIA_MINIMA) || (*distancia > DISTANCIA_MAXIMA)) {
            printf("Distancia inválida.\n");
        }
    }
}

/*
 * Pre: -
 * Post: Solicita al usuario el horario del viaje y valida que esté dentro del rango permitido [00:00, 23:59]
*/
void pedir_horario(horario_t *horario_viaje) {
    while (((horario_viaje->hora < HORAS_MINIMAS) || (horario_viaje->hora > HORAS_MAXIMAS)) || 
           ((horario_viaje->minutos < MINUTOS_MINIMOS) || (horario_viaje->minutos > MINUTOS_MAXIMOS))) {
        printf("¿A qué hora está programado el viaje inaugural? (formato: hh:mm)");
        scanf("%d:%d", &horario_viaje->hora, &horario_viaje->minutos);

        if (((horario_viaje->hora < HORAS_MINIMAS) || (horario_viaje->hora > HORAS_MAXIMAS)) || 
            ((horario_viaje->minutos < MINUTOS_MINIMOS) || (horario_viaje->minutos > MINUTOS_MAXIMOS))) {
            printf("Horario inválido.\n");
        }
    }
}

/*
 * Pre: -
 * Post: Solicita al usuario el contenido del compartimento y valida que esté dentro de las opciones permitidas [M/Z/V]
*/
void pedir_contenido_compartimento(char *tipo) {
    while ((*tipo != MATAFUEGOS) && (*tipo != ZARIGUEYAS) && (*tipo != VACIO)) {
        printf("¿Qué encontró Marge en el compartimiento del matafuegos?");
        scanf(" %c", tipo);

        if ((*tipo != MATAFUEGOS) && (*tipo != ZARIGUEYAS) && (*tipo != VACIO)) {
            printf("Tipo de compartimento inválido.\n");
        }
    }
}

/*
 * Pre: 'pasajeros' debe estar dentro del rango válido [1, 250]
 * Post: Devuelve true si la cantidad de pasajeros es apta (<=180), false en caso de no serlo
*/
bool es_cantidad_pasajeros_apta(int pasajeros) {
    return (pasajeros <= PASAJEROS_APTOS);
}

/*
 * Pre: 'distancia' debe estar dentro del rango válido [0.0, 150.0]
 * Post: Devuelve el puntaje correspondiente a la distancia recorrida:
         0 puntos si la distancia es menor o igual a 50.0
        -1 puntos si la distancia es mayor a 50.0 y menor o igual a 100.0
        -2 puntos si la distancia es mayor a 100.0
*/
int calcular_puntos_distancia(float distancia) {
    int puntos = 0;

    if (distancia <= DISTANCIA_APROBADA) {
        puntos = PUNTOS_DISTANCIA_OK;
    } else if ( distancia <= DISTANCIA_NO_APROBADA) {
        puntos = PUNTOS_DISTANCIA_MEDIO;
    } else {
        puntos = PUNTOS_DISTANCIA_MALO;
    }

    return puntos;
}

/*
 * Pre: 'horario_viaje' debe contener hora en rango [0, 23] y minutos en [0, 59]
 * Post: Devuelve el puntaje correspondiente al horario del viaje:
         0 puntos si el horario está entre 6:00 y 19:59
        -3 puntos si el horario está fuera de ese rango
*/
int calcular_puntos_horario(horario_t horario_viaje ) {
    int puntos = 0;

    // Se decidio no incluir los minutos ya que no afectan el rango horario
    if (horario_viaje.hora >= HORA_MINIMA_APROBADA && horario_viaje.hora <= HORA_MAXIMA_APROBADA) {
        puntos = PUNTOS_HORA_OK;
    } else {
        puntos = PUNTOS_HORA_MALO;
    }

    return puntos;
}

/*
 * Pre: 'tipo' debe ser uno de los caracteres válidos [M/Z/V]
 * Post: Devuelve el puntaje correspondiente al contenido del compartimento:
         1 punto si el compartimento contiene un matafuegos (M)
        -1 punto si el compartimento contiene zarigüeyas (Z)
        -3 puntos si el compartimento está vacío (V)
*/
int calcular_puntos_compartimento(char tipo) {
    int puntos = 0;

    if (tipo == MATAFUEGOS) {
        puntos = PUNTOS_MATAFUEGOS;
    } else if (tipo == ZARIGUEYAS) {
        puntos = PUNTOS_ZARIGUEYAS;
    } else if (tipo == VACIO) {
        puntos = PUNTOS_VACIO;
    }

    return puntos;
}

/*
 * Pre: 'puntos_distancia' debe estar dentro de los valores válidos {-2, -1, 0}
        'puntos_horario' debe estar dentro de los valores válidos {-3, 0}
        'puntos_compartimento' debe estar dentro de los valores válidos {-3, -1, 1}
 * Post: Devuelve la suma del puntaje inicial y los puntos obtenidos en cada sector
*/
int calcular_puntaje_total(int puntos_distancia, int puntos_horario, int puntos_compartimento) {
    return PUNTAJE_INICIAL + puntos_distancia + puntos_horario + puntos_compartimento;
}

int main() {
    char* estado_final = "";
    int pasajeros = -1;
    pedir_pasajeros(&pasajeros);

    if (!es_cantidad_pasajeros_apta(pasajeros)) {
        estado_final = ESTADO_NO_APTO;
    } else {
        float distancia = -1.0f;
        horario_t horario_viaje = {-1, -1};
        char tipo_compartimento = ' ';
        
        pedir_distancia(&distancia);
        pedir_horario(&horario_viaje);
        pedir_contenido_compartimento(&tipo_compartimento);

        int puntos_distancia = calcular_puntos_distancia(distancia);
        int puntos_horario = calcular_puntos_horario(horario_viaje);
        int puntos_compartimento = calcular_puntos_compartimento(tipo_compartimento);
    
        int puntaje_total = calcular_puntaje_total(puntos_distancia, puntos_horario, puntos_compartimento);

        if (puntaje_total >= PUNTAJE_APTO_MINIMO) {
            estado_final = ESTADO_APTO;
        } else if (puntaje_total >= PUNTAJE_REVISION_MINIMO) {
            estado_final = ESTADO_REVISION;
        } else {
            estado_final = ESTADO_NO_APTO;
        }
    }

    printf("Con las respuestas brindadas, el estado de la inspección de seguridad del monorriel es: %s", estado_final);

    return 0;
}