#ifndef FLAGS_H
#define FLAGS_H

#include <QFlag>

struct Setup{
    enum RunState{
        Boot,
        RunTime
    };
    Q_DECLARE_FLAGS(RunStates,RunState)
};
Q_DECLARE_OPERATORS_FOR_FLAGS(Setup::RunStates)

#define BOOT 1

#endif // FLAGS_H
