#include <liblea/common.h>
#include <liblea/value.h>

static LeaError leaEvalList(LeaState* state, LeaValue* out, LeaValue list)
{
    /*
     * List evaluation:
     *
     * - If the list is empty, then it evaluates to nil
     * - If the list is non empty, then we separate the head from the tail
     *   and evaluate the head.
     * - If the head evaluates to a function, then we call that function
     *   with the tail as the arguments
     *   Else it's an error.
     */
    LeaValue head;
    LeaValue tail;

    if (leaValueGetPtr(list) == NULL)
    {
        /* Empty list */
        *out = LEA_NIL;
        return LEA_OK;
    }

    leaListCar(state, &head, list);
    leaListCdr(state, &tail, list);

    leaEval(state, &head, head);

    return leaFunctionCall(state, out, head, tail);
}

LEA_API LeaError leaEval(LeaState* state, LeaValue* out, LeaValue v)
{
    switch (leaValueGetType(v))
    {
    case LEA_TYPE_LIST:
        return leaEvalList(state, out, v);
    default:
        *out = v;
        break;
    }

    return LEA_OK;
}
