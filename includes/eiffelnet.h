#ifndef _EIFFELNET_H
#define _EIFFELNET_H

#include "lycee.h"
#include "eleve.h"
#include "voeux.h"
#include <stdlib.h>

#undef PRETTY_PRINT

/**
 * @brief Algorithme de répartition des élèves dans les lycées (plusieurs zones)
 * @param lycees: tableau de lycées
 * @note La répartition se fait "en place" dans les lycées
 */
void marea_algorithm(struct lycee **lycees);

#endif // _EIFFELNET_H
