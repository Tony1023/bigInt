# bigInt: used a vector of chars to represent digits

# A BigInt class that mimics the behavior of the int type, with (nearly) no upper/lower value bounds.

p_int is the nonnegative implementation, corresponding to unsigned int. It supports most of the commonly used funcionalities (except divide yet) of the primitive type unsigned int. 

When a smaller unsigned int minuses a larger one, an exception (NegativeExcept) is thrown.

A complete implementation that supports both negative and positive is still on the way.
