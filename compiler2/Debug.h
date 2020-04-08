#pragma once
#include <iostream>
#define ShowMessages 1
#if ShowMessages
#define MSG(X) (cout << X << endl)
#else
#define MSG(X)
#endif
