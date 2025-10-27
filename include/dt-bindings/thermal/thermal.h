/*
 * This header provides constants for most thermal bindings.
 *
 * Copyright (C) 2013 Texas Instruments
 *	Eduardo Valentin <eduardo.valentin@ti.com>
 *
 * GPLv2 only
 */

#ifndef _DT_BINDINGS_THERMAL_THERMAL_H
#define _DT_BINDINGS_THERMAL_THERMAL_H

/* On cooling devices upper and lower limits */
#define THERMAL_NO_LIMIT		(~0)
#define THERMAL_MAX_LIMIT		(THERMAL_NO_LIMIT - 1)
#define THERMAL_LIMIT_MINUS_1  (THERMAL_MAX_LIMIT - 1)
#define THERMAL_LIMIT_MINUS_5  (THERMAL_MAX_LIMIT - 5)
#define THERMAL_LIMIT_MINUS_6  (THERMAL_MAX_LIMIT - 6)

#endif

