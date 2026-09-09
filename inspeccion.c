#include <stdio.h>
#include <stdbool.h>

// Constante de validacion de input
const int MINIMO_PASAJEROS = 1;
const int MAXIMO_PASAJEROS = 250;

const float DISTANCIA_MINIMA = 0.0f;
const float DISTANCIA_MAXIMA = 150.0f;

const int HORAS_MINIMAS = 0;
const int HORAS_MAXIMAS = 23;
const int MINUTOS_MINIMOS = 0;
const int MINUTOS_MAXIMOS = 59;

const char MATAFUEGOS = 'M';
const char ZARIGUEYAS = 'Z';
const char VACIO = 'V';

// Constantes de procesamiento
const int PASAJEROS_APTOS = 180;

const float DISTANCIA_APROBADA = 50.0f;
const float DISTANCIA_NO_APROBADA = 100.0f;

const int HORA_MINIMA_APROBADA = 6;
const int HORA_MAXIMA_APROBADA = 19;

// Constantes de calculo de puntaje
const int PUNTAJE_INICIAL = 10;

const int PUNTOS_DISTANCIA_APROBADA = 0;
const int PUNTOS_DISTANCIA_REGULAR = -1;
const int PUNTOS_DISTANCIA_DESAPROBADA = -2;

const int PUNTOS_HORA_APROBADO = 0;
const int PUNTOS_HORA_DESAPROBADO = -3;

const int PUNTOS_MATAFUEGOS = 1;
const int PUNTOS_ZARIGUEYAS = -1;
const int PUNTOS_VACIO = -3;

// Constantes para la evaluación del resultado
const int PUNTAJE_APTO_MINIMO = 8;
const int PUNTAJE_REVISION_MINIMO = 5;

const char *ESTADO_APTO = "-APTO-";
const char *ESTADO_REVISION = "-REQUIERE REVISION-";
const char *ESTADO_NO_APTO = "-NO APTO-";

typedef struct horario {
    int hora;
    int minutos;
} horario_t;

/*
 * Pre: -
 * Post: Solicita al usuario la cantidad de pasajeros que realizarán el viaje y
         valida que esté dentro del rango permitido [MINIMO_PASAJEROS, MAXIMO_PASAJEROS]
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
 * Post: Solicita al usuario la distancia recorrida al frenar y 
         valida que esté dentro del rango permitido [DISTANCIA_MINIMA, DISTANCIA_MAXIMA]
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
 * Post: Solicita al usuario el horario del viaje y 
         valida que esté dentro del rango de horas y minutos permitidos 
         [HORAS_MINIMAS, HORAS_MAXIMAS] para la hora 
         [MINUTOS_MINIMOS, MINUTOS_MAXIMOS] para los minutos
*/
void pedir_horario(horario_t *horario_viaje) {
    while (((horario_viaje->hora < HORAS_MINIMAS) || (horario_viaje->hora > HORAS_MAXIMAS)) || 
           ((horario_viaje->minutos < MINUTOS_MINIMOS) || (horario_viaje->minutos > MINUTOS_MAXIMOS))) {
        printf("¿A qué hora está programado el viaje inaugural? (formato: hh:mm)");
        scanf("%d:%d", &(horario_viaje->hora), &(horario_viaje->minutos));

        if (((horario_viaje->hora < HORAS_MINIMAS) || (horario_viaje->hora > HORAS_MAXIMAS)) || 
            ((horario_viaje->minutos < MINUTOS_MINIMOS) || (horario_viaje->minutos > MINUTOS_MAXIMOS))) {
            printf("Horario inválido.\n");
        }
    }
}

/*
 * Pre: -
 * Post: Solicita al usuario el contenido del compartimento y 
         valida que esté dentro de las opciones permitidas
         [M] MATAFUEGOS
         [Z] ZARIGUEYAS
         [V] VACIO
*/
void pedir_contenido_compartimento(char *tipo) {
    while ((*tipo != MATAFUEGOS) && (*tipo != ZARIGUEYAS) && (*tipo != VACIO)) {
        printf("¿Qué encontró Marge en el compartimiento del matafuegos?\n");
        printf("[M] Matafuegos\n[Z] Zarigüeyas\n[V] Vacío\n");
        scanf(" %c", tipo);

        if ((*tipo != MATAFUEGOS) && (*tipo != ZARIGUEYAS) && (*tipo != VACIO)) {
            printf("Tipo de compartimento inválido.\n");
        }
    }
}

