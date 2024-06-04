#ifndef __MOC_CLOCK_H
#define __MOC_CLOCK_H

#include "type.h"

namespace moc {

i64 get_tick();
void tick(i64 period_time);

};

#endif