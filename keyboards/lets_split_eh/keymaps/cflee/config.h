#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

// Usually KC_GESC sends ` on with GUI/Cmd, making it impossible to send Cmd-Opt-Esc.
// We can force it to send Esc when some modifier(s) are active.
// Since we do want Cmd-Esc to send Cmd-`, override this behaviour for ALT/Opt.
#define GRAVE_ESC_ALT_OVERRIDE

#endif
