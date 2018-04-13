#ifndef FLAGS_H
#define FLAGS_H

#include <QFlags>
#include <QFlag>

////////////////////////////////////////////////
/*!
 * \brief
 */
struct Setup{
    ////////////////////////////////////////////////
    /*!
     * \brief The RunState enum
     */
    enum RunState{
        Boot,
        RunTime
    };

    Q_DECLARE_FLAGS(RunStates,RunState)
};
Q_DECLARE_OPERATORS_FOR_FLAGS(Setup::RunStates)

extern Setup::RunStates RunMode;

#endif // FLAGS_H

