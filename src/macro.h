#ifndef __MOC_MACRO_H
#define __MOC_MACRO_H

#define make(type, args...) moc::make_##type<args>()

#endif