/*
 * Pre: 'pasajeros' debe estar dentro del rango válido [MINIMO_PASAJEROS, MAXIMO_PASAJEROS]
 * Post: Devuelve: 
         true si la cantidad de pasajeros es apta (<= PASAJEROS_APTOS), 
         false en caso de no serlo
*/
bool es_cantidad_pasajeros_apta(int pasajeros) {
    return (pasajeros <= PASAJEROS_APTOS);
}

/*
 * Pre: 'distancia' debe estar dentro del rango válido [DISTANCIA_MINIMA, DISTANCIA_MAXIMA]
 * Post: Devuelve el puntaje correspondiente a la distancia recorrida:
         PUNTOS_DISTANCIA_APROBADA si la distancia es menor o igual a la DISTANCIA_APROBADA
         PUNTOS_DISTANCIA_REGULAR si la distancia ese encuentra entre la DISTANCIA_APROBADA y la DISTANCIA_NO_APROBADA
         PUNTOS_DISTANCIA_DESAPROBADA si la distancia es mayor a la DISTANCIA_NO_APROBADA
*/
int calcular_puntos_distancia(float distancia) {
    int puntos = 0;

    if (distancia <= DISTANCIA_APROBADA) {
        puntos = PUNTOS_DISTANCIA_APROBADA;
    } else if ( distancia <= DISTANCIA_NO_APROBADA) {
        puntos = PUNTOS_DISTANCIA_REGULAR;
    } else {
        puntos = PUNTOS_DISTANCIA_DESAPROBADA;
    }

    return puntos;
}

/*
 * Pre: 'horario_viaje' debe estar dentro del rango válido:
         hora en rango [HORAS_MINIMAS, HORAS_MAXIMAS]
         minutos en [MINUTOS_MINIMOS, MINUTOS_MAXIMOS]
 * Post: Devuelve el puntaje correspondiente al horario del viaje:
         PUNTOS_HORA_APROBADO si el horario está entre la HORA_MINIMA_APROBADA y la HORA_MAXIMA_APROBADA
         PUNTOS_HORA_DESAPROBADO si el horario está fuera de ese rango
*/
int calcular_puntos_horario(horario_t horario_viaje ) {
    int puntos = 0;

    // Se decidio no incluir los minutos ya que no afectan el rango horario
    if (horario_viaje.hora >= HORA_MINIMA_APROBADA && horario_viaje.hora <= HORA_MAXIMA_APROBADA) {
        puntos = PUNTOS_HORA_APROBADO;
    } else {
        puntos = PUNTOS_HORA_DESAPROBADO;
    }

    return puntos;
}

/*
 * Pre: 'tipo' debe ser uno de los caracteres válidos
        [M] MATAFUEGOS
        [Z] ZARIGUEYAS
        [V] VACIO
 * Post: Devuelve el puntaje correspondiente al contenido del compartimento:
         PUNTOS_MATAFUEGOS si el compartimento contiene MATAFUEGOS (M)
         PUNTOS_ZARIGUEYAS si el compartimento contiene ZARIGUEYAS (Z)
         PUNTOS_VACIO si el compartimento está VACIO (V)
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
 * Pre: 'puntos_distancia' debe estar dentro de los valores válidos {PUNTOS_DISTANCIA_APROBADA, PUNTOS_DISTANCIA_REGULAR, PUNTOS_DISTANCIA_DESAPROBADA}
        'puntos_horario' debe estar dentro de los valores válidos {PUNTOS_HORA_APROBADO, PUNTOS_HORA_DESAPROBADO}
        'puntos_compartimento' debe estar dentro de los valores válidos {PUNTOS_MATAFUEGOS, PUNTOS_ZARIGUEYAS, PUNTOS_VACIO}
 * Post: Devuelve la suma del puntaje inicial y los puntos obtenidos en cada sector
*/
int calcular_puntaje_total(int puntos_distancia, int puntos_horario, int puntos_compartimento) {
    return PUNTAJE_INICIAL + puntos_distancia + puntos_horario + puntos_compartimento;
}

int main() {
    const char* estado_final = "";
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